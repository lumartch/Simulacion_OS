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

void Proceso::setTME(const int& tme) {
    this->tme = tme;
    this->tRestante = tme;
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
}

void Proceso::setTBloqueo(const int & tBloqueado) {
    this->tBloqueado = tBloqueado;
}

void Proceso::setTTranscurrido(const int& tTranscurrido) {
    this->tTranscurrido = tTranscurrido;
}

void Proceso::setTRestante(const int& tRestante) {
    this->tRestante = tRestante;
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

int Proceso::getTME() {
    return tme;
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

void Proceso::setTPaginas(const int& tPaginas) {
    this->tPaginas = tPaginas;
}

int Proceso::getTPaginas() {
    return tPaginas;
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

void Proceso::setTamanio(const int& tamanio) {
    this->tamanio = tamanio;
}

int Proceso::getTamanio() {
    return tamanio;
}

std::string Proceso::toString() {
    std::string r = "";
    r += std::to_string(id) + "|" + std::to_string(n1) + "|" + std::to_string(n2) + "|" + operador + "|" + std::to_string(tme) + "|" + resultado + "|";
    r += std::to_string(tLlegada) + "|" + std::to_string(tFinalizacion) + "|" + std::to_string(tRetorno) + "|" + std::to_string(tRespuesta) + "|";
    r += std::to_string(tEspera) + "|" + std::to_string(tServicio) + "|" + std::to_string(tTranscurrido) + "|" + std::to_string(tRestante) + "|";
    r += std::to_string(tBloqueado) + "|" + std::to_string(tResFlag) + "|" + std::to_string(tamanio);
    return r;
}
