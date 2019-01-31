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
        cout << "|      Simulación de un OS                                        |" << endl;
        cout << "+-------------------------------+--------------+------------------+" << endl;
        cout << "| Ingrese la cantidad de procesos a crear:                        |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "\033[4;44H";
        getline(cin, cadena);
        if(checkNumInt(cadena)) {
            break;
        }
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        pausa();
    } while(true);
    procesoTotal = atoi(cadena.c_str());
    capturarProceso();
    system(CLEAR);
    procesamientoLotes();
    while(!cola.empty()) {
        cout << "\033[2;50H" << ++tiempoTotal << endl;
        cout << "\033[2;27H" << cola.size() - 1 << endl;
        cout << "\033[4;17H" << ++loteActual << endl;
        Lote l = cola.front();
        cola.pop();
        limpiarTabulacionLote();
        for(int i = 0; i < 3; i++) {
            if(l[i].getId() != -1111) {
                agregarTabulacionLote(l[i], i);
            }
        }
        for(int i = 0; i < 3; i++) {
            if(l[i].getId() != -1111) {
                procesoActual++;
                procesoTotal--;
                limpiarTablaProceso();
                sleep(1);
                agregarTabulacionTerminado(i);
                procesarDatos(l[i]);
                quitarProceso(i);
                cout << "\033[2;50H" << ++tiempoTotal << endl;
            }
        }
        sleep(1);
    }
    pausaProceso();
}

void Interfaz::capturarProceso() {
    string str = "", operador;
    Lote auxLote;
    int con = 0;
    for(int i = 0; i < procesoTotal; i++) {
        Proceso auxProceso;
        system(CLEAR);
        cout << "+-------------------------------+--------------+------------------+" << endl;
        cout << "|  Registro de proceso:                                           |" << endl;
        cout << "+-------------------------------+--------------+------------------+" << endl;
        cout << "| Nombre del programador:                                         |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Operador (+,-,/,*,%):                                           |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Primer número:                  Segundo número:                 |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Tiempo máximo estimado(Mayor a 0):                              |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| ID de programa:                                                 |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "\033[2;25H" << i + 1;
        // Nombre
        cout << "\033[4;27H";
        getline(cin, str);
        auxProceso.setProgramador(str);
        // Operador
        do {
            cout << "\033[6;25H";
            getline(cin, str);
            if(!checkOperador(str)) {
                break;
            }
            cout << "\033[14;1H";
            cout << "| Ha introducido operador o cáracter inválido. Intente de nuevo.  |" << endl;
            cout << "+-----------------------------------------------------------------+" << endl;
            pausaProceso();
            cout << "\033[6;25H                          ";
            cout << "\033[14;1H                                                                   " << endl;
            cout << "\033[15;1H                                                                   " << endl;
        } while(true);
        operador = str;
        auxProceso.setOperador(str);
        // Primero número
        do {
            cout << "\033[8;18H";
            getline(cin, str);
            if(!checkNumero(str)) {
                break;
            }
            cout << "\033[14;1H";
            cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
            cout << "+-----------------------------------------------------------------+" << endl;
            pausaProceso();
            cout << "\033[8;18H                 ";
            cout << "\033[14;1H                                                                   " << endl;
            cout << "\033[15;1H                                                                   " << endl;
        } while(true);
        auxProceso.setN1(atof(str.c_str()));
        if(operador == "/" or operador == "%") {
            // Segundo número
            do {
                cout << "\033[8;51H";
                getline(cin, str);
                if(!checkNumero(str)) {
                    if(atof(str.c_str()) != 0) {
                        break;
                    } else {
                        cout << "\033[14;1H";
                        cout << "| El segundo número debe ser distinto de cero. Intente de nuevo.  |" << endl;
                        cout << "+-----------------------------------------------------------------+" << endl;
                    }
                } else {
                    cout << "\033[14;1H";
                    cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
                    cout << "+-----------------------------------------------------------------+" << endl;
                }
                pausaProceso();
                cout << "\033[8;51H                ";
                cout << "\033[14;1H                                                                   " << endl;
                cout << "\033[15;1H                                                                   " << endl;
            } while(true);
            auxProceso.setN2(atof(str.c_str()));
        } else {
            // Segundo número
            do {
                cout << "\033[8;51H";
                getline(cin, str);
                if(!checkNumero(str)) {
                    break;
                }
                cout << "\033[14;1H";
                cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
                cout << "+-----------------------------------------------------------------+" << endl;
                pausaProceso();
                cout << "\033[8;51H                ";
                cout << "\033[14;1H                                                                   " << endl;
                cout << "\033[15;1H                                                                   " << endl;
            } while(true);
            auxProceso.setN2(atof(str.c_str()));
        }
        // Tiempo máxmo estimado
        do {
            cout << "\033[10;38H";
            getline(cin, str);
            if(!checkNumero(str)) {
                if(atoi(str.c_str()) >= 1) {
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
        } while(true);
        auxProceso.setTiempoEstimado(atoi(str.c_str()));
        // ID del programa
        do {
            cout << "\033[12;19H";
            getline(cin, str);
            if(checkNumInt(str)) {
                if(!checkId(str)){
                    break;
                }
            }
            cout << "\033[14;1H";
            cout << "| El ID ingresado ya existe o caracter inválido Intente de nuevo. |" << endl;
            cout << "+-----------------------------------------------------------------+" << endl;
            pausaProceso();
            cout << "\033[12;19H                                               ";
            cout << "\033[14;1H                                                                   " << endl;
            cout << "\033[15;1H                                                                   " << endl;
        } while(true);
        auxProceso.setId(atoi(str.c_str()));
        listId.push_back(atoi(str.c_str()));
        auxLote.setProceso(auxProceso, con++);
        if(con == 3) {
            con = 0;
            cola.push(auxLote);
            Lote l;
            auxLote = l;
        }
    }
    if(con != 3 and con != 0) {
        cola.push(auxLote);
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

void Interfaz::agregarTabulacionTerminado(int &cant) {
    /* Terminados */
    cout << "\033[" << 8 + procesoActual + loteActual << ";88H                                                                                             " << endl;
    cout << "\033[" << 8 + procesoActual + loteActual << ";87H|      |                                                          |                           |" << endl;
    if(cola.size() == 0 or (cant + 1 ) == 3) {
        cout << "\033[" << 9 + procesoActual + loteActual << ";87H+------+----------------------------------------------------------+---------------------------+" << endl;
    } else {
        /* Terminados */
        if(procesoActual == 3) {
            cout << "\033[" << 9 + procesoActual + loteActual << ";87H+------+----------------------------------------------------------+---------------------------|" << endl;
        } else {
            cout << "\033[" << 9 + procesoActual + loteActual << ";87H|------+----------------------------------------------------------+---------------------------|" << endl;
        }
    }
}

void Interfaz::agregarTabulacionLote(Proceso& p, int &cant) {
    /* Procesados */
    cout << "\033[" << 8 + cant << ";2H                                      " << endl;
    cout << "\033[" << 8 + cant << ";1H|                            |        |"<< endl;
    cout << "\033[" << 9 + cant << ";1H+----------------------------+--------+"<< endl;
    /* Primer tabla "Nombres" */
    cout << "\033[" << 8 + cant << ";3H" << p.getProgramador() << endl;
    cout << "\033[" << 8 + cant << ";32H" << p.getTiempoEstimado() << endl;
}

void Interfaz::limpiarTabulacionLote() {
    for(int i = 0; i < 4; i++){
        cout << "\033[" << 8 + i << ";1H                                      "<< endl;
    }
}

void Interfaz::quitarProceso(int& pos) {
    cout << "\033[" << 8 + pos << ";2H                                     " << endl;
}


void Interfaz::procesarDatos(Proceso& p) {
    tiempoRestante = p.getTiempoEstimado();
    tiempoTranscurrido = 0;

    /* Segunda Tabla "Procesos" */
    cout << "\033[" << 8 << ";59H" << p.getProgramador() << endl;
    cout << "\033[" << 9 << ";59H" << p.getOperacion() << endl;
    cout << "\033[" << 10 << ";59H" << p.getId() << endl;
    cout << "\033[" << 11 << ";59H" << tiempoTranscurrido << endl;
    cout << "\033[" << 12 << ";59H" << tiempoRestante << endl;
    /* Impresión del tiempo transcurrido, tiempo total e incremento del tiempo total */
    //tiempoTotal--;
    while(tiempoRestante >= 0) {
        cout << "\033[2;50H" << ++tiempoTotal << endl;
        cout << "\033[" << 11 << ";59H" << tiempoTranscurrido++ << endl;
        cout << "\033[" << 12 << ";59H" << tiempoRestante-- << endl;
        sleep(1);
    }
    /* Tercer Tabla "Terminados" */
    //cout << "\033[2;50H" << ++tiempoTotal << endl;
    cout << "\033[" << 8 + procesoActual + loteActual << ";89H" << p.getId() << endl;
    cout << "\033[" << 8 + procesoActual + loteActual << ";96H" << p.getOperacion() << endl;
    float resultado = 0;
    if(p.getOperador() == "+") {
        resultado = p.getN1() + p.getN2();
    } else if(p.getOperador() == "-") {
        resultado = p.getN1() - p.getN2();
    } else if(p.getOperador() == "*") {
        resultado = p.getN1() * p.getN2();
    } else if(p.getOperador() == "/") {
        resultado = p.getN1() / p.getN2();
    } else {
        resultado = int(p.getN1()) % int(p.getN2());
    }
    cout << "\033[" << 8 + procesoActual + loteActual << ";155H" << resultado << endl;
}

void Interfaz::tiempoEjecucionTotal() {
    while(procesoTotal != 0){
        cout << "\033[2;50H" << ++tiempoTotal << endl;
        sleep(1);
    }
}


void Interfaz::limpiarTablaProceso() {
    for(int i = 0; i < 5; i++) {
        cout << "\033[" << i + 8 << ";58H                           " << endl;
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
    regex rx("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?");
    if(!regex_match(cadena, rx)) {
        return true;
    }
    return false;
}

bool Interfaz::checkOperador(const string& cadena) {
    regex rx("[+|\\-|*|/|%]");
    if(!regex_match(cadena, rx)) {
        return true;
    }
    return false;
}

bool Interfaz::checkNumInt(const string& cadena) {
    regex rx("[0-9]+");
    if(regex_match(cadena, rx)) {
        return true;
    }
    return false;
}


bool Interfaz::checkId(const string& cadena) {
    std::list<int>::iterator it = std::find(listId.begin(), listId.end(), atoi(cadena.c_str()));
    if(it != listId.end()){
        return true;
    }
    return false;
}

