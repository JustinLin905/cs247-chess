#include "ChessBoard.h"

ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            _board[i][j] = std::make_shared<Square>();
            _board[i][j]->setPosition(Position{i, j});
        }
    }

    observers = std::vector<Observer *>();
}

void ChessBoard::reset() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // needs implementation to move pieces to their initial positions
        }
    }
}

void ChessBoard::defaultSetup(std::unique_ptr<Player> &whitePlayer, std::unique_ptr<Player> &blackPlayer, std::shared_ptr<ChessBoard> chessBoard) {
    // Thought: we will need to be able to reverse this based on the current
    // player's color
    reset();

    char defaultBoard[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', '-', 'K', '-', 'K', '-', '-', 'R'}};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (defaultBoard[i][j] == '-') continue;

            char p = std::toupper(defaultBoard[i][j]);
            bool isWhite = p == defaultBoard[i][j];
            Color col = isWhite ? Color::WHITE : Color::BLACK;
            Player *player = isWhite ? whitePlayer.get() : blackPlayer.get();

            switch (p) {
                case 'R':
                    _board[i][j]->setPiece(std::make_unique<Rook>(
                        col, player, chessBoard, std::weak_ptr<Square>(_board[i][j])));
                    break;
                case 'N':
                    _board[i][j]->setPiece(std::make_unique<Knight>(
                        col, player, chessBoard, std::weak_ptr<Square>(_board[i][j])));
                    break;
                case 'B':
                    _board[i][j]->setPiece(std::make_unique<Bishop>(
                        col, player, chessBoard, std::weak_ptr<Square>(_board[i][j])));
                    break;
                case 'Q':
                    _board[i][j]->setPiece(std::make_unique<Queen>(
                        col, player, chessBoard, std::weak_ptr<Square>(_board[i][j])));
                    break;
                case 'K':
                    _board[i][j]->setPiece(std::make_unique<King>(
                        col, player, chessBoard, std::weak_ptr<Square>(_board[i][j])));
                    break;
                case 'P':
                    _board[i][j]->setPiece(std::make_unique<Pawn>(
                        col, player, chessBoard, std::weak_ptr<Square>(_board[i][j])));
                    break;
            }
        }
    }

    updateAttackMap();
}

char ChessBoard::getState(int row, int col) const {
    return _board[row][col]->getState();
}

Square &ChessBoard::getSquare(Position position) {
    return *_board[position.r][position.c];
}

// Currently used to swap the weak_ptr that pieces have to their new square, after moving
std::shared_ptr<Square> ChessBoard::getSquarePtr(Position position) {
    return _board[position.r][position.c];
}

void ChessBoard::render() { notifyObservers(); }

void ChessBoard::updateAttackMap() {
    attack_map.clear();

    // Update attacked squares
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto piece = _board[i][j]->getPiece();
            if (piece) {
                auto attacked_squares = piece->getAttackedSquares();
                for (auto &pos : attacked_squares) {
                    attack_map[pos].push_back(piece);
                }
            }
        }
    }

    // print the attack map (debugging)
    // for (auto &pair : attack_map) {
    //     std::cout << "Position: " << pair.first.r << ", " << pair.first.c
    //               << std::endl;
    //     std::cout << "Attacking Pieces: ";
    //     for (auto &piece : pair.second) {
    //         if (piece.lock()) std::cout << piece.lock()->getPieceChar();
    //     }
    //     std::cout << std::endl;

    //     std::cout << "----------------" << std::endl;
    // }
}

/*
Returns true if a position on the Chessboard is under attack by a piece of the specified color.

For example, if we pass in Color::WHITE, this function will return true if a white piece is attacking that position
*/
bool ChessBoard::isPositionUnderAttack(Position position, Color color) const {
    if (attack_map.find(position) == attack_map.end()) {
        return false;
    }

    for (auto &piece : attack_map.at(position)) {
        if (piece.lock() && piece.lock()->getColor() == color) {
            return true;
        }
    }

    return false;
}
