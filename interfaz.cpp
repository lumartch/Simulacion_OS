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
    system(CLEAR);
    procesamientoLotes();
    while(!cola.empty()) {
        cout << "\033[2;27H" << cola.size() - 1 << endl;
        cout << "\033[4;17H" << ++loteActual << endl;
        Lote l = cola.front();
        cola.pop();
        for(int i = 0; i < 3; i++){
            if(l[i].getId() != -1111){
                procesoActual++;
                procesoTotal--;
                limpiarTablaProceso();
                sleep(1);
                agregarTabulacion(i);
                procesarDatos(l[i]);
            }
        }
        sleep(1);
    }
    pausaProceso();
}

void Interfaz::capturarProceso() {
    string str = "", operacion;
    Lote auxLote;
    int con = 0;
    for(int i = 0; i < procesoTotal; i++) {
        Proceso auxProceso;
        system(CLEAR);
        cout << "+-------------------------------+--------------+------------------+" << endl;
        cout << "|  Registro de proceso:         | Tiempo Total | 0                |" << endl;
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
        cout << "\033[2;25H" << i + 1;
        // Nombre
        cout << "\033[4;27H";
        getline(cin, str);
        auxProceso.setProgramador(str);
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
        auxProceso.setN1(atoi(str.c_str()));
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
        auxProceso.setN2(atoi(str.c_str()));
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
        auxProceso.setOperador(str);
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
        auxProceso.setTiempoEstimado(atoi(str.c_str()));
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
        auxProceso.setId(atoi(str.c_str()));
        auxLote.setProceso(auxProceso, con++);
        if(con == 3){
            con = 0;
            cola.push(auxLote);
            Lote l;
            auxLote = l;
        }
    }
    if(con != 3 and con != 0){
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

void Interfaz::agregarTabulacion(int &cant) {
    /* Procesados */
    cout << "\033[" << 6 + procesoActual + loteActual << ";2H                                      " << endl;
    cout << "\033[" << 6 + procesoActual + loteActual << ";1H|                            |        |"<< endl;
    /* Terminados */
    cout << "\033[" << 8 + procesoActual + loteActual << ";88H                                                                                             " << endl;
    cout << "\033[" << 8 + procesoActual + loteActual << ";87H|      |                                                          |                           |" << endl;
    if(cola.size() == 0 or (cant + 1 ) == 3) {
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

void Interfaz::procesarDatos(Proceso& p) {
    tiempoRestante = p.getTiempoEstimado();
    tiempoTranscurrido = 0;
    /* Primer tabla "Nombres" */
    cout << "\033[" << 6 + procesoActual + loteActual << ";3H" << p.getProgramador() << endl;
    cout << "\033[" << 6 + procesoActual + loteActual << ";32H" << p.getTiempoEstimado() << endl;
    /* Segunda Tabla "Procesos" */
    cout << "\033[" << 8 << ";59H" << p.getProgramador() << endl;
    cout << "\033[" << 9 << ";59H" << p.getOperacion() << endl;
    cout << "\033[" << 10 << ";59H" << p.getId() << endl;
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
    cout << "\033[" << 8 + procesoActual + loteActual << ";89H" << p.getId() << endl;
    cout << "\033[" << 8 + procesoActual + loteActual << ";96H" << p.getOperacion() << endl;
    int resultado = 0;
    if(p.getOperador() == "+"){
        resultado = p.getN1() + p.getN2();
    }
    else if(p.getOperador() == "-"){
        resultado = p.getN1() - p.getN2();
    }
    else if(p.getOperador() == "*"){
        resultado = p.getN1() * p.getN2();
    }
    else if(p.getOperador() == "/"){
        resultado = p.getN1() / p.getN2();
    }
    else{
        resultado = p.getN1() % p.getN2();
    }
    cout << "\033[" << 8 + procesoActual + loteActual << ";155H" << resultado << endl;
}

void Interfaz::tiempoEjecucionTotal() {

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
    if(!checkNumero(cadena)){
        return false;
    }
    queue <Lote> aux = cola;
    for(unsigned int i = 0; i < aux.size(); i++){
        Lote l = aux.front();
        for(int j = 0; j < 3; j++){
            if(atoi(cadena.c_str()) == l[j].getId()){
                return true;
            }
        }
        aux.pop();
    }
    return false;
}

