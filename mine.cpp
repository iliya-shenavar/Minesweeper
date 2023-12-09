#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <time.h>

using namespace std;

const int EASY_ROWS = 10;
const int EASY_COLS = 10;
const int EASY_BOMBS = 10;
int bombsRemaining = 10;

const int HARD_ROWS = 16;
const int HARD_COLS = 16;
const int HARD_BOMBS = 40;


const int VERY_HARD_ROWS = 16;
const int VERY_HARD_COLS = 40;
const int VERY_HARD_BOMBS = 99;

struct Square {
    bool bomb;
    bool revealed;
    bool flagged;
    int bombsNearby;
    
};

void printBoard(const vector<vector<Square>> &board, int numBombs, int numFlags) {
    cout << "   ";
    for (int col = 0; col < board[0].size(); col++) {
        cout << col << " ";
    }
    cout << endl;
    for (int row = 0; row < board.size(); row++) {
        cout << row << " |";
        for (int col = 0; col < board[row].size(); col++) {
            char c;
            if (!board[row][col].revealed) {
                c = ' ';
            } else if (board[row][col].bomb) {
                c = '*';
            } else if (board[row][col].bombsNearby > 0) {
                c = '0' + board[row][col].bombsNearby;
            } else {
                c = '-';
            }
            if (board[row][col].flagged) {
                c = '#';
            }
            cout << c << "|";
        }
        cout << endl;
    }
 
    
}

bool checkWin(const vector<vector<Square>> &board, int numBombs) {
    int numFlags = 0;
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            if (!board[row][col].revealed && !board[row][col].flagged) {
                return false;
            }
            if (board[row][col].flagged) {
                numFlags++;
            }
        }
        return true;
    }
}



void revealAll(vector<vector<Square>> &board) {
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            board[row][col].revealed = true;
        }
    }
}

int countBombsNearby(const vector<vector<Square>> &board, int row, int col) {
    const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int r = row + dr[i];
        int c = col + dc[i];
        if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size()) {
            if (board[r][c].bomb) {
                count++;
            }
        }
    }
    return count;
}


bool revealSquares(vector<vector<Square>> &board, int row, int col) {
    if (row < 0 || row >= board.size() || col < 0 || col >= board[row].size()) {
        return false;
    }
    Square &square = board[row][col];
    if (square.flagged || square.revealed) {
		return false;
    }
    square.revealed = true;
    if (square.bomb) {
   	bombsRemaining = bombsRemaining - 1;
   		cout << "true";
        return true;
    }
    if (square.bombsNearby > 0) {
        return false;
    }
    const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++) {
        int r = row + dr[i];
        int c = col + dc[i];
        
        if (r >= 0 && r < board.size() && c >= 0 && c < board[r].size() && board[r][c].flagged) {
          
            if(board[r][c].bomb){
            
                return true;
                  
                  
            }
        } else {
            revealSquares(board, r, c);
        }
    }
    return false;
}

void insertFlag(vector<vector<Square>> &board, int row, int col) {
Square &square = board[row][col];
if (!square.revealed) {
square.flagged = !square.flagged;
}
    if (square.bomb) {
   	bombsRemaining = bombsRemaining - 1;
      }
}


void initializeBoard(vector<vector<Square>> &board, int numBombs) {

int count = 0;
while (count < numBombs) {

int row = rand() % board.size();
int col = rand() % board[row].size();
if (!board[row][col].bomb) {
board[row][col].bomb = true;
count++;
}
}

for (int row = 0; row < board.size(); row++) {
for (int col = 0; col < board[row].size(); col++) {
board[row][col].bombsNearby = countBombsNearby(board, row, col);
}
}
}
void game(int rows, int cols, int numBombs){

		time_t start_time = time(nullptr);
					
					vector<vector<Square>> board(rows, vector<Square>(cols));
initializeBoard(board, numBombs);
bool gameOver = false;

while (!gameOver) {
	system("cls");

int numFlags = 0;
for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board[row].size(); col++) {
        if (board[row][col].flagged) {
            numFlags++;
        }
    }
}

printBoard(board, numBombs, numFlags);


int x, y;
int action;
	
cout << endl << "Bombs remaining: " << bombsRemaining << endl;
time_t end_time = time(nullptr);

			double elapsed_time = difftime(end_time, start_time);
			cout << "Elapsed time: " << elapsed_time << " seconds\n";
			cout << "Choose an action:" << endl;
			cout << "1. Choose a unit" << endl;
			cout << "2. Insert a flag" << endl;

cin >> action;
cout << "Enter the coordinates of the square (row, column): ";
cin >> x >> y;
if (x < 0 || x >= board.size() || y < 0 || y >= board[x].size()) {
cout << "Invalid coordinates. Please try again." << endl;
continue;
}
switch(action){

case(1): {
if (revealSquares(board, x, y)) {
gameOver = true;


cout << "YOU LOST THE GAME!" << endl;
} else if (checkWin(board, numBombs)) {
gameOver = true;


cout << "YOU WIN THE GAME!" << endl;
}
break;
}
 case(2):{
	 {
insertFlag(board, x, y);
}  
break;
}
default:
{
cout << "Invalid action. Please try again." << endl;
} 
}

}
revealAll(board);
	

			}
	
	
	




int main(){
	srand(time(0));
ofstream records("records.txt",ios_base::app);
string name;
cout << "enter your name: ";
cin >> name;
system("cls");
	cout << "1.play game"<< endl << "2.exit"<< endl<< "3.records"<<endl;
	int a,b;
	string output;
	cin >> a;
	system("cls");
	switch(a){
		case (1):{
		
			cout << "1.easy"<<endl<<"2.hard"<<endl<<"3.very hard"<<endl;
			cin>>b;
	
			switch(b){
				case (1):{
				game(EASY_ROWS, EASY_COLS,EASY_BOMBS);
				
				records<<name<<" "<<bombsRemaining<<"/"<<10<<endl;
				records.close();
				break;
				case (2):{
					bombsRemaining += 30;
				game(HARD_ROWS, HARD_COLS,HARD_BOMBS);
				records<<name<<" "<<bombsRemaining<<"/"<<40<<endl;
				records.close();
				break;
				}
				case (3):{
					bombsRemaining += 89;
				game(VERY_HARD_ROWS, VERY_HARD_COLS,VERY_HARD_BOMBS);
				records<<name<<" "<<bombsRemaining<<"/"<<99<<endl;
				records.close();
				break;
				}
				
				
			}
		
		}
		
			
		case(2):{
			return 0;
			break;
		}
		case(3):{
			system("cls");
			ifstream records("records.txt");
			while(getline(records,output)){
				cout <<output<<endl;
			}
			break;
		}
	}
}
}

			
			