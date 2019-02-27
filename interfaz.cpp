#include "interfaz.h"

Interfaz::Interfaz() {
    procesoTotal = 0;
    tiempoTotal = 0;
    index = 0;
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
        cout << "|      Simulación de un OS        V 1.3                           |" << endl;
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
    system(CLEAR);
    generarProcesos(atoi(cadena.c_str()));
    pantallaDeProcesos();
    unsigned int pActuales = 0;
    while(int(terminado.size()) != procesoTotal) {
        cout << "\033[2;21H" << nuevo.size() << endl;
        cout << "\033[2;45H" << tiempoTotal << endl;
        sleep(1);
        pActuales = listo.size() + bloqueado.size() + ejecucion.size();
        maxProcesos(pActuales);
        pActuales = listo.size() + bloqueado.size() + ejecucion.size();
        bool f = false;
        while(f == false) {
            imprimirListos();
            imprimirEjecucion();
            maxProcesos(pActuales);
            imprimirTerminados();
            imprimirBloqueados();
            sleep(1);
            imprimirListos();
            sleep(1);
            int ch = procesarDatos();
            if(ch == 0) {
                /*Interrupcion*/
                ejecucion.front().setTBloqueo(10);
                bloqueado.push(ejecucion.front());
                ejecucion.pop();
                f = true;
            } else if(ch == 1) {
                /*ERROR*/
                ejecucion.front().setTBloqueo(0);
                ejecucion.front().setResultado("ERROR");
                ejecucion.front().setTFinalizacion(tiempoTotal);
                terminado.push(ejecucion.front());
                ejecucion.pop();
                f = true;
            } else if(ch == 2) {
                /*Terminado*/
                int resultado = 0;
                if(ejecucion.front().getOperador() == "+") {
                    resultado = ejecucion.front().getN1() + ejecucion.front().getN2();
                } else if(ejecucion.front().getOperador() == "-") {
                    resultado = ejecucion.front().getN1() - ejecucion.front().getN2();
                } else if(ejecucion.front().getOperador() == "*") {
                    resultado = ejecucion.front().getN1() * ejecucion.front().getN2();
                } else if(ejecucion.front().getOperador() == "/") {
                    resultado = ejecucion.front().getN1() / ejecucion.front().getN2();
                } else {
                    resultado = ejecucion.front().getN1()%ejecucion.front().getN2();
                }
                ejecucion.front().setTBloqueo(0);
                ejecucion.front().setResultado(to_string(resultado));
                ejecucion.front().setTFinalizacion(tiempoTotal);
                terminado.push(ejecucion.front());
                ejecucion.pop();
                f = true;
            } else {
                f = false;
            }
        }
    }
    imprimirListos();
    imprimirEjecucion();
    imprimirTerminados();
    imprimirBloqueados();
    cout << "\033[15;1H" << endl << endl;
    cout << "Presione [enter] para continuar...";
    while(true) {
        if(kbhit() == 10) {
            break;
        }
    }
}

int Interfaz::procesarDatos() {
    int ch = -1;
    if(bloqueado.size() == 3) {
        while(bloqueado.size() == 3) {
            ch = kbhit();
            if(ch == 112 or ch == 80) {
                pausaKbhit();
            }
            if(bloqueado.front().getTBloqueo() > 0) {
                cout << "\033[2;45H" << ++tiempoTotal << endl;
                bloqueado.front().sustraerTBloqueo();
            } else {
                cout << "\033[2;45H" << tiempoTotal << endl;
                cout << "\033[" << 13  << ";52H              " << endl;
                cout << "\033[" << 13  << ";52H" << bloqueado.front().getTBloqueo() << endl;
                listo.push(bloqueado.front());
                bloqueado.pop();
                ch = -1;
                break;
            }
            cout << "\033[" << 13  << ";52H              " << endl;
            cout << "\033[" << 13  << ";52H" << bloqueado.front().getTBloqueo() << endl;
            sleep(1);
        }
    } else {
        while(ch != 0 and ch != 1 and ch != 2) {
            /* Impresión del tiempo transcurrido, tiempo total e incremento del tiempo total */
            imprimirListos();
            imprimirBloqueados();
            imprimirEjecucion();
            sleep(1);
            ch = kbhit();
            if(ch == 105 or ch == 73) {
                ch = 0;
            } else if(ch == 101 or ch == 69) {
                ch = 1;
            } else if(ch == 112 or ch == 80) {
                pausaKbhit();
            } else {
                // En caso de terminar el proceso CH = 2
                if(ejecucion.front().getTRestante() == 0) {
                    ch = 2;
                } else {
                    // Se hacen las sustracciones y adhisiones a los tiempos correspondientes
                    cout << "\033[2;45H" << ++tiempoTotal << endl;
                    ejecucion.front().sustraerTRestante();
                    ejecucion.front().adherirTTranscurrido();
                    // Impresión de cualquier proceso en bloqueado
                    if(!bloqueado.empty()) {
                        if(bloqueado.front().getTBloqueo() == 0) {
                            listo.push(bloqueado.front());
                            bloqueado.pop();
                        } else {
                            bloqueado.front().sustraerTBloqueo();
                        }
                    }
                    ch = -1;
                }
            }
        }
    }
    return ch;
}

void Interfaz::generarProcesos(const int & cProcesos) {
    procesoTotal += cProcesos;
    string op[5] = {"+", "-", "*", "/", "%"};
    srand(time(nullptr));
    for(; index < procesoTotal; index++) {
        Proceso p;
        int opTipo = rand() % 4 - 0;
        p.setId(index + 1);
        p.setN1(rand() % -2000 + 2000);
        p.setOperador(op[opTipo]);
        if(opTipo == 3 or opTipo == 4) {
            p.setN2(rand() % 1 + 10);
        } else {
            p.setN2(rand() % -2000 + 1000);
        }
        p.setTServicio(rand() % 7 + 11);
        nuevo.push(p);
    }
}

void Interfaz::maxProcesos(const int & pActuales) {
    if(pActuales < 3) {
        if(!nuevo.empty()) {
            Proceso p = nuevo.front();
            nuevo.front().setTLlegada(tiempoTotal);
            listo.push(p);
            nuevo.pop();
            cout << "\033[2;21H" << nuevo.size() << endl;
        }
        sleep(1);
    }
}


void Interfaz::pantallaDeProcesos() {
    cout << "+-----------------+-------+--------------+---------+" << endl;
    cout << "| Procesos nuevos |       | Tiempo Total |         |" << endl;
    cout << "+------+---------++-------+------+-------+---------+-----------------------------+---------------------------------------------------------------------------------------------+" << endl;
    cout << "|  ID  |  T.M.E  |  T.Restante   |                Ejecucion                      |                                             Terminados                                      |" << endl;
    cout << "+------+---------+---------------+-----------------+-----------------------------+------+----------------------------------------------------------+---------------------------+" << endl;
    cout << "                                 | ID Programa     |                             | ID   |        Operación                                         |          Resultado        |" << endl;
    cout << "                                 | Operación       |                             +------+----------------------------------------------------------+---------------------------+ "<< endl;
    cout << "                                 | T. Restante     |                             | " << endl;
    cout << "                                 | T. Transcurrido |                             | " << endl;
    cout << "                                 +---------------+-+--------------+--------------+ " << endl;
    cout << "                                 | ID Bloqueado  |  T. de bloqueo |" << endl;
    cout << "                                 +---------------+----------------+" << endl;
}

void Interfaz::imprimirListos() {
    // Código para limpiar la tabla de listos
    for(int i = 0; i < 4; i++) {
        cout << "\033["<< 6 + i << ";1H                                 " << endl;
    }
    // Imprime los valores de la cola
    for(unsigned int i = 0; i < listo.size(); i++) {
        cout << "\033["<< 6 + i << ";1H|      |         |               |" << endl;
        cout << "\033["<< 6 + i << ";2H" << listo.front().getId() << endl;
        cout << "\033["<< 6 + i << ";10H" << listo.front().getTServicio() << endl;
        cout << "\033["<< 6 + i << ";20H" << listo.front().getTRestante() << endl;
        cout << "\033["<< 7 + i << ";1H+------+---------+---------------+" << endl;
        listo.push(listo.front());
        listo.pop();
    }
}

void Interfaz::imprimirEjecucion() {
    // Código para limpiar los campos de ejecucion
    for(int i = 0; i < 4; i++) {
        cout << "\033[" << 6 + i << ";53H                             " << endl;
    }
    // Código para imprimir el proceso en el FRONT de la cola listos
    if(!listo.empty()) {
        if(ejecucion.empty()) {
            ejecucion.push(listo.front());
            listo.pop();
        }
    }
    // Imprime en pantalla todo dato que se encuentre dentro de la cola Ejecucion
    if(!ejecucion.empty()) {
        cout <<"\033[" << 6 << ";54H" << ejecucion.front().getId() << endl;
        cout <<"\033[" << 7 << ";54H" << ejecucion.front().getOperacion() << endl;
        cout <<"\033[" << 8 << ";54H" << ejecucion.front().getTRestante() << endl;
        cout <<"\033[" << 9 << ";54H" << ejecucion.front().getTTranscurrido() << endl;
    }
}

void Interfaz::imprimirBloqueados() {
    // Código para limpiar los campos de bloqueo
    for(int i = 0; i < 4; i++) {
        cout << "\033[" << 13 + i << ";34H                                  " << endl;
    }
    // Código para imprimir los campos de bloqueo
    for(unsigned int i = 0; i < bloqueado.size(); i++) {
        cout << "\033[" << 13 + i << ";34H|               |                |" << endl;
        cout << "\033[" << 13 + i << ";36H" << bloqueado.front().getId() << endl;
        cout << "\033[" << 13 + i << ";52H" << bloqueado.front().getTBloqueo() << endl;
        cout << "\033[" << 14 + i << ";34H+---------------+----------------+" << endl;
        bloqueado.push(bloqueado.front());
        bloqueado.pop();
    }
}

void Interfaz::imprimirTerminados() {
    /* Terminados */
    for(unsigned int i = 0; i < terminado.size(); i++) {
        cout << "\033[" << 8 + i << ";83H                                                                                              " << endl;
        cout << "\033[" << 8 + i << ";82H|      |                                                          |                           |" << endl;
        cout << "\033[" << 8 + i << ";84H" << terminado.front().getId() << endl;
        cout << "\033[" << 8 + i << ";91H" << terminado.front().getOperacion() << endl;
        cout << "\033[" << 8 + i << ";150H" << terminado.front().getResultado() << endl;
        terminado.push(terminado.front());
        terminado.pop();
    }
    if(!terminado.empty()) {
        cout << "\033[" << 8 + terminado.size() << ";82H+------+----------------------------------------------------------+---------------------------+" << endl;
    }
}

void Interfaz::pausaProceso() {
    cout << "\033[20;1H" << endl << endl;
    cout << "Presione [enter] para continuar...";
    cin.get();
    cout << "\033[20;1H" << endl << endl;
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
    cout << "\033[20;1H¡Pausa! Presione [c] para continuar..." << endl;
    int ch = 0;
    while (getchar() != EOF);
    while(true) {
        ch = kbhit();
        if(ch == 99 or ch == 67) {
            cout << "\033[20;1H                                      " << endl;
            cout << "\033[20;1H¡Continuemos!                        " << endl;
            sleep(1);
            cout << "\033[20;1H                                      " << endl;
            break;
        }
    }
}
