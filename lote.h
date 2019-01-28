#ifndef LOTE_H
#define LOTE_H

#include "proceso.h"

class Lote {
    public:
        Lote();
        virtual ~Lote();
        Proceso& getProceso(const int pos);
        void setProceso(const Proceso&pro, const int pos);
    private:
        Proceso p[3];
};

#endif // LOTE_H
