#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

static string CheckWinner(vector<int>& board, int turn) {
    // check horizontal wins
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == board[i + 1] && board[i + 1] == board[i + 2] && board[i] != 0) {
            if (board[i] == 1) return "X";
            else return "O";
        }
    }
    // check vertical wins
    for (int i = 0; i < 3; i++) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i] != 0) {
            if (board[i] == 1) return "X";
            else return "O";
        }
    }
    // checking diagonals
    if (board[0] == board[4] && board[4] == board[8] && board[0] != 0)
        if (board[0] == 1) return "X";
        else return "O";
    if (board[2] == board[4] && board[4] == board[6] && board[2] != 0) {
        if (board[2] == 1) return "X";
        else return "O";
    }

    if (turn == 9)
        return "Tie";
    else return "Not Finished";
}

struct Ai {
    // Get all the empty spaces on the given board
	vector<int> possible_moves(vector<int>& board) {
		vector<int> possible;
		for (int i = 0; i < board.size(); i++) {
			if (board[i] == 0) possible.push_back(i);
		}return possible;
	}
    // Find the score of the current terminal state
    int score(string& winner) {
        if (winner == "X") return 1;
        else if (winner == "O") return -1;
        else return 0;
    }
    // Use minimax to find the optimal move to make on the current board
    int minimax(vector<int> board, int turn, int player, int depth=0) {

        string winner = CheckWinner(board, turn);
        if (winner != "Not Finished") {
            return score(winner);
        }

        if (player == 1) {
            vector<int> moves = possible_moves(board);
            int highest = INT_MIN, best_move = -1;
            int new_player = -1;
            for (auto move : moves) {
                vector<int> new_board = board;
                new_board[move] = player;
                int move_score = minimax(new_board, turn + 1, new_player, depth + 1);

                // applying alpha-beta pruning.
                if (move_score == 1) {
                    highest = 1;
                    best_move = move;
                    break;
                }
                
                if (move_score > highest) {
                    highest = move_score;
                    best_move = move;
                }
            }
            if (depth == 0) return best_move;
            else return highest;
        }
        else {
            vector<int> moves = possible_moves(board);
            int lowest = INT_MAX, best_move = -1;
            int new_player = 1;
            for (auto move : moves) {
                vector<int> new_board = board;
                new_board[move] = player;
                int move_score = minimax(new_board, turn + 1, new_player, depth + 1);

                // applying alpha-beta pruning.
                if (move_score == -1) {
                    lowest = -1;
                    best_move = move;
                    break;
                }

                if (move_score < lowest) {
                    lowest = move_score;
                    best_move = move;
                }
            }
            if (depth == 0) return best_move;
            else return lowest;
        }
    }
};