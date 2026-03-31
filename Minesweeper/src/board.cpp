#include "../include/board.h"

Board::Board(int m, int n, int mines) : m_{m}, n_{n}, mines_{mines} {
    board_.assign(m_, std::vector<Cell>{});
    mines_poses_.resize(m_);

    for (int i{}; i < m_; ++i) {
        board_[i].assign(n_, Cell{});
    }

    while (mines > 0) {
        int i{randomizer(m_ - 1)};
        int j{randomizer(n_ - 1)};
    
        if (mines_poses_[i].find(j) == mines_poses_[i].end()) {
            mines_poses_[i].insert(j);
            board_[i][j].set_mine();
            --mines;
        }
    }

    for (int i{}; i < m_; ++i) {
        for (int j{}; j < n_; ++j) {
            int mc{};

            for (const auto &dir : dirs) {
                int ni{dir[0] + i}, nj{dir[1] + j};

                if (ni >= 0 && ni < m_ && nj >= 0 && nj < n_ && mines_poses_[ni].find(nj) != mines_poses_[ni].end()) {
                    ++mc;
                }
            }

            if (mc > 0) { board_[i][j].set_neighbor_mines(mc); }
        }
    }

    board_[(m_ - 1) / 2][(n_ - 1) / 2].set_active();
}

int Board::randomizer(int n) const {
    static std::random_device rd; \
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dist(0, n); 
    return dist(gen);
}

void Board::display() const {
    for (int i{}; i < m_; ++i) {
        for (int j{}; j < n_; ++j) {
            board_[i][j].draw();
        }
        std::cout << std::endl;
    }  
}

void Board::bound_checking(int i, int j) const {
    if (i >= m_ || j >= n_) {
        throw std::out_of_range("error: invalid coordinates");
    }
}

void Board::clear() const {
    std::system("cls");
}

void Board::activate_cell(int i, int j) {
    bound_checking(i, j);
    board_[i][j].set_active();
}

void Board::set_cell_flag(int i, int j) {
    bound_checking(i, j);
    board_[i][j].set_flag();
}

void Board::deactivate_cell(int i, int j) {
    bound_checking(i, j);
    board_[i][j].set_unactive();
}

void Board::open_unmined_cells(int i, int j) {
    if (board_[i][j].open_state() || board_[i][j].mine()) { return; }
    
    ++opened_cells;
    board_[i][j].set_open();

    if (board_[i][j].neighbors() > 0) { return; }

    for (const auto &dir : dirs) {
        int ni{dir[0] + i}, nj{dir[1] + j};

        if (ni >= 0 && ni < m_ && nj >= 0 && nj < n_ && !board_[i][j].mine()) {
            open_unmined_cells(ni, nj);
        }
    }
}

void Board::open_cell(int i, int j) {
    bound_checking(i, j);

    if (!board_[i][j].open_state() && !board_[i][j].mine()) {
        open_unmined_cells(i, j);
    }
}

int Board::opened_count() const {
    return opened_cells;
}

int Board::mines_count() const {
    return mines_;
}

bool Board::flagged_cell(int i, int j) const {
    return board_[i][j].flagged();
}

bool Board::mined(int i, int j) const {
    return mines_poses_[i].find(j) != mines_poses_[i].end();
}