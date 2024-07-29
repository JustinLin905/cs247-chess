#include "ChessBoard.h"

#include "SampleBoards.h"

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
        {'-', '-', '-', '-', 'q', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'P', 'P', 'P', 'P', '-', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

    // char defaultBoard[8][8] = {
    //     {'r', 'n', 'b', '-', 'k', 'b', 'n', 'r'},
    //     {'-', '-', 'q', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'R', '-', '-', '-', 'K', 'B', 'N', 'R'}};

    // char defaultBoard[8][8] = {
    //     {'-', 'k', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', 'R', '-'},
    //     {'-', 'K', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'}};

    // char defaultBoard[8][8] = {
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'k', '-', '-', '-', '-', '-', 'K', '-'},
    //     {'-', '-', '-', 'B', '-', '-', '-', '-'},
    //     {'-', '-', '-', 'Q', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'}};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (defaultBoard[i][j] == '-') continue;

            char p = std::toupper(defaultBoard[i][j]);
            bool isWhite = p == defaultBoard[i][j];
            Color col = isWhite ? Color::WHITE : Color::BLACK;
            Player *player = isWhite ? whitePlayer.get() : blackPlayer.get();

            std::shared_ptr<Piece> piece;

            switch (p) {
                case 'R':
                    piece = std::make_shared<Rook>(col, player, chessBoard, std::weak_ptr<Square>(_board.at(i).at(j)));
                    break;
                case 'N':
                    piece = std::make_shared<Knight>(col, player, chessBoard, std::weak_ptr<Square>(_board.at(i).at(j)));
                    break;
                case 'B':
                    piece = std::make_shared<Bishop>(col, player, chessBoard, std::weak_ptr<Square>(_board.at(i).at(j)));
                    break;
                case 'Q':
                    piece = std::make_shared<Queen>(col, player, chessBoard, std::weak_ptr<Square>(_board.at(i).at(j)));
                    break;
                case 'K':
                    piece = std::make_shared<King>(col, player, chessBoard, std::weak_ptr<Square>(_board.at(i).at(j)));
                    player->setKing(std::dynamic_pointer_cast<King>(piece));
                    break;
                case 'P':
                    piece = std::make_shared<Pawn>(col, player, chessBoard, std::weak_ptr<Square>(_board.at(i).at(j)));
                    break;
            }

            _board.at(i).at(j)->setPiece(piece);
            if (isWhite)
                _white_alive_pieces.emplace_back(piece);
            else
                _black_alive_pieces.emplace_back(piece);
        }
    }

    updateAttackMap();
}

char ChessBoard::getState(int row, int col) const {
    return _board.at(row).at(col)->getState();
}

Square &ChessBoard::getSquare(Position position) {
    return *getSquarePtr(position);
}

// Currently used to swap the weak_ptr that pieces have to their new square, after moving
std::shared_ptr<Square> ChessBoard::getSquarePtr(Position position) {
    return _board.at(position.r).at(position.c);
}

void ChessBoard::render() { notifyObservers(); }

/*
This method is to check whether or not a player has any more available moves to make.
This is used to check for checks and stalemates
*/
bool ChessBoard::hasValidMove(Color color) const {
    for (auto piece : (color == Color::WHITE ? _white_alive_pieces : _black_alive_pieces)) {
        if (piece->getValidMoves().size() > 0) return true;
    }
    return false;
}

void ChessBoard::updateAttackMap() {
    attack_map.clear();

    // Update attacked squares
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto piece = getSquarePtr(Position{i, j})->getPiece();
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

void ChessBoard::removeDeadPiece(std::shared_ptr<Piece> piece) {
    _white_alive_pieces.erase(std::remove(_white_alive_pieces.begin(), _white_alive_pieces.end(), piece), _white_alive_pieces.end());
    _black_alive_pieces.erase(std::remove(_black_alive_pieces.begin(), _black_alive_pieces.end(), piece), _black_alive_pieces.end());
}

// Used to restore alive pieces to an old state
void ChessBoard::setAlivePieces(std::vector<std::shared_ptr<Piece>> pieces, Color color) {
    (color == Color::WHITE ? _white_alive_pieces : _black_alive_pieces) = pieces;
}

std::vector<std::shared_ptr<Piece>> ChessBoard::getAlivePieces(Color color) const {
    return color == Color::WHITE ? _white_alive_pieces : _black_alive_pieces;
}
