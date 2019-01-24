#include "interfaz.h"

Interfaz::Interfaz() {
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
    procesamientoLotes();
    proceso();

    pausa();
    }

void Interfaz::procesamientoLotes() {
    cout << "+-----------------------+-------+----------+---------+" << endl;
    cout << "| No. Lotes Pendientes  |       | Contador |---------|" << endl;
    cout << "+-------------+---------+-------+----------+---------+" << endl;
    cout << "| Lote actual |         | "<< endl;
    cout << "+-------------+---------+--------+-----------------------------------------------+---------------------------------------------------------------+" << endl;
    cout << "|       Nombre          | Tiempo |                Proceso                        |                            Terminados                         |" << endl;
    cout << "+-----------------------+--------+-----------------+-----------------------------+------+----------------------------+---------------------------+" << endl;
    cout << "| Idelfonso Castellanos |        | Nombre          | Idelfonso Castellanos       | ID   |       Operación            |          Resultado        |" << endl;
    cout << "+--------------------------------| Operación       | 9,223,372,036,854,775,807*1 +------+----------------------------+---------------------------+" << endl;
    cout << "                                 | Tiempo          |-----------------------------|------|9,223,372,036,854,775,807*1 | 9,223,372,036,854,775,807 |" << endl;
    cout << "                                 | T. Transcurrido |-----------------------------+------+----------------------------+---------------------------+" << endl;
    cout << "                                 | T. Restante     |-----------------------------|" << endl;
    cout << "                                 +-----------------+-----------------------------+" << endl;
    }

void Interfaz::proceso() {

    }

void Interfaz::contador() {
    printf("\033[%d;%dH%s\n", 3, 3, "Hola mundo");
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


