#include "lote.h"

Lote::Lote() {
    //ctor
}

Lote::~Lote() {
    //dtor
}

Proceso& Lote::operator[](const int pos) {
    return p[pos];
}


void Lote::setProceso(const Proceso&pro, const int pos) {
    p[pos] = pro;
}
