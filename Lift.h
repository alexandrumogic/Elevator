#ifndef LIFT_H
#define LIFT_H
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class Lift
{
    public:
        Lift(int, int);
        void afisare();
        int timp(int destinatie);
        int getNivelCurent();
        int getTimpPanaLaUltimaComanda();
        int getUltimaComanda();
        string getStare();
        bool areComenzi();
        void avansare();
        void adaugareComanda(int, int);
        virtual ~Lift();
    protected:
    private:
        int nivelCurent, nrEtaje, nrLift;
        string stare, stareAnterioara;
        list<int> comenzi;
};

#endif // LIFT_H
