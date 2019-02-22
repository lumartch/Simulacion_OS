#ifndef INTERFAZ_H
#define INTERFAZ_H

#ifndef WIN_32
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif // WIN_32

#include <iostream>
/* TDA para los datos generados */
#include <queue>
#include <vector>
/* Herramientas para el manejo de interfaz */
#include <ctime>
#include <string>
#include <regex>
#include <unistd.h>
/* Librerías necesarias para el funcionamiento de kbhit */
#include <termios.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
/* Tipo de dato creados */
#include "lote.h"

using namespace std;

class Interfaz {
    public:
        Interfaz();
        virtual ~Interfaz();
        void menuInicio();
    private:
        queue<Proceso> nuevo;
        vector<Proceso> listo;
        queue<Proceso> ejecucion;
        vector<Proceso> bloqueado;
        vector<Proceso> terminado;
        int index;
        int tiempoTotal;
        int procesoActual;
        int procesoTotal;
        void generarProcesos();
        void pantallaDeProcesos();
        void limpiarEjecucion();
        void imprimirListos();
        void imprimirBloqueados();
        void tabulacionTerminados();
        int procesarDatos();
        void pausa();
        void pausaProceso();
        bool checkNumInt(const string &cadena);
        int kbhit(void);
        void pausaKbhit();
    };

#endif // INTERFAZ_H
