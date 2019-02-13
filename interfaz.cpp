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
        limpiarTabulacionLote();
        for(int i = 0; i < 3; i++) {
            if(l[i].getId() != -1111) {
                lista.push_back(l[i]);
            }
        }
        unsigned int index = 0;
        while(!lista.empty()) {
            limpiarTablaProceso();
            imprimirLote();
            sleep(1);
            int res = procesarDatos(index);
            if(res == 1) {
                /* Procesos con ERROR */
                procesoActual++;
                procesoTotal--;
                agregarTabulacionTerminado(index);
                cout << "\033[" << 8 + procesoActual + loteActual << ";89H" << lista[index].getId() << endl;
                cout << "\033[" << 8 + procesoActual + loteActual << ";96H" << lista[index].getOperacion() << endl;
                cout << "\033[" << 8 + procesoActual + loteActual << ";155HERROR" << endl;
                lista.erase(lista.begin() + index);
                imprimirLote();

            } else if(res == 2) {
                procesoActual++;
                procesoTotal--;
                agregarTabulacionTerminado(index);
                /* Tercer Tabla "Terminados" */
                cout << "\033[" << 8 + procesoActual + loteActual << ";89H" << lista[index].getId() << endl;
                cout << "\033[" << 8 + procesoActual + loteActual << ";96H" << lista[index].getOperacion() << endl;
                float resultado = 0;
                if(lista[index].getOperador() == "+") {
                    resultado = lista[index].getN1() + lista[index].getN2();
                } else if(lista[index].getOperador() == "-") {
                    resultado = lista[index].getN1() - lista[index].getN2();
                } else if(lista[index].getOperador() == "*") {
                    resultado = lista[index].getN1() * lista[index].getN2();
                } else if(lista[index].getOperador() == "/") {
                    resultado = lista[index].getN1() / lista[index].getN2();
                } else {
                    resultado = int(lista[index].getN1()) % int(lista[index].getN2());
                }
                cout << "\033[" << 8 + procesoActual + loteActual << ";155H" << resultado << endl;
                lista.erase(lista.begin() + index);
                imprimirLote();
            } else {
                index++;
            }
            if(index > lista.size() - 1) {
                index = 0;
            }
            cout << "\033[2;50H" << ++tiempoTotal << endl;
        }
        sleep(1);
    }
    cout << "\033[15;1H" << endl << endl;
    cout << "Presione [enter] para continuar...";
    while(true){
        if(kbhit() == 10){
            break;
        }
    }
}

void Interfaz::generarProcesos() {
    Lote l;
    int actual = 0;
    string op[5] = {"+", "-", "*", "/", "%"};
    srand(time(nullptr));
    for(int i = 0; i < procesoTotal; i++) {
        Proceso p;
        int opTipo = rand() % 4 - 0;
        p.setId(i + 1);
        p.setN1(rand() % -2000 + 2000);
        p.setOperador(op[opTipo]);
        if(opTipo == 3 or opTipo == 4) {
            p.setN2(rand() % 1 + 10);
        } else {
            p.setN2(rand() % -2000 + 1000);
        }
        p.setTiempoEstimado(rand() % 7 + 11);
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
    cout << "+------+------+-------+-+-------------+-----------------------------------------------+---------------------------------------------------------------------------------------------+" << endl;
    cout << "|  ID  |  T.Estimado  |  T.Restante   |                Proceso                        |                                             Terminados                                      |" << endl;
    cout << "+------+--------------+---------------+-----------------+-----------------------------+------+----------------------------------------------------------+---------------------------+" << endl;
    cout << "                                      | ID Programa     |                             | ID   |        Operación                                         |          Resultado        |" << endl;
    cout << "                                      | Operación       |                             +------+----------------------------------------------------------+---------------------------+ "<< endl;
    cout << "                                      | T. Transcurrido |                             | " << endl;
    cout << "                                      | T. Restante     |                             | " << endl;
    cout << "                                      +-----------------+-----------------------------+ " << endl;
}

void Interfaz::agregarTabulacionTerminado(const int &cant) {
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

void Interfaz::imprimirLote() {
    limpiarTabulacionLote();
    for(unsigned int i = 0; i < lista.size(); i++){
        /* Procesados */
        cout << "\033[" << 8 + i << ";2H                                      " << endl;
        cout << "\033[" << 8 + i << ";1H|      |              |               |"<< endl;
        cout << "\033[" << 9 + i << ";1H+------+--------------+---------------+"<< endl;
        /* Primer tabla  */
        cout << "\033[" << 8 + i << ";2H" << lista[i].getId() << endl;
        cout << "\033[" << 8 + i << ";11H" << lista[i].getTiempoEstimado() << endl;
        cout << "\033[" << 8 + i << ";26H" << lista[i].getTiempoRestante() << endl;
    }
}

void Interfaz::limpiarTabulacionLote() {
    for(int i = 0; i < 4; i++) {
        cout << "\033[" << 8 + i << ";1H                                      "<< endl;
    }
}

int Interfaz::procesarDatos(unsigned int &index) {
    int ch = kbhit();
    if(ch == 105 or ch == 73) {
        return 0;
    } else if(ch == 101 or ch == 69) {
        return 1;
    } else if(ch == 112 or ch == 80) {
        pausaKbhit();
    } else {
        ch = 0;
    }
    /* Segunda Tabla "Procesos" */
    cout << "\033[" << 8 << ";59H" << lista[index].getId() << endl;
    cout << "\033[" << 9 << ";59H" << lista[index].getOperacion() << endl;
    cout << "\033[" << 10 << ";59H" << lista[index].getTiempoRestante() << endl;
    cout << "\033[" << 11 << ";59H" << lista[index].getTiempoTranscurrido() << endl;
    cout << "\033[2;50H" << ++tiempoTotal << endl;
    sleep(1);
    ch = kbhit();
    if(ch == 105 or ch == 73) {
        return 0;
    } else if(ch == 101 or ch == 69) {
        return 1;
    } else if(ch == 112 or ch == 80) {
        pausaKbhit();
    } else {
        ch = 0;
    }
    /* Impresión del tiempo transcurrido, tiempo total e incremento del tiempo total */
    while(lista[index].getTiempoRestante() > 0) {
        ch = kbhit();
        if(ch == 105 or ch == 73) {
            return 0;
        } else if(ch == 101 or ch == 69) {
            return 1;
        } else if(ch == 112 or ch == 80) {
            pausaKbhit();
        } else {
            ch = 0;
        }
        cout << "\033[2;50H" << ++tiempoTotal << endl;
        cout << "\033[" << 10 << ";59H    " << endl;
        cout << "\033[" << 11 << ";59H    " << endl;
        cout << "\033[" << 10 << ";59H" << lista[index].adherirTiempoTranscurrido() << endl;
        cout << "\033[" << 11 << ";59H" << lista[index].sustraerTiempoRestante() << endl;
        sleep(1);
    }
    return 2;
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
    cout << "\033[15;1H" << endl << endl;
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
        while (getchar() != EOF);
        return ch;
    }
    while (getchar() != EOF);
    return 0;
}

void Interfaz::pausaKbhit() {
    cout << "\033[15;1H¡Pausa! Presione [c] para continuar..." << endl;
    int ch = 0;
    while (getchar() != EOF);
    while(true) {
        ch = kbhit();
        if(ch == 99 or ch == 67) {
            cout << "\033[15;1H                                      " << endl;
            cout << "\033[15;1H¡Continuemos!                        " << endl;
            sleep(1);
            cout << "\033[15;1H                                      " << endl;
            break;
        }
    }
}
