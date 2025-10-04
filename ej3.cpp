#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Equipo
{
private:
    string nombre;

public:
    Equipo(string n)
    {
        nombre = n;
    }
    string getNombre() const { return nombre; }
};

class Partido
{
private:
    Equipo equipo1;
    Equipo equipo2;
    int golesEquipo1;
    int golesEquipo2;

public:
    Partido(Equipo eq1, Equipo eq2, int g1, int g2) : equipo1(eq1), equipo2(eq2),
                                                      golesEquipo1(g1), golesEquipo2(g2) {}
    Equipo getEquipo1() const { return equipo1; }
    Equipo getEquipo2() const { return equipo2; }
    int getGolesEquipo1() const { return golesEquipo1; }
    int getGolesEquipo2() const { return golesEquipo2; }
};

int golesT(Partido &p)
{
    return (p.getGolesEquipo1() + p.getGolesEquipo2());
}

void programa(Partido arreglo[15])
{
    for (int i = 0; i < 15 - 1; i++)
    {
        for (int j = 0; j < 15 - i - 1; j++)
        {
            if (golesT(arreglo[j]) > golesT(arreglo[j + 1]))
            {
                Partido temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
            }
        }
    }
    unordered_map<string, int> h;
    for (int i = 0; i < 15; i++)
    {
        string equipo1 = arreglo[i].getEquipo1().getNombre();
        string equipo2 = arreglo[i].getEquipo2().getNombre();
        if (arreglo[i].getGolesEquipo1() > arreglo[i].getGolesEquipo2())
        {
            h[equipo1] += 3;
        }
        else if (arreglo[i].getGolesEquipo1() == arreglo[i].getGolesEquipo2())
        {
            h[equipo1] += 1;
            h[equipo2] += 1;
        }
        else
        {
            h[equipo2] += 3;
        }
    }
    pair<string, int> ganadores[3];
    ganadores[0].second = 0;
    ganadores[1].second = 0;
    ganadores[2].second = 0;

    for (const auto &pair : h)
    {
        if (pair.second > ganadores[0].second)
        {
            ganadores[2] = ganadores[1];
            ganadores[1] = ganadores[0];
            ganadores[0].first = pair.first;
            ganadores[0].second = pair.second;
        }
        else if (pair.second > ganadores[1].second)
        {
            ganadores[2] = ganadores[1];
            ganadores[1].first = pair.first;
            ganadores[1].second = pair.second;
        }
        else if (pair.second > ganadores[2].second)
        {
            ganadores[2].first = pair.first;
            ganadores[2].second = pair.second;
        }
    }

    cout << "Partidos ordenados por goles totales:" << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << arreglo[i].getEquipo1().getNombre() << " (" << arreglo[i].getGolesEquipo1() << ") vs "
             << arreglo[i].getEquipo2().getNombre() << " (" << arreglo[i].getGolesEquipo2() << ") - Total: "
             << golesT(arreglo[i]) << endl;
    }
    cout << "\nPodio:" << endl;
    for (int i = 0; i < 3; i++)
    {
        if (ganadores[i].second > 0)
            cout << (i + 1) << ". " << ganadores[i].first << " - " << ganadores[i].second << " puntos" << endl;
    }
}

int main() {
    // 6 equipos, 15 partidos (todas las combinaciones)
    Equipo boca("Boca"), river("River"), racing("Racing"),
           indep("Independiente"), sanlo("San Lorenzo"), hur("Huracan");

    Partido partidos[15] = {
        // Boca contra todos
        Partido(boca, river, 2, 1),   // Boca +3
        Partido(boca, racing, 1, 1),  // +1 c/u
        Partido(boca, indep, 3, 0),   // Boca +3
        Partido(boca, sanlo, 0, 0),   // +1 c/u
        Partido(boca, hur,   2, 2),   // +1 c/u

        // River contra todos menos Boca
        Partido(river, racing, 0, 2), // Racing +3
        Partido(river, indep, 1, 0),  // River +3
        Partido(river, sanlo, 2, 2),  // +1 c/u
        Partido(river, hur,   3, 1),  // River +3

        // Racing contra todos menos Boca y River
        Partido(racing, indep, 1, 0), // Racing +3
        Partido(racing, sanlo, 2, 2), // +1 c/u
        Partido(racing, hur,   0, 1), // Huracan +3

        // Independiente contra los que faltan
        Partido(indep, sanlo, 1, 1),  // +1 c/u
        Partido(indep, hur,   0, 2),  // Huracan +3

        // San Lorenzo vs Huracan
        Partido(sanlo, hur,   0, 0)   // +1 c/u
    };

    programa(partidos);
    return 0;
}