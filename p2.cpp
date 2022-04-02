#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <vector>
using namespace std;

struct Alumno
{
    char codigo[5];
    char nombre[11];
    char apellidos[20];
    char carrera[15];

    int ciclo;
    float mensualidad;
};

ostream &operator<<(ostream &stream, Alumno &p)
{
    stream << p.codigo;
    stream << p.nombre;
    stream << p.apellidos;
    stream << p.carrera;
    stream << "\n";
    stream << flush;
    return stream;
}

istream &operator>>(istream &stream, Alumno &p)
{
    stream.get(p.codigo, 5);
    stream.get(p.nombre, 11);
    stream.get(p.apellidos, 20);
    stream.get(p.carrera, 15);
    stream.get();
    return stream;
}

void readFromConsole(char buffer[], int size)
{
    string temp;
    cin >> temp;
    for (int i = 0; i < size; i++)
        buffer[i] = (i < temp.size()) ? temp[i] : ' ';
    buffer[size - 1] = '\0';
    cin.clear();
}

class FixedRecord
{
    string filename;

public:
    FixedRecord(string filename) : filename(filename){};

    vector<Alumno> load()
    {
        ifstream file;

        file.open(filename, ios::binary);
        vector<Alumno> todosLosAlumnos;
        if (file.is_open())
        {
            while (!file.eof())
            {
                Alumno alumno;
                file >> alumno;
                todosLosAlumnos.push_back(alumno);
            }
            file.close();
        }
        else
            cerr << "No se pudo abrir el archivo\n";

        return todosLosAlumnos;
    }

    void add(Alumno record)
    {
        ofstream file;

        file.open(filename, ios::app | ios::binary);

        if (file.is_open())
        {
            file << record;
            file.close();
        }
        else
            cerr << "No se pudo abrir el archivo\n";
    }

    Alumno readRecord(int pos)
    {
        ifstream file;
        file.open(filename, ios::binary);

        Alumno alumno;

        if (file.is_open())
        {
            file.seekg(pos * sizeof(alumno), ios::beg);

            file.read((char *)&alumno, sizeof(Alumno));

            file.close();

            return alumno;
        }
        else
            cerr << "No se pudo abrir el archivo\n";
    }
};

int main()
{
    FixedRecord record("datos1.txt");

    /*
        vector<Alumno> prueba = record.load();

        for (Alumno alumno : prueba)
            cout << alumno.nombre << endl;
    */

    /*
        Alumno prueba;
        readFromConsole(prueba.codigo, 5);
        readFromConsole(prueba.nombre, 11);
        readFromConsole(prueba.apellidos, 20);
        readFromConsole(prueba.carrera, 15);

        record.add(prueba);
    */

    Alumno prueba = record.readRecord(2);

    cout << prueba << endl;

    return 0;
}