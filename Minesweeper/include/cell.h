#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <string>
#include <ncurses/ncurses.h>
#include "color.h"

class Cell {
private:
    bool is_active{};
    bool is_mine{};
    bool is_open{};
    bool is_flagged{};
    int neighbor_mines{};

public:
    Cell() = default;

    // ----- setters -----
    void set_mine();
    void set_neighbor_mines(int n);
    void set_active();
    void set_unactive();
    void set_flag();
    void set_open();

    // ----- getters -----
    bool mine() const;
    bool open_state() const;
    int neighbors() const;
    bool flagged() const;

    // ----- drawing -----
    void draw() const;
};

#endif