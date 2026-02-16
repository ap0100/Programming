#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int count_possible_onward_moves(vector<vector<int>> &board, int x_moves[], int y_moves[], int x, int y) {
    int count=0;

    for (int i=0; i<8; i++) {
        int next_x=x+x_moves[i];
        int next_y=y+y_moves[i];
        if (next_x>=0 && next_x<8 && next_y>=0 && next_y<8 && board[next_x][next_y]==0) count++;
    }

    return count;
}

vector<tuple<int,int,int>> get_best_moves(vector<vector<int>> &board, int x_moves[], int y_moves[], int x, int y) {
    vector<tuple<int,int,int>> best_moves;

    for (int i=0; i<8; i++) {
        int next_x=x+x_moves[i];
        int next_y=y+y_moves[i];
        if (next_x>=0 && next_x<8 && next_y>=0 && next_y<8 && board[next_x][next_y]==0)
            best_moves.push_back(tuple<int,int,int>(next_x, next_y, count_possible_onward_moves(board, x_moves, y_moves, next_x, next_y)));
    }

    sort(best_moves.begin(), best_moves.end(), [](const tuple<int,int,int> &a, const tuple<int,int,int> &b) {
         return get<2>(a) < get<2>(b); //sorts in descending order
    });

    return best_moves;
}

bool warnsdorff_track_moves(vector<vector<int>> &board, int x, int y, int move_count) {
    if (move_count>64) return true; //znachi deka se pominati site polinja na tablata i turata e zavrshena

    int x_moves[8]={2,1,-2,-1,2,1,-2,-1},
        y_moves[8]={1,2,1,2,-1,-2,-1,-2};
    vector<tuple<int,int,int>> moves=get_best_moves(board, x_moves, y_moves, x, y);

    for (tuple<int,int,int> &move: moves) {
        int next_x=get<0>(moves[i]);
        int next_y=get<1>(moves[i]);
        board[next_x][next_y]=move_count;
        if (warnsdorff_track_moves(board,next_x,next_y,move_count+1)) return true; //turata uspeshno e zavrshena so vakviot (next_x, next_y) poteg
        board[next_x][next_y]=0; //backtrack, potegot nosi do return false od funkcijata, znachi nosi do dead end i ne treba da se napravi
    }

    return false; //turata ne e gotova, potegot shto bil napraven nosi do dead end
}

int main() {
    //Knight's Tour - konjot treba da go poseti sekoe pole na shahovska tabla tochno ednash
    //potezi: x+1->y-2; y+2->x-1; y-1->x-2; x+2->y+1; y-1->x+2; x-2->y+1; y-2->x+1; x-1->y+2; y-2->x-1; x+1->y+2; y+2->x+1; x-1->y-2; y+1->x+2; x-2->y-1; y+1->x-2; x+2->y-1;
    vector<vector<int>> board(8, vector<int>(8, 0));
    board[0][0]=1;

    warnsdorff_track_moves(board, 0, 0, 2);

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            cout << board[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}
