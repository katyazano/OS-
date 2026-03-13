#include <iostream>
#include <iomanip>

using namespace std;
double procesos_mb[3];
int numProcesos;
int unidad;
double tamano;
int arquitectura;
double fragmentacion;
double mb;
double vf;
double lote;
double totalMB;

void conversion(){
    for(int i = 0; i < numProcesos; i++) {
        cout << "\nSeleccione la unidad original (1: KB, 2: MB, 3: GB, 4: TB): ";
        cin >> unidad;
        cout << "\nIngrese el tamano del proceso: ";
        cin >> tamano;

        if (unidad == 1) {
            mb = tamano / 1024.0;
        } else if (unidad == 3) {
            mb = tamano * 1024.0;
        } else if (unidad == 4){
            mb = tamano * 1024.0 * 1024.0;
        } else{
            mb = tamano;
        }
        procesos_mb[i] = mb;
    }
}

double suma(){
    double total = 0.0;
    for(int i = 0; i < numProcesos; i++) {
        total += procesos_mb[i];
    }
    return total;
}

void secuencial(){
    double secu = totalMB / vf;
    cout << "-> TIEMPO PROCESAMIENTO SECUENCIAL: " << secu << endl;
    cout << "-> VELOCIDAD FINAL DEL PROCESADOR: " << vf << " MB/s" << endl;
}

void batch(){
    cout << "\nIngrese el lote: ";
    cin >> lote;
    double batch = totalMB / lote;
    double tBatch = batch / vf;
    cout << "-> BATCH: " << batch << endl;
    cout << "-> TIEMPO PROCESAMIENTO BATCH: " << tBatch << endl;
    cout << "-> VELOCIDAD FINAL DEL PROCESADOR: " << vf << " MB/s" << endl;
}

int main() {
    int op;
    cout << "\nIngrese la arquitectura del procesador (1: 16x, 2: 32x, 3: 64x): ";
    cin >> arquitectura;
    cout << "\nIngrese el porcentaje de fragmentacion de la memoria (0-100): ";
    cin >> fragmentacion;
    do {
        cout << "Ingrese la cantidad de procesos (max 3): ";
        cin >> numProcesos;
    } while (numProcesos < 1 || numProcesos > 3);

    conversion();
    totalMB = suma();
    vf = (arquitectura * fragmentacion)/100;
    cout << fixed << setprecision(4);

    do{
        cout << R"(---- Simulador de Gestion de Memoria y Procesamientos ----
        1. Procesamiento secuencial
        2. Procesamiento por lote
        3. Multiprocesamiento //tbd
        4. Todos
        0. Salir
        )" << endl;
        cin >> op;

        switch (op)
        {
        case 1:
            secuencial();
            break;
        case 2:
            batch();
            break;
        case 3:
            cout << "tbd" << endl;
            break;
        case 0:
            break;
        default:
            cout << "\nOpcion no valida.\n" << endl;
            break;
        }
    } while (op != 0);

    return 0;
}