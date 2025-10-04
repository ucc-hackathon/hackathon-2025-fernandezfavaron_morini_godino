# Juego de Tuberías (Pipe Game)

Un juego en C++ donde los jugadores conectan tuberías para obtener la máxima puntuación posible.

## Características

- **Tablero dinámico**: Tamaños de 8x8 a 20x20
- **11 tipos de piezas dobles**: Diferentes tuberías con códigos ASCII específicos
- **Turnos alternados**: Jugador coloca una pieza, luego la computadora
- **Posicionamiento secuencial**: Empezando en (0,0) y avanzando por filas
- **Sistema de puntuación**: Basado en conexiones y longitud de fragmentos

## Reglas del Juego

1. **Objetivo**: Conectar el máximo número de tuberías posible
2. **Turnos**: Alternados entre jugador y computadora
3. **Posicionamiento**: Secuencial empezando en (0,0), avanzando por filas
4. **Puntuación**: Cada conexión vale 1 punto, multiplicado por la longitud del fragmento
5. **Fórmula**: `Puntos = Σ(conexiones × longitud del fragmento)`
6. **Fin del juego**: Cuando el tablero está completamente lleno

## Tipos de Piezas (11 tipos dobles)

| # | Símbolo | Descripción |
|---|---------|-------------|
| 1 | ╣ | T vertical derecho |
| 2 | ║ | Línea vertical doble |
| 3 | ╗ | Esquina superior derecha |
| 4 | ╝ | Esquina inferior derecha |
| 5 | ╚ | Esquina inferior izquierda |
| 6 | ╔ | Esquina superior izquierda |
| 7 | ╩ | T horizontal inferior |
| 8 | ╦ | T horizontal superior |
| 9 | ╠ | T vertical izquierdo |
| 10 | ═ | Línea horizontal doble |
| 11 | ╬ | Cruce doble |

## Compilación y Ejecución

### Usando Makefile (recomendado)
```bash
make          # Compilar
make run      # Compilar y ejecutar
make clean    # Limpiar archivos compilados
```

### Compilación manual
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o pipe_game pipe_game.cpp
./pipe_game
```

## Cómo Jugar

1. Ejecuta el programa
2. Selecciona el tamaño del tablero (8-20)
3. El juego muestra las 11 piezas dobles disponibles
4. **Turnos alternados**:
   - **Tu turno**: Selecciona una pieza (1-11) para colocar en la posición actual
   - **Turno de la computadora**: Coloca una pieza aleatoria en la siguiente posición
5. **Posicionamiento secuencial**: Las piezas se colocan automáticamente en orden (0,0), (0,1), (0,2)... hasta llenar el tablero
6. El juego termina cuando el tablero está completamente lleno
7. ¡Trata de obtener la máxima puntuación!

## Ejemplos de Puntuación

### Ejemplo 1: Cuadrado simple
```
═ ╗
╚ ╝
```
- Conexiones: 3 (derecha + abajo + T)
- Longitud: 4
- Puntuación: 4 × 3 = 12

### Ejemplo 2: Cuadrado con T mejorado
```
╦ ╔
╚ ╝
```
- Conexiones: 4 (derecha + abajo + T con 2 conexiones)
- Longitud: 4
- Puntuación: 4 × 4 = 16

## Requisitos del Sistema

- Compilador C++11 o superior (g++, clang++, etc.)
- Terminal que soporte caracteres Unicode para mostrar las piezas correctamente
- Linux, macOS, o Windows con WSL

## Notas Técnicas

- El programa usa caracteres de código de página 437 para los símbolos de tubería
- La validación de conexiones verifica que las piezas sean compatibles
- El algoritmo de puntuación usa BFS para encontrar fragmentos conectados
- Las piezas aleatorias se colocan automáticamente en el tablero al inicio
- Generación de números aleatorios usando `rand()` y `srand()` de `<cstdlib>`
