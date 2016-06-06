#include "Cladire.h"

Cladire::Cladire()
{
    // Citim numar etaje si numar lifturi
    intrari.open("intrari.txt");
    intrari >> nrEtaje >> nrLifturi;
    intrari.close();

    // Cream obiectele lift
    for (int i=0;i < nrLifturi; i++) {
        lifturi[i] = new Lift(i+1, nrEtaje);
    }
}

Cladire::~Cladire()
{
    //dtor
}

void Cladire::comanda(int etajComanda, int etajDestinatie)
{
    Lift * aux;
    int bestTime = nrEtaje;
    int calcul;
    string directia;

    if (etajComanda < etajDestinatie) directia = "URCARE";
    else directia = "COBORARE";

    for (int i=0; i < nrLifturi; i++) {
        // Daca liftul este stationat la etajul comandat
        if ((lifturi[i]->getNivelCurent() == etajComanda) && (lifturi[i]->getStare() == "STATIONARE")) {
            lifturi[i]->adaugareComanda(etajComanda, etajDestinatie);
            return;
        } else {
            // Daca liftul este stationat la alt etaj
            if (lifturi[i]->getStare() == "STATIONARE") {
                calcul = abs(lifturi[i]->getNivelCurent() - etajComanda);
                if (calcul < bestTime) {
                    bestTime = calcul;
                    aux = lifturi[i]; }
            // Daca liftul este in miscare
            } else {
                if (((directia == "COBORARE") && (lifturi[i]->getStare() == "COBORARE") && (lifturi[i]->getNivelCurent() > etajComanda))) {
                    calcul = abs(lifturi[i]->getNivelCurent() - etajComanda);
                    if (calcul < bestTime) {
                        bestTime = calcul;
                        aux = lifturi[i]; }
                } else if (((directia == "URCARE") && (lifturi[i]->getStare() == "URCARE") && (lifturi[i]->getNivelCurent() < etajComanda))) {
                    calcul = abs(lifturi[i]->getNivelCurent() - etajComanda);
                    if (calcul < bestTime) {
                        bestTime = calcul;
                        aux = lifturi[i]; }
                }
                    // Daca liftul este oprit la un etaj
                else {
                    calcul = abs(lifturi[i]->getTimpPanaLaUltimaComanda() + lifturi[i]->getUltimaComanda() - etajComanda);
                    if (calcul < bestTime) {
                        bestTime = calcul;
                        aux = lifturi[i]; }
                }
            }
        }
    }

    aux->adaugareComanda(etajComanda,etajDestinatie);
}

bool Cladire::unulDintreLifturiAreComanda()
{
    for (int i=0;i<nrLifturi;i++) {
        if (lifturi[i]->areComenzi() == true) return true;
    }

    return false;
}

bool Cladire::toateLifturileSuntStationate()
{
    for (int i=0;i<nrLifturi;i++) {
        if (lifturi[i]->getStare() != "STATIONARE") return false;
    }

    return true;
}

void Cladire::avanseazaEtaj()
{
    for (int i=0; i < nrLifturi; i++) {
        lifturi[i]->afisare();
        lifturi[i]->avansare();
    }
}

void Cladire::ruleazaLifturi()
{
    int t, etajComanda, etajDestinatie, timp = 0;
    string line;

    intrari.open("intrari.txt");
    getline(intrari, line);

    bool start = true;

    do
    {
        intrari >> t >> etajComanda >> etajDestinatie;

        do {

            cout << "t=" << timp << endl;
            avanseazaEtaj();
            timp++;
            cout << "\n";

        } while (t != timp && (!intrari.eof()));

        if (t == timp) comanda(etajComanda, etajDestinatie);

        if ( intrari.eof()) {

            intrari.close();

            do {

                cout << "t=" << timp << endl;
                avanseazaEtaj();
                timp++;
                cout << "\n";

            } while (unulDintreLifturiAreComanda() || !toateLifturileSuntStationate());

            cout << "t=" << timp << endl;
            avanseazaEtaj();

            start = false;
        }

    } while (start);
}
