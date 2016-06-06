#ifndef CLADIRE_H
#define CLADIRE_H
#define MAX 5
#include "Lift.h"
#include <fstream>



class Cladire
{
    public:
        Cladire();
        void ruleazaLifturi();
        virtual ~Cladire();
    protected:
    private:
        void comanda(int, int);
        void avanseazaEtaj();
        bool unulDintreLifturiAreComanda();
        bool toateLifturileSuntStationate();
        int nrEtaje, nrLifturi;
        Lift * lifturi[MAX];
        ifstream intrari;
};

#endif // CLADIRE_H
