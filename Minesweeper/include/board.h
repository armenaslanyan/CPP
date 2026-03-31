#ifndef BOARD_H
#define BOARD_H
#include <random>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <ncurses/ncurses.h>
#include "cell.h"

class Board {
private:
    const std::vector<std::vector<int>> dirs { {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1} };
    int m_{}, n_{};
    int mines_;
    std::vector<std::vector<Cell>> board_;
    std::vector<std::unordered_set<int>> mines_poses_;
    int opened_cells{};

    int randomizer(int n) const;
public:
    Board(int m, int n, int mines);

    void display() const;
    void bound_checking(int i, int j) const;
    void clear() const;

    void activate_cell(int i, int j);
    void set_cell_flag(int i, int j);
    void deactivate_cell(int i, int j);
    void open_unmined_cells(int i, int j);
    void open_cell(int i, int j);
    int opened_count() const;
    int mines_count() const;
    bool flagged_cell(int i, int j) const;

    bool mined(int i, int j) const;
};

#endif