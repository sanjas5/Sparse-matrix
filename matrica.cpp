#ifndef MATRICA_CPP
#define MATRICA_CPP

#include "matrica.h"

Matrica::Matrica(int broj_redova, int broj_kolona, const vector<pair<pair<int, int>, double>> &elementi, bool optimizacija):
    broj_redova(broj_redova), broj_kolona(broj_kolona)
{
    if (!optimizacija)
    {
        for (int i = 0; i < elementi.size(); i++)
        {
            DodajElement(elementi[i].first.first, elementi[i].first.second, elementi[i].second);
        }
    }
    else
    {

        KreirajMatricuOptimizovano(elementi);
    }
}
void Matrica::KreirajMatricuOptimizovano(const vector<pair<pair<int, int>, double>> &elementi)
{
    if (elementi.size() == 0)
    {
        return;
    }

    Red *red = matrica;
    int j = 0;
    for (int i = 0; i < broj_redova; i++)
    {
        if (elementi[j].first.first != i)
        {
            continue;
        }
        Red *novi_red = new Red{i, nullptr, nullptr};
        Element *el = novi_red->elementi;
        while (j < elementi.size() && elementi[j].first.first == i)
        {
            Element *novi_element = new Element{elementi[j].first.second, elementi[j].second, nullptr};
            if (el == nullptr)
            {
                novi_red->elementi = novi_element;
                el = novi_element;
            }
            else
            {
                el->veza = novi_element;
                el = el->veza;
            }
            j++;
        }

        if (red == nullptr)
        {
            matrica = novi_red;
            red = novi_red;
        }
        else
        {
            red->veza = novi_red;
            red = red->veza;
        }
    }
}

double Matrica::IzvrsiOperaciju(double a, double b, char op)
{
    if (op == '+')
    {
        return a + b;
    }
    else if (op == '-')
    {
        return a - b;
    }

    return 0;
}

void Matrica::DodajElement(int i, int j, double el)
{

    if (i > broj_redova - 1)
        throw domain_error("Indeks reda izvan opsega matrice.");
    if (j > broj_kolona - 1)
        throw domain_error("Indeks kolone izvan opsega matrice.");

    if (matrica == nullptr)
    {
        matrica = new Red{i, nullptr, nullptr};
        Element *novi_element = new Element{j, el};
        matrica->elementi = novi_element;
        return;
    }
    //posotoje vec neki redovi i trazimo mjesto da ubacimo red
    //pomocni pokazivac za kretanje kroz redove
    Red *tmp_red = matrica;
    Red *prateci = nullptr;
    while (tmp_red != nullptr && tmp_red->index < i)
    {
        if (prateci == nullptr)
            prateci = matrica;
        else
            prateci = prateci->veza;

        tmp_red = tmp_red->veza;
    }

    if (tmp_red == nullptr || tmp_red->index > i)
    {
        Red *novi = new Red{i, nullptr, nullptr};
        if (prateci != nullptr)
            prateci->veza = novi;

        else
            matrica = novi;

        novi->veza = tmp_red;
        tmp_red = novi;
    }

    Element *tmp_element = tmp_red->elementi;            //trenutni red u koji dodajemo element
    Element *novi_element = new Element{j, el, nullptr};

    if (tmp_element == nullptr)
        tmp_red->elementi = novi_element;
    //cout << tmp_red -> index << " ";
    //cout<< "++ " <<tmp_element -> kolona << " " << tmp_element -> sadrzaj<<endl;

    else
    {
        Element *prateci_element = nullptr;
        while (tmp_element != nullptr && tmp_element->kolona < j)
        { //kad se pomjerio element i ne postoji kolona koja pokauzje na null
            if (prateci_element == nullptr)
            {
                prateci_element = tmp_element;
            }
            else
            {
                prateci_element = prateci_element->veza;
            }
            tmp_element = tmp_element->veza;
        }
        //opet postoje dva slucaja ili su veci ili jednaki
        if (tmp_element == nullptr || tmp_element->kolona > j)
        {
            if (prateci_element == nullptr)
            {
                tmp_red->elementi = novi_element;
            }
            else
            {
                prateci_element->veza = novi_element;
            }
            novi_element->veza = tmp_element;
            tmp_element = novi_element;
        }
        else
        {
            throw logic_error("Definisali ste element više puta!");
        }

    }
}

Red *Matrica::DodajRed(Red *r, Red *c, bool minus = false)
{
    Red *novi_red = new Red{r->index, nullptr, nullptr};
    c = SpojiRed(c, novi_red);

    Element *el = r->elementi;
    Element *c_el = c->elementi;
    while (el != nullptr)
    {
        double novi_sadrzaj = el->sadrzaj;
        if (minus)
        {
            novi_sadrzaj = Matrica::IzvrsiOperaciju(0, el->sadrzaj, '-');
        }
        Element *novi = new Element{el->kolona, novi_sadrzaj, nullptr};
        c_el = Matrica::SpojiElement(c, c_el, novi);
        el = el->veza;
    }

    return c;
}

Element *Matrica::SpojiElement(Red *c, Element *c_el, Element *novi)
{
    if (c_el == nullptr)
    {
        c->elementi = novi;
        c_el = novi;
    }
    else
    {
        c_el->veza = novi;
        c_el = c_el->veza;
    }

    return c_el;
}

Red *Matrica::SpojiRed(Red *c, Red *novi_red)
{
    if (c == nullptr)
    {
        matrica = novi_red;
        c = novi_red;
    }
    else
    {
        c->veza = novi_red;
        c = novi_red;
    }

    return c;
}

Matrica Matrica::SaberiOduzmi(const Matrica &m1, const Matrica &m2, char op)
{
    Red *r1 = m1.matrica;
    Red *r2 = m2.matrica;
    Matrica C(m1.broj_redova, m1.broj_kolona);  //rezultantna matrica
    Red *c = C.matrica;
    while (r1 != nullptr && r2 != nullptr)
    {
        if (r1->index < r2->index)
        {
            c = C.DodajRed(r1, c);
            r1 = r1->veza;
        }
        else if (r1->index > r2->index)
        {
            c = C.DodajRed(r2, c, true);
            r2 = r2->veza;
        }
        else
        {
            Red *novi_red = new Red{r1->index, nullptr, nullptr};
            c = C.SpojiRed(c, novi_red);

            Element *el1 = r1->elementi;
            Element *el2 = r2->elementi;
            Element *c_el = c->elementi;
            while (el1 != nullptr && el2 != nullptr)
            {
                if (el1->kolona < el2->kolona)
                {
                    Element *novi = new Element{el1->kolona, el1->sadrzaj, nullptr};
                    c_el = Matrica::SpojiElement(c, c_el, novi);
                    el1 = el1->veza;
                }
                else if (el1->kolona > el2->kolona)
                {
                    Element *novi = new Element{el2->kolona, Matrica::IzvrsiOperaciju(0, el2->sadrzaj, op), nullptr};
                    c_el = Matrica::SpojiElement(c, c_el, novi);
                    el2 = el2->veza;
                }
                else
                {
                    Element *novi = new Element{el1->kolona, Matrica::IzvrsiOperaciju(el1->sadrzaj, el2->sadrzaj, op), nullptr};
                    c_el = Matrica::SpojiElement(c, c_el, novi);
                    el1 = el1->veza;
                    el2 = el2->veza;
                }
            }

            while (el1 != nullptr)
            {
                Element *novi = new Element{el1->kolona, el1->sadrzaj, nullptr};
                c_el = Matrica::SpojiElement(c, c_el, novi);
                el1 = el1->veza;
            }

            while (el2 != nullptr)
            {
                Element *novi = new Element{el2->kolona, Matrica::IzvrsiOperaciju(0, el2->sadrzaj, op), nullptr};
                c_el = Matrica::SpojiElement(c, c_el, novi);
                el2 = el2->veza;
            }

            r1 = r1->veza;
            r2 = r2->veza;
        }
    }

    while (r1 != nullptr)
    {
        Red *novi_red = new Red{r1->index, nullptr, nullptr};
        c = C.SpojiRed(c, novi_red);

        Element *el = r1->elementi;
        Element *c_el = c->elementi;
        while (el != nullptr)
        {
            Element *novi = new Element{el->kolona, el->sadrzaj, nullptr};
            c_el = Matrica::SpojiElement(c, c_el, novi);
            el = el->veza;
        r1 = r1->veza;
    }

    while (r2 != nullptr)
    {
        Red *novi_red = new Red{r2->index, nullptr, nullptr};
        c = C.SpojiRed(c, novi_red);

        Element *el = r2->elementi;
        Element *c_el = c->elementi;
        while (el != nullptr)
        {
            Element *novi = new Element{el->kolona, Matrica::IzvrsiOperaciju(0, el->sadrzaj, op), nullptr};
            c_el = Matrica::SpojiElement(c, c_el, novi);
            el = el->veza;
        }
        r2 = r2->veza;
    }

    return C;
    }
}
ostream &operator<<(ostream &tok, const Matrica &m)
{
    tok << "....................." << endl;
    Red *tmp_red = m.matrica;
    Element *tmp_element = nullptr;
    int i = 0;
    while (tmp_red != nullptr)
    {
        //cout << tmp_red -> index << " -> ";
        if (i != tmp_red->index)
        { //ukoliko red ne postoji
            for (int k = 0; k < m.broj_kolona; k++)
            {
                tok << "0 ";
            }
        }

        else
        {
            tmp_element = tmp_red->elementi;
            int j = 0;
            while (tmp_element != nullptr)
            {
                if (j != tmp_element->kolona)
                {
                    tok << "0 ";
                }
                else
                {
                    //cout << tmp_element -> kolona << " ";
                    tok << tmp_element->sadrzaj << " ";
                    tmp_element = tmp_element->veza;
                }
                j++;
            }

            if (j != m.broj_kolona)
            {
                for (int k = j; k < m.broj_kolona; k++)
                {
                    tok << "0 ";
                }
            }

            tmp_red = tmp_red->veza;
        }
        //tmp_red = tmp_red->veza;
        tok << endl;
        i++;
    }

    if (i != m.broj_redova)
    {
        for (int k = i; k < m.broj_redova; k++)
        {
            for (int p = 0; p < m.broj_kolona; p++)
            {
                tok << "0 ";
            }
            tok << endl;
        }
    }

    return tok;
}

Matrica operator+(const Matrica &m1, const Matrica &m2)
{
    if (m1.broj_kolona != m2.broj_kolona || m1.broj_redova != m2.broj_redova){
        throw domain_error("Matrice nisu saglasne za sabiranje.");
    }
    return Matrica::SaberiOduzmi(m1, m2, '+');
}

Matrica operator-(const Matrica &m1, const Matrica &m2)
{
    if (m1.broj_kolona != m2.broj_kolona || m1.broj_redova != m2.broj_redova){
        throw domain_error("Matrice nisu saglasne za oduzimanje.");
    }
    return Matrica::SaberiOduzmi(m1, m2, '-');
}

Matrica Matrica::transponuj()
{
    Matrica transponovana(broj_kolona, broj_redova);
    Red *red = matrica;
    while (red != nullptr)
    {
        Element *elementi = red->elementi;
        while (elementi != nullptr)
        {
            transponovana.DodajElement(elementi->kolona, red->index, elementi->sadrzaj);
            elementi = elementi->veza;
        }
        red = red->veza;
    }
    return transponovana;
}

Matrica::~Matrica()
{
    Red *red = matrica;
    while (red != nullptr)
    {
        Red *tmp_red = red;
        Element *elementi = red->elementi;
        while (elementi != nullptr)
        {
            Element *tmp = elementi;
            elementi = elementi->veza;
            delete tmp;
        }
        red = red->veza;
        delete tmp_red;
    }
}

Matrica::Matrica(const Matrica &m)
{
    broj_redova = m.broj_redova;
    broj_kolona = m.broj_kolona;

    Red *red = m.matrica;   //prolazi kroz matricu koja se kopira
    Red *moj_red = matrica; //prolazi kroz matricu koja se kreira (this)
    while (red != nullptr)
    {
        Red *novi_red = new Red{red->index, nullptr, nullptr};
        if (matrica == nullptr)
        {
            matrica = novi_red;
            moj_red = novi_red;
        }
        else
        {
            moj_red->veza = novi_red;
            moj_red = moj_red->veza;
        }
        Element *elementi = red->elementi;
        Element *moji_elementi = nullptr;
        while (elementi != nullptr)
        {
            Element *novi_element = new Element{elementi->kolona, elementi->sadrzaj, nullptr};
            if (moji_elementi == nullptr)
            {
                moj_red->elementi = novi_element;
                moji_elementi = novi_element;
            }
            else
            {
                moji_elementi->veza = novi_element;
                moji_elementi = moji_elementi->veza;
            }
            elementi = elementi->veza;
        }
        red = red->veza;
    }
}

Matrica &Matrica::operator=(const Matrica &m)
{

    if (this == &m)
    {
        //samododjela
        return *this;
    }

    Red *red = matrica;
    while (red != nullptr)
    {
        Red *tmp_red = red;
        Element *elementi = red->elementi;
        while (elementi != nullptr)
        {
            Element *tmp = elementi;
            elementi = elementi->veza;
            delete tmp;
        }
        red = red->veza;
        delete tmp_red;
    }

    matrica = nullptr;

    broj_redova = m.broj_redova;
    broj_kolona = m.broj_kolona;

    red = m.matrica;
    Red *moj_red = matrica;
    while (red != nullptr)
    {
        Red *novi_red = new Red{red->index, nullptr, nullptr};
        if (matrica == nullptr)
        {
            matrica = novi_red;
            moj_red = novi_red;
        }
        else
        {
            moj_red->veza = novi_red;
            moj_red = moj_red->veza;
        }
        Element *elementi = red->elementi;
        Element *moji_elementi = nullptr;
        while (elementi != nullptr)
        {
            Element *novi_element = new Element{elementi->kolona, elementi->sadrzaj, nullptr};
            if (moji_elementi == nullptr)
            {
                moj_red->elementi = novi_element;
                moji_elementi = novi_element;
            }
            else
            {
                moji_elementi->veza = novi_element;
                moji_elementi = moji_elementi->veza;
            }
            elementi = elementi->veza;
        }
        red = red->veza;
    }

    return *this;
}

double Matrica::element(int i, int j) const
{
    Red *red = matrica;
    while (red != nullptr)
    {
        if (red->index != i)
        {
            red = red->veza;
            continue;
        }
        Element *elementi = red->elementi;
        while (elementi != nullptr)
        {
            if (elementi->kolona == j)
            {
                return elementi->sadrzaj;
            }
            elementi = elementi->veza;
        }
        red = red->veza;
    }

    return 0;
}

Matrica operator*(const Matrica &m1, const Matrica &m2)
{
    Matrica C(m1.broj_redova, m2.broj_kolona);

    for (int i = 0; i < m1.broj_redova; i++)
    {
        for (int j = 0; j < m2.broj_kolona; j++)
        {
            double suma = 0;
            for (int k = 0; k < m1.broj_kolona; k++)
            {
                suma += m1.element(i, k) * m2.element(k, j);
            }
            if (suma != 0)
            {
                C.DodajElement(i, j, suma);
            }
        }
    }

    return C;

}

Matrica Matrica::operator*(const double &c)
{
    Matrica rezultat(*this);
    rezultat *= c;
    return rezultat;
}

Matrica &Matrica::operator*=(const double &c)
{
    Red *red = matrica;
    while (red != nullptr)
    {
        Red *tmp_red = red;
        Element *elementi = red->elementi;
        while (elementi != nullptr)
        {
            elementi->sadrzaj *= c;
            elementi = elementi->veza;
        }
        red = red->veza;
    }
    return *this;
}

Matrica Matrica::operator/(const double &c)
{
    Matrica rezultat(*this);
    rezultat /= c;
    return rezultat;
}

Matrica &Matrica::operator/=(const double &c)
{
    if (c == 0)
    {
        throw domain_error("Dijeljenje nulom!");
    }
    Red *red = matrica;
    while (red != nullptr)
    {
        Red *tmp_red = red;
        Element *elementi = red->elementi;
        while (elementi != nullptr)
        {
            elementi->sadrzaj /= c;
            elementi = elementi->veza;
        }
        red = red->veza;
    }
    return *this;
}

Matrica Matrica::stepenuj(int stepen)
{
    if (stepen < 0)
    {
        throw domain_error("Stepen mora biti nenegativan!");
    }

    Matrica rezultat(*this);
    for (int i = 1; i < stepen; i++)
    {
        rezultat = rezultat * (*this);
    }

    return rezultat;
}

Matrica &Matrica::T()
{
    //Matrica transp(*this);
    //transp.transponuj();
    *this = transponuj(); //transp;
    return *this;
}

Matrica &Matrica::Pow(int stepen)
{
    //Matrica stepenovana(*this);
    //stepenovana.stepenuj(stepen);
    *this = stepenuj(stepen); //stepenovana;
    return *this;
}

Matrica &Matrica::operator+=(const Matrica &m)
{
    *this = *this + m;
    return *this;
}

Matrica &Matrica::operator-=(const Matrica &m)
{
    *this = *this - m;
    return *this;
}

Matrica &Matrica::operator*=(const Matrica &m)
{
    *this = (*this) * m;
    return *this;
}

#endif // MATRICA_CPP
