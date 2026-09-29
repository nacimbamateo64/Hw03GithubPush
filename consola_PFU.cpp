#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <windows.h>
#include <limits>

using namespace std;

bool validarNombreGeneral(const string &);
string aMayusculasGeneral(const string &);
bool esBisiesto(int);
bool validarFecha(int , int , int , int );
int calcularEdadFn(int , int , int, int , int , int );
int pedirEnteroValido(const string &);

string elegirPalabra();
void mostrarAhorcado(int );
void mostrarPalabraOculta(const string &, const vector<bool> &);
bool letraYaUsada(char letra, const vector<char> &usadas);
bool procesarLetra(char letra, const string &palabra, vector<bool> &);
char pedirLetraValida(const vector<char> &);
bool palabraCompleta(const vector<bool> &);
void guardarArchivoAhorcado(const string &, const string &, int , const vector<char> &, bool );
void jugarAhorcado(const string &);


void generarCarton(int [5][5]);
void imprimirCarton(int [5][5], bool [5][5], bool );
string comprobarGanador(bool [5][5]);
void guardarArchivoBingo(string , int , int , string , int [5][5], bool [5][5]);
void jugarBingo();


const int FILAS_TETRIS = 20;
const int COLS_TETRIS = 10;

struct PiezaTetris {
    int x, y;
    int tipo;
    char matriz[4][4];
    int size;
};

void asignarPieza(PiezaTetris &);
void rotarPieza(PiezaTetris &);
bool comprobarColision(PiezaTetris , int , int , char [FILAS_TETRIS][COLS_TETRIS]);
void fijarPieza(PiezaTetris , char [FILAS_TETRIS][COLS_TETRIS]);
void mostrarOcultarCursorTetris(bool );
void moverCursorInicioTetris();
void ejecutarModuloTetris(string );


const int filasSnake = 20;
const int columnasSnake = 20;
const int longitudMaxSnake = filasSnake * columnasSnake;

struct PuntoSnake {
    int fila;
    int columna;
};


char tableroSnake[filasSnake][columnasSnake];
PuntoSnake serpiente[longitudMaxSnake];
int longitudSerpiente;
PuntoSnake comidaSnake;
char direccionActualSnake;
int puntajeSnake;
int alimentosConsumidosSnake;
int siguienteBonusLongitud;
bool bonus15Otorgado;

void mostrarOcultarCursorSnake(bool );
void moverCursorInicioSnake();
void inicializarTableroSnake();
bool posicionOcupadaPorSerpiente(int , int );
void generarComidaSnake();
void inicializarSerpiente();
void dibujarTableroSnake(const string &);
void leerTeclaSnake();
bool moverSerpiente();
void guardarResultadosSnake(const string &, double);
void jugarSnake(const string &);

int pedirEnteroValido(const string &mensaje) {
    int numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero) {
            return numero;
        } else {
            cout << "[Error]: solo se permiten numeros.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    string nombreJugador;
    bool accesoPermitido = false;

    while (!accesoPermitido) {
        system("cls");
        cout << "===================================================\n";
        cout << "        CONSOLA DE VIDEOJUEGOS - MENU PRINCIPAL      \n";
        cout << "===================================================\n";
        cout << "Ingrese su nombre: ";
        getline(cin, nombreJugador);

        while (!validarNombreGeneral(nombreJugador)) {
            cout << "Nombre invalido. Solo se permiten letras y espacios.\n";
            cout << "Ingrese su nombre: ";
            getline(cin, nombreJugador);
        }
        nombreJugador = aMayusculasGeneral(nombreJugador);

        time_t t = time(0);
        tm *ahora = localtime(&t);
        int anioActual = ahora->tm_year + 1900;

        int dia = 0, mes = 0, anio = 0;
        bool fechaValida = false;

        while (!fechaValida) {
            cout << "\nIngrese su fecha de nacimiento.\n";
            dia = pedirEnteroValido("Dia: ");
            mes = pedirEnteroValido("Mes: ");
            anio = pedirEnteroValido("Anio: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (validarFecha(dia, mes, anio, anioActual)) {
                fechaValida = true;
            } else {
                cout << "Fecha invalida. Intente nuevamente.\n";
            }
        }

        int edad = calcularEdadFn(dia, mes, anio, ahora->tm_mday, ahora->tm_mon + 1, anioActual);

        if (edad < 18) {
            cout << "\nLo sentimos, " << nombreJugador << ". No cumples con la edad";
            cout << " minima (18 anios) para jugar. Edad calculada: " << edad << " anios.\n";
            cout << "El proceso se reiniciara.\n\n";
            system("pause");
        } else {
            accesoPermitido = true;
            cout << "\nBienvenido, " << nombreJugador << " (" << edad << " anios). Acceso concedido.\n";
            system("pause");
        }
    }

    char opcion;
    bool salir = false;

    while (!salir) {
        system("cls");
        cout << "===================================================\n";
        cout << "   MENU PRINCIPAL - Jugador: " << nombreJugador << "\n";
        cout << "===================================================\n";
        cout << "A - Jugar EL AHORCADO\n";
        cout << "B - Jugar BINGO\n";
        cout << "C - Jugar TETRIS\n";
        cout << "D - Jugar SNAKE\n";
        cout << "F - Salir de la consola\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        opcion = tolower(opcion);

        switch (opcion) {
            case 'a':
                jugarAhorcado(nombreJugador);
                break;
            case 'b':
                jugarBingo();
                break;
            case 'c':
                ejecutarModuloTetris(nombreJugador);
                break;
            case 'd':
                jugarSnake(nombreJugador);
                break;
            case 'f':
                cout << "\nGracias por jugar, " << nombreJugador << ". Hasta pronto.\n";
                salir = true;
                break;
            default:
                cout << "\nOpcion no valida. Intente nuevamente.\n";
                system("pause");
                break;
        }
    }

    return 0;
}

bool validarNombreGeneral(const string &nombre) {
    if (nombre.empty()) return false;
    for (size_t i = 0; i < nombre.length(); i++) {
        char c = nombre[i];
        if (!isalpha((unsigned char)c) && c != ' ') return false;
    }
    return true;
}

string aMayusculasGeneral(const string &texto) {
    string resultado = texto;
    for (size_t i = 0; i < resultado.length(); i++) {
        resultado[i] = toupper((unsigned char)resultado[i]);
    }
    return resultado;
}

bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

bool validarFecha(int dia, int mes, int anio, int anioActual) {
    if (anio < 1900 || anio > anioActual) return false;
    if (mes < 1 || mes > 12) return false;

    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (esBisiesto(anio)) diasPorMes[1] = 29;

    if (dia < 1 || dia > diasPorMes[mes - 1]) return false;

    return true;
}

int calcularEdadFn(int diaNac, int mesNac, int anioNac, int diaAct, int mesAct, int anioAct) {
    int edad = anioAct - anioNac;
    if (mesAct < mesNac || (mesAct == mesNac && diaAct < diaNac)) {
        edad--;
    }
    return edad;
}

string elegirPalabra() {
    vector<string> palabras;
    palabras.push_back("programacion");
    palabras.push_back("computadora");
    palabras.push_back("algoritmo");
    palabras.push_back("variable");
    palabras.push_back("funcion");
    palabras.push_back("compilador");
    palabras.push_back("teclado");
    palabras.push_back("software");
    palabras.push_back("arreglo");
    palabras.push_back("libreria");
    palabras.push_back("pelota");
    palabras.push_back("jugador");
    palabras.push_back("arquero");
    palabras.push_back("cancha");
    palabras.push_back("penal");

    int indice = rand() % palabras.size();
    return palabras[indice];
}

void mostrarAhorcado(int errores) {
    cout << endl;
    switch (errores) {
        case 0:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << "     |\n";
            cout << "     |\n";
            cout << "     |\n";
            cout << "=========\n";
            break;
        case 1:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "     |\n";
            cout << "     |\n";
            cout << "=========\n";
            break;
        case 2:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << " |   |\n";
            cout << "     |\n";
            cout << "=========\n";
            break;
        case 3:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "/|   |\n";
            cout << "     |\n";
            cout << "=========\n";
            break;
        case 4:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "/|\\  |\n";
            cout << "     |\n";
            cout << "=========\n";
            break;
        case 5:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "/|\\  |\n";
            cout << "/    |\n";
            cout << "=========\n";
            break;
        default:
            cout << " +---+\n";
            cout << " |   |\n";
            cout << " O   |\n";
            cout << "/|\\  |\n";
            cout << "/ \\  |\n";
            cout << "=========\n";
            break;
    }
    cout << endl;
}

void mostrarPalabraOculta(const string &palabra, const vector<bool> &acertadas) {
    cout << "Palabra: ";
    for (size_t i = 0; i < palabra.size(); i++) {
        if (acertadas[i]) {
            cout << palabra[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool letraYaUsada(char letra, const vector<char> &usadas) {
    for (size_t i = 0; i < usadas.size(); i++) {
        if (usadas[i] == letra) {
            return true;
        }
    }
    return false;
}

char pedirLetraValida(const vector<char> &usadas) {
    string entrada;
    while (true) {
        cout << "Ingrese una letra (o '0' para salir del juego): ";
        getline(cin, entrada);

        if (entrada.empty()) {
            continue;
        }

        char c = entrada[0];

        if (c == '0' || c == 27) {
            return '0';
        }

        c = tolower(c);

        if (!isalpha((unsigned char)c)) {
            cout << "Entrada invalida. Solo se permiten letras (A-Z).\n";
        } else if (letraYaUsada(c, usadas)) {
            cout << "Esa letra ya fue usada. Intente con otra.\n";
        } else {
            return c; 
        }
    }
}

bool procesarLetra(char letra, const string &palabra, vector<bool> &acertadas) {
    bool encontrada = false;
    for (size_t i = 0; i < palabra.size(); i++) {
        if (palabra[i] == letra) {
            acertadas[i] = true;
            encontrada = true;
        }
    }
    return encontrada;
}

bool palabraCompleta(const vector<bool> &acertadas) {
    for (size_t i = 0; i < acertadas.size(); i++) {
        if (!acertadas[i]) {
            return false;
        }
    }
    return true;
}

void guardarArchivoAhorcado(const string &nombreJugador, const string &palabra, int intentosRealizados, const vector<char> &usadas, bool gano) {
    string nombreArchivo = nombreJugador + "_AHORCADO.txt";
    ofstream archivo(nombreArchivo.c_str());

    if (archivo.is_open()) {
        archivo << "===== RESULTADOS AHORCADO =====\n";
        archivo << "Jugador: " << nombreJugador << "\n";
        archivo << "Juego: AHORCADO\n";
        archivo << "Palabra secreta: " << palabra << "\n";
        archivo << "Intentos realizados: " << intentosRealizados << "\n";

        archivo << "Letras acertadas: ";
        for (size_t i = 0; i < usadas.size(); i++) {
            bool estaEnPalabra = false;
            for (size_t j = 0; j < palabra.size(); j++) {
                if (palabra[j] == usadas[i]) estaEnPalabra = true;
            }
            if (estaEnPalabra) archivo << usadas[i] << " ";
        }
        archivo << "\n";

        archivo << "Letras incorrectas: ";
        for (size_t i = 0; i < usadas.size(); i++) {
            bool estaEnPalabra = false;
            for (size_t j = 0; j < palabra.size(); j++) {
                if (palabra[j] == usadas[i]) estaEnPalabra = true;
            }
            if (!estaEnPalabra) archivo << usadas[i] << " ";
        }
        archivo << "\n";

        archivo << "Resultado: " << (gano ? "GANO" : "PERDIO") << "\n";
        archivo.close();

        cout << "\nResultados guardados en \"" << nombreArchivo << "\"\n";
    } else {
        cout << "\n[ERROR]: No se pudo guardar el archivo de resultados de AHORCADO." << endl;
    }
}

void jugarAhorcado(const string &nombreJugador) {
    bool jugarDeNuevo = true;

    while (jugarDeNuevo) {
        system("cls");
        cout << "=========================================================\n";
        cout << "                BIENVENIDO A EL AHORCADO                 \n";
        cout << "=========================================================\n";
        cout << "Hola " << nombreJugador << ", adivina la palabra secreta.\n\n";
        cout << "REGLAS BASICAS:\n";
        cout << "1. Ingrese una letra y presione [ENTER] para probar.\n";
        cout << "2. Tienes un maximo de 6 errores permitidos.\n";
        cout << "3. Ingrese '0' y presione [ENTER] en cualquier momento para salir.\n\n";
        system("pause");

        string palabra = elegirPalabra();
        vector<bool> acertadas(palabra.size(), false);
        vector<char> letrasUsadas;
        int errores = 0;
        const int maxErrores = 6;
        bool abandono = false;

        while (errores < maxErrores && !palabraCompleta(acertadas)) {
            system("cls");
            cout << "================ EL AHORCADO ================\n";
            cout << "Jugador: " << nombreJugador << "\n";
            cout << "La palabra tiene " << palabra.size() << " letras.\n";

            mostrarAhorcado(errores);
            mostrarPalabraOculta(palabra, acertadas);
            cout << "\nIntentos restantes: " << (maxErrores - errores) << endl;

            cout << "Letras usadas: ";
            for (size_t i = 0; i < letrasUsadas.size(); i++) {
                cout << letrasUsadas[i] << " ";
            }
            cout << "\n\n";

            char letra = pedirLetraValida(letrasUsadas);
            if (letra == '0') {
                abandono = true;
                break;
            }

            letrasUsadas.push_back(letra);

            bool acerto = procesarLetra(letra, palabra, acertadas);
            if (!acerto) {
                errores++;
            }
        }

        system("cls");
        if (abandono) {
            cout << "Has abandonado la partida de AHORCADO.\n";
        } else {
            mostrarAhorcado(errores);
            bool gano = palabraCompleta(acertadas);
            if (gano) {
                cout << "Felicidades, ganaste! La palabra era: " << palabra << endl;
            } else {
                cout << "Perdiste. Alcanzaste el numero maximo de errores." << endl;
                cout << "La palabra era: " << palabra << endl;
            }
            guardarArchivoAhorcado(nombreJugador, palabra, static_cast<int>(letrasUsadas.size()), letrasUsadas, gano);
        }

        char respuesta;
        do {
            cout << "\nDeseas jugar otra partida de AHORCADO? (S: Si / N: No, volver al menu principal): ";
            cin >> respuesta;
            respuesta = toupper(respuesta);
            if (respuesta != 'S' && respuesta != 'N') {
                cout << "[ERROR]: Seleccion invalida. Intente de nuevo.\n";
            }
        } while (respuesta != 'S' && respuesta != 'N');

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        jugarDeNuevo = (respuesta == 'S');
    }
}

void generarCarton(int carton[5][5]) {
    int i, j, k, minVal, maxVal, num;
    bool repetido;
    for (j = 0; j < 5; j++) {
        minVal = j * 15 + 1;
        maxVal = minVal + 14;
        for (i = 0; i < 5; i++) {
            do {
                num = minVal + rand() % (maxVal - minVal + 1);
                repetido = false;
                for (k = 0; k < i; k++) if (carton[k][j] == num) repetido = true;
            } while (repetido);
            carton[i][j] = num;
        }
    }
}

void imprimirCarton(int carton[5][5], bool marcado[5][5], bool mostrarMarca) {
    cout << " B \t I \t N \t G \t O " << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (mostrarMarca && marcado[i][j]) {
                cout << "*\t";
            } else {
                cout << carton[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

string comprobarGanador(bool marcado[5][5]) {
    int i, j;
    bool g;
    for (i = 0; i < 5; i++) {
        g = true;
        for (j = 0; j < 5; j++) if (!marcado[i][j]) g = false;
        if (g) return "Fila completa";
    }
    for (j = 0; j < 5; j++) {
        g = true;
        for (i = 0; i < 5; i++) if (!marcado[i][j]) g = false;
        if (g) return "Columna completa";
    }
    g = true;
    for (i = 0; i < 5; i++) if (!marcado[i][i]) g = false;
    if (g) return "Diagonal principal";
    g = true;
    for (i = 0; i < 5; i++) if (!marcado[i][4 - i]) g = false;
    if (g) return "Diagonal secundaria";
    return "";
}

void guardarArchivoBingo(string nombreGanador, int numJugadores, int bolasSorteadas, string combinacion, int carton[5][5], bool marcado[5][5]) {
    ofstream archivo((nombreGanador + "_BINGO.txt").c_str());
    if (archivo.is_open()) {
        archivo << "===== RESULTADOS BINGO =====\n";
        archivo << "Ganador: " << nombreGanador << "\n";
        archivo << "Juego: BINGO\n";
        archivo << "Jugadores: " << numJugadores << "\n";
        archivo << "Bolas sorteadas: " << bolasSorteadas << "\n";
        archivo << "Combinacion ganadora: " << combinacion << "\n";
        archivo << "\nCarton ganador:\n";
        archivo << " B \t I \t N \t G \t O \n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (marcado[i][j]) {
                    archivo << "*\t";
                } else {
                    archivo << carton[i][j] << "\t";
                }
            }
            archivo << "\n";
        }
        archivo.close();
        cout << "\nResultados guardados en \"" << (nombreGanador + "_BINGO.txt") << "\"\n";
    } else {
        cout << "\n[ERROR]: No se pudo guardar el archivo de resultados de BINGO." << endl;
    }
}

void jugarBingo() {
    bool jugarDeNuevo = true;

    while (jugarDeNuevo) {
        system("cls");
        cout << "=========================================================\n";
        cout << "                    BIENVENIDO A BINGO                   \n";
        cout << "=========================================================\n";
        cout << "REGLAS:\n";
        cout << "1. Se generan cartones de 5x5 (B-I-N-G-O) y se sortean numeros del 1 al 75.\n";
        cout << "2. Gana quien complete primero una fila, columna o diagonal.\n";
        cout << "3. Presione 'F' durante el sorteo para salir al menu principal.\n\n";
        system("pause");

        system("cls");
        int numJugadores;
        string nombres[20];
        int cartones[20][5][5];
        bool marcados[20][5][5];
        int i, j, k, m;

        do {
            numJugadores = pedirEnteroValido("Ingrese el numero de jugadores (minimo 3, maximo 20): ");
        } while (numJugadores < 3 || numJugadores > 20);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (i = 0; i < numJugadores; i++) {
            cout << "Ingrese el nombre del jugador " << (i + 1) << ": ";
            getline(cin, nombres[i]);
            nombres[i] = aMayusculasGeneral(nombres[i]);
            for (j = 0; j < 5; j++) {
                for (k = 0; k < 5; k++) {
                    marcados[i][j][k] = false;
                }
            }
            generarCarton(cartones[i]);
        }

        system("cls");
        cout << "--- Cartones iniciales ---" << endl;
        for (i = 0; i < numJugadores; i++) {
            cout << "\nCarton de " << nombres[i] << ":" << endl;
            imprimirCarton(cartones[i], marcados[i], false);
        }

        bool bolaSorteada[76];
        for (m = 0; m < 76; m++) bolaSorteada[m] = false;

        bool juegoTerminado = false;
        bool abandono = false;
        int contadorBolas = 0;
        string combinacionGanadora = "";
        int indiceGanador = -1;

      
        cout << "\nPresione [ENTER] para comenzar el sorteo...";
        string esperaInicio;
        getline(cin, esperaInicio);

        while (!juegoTerminado && contadorBolas < 75) {
            system("cls");
            int bola;
            do {
                bola = 1 + rand() % 75;
            } while (bolaSorteada[bola]);

            bolaSorteada[bola] = true;
            contadorBolas++;

            cout << ">>> BOLA SORTEADA: " << bola << " <<<" << endl;

            for (i = 0; i < numJugadores; i++) {
                for (j = 0; j < 5; j++) {
                    for (k = 0; k < 5; k++) {
                        if (cartones[i][j][k] == bola) marcados[i][j][k] = true;
                    }
                }
                cout << "\nCarton de " << nombres[i] << ":" << endl;
                imprimirCarton(cartones[i], marcados[i], true);

                combinacionGanadora = comprobarGanador(marcados[i]);
                if (combinacionGanadora != "") {
                    juegoTerminado = true;
                    indiceGanador = i;
                    break;
                }
            }
            if (!juegoTerminado) {
                cout << "\nPresione [ENTER] para la siguiente bola (o presione 'F' + ENTER para salir): ";
                string entrada;
                getline(cin, entrada);
                if (!entrada.empty() && (entrada[0] == 'f' || entrada[0] == 'F')) {
                    abandono = true;
                    break;
                }
            }
        }

        if (abandono) {
            cout << "\nHas abandonado el juego de BINGO.\n";
        } else if (juegoTerminado) {
            cout << "\nBINGO! Felicidades, has ganado \"" << nombres[indiceGanador] << "\" por: " << combinacionGanadora << endl;
            guardarArchivoBingo(nombres[indiceGanador], numJugadores, contadorBolas, combinacionGanadora, cartones[indiceGanador], marcados[indiceGanador]);
        } else {
            cout << "\nLa partida ha terminado sin ganador. Se agotaron los numeros disponibles." << endl;
        }

        char respuesta;
        do {
            cout << "\nDesea jugar nuevamente BINGO? (S: Si / N: No, volver al menu principal): ";
            cin >> respuesta;
            respuesta = toupper(respuesta);
            if (respuesta != 'S' && respuesta != 'N') {
                cout << "[ERROR]: Seleccion invalida. Intente de nuevo.\n";
            }
        } while (respuesta != 'S' && respuesta != 'N');

       
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        jugarDeNuevo = (respuesta == 'S');
    }
}

void mostrarOcultarCursorTetris(bool visible) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible ? TRUE : FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void moverCursorInicioTetris() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);
}

void asignarPieza(PiezaTetris &p) {
    p.tipo = rand() % 7;
    p.y = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            p.matriz[i][j] = ' ';
        }
    }

    switch (p.tipo) {
        case 0:
            p.size = 2;
            p.matriz[0][0] = '#'; p.matriz[0][1] = '#';
            p.matriz[1][0] = '#'; p.matriz[1][1] = '#';
            break;
        case 1:
            p.size = 4;
            p.matriz[1][0] = '#'; p.matriz[1][1] = '#'; p.matriz[1][2] = '#'; p.matriz[1][3] = '#';
            break;
        case 2:
            p.size = 3;
            p.matriz[0][1] = '#';
            p.matriz[1][0] = '#'; p.matriz[1][1] = '#'; p.matriz[1][2] = '#';
            break;
        case 3:
            p.size = 3;
            p.matriz[0][2] = '#';
            p.matriz[1][0] = '#'; p.matriz[1][1] = '#'; p.matriz[1][2] = '#';
            break;
        case 4:
            p.size = 3;
            p.matriz[0][0] = '#';
            p.matriz[1][0] = '#'; p.matriz[1][1] = '#'; p.matriz[1][2] = '#';
            break;
        case 5:
            p.size = 3;
            p.matriz[0][1] = '#'; p.matriz[0][2] = '#';
            p.matriz[1][0] = '#'; p.matriz[1][1] = '#';
            break;
        case 6:
            p.size = 3;
            p.matriz[0][0] = '#'; p.matriz[0][1] = '#';
            p.matriz[1][1] = '#'; p.matriz[1][2] = '#';
            break;
    }
    p.x = (COLS_TETRIS / 2) - (p.size / 2);
}

void rotarPieza(PiezaTetris &p) {
    PiezaTetris temporal = p;
    for (int i = 0; i < p.size; i++) {
        for (int j = 0; j < p.size; j++) {
            p.matriz[j][p.size - 1 - i] = temporal.matriz[i][j];
        }
    }
}

bool comprobarColision(PiezaTetris p, int nx, int ny, char tablero[FILAS_TETRIS][COLS_TETRIS]) {
    for (int i = 0; i < p.size; i++) {
        for (int j = 0; j < p.size; j++) {
            if (p.matriz[i][j] != ' ') {
                int tx = nx + j;
                int ty = ny + i;

                if (tx < 0 || tx >= COLS_TETRIS || ty >= FILAS_TETRIS) return true;
                if (ty >= 0 && tablero[ty][tx] != ' ') return true;
            }
        }
    }
    return false;
}

void fijarPieza(PiezaTetris p, char tablero[FILAS_TETRIS][COLS_TETRIS]) {
    for (int i = 0; i < p.size; i++) {
        for (int j = 0; j < p.size; j++) {
            if (p.matriz[i][j] != ' ' && p.y + i >= 0) {
                tablero[p.y + i][p.x + j] = p.matriz[i][j];
            }
        }
    }
}

void ejecutarModuloTetris(string nombreJugador) {
    bool quiereJugarDeNuevo = true;

    while (quiereJugarDeNuevo) {
        system("cls");
        cout << "=========================================================" << endl;
        cout << "                    BIENVENIDO A TETRIS                  " << endl;
        cout << "=========================================================" << endl;
        cout << "Hola " << nombreJugador << ", preparate para jugar.\n\n";
        cout << "REGLAS BASICAS:\n";
        cout << "1. Alinea bloques para completar filas enteras y eliminarlas.\n";
        cout << "2. El juego termina si los bloques llegan al tope superior.\n\n";
        cout << "CONTROLES:\n";
        cout << "  W / w -> Rotar pieza\n";
        cout << "  A / a -> Mover a la izquierda\n";
        cout << "  D / d -> Mover a la derecha\n";
        cout << "  S / s -> Caida rapida (Bajar)\n";
        cout << "  F / f -> Forzar salida guardando progreso\n\n";
        system("pause");

        system("cls");
        mostrarOcultarCursorTetris(false);

        char tableroTetris[FILAS_TETRIS][COLS_TETRIS];
        for (int i = 0; i < FILAS_TETRIS; i++) {
            for (int j = 0; j < COLS_TETRIS; j++) {
                tableroTetris[i][j] = ' ';
            }
        }

        int puntaje = 0;
        int filasEliminadas = 0;
        int piezasUsadas = 0;
        bool juegoActivo = true;

        time_t tiempoInicio = time(0);

        PiezaTetris actual;
        asignarPieza(actual);
        piezasUsadas++;

        while (juegoActivo) {
            moverCursorInicioTetris();

            int nivelActual = (filasEliminadas / 4) + 1;

            stringstream frame;
            frame << " JUGADOR: " << nombreJugador << " | NIVEL: " << nivelActual << "\n";
            frame << " PUNTOS: " << puntaje << " | FILAS: " << filasEliminadas << " | F: Salir\n";
            frame << "---------------------------------------------------------\n";

            for (int i = 0; i < FILAS_TETRIS; i++) {
                frame << "#";
                for (int j = 0; j < COLS_TETRIS; j++) {
                    bool partePieza = false;

                    if (i >= actual.y && i < actual.y + actual.size && j >= actual.x && j < actual.x + actual.size) {
                        if (actual.matriz[i - actual.y][j - actual.x] != ' ') {
                            partePieza = true;
                        }
                    }

                    if (partePieza || tableroTetris[i][j] != ' ') {
                        frame << "[]";
                    } else {
                        frame << "  ";
                    }
                }
                frame << "#\n";
            }

            for (int j = 0; j < (COLS_TETRIS * 2) + 2; j++) {
                frame << "#";
            }
            frame << "\n";

            cout << frame.str();

            if (_kbhit()) {
                char t = tolower(_getch());

                if (t == 'a' && !comprobarColision(actual, actual.x - 1, actual.y, tableroTetris)) actual.x--;
                if (t == 'd' && !comprobarColision(actual, actual.x + 1, actual.y, tableroTetris)) actual.x++;
                if (t == 's' && !comprobarColision(actual, actual.x, actual.y + 1, tableroTetris)) actual.y++;

                if (t == 'w') {
                    PiezaTetris rotada = actual;
                    rotarPieza(rotada);
                    if (!comprobarColision(rotada, rotada.x, rotada.y, tableroTetris)) {
                        actual = rotada;
                    }
                }

                if (t == 'f') {
                    juegoActivo = false;
                    break;
                }
            }

            if (!comprobarColision(actual, actual.x, actual.y + 1, tableroTetris)) {
                actual.y++;
            } else {
                fijarPieza(actual, tableroTetris);

                int filasSimultaneas = 0;
                for (int i = FILAS_TETRIS - 1; i >= 0; i--) {
                    bool llena = true;
                    for (int j = 0; j < COLS_TETRIS; j++) {
                        if (tableroTetris[i][j] == ' ') llena = false;
                    }

                    if (llena) {
                        filasSimultaneas++;
                        filasEliminadas++;

                        for (int k = i; k > 0; k--) {
                            for (int j = 0; j < COLS_TETRIS; j++) {
                                tableroTetris[k][j] = tableroTetris[k - 1][j];
                            }
                        }
                        i++;
                    }
                }

                if (filasSimultaneas == 1) puntaje += 100;
                if (filasSimultaneas == 2) puntaje += 300;
                if (filasSimultaneas == 3) puntaje += 500;
                if (filasSimultaneas == 4) puntaje += 800;

                asignarPieza(actual);
                piezasUsadas++;

                if (comprobarColision(actual, actual.x, actual.y, tableroTetris)) {
                    juegoActivo = false;
                }
            }

            Sleep(180);
        }

      
        mostrarOcultarCursorTetris(true);

        time_t tiempoFin = time(0);
        int tiempoTotalSegundos = (int)difftime(tiempoFin, tiempoInicio);

        system("cls");
        cout << "==============================================" << endl;
        cout << "         FIN DEL JUEGO: GAME OVER             " << endl;
        cout << "==============================================" << endl;
        cout << "Jugador: " << nombreJugador << endl;
        cout << "Puntaje Definitivo: " << puntaje << " puntos." << endl;
        cout << "Filas Eliminadas: " << filasEliminadas << endl;
        cout << "Tiempo de juego: " << tiempoTotalSegundos << " segundos." << endl;

        string fileC = nombreJugador + "_TETRIS.txt";
        ofstream outC(fileC.c_str());
        if (outC.is_open()) {
            outC << "Nombre del jugador: " << nombreJugador << endl;
            outC << "Nombre del juego: Tetris" << endl;
            outC << "Puntaje obtenido: " << puntaje << endl;
            outC << "Cantidad de filas eliminadas: " << filasEliminadas << endl;
            outC << "Nivel alcanzado: " << (filasEliminadas / 4) + 1 << endl;
            outC << "Numero de piezas utilizadas: " << piezasUsadas << endl;
            outC << "Tiempo de juego: " << tiempoTotalSegundos << " segundos" << endl;
            outC.close();
            cout << "\n[SISTEMA]: Resultados de partida guardados en \"" << fileC << "\"" << endl;
        } else {
            cout << "\n[ERROR]: No se pudo escribir el archivo de reporte estadistico." << endl;
        }

        char respuesta;
        do {
            cout << "\nDeseas jugar otra partida de TETRIS? (S: Si / N: No, volver al menu principal): ";
            cin >> respuesta;
            respuesta = toupper(respuesta);
            if (respuesta != 'S' && respuesta != 'N') {
                cout << "[ERROR]: Seleccion invalida. Intente de nuevo.\n";
            }
        } while (respuesta != 'S' && respuesta != 'N');

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (respuesta == 'N') {
            quiereJugarDeNuevo = false;
        }
    }
}

void mostrarOcultarCursorSnake(bool visible) {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;

    cursor.dwSize = 1;
    cursor.bVisible = visible ? TRUE : FALSE;

    SetConsoleCursorInfo(hConsola, &cursor);
}

void moverCursorInicioSnake() {
    COORD posicion;
    posicion.X = 0;
    posicion.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicion);
}

void inicializarTableroSnake() {
    for (int f = 0; f < filasSnake; f++)
        for (int c = 0; c < columnasSnake; c++)
            tableroSnake[f][c] = '.';
}

bool posicionOcupadaPorSerpiente(int f, int c) {
    for (int i = 0; i < longitudSerpiente; i++)
        if (serpiente[i].fila == f && serpiente[i].columna == c) return true;
    return false;
}

void generarComidaSnake() {
    int f, c;
    do {
        f = rand() % filasSnake;
        c = rand() % columnasSnake;
    } while (posicionOcupadaPorSerpiente(f, c));
    comidaSnake.fila = f;
    comidaSnake.columna = c;
}

void inicializarSerpiente() {
    longitudSerpiente = 3;
    int filaInicial = filasSnake / 2;
    int colInicial = columnasSnake / 2;

    serpiente[0].fila = filaInicial;
    serpiente[0].columna = colInicial;

    serpiente[1].fila = filaInicial;
    serpiente[1].columna = colInicial - 1;

    serpiente[2].fila = filaInicial;
    serpiente[2].columna = colInicial - 2;

    direccionActualSnake = 'D';
    puntajeSnake = 0;
    alimentosConsumidosSnake = 0;
    siguienteBonusLongitud = 5;
    bonus15Otorgado = false;
}

void dibujarTableroSnake(const string &nombreJugador) {
    moverCursorInicioSnake();
    inicializarTableroSnake();

    for (int i = 0; i < longitudSerpiente; i++)
        tableroSnake[serpiente[i].fila][serpiente[i].columna] = 'O';
    tableroSnake[comidaSnake.fila][comidaSnake.columna] = '*';

    stringstream frame;
    frame << "==================== SNAKE ====================\n";
    frame << "Jugador: " << nombreJugador << "   Puntaje: " << puntajeSnake << "\n";
    frame << "Longitud actual: " << longitudSerpiente << "\n\n";

    for (int f = 0; f < filasSnake; f++) {
        for (int c = 0; c < columnasSnake; c++)
            frame << tableroSnake[f][c] << ' ';
        frame << '\n';
    }
    frame << "\nControles: Flechas = mover   |   F = salir          \n";

    cout << frame.str();
}

void leerTeclaSnake() {
    if (_kbhit()) {
        int tecla = _getch();
        char nuevaDireccion = direccionActualSnake;

        if (tecla == 224) {
            int flecha = _getch();
            switch (flecha) {
                case 72: nuevaDireccion = 'W'; break; 
                case 80: nuevaDireccion = 'S'; break; 
                case 75: nuevaDireccion = 'A'; break; 
                case 77: nuevaDireccion = 'D'; break; 
            }
        } else {
            char t = toupper((char)tecla);
            if (t == 'F') nuevaDireccion = 'F';
        }
        bool opuestas = (direccionActualSnake == 'W' && nuevaDireccion == 'S') ||
                         (direccionActualSnake == 'S' && nuevaDireccion == 'W') ||
                         (direccionActualSnake == 'A' && nuevaDireccion == 'D') ||
                         (direccionActualSnake == 'D' && nuevaDireccion == 'A');

        if (!opuestas) direccionActualSnake = nuevaDireccion;
    }
}

bool moverSerpiente() {
    if (direccionActualSnake == 'F') return false;

    PuntoSnake nuevaCabeza = serpiente[0];
    switch (direccionActualSnake) {
        case 'W': nuevaCabeza.fila--;    break;
        case 'S': nuevaCabeza.fila++;    break;
        case 'A': nuevaCabeza.columna--; break;
        case 'D': nuevaCabeza.columna++; break;
    }

    if (nuevaCabeza.fila < 0 || nuevaCabeza.fila >= filasSnake ||
        nuevaCabeza.columna < 0 || nuevaCabeza.columna >= columnasSnake) {
        return false;
    }

    if (posicionOcupadaPorSerpiente(nuevaCabeza.fila, nuevaCabeza.columna)) {
        return false;
    }

    bool comioAlimento = (nuevaCabeza.fila == comidaSnake.fila &&
                           nuevaCabeza.columna == comidaSnake.columna);
    int limite = comioAlimento ? longitudSerpiente : longitudSerpiente - 1;
    for (int i = limite; i > 0; i--)
        serpiente[i] = serpiente[i - 1];
    serpiente[0] = nuevaCabeza;

    if (comioAlimento) {
        longitudSerpiente++;
        alimentosConsumidosSnake++;
        puntajeSnake += 10;

        if (longitudSerpiente >= siguienteBonusLongitud) {
            puntajeSnake += 25;
            siguienteBonusLongitud += 5;
        }
        if (longitudSerpiente >= 15 && !bonus15Otorgado) {
            puntajeSnake += 50;
            bonus15Otorgado = true;
        }

        generarComidaSnake();
    }

    return true;
}

void guardarResultadosSnake(const string &nombreJugador, double segundosJugados) {
    string nombreArchivo = nombreJugador + "_SNAKE.txt";

    ofstream archivo;
    archivo.open(nombreArchivo.c_str());

    if (archivo.is_open()) {
        archivo << "===== RESULTADOS SNAKE =====\n";
        archivo << "Jugador: " << nombreJugador << "\n";
        archivo << "Juego: SNAKE\n";
        archivo << "Puntaje final: " << puntajeSnake << "\n";
        archivo << "Longitud maxima alcanzada: " << longitudSerpiente << "\n";
        archivo << "Alimentos consumidos: " << alimentosConsumidosSnake << "\n";
        archivo << "Tiempo de juego (segundos): " << segundosJugados << "\n";

        archivo.close();

        cout << "\nResultados guardados en \"" << nombreArchivo << "\"\n";
    } else {
        cout << "\n[ERROR]: No se pudo guardar el archivo de resultados de SNAKE." << endl;
    }
}

void jugarSnake(const string &nombreJugador) {
    bool jugarDeNuevo = true;

    while (jugarDeNuevo) {
        system("cls");
        cout << "=========================================================\n";
        cout << "                    BIENVENIDO A SNAKE                   \n";
        cout << "=========================================================\n";
        cout << "Hola " << nombreJugador << ", esquiva los bordes y come la fruta.\n\n";
        cout << "REGLAS BASICAS:\n";
        cout << "1. Usa las flechas para moverte y comer la comida (*).\n";
        cout << "2. Cada fruta aumenta tu longitud y tu puntaje.\n";
        cout << "3. No choques con los bordes del mapa ni contigo mismo.\n\n";
        cout << "CONTROLES:\n";
        cout << "  Flechas Direccionales -> Mover serpiente\n";
        cout << "  F / f                 -> Salir del juego\n\n";
        system("pause");

        system("cls");
        mostrarOcultarCursorSnake(false);
        inicializarSerpiente();
        generarComidaSnake();
        time_t inicio = time(NULL);

        bool continuar = true;
        while (continuar) {
            dibujarTableroSnake(nombreJugador);
            leerTeclaSnake();
            continuar = moverSerpiente();
            Sleep(150);
        }

        mostrarOcultarCursorSnake(true);

        time_t fin = time(NULL);
        double segundos = difftime(fin, inicio);

        system("cls");
        cout << "\n================ FIN DEL JUEGO ================\n";
        cout << "Jugador: " << nombreJugador << "\n";
        cout << "Puntaje final: " << puntajeSnake << "\n";
        cout << "Longitud final de la serpiente: " << longitudSerpiente << "\n";
        cout << "Alimentos consumidos: " << alimentosConsumidosSnake << "\n";
        cout << "Tiempo jugado: " << segundos << " segundos\n";

        guardarResultadosSnake(nombreJugador, segundos);

        char respuesta;
        do {
            cout << "\nDeseas jugar otra partida de SNAKE? (S: Si / N: No, volver al menu principal): ";
            cin >> respuesta;
            respuesta = toupper(respuesta);
            if (respuesta != 'S' && respuesta != 'N') {
                cout << "[ERROR]: Seleccion invalida. Intente de nuevo.\n";
            }
        } while (respuesta != 'S' && respuesta != 'N');

     
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        jugarDeNuevo = (respuesta == 'S');
    }
}