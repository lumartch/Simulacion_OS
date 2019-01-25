#include "interfaz.h"

Interfaz::Interfaz() {
    tiempoTotal = 0;
    tiempoTranscurrido = 0;
    tiempoRestante = 0;
    loteActual = 0;
    lotesPendientes = 0;
    cantLotes = 0;
    menuInicio();
    }

Interfaz::~Interfaz() {
    //dtor
    }

void Interfaz::menuInicio() {
    string cadena;
    do{
        system(CLEAR);
        cout << "Ingrese la cantidad de lotes a procesar: ";
        getline(cin, cadena);
        if(!checkNumero(cadena)){ break; }
        cout << endl << endl << "Ha introducido un número o carácter inválido. Intente de nuevo.";
        pausa();
    }while(true);

    system(CLEAR);
    procesamientoLotes();
    contador();
    proceso();
    pausaProceso();

    }

void Interfaz::procesamientoLotes() {
    cout << "+-----------------------+-------+----------+---------+" << endl;
    cout << "| No. Lotes Pendientes  |       | Contador |         |" << endl;
    cout << "+-------------+---------+-------+----------+---------+" << endl;
    cout << "| Lote actual |         | "<< endl;
    cout << "+-------------+---------+--------+-----------------------------------------------+---------------------------------------------------------------------------------------------+" << endl;
    cout << "|       Nombre          | Tiempo |                Proceso                        |                                             Terminados                                      |" << endl;
    cout << "+-----------------------+--------+-----------------+-----------------------------+------+----------------------------------------------------------+---------------------------+" << endl;
    cout << "                                 | Nombre          |                             | ID   |        Operación                                         |          Resultado        |" << endl;
    cout << "                                 | Operación       |                             +------+----------------------------------------------------------+---------------------------+ "<< endl;
    cout << "                                 | Tiempo          |                             | " << endl;
    cout << "                                 | T. Transcurrido |                             | " << endl;
    cout << "                                 | T. Restante     |                             | " << endl;
    cout << "                                 |-----------------+-----------------------------+ " << endl;
    }

void Interfaz::proceso() {
    //Limpia tabla de procesos
    limpiarTablaProceso();
    /* Lotes pendientes y lote actual*/
    printf("\033[%d;%dH%d", 2, 27, lotesPendientes);
    printf("\033[%d;%dH%d", 4, 17, loteActual);
    /* Proceso */
    // Medir nombre no mayor a 21
    printf("\033[%d;%dH%s", 8, 3, "Idelfonso Castellanos");
    printf("\033[%d;%dH%s", 8, 1, "|");
    printf("\033[%d;%dH%s", 8, 25, "|");
    printf("\033[%d;%dH%s", 9, 1, "+-----------------------+--------|");
    //Segunda parte del nombre
    printf("\033[%d;%dH%s", 8, 53, "Idelfonso Castellanos");
    printf("\033[%d;%dH%s", 9, 53, "9,223,372,036,854,775,807*1");
    /* Calculos e impresión del tiempo de forma "real" */
    printf("\033[%d;%dH%s", 10, 53, "9,223,372,036,854,775,807*1");
    printf("\033[%d;%dH%s", 11, 53, "9,223,372,036,854,775,807*1");
    printf("\033[%d;%dH%s", 12, 53, "9,223,372,036,854,775,807*1");
    /* Terminados */
    printf("\033[%d;%dH%s", 10, 84, "ID");
    printf("\033[%d;%dH%s", 10, 91, "9,223,372,036,854,775,807*1");
    printf("\033[%d;%dH%s", 10, 150,"9,223,372,036,854,775,807");
    printf("\033[%d;%dH%s", 10, 82, "|");
    printf("\033[%d;%dH%s", 10, 89, "|");
    printf("\033[%d;%dH%s", 10, 176, "|");
    printf("\033[%d;%dH%s", 11, 82, "|------+----------------------------------------------------------+---------------------------|");

    }

void Interfaz::contador() {
    printf("\033[%d;%dH%d", 2, 46, tiempoTotal);
    }

void Interfaz::limpiarTablaProceso() {
    for(int i = 9; i < 13; i++){
        printf("\033[%d;%dH%s", i, 53, "                           ");
    }
}

void Interfaz::pausaProceso(){
    if(loteActual >= (loteActual+13)){
        printf("\033[%d;%dH", loteActual+13, 1);
    }
    else{
        printf("\033[%d;%dH", 13, 1);
    }
    cout << endl << endl << "Presione [enter] para continuar...";
    cin.get();
    }

void Interfaz::pausa(){
    cout << endl << endl << "Presione [enter] para continuar...";
    cin.get();
    }

bool Interfaz::checkNumero(const string& cadena) {
    regex rx("[0-9]*");
    if(!regex_match(cadena, rx)){
        return true;
    }
    return false;
    }


