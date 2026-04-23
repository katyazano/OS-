#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

// Límite máximo de procesos
const int MAX_PROCESOS = 3; 

// ================= ESTRUCTURA UNIFICADA =================
struct Proceso {
    int id;             // PID
    string nombre;      // padre_pid
    string padre; 
    float tamano;       // Tamaño en MB
    short estado;       // 0-nuevo, 1-listo, 2-ejecución, 3-bloqueado
    int prioridad;      // 1-Alta, 2-Media, 3-Baja
    int llegada;        // time_arrival
};

// ================= VARIABLES GLOBALES =================
Proceso procesos[MAX_PROCESOS];
int totalProcesos = 0;
double vf = 0;
double lote = 0; 

// ================= FUNCIONES DE HARDWARE Y MEMORIA =================

void velocidadFinal() {
    int arquitectura;
    double fragmentacion;
    cout << "\n--- CONFIGURACION INICIAL DEL PROCESADOR ---\n";
    cout << "Ingrese la arquitectura del procesador (1: 16x, 2: 32x, 3: 64x): ";
    cin >> arquitectura;
    cout << "Ingrese el porcentaje de fragmentacion de la memoria (1-100): ";
    cin >> fragmentacion;

    int bits = (arquitectura == 1) ? 16 : (arquitectura == 3) ? 64 : 32;
    vf = (bits * fragmentacion) / 100.0;
}

double conversionMB() {
    double total = 0;
    for (int i = 0; i < totalProcesos; i++) {
        total += procesos[i].tamano;
    }
    return total;
}

void agregarProceso() {
    if (totalProcesos >= MAX_PROCESOS) {
        cout << "No se pueden agregar mas procesos. Limite de " << MAX_PROCESOS << " alcanzado.\n";
        return;
    }

    int i = totalProcesos;
    procesos[i].id = 100 + rand() % 900; // Random PID
    
    cout << "\n--- NUEVO PROCESO ---\n";
    cout << "Tiempo de llegada (0 en adelante): ";
    cin >> procesos[i].llegada;

    cout << "Nombre del proceso padre: ";
    cin >> procesos[i].padre;

    int unidad;
    double tamRaw;
    cout << "Unidad de Tamano (1:KB, 2:MB, 3:GB): ";
    cin >> unidad;
    cout << "Tamano: ";
    cin >> tamRaw;

    if (unidad == 1) procesos[i].tamano = tamRaw / 1024.0;
    else if (unidad == 3) procesos[i].tamano = tamRaw * 1024.0;
    else procesos[i].tamano = tamRaw;

    cout << "Estado (0-Nuevo, 1-Listo, 2-Ejecucion, 3-Bloqueado): ";
    cin >> procesos[i].estado;
    cout << "Prioridad (Numero menor = mas prioridad): ";
    cin >> procesos[i].prioridad;

    procesos[i].nombre = procesos[i].padre + "_" + to_string(procesos[i].id);
    totalProcesos++;
    
    cout << "Proceso " << procesos[i].nombre << " creado exitosamente.\n";
}

void simularProcesamiento() {
    if (totalProcesos == 0) {
        cout << "No hay procesos para procesar.\n";
        return;
    }

    double totalMB = conversionMB();
    int subOp;
    cout << "\n--- SIMULACION DE PROCESAMIENTO ---\n";
    cout << "1. Secuencial\n2. Batch\n3. Multiproceso\nSeleccione: ";
    cin >> subOp;

    switch (subOp) {
        case 1:
            cout << "Tiempo Secuencial: " << (totalMB / vf) << "s\n";
            break;
        case 2:
            cout << "Tamano del lote (MB): "; cin >> lote;
            cout << "Tiempo Batch: " << ((totalMB / lote) / vf) << "s\n";
            break;
        case 3:
            int n, sync;
            cout << "Nucleos: "; cin >> n;
            cout << "1. Sincrono / 2. Asincrono: "; cin >> sync;
            if (sync == 2) n--;
            cout << "Tamano del lote (MB): "; cin >> lote;
            cout << "Tiempo Multiproceso: " << (((totalMB / lote) / n) / vf) << "s\n";
            break;
        default:
            cout << "Opcion invalida.\n";
    }
}

// ================= ALGORITMOS DE PLANIFICACION =================

void fcfs() {
    if(totalProcesos == 0) { cout << "No hay procesos.\n"; return; }

    int llegada[MAX_PROCESOS], burst[MAX_PROCESOS], idx[MAX_PROCESOS];

    for(int i = 0; i < totalProcesos; i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = max(1, (int)(procesos[i].tamano * 0.5)); // Asegurar burst >= 1
        idx[i] = i;
    }

    // Ordenar por llegada
    for(int i = 0; i < totalProcesos - 1; i++){
        for(int j = i + 1; j < totalProcesos; j++){
            if(llegada[idx[i]] > llegada[idx[j]])
                swap(idx[i], idx[j]);
        }
    }

    int tiempo = 0;
    cout << "\n--- FCFS ---\n";

    for(int k = 0; k < totalProcesos; k++){
        int i = idx[k];
        if(tiempo < llegada[i]) tiempo = llegada[i];
        tiempo += burst[i];

        cout << "P" << procesos[i].id << " (" << procesos[i].nombre << ")"
             << " | tam=" << procesos[i].tamano << "MB | burst=" << burst[i]
             << " | fin=" << tiempo << endl;
    }
}

void sjf() {
    if(totalProcesos == 0) { cout << "No hay procesos.\n"; return; }

    int llegada[MAX_PROCESOS], burst[MAX_PROCESOS];
    bool hecho[MAX_PROCESOS] = {false};

    for(int i = 0; i < totalProcesos; i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = max(1, (int)(procesos[i].tamano * 0.5));
    }

    int tiempo = 0, completados = 0;
    cout << "\n--- SJF ---\n";

    while(completados < totalProcesos){
        int idx = -1, menor = 999999;

        for(int i = 0; i < totalProcesos; i++){
            if(!hecho[i] && llegada[i] <= tiempo && burst[i] < menor){
                menor = burst[i];
                idx = i;
            }
        }

        if(idx != -1){
            tiempo += burst[idx];
            hecho[idx] = true;
            completados++;
            cout << "P" << procesos[idx].id << " (" << procesos[idx].nombre << ")"
                 << " | fin=" << tiempo << endl;
        } else {
            tiempo++;
        }
    }
}

void roundRobin() {
    if(totalProcesos == 0) { cout << "No hay procesos.\n"; return; }

    int llegada[MAX_PROCESOS], burst[MAX_PROCESOS], restante[MAX_PROCESOS];
    bool enCola[MAX_PROCESOS] = {false};

    for(int i = 0; i < totalProcesos; i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = max(1, (int)(procesos[i].tamano * 0.5));
        restante[i] = burst[i];
    }

    int quantum = 2;
    int tiempo = 0, completados = 0;
    queue<int> cola;

    cout << "\n--- ROUND ROBIN (Quantum = " << quantum << ") ---\n";

    while(completados < totalProcesos){
        for(int i = 0; i < totalProcesos; i++){
            if(llegada[i] <= tiempo && !enCola[i] && restante[i] > 0){
                cola.push(i);
                enCola[i] = true;
            }
        }

        if(cola.empty()){
            tiempo++;
            continue;
        }

        int i = cola.front();
        cola.pop();

        int ejec = min(quantum, restante[i]);
        restante[i] -= ejec;
        tiempo += ejec;

        for(int j = 0; j < totalProcesos; j++){
            if(llegada[j] <= tiempo && !enCola[j] && restante[j] > 0){
                cola.push(j);
                enCola[j] = true;
            }
        }

        if(restante[i] > 0){
            cola.push(i);
        } else {
            completados++;
            cout << "P" << procesos[i].id << " (" << procesos[i].nombre << ")"
                 << " | fin=" << tiempo << endl;
        }
    }
}

void colasMultiples() {
    if(totalProcesos == 0) { cout << "No hay procesos.\n"; return; }

    int llegada[MAX_PROCESOS], burst[MAX_PROCESOS], idx[MAX_PROCESOS];

    for(int i = 0; i < totalProcesos; i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = max(1, (int)(procesos[i].tamano * 0.5));
        idx[i] = i;
    }

    // Ordenar por prioridad
    for(int i = 0; i < totalProcesos - 1; i++){
        for(int j = i + 1; j < totalProcesos; j++){
            if(procesos[idx[i]].prioridad > procesos[idx[j]].prioridad) 
                swap(idx[i], idx[j]); // Menor número = mayor prioridad
        }
    }

    int tiempo = 0;
    cout << "\n--- COLAS MULTIPLES ---\n";

    for(int k = 0; k < totalProcesos; k++){
        int i = idx[k];
        if(tiempo < llegada[i]) tiempo = llegada[i];
        tiempo += burst[i];

        cout << "P" << procesos[i].id << " (" << procesos[i].nombre << ")"
             << " | prio=" << procesos[i].prioridad
             << " | fin=" << tiempo << endl;
    }
}

void customMCP() {
    if(totalProcesos == 0) { cout << "No hay procesos.\n"; return; }

    int llegada[MAX_PROCESOS], burst[MAX_PROCESOS];
    bool hecho[MAX_PROCESOS] = {false};

    for(int i = 0; i < totalProcesos; i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = max(1, (int)(procesos[i].tamano * 0.5));
    }

    int tiempo = 0, completados = 0;

    cout << "\n--- CUSTOM: MENOR COSTO PONDERADO (MCP) ---\n";
    cout << "Formula: Costo = Burst * Prioridad. (Menor costo va primero)\n";

    while(completados < totalProcesos){
        int idx = -1;
        int menorCosto = 999999;

        for(int i = 0; i < totalProcesos; i++){
            if(!hecho[i] && llegada[i] <= tiempo){
                int costoActual = burst[i] * procesos[i].prioridad;
                if(costoActual < menorCosto){
                    menorCosto = costoActual;
                    idx = i;
                }
            }
        }

        if(idx != -1){
            tiempo += burst[idx];
            hecho[idx] = true;
            completados++;

            cout << "P" << procesos[idx].id << " (" << procesos[idx].nombre << ")"
                 << " | burst=" << burst[idx]
                 << " | prio=" << procesos[idx].prioridad
                 << " | costo=" << menorCosto
                 << " | fin=" << tiempo << endl;
        } else {
            tiempo++; 
        }
    }
}

// ================= MENU PRINCIPAL =================
int main() {
    srand(time(0));
    
    velocidadFinal();
    
    int op;
    do {
        cout << "\n===== SISTEMA FUSIONADO: GESTOR Y PLANIFICADOR =====\n";
        cout << "1. Agregar Proceso\n";
        cout << "2. Mostrar Procesos Activos\n";
        cout << "3. Simular Tiempos de Procesamiento (Secuencial, Batch...)\n";
        cout << "------------------------------------------------------\n";
        cout << "4. Ejecutar Planificador FCFS\n";
        cout << "5. Ejecutar Planificador SJF\n";
        cout << "6. Ejecutar Planificador Round Robin\n";
        cout << "7. Ejecutar Planificador Colas Multiples\n";
        cout << "8. Ejecutar Planificador Custom MCP\n";
        cout << "------------------------------------------------------\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op){
            case 1: agregarProceso(); break;
            case 2: 
                cout << "\n--- LISTA DE PROCESOS ---\n";
                if (totalProcesos == 0) {
                    cout << "No hay procesos agregados todavia.\n";
                } else {
                    for(int i = 0; i < totalProcesos; i++){
                        cout << "PID: " << procesos[i].id 
                             << " | Nombre: " << procesos[i].nombre 
                             << " | Llegada: " << procesos[i].llegada
                             << " | Prio: " << procesos[i].prioridad
                             << " | Tam: " << procesos[i].tamano << " MB\n";
                    }
                }
                break;
            case 3: simularProcesamiento(); break;
            case 4: fcfs(); break;
            case 5: sjf(); break;
            case 6: roundRobin(); break;
            case 7: colasMultiples(); break;
            case 8: customMCP(); break;
            case 0: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida.\n";
        }

    } while(op != 0);

    return 0;
}