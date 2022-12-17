#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

const char human = 'O';
const char ai = 'X';


enum Player { HUMAN, AI };



struct Move {
	int x;
	int y;
};


void initializeBoard(char board[3][3]){
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			board[i][j] = '-';
		}
	}
}

void printBoard(char board[3][3]) {
	cout << "-------------------";
	for(int i = 0; i < 3; i++) {
		cout << '\n' << "|";
		for(int j = 0; j < 3; j++) {
			cout << "  " << board[i][j] << " " << " |";
		}
	}
	cout << '\n' << "-------------------" << '\n';
}

bool checkWin(Player player,char board[3][3]) {
	char playerChar;
	if(player == HUMAN) playerChar = human;
	else playerChar = ai;

	for(int i = 0; i < 3; i++) {
		// Check horizontals
		if(board[i][0] == playerChar && board[i][1] == playerChar
			&& board[i][2] == playerChar)
			return true;

		// Check verticals
		if(board[0][i] == playerChar && board[1][i] == playerChar
			&& board[2][i] == playerChar)
			return true;
	}

	// Check diagonals
	if (board[0][0] == playerChar && board[1][1] == playerChar 
		&& board[2][2] == playerChar) {
		return true;
	} else if (board[0][2] == playerChar && board[1][1] == playerChar 
		&& board[2][0] == playerChar) {
		return true;
	}

	return false;
}


bool gameOver(char board[3][3]) {
	if(checkWin(HUMAN,board)) return true;
	else if(checkWin(AI,board)) return true;

	bool emptySpace = false;
	for(int i = 0; i < 3; i++) {
		if(board[i][0] == '-' || board[i][1] == '-' || board[i][2] == '-')
			emptySpace = true;
	}
	return !emptySpace;
}


int score(char board[3][3]) {
	if(checkWin(HUMAN,board)) { return -10; }
	else if(checkWin(AI,board)) { return 10; }
	return 0; 
}

void getHumanMove(char board[3][3]) {
	int x, y = -1; 
	while(x < 0 || x > 2 || y < 0 || y > 2) {
		cout << "Enter your move in coordinate form, ex: (2,2)" << endl;
		cout << "Your Move: ";
		char c;
		string restofline;
		cin >> c >> c;
		x = c - '0' - 1;
		cin >> c >> c;
		y = c - '0' - 1;
		getline(cin, restofline); 
	}
	board[x][y] = human;
}

int minimax(char board[3][3], int depth, bool isAI){
	int tscore = 0;
	int bestScore = 0;
	if(gameOver(board)){
		return score(board);
	}else{
		if(isAI==true){
			bestScore = -1000;
			for(int i = 0;i<3;i++){
				for(int j= 0;j<3;j++){
					if(board[i][j] == '-'){
						board[i][j] = ai;
						tscore = minimax(board,depth+1,false);
						board[i][j] = '-';

						bestScore = max(tscore,bestScore);
					}
				}
			}
			return bestScore;
		}
		else{
			bestScore = 1000;
			for(int i = 0;i<3;i++){
				for(int j= 0;j<3;j++){
					if(board[i][j] == '-'){
						board[i][j] = human;
						tscore = minimax(board,depth+1,true);
						board[i][j] = '-';

						bestScore = min(tscore,bestScore);
					}
				}
			}
			return bestScore;
		}
	}
}

Move getBestMove(char board[3][3]){
	int tscore =0,bestScore =-1000;
	Move bestMove;
	for(int i = 0;i<3;i++){
		for(int j= 0;j<3;j++){
			if(board[i][j] == '-'){
				board[i][j] = ai;
				tscore = minimax(board,0,false);
				board[i][j] = '-';
				if(tscore>bestScore){
					bestScore = tscore;
					bestMove.x = i;
					bestMove.y = j;
				}
			}
		}
	}
	return bestMove;
}

void play(char board[3][3]) {
	int turn = 0;
	printBoard(board);
	while(!checkWin(HUMAN,board) && !checkWin(AI,board) && !gameOver(board)) {
		
		if(turn % 2 == 0) {
			getHumanMove(board);
			if(checkWin(HUMAN,board)) cout << "Human Player Wins" << endl;
			turn++;
			printBoard(board);
		} else {
			cout << endl << "Computer Player Move:" << endl;
			Move AImove = getBestMove(board);
			board[AImove.x][AImove.y] = ai;
			if(checkWin(AI,board)) cout << "Computer Player Wins" << endl;
			turn++;
			printBoard(board);
		}
	}
}


int main(){
	char board[3][3];
	initializeBoard(board);
	play(board);

	return 0;
}



