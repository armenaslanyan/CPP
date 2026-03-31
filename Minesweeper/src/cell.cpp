#include "../include/cell.h"

// ----- setters -----
void Cell::set_mine() { 
    is_mine = true; 
}

void Cell::set_neighbor_mines(int n) {
    neighbor_mines = n;
}

void Cell::set_active() {
    is_active = true;
}

void Cell::set_unactive() {
    is_active = false;
}

void Cell::set_flag() {
    if (!is_open) {
        is_flagged = !is_flagged;
    }
}

void Cell::set_open() {
    if (!is_flagged) {
        is_open = true;
    }
}

// ----- getters -----
bool Cell::open_state() const {
    return is_open;
}

bool Cell::mine() const {
    return is_mine;
}

int Cell::neighbors() const {
    return neighbor_mines;
}

bool Cell::flagged() const {
    return is_flagged;
}

// ----- drawing -----
void Cell::draw() const {
    if (is_active) { std::cout << "["; }

    if (is_flagged) {
        if (is_active) {
            std::cout << RED << "F" << RESET;
        } else {
            std::cout << RED << " F " << RESET;
        }
    } else if (!is_open) {
        if (is_active) {
            std::cout << GRAY << "#" << RESET;
        } else {
            std::cout <<  GRAY << " # " << RESET;
        }
    } else if (is_mine) {
        if (is_active) {
            std::cout << "*";
        } else {
            std::cout << " * ";
        }
    } else if (neighbor_mines == 0) {
        if (is_active) {
            std::cout << GRAY << "." << RESET;
        } else {
            std::cout << GRAY << " . " << RESET;
        }
    } else {
        if (is_active) {
            std::cout << neighbor_mines;
        } else {
            std::cout << " " << neighbor_mines << " ";
        }
    }

    if (is_active) { std::cout << "]"; }
}