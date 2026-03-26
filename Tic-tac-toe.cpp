#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

auto win = [](const vector<string>& b, char ch){
    return ranges::any_of(views::iota(0,3), [&](int i){
        return (b[i][0]==ch && b[i][1]==ch && b[i][2]==ch) ||
               (b[0][i]==ch && b[1][i]==ch && b[2][i]==ch);
    }) || (b[0][0]==ch && b[1][1]==ch && b[2][2]==ch) ||
         (b[0][2]==ch && b[1][1]==ch && b[2][0]==ch);
};

int main(){
    vector<string> board(3);
    ranges::for_each(board, [](string& row){ cin >> row; });

    int countX=0, count0=0;
    #pragma omp parallel for reduction(+:countX,count0)
    for(int i=0;i<3;i++)
        for(char c:board[i])
            if(c=='X') countX++;
            else if(c=='0') count0++;

    bool xWins=win(board,'X'), oWins=win(board,'0');

    if(count0>countX || countX>count0+1) { cout<<"illegal"; return 0; }
    if(xWins && oWins) { cout<<"illegal"; return 0; }
    if(xWins){ if(countX!=count0+1){ cout<<"illegal"; return 0; } cout<<"the first player won"; return 0; }
    if(oWins){ if(countX!=count0){ cout<<"illegal"; return 0; } cout<<"the second player won"; return 0; }
    if(countX+count0==9){ cout<<"draw"; return 0; }
    cout<<(countX==count0?"first":"second");
}
