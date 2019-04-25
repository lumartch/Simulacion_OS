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
        queue<Proceso> listo;
        queue<Proceso> ejecucion;
        queue<Proceso> bloqueado;
        queue<Proceso> terminado;
        int index;
        int tiempoTotal;
        int procesoTotal;
        int quantum;
        int contQuantum;
        struct Memoria{
            int tUsado = 0;
            char estado = '-';
            int idProceso = 0;
            bool ocupado = false;
        } m[34];
        int mLibre;
        int mUsada;
        int pagDis;
        void pantallaDeProcesos();
        void generarProcesos(const int &cProcesos);
        void maxProcesos();
        void imprimirListos();
        void imprimirEjecucion();
        void imprimirBloqueados();
        void imprimirTerminados();
        void imprimirMemoria();
        int procesarDatos();
        void imprimirTiemposFinal();
        void imprimirTiemposActual();
        void datosTiempoActual(queue<Proceso>& q, const string &n, unsigned int &i);
        void liberarMemoria(const int &index);
        void asignarEstado(const int& index, const char& estado);
        void pausa();
        void pausaProceso();
        bool checkNumInt(const string &cadena);
        int kbhit(void);
        void pausaKbhit();
    };

#endif // INTERFAZ_H
