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
        cout << "|      Simulación de un OS        V 1.2                           |" << endl;
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
    system(CLEAR);
    generarProcesos();
    procesamientoLotes();
    while(!cola.empty()) {
        cout << "\033[2;50H" << ++tiempoTotal << endl;
        cout << "\033[2;27H" << cola.size() - 1 << endl;
        cout << "\033[4;17H" << ++loteActual << endl;
        Lote l = cola.front();
        cola.pop();
        list<Proceso> lista;
        limpiarTabulacionLote();
        for(int i = 0; i < 3; i++) {
            if(l[i].getId() != -1111) {
                agregarTabulacionLote(l[i], i);
                lista.push_back(l[i]);
            }
        }
        /*while(!lista.empty()) {
            kbhitOpc(kbhit());
        }*/

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

void Interfaz::generarProcesos() {
    Lote l;
    int actual = 0;
    string op[5] = {"+", "-", "*", "/", "%"};
    srand(time(nullptr));
    for(int i = 0; i < procesoTotal; i++) {
        Proceso p;
        int opTipo = rand() % 5 + 0;
        p.setId(i + 1);
        p.setN1(rand() % -2000 + 2000);
        p.setOperador(op[opTipo]);
        if(opTipo == 3 or opTipo == 4) {
            p.setN2(rand() % 1 + 1000);
        } else {
            p.setN2(rand() % -2000 + 2000);
        }

        p.setTiempoEstimado(rand() % 7 + 9);
        l.setProceso(p, actual++);
        if(actual == 3) {
            actual = 0;
            cola.push(l);
            Lote aux;
            l = aux;
        }
    }
    if(actual != 3 and actual != 0) {
        cola.push(l);
    }
}

void Interfaz::procesamientoLotes() {
    cout << "+-----------------------+-------+--------------+---------+" << endl;
    cout << "| No. Lotes Pendientes  |       | Tiempo Total | 0       |" << endl;
    cout << "+-------------+---------+-------+--------------+---------+" << endl;
    cout << "| Lote actual |         | "<< endl;
    cout << "+----------+--+---------+-------------+-----------------------------------------------+---------------------------------------------------------------------------------------------+" << endl;
    cout << "|  ID      |  Tiempo estimado         |                Proceso                        |                                             Terminados                                      |" << endl;
    cout << "+----------+--------------------------+-----------------+-----------------------------+------+----------------------------------------------------------+---------------------------+" << endl;
    cout << "                                      | ID Programa     |                             | ID   |        Operación                                         |          Resultado        |" << endl;
    cout << "                                      | Operación       |                             +------+----------------------------------------------------------+---------------------------+ "<< endl;
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
    cout << "\033[" << 8 + cant << ";1H|          |                          |"<< endl;
    cout << "\033[" << 9 + cant << ";1H+----------+--------------------------+"<< endl;
    /* Primer tabla  */
    cout << "\033[" << 8 + cant << ";3H" << p.getId() << endl;
    cout << "\033[" << 8 + cant << ";32H" << p.getTiempoEstimado() << endl;
}

void Interfaz::limpiarTabulacionLote() {
    for(int i = 0; i < 4; i++) {
        cout << "\033[" << 8 + i << ";1H                                      "<< endl;
    }
}

void Interfaz::quitarProceso(int& pos) {
    cout << "\033[" << 8 + pos << ";2H                                     " << endl;
}

void Interfaz::procesarDatos(Proceso& p) {
    /* Segunda Tabla "Procesos" */
    cout << "\033[" << 8 << ";59H" << p.getId() << endl;
    cout << "\033[" << 9 << ";59H" << p.getOperacion() << endl;
    cout << "\033[" << 10 << ";59H" << p.getTiempoRestante() << endl;
    cout << "\033[" << 11 << ";59H" << p.getTiempoTranscurrido() << endl;
    cout << "\033[2;50H" << ++tiempoTotal << endl;
    sleep(1);
    /* Impresión del tiempo transcurrido, tiempo total e incremento del tiempo total */
    while(p.getTiempoRestante() > 0) {
        cout << "\033[2;50H" << ++tiempoTotal << endl;
        cout << "\033[" << 10 << ";59H    " << endl;
        cout << "\033[" << 11 << ";59H    " << endl;
        cout << "\033[" << 10 << ";59H" << p.adherirTiempoTranscurrido() << endl;
        cout << "\033[" << 11 << ";59H" << p.sustraerTiempoRestante() << endl;
        sleep(1);
    }
    /* Tercer Tabla "Terminados" */
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
    while(procesoTotal != 0) {
        cout << "\033[2;50H" << ++tiempoTotal << endl;
        sleep(1);
    }
}

void Interfaz::limpiarTablaProceso() {
    for(int i = 0; i < 4; i++) {
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

bool Interfaz::checkNumInt(const string& cadena) {
    regex rx("[0-9]+");
    if(regex_match(cadena, rx)) {
        return true;
    }
    return false;
}

int Interfaz::kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

void Interfaz::kbhitOpc(int tecla) {
    if(tecla == 105 or tecla == 73){

    }
    else if(tecla == 101 or tecla == 69){

    }
    else if(tecla == 112 or tecla == 80){
        while(true){
            if(kbhit() == 99 or kbhit() == 67){
                break;
            }
        }
    }
}
