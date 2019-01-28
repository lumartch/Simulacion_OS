#ifndef PROCESO_H
#define PROCESO_H

#include <string>

class Proceso
{
    public:
        Proceso();
        virtual ~Proceso();
        void setId(const int & id);
        void setProgramador(const std::string&programador);
        void setOperacion(const std::string&operacion);
        void setTiempoEstimado(const int & tiempoEstimado);
        int getId();
        std::string getProgramador();
        std::string getOperacion();
        int getTiempoEstimado();
    private:
        int id;
        std::string programador;
        std::string operacion;
        int tiempoEstimado;
};

#endif // PROCESO_H
