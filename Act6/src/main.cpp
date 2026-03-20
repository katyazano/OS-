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
    
    cout << "Nombre del proceso padre: ";
    cin >> procesos[i].padre;

    int unidad;
    double tamRaw;
    cout << "Unidad (1:KB, 2:MB, 3:GB): ";
    cin >> unidad;
    cout << "Tamano: ";
    cin >> tamRaw;

    if (unidad == 1) procesos[i].tamano = tamRaw / 1024.0;
    else if (unidad == 3) procesos[i].tamano = tamRaw * 1024.0;
    else procesos[i].tamano = tamRaw;

    cout << "Estado (0-Nuevo, 1-Listo, 2-Ejecucion, 3-Bloqueado): ";
    cin >> procesos[i].estado;
    cout << "Prioridad (0-Baja, 1-Media, 2-Alta): ";
    cin >> procesos[i].prioridad;

    procesos[i].nombre = procesos[i].padre + "_" + to_string(procesos[i].PID);
    totalProcesos++;
    cout << "Proceso " << procesos[i].nombre << " creado." << endl;
}

void simularProcesamiento() {
    if (totalProcesos == 0) {
        cout << "No hay procesos para procesar." << endl;
        return;
    }

    double totalMB = conversionMB();
    int subOp;
    cout << "\n1. Secuencial\n2. Batch\n3. Multiproceso\nSeleccione: ";
    cin >> subOp;

    switch (subOp) {
        case 1:
            cout << "Tiempo Secuencial: " << (totalMB / vf) << "s" << endl;
            break;
        case 2:
            cout << "Tamano del lote (MB): "; cin >> lote;
            cout << "Tiempo Batch: " << ((totalMB / lote) / vf) << "s" << endl;
            break;
        case 3:
            int n, sync;
            cout << "Nucleos: "; cin >> n;
            cout << "1. Sincrono / 2. Asincrono: "; cin >> sync;
            if (sync == 2) n--;
            cout << "Tamano del lote (MB): "; cin >> lote;
            cout << "Tiempo Multiproceso: " << (((totalMB / lote) / n) / vf) << "s" << endl;
            break;
    }
}

int main() {
    srand(time(0));
    velocidadFinal();
    
    int op;
    do {
        cout << "\n--- SISTEMA FUSIONADO ---" << endl;
        cout << "1. Agregar Proceso\n2. Mostrar Procesos\n3. Simular Procesamiento\n0. Salir\nOpcion: ";
        cin >> op;

        switch (op) {
            case 1: agregarProceso(); break;
            case 2: 
                for(int i=0; i<totalProcesos; i++) 
                    cout << "PID: " << procesos[i].PID << " | " << procesos[i].nombre << " | " << procesos[i].tamano << " MB" << endl;
                break;
            case 3: simularProcesamiento(); break;
        }
    } while (op != 0);

    return 0;
}