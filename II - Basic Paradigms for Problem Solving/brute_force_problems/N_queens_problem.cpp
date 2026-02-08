#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;
using namespace std::chrono;

bool can_place_queen(vector<int> &board) {
    for (int i=0; i<board.size(); i++)
        for (int j = i+1; j<board.size(); j++)
            //proveruva dali se vo ista kolona ili dijagonala
            if (board[i]==board[j] || abs(board[i]-board[j])==abs(i-j)) return false;

    return true;
}

void generate_solutions(vector<int> &board, int row, int &sols) {
    if (row==board.size()) {
        if (can_place_queen(board)) sols++;
        return;
    }

    for (int c=0; c<board.size(); c++) {
        board[row]=c;
        generate_solutions(board, row+1, sols);
    }
}

void input(int N) {
    int  num_of_solutions=0;
    vector<int> queens_board_pos(N); //i e redot, a board[i] e kolonata vo koja se naoga kralica, se chuvaat samo poz. na kralicite

    auto s=high_resolution_clock::now();
    generate_solutions(queens_board_pos, 0, num_of_solutions);
    auto f=high_resolution_clock::now();

    duration<double> elapsed=f-s;

    cout << fixed << setprecision(5) << "solutions count: " << num_of_solutions << " | time: " << elapsed << '\n';
}

int main() {
    //problem: imame N kralici, treba da gi stavime na shahovska tabla tkd niedna ne napaga niedna druga
    //napadite se po redici, koloni i dijagonali
    //se bara da se izbrojat site mozni reshenija, t.e. konfiguracii shto go reshavaat problemot

    cout << "for 8 queens: " <<'\n';
    input(8);
    cout << "for 12 queens: " << '\n';
    input(12);

    return 0;
}