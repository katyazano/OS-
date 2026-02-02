#include <iostream>
#include <cstdlib>  // rand, srand
#include <ctime>    // time

using namespace std;
struct proceso
    {
        short PID;
        string nombre;
        string padre;
        float tamano;
        short estado; //nuevo, listo, ejecución, bloqueado, terminado
        short prioridad; //baja, media, alta
        int time_arrival;
    };

int op = NULL;
proceso procesos[3];

void menu(){
    int op = NULL;
    cout << "Seleccion una de las opciones" << endl;
    cout << "1. Agregar proceso" << endl;
    cout << "2. Mostrar procesos" << endl;
    cout << "3. Eliminar proceso" << endl;
    cout << "4. Salir" << endl;
}
void agregarProceso(){
    short cant, aux[3];
    cout << "Cuantos procesos desea agregar (max 3): ";
    cin >> cant;
    srand(time(0));
    for (int i = 0; i < cant; i++){
        aux[i] = rand() % 1000;
        if (i = 0){
            procesos[i].PID = aux[i];
        }
        else{
            for (int j = 0; j < i; j++){
                while (aux[i] == aux[j]){
                    aux[i] = rand() % 1000;
                }
            }
            procesos[i].PID = aux[i];
        }
        


        cout << "Ingrese el nombre del proceso padre: ";
        cin >> procesos[i].padre;
        cout << "Ingrese el tamano del proceso: ";
        cin >> procesos[i].tamano;
        cout << "Ingrese el estado del proceso (0-nuevo, 1-listo, 2-ejecucion, 3-bloqueado, 4-terminado): ";
        cin >> procesos[i].estado;
        cout << "Ingrese la prioridad del proceso (0-baja, 1-media, 2-alta): ";
        cin >> procesos[i].prioridad;
    }
}

int main(){
    menu();
    cin >> op;
    while (op < 1 || op > 4)
    {
        switch (op)
        {
        case 1:
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
            break;
        }
        cout << "Opcion no valida, intente de nuevo" << endl;
        system("pause");
        system("cls");
        menu();
        cin >> op;
    }
}