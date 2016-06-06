#include "Lift.h"

Lift::Lift(int nrLift, int etaje)
{
    this->nrLift = nrLift;
    nivelCurent = 0;
    stare = "STATIONARE";
    nrEtaje = etaje;
}

Lift::~Lift()
{
    //dtor
}

void Lift::avansare()
{
    if (!comenzi.empty()) {

        if (stare == "STATIONARE") { stare = "OPRIRE"; return; }

        if (nivelCurent <= comenzi.front()) {

                stareAnterioara = "URCARE";

                if (stare == "OPRIRE" && !comenzi.empty()) { stare = "URCARE"; return; }

                nivelCurent++;

                if (nivelCurent == comenzi.front()) {
                        comenzi.pop_front();
                        stare = "OPRIRE";
                } else {
                    stare = "URCARE";
                }
        }

        else if (nivelCurent >= comenzi.back()) {

                stareAnterioara = "COBORARE";

                if (stare == "OPRIRE" && !comenzi.empty()) { stare = "COBORARE"; return; }

                nivelCurent--;

                if (nivelCurent == comenzi.back()) {
                    comenzi.pop_back();
                    stare = "OPRIRE";
                } else {
                    stare = "COBORARE";
                }

        } else if ((nivelCurent > comenzi.front()) && (nivelCurent < comenzi.back())) {

            if (stareAnterioara == "COBORARE") {

                nivelCurent--;

                if (nivelCurent == comenzi.front()) {
                    comenzi.pop_front();
                    stare = "OPRIRE";

                } else {

                    for (int i=0; i < nrEtaje; i++) {

                    list<int>::iterator findValue = find(comenzi.begin(), comenzi.end(), i);
                    if (findValue != comenzi.end() && i == nivelCurent) {
                            comenzi.remove(i);
                            stare = "OPRIRE";
                        }
                    }
                }
            }

            else if (stareAnterioara == "URCARE") {

                nivelCurent++;

                if (nivelCurent == comenzi.back()) {
                    comenzi.pop_back();
                    stare = "OPRIRE";

                } else {

                    for (int i=0; i < nrEtaje; i++) {

                    list<int>::iterator findValue = find(comenzi.begin(), comenzi.end(), i);
                    if (findValue != comenzi.end() && i == nivelCurent) {
                            comenzi.remove(i);
                            stare = "OPRIRE";
                        }
                    }
                }
            }
        }
    }

    else {

        stare = "STATIONARE";
        for (int i=0;i<nrEtaje;i++)
            comenzi.remove(i);

        }
}

void Lift::afisare()
{
    cout << "L" << nrLift << ": ";

    for (int i=0;i<=nrEtaje;i++)
    {
        list<int>::iterator findValue = find(comenzi.begin(), comenzi.end(), i);
        if (findValue != comenzi.end() && i != nivelCurent) cout << " " << i << " ";
        else if ( i == nivelCurent) {
            if (stare == "STATIONARE")
                cout << " S ";
            if (stare == "OPRIRE")
                cout << " * ";
            if (stare == "URCARE")
                cout << " > ";
            if (stare == "COBORARE")
                cout << " < ";
        }
        else {
            cout << " - ";
        }
    }

    cout << endl;
}

void Lift::adaugareComanda(int etaj1, int etaj2)
{
    cout << "Lift cerut la etaj " << etaj1 << " pentru etaj " << etaj2 << " gasit lift " << nrLift << endl;
    comenzi.push_back(etaj1);
    comenzi.push_back(etaj2);
    comenzi.unique();
    comenzi.sort();
}

int Lift::timp(int destinatie)
{
    return (nivelCurent - destinatie);
}

int Lift::getNivelCurent()
{
    return nivelCurent;
}

string Lift::getStare()
{
    return stare;
}

bool Lift::areComenzi()
{
    return !comenzi.empty();
}


int Lift::getTimpPanaLaUltimaComanda()
{
    if (stare == "URCARE") return abs(nivelCurent - comenzi.back());
    else if (stare == "COBORARE") return abs(nivelCurent - comenzi.front());
    else if (stare == "OPRIRE") {
        if (nivelCurent <= comenzi.back()) return abs(nivelCurent - comenzi.back());
        else if (nivelCurent >= comenzi.front() ) return abs(nivelCurent - comenzi.front());
    }

    return 0;
}

int Lift::getUltimaComanda()
{
    if (stare == "COBORARE") return comenzi.front();
    else if (stare == "URCARE") return comenzi.back();
    else if (stare == "OPRIRE") {
        if (nivelCurent <= comenzi.back()) return comenzi.back();
        else if (nivelCurent >= comenzi.front() ) return comenzi.front();
    }

    return 0;
}

