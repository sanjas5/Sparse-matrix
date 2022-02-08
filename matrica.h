#ifndef MATRICA_H
#define MATRICA_H
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

struct Element;

struct Red
{
    int index;
    Element *elementi;
    Red *veza;
    Element *trenutni = nullptr;
};

struct Element
{
    int kolona;
    double sadrzaj;
    Element *veza;
};

class Matrica
{
private:
    int broj_redova;
    int broj_kolona;
    Red *matrica = nullptr; //pok na prvi cvor reda

    void DodajElement(int i, int j, double el);
    void KreirajMatricuOptimizovano(const vector<pair<pair<int, int>, double>> &elementi);
    static Element *SpojiElement(Red *c, Element *c_el, Element *novi);
    Red *DodajRed(Red *r, Red *c, bool minus);
    Red *SpojiRed(Red *c, Red *novi_red);
    static Matrica SaberiOduzmi(const Matrica &m1, const Matrica &m2, char op);
    static double IzvrsiOperaciju(double a, double b, char op);

public:
    Matrica(int broj_redova, int broj_kolona) : broj_redova(broj_redova), broj_kolona(broj_kolona) {}
    Matrica(int broj_redova, int broj_kolona, const vector<pair<pair<int, int>, double>> &elementi, bool optimizacija = 1);
    Matrica(const Matrica &m);
    Matrica &operator=(const Matrica &m);
    ~Matrica();

    Matrica transponuj();
    Matrica stepenuj(int stepen);
    Matrica &T();
    Matrica &Pow(int stepen);

    //popraviti mnozenje
    friend ostream &operator<<(ostream &tok, const Matrica &m);
    friend Matrica operator+(const Matrica &m1, const Matrica &m2);
    friend Matrica operator-(const Matrica &m1, const Matrica &m2);
    friend Matrica operator*(const Matrica &m1, const Matrica &m2);

    Matrica operator*(const double &c);
    Matrica &operator*=(const double &c);
    Matrica operator/(const double &c);
    Matrica &operator/=(const double &c);
    Matrica &operator+=(const Matrica &m);
    Matrica &operator-=(const Matrica &m);
    Matrica &operator*=(const Matrica &m);
    double element(int i, int j) const;
};
#endif // MATRICA_H
