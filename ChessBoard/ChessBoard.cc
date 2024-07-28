#include "ChessBoard.h"

ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            _board[i][j] = std::make_shared<Square>();
            _board[i][j]->setPosition(Position{i, j});
        }
    }

    observers = std::vector<std::shared_ptr<Observer>>();
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
    for (int i = 0; i < 8; i++) {
        // Need to update to set Player pointers correctly, instead of to nullptr
        // _board[1][i]->setPiece(std::make_unique<Pawn>(
        //     Color::BLACK, blackPlayer.get(), chessBoard,
        //     std::weak_ptr<Square>(_board[1][i])));
        // _board[6][i]->setPiece(std::make_unique<Pawn>(
        //     Color::WHITE, whitePlayer.get(), chessBoard,
        //     std::weak_ptr<Square>(_board[6][i])));
    }
    _board[0][0]->setPiece(std::make_unique<Rook>(
        Color::BLACK, blackPlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[0][0])));
    _board[0][1]->setPiece(std::make_unique<Knight>(
        Color::BLACK, blackPlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[0][1])));
    _board[0][2]->setPiece(std::make_unique<Bishop>(
        Color::BLACK, blackPlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[0][2])));
    _board[0][3]->setPiece(std::make_unique<Queen>(
        Color::BLACK, blackPlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[0][3])));
    _board[0][4]->setPiece(std::make_unique<King>(
        Color::BLACK, blackPlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[0][4])));
    _board[0][5]->setPiece(std::make_unique<Bishop>(
        Color::BLACK, blackPlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[0][5])));
    _board[0][6]->setPiece(std::make_unique<Knight>(
        Color::BLACK, blackPlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[0][6])));
    _board[0][7]->setPiece(std::make_unique<Rook>(
        Color::BLACK, blackPlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[0][7])));

    _board[7][0]->setPiece(std::make_unique<Rook>(
        Color::WHITE, whitePlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[7][0])));
    _board[7][1]->setPiece(std::make_unique<Knight>(
        Color::WHITE, whitePlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[7][1])));
    _board[7][2]->setPiece(std::make_unique<Bishop>(
        Color::WHITE, whitePlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[7][2])));
    _board[7][3]->setPiece(std::make_unique<Queen>(
        Color::WHITE, whitePlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[7][3])));
    _board[7][4]->setPiece(std::make_unique<King>(
        Color::WHITE, whitePlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[7][4])));
    _board[7][5]->setPiece(std::make_unique<Bishop>(
        Color::WHITE, whitePlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[7][5])));
    _board[7][6]->setPiece(std::make_unique<Knight>(
        Color::WHITE, whitePlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[7][6])));
    _board[7][7]->setPiece(std::make_unique<Rook>(
        Color::WHITE, whitePlayer.get(), chessBoard,
        std::weak_ptr<Square>(_board[7][7])));

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
