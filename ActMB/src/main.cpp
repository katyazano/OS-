#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double cantidad;
    int opcion;
    double mb = 0.0;
    int arquitectura;
    double fragmentacion;

    cout << "--- Simulador de Gestion de Memoria y Procesos ---" << endl;

    cout << "Ingrese la cantidad del proceso: ";
    cin >> cantidad;
    cout << "Seleccione la unidad original (1: KB, 2: MB, 3: GB): ";
    cin >> opcion;

    if (opcion == 1) {
        mb = cantidad / 1024.0;
    } else if (opcion == 3) {
        mb = cantidad * 1024.0;
    } else {
        mb = cantidad;
    }

    cout << fixed << setprecision(4);
    cout << "\n-> Tamano del proceso: " << mb << " MB" << endl;

    cout << "\nIngrese la arquitectura del procesador (ej. 32 o 64 bits): ";
    cin >> arquitectura;

    // AQUI CALCULAMOS LA VELOCIDAD EN MB/s
    // Nota: Puse un multiplicador de ejemplo (arquitectura * 1.5). 
    // Cambia el "1.5" por la constante o formula exacta de tu proyecto.
    double velocidad_mb_s = arquitectura * 1.5; 
    
    cout << "-> VELOCIDAD FINAL DEL PROCESADOR: " << velocidad_mb_s << " MB/s" << endl;

    double tiempo_segundos = mb / velocidad_mb_s;
    cout << "-> TIEMPO CALCULADO DE EJECUCION: " << tiempo_segundos << " segundos" << endl;

    cout << "\nIngrese el porcentaje de fragmentacion de la memoria (0-100): ";
    cin >> fragmentacion;

    double memoria_perdida = mb * (fragmentacion / 100.0);
    cout << "-> Memoria desperdiciada por fragmentacion: " << memoria_perdida << " MB" << endl;

    return 0;
}