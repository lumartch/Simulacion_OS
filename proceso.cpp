#include "proceso.h"

Proceso::Proceso() {
    id = 0;
    programador = "";
    operacion = "";
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

void Proceso::setOperacion(const std::string& operacion) {
    this->operacion = operacion;
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

std::string Proceso::getOperacion() {
    return operacion;
}

int Proceso::getTiempoEstimado() {
    return tiempoEstimado;
}

