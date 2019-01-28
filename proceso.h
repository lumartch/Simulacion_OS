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
        void setProgramador(const std::string&programador);
        void setN1(const float & n1);
        void setN2(const float & n2);
        void setOperador(const std::string&operador);
        void setTiempoEstimado(const int & tiempoEstimado);
        int getId();
        std::string getProgramador();
        float getN1();
        float getN2();
        std::string getOperador();
        int getTiempoEstimado();
        std::string getOperacion();
    private:
        int id;
        std::string programador;
        float n1;
        float n2;
        std::string operador;
        int tiempoEstimado;
};

#endif // PROCESO_H
