#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estructura para representar una pieza de tubería
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
    
    // Inicializar las piezas dobles según las especificaciones
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
    
    // Avanzar a la siguiente posición secuencial
    void advancePosition() {
        currentCol++;
        if (currentCol >= boardSize) {
            currentCol = 0;
            currentRow++;
        }
    }
    
    // Verificar si el tablero está lleno
    bool isBoardFull() {
        return currentRow >= boardSize;
    }
    
    // Verificar si una posición es válida
    bool isValidPosition(int row, int col) {
        return row >= 0 && row < boardSize && col >= 0 && col < boardSize;
    }
    
    // Colocar una pieza en la posición actual
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
    
    // Calcular puntuación basada en conexiones
    int calculateScore() {
        int totalScore = 0;
        vector<vector<bool>> visited(boardSize, vector<bool>(boardSize, false));
        
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] != '.' && !visited[i][j]) {
                    int fragmentLength = 0;
                    int connections = 0;
                    
                    // BFS para encontrar el fragmento conectado
                    vector<pair<int, int>> queue = {{i, j}};
                    visited[i][j] = true;
                    
                    while (!queue.empty()) {
                        auto current = queue.front();
                        queue.erase(queue.begin());
                        fragmentLength++;
                        
                        // Buscar la pieza actual
                        PipePiece currentPiece = availablePieces[0];
                        for (auto& piece : availablePieces) {
                            if (piece.symbol == board[current.first][current.second]) {
                                currentPiece = piece;
                                break;
                            }
                        }
                        
                        // Contar conexiones y explorar vecinos
                        for (auto& conn : currentPiece.connections) {
                            int newRow = current.first + conn.first;
                            int newCol = current.second + conn.second;
                            
                            if (isValidPosition(newRow, newCol) && board[newRow][newCol] != '.') {
                                connections++;
                                
                                if (!visited[newRow][newCol]) {
                                    visited[newRow][newCol] = true;
                                    queue.push_back({newRow, newCol});
                                }
                            }
                        }
                    }
                    
                    totalScore += connections * fragmentLength;
                }
            }
        }
        
        return totalScore;
    }
    
public:
    int numPieces;

    PipeGame(int size) : boardSize(size), currentRow(0), currentCol(0), score(0), isPlayerTurn(true) {
        srand(time(NULL));
        board.resize(boardSize, vector<char>(boardSize, '.'));
        initializePieces();
    }
    
    // Mostrar el tablero
    void displayBoard() {
        cout << "\nTablero actual:\n";
        cout << "  ";
        for (int j = 0; j < boardSize; j++) {
            cout << " " << j << " ";
        }
        cout << "\n";
        
        for (int i = 0; i < boardSize; i++) {
            cout << i << " ";
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == '.') {
                    cout << " . ";
                } else {
                    // Buscar la descripción del símbolo
                    string description = "?";
                    for (auto& piece : gamePieces) {
                        if (piece.symbol == board[i][j]) {
                            description = piece.description;
                            break;
                        }
                    }
                    cout << " " << description << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    
    // Mostrar todas las piezas disponibles
    void displayAvailablePieces() {
        cout << "\nPiezas disponibles:\n";
        for (int i = 0; i < availablePieces.size(); i++) {
            cout << i + 1 << ". " << availablePieces[i].description << " ";
        }
        cout << "\n";
    }
    
    // Colocar una pieza del jugador
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
    
    // Turno de la computadora
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
    
    // Verificar si el juego ha terminado
    bool isGameOver() {
        return isBoardFull();
    }
    
    // Obtener puntuación actual
    int getScore() {
        score = calculateScore();
        return score;
    }
    
    // Obtener turno actual
    bool getIsPlayerTurn() {
        return isPlayerTurn;
    }
    
    // Obtener posición actual
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
    
    cout << "\nReglas del juego:\n";
    cout << "- Turnos alternados: Jugador coloca una pieza, luego la computadora\n";
    cout << "- Posicionamiento secuencial: Empezando en (0,0) y avanzando por filas\n";
    cout << "- Cada conexión vale 1 punto, multiplicado por la longitud del fragmento\n";
    cout << "- El juego termina cuando el tablero está lleno\n\n";
       
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
