#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Habitacion
{
public:
    string elemento;
    Habitacion *norte;
    Habitacion *sur;
    Habitacion *este;
    Habitacion *oeste;

    void Conectar(Habitacion *otra, string direccion)
    {
        if (direccion == "norte")
        {
            norte = otra;
            otra->sur = this;
        }
        else if (direccion == "sur")
        {
            sur = otra;
            otra->norte = this;
        }
        else if (direccion == "este")
        {
            este = otra;
            otra->oeste = this;
        }
        else if (direccion == "oeste")
        {
            oeste = otra;
            otra->este = this;
        }
    };
    Habitacion(string elem) : elemento(elem), norte(nullptr), sur(nullptr), este(nullptr), oeste(nullptr) {};
};

string elementoRandom()
{
    if (rand() % 2 == 0)
    {
        return "alimento";
    }
    else
    {
        return "arma";
    }
};

class Mapa
{
public:
    vector<Habitacion> habitaciones;
    Habitacion *habitacionActual;

    Mapa()
    {
        habitaciones.push_back(Habitacion(elementoRandom()));
        habitaciones.push_back(Habitacion(elementoRandom()));
        habitaciones.push_back(Habitacion(elementoRandom()));
        habitaciones.push_back(Habitacion(elementoRandom()));
        habitaciones.push_back(Habitacion(elementoRandom()));
        habitaciones.push_back(Habitacion(elementoRandom()));
        habitaciones.push_back(Habitacion(elementoRandom()));
        habitaciones.push_back(Habitacion(elementoRandom()));

        habitacionActual = &habitaciones[1];

        habitaciones[1].Conectar(&habitaciones[3], "sur");
        habitaciones[3].Conectar(&habitaciones[4], "oeste");
        habitaciones[4].Conectar(&habitaciones[2], "norte");
        habitaciones[4].Conectar(&habitaciones[6], "sur");
        habitaciones[4].Conectar(&habitaciones[5], "oeste");
        habitaciones[6].Conectar(&habitaciones[7], "oeste");
        habitaciones[5].Conectar(&habitaciones[7], "sur");
    }
};

class personaje
{
private:
    int armas = 0;
    int alimentos = 0;

public:
    void tomarElemento(string elemento)
    {
        if (elemento == "arma")
        {
            armas++;
        }
        else if (elemento == "alimento")
        {
            alimentos++;
        }
    }
    void mostrarInventario()
    {
        cout << "Armas: " << armas << ", Alimentos: " << alimentos << endl;
    }
    int CalcularPuntaje()
    {
        return (armas * 10) + (alimentos * 5);
    }
};

int main()
{
    Mapa mapa;
    personaje jugador;
    int pasos = rand() % 10 + 7;

    jugador.mostrarInventario();
    cout << "Puntaje total: " << jugador.CalcularPuntaje() << endl;
    for (int i = 0; i < pasos; i++)
    {
        cout << "Pasos restantes: " << pasos - i << endl;
        cout << "Estas en la habitacion con elemento: " << mapa.habitacionActual->elemento << endl;
        if (mapa.habitacionActual->elemento != "ninguno")
        {
            cout << "Deseas tomar el elemento? (s/n): ";
            char opcion;
            cin >> opcion;
            if (opcion == 's' || opcion == 'S')
            {
                jugador.tomarElemento(mapa.habitacionActual->elemento);
                mapa.habitacionActual->elemento = "ninguno";
            }
        }
        cout << "Hacia donde deseas ir? (norte/sur/este/oeste): ";
        string direccion;
        cin >> direccion;
        if (direccion == "norte" && mapa.habitacionActual->norte != nullptr)
        {
            mapa.habitacionActual = mapa.habitacionActual->norte;
        }
        else if (direccion == "sur" && mapa.habitacionActual->sur != nullptr)
        {
            mapa.habitacionActual = mapa.habitacionActual->sur;
        }
        else if (direccion == "este" && mapa.habitacionActual->este != nullptr)
        {
            mapa.habitacionActual = mapa.habitacionActual->este;
        }
        else if (direccion == "oeste" && mapa.habitacionActual->oeste != nullptr)
        {
            mapa.habitacionActual = mapa.habitacionActual->oeste;
        }
        else
        {
            cout << "Direccion invalida. Permanece en la misma habitacion." << endl;
        }
        jugador.mostrarInventario();
    }
    cout << "Juego terminado. Puntaje total: " << jugador.CalcularPuntaje() << endl;
    cout << "Gracias por jugar!" << endl;
    return 0;
};