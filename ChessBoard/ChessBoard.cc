#include "ChessBoard.h"

#include "../CommandInterpreter/CommandInterpreter.h"
#include "../SetupInstruction/SetupInstruction.h"
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

void ChessBoard::addPieceToBoard(char c, Position pos, std::shared_ptr<ChessBoard> chessBoard) {
    char p = std::toupper(c);
    bool isWhite = p == c;
    Color col = isWhite ? Color::WHITE : Color::BLACK;
    std::shared_ptr<Piece> piece;

    switch (p) {
        case 'R':
            piece = std::make_shared<Rook>(col, chessBoard, std::weak_ptr<Square>(_board.at(pos.r).at(pos.c)));
            break;
        case 'N':
            piece = std::make_shared<Knight>(col, chessBoard, std::weak_ptr<Square>(_board.at(pos.r).at(pos.c)));
            break;
        case 'B':
            piece = std::make_shared<Bishop>(col, chessBoard, std::weak_ptr<Square>(_board.at(pos.r).at(pos.c)));
            break;
        case 'Q':
            piece = std::make_shared<Queen>(col, chessBoard, std::weak_ptr<Square>(_board.at(pos.r).at(pos.c)));
            break;
        case 'K':
            piece = std::make_shared<King>(col, chessBoard, std::weak_ptr<Square>(_board.at(pos.r).at(pos.c)));
            (isWhite ? _white_king : _black_king) = std::dynamic_pointer_cast<King>(piece);
            break;
        case 'P':
            piece = std::make_shared<Pawn>(col, chessBoard, std::weak_ptr<Square>(_board.at(pos.r).at(pos.c)));
            break;
    }

    _board.at(pos.r).at(pos.c)->setPiece(piece);
    if (isWhite)
        _white_alive_pieces.emplace_back(piece);
    else
        _black_alive_pieces.emplace_back(piece);
}

void ChessBoard::defaultSetup(std::shared_ptr<ChessBoard> chessBoard) {
    // Thought: we will need to be able to reverse this based on the current
    // player's color
    reset();

    char defaultBoard[8][8] = {
        {'r', '-', 'b', '-', 'k', 'b', 'n', 'r'},
        {'p', 'p', '-', 'p', '-', 'p', 'p', 'p'},
        {'-', '-', 'n', '-', 'p', '-', '-', '-'},
        {'-', '-', 'p', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', 'P', 'P', 'P', 'q'},
        {'-', '-', 'N', '-', '-', '-', '-', '-'},
        {'P', 'P', 'P', 'P', '-', '-', '-', 'P'},
        {'R', '-', 'B', 'Q', 'K', 'B', 'N', 'R'}};

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

    // char defaultBoard[8][8] = {
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', 'k', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', 'Q', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'p', '-', '-', '-', '-', '-', 'K', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'}};

    // char defaultBoard[8][8] = {
    //     {'-', 'K', '-', 'k', '-', '-', '-', '-'},
    //     {'-', 'P', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'r', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', 'R', '-', '-', '-', '-', '-'}};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (defaultBoard[i][j] == '-') continue;
            addPieceToBoard(defaultBoard[i][j], Position{i, j}, chessBoard);
        }
    }

    updateAttackMap();
}

void ChessBoard::customSetup(std::shared_ptr<ChessBoard> chessBoard) {
    render();

    while (true) {
        SetupInstruction instr = CommandInterpreter::processSetupInput();

        switch (instr.cmd) {
            case SetupCmds::CMD_ADD_PIECE: {
                // if we're adding a piece to a square that already has a piece, delete the old one
                std::shared_ptr<Piece> oldPiece = _board[instr.pos.r][instr.pos.c]->getPiece();
                if (oldPiece != nullptr) removeDeadPiece(oldPiece);

                // add new piece
                addPieceToBoard(instr.piece, instr.pos, chessBoard);

                render();
                break;
            }
            case SetupCmds::CMD_REMOVE_PIECE: {
                {
                    // remove piece if a piece exists on specified square
                    std::shared_ptr<Piece> oldPiece = _board[instr.pos.r][instr.pos.c]->getPiece();
                    if (oldPiece != nullptr) removeDeadPiece(oldPiece);
                }

                // render board after oldPiece goes out of scope and the Piece is destructed
                render();
                break;
            }
            case SetupCmds::CMD_SET_TURN:
                Manager::setTurn(instr.color);
                break;
            case SetupCmds::CMD_SETUP_DONE: {
                // check number of kings
                int whiteKingCount = std::count_if(_white_alive_pieces.begin(), _white_alive_pieces.end(),
                                                   [](const std::shared_ptr<Piece> &piece) {
                                                       return std::dynamic_pointer_cast<King>(piece) != nullptr;
                                                   });
                int blackKingCount = std::count_if(_black_alive_pieces.begin(), _black_alive_pieces.end(),
                                                   [](const std::shared_ptr<Piece> &piece) {
                                                       return std::dynamic_pointer_cast<King>(piece) != nullptr;
                                                   });

                if (whiteKingCount != 1 || blackKingCount != 1) {
                    std::cout << "CANNOT EXIT SETUP MODE: Number of Kings on the board is not valid" << std::endl;
                    break;
                }

                // check if kings are in check
                updateAttackMap();
                if (_white_king->inCheck() || _black_king->inCheck()) {
                    std::cout << "CANNOT EXIT SETUP MODE: King cannot be in check" << std::endl;
                    break;
                }

                // check that there are no pawns in the first or last row
                bool invalidPawnPos = false;
                for (int i = 0; i < 8; i++) {
                    if ((_board.at(0).at(i)->getPiece() && std::toupper(_board.at(0).at(i)->getPiece()->getPieceChar()) == 'P') ||
                        (_board.at(7).at(i)->getPiece() && std::toupper(_board.at(7).at(i)->getPiece()->getPieceChar()) == 'P')) {
                        std::cout << "CANNOT EXIT SETUP MODE: Pawn cannot be on first or last row of the board" << std::endl;
                        invalidPawnPos = true;
                        break;
                    }
                }
                if (invalidPawnPos) break;

                std::cout << "Exited Setup Mode" << std::endl;
                return;
                break;
            }
            case SetupCmds::CMD_UNKNOWN:
                std::cerr << "Unknown Setup Instruction" << std::endl;
                break;
        }
    }
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
    // if the removed piece is a King, also remove the king ptr to it in ChessBoard
    if (std::toupper(piece->getPieceChar()) == 'K') {
        if (piece->getColor() == Color::WHITE)
            _white_king = nullptr;
        else
            _black_king = nullptr;
    }

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

std::shared_ptr<King> ChessBoard::getKing(Color color) const {
    return (color == Color::WHITE ? _white_king : _black_king);
}

void ChessBoard::addToAlivePieces(std::shared_ptr<Piece> piece, Color color) {
    (color == Color::WHITE ? _white_alive_pieces : _black_alive_pieces).emplace_back(piece);
}
