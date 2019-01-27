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
    do{
        system(CLEAR);
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "|                       Simulación del OS                         |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Ingrese la cantidad de lotes a procesar:                        |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "\033[4;44H";
        getline(cin, cadena);
        if(!checkNumero(cadena)){ break; }
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        pausa();
    }while(true);
    procesoTotal = atoi(cadena.c_str());
    system(CLEAR);
    procesamientoLotes();
    while(procesoTotal > 0){
        procesoActual++;
        procesoTotal--;
        agregarTabulacion();
        sleep(1);
    }
    pausaProceso();
    }


void Interfaz::procesamientoLotes() {
    cout << "+-----------------------+-------+----------+---------+" << endl;
    cout << "| No. Lotes Pendientes  |       | Contador |         |" << endl;
    cout << "+-------------+---------+-------+----------+---------+" << endl;
    cout << "| Lote actual |         | "<< endl;
    cout << "+-------------+---------+----+--------+-----------------------------------------------+---------------------------------------------------------------------------------------------+" << endl;
    cout << "|       Nombre               | Tiempo |                Proceso                        |                                             Terminados                                      |" << endl;
    cout << "+----------------------------+--------+-----------------+-----------------------------+------+----------------------------------------------------------+---------------------------+" << endl;
    cout << "                                      | Nombre          |                             | ID   |        Operación                                         |          Resultado        |" << endl;
    cout << "                                      | Operación       |                             +------+----------------------------------------------------------+---------------------------+ "<< endl;
    cout << "                                      | Tiempo          |                             | " << endl;
    cout << "                                      | T. Transcurrido |                             | " << endl;
    cout << "                                      | T. Restante     |                             | " << endl;
    cout << "                                      +-----------------+-----------------------------+ " << endl;
    }

void Interfaz::agregarTabulacion() {
    /* Procesados */
    cout << "\033[" << 7 + procesoActual << ";1H                                      " << endl;
    cout << "\033[" << 7 + procesoActual << ";1H|                            |"<< endl;
    /* Terminados */
    cout << "\033[" << 9 + procesoActual << ";88H                                                                                             " << endl;
    cout << "\033[" << 9 + procesoActual << ";88H      |                                                          |                           |" << endl;
    if(procesoTotal == 0){
        cout << "\033[" << 8 + procesoActual << ";1H+----------------------------+--------+" << endl;
        cout << "\033[" << 10 + procesoActual << ";87H+------+----------------------------------------------------------+---------------------------+" << endl;
    }
    else{
        /* Procesados */
        if(procesoActual == 5){
            cout << "\033[" << 8 + procesoActual << ";1H+----------------------------+--------" << endl;
        }
        else{
            cout << "\033[" << 8 + procesoActual << ";1H+----------------------------+--------|" << endl;
        }
        /* Terminados */
        if(procesoActual == 3){
            cout << "\033[" << 10 + procesoActual << ";88H------+----------------------------------------------------------+---------------------------+" << endl;
        }
        else{
            cout << "\033[" << 10 + procesoActual << ";87H|------+----------------------------------------------------------+---------------------------|" << endl;
        }
    }
}

void Interfaz::limpiarTablaProceso() {
    for(int i = 9; i < 13; i++){
        cout << "\033[" << i + 8 << ";44H";
    }
}

void Interfaz::pausaProceso(){
    if(procesoActual > 4){
        cout << "\033[" << 10 + procesoActual << ";1H" << endl;
    }
    else{
        cout << "\033[13;1H" << endl << endl;
    }
    cout << "Presione [enter] para continuar...";
    cin.get();
    }

void Interfaz::pausa(){
    cout << endl << endl << "Presione [enter] para continuar...";
    cin.get();
    }

bool Interfaz::checkNumero(const string& cadena) {
    regex rx("[0-9]+");
    if(!regex_match(cadena, rx)){
        return true;
    }
    return false;
    }


