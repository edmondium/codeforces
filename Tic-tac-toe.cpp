#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool win(const vector<string>& board, char ch) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if(board[i][0] == ch && board[i][1] == ch && board[i][2] == ch)
            return true;
        if(board[0][i] == ch && board[1][i] == ch && board[2][i] == ch)
            return true;
    }
    // Check diagonals
    if(board[0][0] == ch && board[1][1] == ch && board[2][2] == ch)
        return true;
    if(board[0][2] == ch && board[1][1] == ch && board[2][0] == ch)
        return true;
    return false;
}

int main(){
    vector<string> board(3);
    for (int i = 0; i < 3; i++){
        cin >> board[i];
    }
    
    int countX = 0, count0 = 0;
    for(const auto &row: board){
        for(char c: row){
            if(c == 'X') countX++;
            else if(c == '0') count0++;
        }
    }
    
    // Check counts for a valid sequence
    if(count0 > countX || countX > count0 + 1) {
        cout << "illegal";
        return 0;
    }
    
    bool xWins = win(board, 'X');
    bool oWins = win(board, '0');
    
    // If both have winning lines, or winning move contradicts counts => illegal.
    if(xWins && oWins) {
        cout << "illegal";
        return 0;
    }
    
    if(xWins){
        // As X goes first, if X has just won then countX should be exactly one more than count0.
        if(countX != count0 + 1) {
            cout << "illegal";
            return 0;
        }
        cout << "the first player won";
        return 0;
    }
    
    if(oWins){
        // If 0 (nought) just won then counts must be equal.
        if(countX != count0) {
            cout << "illegal";
            return 0;
        }
        cout << "the second player won";
        return 0;
    }
    
    // If no win, then check if board is full.
    if(countX + count0 == 9){
        cout << "draw";
        return 0;
    }
    
    // Otherwise, the game is not finished. Determine whose turn is next.
    // If counts are equal, first player's turn, else if there's one more X, then second's turn.
    if(countX == count0)
        cout << "first";
    else if(countX == count0 + 1)
        cout << "second";
    
    return 0;
}
