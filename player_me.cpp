#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits.h>
#include <algorithm>
#include <cmath>
using namespace std;
int player;
const int SIZE = 8;
int weight[8][8] =
{
          {400, -30, 11, 8, 8, 11, -30, 400},
          {-30, -70, -4, 1, 1, -4, -70, -30},
          {11, -4, 2, 2, 2, 2, -4, 11},
          {8, 1, 2, -3, -3, 2, 1, 8},
          {8, 1, 2, -3, -3, 2, 1, 8},
          {11, -4, 2, 2, 2, 2, -4, 11},
          {-30, -70, -4, 1, 1, -4, -70, -30},
          {400, -30, 11, 8, 8, 11, -30, 400}
    
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
    int all_disc;
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
int state_value(OthelloBoard& pre,int len1,int flag);

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
        
        if(maximizing)
            value=state_value(game,len1,1);
        else
            value=state_value(game,len1,0);
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
    int max=INT_MIN;
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
int state_value(OthelloBoard& pre,int len1,int flag)
{
    int my_value=0;int enemy_value=0;
    int total=pre.disc_count[player]+pre.disc_count[3-player];
    int dx[8]={-1,-1,0,1,1,1,0,-1};
    int dy[8]={0,1,1,1,0,-1,-1,-1};
    int p=0,c=0,l=0,m=0,d=0,f=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(pre.board[i][j]==player)d+=weight[i][j];
            else if(pre.board[i][j]==3-player)d-=weight[i][j];
           if(pre.board[i][j]!=0)
            {
                for(int k=0;k<8;k++)
                {
                    int x=i+dx[k];int y=j+dy[k];
                    if(x>=0&&x<8&&y>=0&&y<8&&pre.board[x][y]==0)
                    {
                        if(pre.board[i][j]==player)my_value++;
                        else if(pre.board[i][j]==3-player)enemy_value++;
                        break;
                    }
                }
            }
        }
    }
    
        p=100*(pre.disc_count[player]-pre.disc_count[3-player]);
    
    if(my_value>enemy_value)
        f=-100*my_value/(my_value+enemy_value);
    else if(enemy_value>my_value)
        f=100*enemy_value/(my_value+enemy_value);

    
    // Corner occupancy
    my_value=enemy_value=0;
        if(pre.board[0][0] == player) my_value++;
        else if(pre.board[0][0] == 3-player) enemy_value+=10;
        if(pre.board[0][7] == player) my_value++;
        else if(pre.board[0][7] == 3-player) enemy_value+=10;
        if(pre.board[7][0] == player) my_value++;
        else if(pre.board[7][0] == 3-player) enemy_value+=10;
        if(pre.board[7][7] == player) my_value++;
        else if(pre.board[7][7] == 3-player) enemy_value+=10;
        c = 25 * (my_value-enemy_value);

    // Corner closeness
    my_value=enemy_value=0;
        if(pre.board[0][0] == 0)   {
            if(pre.board[0][1] == player) my_value+=10;
            else if(pre.board[0][1] == 3-player) enemy_value++;
            if(pre.board[1][1] == player) my_value+=10;
            else if(pre.board[1][1] == 3-player) enemy_value++;
            if(pre.board[1][0] == player) my_value+=10;
            else if(pre.board[1][0] == 3-player) enemy_value++;
        }
    if(pre.board[0][7] == 0)   {
        if(pre.board[0][6] == player) my_value+=10;
        else if(pre.board[0][6] == 3-player) enemy_value++;
        if(pre.board[1][6] == player) my_value+=10;
        else if(pre.board[1][6] == 3-player) enemy_value++;
        if(pre.board[1][7] == player) my_value+=10;
        else if(pre.board[1][7] == 3-player) enemy_value++;
    }
    if(pre.board[7][0] == 0)   {
        if(pre.board[7][1] == player) my_value+=10;
        else if(pre.board[7][1] == 3-player) enemy_value++;
        if(pre.board[6][1] == player) my_value+=10;
        else if(pre.board[6][1] == 3-player) enemy_value++;
        if(pre.board[6][0] == player) my_value+=10;
        else if(pre.board[6][0] == 3-player) enemy_value++;
    }
    
    if(pre.board[7][7] ==0)   {
        if(pre.board[6][7] == player) my_value+=10;
        else if(pre.board[6][7] == 3-player) enemy_value++;
        if(pre.board[6][6] == player) my_value+=10;
        else if(pre.board[6][6] == 3-player) enemy_value++;
        if(pre.board[7][6] == player) my_value+=10;
        else if(pre.board[7][6] == 3-player) enemy_value++;
    }
    l = -12.5 * (my_value-enemy_value);
    if(flag)
    {
        my_value=pre.next_valid_spots.size();
        enemy_value=len1;
    }
    else
    {
        my_value=len1;
        enemy_value=pre.next_valid_spots.size();
    }
   
    if(my_value>enemy_value)
        m=100*my_value/(my_value+enemy_value);
    else if(my_value<enemy_value)
        m=-100*enemy_value/(my_value+enemy_value);
    
    int value=0;
    //c:corner occupy //p:what have the most amount of discs
    //m:modibility    //l:corner closeness
    //d:weight         //f:防止一整片被佔據
    //初期想辦法佔據重要位置，越多選擇越好
    
    //中期要想辦法增加穩定子，並把對手逼到牆角
//if(total<25)
//(3,5)
 //100m-->(2,3)
 //if(total<25)value= 10*p+802*c +382*l + 79*m+ 74*f+100*d;
 //else  value=10*p + 802*c +382*l + 79*m+ 74*f+10*d;
if(total<25)value= 10*p+802*c +382*l + 79*m+ 74*f+50*d;

  /* //  value=(10 * p) + (1000 * c) + (382.026 * l) + (300 * m)  + (300 * d)+200*f;*/
 else  value=10*p + 802*c +390*l + 100*m+ 200*f+50*d;
    return value;
    
    //10*p + 802*c +382*l + 79*m+ 74*f+10*d;
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

