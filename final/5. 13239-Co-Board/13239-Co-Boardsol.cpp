// model solution by Yazmau
#include <iostream>
#include <queue>
#include <set>
using namespace std;
class Board {
	public:
		Board() {}
		Board(int *initVal) {
			step = 0;
			for(int i=0;i<8;i++)	val[i] = initVal[i];
		}
		void move() {
			step++;
			for(int i=0;i<7;i++)	swap(val[i], val[7]);
		}
		void adjSwap(int i) {
			step++;
			swap(val[i], val[(i + 1) % 8]);
		}
		void oppSwap(int i) {
			step++;
			swap(val[i], val[(i + 4) % 8]);
		}
		int getStep() { return step; }
		bool operator < (const Board &a) const {
			for(int i=0;i<8;i++)	if(val[i] != a.val[i])	return val[i] < a.val[i];
			return false;
		}
		bool operator == (const Board &a) const{
			for(int i=0;i<8;i++)	if(val[i] != a.val[i])	return false;
			return true;
		}
	private:
		int step, val[8];
};
void updateState(Board &nextBoard, queue<Board> &q, set<Board> &visBoard, const Board& boardB, int &ans) {
	if(nextBoard == boardB) {
		ans = nextBoard.getStep();
		return;
	}
	if(visBoard.count(nextBoard) == 1)	return;
	q.push(nextBoard);
	visBoard.insert(nextBoard);
}
int main() {
	int t;
	cin >> t;
	while(t--) {
		Board boardA, boardB;
		for(int i=0;i<2;i++) {
			int initVal[8];
			for(int j : {0, 1, 2, 7, 3, 6, 5, 4})
				cin >> initVal[j];
			(i == 0 ? boardA : boardB) = Board(initVal);
		}

		int ans = -1;
		if(boardA == boardB)
			ans = 0;
		else {
			queue<Board> q;
			q.push(boardA);
			
			set<Board> visBoard;
			visBoard.insert(boardA);

			while(!q.empty() && ans == -1) {
				Board now = q.front();	q.pop();
				
				Board nextBoard = now;
				nextBoard.move();
				updateState(nextBoard, q, visBoard, boardB, ans);

				for(int i=0;i < 8 && ans == -1;i++) {
					nextBoard = now;
					nextBoard.adjSwap(i);
					updateState(nextBoard, q, visBoard, boardB, ans);
				}
				
				for(int i=0;i < 4 && ans == -1;i++) {
					nextBoard = now;
					nextBoard.oppSwap(i);
					updateState(nextBoard, q, visBoard, boardB, ans);
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
