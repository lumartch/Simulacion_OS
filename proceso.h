#ifndef PROCESO_H
#define PROCESO_H

#include <string>

class Proceso {
    public:
        Proceso();
        virtual ~Proceso();
        void setId(const int & id);
        void setProgramador(const std::string&programador);
        void setN1(const int & n1);
        void setN2(const int & n2);
        void setOperador(const std::string&operador);
        void setTiempoEstimado(const int & tiempoEstimado);
        int getId();
        std::string getProgramador();
        int getN1();
        int getN2();
        std::string getOperador();
        int getTiempoEstimado();
        std::string getOperacion();
    private:
        int id;
        std::string programador;
        int n1;
        int n2;
        std::string operador;
        int tiempoEstimado;
};

#endif // PROCESO_H
