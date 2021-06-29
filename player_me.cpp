//
//  main.cpp
//  mp3
//
//  Created by 朱季葳 on 2021/6/28.
//

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits.h>
#include <algorithm>
using namespace std;
int player;
const int SIZE = 8;
const int weight[8][8] =
{
    { 65,  -3, 6, 4, 4, 6,  -3, 65},
    {-3, -29, 3, 1, 1, 3, -29, -3},
    {6,   3, 5, 3, 3, 5,   3,  6},
    {4,   1, 3, 1, 1, 3,   1,  4},
    {4,   1, 3, 1, 1, 3,   1,  4},
    {6,   3, 5, 3, 3, 5,   3,  6},
    {-3, -29, 3, 1, 1, 3, -29, -3},
    {65,  -3, 6, 4, 4, 6,  -3, 65},
    
};

std::array<std::array<int, SIZE>, SIZE> board;
struct Point {
    int x, y;
    int data;
    Point() : Point(0, 0) {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator==(const Point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const Point& rhs) const {
        return !operator==(rhs);
    }
    Point operator+(const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator-(const Point& rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
};
int state_value(std::array<std::array<int, SIZE>, SIZE> &board);

class OthelloBoard {
public:
    enum SPOT_STATE {
        EMPTY = 0,
        BLACK = 1,
        WHITE = 2
    };
    
    static const int SIZE = 8;
    const std::array<Point, 8> directions{{
        Point(-1, -1), Point(-1, 0), Point(-1, 1),
        Point(0, -1), /*{0, 0}, */Point(0, 1),
        Point(1, -1), Point(1, 0), Point(1, 1)
    }};
    std::array<std::array<int, SIZE>, SIZE> board;
    std::vector<Point> next_valid_spots;
    std::array<int, 3> disc_count;
    int cur_player;
    bool done;
    int winner;
    OthelloBoard &operator =(const OthelloBoard& pre)
    {
        this->board=pre.board;
        this->next_valid_spots=pre.next_valid_spots;
        this->disc_count=pre.disc_count;
        this->cur_player=pre.cur_player;
        this->done=pre.done;
        this->winner=pre.winner;
        return *this;
    }
    int get_next_player(int player) const {
        return 3 - player;
    }
    bool is_spot_on_board(Point p) const {
        return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
    }
    int get_disc(Point p) const {
        return board[p.x][p.y];
    }
    void set_disc(Point p, int disc) {
        board[p.x][p.y] = disc;
    }
    bool is_disc_at(Point p, int disc) const {
        if (!is_spot_on_board(p))
            return false;
        if (get_disc(p) != disc)
            return false;
        return true;
    }
    bool is_spot_valid(Point center) const {
        if (get_disc(center) != EMPTY)
            return false;
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, cur_player))
                    return true;
                p = p + dir;
            }
        }
        return false;
    }
    void flip_discs(Point center) {
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            std::vector<Point> discs({p});
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY) {
                if (is_disc_at(p, cur_player)) {
                    for (Point s: discs) {
                        set_disc(s, cur_player);
                    }
                    disc_count[cur_player] += discs.size();
                    disc_count[get_next_player(cur_player)] -= discs.size();
                    break;
                }
                discs.push_back(p);
                p = p + dir;
            }
        }
    }
    OthelloBoard() {
        reset();
    }
    void reset() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = EMPTY;
            }
        }
        board[3][4] = board[4][3] = BLACK;
        board[3][3] = board[4][4] = WHITE;
        cur_player = BLACK;
        disc_count[EMPTY] = 8*8-4;
        disc_count[BLACK] = 2;
        disc_count[WHITE] = 2;
        next_valid_spots = get_valid_spots();
        done = false;
        winner = -1;
    }
    std::vector<Point> get_valid_spots() const {
        std::vector<Point> valid_spots;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                Point p = Point(i, j);
                if (board[i][j] != EMPTY)
                    continue;
                if (is_spot_valid(p))
                    valid_spots.push_back(p);
            }
        }
        return valid_spots;
    }
    bool put_disc(Point p) {
        if(!is_spot_valid(p)) {
            winner = get_next_player(cur_player);
            done = true;
            return false;
        }
        set_disc(p, cur_player);
        disc_count[cur_player]++;
        disc_count[EMPTY]--;
        flip_discs(p);
        // Give control to the other player.
        cur_player = get_next_player(cur_player);
        next_valid_spots = get_valid_spots();
        // Check Win
        if (next_valid_spots.size() == 0) {
            cur_player = get_next_player(cur_player);
            next_valid_spots = get_valid_spots();
            if (next_valid_spots.size() == 0) {
                // Game ends
                done = true;
                int white_discs = disc_count[WHITE];
                int black_discs = disc_count[BLACK];
                if (white_discs == black_discs) winner = EMPTY;
                else if (black_discs > white_discs) winner = BLACK;
                else winner = WHITE;
            }
        }
        return true;
    }

};
std::vector<Point> next_valid_spots;
int alphabeta(Point& p,int depth,int alpha,int beta,bool maximizing,OthelloBoard &pre);

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void read_valid_spots(std::ifstream& fin) {
    int n_valid_spots;
    fin >> n_valid_spots;
    int x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        fin >> x >> y;
        next_valid_spots.push_back({x, y});
    }
}
int alphabeta(Point& p,int depth,int alpha,int beta,bool maximizing,OthelloBoard &pre)
{
    OthelloBoard game;
    game=pre;
    int len1=game.next_valid_spots.size();
    game.put_disc(p);
    int len2=game.next_valid_spots.size();
    std::vector<Point> valid_spots=game.next_valid_spots;
    int value=0;
    if(depth==5||game.done)
    {
        value= state_value(game.board)+15*(len1-len2);
        return value;
    }
    
    if(maximizing)
    {
        value=INT_MIN;
        for(auto i=0;i<len2;i++)
        {
            value=std::max(value, alphabeta(valid_spots[i], depth+1, alpha, beta, false,game));
            alpha=std::max(alpha, value);
            if(alpha>=beta)break;
        }
        return value;
    }
    else
    {
        value=INT_MAX;
        for(auto i=0;i<len2;i++)
        {
            value=std::min(value, alphabeta(valid_spots[i], depth+1, alpha, beta, true,game));
            beta=std::min(value, beta);
            if(beta<=alpha)break;
        }
        return value;
    }
}

void write_valid_spot(std::ofstream& fout) {
    int n_valid_spots = next_valid_spots.size();
    int max=0;
    int index=0;
    OthelloBoard game;
    game.board=board;
    game.next_valid_spots=next_valid_spots;
        for (int i = 0; i < n_valid_spots; i++)
        {
            int value=alphabeta(next_valid_spots[i], 0, -INT_MAX, INT_MAX, true,game);
            if(value>max)
            {
                max=value;
                index=i;
            }
        }
    Point p = next_valid_spots[index];
    // Remember to flush the output to ensure the last action is written to file.
    fout << p.x << " " << p.y << std::endl;
    fout.flush();
}
int state_value(std::array<std::array<int, SIZE>, SIZE> &board)
{
    int value=0;
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if(board[i][j]==player)
            {
                value+=weight[i][j];
            }
            else if(board[i][j]==3-player)
            {
                value-=weight[i][j];
            }
        }
    }
    
    return value;
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    read_valid_spots(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}