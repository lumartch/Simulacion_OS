#include "proceso.h"

Proceso::Proceso() {
    id = -1111;
    n1 = 0;
    n2 = 0;
    operador = "";
    tLlegada = 0;
    tFinalizacion = 0;
    tRetorno = 0;
    tRespuesta = 0;
    tEspera = 0;
    tServicio = 0;
    tTranscurrido = 0;
    tRestante = 0;
    tBloqueado = 0;
    tResFlag = false;
}

Proceso::~Proceso() {
    //dtor
}

void Proceso::setId(const int& id) {
    this->id = id;
}

void Proceso::setN1(const int& n1) {
    this->n1 = n1;
}

void Proceso::setN2(const int& n2) {
    this->n2 = n2;
}

void Proceso::setOperador(const std::string& operador) {
    this->operador = operador;
}

void Proceso::setResultado(const std::string& resultado) {
    this->resultado = resultado;
}

void Proceso::setTLlegada(const int& tLlegada) {
    this->tLlegada = tLlegada;
}

void Proceso::setTFinalizacion(const int& tFinalizacion) {
    this->tFinalizacion = tFinalizacion;
}

void Proceso::setTRetorno(const int& tRetorno) {
    this->tRetorno = tRetorno;
}

void Proceso::setTRespuesta(const int& tRespuesta) {
    this->tRespuesta = tRespuesta;
    this->tResFlag = true;
}

void Proceso::setTEspera(const int& tEspera) {
    this->tEspera = tEspera;
}

void Proceso::setTServicio(const int& tServicio) {
    this->tServicio = tServicio;
    this->tRestante = tServicio;
}

void Proceso::setTBloqueo(const int & tBloqueado) {
    this->tBloqueado = tBloqueado;
}

void Proceso::adherirTTranscurrido() {
    tTranscurrido++;
}

void Proceso::sustraerTRestante() {
    tRestante--;
}

void Proceso::sustraerTBloqueo() {
    tBloqueado--;
}

int Proceso::getId() {
    return id;
}

int Proceso::getN1() {
    return n1;
}

int Proceso::getN2() {
    return n2;
}

std::string Proceso::getOperador() {
    return operador;
}

std::string Proceso::getResultado() {
    return resultado;
}

int Proceso::getTLlegada() {
    return tLlegada;
}

int Proceso::getTFinalizacion() {
    return tFinalizacion;
}

int Proceso::getTRetorno() {
    return tRetorno;
}

int Proceso::getTRespuesta() {
    return tRespuesta;
}

int Proceso::getTEspera() {
    return tEspera;
}

int Proceso::getTServicio() {
    return tServicio;
}

int Proceso::getTTranscurrido() {
    return tTranscurrido;
}

int Proceso::getTRestante() {
    return tRestante;
}

int Proceso::getTBloqueo() {
    return tBloqueado;
}

bool Proceso::getTResFlag() {
    return tResFlag;
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


