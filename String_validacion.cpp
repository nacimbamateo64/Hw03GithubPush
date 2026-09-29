#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;


bool esValido(string );
string leerEnteroValido();
void mostrarMensajeError();
void mostrarResultado(int);

int main() { 

    string valor = leerEnteroValido();

    int numero = atoi(valor.c_str());

    mostrarResultado(numero);

    return 0;
}

string leerEnteroValido() {
    string entrada;
    
    cout << "Introduzca un numero entero: ";
    getline(cin, entrada);

    while (!esValido(entrada)) {
        mostrarMensajeError(); 
        getline(cin, entrada); 
    }

    return entrada;
}


bool esValido(string str) {
    bool valido = true;

    if (str.length() == 0) {
        valido = false;
    }
    int inicio = 0;

    if (valido && (str.at(0) == '-' || str.at(0) == '+')) {
        inicio = 1;
        if (str.length() == 1) { 
            valido = false;
        }
    }

    int i = inicio;
    while (valido && i < str.length()) {
        if (!isdigit(str.at(i))) {
            valido = false;
        }
        i++;
    }

    return valido;
}


void mostrarMensajeError() {
    cout << "El numero no es valido, ingrese un numero entero: ";
}


void mostrarResultado(int num) {
    cout << "\nEl numero entero que introdujo es: " << num << endl;
}