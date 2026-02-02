#include <iostream>
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

void menu(){
    int op = NULL;
    cout << "Seleccion una de las opciones" << endl;
    cout << "1. Agregar proceso" << endl;
    cout << "2. Mostrar procesos" << endl;
    cout << "3. Eliminar proceso" << endl;
    cout << "4. Salir" << endl;
}

int main(){
    menu();
    cin >> op;
    while (op < 1 || op > 4)
    {
        cout << "Opcion no valida, intente de nuevo" << endl;
        menu();
        cin >> op;
    }
    
    system("cls");

    
}