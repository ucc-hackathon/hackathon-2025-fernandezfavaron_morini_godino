#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct PipePiece {
    char symbol;
    string description;
    vector<pair<int, int>> connections;
    
    PipePiece(){};
    PipePiece(char sym, string desc, vector<pair<int, int>> conn) 
        : symbol(sym), description(desc), connections(conn) {}
};

class PipeGame {
private:
    int boardSize;
    vector<vector<char>> board;
    vector<PipePiece> availablePieces;
    vector<PipePiece> gamePieces;
    int currentRow, currentCol;
    int score;
    bool isPlayerTurn;
    
    void initializePieces() {
        gamePieces = {
            PipePiece((char)185, "╣", {{-1, 0}, {1, 0}, {0, -1}}),
            PipePiece((char)186, "║", {{-1, 0}, {1, 0}}),
            PipePiece((char)187, "╗", {{-1, 0}, {0, -1}}),
            PipePiece((char)188, "╝", {{1, 0}, {0, -1}}),
            PipePiece((char)200, "╚", {{1, 0}, {0, 1}}),
            PipePiece((char)201, "╔", {{-1, 0}, {0, 1}}),
            PipePiece((char)202, "╩", {{0, -1}, {0, 1}, {1, 0}}),
            PipePiece((char)203, "╦", {{0, -1}, {0, 1}, {-1, 0}}),
            PipePiece((char)204, "╠", {{-1, 0}, {1, 0}, {0, 1}}),
            PipePiece((char)205, "═", {{0, -1}, {0, 1}}),
            PipePiece((char)206, "╬", {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}),
        };

        availablePieces.clear();
        numPieces = (boardSize * boardSize) / 2;
        srand(time(0));
        for (int i = 0; i < numPieces; ++i) {
            int idx = rand() % gamePieces.size();
            availablePieces.push_back(gamePieces[idx]);
        }
    }
    
    void advancePosition() {
        currentCol++;
        if (currentCol >= boardSize) {
            currentCol = 0;
            currentRow++;
        }
    }
    
    bool isBoardFull() {
        return currentRow >= boardSize;
    }
    
    bool isValidPosition(int row, int col) {
        return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
    }
    
    bool placePieceAtCurrentPosition(int pieceIndex) {
        if (pieceIndex < 1 || pieceIndex > availablePieces.size()) {
            return false;
        }
        
        if (isBoardFull()) {
            return false;
        }
        
        PipePiece piece;
        if (isPlayerTurn) {
            piece = availablePieces[pieceIndex - 1];
            availablePieces.erase(availablePieces.begin() + (pieceIndex - 1));
        } else {
            piece = gamePieces[rand() % 11];
        }
        board[currentRow][currentCol] = piece.symbol;
        advancePosition();
        return true;
    }
    
    void placeComputerPiece() {
        if (!isBoardFull()) {
            placePieceAtCurrentPosition(1);
        }
    }
    
    int calculateScore() {
        int totalScore = 0;
        return totalScore;
    }
    
public:
    int numPieces;

    PipeGame(int size) : boardSize(size), currentRow(0), currentCol(0), score(0), isPlayerTurn(true) {
        srand(time(NULL));
        board.resize(boardSize, vector<char>(boardSize, '.'));
        initializePieces();
    }
    
    void displayBoard() {
        cout << "\nTablero actual:\n";
        cout << "  ";
        for (int j = 0; j < boardSize; j++) {
            cout << "|" << j+1;
        }
        cout << "\n";
        
        for (int i = 0; i < boardSize; i++) {
            cout << i+1 << " ";
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == '.') {
                    cout << "| ";
                } else {
                    string description = "?";
                    for (auto& piece : gamePieces) {
                        if (piece.symbol == board[i][j]) {
                            description = piece.description;
                            break;
                        }
                    }
                    cout << "|" << description;
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    void displayAvailablePieces() {
        cout << "\nPiezas disponibles:\n";
        for (int i = 0; i < availablePieces.size(); i++) {
            cout << i + 1 << ". " << availablePieces[i].description << " ";
        }
        cout << "\n";
    }
    
    bool placePlayerPiece(int pieceIndex) {
        if (!isPlayerTurn) {
            cout << "No es tu turno!\n";
            return false;
        }
        
        if (isBoardFull()) {
            cout << "El tablero está lleno!\n";
            return false;
        }
        
        if (placePieceAtCurrentPosition(pieceIndex)) {
            cout << "Pieza colocada en posición (" << currentRow << "," << currentCol << ")\n";
            isPlayerTurn = false;
            return true;
        } else {
            cout << "Pieza inválida!\n";
            return false;
        }
    }
    
    void computerTurn() {
        if (isPlayerTurn) {
            cout << "No es el turno de la computadora!\n";
            return;
        }
        
        if (!isBoardFull()) {
            placeComputerPiece();
            cout << "Computadora colocó pieza en posición (" << currentRow << "," << currentCol << ")\n";
            isPlayerTurn = true;
        }
    }
    
    bool isGameOver() {
        return isBoardFull();
    }
    
    int getScore() {
        score = calculateScore();
        return score;
    }
    
    bool getIsPlayerTurn() {
        return isPlayerTurn;
    }
    
    pair<int, int> getCurrentPosition() {
        return {currentRow, currentCol};
    }
};

int main() {
    cout << "=== JUEGO DE TUBERÍAS ===\n";
    cout << "Conecta las tuberías para obtener la máxima puntuación!\n\n";
    
    int boardSize;
    do {
        cout << "Ingrese valor del tablero (8-20): ";
        cin >> boardSize;
        if (boardSize < 8 || boardSize > 20) {
            cout << "El tamaño debe estar entre 8 y 20!\n";
        }
    } while (boardSize < 8 || boardSize > 20);
    
    PipeGame game(boardSize);
    
    while (!game.isGameOver()) {
        game.displayAvailablePieces();
        game.displayBoard();
        
        auto pos = game.getCurrentPosition();
        cout << "Posición actual: (" << pos.first << "," << pos.second << ")\n";
        cout << "Puntuación actual: " << game.getScore() << "\n\n";
        
        if (game.getIsPlayerTurn()) {
            cout << "=== TU TURNO ===\n";
            int pieceIndex;
            printf("Selecciona una pieza (1-%d): ", game.numPieces);
            cin >> pieceIndex;
            
            if (!game.placePlayerPiece(pieceIndex)) {
                cout << "Intenta de nuevo...\n";
            }
        } else {
            cout << "=== TURNO DE LA COMPUTADORA ===\n";
            game.computerTurn();
        }
        
        cout << "\n" << string(50, '-') << "\n";
    }
    
    cout << "\n=== JUEGO TERMINADO ===\n";
    cout << "Puntuación final: " << game.getScore() << "\n";
    cout << "¡Gracias por jugar!\n";
    
    return 0;
}
