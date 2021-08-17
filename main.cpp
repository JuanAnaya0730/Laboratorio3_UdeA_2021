#include "funciones.h"

/*"../Aplicacion_AnayaReginoJuanSebastian/prueba.txt"*/
using namespace std;

int main()
{
    int opcion;

    menuCajero();
    cin >> opcion;

    system("CLS");
    switch (opcion) {
    case 1:
        mostrarSaldo();
        break;

    case 2:
        retirarSaldo();
        break;

    case 3:
        if(verificarContrasena()){
            menuOperador();
            cin >> opcion;
            switch(opcion){
            case 1:
                nuevoUsuario();
                break;
            case 2:
                return 0;
            default:
                cout << "Opcion invalida" << endl;
            }
        }
        else{
            cout << "Demaciados intentos" << endl;
        }

        break;
    case 4:
        return  0;

    default:
        cout << "Opcion invalida." << endl;
    }

    return 0;
}
