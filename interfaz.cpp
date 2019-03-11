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
        cout << "|      Simulación de un OS        V 1.4                           |" << endl;
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
    while(int(terminado.size()) != procesoTotal) {
        cout << "\033[2;21H    " << endl;
        cout << "\033[2;21H" << nuevo.size() << endl;
        cout << "\033[2;45H" << tiempoTotal << endl;
        sleep(1);
        maxProcesos();
        bool f = false;
        while(f == false) {
            imprimirListos();
            imprimirEjecucion();
            imprimirTerminados();
            imprimirBloqueados();
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
                ejecucion.front().setTRetorno(ejecucion.front().getTFinalizacion() - ejecucion.front().getTLlegada());
                ejecucion.front().setTEspera(ejecucion.front().getTRetorno() - ejecucion.front().getTServicio());
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
                // Últimos cálculos
                ejecucion.front().setTRetorno(ejecucion.front().getTFinalizacion() - ejecucion.front().getTLlegada());
                ejecucion.front().setTEspera(ejecucion.front().getTRetorno() - ejecucion.front().getTServicio());
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
    cout << "Presione [enter] para mostrar el cálculo de los tiempos...";
    while(true) {
        if(kbhit() == 10) {
            break;
        }
    }
    imprimirTiemposFinal();
    cout << "\033[15;1H" << endl << endl;
    cout << "Presione [enter] para continuar...";
    while(true) {
        if(kbhit() == 10) {
            break;
        }
    }
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
        p.setTME(rand() % 7 + 11);
        nuevo.push(p);
    }
}

void Interfaz::maxProcesos() {
    unsigned int pActuales = listo.size() + bloqueado.size() + ejecucion.size();
    while(pActuales < 3) {
        imprimirListos();
        if(!nuevo.empty()) {
            nuevo.front().setTLlegada(tiempoTotal);
            listo.push(nuevo.front());
            nuevo.pop();
            cout << "\033[2;21H    " << endl;
            cout << "\033[2;21H" << nuevo.size() << endl;
        } else {
            break;
        }
        pActuales = listo.size() + bloqueado.size() + ejecucion.size();
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
        cout << "\033["<< 6 + i << ";3H" << listo.front().getId() << endl;
        cout << "\033["<< 6 + i << ";10H" << listo.front().getTME() << endl;
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
            if(listo.front().getTResFlag() == false) {
                listo.front().setTRespuesta(tiempoTotal - listo.front().getTLlegada());
            }
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

int Interfaz::procesarDatos() {
    int ch = -1;
    if(listo.empty() and ejecucion.empty() and !bloqueado.empty()) {
        while(true) {
            ch = kbhit();
            if(ch == 112 or ch == 80) {
                pausaKbhit();
            } else if(ch == 78 or ch == 110) {
                generarProcesos(1);
                maxProcesos();
                imprimirListos();
                cout << "\033[2;21H" << nuevo.size() << endl;
                if(bloqueado.size() < 3){
                    break;
                }
            } else if(ch == 116 or ch == 84) {
                imprimirTiemposActual();
            }
            if(bloqueado.front().getTBloqueo() > 0) {
                for(unsigned int i = 0; i < bloqueado.size(); i++) {
                    bloqueado.front().sustraerTBloqueo();
                    bloqueado.push(bloqueado.front());
                    bloqueado.pop();
                }
                imprimirBloqueados();
                cout << "\033[2;45H" << ++tiempoTotal << endl;
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
            } else if(ch == 78 or ch == 110) {
                generarProcesos(1);
                maxProcesos();
                imprimirListos();
                cout << "\033[2;21H" << nuevo.size() << endl;
            } else if(ch == 116 or ch == 84) {
                imprimirTiemposActual();
            } else {
                // En caso de terminar el proceso CH = 2
                if(ejecucion.front().getTRestante() == 0) {
                    ch = 2;
                } else {
                    // Se hacen las sustracciones y adhisiones a los tiempos correspondientes
                    cout << "\033[2;45H" << ++tiempoTotal << endl;
                    ejecucion.front().setTServicio(ejecucion.front().getTServicio() + 1);
                    ejecucion.front().sustraerTRestante();
                    ejecucion.front().adherirTTranscurrido();
                    // Impresión de cualquier proceso en bloqueado
                    if(!bloqueado.empty()) {
                        if(bloqueado.front().getTBloqueo() == 0) {
                            listo.push(bloqueado.front());
                            bloqueado.pop();
                        } else {
                            for(unsigned int i = 0; i < bloqueado.size(); i++) {
                                bloqueado.front().sustraerTBloqueo();
                                bloqueado.push(bloqueado.front());
                                bloqueado.pop();
                            }
                        }
                    }
                    ch = -1;
                }
            }
        }
    }
    return ch;
}


void Interfaz::imprimirTiemposActual() {
    system(CLEAR);
    unsigned int i = 0;
    cout << "+-----+------------------+-----------------+---------------+------------+-----------+----------------+--------------+-------------+-----------+------------+-----+" << endl;
    cout << "| ID  |    Operación     |    Resultado    | Estado actual | T.Restante | T.Llegada | T.Finalización | T. Respuesta | T. Servicio | T. Espera | T. Retorno | TME |" << endl;
    cout << "+-----+------------------+-----------------+---------------+------------+-----------+----------------+--------------+-------------+-----------+------------+-----+" << endl;
    datosTiempoActual(nuevo, "Nuevo", i);
    datosTiempoActual(listo, "Listo", i);
    datosTiempoActual(ejecucion, "Ejecucion", i);
    datosTiempoActual(bloqueado, "Bloqueado", i);
    datosTiempoActual(terminado, "Terminado", i);
    cout << "+-----+------------------+-----------------+---------------+------------+-----------+----------------+--------------+-------------+-----------+------------+-----+" << endl;
    cout << "\033[15;1H" << endl << endl;
    cout << "Presione [c] para continuar...";
    while(true) {
        int ch = kbhit();
        if(ch == 99 or ch == 67) {
            break;
        }
    }
    system(CLEAR);
    pantallaDeProcesos();
    cout << "\033[2;21H" << nuevo.size() << endl;
    cout << "\033[2;45H" << tiempoTotal << endl;
    imprimirListos();
    imprimirEjecucion();
    imprimirTerminados();
    imprimirBloqueados();
}

void Interfaz::datosTiempoActual(queue<Proceso>& q, const string& n, unsigned int &i) {
    // Impresión para la cola recibida (NUEVO, LISTO, EJECUCION, BLOQUEADO, TERMINADO)
    for(unsigned int j = 0; j < q.size(); i++, j++) {
        cout << "\033[" << 4 + i << ";1H|     |                  |                 |               |            |           |                |              |             |           |            |     |" << endl;
        cout << "\033[" << 4 + i << ";3H" << q.front().getId() << endl;
        cout << "\033[" << 4 + i << ";9H" << q.front().getOperacion() << endl;
        cout << "\033[" << 4 + i << ";158H" << q.front().getTME() << endl;
        cout << "\033[" << 4 + i << ";46H" << n  << endl;
        if(n == "Nuevo") {
            cout << "\033[" << 4 + i << ";28HNULL"  << endl;
            cout << "\033[" << 4 + i << ";62HNULL" << endl;
            cout << "\033[" << 4 + i << ";75HNULL" << endl;
            cout << "\033[" << 4 + i << ";87HNULL" << endl;
            cout << "\033[" << 4 + i << ";104HNULL" << endl;
            cout << "\033[" << 4 + i << ";119HNULL" << endl;
            cout << "\033[" << 4 + i << ";133HNULL" << endl;
            cout << "\033[" << 4 + i << ";145HNULL" << endl;
        } else {
            cout << "\033[" << 4 + i << ";75H" << q.front().getTLlegada() << endl;
            if(n != "Terminado") {
                cout << "\033[" << 4 + i << ";28HN/A"  << endl;
                cout << "\033[" << 4 + i << ";62H" << q.front().getTRestante() << endl;
                cout << "\033[" << 4 + i << ";87HN/A" << endl;
                cout << "\033[" << 4 + i << ";133H" << (tiempoTotal - q.front().getTLlegada()) - q.front().getTServicio() << endl;
                cout << "\033[" << 4 + i << ";145HN/A" << endl;
                if(q.front().getTResFlag() == true) {
                    cout << "\033[" << 4 + i << ";104H" << q.front().getTRespuesta() << endl;
                    cout << "\033[" << 4 + i << ";119H" << q.front().getTServicio() << endl;
                } else {
                    cout << "\033[" << 4 + i << ";104HN/A" << endl;
                    cout << "\033[" << 4 + i << ";119HN/A" << endl;
                }
            } else {
                cout << "\033[" << 4 + i << ";28H" << q.front().getResultado() << endl;
                cout << "\033[" << 4 + i << ";62HN/A" << endl;
                cout << "\033[" << 4 + i << ";87H" << q.front().getTFinalizacion() << endl;
                cout << "\033[" << 4 + i << ";104H" << q.front().getTRespuesta() << endl;
                cout << "\033[" << 4 + i << ";119H" << q.front().getTServicio() << endl;
                cout << "\033[" << 4 + i << ";133H" << q.front().getTEspera() << endl;
                cout << "\033[" << 4 + i << ";145H" << q.front().getTRetorno() << endl;
            }
        }
        q.push(q.front());
        q.pop();
    }
}


void Interfaz::imprimirTiemposFinal() {
    system(CLEAR);
    cout << "+-----+------------------+-----------------+-----------+----------------+--------------+-------------+-----------+------------+-----+" << endl;
    cout << "| ID  |    Operación     |    Resultado    | T.Llegada | T.Finalización | T. Respuesta | T. Servicio | T. Espera | T. Retorno | TME |" << endl;
    cout << "+-----+------------------+-----------------+-----------+----------------+--------------+-------------+-----------+------------+-----+" << endl;
    for(unsigned int i = 0; i < terminado.size(); i++) {
        cout << "\033[" << 4 + i << ";1H|     |                  |                 |           |                |              |             |           |            |     |" << endl;
        cout << "\033[" << 4 + i << ";3H" << terminado.front().getId() << endl;
        cout << "\033[" << 4 + i << ";9H" << terminado.front().getOperacion() << endl;
        cout << "\033[" << 4 + i << ";28H" << terminado.front().getResultado() << endl;
        cout << "\033[" << 4 + i << ";46H" << terminado.front().getTLlegada() << endl;
        cout << "\033[" << 4 + i << ";58H" << terminado.front().getTFinalizacion() << endl;
        cout << "\033[" << 4 + i << ";90H" << terminado.front().getTServicio() << endl;
        cout << "\033[" << 4 + i << ";75H" << terminado.front().getTRespuesta() << endl;
        cout << "\033[" << 4 + i << ";104H" << terminado.front().getTEspera() << endl;
        cout << "\033[" << 4 + i << ";116H" << terminado.front().getTRetorno() << endl;
        cout << "\033[" << 4 + i << ";129H" << terminado.front().getTME() << endl;
        terminado.push(terminado.front());
        terminado.pop();
    }
    cout << "\033[" << 4 + terminado.size() << ";1H+-----+------------------+-----------------+-----------+----------------+--------------+-------------+-----------+------------+-----+" << endl;
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
