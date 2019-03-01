#ifndef PROCESO_H
#define PROCESO_H

#include <string>
#include <sstream>
#include <iomanip>

class Proceso {
    public:
        Proceso();
        virtual ~Proceso();
        void setId(const int & id);
        void setN1(const int & n1);
        void setN2(const int & n2);
        void setOperador(const std::string&operador);
        void setTME(const int & tme);
        void setResultado(const std::string& resultado);
        void setTLlegada(const int &tLlegada);
        void setTFinalizacion(const int & tFinalizacion);
        void setTRetorno(const int & tRetorno);
        void setTRespuesta(const int & tRespuesta);
        void setTEspera(const int & tEspera);
        void setTServicio(const int & tServicio);
        void setTBloqueo(const int & tBloqueado);
        void adherirTTranscurrido();
        void sustraerTRestante();
        void sustraerTBloqueo();
        int getId();
        int getN1();
        int getN2();
        std::string getOperador();
        int getTME();
        std::string getResultado();
        std::string getOperacion();
        int getTLlegada();
        int getTFinalizacion();
        int getTRetorno();
        int getTRespuesta();
        int getTEspera();
        int getTServicio();
        int getTTranscurrido();
        int getTRestante();
        int getTBloqueo();
        bool getTResFlag();
    private:
        int id;
        int n1;
        int n2;
        std::string operador;
        int tme;
        std::string resultado;
        int tLlegada;
        int tFinalizacion;
        int tRetorno;
        int tRespuesta;
        int tEspera;
        int tServicio;
        int tTranscurrido;
        int tRestante;
        int tBloqueado;
        bool tResFlag;
};

#endif // PROCESO_H
