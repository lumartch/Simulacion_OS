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
        queue<Lote> cola;
        vector<Proceso> lista;
        int loteActual;
        int lotesPendientes;
        int tiempoTotal;
        int tiempoTranscurrido;
        int tiempoRestante;
        int procesoActual;
        int procesoTotal;
        void generarProcesos();
        void procesamientoLotes();
        void imprimirLote();
        void agregarTabulacionTerminado(const int &cant);
        void limpiarTabulacionLote();
        int procesarDatos(unsigned int &index);
        void tiempoEjecucionTotal();
        void pausa();
        void pausaProceso();
        void limpiarTablaProceso();
        bool checkNumInt(const string &cadena);
        int kbhit(void);
        void pausaKbhit();
    };

#endif // INTERFAZ_H
