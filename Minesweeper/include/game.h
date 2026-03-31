#ifndef GAME_H
#define GAME_H
#include <conio.h>
#include <tuple>
#include "cell.h"
#include "board.h"
#include <ncurses/ncurses.h>

class Minesweeper {
private:
    mutable int m{}, n{};
    mutable int mines{};

    void control_help() const {
        std::cout << "Control" << std::endl;
        std::cout << "\tW (UP)" << std::endl;
        std::cout << "\tA (LEFT)" << std::endl;
        std::cout << "\tS (DOWN)" << std::endl;
        std::cout << "\tD (RIGHT)" << std::endl;
        // std::cout << std::endl;
    }

    struct Difficulty {
        std::tuple<int, int, int> diff;

        Difficulty(int choice) {
            if (choice == 1) {
                diff = std::make_tuple(9, 9, 10);
            } else if (choice == 2) {
                diff = std::make_tuple(16, 16, 40);
            } else if (choice == 3) {
                diff = std::make_tuple(30, 16, 99);
            }
        }
    };
public:
    Minesweeper() = default;

    void run() const {
        control_help();

        std::cout << std::endl << "Choose Difficulty: " << std::endl;
        std::cout << "1. " << GREEN << "Easy " << RESET << "(9x9, 10 mines)" << std::endl;
        std::cout << "2. " << YELLOW << "Medium " << RESET << "(16x16, 40 mines)" << std::endl;
        std::cout << "3. " << RED << "Hard " << RESET << "(30x16, 99 mines)" << std::endl;

        int choice{};
        while (!(choice >= 1 && choice <= 3)) {
            std::cin >> choice;
        }

        auto [in_m, in_n, in_mines] = Difficulty(choice).diff;
        m = in_m; 
        n = in_n;
        mines = in_mines;

        Board board(in_m, in_n, mines);
        board.clear();
        board.display();
        int i{(m - 1) / 2}, j{(n - 1) / 2};

        while (true) {
            char dir = _getch();
            
            if (dir == 'f') {
                board.set_cell_flag(i, j);
                board.clear();
                board.display();
            } else {
                board.deactivate_cell(i, j);
                
                if (dir == 'w') {
                    if (i > 0) {
                        --i;
                    }
                    board.activate_cell(i, j);
                } else if (dir == 'a') {
                    if (j > 0) {
                        --j;
                    }
                    board.activate_cell(i, j);
                } else if (dir == 's') {
                    if (i < m - 1) {
                        ++i;
                    }
                    board.activate_cell(i, j);
                } else if (dir == 'd') {
                    if (j < n - 1) {
                        ++j;
                    } 
                    board.activate_cell(i, j);
                } else if (dir == '\r' && !board.flagged_cell(i, j)) {
                    if (board.mined(i, j)) {
                        board.clear();
                        board.display();
                        std::cout << "Game Over \n";
                        break;
                    }
                    
                    board.open_cell(i, j);
                    board.clear();
                    board.display();
                    board.activate_cell(i, j);
                } else if (dir == 'q') {
                    break;
                } else {
                    board.activate_cell(i, j);
                }
                
                if ((m * n) - board.opened_count() == board.mines_count()) {
                    std::cout << GREEN << "You Win !" << RESET << std::endl;
                    break;
                }

                board.clear();
                // control_help();
                board.display();
                board.activate_cell(i, j);
            }
        }
    }
};

#endif