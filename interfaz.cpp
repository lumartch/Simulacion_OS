#include "interfaz.h"

Interfaz::Interfaz() {
    procesoActual = 0;
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
    procesoTotal = atoi(cadena.c_str());
    system(CLEAR);
    generarProcesos();
    pantallaDeProcesos();
    unsigned int maxProcesos;
    while(int(terminado.size()) != (procesoActual + procesoTotal)) {
        cout << "\033[2;21H" << nuevo.size() << endl;
        cout << "\033[2;45H" << tiempoTotal << endl;
        maxProcesos = listo.size() + bloqueado.size() + ejecucion.size();
        if(maxProcesos < 3) {
            Proceso p = nuevo.front();
            listo.push(p);
            nuevo.pop();
            cout << "\033[2;21H" << nuevo.size() << endl;
            sleep(1);
        }
        maxProcesos = listo.size() + bloqueado.size() + ejecucion.size();
        while(true) {
            imprimirBloqueados();
            limpiarEjecucion();
            imprimirListos();
            sleep(1);
            int ch = procesarDatos();
            if(ch == 0){
                /*Interrupcion*/
                break;
            }
            else if(ch == 1){
                /*ERROR*/
                break;
            }
            else if(ch == 2){
                /*Terminado*/
                break;
            }
            else{

            }
        }
    }
    cout << "\033[15;1H" << endl << endl;
    cout << "Presione [enter] para continuar...";
    while(true) {
        if(kbhit() == 10) {
            break;
        }
    }
}

int Interfaz::procesarDatos() {
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
    return -1;
}

void Interfaz::generarProcesos() {
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
    for(int i = 0; i < 4; i++){
        cout << "\033["<< 6 + i << ";1H                                 " << endl;
    }
    // Imprime los valores de la cola
    for(unsigned int i = 0; i < listo.size(); i++){
        Proceso p = listo.front();
        listo.push(p);
        listo.pop();
        cout << "\033["<< 6 + i << ";1H|      |         |               |" << endl;
        cout << "\033["<< 6 + i << ";2H" << p.getId() << endl;
        cout << "\033["<< 6 + i << ";10H" << p.getTServicio() << endl;
        cout << "\033["<< 6 + i << ";20H" << p.getTRestante() << endl;
        cout << "\033["<< 7 + i << ";1H+------+---------+---------------+" << endl;
    }
    sleep(1);
}

void Interfaz::imprimirEjecucion() {
    // Código para limpiar los campos de ejecucion
    for(int i = 0; i < 4; i++){
        cout << "\033[" << 6 + i << ";53H                             " << endl;
    }
    // Código para imprimir el proceso en el FRONT de la cola listos
    if(!listo.empty()){
        if(ejecucion.empty()){
            Proceso p = listo.front();
            ejecucion.push(p);
            listo.pop();
            cout <<"\033[" << 6 << ";54H" << p.getId() << endl;
            cout <<"\033[" << 7 << ";54H" << p.getOperacion() << endl;
            cout <<"\033[" << 8 << ";54H" << p.getTRestante() << endl;
            cout <<"\033[" << 9 << ";54H" << p.getTTranscurrido() << endl;
        }
    }
    sleep(1);
}

void Interfaz::imprimirBloqueados() {
    // Código para limpiar los campos de bloqueo
    for(int i = 0; i < 4; i++){
        cout << "\033[" << 13 + i << ";35H                                  " << endl;
    }
    // Código para imprimir los campos de bloqueo
    for(unsigned int i = 0; i < bloqueado.size(); i++){
        Proceso p = bloqueado.front();
        bloqueado.push(p);
        bloqueado.pop();
        cout << "\033[" << 13 + i << ";35H|               |                |" << endl;
        cout << "\033[" << 13 + i << ";36H" << p.getId() << endl;
        cout << "\033[" << 13 + i << ";51H" << p.getTBloqueo() << endl;
        cout << "\033[" << 14 + i << ";35H+---------------+----------------+" << endl;
    }
    sleep(1);
}

void Interfaz::imprimirTerminados() {
    /* Terminados */
    cout << "\033[" << 8 + procesoActual << ";88H                                                                                             " << endl;
    cout << "\033[" << 8 + procesoActual << ";87H|      |                                                          |                           |" << endl;
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
