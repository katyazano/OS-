#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>  
#include <string>
using namespace std;

// Estructura para representar un proceso
struct proceso
    {
        short PID; //random
        string nombre; //padre_pid
        string padre; 
        float tamano;
        short estado; //nuevo, listo, ejecución, bloqueado, terminado
        short prioridad; //baja, media, alta
        int time_arrival; //random
    };

// Variables globales
proceso procesos[3];
short totalProcesos = 0;
double vf = 0;
double lote = 0; 

double conversionMB(){
    double total = 0;
    for (int i = 0; i < totalProcesos; i++) {
        total += procesos[i].tamano;
    }
    return total;
}

void velocidadFinal(){
    int arquitectura;
    double fragmentacion;
    cout << "Ingrese la arquitectura del procesador (1: 16x, 2: 32x, 3: 64x): ";
    cin >> arquitectura;
    cout << "Ingrese el porcentaje de fragmentacion de la memoria (1-100): ";
    cin >> fragmentacion;

    int bits = (arquitectura == 1) ? 16 : (arquitectura == 3) ? 64 : 32;
    vf = (bits * fragmentacion) / 100.0;
}

void agregarProceso(){
    if (totalProcesos >= 3) {
        cout << "No se pueden agregar mas procesos. Limite alcanzado." << endl;
        return;
    }

    int i = totalProcesos;
    procesos[i].PID = 100 + rand() % 900;
    procesos[i].time_arrival = rand() % 1000;
    
}