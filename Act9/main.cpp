#include <iostream>
#include <algorithm>
#include <queue> 
using namespace std;

const int N = 3;

// ================= ESTRUCTURA =================
struct Proceso {
    int id;
    int llegada;
    int prioridad;
    float tamano;   // MB
};

// ================= PROCESOS =================
Proceso procesos[N] = {
    {1, 0, 2, 10.5},
    {2, 2, 1, 25.0},
    {3, 4, 3, 15.75}
};

// ================= FCFS =================
void fcfs() {
    int llegada[N], burst[N], idx[N];

    for(int i=0;i<N;i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = (int)(procesos[i].tamano * 0.5); 
        idx[i] = i;
    }

    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            if(llegada[idx[i]] > llegada[idx[j]])
                swap(idx[i], idx[j]);
        }
    }

    int tiempo = 0;

    cout << "\n--- FCFS ---\n";

    for(int k=0;k<N;k++){
        int i = idx[k];

        if(tiempo < llegada[i])
            tiempo = llegada[i];

        tiempo += burst[i];

        cout << "P" << procesos[i].id
             << " | tam=" << procesos[i].tamano
             << "MB | burst=" << burst[i]
             << " | fin=" << tiempo << endl;
    }
}

// ================= SJF =================
void sjf() {
    int llegada[N], burst[N];
    bool hecho[N] = {false};

    for(int i=0;i<N;i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = (int)(procesos[i].tamano * 0.5);
    }

    int tiempo = 0, completados = 0;

    cout << "\n--- SJF ---\n";

    while(completados < N){
        int idx = -1, menor = 9999;

        for(int i=0;i<N;i++){
            if(!hecho[i] && llegada[i] <= tiempo && burst[i] < menor){
                menor = burst[i];
                idx = i;
            }
        }

        if(idx != -1){
            tiempo += burst[idx];
            hecho[idx] = true;
            completados++;

            cout << "P" << procesos[idx].id
                 << " | fin=" << tiempo << endl;
        } else {
            tiempo++;
        }
    }
}

// ================= ROUND ROBIN =================
void roundRobin() {
    int llegada[N], burst[N], restante[N];
    bool enCola[N] = {false};

    for(int i=0;i<N;i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = (int)(procesos[i].tamano * 0.5);
        restante[i] = burst[i];
    }

    int quantum = 2;
    int tiempo = 0, completados = 0;

    queue<int> cola;

    cout << "\n--- ROUND ROBIN ---\n";

    while(completados < N){

        for(int i=0;i<N;i++){
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

        for(int j=0;j<N;j++){
            if(llegada[j] <= tiempo && !enCola[j] && restante[j] > 0){
                cola.push(j);
                enCola[j] = true;
            }
        }

        if(restante[i] > 0){
            cola.push(i);
        } else {
            completados++;

            cout << "P" << procesos[i].id
                 << " | fin=" << tiempo << endl;
        }
    }
}

// ================= COLAS MULTIPLES =================
void colasMultiples() {
    int llegada[N], burst[N], idx[N];

    for(int i=0;i<N;i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = (int)(procesos[i].tamano * 0.5);
        idx[i] = i;
    }

    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            if(procesos[idx[i]].prioridad < procesos[idx[j]].prioridad)
                swap(idx[i], idx[j]);
        }
    }

    int tiempo = 0;

    cout << "\n--- COLAS MULTIPLES ---\n";

    for(int k=0;k<N;k++){
        int i = idx[k];

        if(tiempo < llegada[i])
            tiempo = llegada[i];

        tiempo += burst[i];

        cout << "P" << procesos[i].id
             << " | prio=" << procesos[i].prioridad
             << " | fin=" << tiempo << endl;
    }
}

// ================= CUSTOM: MENOR COSTO PONDERADO =================
void customMCP() {
    int llegada[N], burst[N];
    bool hecho[N] = {false};

    for(int i=0;i<N;i++){
        llegada[i] = procesos[i].llegada;
        burst[i] = (int)(procesos[i].tamano * 0.5);
    }

    int tiempo = 0, completados = 0;

    cout << "\n--- CUSTOM: MENOR COSTO PONDERADO (MCP) ---\n";
    cout << "Formula: Costo = Burst * Prioridad. (Menor costo va primero)\n";

    while(completados < N){
        int idx = -1;
        int menorCosto = 999999;

        // Buscamos el proceso disponible con el menor "costo"
        for(int i=0;i<N;i++){
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

            cout << "P" << procesos[idx].id
                 << " | burst=" << burst[idx]
                 << " | prio=" << procesos[idx].prioridad
                 << " | costo=" << menorCosto
                 << " | fin=" << tiempo << endl;
        } else {
            tiempo++; // Si no hay nadie en cola todavía, el CPU espera
        }
    }
}

// ================= MENU =================
int main() {
    int op;

    do {
        cout << "\n===== PLANIFICADOR CPU =====\n";
        cout << "Procesos activos:\n";
        for(int i=0;i<N;i++){
            cout << "P" << procesos[i].id
                 << " | llegada=" << procesos[i].llegada
                 << " | prio=" << procesos[i].prioridad
                 << " | tam=" << procesos[i].tamano << "MB\n";
        }

        cout << "\nElige algoritmo:\n";
        cout << "1. FCFS\n";
        cout << "2. SJF\n";
        cout << "3. Round Robin\n";
        cout << "4. Colas Multiples\n";
        cout << "5. CustomS\n"; // <--- Nueva opción
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op){
            case 1: fcfs(); break;
            case 2: sjf(); break;
            case 3: roundRobin(); break;
            case 4: colasMultiples(); break;
            case 5: customMCP(); break; // <--- Ejecución del nuevo algoritmo
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida\n";
        }

    } while(op != 0);

    return 0;
}