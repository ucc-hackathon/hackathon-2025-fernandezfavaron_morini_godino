#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>


using namespace std;

struct Tuberia {
    char ascii;
    char simbolo;
    vector<pair<int, int>> conexiones;
    
    Tuberia(char code, char sym, vector<pair<int, int>> conn) 
        : ascii(code), simbolo(sym), conexiones(conn) {}
};

int main(int argc, char** argv) {

}
