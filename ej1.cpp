#include <iostream>
using namespace std;

struct Libro
{
    int codigo;
    string titulo;
    string autor;
    int año;
    string categoria;
    bool prestado;
    int total_prestamos;

    Libro() = default;
    Libro(int c, string t, string a, int año, string cat)
        : codigo(c), titulo(t), autor(a), año(año), categoria(cat),
          prestado(false), total_prestamos(0) {}
};

class Usuario
{
private:
    string nombre;
    int id;

public:
    Usuario() = default;
    Usuario(string n, int i) : nombre(n), id(i) {}
    string getNombre() const { return nombre; }
    int getId() const { return id; }
};

class Alumno : public Usuario
{
    string legajo;
    int año;

public:
    Alumno() = default;
    Alumno(string n, int i, string l, int a) : Usuario(n, i), legajo(l), año(a) {}
    string getLegajo() const { return legajo; }
    int getAño() const { return año; }
};

class Profesor : public Usuario
{
    string legajo;
    string area;

public:
    Profesor() = default;
    Profesor(string n, int i, string l, string a) : Usuario(n, i), legajo(l), area(a) {}
    string getLegajo() const { return legajo; }
    string getArea() const { return area; }
};

struct Prestamo
{
    int codigoLibro;
    int idUsuario;
    string fechaPrestamo;
    bool devuelto;
    string fechaDevolucion;
};

class Biblioteca
{
public:
    Libro libros[100];
    Usuario *usuarios[20];
    Prestamo prestamos[200];
    int prestamosCount = 0;

    void agregarAlumno(string nombre, int id, string legajo, int año)
    {
        for (int i = 0; i < 20; i++)
        {
            if (usuarios[i] == nullptr)
            {
                usuarios[i] = new Alumno(nombre, id, legajo, año);
                return;
            }
            else
            {
                delete usuarios[i];
                usuarios[i] = new Alumno(nombre, id, legajo, año);
            }
        }
        cout << "No hay espacio para más usuarios." << endl;
    }

    void prestarLibro(int codigoLibro, int idUsuario, string fecha)
    {
        for (int i = 0; i < 100; i++)
        {
            if (libros[i].codigo == codigoLibro && !libros[i].prestado)
            {
                libros[i].prestado = true;
                libros[i].total_prestamos++;
                prestamos[prestamosCount++] = {codigoLibro, idUsuario, fecha, false, ""};
                cout << "Libro prestado" << endl;
                return;
            }
        }
        cout << "Libro no disponible" << endl;
    }

    void devolverLibro(int codigoLibro, int idUsuario, string fecha)
    {
        for (int i = 0; i < prestamosCount; i++)
        {
            if (prestamos[i].codigoLibro == codigoLibro && prestamos[i].idUsuario == idUsuario && !prestamos[i].devuelto)
            {
                prestamos[i].devuelto = true;
                prestamos[i].fechaDevolucion = fecha;
                for (int j = 0; j < 100; j++)
                {
                    if (libros[j].codigo == codigoLibro)
                    {
                        libros[j].prestado = false;
                        cout << "Libro devuelto" << endl;
                        return;
                    }
                }
            }
        }
    }

    void listarLibrosPrestados()
    {
        for (int i = 0; i < prestamosCount; i++)
        {
            if (!prestamos[i].devuelto)
            {
                cout << "Codigo Libro: " << prestamos[i].codigoLibro << endl;
                cout << "ID Usuario: " << prestamos[i].idUsuario << endl;
                cout << "Fecha Prestamo: " << prestamos[i].fechaPrestamo << endl;
                cout << "------------------------" << endl;
            }
        }
    }

    void listarLibrosDisponibles()
    {
        for (int i = 0; i < 100; i++)
        {
            if (!libros[i].prestado && libros[i].codigo != 0)
            {
                cout << "Codigo: " << libros[i].codigo << endl;
                cout << "Titulo: " << libros[i].titulo << endl;
                cout << "Autor: " << libros[i].autor << endl;
                cout << "Año: " << libros[i].año << endl;
                cout << "Categoria: " << libros[i].categoria << endl;
                cout << "------------------------" << endl;
            }
        }
    }

    void buscarLibroPorAutor(string autor)
    {
        for (int i = 0; i < 100; i++)
        {
            if (libros[i].autor == autor)
            {
                cout << "Codigo: " << libros[i].codigo << endl;
                cout << "Titulo: " << libros[i].titulo << endl;
                cout << "Año: " << libros[i].año << endl;
                cout << "Categoria: " << libros[i].categoria << endl;
                cout << "------------------------" << endl;
            }
        }
    }

    void buscarLibroPorCategoria(string categoria)
    {
        for (int i = 0; i < 100; i++)
        {
            if (libros[i].categoria == categoria)
            {
                cout << "Codigo: " << libros[i].codigo << endl;
                cout << "Titulo: " << libros[i].titulo << endl;
                cout << "Autor: " << libros[i].autor << endl;
                cout << "Año: " << libros[i].año << endl;
                cout << "Categoria: " << libros[i].categoria << endl;
                cout << "------------------------" << endl;
            }
        }
    }

    void librosMasPrestados()
    {
        for (int i = 0; i < 100 - 1; i++)
        {
            for (int j = 0; j < 100 - i - 1; j++)
            {
                if (libros[j].total_prestamos < libros[j + 1].total_prestamos)
                {
                    Libro temp = libros[j];
                    libros[j] = libros[j + 1];
                    libros[j + 1] = temp;
                }
            }
        }
        cout << "Los 3 libros más prestados:" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << "Codigo: " << libros[i].codigo << endl;
            cout << "Titulo: " << libros[i].titulo << endl;
            cout << "Autor: " << libros[i].autor << endl;
            cout << "Total prestamos: " << libros[i].total_prestamos << endl;
            cout << "------------------------" << endl;
        }
    }

    void usuarioMasLibrosPrestados(const string &fechaInicio, const string &fechaFin)
    {
        int maxPrestamos = 0;
        int idxUsuarioMax = -1;

        for (int i = 0; i < 20; ++i)
        {
            if (!usuarios[i])
                continue; // <- clave
            int cont = 0;
            int id = usuarios[i]->getId();
            for (int j = 0; j < prestamosCount; ++j)
            {
                const auto &p = prestamos[j];
                if (p.idUsuario == id &&
                    p.fechaPrestamo >= fechaInicio &&
                    p.fechaPrestamo <= fechaFin)
                {
                    ++cont;
                }
            }
            if (cont > maxPrestamos)
            {
                maxPrestamos = cont;
                idxUsuarioMax = i;
            }
        }

        if (idxUsuarioMax != -1)
        {
            cout << "Usuario con más libros prestados entre " << fechaInicio << " y " << fechaFin << ":\n";
            cout << "Nombre: " << usuarios[idxUsuarioMax]->getNombre() << "\n";
            cout << "ID: " << usuarios[idxUsuarioMax]->getId() << "\n";
            cout << "Cantidad de préstamos: " << maxPrestamos << "\n";
        }
        else
        {
            cout << "No se encontraron préstamos en ese rango de fechas.\n";
        }
    }
    ~Biblioteca()
    {
        for (int i = 0; i < 20; i++)
        {
            delete usuarios[i];
        }
    }
};

int main()
{
    Biblioteca b;

    // Crear usuarios
    b.usuarios[0] = new Alumno("Juan", 1, "A001", 2023);
    b.usuarios[1] = new Alumno("Ana", 2, "A002", 2022);
    b.usuarios[2] = new Profesor("Carlos", 3, "P001", "Matematica");
    b.usuarios[3] = new Profesor("Laura", 4, "P002", "Historia");
    b.usuarios[4] = new Alumno("Pedro", 5, "A003", 2021);

    // Crear libros
    b.libros[0] = Libro(101, "C++ Básico", "Bjarne", 2010, "Programacion");
    b.libros[1] = Libro(102, "Historia Universal", "Smith", 2005, "Historia");
    b.libros[2] = Libro(103, "Matematica I", "Euler", 2000, "Matematica");
    b.libros[3] = Libro(104, "Fisica Moderna", "Feynman", 2015, "Fisica");
    b.libros[4] = Libro(105, "Quimica General", "Curie", 2012, "Quimica");
    b.libros[5] = Libro(106, "Literatura", "Cervantes", 1999, "Literatura");
    b.libros[6] = Libro(107, "Biologia", "Darwin", 2008, "Biologia");
    b.libros[7] = Libro(108, "Geografia", "Humboldt", 2011, "Geografia");
    b.libros[8] = Libro(109, "Arte", "Da Vinci", 2003, "Arte");
    b.libros[9] = Libro(110, "Programacion Avanzada", "Stroustrup", 2018, "Programacion");

    // Realizar préstamos
    b.prestarLibro(101, 1, "2023-05-01");
    b.prestarLibro(101, 2, "2023-05-02");
    b.prestarLibro(101, 3, "2023-05-03");
    b.prestarLibro(104, 4, "2023-05-04");
    b.prestarLibro(105, 5, "2023-05-05");
    b.prestarLibro(106, 1, "2023-05-06");
    b.prestarLibro(107, 2, "2023-05-07");
    b.prestarLibro(108, 3, "2023-05-08");
    b.prestarLibro(109, 4, "2023-05-09");
    b.prestarLibro(110, 5, "2023-05-10");

    // Devolver algunos libros
    b.devolverLibro(104, 4, "2023-06-01");
    b.devolverLibro(102, 2, "2023-06-02");

    // Probar métodos
    cout << "\n--- Libros Prestados ---\n";
    b.listarLibrosPrestados();

    cout << "\n--- Libros Disponibles ---\n";
    b.listarLibrosDisponibles();

    cout << "\n--- Buscar por Autor: Darwin ---\n";
    b.buscarLibroPorAutor("Darwin");

    cout << "\n--- Buscar por Categoria: Programacion ---\n";
    b.buscarLibroPorCategoria("Programacion");

    cout << "\n--- Libros Más Prestados ---\n";
    b.librosMasPrestados();

    cout << "\n--- Usuario con más libros prestados entre 2023-05-01 y 2023-05-10 ---\n";
    b.usuarioMasLibrosPrestados("2023-05-01", "2023-05-10");
    return 0;
}