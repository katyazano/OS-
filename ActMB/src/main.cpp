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
double lote = 0; 
double totalMB;
int nucleos;

void conversion(){
    for(int i = 0; i < numProcesos; i++) {
        cout << "\nSeleccione la unidad original (1: KB, 2: MB, 3: GB, 4: TB) para el proceso " << i+1 << ": ";
        cin >> unidad;
        cout << "Ingrese el tamano del proceso: ";
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
    cout << "\n-> TIEMPO PROCESAMIENTO SECUENCIAL: " << secu << " segundos" << endl;
    cout << "-> VELOCIDAD FINAL DEL PROCESADOR: " << vf << " MB/s" << endl;
}

void batch(){
    if (lote <= 0) {
        cout << "\nIngrese el lote (MB): ";
        cin >> lote;
    }
    double batch = totalMB / lote;
    double tBatch = batch / vf;
    cout << "\n-> BATCH (Lotes): " << batch << endl;
    cout << "-> TIEMPO PROCESAMIENTO BATCH: " << tBatch << " segundos" << endl;
    cout << "-> VELOCIDAD FINAL DEL PROCESADOR: " << vf << " MB/s" << endl;
}

void multiproceso(){    
    if (vf <= 0) {
        cout << "\nError: velocidad final invalida (revise la fragmentacion)." << endl;
        return;
    }

    cout << "\nIngrese la cantidad de procesadores (nucleos): ";
    cin >> nucleos;

    if (nucleos <= 0) {
        cout << "Error: cantidad de procesadores invalida." << endl;
        return;
    }

    int sincronia;
    cout << "Ingrese tipo de procesamiento (1. Sincronia / 2. Asincronia): ";
    cin >> sincronia;

    if (sincronia <= 0 || sincronia >= 3) {
        cout << "Error: opcion de sincronia invalida." << endl;
        return;
    } else if (sincronia == 1){
        nucleos = nucleos; // Sincrono: usan todos
    } else {
        nucleos = nucleos - 1; // Asincrono: se reserva uno
    }

    if (lote <= 0) {
        cout << "Para el multiprocesamiento, ingrese el tamano del lote (MB): ";
        cin >> lote;
    }

    double p_multi = ((totalMB / lote ) / nucleos ) / vf;

    cout << "\n[3] Velocidad Final Global: " << vf << " MB/s" << endl;
    cout << "[3] Tiempo Multiproceso (" << nucleos << " nucleos activos): " << p_multi << " segundos\n" << endl;
}

int main() {
    int op;
    cout << "\nIngrese la arquitectura del procesador (1: 16x, 2: 32x, 3: 64x): ";
    cin >> arquitectura;
    cout << "Ingrese el porcentaje de fragmentacion de la memoria (1-100): ";
    cin >> fragmentacion;

    do {
        cout << "Ingrese la cantidad de procesos (max 3): ";
        cin >> numProcesos;
    } while (numProcesos < 1 || numProcesos > 3);

    conversion();
    totalMB = suma();

    int bits_reales = 32;
    if (arquitectura == 1) bits_reales = 16;
    else if (arquitectura == 2) bits_reales = 32;
    else if (arquitectura == 3) bits_reales = 64;

    vf = (bits_reales * fragmentacion) / 100.0;
    
    cout << fixed << setprecision(4);

    do {
        cout << R"(
---- Simulador de Gestion de Memoria y Procesamientos ----
        1. Procesamiento secuencial
        2. Procesamiento por lote
        3. Multiprocesamiento
        4. Todos
        0. Salir
Elige una opcion: )";
        cin >> op;

        switch (op) {
            case 1:
                secuencial();
                break;
            case 2:
                batch();
                break;
            case 3:
                multiproceso();
                break;
            case 4: 
                secuencial();
                batch();
                multiproceso();
                break;
            case 0:
                cout << "\nSaliendo...\n" << endl;
                break;
            default:
                cout << "\nOpcion no valida.\n" << endl;
                break;
        }
    } while (op != 0);

    return 0;
}