#include "interfaz.h"

Interfaz::Interfaz() {
    procesoActual = 0;
    procesoTotal = 0;
    loteActual = 0;
    lotesPendientes = 0;
    tiempoTotal = 0;
    tiempoTranscurrido = 0;
    tiempoRestante = 0;
    menuInicio();
}

Interfaz::~Interfaz() {
    //dtor
}

void Interfaz::menuInicio() {
    string cadena;
    do {
        system(CLEAR);
        cout << "+-------------------------------+--------------+------------------+" << endl;
        cout << "|      Simulación de un OS      | Tiempo Total | 0                |" << endl;
        cout << "+-------------------------------+--------------+------------------+" << endl;
        cout << "| Ingrese la cantidad de procesos a crear:                        |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "\033[4;44H";
        getline(cin, cadena);
        if(!checkNumero(cadena)) { break; }
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        pausa();
    } while(true);
    procesoTotal = atoi(cadena.c_str());
    capturarProceso();

    lotesPendientes = 1 + ((procesoTotal-1)/3.0);
    system(CLEAR);
    procesamientoLotes();
    while(procesoTotal > 0) {
        if(procesoActual%3 == 0) {
            if(lotesPendientes == 0) {
                lotesPendientes++;
            }
            lotesPendientes--;
            loteActual++;
            cout << "\033[2;27H" << lotesPendientes << endl;
            cout << "\033[4;17H" << loteActual << endl;
        }
        procesoActual++;
        procesoTotal--;
        agregarTabulacion();
        procesarDatos();
        sleep(1);
    }
    pausaProceso();
}

void Interfaz::capturarProceso() {
    string str = "";
    for(int i = 0; i < procesoTotal; i++) {
        system(CLEAR);
        cout << "+-------------------------------+--------------+------------------+" << endl;
        cout << "|      Registro de proceso      | Tiempo Total | 0                |" << endl;
        cout << "+-------------------------------+--------------+------------------+" << endl;
        cout << "| Nombre del programador:                                         |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Primer número:                  Segundo número:                 |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Operador (+,-,/,*,%):                                           |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Tiempo máximo estimado(Mayor a 0):                              |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| ID de programa:                                                 |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        // Nombre
        cout << "\033[4;27H";
        getline(cin, str);
        // Primero número
        do{
            cout << "\033[6;18H";
            getline(cin, str);
            if(!checkNumero(str)) { break; }
            cout << "\033[14;1H";
            cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
            cout << "+-----------------------------------------------------------------+" << endl;
            pausaProceso();
            cout << "\033[6;18H                 ";
            cout << "\033[14;1H                                                                   " << endl;
            cout << "\033[15;1H                                                                   " << endl;
        }while(true);
        // Segundo número
        do{
            cout << "\033[6;51H";
            getline(cin, str);
            if(!checkNumero(str)) { break; }
            cout << "\033[14;1H";
            cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
            cout << "+-----------------------------------------------------------------+" << endl;
            pausaProceso();
            cout << "\033[6;51H                ";
            cout << "\033[14;1H                                                                   " << endl;
            cout << "\033[15;1H                                                                   " << endl;
        }while(true);
        // Operador
        do{
            cout << "\033[8;25H";
            getline(cin, str);
            if(!checkOperador(str)) { break; }
            cout << "\033[14;1H";
            cout << "| Ha introducido operador o cáracter inválido. Intente de nuevo.  |" << endl;
            cout << "+-----------------------------------------------------------------+" << endl;
            pausaProceso();
            cout << "\033[8;25H     ";
            cout << "\033[14;1H                                                                   " << endl;
            cout << "\033[15;1H                                                                   " << endl;
        }while(true);
        // Tiempo máxmo estimado
        do{
            cout << "\033[10;38H";
            getline(cin, str);
            if(!checkNumero(str)) {
                if(atoi(str.c_str()) >= 1){
                    break;
                }
            }
            cout << "\033[14;1H";
            cout << "| El tiempo tiene que representarse con números enteros positivos.|" << endl;
            cout << "+-----------------------------------------------------------------+" << endl;
            pausaProceso();
            cout << "\033[10;38H                           ";
            cout << "\033[14;1H                                                                   " << endl;
            cout << "\033[15;1H                                                                   " << endl;
        }while(true);
        // ID del programa
        do{
            cout << "\033[12;19H";
            getline(cin, str);
            if(!checkId(str)) { break; }
            cout << "\033[14;1H";
            cout << "| El ID ingresao ya existe, ingrese uno nuevo.                    |" << endl;
            cout << "+-----------------------------------------------------------------+" << endl;
            pausaProceso();
            cout << "\033[12;19H                                                 ";
            cout << "\033[14;1H                                                                   " << endl;
            cout << "\033[15;1H                                                                   " << endl;
        }while(true);

    }
}

void Interfaz::procesamientoLotes() {
    cout << "+-----------------------+-------+--------------+---------+" << endl;
    cout << "| No. Lotes Pendientes  |       | Tiempo Total | 0       |" << endl;
    cout << "+-------------+---------+-------+--------------+---------+" << endl;
    cout << "| Lote actual |         | "<< endl;
    cout << "+-------------+---------+----+--------+-----------------------------------------------+---------------------------------------------------------------------------------------------+" << endl;
    cout << "|       Nombre               | Tiempo |                Proceso                        |                                             Terminados                                      |" << endl;
    cout << "+----------------------------+--------+-----------------+-----------------------------+------+----------------------------------------------------------+---------------------------+" << endl;
    cout << "                                      | Nombre          |                             | ID   |        Operación                                         |          Resultado        |" << endl;
    cout << "                                      | Operación       |                             +------+----------------------------------------------------------+---------------------------+ "<< endl;
    cout << "                                      | ID Programa     |                             | " << endl;
    cout << "                                      | T. Transcurrido |                             | " << endl;
    cout << "                                      | T. Restante     |                             | " << endl;
    cout << "                                      +-----------------+-----------------------------+ " << endl;
}

void Interfaz::agregarTabulacion() {
    /* Procesados */
    cout << "\033[" << 6 + procesoActual + loteActual << ";2H                                      " << endl;
    cout << "\033[" << 6 + procesoActual + loteActual << ";1H|                            |        |"<< endl;
    /* Terminados */
    cout << "\033[" << 8 + procesoActual + loteActual << ";88H                                                                                             " << endl;
    cout << "\033[" << 8 + procesoActual + loteActual << ";87H|      |                                                          |                           |" << endl;
    if(procesoTotal == 0 or procesoActual%3 == 0) {
        cout << "\033[" << 7 + procesoActual + loteActual << ";1H+----------------------------+--------+" << endl;
        cout << "\033[" << 9 + procesoActual + loteActual << ";87H+------+----------------------------------------------------------+---------------------------+" << endl;
    } else {
        /* Procesados */
        if(procesoActual == 5) {
            cout << "\033[13;39H"<< "+" << endl;
            cout << "\033[" << 7 + procesoActual + loteActual << ";1H|----------------------------+--------+" << endl;
        } else {
            cout << "\033[" << 7 + procesoActual + loteActual << ";1H+----------------------------+--------|" << endl;
        }
        /* Terminados */
        if(procesoActual == 3) {
            cout << "\033[" << 9 + procesoActual + loteActual << ";87H+------+----------------------------------------------------------+---------------------------|" << endl;
        } else {
            cout << "\033[" << 9 + procesoActual + loteActual << ";87H|------+----------------------------------------------------------+---------------------------|" << endl;
        }
    }
}

void Interfaz::procesarDatos() {
    // Desencolar
    limpiarTablaProceso();
    tiempoRestante = 3;
    tiempoTranscurrido = 0;
    /* Primer tabla "Nombres" */
    cout << "\033[" << 6 + procesoActual + loteActual << ";3H" << "Hola mundo" << endl;
    cout << "\033[" << 6 + procesoActual + loteActual << ";32H" << "TM" << endl;
    /* Segunda Tabla "Procesos" */
    cout << "\033[" << 8 << ";59H" << "Hola mundo" << endl;
    cout << "\033[" << 9 << ";59H" << "2+2" << endl;
    cout << "\033[" << 10 << ";59H" << "3" << endl;
    cout << "\033[" << 11 << ";59H" << tiempoTranscurrido << endl;
    cout << "\033[" << 12 << ";59H" << tiempoRestante << endl;
    /* Impresión del tiempo transcurrido, tiempo total e incremento del tiempo total */
    //tiempoTotal--;
    while(tiempoRestante >= 0) {
        //cout << "\033[2;50H" << ++tiempoTotal << endl;
        cout << "\033[" << 11 << ";59H" << tiempoTranscurrido++ << endl;
        cout << "\033[" << 12 << ";59H" << tiempoRestante-- << endl;
        sleep(1);
    }
    /* Tercer Tabla "Terminados" */
    cout << "\033[" << 8 + procesoActual + loteActual << ";89H" << "IDE" << endl;
    cout << "\033[" << 8 + procesoActual + loteActual << ";96H" << "2+2" << endl;
    cout << "\033[" << 8 + procesoActual + loteActual << ";155H" << "4" << endl;
}

void Interfaz::tiempoEjecucionTotal() {

}


void Interfaz::limpiarTablaProceso() {
    for(int i = 9; i < 13; i++) {
        cout << "\033[" << i + 7 << ";58H                           " << endl;
    }
}

void Interfaz::pausaProceso() {
    if(procesoActual > 4) {
        cout << "\033[" << 10 + procesoActual + loteActual << ";1H" << endl;
    } else {
        cout << "\033[15;1H" << endl << endl;
    }
    cout << "Presione [enter] para continuar...";
    cin.get();
    cout << "\033[15;1H" << endl << endl;
    cout << "                                   ";
}

void Interfaz::pausa() {
    cout << endl << endl << "Presione [enter] para continuar...";
    cin.get();
}

bool Interfaz::checkNumero(const string& cadena) {
    regex rx("[0-9]+");
    if(!regex_match(cadena, rx)) {
        return true;
    }
    return false;
}

bool Interfaz::checkOperador(const string& cadena) {
    regex rx("[+|-|*|/|%]");
    if(!regex_match(cadena, rx)) {
        return true;
    }
    return false;
}


bool Interfaz::checkId(const string& cadena) {
    return false;
}

