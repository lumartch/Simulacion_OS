#ifndef INTERFAZ_H
#define INTERFAZ_H

#ifndef WIN_32
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif // WIN_32

#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
#include <regex>
#include <ncurses.h>

using namespace std;

class Interfaz {
    public:
        Interfaz();
        virtual ~Interfaz();
        void menuInicio();
        void procesamientoLotes();

    private:
        int cantLotes;
        int loteActual;
        int lotesPendientes;
        int tiempoTotal;
        int tiempoTranscurrido;
        int tiempoRestante;
        void proceso();
        void contador();
        void pausa();
        void pausaProceso();
        void limpiarTablaProceso();
        bool checkNumero(const string &cadena);

    };

#endif // INTERFAZ_H
