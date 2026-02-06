#include <iostream>
#include <cstdlib>  // rand, srand
#include <ctime>    // time

using namespace std;
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

int op;
proceso procesos[3];
short totalProcesos = 0;

void menu(){
    cout << "Selecciona una de las opciones" << endl;
    cout << "1. Agregar proceso" << endl;
    cout << "2. Mostrar procesos" << endl;
    cout << "3. Eliminar proceso" << endl;
    cout << "4. Salir" << endl;
}

void agregarProceso(){
    short cant, aux[3];
    cout << "Cuantos procesos desea agregar (max 3): ";
    cin >> cant;

    if (cant < 1 || cant > 3) {
        cout << "Cantidad invalida." << endl;
        return;
    } else if (cant < 1 || totalProcesos + cant > 3){
        cout << "No hay espacio para tantos procesos." << endl;
        return;
    }

    for (int i = 0; i < cant; i++){
        aux[i] = 100 + rand() % 900; //100 - 999
        if (i == 0){
            procesos[i].PID = aux[i];
        }
        else{
            for (int j = 0; j < i; j++){
                while (aux[i] == aux[j]){
                    aux[i] = 100 + rand() % 900;
                }
            }
            procesos[i].PID = aux[i];
        }

        procesos[i].time_arrival = 100 + rand() % 900;

        cout << "Ingrese el nombre del proceso padre: ";
        cin >> procesos[i].padre;

        cout << "Ingrese el tamano del proceso: ";
        cin >> procesos[i].tamano;

        cout << "Ingrese el estado del proceso (0-nuevo, 1-listo, 2-ejecucion, 3-bloqueado, 4-terminado): ";
        cin >> procesos[i].estado;

        cout << "Ingrese la prioridad del proceso (0-baja, 1-media, 2-alta): ";
        cin >> procesos[i].prioridad;

        procesos[i].nombre = procesos[i].padre + "_" + to_string(procesos[i].PID);
        
        cout << "Proceso agregado exitosamente!" << endl;

        totalProcesos++;
    }
}

void mostrarProcesos(){
    if (totalProcesos == 0) {
        cout << "No hay procesos registrados." << endl;
        return;
    }

    cout << "Elige una opcion: \n1. Mostrar todos los procesos\n2. Mostrar un proceso" << endl;
    cin >> op;
    
    if (op == 1) {
        for (int i = 0; i < totalProcesos; i++) {
            cout << "\nProceso " << i + 1 << endl;
            cout << "PID: " << procesos[i].PID << endl;
            cout << "Nombre: " << procesos[i].nombre << endl;
            cout << "Padre: " << procesos[i].padre << endl;
            cout << "Tamano: " << procesos[i].tamano << endl;
            cout << "Estado: " << procesos[i].estado << endl;
            cout << "Prioridad: " << procesos[i].prioridad << endl;
            cout << "Tiempo de llegada: " << procesos[i].time_arrival << endl;
        }
    }
    else if (op == 2) {
        int indice;
        cout << "Ingrese el numero del proceso (1 a " << totalProcesos << "): ";
        cin >> indice;

        if (indice < 1 || indice > totalProcesos) {
            cout << "Proceso invalido." << endl;
            return;
        }

        int i = indice - 1;
        cout << "\nPID: " << procesos[i].PID << endl;
        cout << "Nombre: " << procesos[i].nombre << endl;
        cout << "Padre: " << procesos[i].padre << endl;
        cout << "Tamano: " << procesos[i].tamano << endl;
        cout << "Estado: " << procesos[i].estado << endl;
        cout << "Prioridad: " << procesos[i].prioridad << endl;
        cout << "Tiempo de llegada: " << procesos[i].time_arrival << endl;
    }
    else {
        cout << "Opcion invalida." << endl;
    }
}

void eliminarProceso(){
    if (totalProcesos == 0) {
        cout << "No hay procesos para eliminar." << endl;
        return;
    }

    short pid;
    cout << "Ingrese el PID del proceso a eliminar: ";
    cin >> pid;
    short pos = -1;


    for (int i = 0; i < totalProcesos; i++) {
        if (procesos[i].PID == pid) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "No se encontro ningun proceso con ese PID." << endl;
        return;
    }

    for (int i = pos; i < totalProcesos - 1; i++) {
        procesos[i] = procesos[i + 1];
    }

    procesos[totalProcesos - 1] = {};
    totalProcesos--;
    procesos[pos].estado = 4; // terminado
    cout << "Proceso eliminado correctamente." << endl;
}

int main(){
    srand(time(0));

    menu();
    cin >> op;
    while (op >= 1 && op <= 4){
        switch (op)
        {
        case 1:
            cout << "Agregando proceso..." << endl;
            agregarProceso();
            break;
        
        case 2:
            mostrarProcesos();
            break;
        
        case 3:
            eliminarProceso();
            break;
        
        case 4:
            cout << "Saliendo del sistema..." << endl;
            return 0;
        
        default:
            cout << "Opcion no valida, intente de nuevo" << endl;

            break;
        }
        menu();
        cin >> op;
    }
}