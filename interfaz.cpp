#include "interfaz.h"

Interfaz::Interfaz() {
    procesoTotal = 0;
    tiempoTotal = 0;
    index = 0;
    quantum = 0;
    mLibre = 170;
    mUsada = 10;
    pagDis = 34;
    cSuspendidos = 0;
    menuInicio();
}

Interfaz::~Interfaz() {
    //dtor
}

void Interfaz::menuInicio() {
    string cadena, quan;
    do {
        system(CLEAR);
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "|      Simulación de un OS        V 1.7                           |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Ingrese la cantidad de procesos a crear:                        |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "\033[4;44H";
        getline(cin, cadena);
        if(checkNumInt(cadena)) {
            do {
                cout << "\033[5;1H| Ingrese el valor del Quantum:                                   |" << endl;
                cout << "\033[6;1H+-----------------------------------------------------------------+" << endl;
                cout << "\033[5;33H";
                getline(cin, quan);
                if(checkNumInt(quan)) {
                    break;
                } else {
                    cout << "+-----------------------------------------------------------------+" << endl;
                    cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
                    cout << "+-----------------------------------------------------------------+" << endl;
                    pausaProceso();
                    cout << "\033[7;1H                                                                   " << endl;
                    cout << "\033[8;1H                                                                   " << endl;
                    cout << "\033[9;1H                                                                   " << endl;
                }
            } while(true);
            break;
        }
        cout << "+-----------------------------------------------------------------+" << endl;
        cout << "| Ha introducido un número o carácter inválido. Intente de nuevo. |" << endl;
        cout << "+-----------------------------------------------------------------+" << endl;
        pausaProceso();
    } while(true);
    system(CLEAR);
    generarProcesos(atoi(cadena.c_str()));
    quantum = atoi(quan.c_str());
    pantallaDeProcesos();
    while(int(terminado.size()) != procesoTotal) {
        ///
        cout << "\033[2;21H    " << endl;
        cout << "\033[2;21H" << nuevo.size() << endl;
        cout << "\033[2;39H    " << endl;
        cout << "\033[2;54H    " << endl;
        if(nuevo.empty()) {
            cout << "\033[2;39H0" << endl;
            cout << "\033[2;54H0" << endl;
        } else {
            cout << "\033[2;39H" << nuevo.front().getId() << endl;
            cout << "\033[2;54H" << nuevo.front().getTamanio() << endl;

        }
        ///
        cout << "\033[2;80H" << tiempoTotal << endl;
        cout << "\033[2;100H    " << endl;
        cout << "\033[2;100H" << contQuantum << endl;
        cout << "\033[32;94H   " << endl;
        cout << "\033[32;94H" << cSuspendidos << endl;
        sleep(1);
        maxProcesos();
        bool f = false;
        while(f == false) {
            imprimirListos();
            imprimirEjecucion();
            imprimirTerminados();
            imprimirBloqueados();
            imprimirMemoria();
            sleep(1);
            int ch = procesarDatos();
            if(ch == 0) {
                /*Interrupcion*/
                ejecucion.front().setTBloqueo(10);
                asignarEstado(ejecucion.front().getId(), 'B');
                bloqueado.push(ejecucion.front());
                ejecucion.pop();
                contQuantum = 0;
                f = true;
            } else if(ch == 1) {
                /*ERROR*/
                ejecucion.front().setTBloqueo(0);
                ejecucion.front().setResultado("ERROR");
                ejecucion.front().setTFinalizacion(tiempoTotal);
                ejecucion.front().setTRetorno(ejecucion.front().getTFinalizacion() - ejecucion.front().getTLlegada());
                ejecucion.front().setTEspera(ejecucion.front().getTRetorno() - ejecucion.front().getTServicio());
                terminado.push(ejecucion.front());
                //Liberar memoria
                liberarMemoria(ejecucion.front().getId());
                ejecucion.pop();
                contQuantum = 0;
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
                //Liberar memoria
                liberarMemoria(ejecucion.front().getId());
                ejecucion.pop();
                contQuantum = 0;
                f = true;
            } else if(ch == 3) {
                asignarEstado(ejecucion.front().getId(), 'L');
                listo.push(ejecucion.front());
                ejecucion.pop();
                contQuantum = 0;
                cout << "\033[2;100H    " << endl;
                cout << "\033[2;100H" << contQuantum << endl;
                imprimirMemoria();
            } else {
                f = false;
            }
        }
    }
    imprimirListos();
    imprimirEjecucion();
    imprimirTerminados();
    imprimirBloqueados();
    imprimirMemoria();
    cout << "\033[50;1H" << endl << endl;
    cout << "Presione [C] para mostrar el cálculo de los tiempos...";
    while(true) {
        if(kbhit() == 99 or kbhit() == 67) {
            break;
        }
    }
    imprimirTiemposFinal();
    cout << "\033[15;1H" << endl << endl;
    cout << "Presione [C] para finalizar...";
    while(true) {
        if(kbhit() == 99 or kbhit() == 67) {
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
        p.setTamanio(6 + rand()%25);
        nuevo.push(p);
    }
}

void Interfaz::maxProcesos() {
    while(!nuevo.empty()) {
        int noPaginas = (nuevo.front().getTamanio() * 10)/5;
        if(noPaginas%5 == 0) {
            noPaginas = (noPaginas/10);
        } else {
            noPaginas = (noPaginas/10) + 1;
        }
        if(pagDis >= noPaginas) {
            mLibre -= nuevo.front().getTamanio();
            mUsada += nuevo.front().getTamanio();
            pagDis -= noPaginas;
            for(int i = 0, tamanio = nuevo.front().getTamanio(); i < 34 and noPaginas > 0; i++) {
                if(m[i].ocupado == false) {
                    noPaginas--;
                    m[i].ocupado = true;
                    m[i].estado = 'L';
                    m[i].idProceso = nuevo.front().getId();
                    if(tamanio > 5) {
                        tamanio -= 5;
                        m[i].tUsado += 5;
                    } else {
                        m[i].tUsado += tamanio;
                        break;
                    }
                }
            }
            nuevo.front().setTLlegada(tiempoTotal);
            listo.push(nuevo.front());
            nuevo.pop();
            cout << "\033[2;21H    " << endl;
            cout << "\033[2;21H" << nuevo.size() << endl;
            cout << "\033[2;39H    " << endl;
            cout << "\033[2;54H    " << endl;
            if(nuevo.empty()) {
                cout << "\033[2;39H0" << endl;
                cout << "\033[2;54H0" << endl;
            } else {
                cout << "\033[2;39H" << nuevo.front().getId() << endl;
                cout << "\033[2;54H" << nuevo.front().getTamanio() << endl;

            }
            imprimirListos();
            imprimirMemoria();
            sleep(1);
        } else {
            break;
        }
    }
}

void Interfaz::pantallaDeProcesos() {
    cout << "+-----------------+-------+---------+-------+------+--------+--------------+---------+----------+-------+" << endl;
    cout << "| Procesos nuevos |       | ID. NEW |       | TAM  |        | Tiempo Total |         | QUANTUM  |       |" << endl;
    cout << "+------+---------++-------+------+--+-------+------+--------+--------------+-----+---+----------+-------+----------------------------------------------------------------------+" << endl;
    cout << "|  ID  |  T.M.E  |  T.Restante   |                Ejecucion                      |                                             Terminados                                      |" << endl;
    cout << "+------+---------+---------------+-----------------+-----------------------------+------+----------------------------------------------------------+---------------------------+" << endl;
    cout << "                                 | ID Programa     |                             | ID   |        Operación                                         |          Resultado        |" << endl;
    cout << "                                 | Operación       |                             +------+----------------------------------------------------------+---------------------------+ "<< endl;
    cout << "                                 | T. Restante     |                             | " << endl;
    cout << "                                 | T. Transcurrido |                             | " << endl;
    cout << "                                 +---------------+-+--------------+--------------+ " << endl;
    cout << "                                 | ID Bloqueado  |  T. de bloqueo |" << endl;
    cout << "                                 +---------------+----------------+" << endl;
    cout << "\033[31;0H";
    cout << "+---------------+---------+-------+-----------+-------+-----------+-------+      +---------+----+---------+-------+------+--------+" << endl;
    cout << "|    Memoria    | M.Libre |       | M.Ocupada |       | Marcos D. |       |      | C.Susp  |    | ID. SUS |       | TAM  |        |" << endl;
    cout << "+----------+----+----+----+----+--+-+----+----+----+--+-+----+----+----+--+-+----+----+----+----+----+----+----+--+-+----+----+---++----+----+----+----+----+----+----+----+----+----+----+----+" << endl;
    cout << "|  Marcos  |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 |" << endl;
    cout << "+----------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl;
    cout << "|  Tamaño  |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |  5 |" << endl;
    cout << "+----------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl;
    cout << "|  T.Usado |  5 |  5 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;
    cout << "+----------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl;
    cout << "|  Estado  | OS | OS |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;
    cout << "+----------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl;
    cout << endl;
    cout << "+----------+" << endl;
    cout << "|  Páginas |" << endl;
    cout << "+----------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl;
    cout << "|  Proceso |  X |  X |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;
    cout << "+----------+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+" << endl;
    imprimirMemoria();
}

void Interfaz::imprimirListos() {
    // Código para limpiar la tabla de listos
    for(unsigned int i = 0; i < 18; i++) {
        cout << "\033["<< 6 + i << ";1H                                 "  << endl;
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
            asignarEstado(ejecucion.front().getId(), 'E');
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
    for(unsigned int i = 0; i < 18; i++) {
        cout << "\033[" << 13 + i << ";35H                                  " << endl;
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
    if(nuevo.empty() and listo.empty() and ejecucion.empty() and !bloqueado.empty()) {
        bool f = false;
        while(true and f == false) {
            ch = kbhit();
            maxProcesos();
            if(ch == 112 or ch == 80 or ch == 109 or ch == 77) {
                pausaKbhit();
            } else if(ch == 78 or ch == 110) {
                nuevoProceso();
                break;
            } else if(ch == 115 or ch == 83) {
                /// Bloqueado suspendido
                if(!bloqueado.empty()) {
                    bloqueadoSuspendido();
                    maxProcesos();
                    imprimirListos();
                    imprimirBloqueados();
                    imprimirMemoria();
                }
                break;
            } else if(ch == 114 or ch == 82) {
                /// Regresa
                regresaBloqueado();
                break;
            } else if(ch == 116 or ch == 84) {
                imprimirTiemposActual();
            } else {
                for(unsigned int i = 0; i < bloqueado.size(); i++) {
                    bloqueado.front().sustraerTBloqueo();
                    if(bloqueado.front().getTBloqueo() < 0){
                        asignarEstado(bloqueado.front().getId(), 'L');
                        listo.push(bloqueado.front());
                        bloqueado.pop();
                        i--;
                        f = true;
                        ch = -1;
                    }
                    else{
                        bloqueado.push(bloqueado.front());
                        bloqueado.pop();
                    }
                }
                imprimirBloqueados();
                imprimirMemoria();
                cout << "\033[2;80H" << ++tiempoTotal << endl;
                sleep(1);
            }
        }
    } else if(nuevo.empty() and listo.empty() and bloqueado.empty() and ejecucion.empty()) {
        while(true) {
            maxProcesos();
            cout << "\033[2;80H" << ++tiempoTotal << endl;
            ch = kbhit();
            if(ch == 112 or ch == 80 or ch == 109 or ch == 77) {
                pausaKbhit();
            } else if(ch == 78 or ch == 110) {
                nuevoProceso();
                break;
            } else if(ch == 114 or ch == 82) {
                regresaBloqueado();
                break;
            } else if(ch == 116 or ch == 84) {
                imprimirTiemposActual();
            }
            sleep(1);
        }
    } else {
        bool f = false;
        while(ch != 0 and ch != 1 and ch != 2 and ch != 3 and f == false) {
            /* Impresión del tiempo transcurrido, tiempo total e incremento del tiempo total */
            maxProcesos();
            imprimirListos();
            imprimirBloqueados();
            imprimirEjecucion();
            imprimirMemoria();
            sleep(1);
            ch = kbhit();
            if(ch == 105 or ch == 73) {
                ch = 0;
            } else if(ch == 101 or ch == 69) {
                ch = 1;
            } else if(ch == 112 or ch == 80 or ch == 77 or ch == 109) {
                pausaKbhit();
            } else if(ch == 115 or ch == 83) {
                /// Bloqueado suspendido
                if(!bloqueado.empty()) {
                    bloqueadoSuspendido();
                }
                break;
            } else if(ch == 114 or ch == 82) {
                /// Regresa
                regresaBloqueado();
                break;
            } else if(ch == 78 or ch == 110) {
                nuevoProceso();
                break;
            } else if(ch == 116 or ch == 84) {
                imprimirTiemposActual();
            } else {
                // Condicionante para trabajar bajo el quantum
                if(contQuantum != quantum) {
                    // En caso de terminar el proceso CH = 2
                    if(ejecucion.front().getTRestante() <= 0) {
                        ch = 2;
                    } else {
                        // Se hacen las sustracciones y adhisiones a los tiempos correspondientes
                        cout << "\033[2;80H" << ++tiempoTotal << endl;
                        cout << "\033[2;100H" << ++contQuantum << endl;
                        ejecucion.front().setTServicio(ejecucion.front().getTServicio() + 1);
                        ejecucion.front().sustraerTRestante();
                        ejecucion.front().adherirTTranscurrido();
                        if(ejecucion.front().getTRestante() <= 0) {
                            ch = 2;
                            imprimirEjecucion();
                            sleep(0);
                        } else {
                            ch = -1;
                        }
                        // Impresión de cualquier proceso en bloqueado
                        if(!bloqueado.empty()) {
                            for(unsigned int i = 0; i < bloqueado.size(); i++) {
                                bloqueado.front().sustraerTBloqueo();
                                if(bloqueado.front().getTBloqueo() < 0){
                                    asignarEstado(bloqueado.front().getId(), 'L');
                                    listo.push(bloqueado.front());
                                    bloqueado.pop();
                                    i--;
                                    f = true;
                                }
                                else{
                                    bloqueado.push(bloqueado.front());
                                    bloqueado.pop();
                                }
                            }
                            imprimirBloqueados();
                            imprimirMemoria();
                            cout << "\033[2;80H" << ++tiempoTotal << endl;
                        }
                    }
                } else {
                    ch = 3;
                }
            }
        }
    }
    return ch;
}

void Interfaz::imprimirTiemposActual() {
    system(CLEAR);
    unsigned int i = 0;
    cout << "+-----+------------------+-----------------+---------------+------------+-----------+----------------+--------------+-------------+-----------+------------+-----+------+" << endl;
    cout << "| ID  |    Operación     |    Resultado    | Estado actual | T.Restante | T.Llegada | T.Finalización | T. Respuesta | T. Servicio | T. Espera | T. Retorno | TME | Size |" << endl;
    cout << "+-----+------------------+-----------------+---------------+------------+-----------+----------------+--------------+-------------+-----------+------------+-----+------+" << endl;
    datosTiempoActual(nuevo, "Nuevo", i);
    datosTiempoActual(listo, "Listo", i);
    datosTiempoActual(ejecucion, "Ejecucion", i);
    datosTiempoActual(bloqueado, "Bloqueado", i);
    datosTiempoActual(terminado, "Terminado", i);
    cout << "+-----+------------------+-----------------+---------------+------------+-----------+----------------+--------------+-------------+-----------+------------+-----+------+" << endl;
    cout << "\033[" << 4 + i << ";1H" << endl << endl;
    cout << "Presione [c] para continuar...";
    while(true) {
        int ch = kbhit();
        if(ch == 99 or ch == 67) {
            break;
        }
    }
    system(CLEAR);
    pantallaDeProcesos();
    cout << "\033[2;21H    " << endl;
    cout << "\033[2;21H" << nuevo.size() << endl;
    cout << "\033[2;39H    " << endl;
    cout << "\033[2;54H    " << endl;
    if(nuevo.empty()) {
        cout << "\033[2;39H0" << endl;
        cout << "\033[2;54H0" << endl;
    } else {
        cout << "\033[2;39H" << nuevo.front().getId() << endl;
        cout << "\033[2;54H" << nuevo.front().getTamanio() << endl;

    }
    //
    cout << "\033[32;29H    " << endl;
    cout << "\033[32;29H" << mLibre << endl;
    cout << "\033[32;49H    "<< endl;
    cout << "\033[32;49H" << mUsada << endl;
    cout << "\033[32;69H    "<< endl;
    cout << "\033[32;69H" << pagDis << endl;
    cout << "\033[2;80H" << tiempoTotal << endl;
    cout << "\033[32;94H   " << endl;
    cout << "\033[32;94H" << cSuspendidos << endl;
    ///
    ifstream fin("Bloqueado-Suspendido.txt");
    Proceso p;
    string str;
    if(fin.good()) {
        getline(fin, str, '|');
        p.setId(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setN1(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setN2(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setOperador(str);
        getline(fin, str, '|');
        p.setTME(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setResultado(str);
        getline(fin, str, '|');
        p.setTLlegada(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTFinalizacion(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTRetorno(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTRespuesta(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTEspera(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTServicio(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTTranscurrido(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTRestante(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTBloqueo(atoi(str.c_str()));
        getline(fin, str, '|');
        getline(fin, str, '|');
        p.setTamanio(atoi(str.c_str()));
        getline(fin, str, '\n');
        p.setTEspera(p.getTEspera() + (tiempoTotal - atoi(str.c_str())) );
        cout << "\033[32;109H   " << endl;
        cout << "\033[32;109H" << p.getId() << endl;
        cout << "\033[32;124H   " << endl;
        cout << "\033[32;124H" << p.getTamanio() << endl;
    }
    fin.close();
    imprimirListos();
    imprimirEjecucion();
    imprimirTerminados();
    imprimirBloqueados();
    imprimirMemoria();
}

void Interfaz::datosTiempoActual(queue<Proceso>& q, const string& n, unsigned int &i) {
    // Impresión para la cola recibida (NUEVO, LISTO, EJECUCION, BLOQUEADO, TERMINADO)
    for(unsigned int j = 0; j < q.size(); i++, j++) {
        cout << "\033[" << 4 + i << ";1H|     |                  |                 |               |            |           |                |              |             |           |            |     |      |" << endl;
        cout << "\033[" << 4 + i << ";3H" << q.front().getId() << endl;
        cout << "\033[" << 4 + i << ";9H" << q.front().getOperacion() << endl;
        cout << "\033[" << 4 + i << ";158H" << q.front().getTME() << endl;
        cout << "\033[" << 4 + i << ";165H" << q.front().getTamanio() << endl;
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

void Interfaz::liberarMemoria(const int& index) {
    for(int i = 0; i < 34; i++) {
        if(m[i].idProceso == index) {
            mLibre += m[i].tUsado;
            mUsada -= m[i].tUsado;
            pagDis++;
            m[i].tUsado = 0;
            m[i].estado = '-';
            m[i].idProceso = 0;
            m[i].ocupado = false;
        }
    }
}

void Interfaz::asignarEstado(const int& index, const char& estado) {
    for(int i = 0; i < 34; i++) {
        if(m[i].idProceso == index) {
            m[i].estado = estado;
        }
    }
}

void Interfaz::imprimirTiemposFinal() {
    system(CLEAR);
    cout << "+-----+------------------+-----------------+-----------+----------------+--------------+-------------+-----------+------------+-----+------+" << endl;
    cout << "| ID  |    Operación     |    Resultado    | T.Llegada | T.Finalización | T. Respuesta | T. Servicio | T. Espera | T. Retorno | TME | Size |" << endl;
    cout << "+-----+------------------+-----------------+-----------+----------------+--------------+-------------+-----------+------------+-----+------+" << endl;
    for(unsigned int i = 0; i < terminado.size(); i++) {
        cout << "\033[" << 4 + i << ";1H|     |                  |                 |           |                |              |             |           |            |     |      |" << endl;
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
        cout << "\033[" << 4 + i << ";136H" << terminado.front().getTamanio() << endl;
        terminado.push(terminado.front());
        terminado.pop();
    }
    cout << "\033[" << 4 + terminado.size() << ";1H+-----+------------------+-----------------+-----------+----------------+--------------+-------------+-----------+------------+-----+------+" << endl;

    cout << "\033[32;94H   " << endl;
    cout << "\033[32;94H" << cSuspendidos << endl;
}

void Interfaz::imprimirMemoria() {
    //
    cout << "\033[32;29H    " << endl;
    cout << "\033[32;29H" << mLibre << endl;
    cout << "\033[32;49H    "<< endl;
    cout << "\033[32;49H" << mUsada << endl;
    cout << "\033[32;69H    "<< endl;
    cout << "\033[32;69H" << pagDis << endl;
    for(int i = 0; i < 34; i++) {
        cout << "\033[38;" << 24 + (i * 5) << "H   " << endl;
        cout << "\033[38;" << 24 + (i * 5) << "H" << m[i].tUsado << endl;
        cout << "\033[40;" << 24 + (i * 5) << "H   " << endl;
        cout << "\033[40;" << 24 + (i * 5) << "H" << m[i].estado << endl;
        cout << "\033[46;" << 24 + (i * 5) << "H   " << endl;
        cout << "\033[46;" << 24 + (i * 5) << "H" << m[i].idProceso << endl;
    }
}

void Interfaz::pausaProceso() {
    cout << "\033[50;1H" << endl << endl;
    cout << "Presione [enter] para continuar...";
    while(getchar() != 10);
    cout << "\033[50;1H" << endl << endl;
    cout << "                                   " << endl;
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

void Interfaz::bloqueadoSuspendido() {
    ///
    fstream fout("Bloqueado-Suspendido.txt", ios::app);
    fout << bloqueado.front().toString() << "|" << tiempoTotal << endl;
    fout.close();
    liberarMemoria(bloqueado.front().getId());
    bloqueado.pop();
    ///
    ifstream fin("Bloqueado-Suspendido.txt");
    Proceso p;
    string str;
    if(fin.good()) {
        getline(fin, str, '|');
        p.setId(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setN1(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setN2(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setOperador(str);
        getline(fin, str, '|');
        p.setTME(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setResultado(str);
        getline(fin, str, '|');
        p.setTLlegada(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTFinalizacion(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTRetorno(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTRespuesta(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTEspera(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTServicio(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTTranscurrido(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTRestante(atoi(str.c_str()));
        getline(fin, str, '|');
        p.setTBloqueo(atoi(str.c_str()));
        getline(fin, str, '|');
        getline(fin, str, '|');
        p.setTamanio(atoi(str.c_str()));
        getline(fin, str, '\n');
        p.setTEspera(p.getTEspera() + (tiempoTotal - atoi(str.c_str())) );
        cout << "\033[32;109H   " << endl;
        cout << "\033[32;109H" << p.getId() << endl;
        cout << "\033[32;124H   " << endl;
        cout << "\033[32;124H" << p.getTamanio() << endl;
    }
    fin.close();
    cout << "\033[32;94H   " << endl;
    cout << "\033[32;94H" << ++cSuspendidos << endl;
}

void Interfaz::regresaBloqueado() {
    ifstream fileIn("Bloqueado-Suspendido.txt");
    Proceso p;
    string str;
    if(fileIn.good()) {
        getline(fileIn, str, '|');
        p.setId(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setN1(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setN2(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setOperador(str);
        getline(fileIn, str, '|');
        p.setTME(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setResultado(str);
        getline(fileIn, str, '|');
        p.setTLlegada(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setTFinalizacion(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setTRetorno(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setTRespuesta(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setTEspera(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setTServicio(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setTTranscurrido(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setTRestante(atoi(str.c_str()));
        getline(fileIn, str, '|');
        p.setTBloqueo(atoi(str.c_str()));
        getline(fileIn, str, '|');
        getline(fileIn, str, '|');
        p.setTamanio(atoi(str.c_str()));
        getline(fileIn, str, '\n');
        p.setTEspera(p.getTEspera() + (tiempoTotal - atoi(str.c_str())) );
    }
    fileIn.close();
    ///
    if(p.getId() != -1111) {
        int noPaginas = (p.getTamanio() * 10)/5;
        if(noPaginas%5 == 0) {
            noPaginas = (noPaginas/10);
        } else {
            noPaginas = (noPaginas/10) + 1;
        }
        if(pagDis >= noPaginas) {
            mLibre -= p.getTamanio();
            mUsada += p.getTamanio();
            pagDis -= noPaginas;
            for(int i = 0, tamanio = p.getTamanio(); i < 34 and noPaginas > 0; i++) {
                if(m[i].ocupado == false) {
                    noPaginas--;
                    m[i].ocupado = true;
                    m[i].estado = 'B';
                    m[i].idProceso = p.getId();
                    if(tamanio > 5) {
                        tamanio -= 5;
                        m[i].tUsado += 5;
                    } else {
                        m[i].tUsado += tamanio;
                        break;
                    }
                }
            }
            ///
            ifstream fin("Bloqueado-Suspendido.txt");
            ofstream fout("temporal.txt");
            bool f = false;
            if(fin.good()) {
                int i = 0;
                while(!fin.eof()) {
                    f = true;
                    getline(fin, str, '|');
                    p.setId(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setN1(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setN2(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setOperador(str);
                    getline(fin, str, '|');
                    p.setTME(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setResultado(str);
                    getline(fin, str, '|');
                    p.setTLlegada(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setTFinalizacion(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setTRetorno(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setTRespuesta(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setTEspera(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setTServicio(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setTTranscurrido(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setTRestante(atoi(str.c_str()));
                    getline(fin, str, '|');
                    p.setTBloqueo(atoi(str.c_str()));
                    getline(fin, str, '|');
                    getline(fin, str, '|');
                    p.setTamanio(atoi(str.c_str()));
                    getline(fin, str, '\n');
                    p.setTEspera(p.getTEspera() + (tiempoTotal - atoi(str.c_str())) );
                    if(fin.eof()) {
                        break;
                    }
                    if(i == 0) {
                        bloqueado.push(p);
                        cout << "\033[32;124H   " << endl;
                        cout << "\033[32;109H   " << endl;
                    } else if(i == 1) {
                        ///
                        cout << "\033[32;109H" << p.getId() << endl;
                        cout << "\033[32;124H" << p.getTamanio() << endl;
                        fout << p.toString();
                    } else {
                        fout << p.toString();
                    }
                    i++;
                }
            }
            fin.close();
            fout.close();
            remove("Bloqueado-Suspendido.txt");
            rename("temporal.txt", "Bloqueado-Suspendido.txt");
            if(cSuspendidos > 0){
                cout << "\033[32;94H   " << endl;
                cout << "\033[32;94H" << --cSuspendidos << endl;
            }
            else{
                cout << "\033[32;94H   " << endl;
                cout << "\033[32;94H" << cSuspendidos << endl;
            }
            if(f == false) {
                cout << "\033[32;109H   " << endl;
                cout << "\033[32;124H   " << endl;
                cout << "\033[32;109H0" << endl;
                cout << "\033[32;124H0" << endl;
            }
            imprimirListos();
            imprimirMemoria();
            sleep(1);
        }
    }
}

void Interfaz::nuevoProceso() {
    generarProcesos(1);
    maxProcesos();
    imprimirListos();
    imprimirMemoria();
    cout << "\033[2;21H    " << endl;
    cout << "\033[2;21H" << nuevo.size() << endl;
    cout << "\033[2;39H    " << endl;
    cout << "\033[2;54H    " << endl;
    if(nuevo.empty()) {
        cout << "\033[2;39H0" << endl;
        cout << "\033[2;54H0" << endl;
    } else {
        cout << "\033[2;39H" << nuevo.front().getId() << endl;
        cout << "\033[2;54H" << nuevo.front().getTamanio() << endl;
    }
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
    cout << "\033[50;1H¡Pausa! Presione [c] para continuar..." << endl;
    int ch = 0;
    while (getchar() != EOF);
    while(true) {
        ch = kbhit();
        if(ch == 99 or ch == 67) {
            cout << "\033[50;1H                                      " << endl;
            cout << "\033[50;1H¡Continuemos!                        " << endl;
            sleep(1);
            cout << "\033[50;1H                                      " << endl;
            break;
        }
    }
}
