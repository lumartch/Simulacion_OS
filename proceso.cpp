#include "proceso.h"

Proceso::Proceso() {
    id = -1111;
    programador = "";
    n1 = 0;
    n2 = 0;
    operador = "";
    tiempoEstimado = 0;
}

Proceso::~Proceso() {
    //dtor
}

void Proceso::setId(const int& id) {
    this->id = id;
}

void Proceso::setProgramador(const std::string& programador) {
    this->programador = programador;
}

void Proceso::setN1(const float& n1) {
    this->n1 = n1;
}

void Proceso::setN2(const float& n2) {
    this->n2 = n2;
}


void Proceso::setOperador(const std::string& operador) {
    this->operador = operador;
}

void Proceso::setTiempoEstimado(const int& tiempoEstimado) {
    this->tiempoEstimado = tiempoEstimado;
}

int Proceso::getId() {
    return id;
}

std::string Proceso::getProgramador() {
    return programador;
}

float Proceso::getN1() {
    return n1;
}

float Proceso::getN2() {
    return n2;
}

std::string Proceso::getOperador() {
    return operador;
}

int Proceso::getTiempoEstimado() {
    return tiempoEstimado;
}

std::string Proceso::getOperacion() {
    std::string s;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << n1;
    stream << " " << operador << " ";
    stream << std::fixed << std::setprecision(2) << n2;
    s = stream.str();
    return s;
}


