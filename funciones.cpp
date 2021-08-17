#include "funciones.h"

string Cabin(string texto){
/*
    Esta funcion recibe una cadena string y retorna su equivalente en binario.
*/
    string bin, textobinario;
    unsigned num;

    for(unsigned long i=0; i<texto.length(); ++i){
        num=texto[i];
        for(int h=0; h<8; ++h){
            bin+=(num%2)+48;
            num/=2;
        }
        bin=reverse(bin);
        textobinario+=bin;
        bin="";
    }

    return textobinario;
}

string Binca(string textobinario){
    string bin, textocaracteres;
    int dec;

    for(unsigned long i=0; i<textobinario.length(); i+=8){
        dec=0;
        bin=textobinario.substr(i,8);
        bin=reverse(bin);
        for(int h=0; h<8; ++h){
            dec+=(int(bin[h])-48)*pow(2,h);
        }
        textocaracteres+=char(dec);
    }

    return textocaracteres;
}

string Codificar1(string textobinario, int semilla){
/*
    Esta funcion recibe un texto en binario y una semilla, toma bloques de bits dependiendo
    de la semilla y restorna el texto que fue ingresado ya codificado.
*/
    string bloque, codificado="";
    long unos=0, ceros=0;

    for(unsigned long i=0; i<textobinario.length(); i+=semilla){
        bloque=textobinario.substr(i,semilla);

        if(unos==ceros){
            codificado+=Invertir(bloque,1);
        }
        else if(ceros>unos){
            codificado+=Invertir(bloque,2);
        }
        else{
            codificado+=Invertir(bloque,3);
        }

        unos=Contar1y0(bloque,'1');
        ceros=Contar1y0(bloque,'0');

    }

    return codificado;
}

string Decodificar1(string codificado, int semilla){
/*
    Esta funcion recibe un texto binario codificado y una semilla, luego se encarga de decodificar
    el texto binario separandolo en bloque del tamaña de semilla.
*/
    string bloque, decodificado="";
    long unos=0, ceros=0;

    for(unsigned long i=0; i<codificado.length(); i+=semilla){
        bloque=codificado.substr(i,semilla);

        if(unos==ceros){
            decodificado+=Invertir(bloque,1);
        }
        else if(ceros>unos){
            decodificado+=Invertir(bloque,2);
        }
        else{
            decodificado+=Invertir(bloque,3);
        }

        unos=Contar1y0(decodificado.substr(i,semilla),'1');
        ceros=Contar1y0(decodificado.substr(i,semilla),'0');

    }

    return decodificado;
}

string Invertir(string binario, int num){
/*
    Esta funcion recibe un texto binario y un numero, el numero indica
    el tipo de codificacion que se le hara al texto binario.
*/
    for(unsigned long i=1; i<=binario.length(); ++i){
        if(i%num==0){
            if(binario[i-1]=='0')
                binario[i-1]='1';
            else
                binario[i-1]='0';
        }
    }

    return binario;
}

long Contar1y0(string binario, char numero){
    long contador=0;
    for(unsigned long i=0; i<binario.length(); ++i){
        if(binario[i]==numero)
            contador++;
    }

    return contador;
}

string Leer(string nombre, int tipo){
/*
    Esta funcion recibe el nombre de un archivo, lo lee y posteriormente
    retorna una cadena string con todo lo que esta en el archivo.
*/
    ifstream archivo;
    string texto, aux;

    archivo.open(nombre);
    if (archivo.is_open()){
        while (!archivo.eof()) {
            getline(archivo,aux);
            if(tipo==1)
                texto+=aux+'\n';
            else
                texto+=aux;
        }
        archivo.close();
    }
    else{
        cout << "Error al abrir el archivo." << endl;
        exit(1);
    }

    return texto;
}

void Escribir(string nombre, string texto, int tipo){
/*
    Esta funcion recibe un nombre y un texto para luego guardar
    el texto en un archivo con el nombre se le paso a la funcion.
*/
    ofstream archivo;

    if(tipo == 1){
        archivo.open(nombre, ios::trunc);
    }
    else{
        archivo.open(nombre, ios::app);
    }
    if(!archivo.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    archivo << texto;

    archivo.close();
}

string reverse(string cadena){
/*
    Esta funcion recibe una cadena string y la retorna invertida.
*/
    string auxcadena;

    for(long long i=cadena.length()-1; i>=0; --i){
        auxcadena+=cadena[i];
    }

    return  auxcadena;
}

void menuCajero()
{
    cout << "~~~~~~~~~~ CAJERO AUTOMATICO ~~~~~~~~~~" << endl
         << "1. Consultar saldo." << endl
         << "2. Retirar dinero." << endl
         << "3. Usuario operador." << endl
         << "4. Cancelar." << endl
         << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << "Opcion: ";
}

void menuOperador()
{
    cout << "~~~~~~~~~~~~ MENU OPERADOR ~~~~~~~~~~~~" << endl
         << "1. Nuevo/Sobrescribir usuario" << endl
         << "2. Cancelar" << endl
         << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << "Opcion: ";
}

bool verificarContrasena()
{
    string contrasena;
    int errores = 0;

    do{
        cout << "Contrasena: ";
        cin >> contrasena;
        system("CLS");

        if(contrasena == Binca(Decodificar1(Leer("sudo.txt", 2), 4))){
            return true;
        }
        cout << "Contrasena incorrecta. Intente de nuevo." << endl;
        errores++;
    }while (errores < 3);

    system("CLS");

    return false;
}

void nuevoUsuario()
{
    string usuario[3];
    string datos[3]={"Cedula","Clave","Saldo"};

    for(int i=0; i<3; ++i){
        system("CLS");
        cout << datos[i] << ": ";
        cin >> usuario[i];
        while(!isNum(usuario[i])){
            system("CLS");
            cout << "Solo se admiten numeros." << endl
                 << datos[i] << ": ";
            cin >> usuario[i];
        }
    }
    Escribir("data.txt", Codificar1(Cabin(usuario[0]+","+usuario[1]+","+usuario[2]+"\n"), 4), 2);
}

bool isNum(string cadena)
{
    for(int i=0; i<int(cadena.size()); ++i){
        if(!(cadena[i]>= 48 && cadena[i] <=57)){
            return false;
        }
    }
    return true;
}

string buscarDatos(string __cedula__)
{
    int contador = 0;
    string datos[100][3] = {}, aux, aux1 = Binca(Decodificar1(Leer("data.txt",2),4));
    for(int j=0; aux1.size()>0; ++j){
        aux = aux1.substr(0,aux1.find("\n"));
        for(int i=0; i<3;++i){
            datos[j][i] = aux.substr(0,aux.find(","));
            aux = aux.substr(aux.find(",")+1, aux.size());
        }
        aux1 = aux1.substr(aux1.find("\n")+1, aux1.size());
        contador++;
    }

    for(int i=0; i<contador; ++i){
        if(datos[i][0] == __cedula__){
            return datos[i][1]+ "," + datos[i][2];
        }
    }
    return  "-1";
}

void mostrarSaldo()
{
    string cedula, contrasena, aux;

    cout << "Cedula:";
    cin >> cedula;

    aux = buscarDatos(cedula);

    system("CLS");
    if(!(aux == "-1")){
        cout << "Contrasena: ";
        cin >> contrasena;
        system("CLS");
        if(contrasena == aux.substr(0, aux.find(","))){
            if(atoi(aux.substr(aux.find(",")+1,aux.size()).c_str()) <0 ){
                cout << "Saldo insuficiente para realizar esta accion. " << endl;
            }
            else{
                cout << "Saldo: " << aux.substr(aux.find(",")+1,aux.size()) << endl;
                restarSaldo(cedula, 1000);
            }
        }

    }else{
        cout << "la cedula ingresada no se encuentra registrada" << endl;
    }
}

void restarSaldo(string __cedula__, int __cantidad__)
{
    int contador = 0;
    string datos[100][3] = {}, aux, aux1 = Binca(Decodificar1(Leer("data.txt",2),4));
    for(int j=0; aux1.size()>0; ++j){
        aux = aux1.substr(0,aux1.find("\n"));
        for(int i=0; i<3;++i){
            datos[j][i] = aux.substr(0,aux.find(","));
            aux = aux.substr(aux.find(",")+1, aux.size());
        }
        aux1 = aux1.substr(aux1.find("\n")+1, aux1.size());
        contador++;
    }

    for(int i=0; i<contador; ++i){
        if(datos[i][0] == __cedula__){
            datos[i][2] = to_string(atoi((datos[i][2]).c_str())-__cantidad__);
        }
    }

    string datosAux = "";
    for(int i=0; i<contador; ++i){
        datosAux += datos[i][0] + "," + datos[i][1] + "," + datos[i][2] + "\n";
    }
    Escribir("data.txt", Codificar1(Cabin(datosAux),4), 1);
}

void retirarSaldo()
{
    string cedula, contrasena, aux;
    int cantidad;

    cout << "Cedula:";
    cin >> cedula;

    aux = buscarDatos(cedula);
    system("CLS");
    if(!(aux == "-1")){
        cout << "Contrasena: ";
        cin >> contrasena;
        system("CLS");
        cout << "Ingrese la cantidad a retirar: ";
        cin >> cantidad;
        system("CLS");
        if(contrasena == aux.substr(0, aux.find(","))){
            if(atoi(aux.substr(aux.find(",")+1,aux.size()).c_str()) < cantidad ){
                cout << "Saldo insuficiente para realizar esta accion. " << endl;
            }
            else{
                cout << "Saldo restante: " << atoi(aux.substr(aux.find(",")+1,aux.size()).c_str())-cantidad << endl;
                restarSaldo(cedula, cantidad);
                restarSaldo(cedula, 1000);
            }
        }

    }else{
        cout << "la cedula ingresada no se encuentra registrada" << endl;
    }
}
