#include <iostream>
#include <vector>
#include <stdexcept>
#include "matrica.h"
using namespace std;


int main()
{
    vector<pair<pair<int,int>,double>> elementi{{{2,8},5},{{6,4},25},{{2,3},15},{{7,9},35}};
    vector<pair<pair<int,int>,double>> elementi0{{{0,8},5},{{0,4},25},{{2,3},15},{{9,9},35}};

    vector<pair<pair<int, int>, double>> elementi1{{{0, 0}, 1}, {{0, 3}, 2}, {{2, 0}, 7}, {{3, 0}, 1}, {{3, 1}, 4}, {{3, 2}, 3}};
    vector<pair<pair<int, int>, double>> elementi2{{{0, 0}, 4}, {{1, 0}, 5}, {{1, 2}, 1}, {{2, 0}, 7}, {{2, 1}, 6}, {{2, 2}, 3}};

    vector<pair<pair<int, int>, double>> elementi3{{{0, 0}, 3}, {{0, 2}, 2}, {{1, 2}, 1}, {{2, 1}, 5}};
    vector<pair<pair<int, int>, double>> elementi4{{{0, 0}, 4}, {{1, 1}, 1}, {{2, 0}, 6}};

    vector<pair<pair<int, int>, double>> elementi5{{{0, 0}, 1}, {{0, 1}, 2}, {{0, 2}, 3}, {{1, 0}, 4}, {{1, 1}, 5}, {{1, 2}, 6}};
    vector<pair<pair<int, int>, double>> elementi6{{{0, 0}, 8}, {{0, 1}, 3}, {{1, 0}, 7}, {{1, 1}, 1}, {{2, 0}, 6}, {{2, 1}, 4}};

    Matrica m(10,10,elementi,false);
    Matrica m0(10,10,elementi0,false);
    Matrica m1(4,4,elementi1);
    Matrica m2(3,3,elementi2);
    Matrica m3(3,3,elementi3);
    Matrica m4(3,2,elementi4);
    Matrica m5(2,3,elementi5);
    Matrica m6(3,2,elementi6);
    cout<<"m";
    cout<<m;
    cout<<"m0";
    cout<<m0;
    cout<<"m1";
    cout<<m1;
    cout<<"m2";
    cout<<m2;
    cout<<"m3";
    cout<<m3;
    cout<<"m4";
    cout<<m4;
    cout<<"m5";
    cout<<m5;
    cout<<"m6";
    cout<<m6;

    //Sabiranje matrica
    cout<<"Rezultat sabiranja matrica m2 i m3: ";
    cout<<m2+m3;

    cout<<"Rezultat sabiranja matrica m i m0: ";
    Matrica zbir = m+m0;
    cout<<zbir;
    //Oduzimanje matrica
    cout<<"Rezultat oduzimanja matrica m i m0: ";
    Matrica razlika = m-m0;
    cout<<razlika;
    //Množenje matrica
    cout<<"Rezultat mnozenja matrica m2 i m4: ";
    cout<<m2*m4;
    //Stepenovana matrica
    cout<<"Rezultat stepenovanja matrice m1, pa m2 sa 2: ";
    m1.Pow(2);
    cout << m1;
    cout<<"Kvadriranje matrice m3: ";
    Matrica stepen = m3.stepenuj(2);
    cout << stepen;
    //Operator -=
    cout<<"matrica-matrica m1-m1: ";
    m1 -= m1;
    cout << m1;         //od sad je matrica m1 = 0
    //Operator +=
    cout<<"m2 plus m2: ";
    m2 += m2;
    cout << m2;         //od sad je matrica m2 = m2+m2
    //operator *=
    cout<<"Matrica m3 pomnozena sama sa sobom: ";
    m3 *= m3;
    cout << m3;          //od sad je matrica m3 = m3*m3
    cout<<"Matrica m6 pomnozena sa konstantom: ";
    m6 *= 5; //operator *=
    cout << m6;         //od sad je matrica m6 = m6*5
    cout<<"Matrica c = m2*5: ";
    Matrica c = m2 * 5; //operator *
    cout<<c;
    //Dijenjenje konstantom
    cout<<"Matrica m3/5: ";
    cout << m3 / 5;
    //Transponovana matrica
    cout<<"Transponovana matrica m4: ";
    m4.T();
    cout << m4;

    //operator =
    cout<<"m6 = m6";
    m6 = m6;
    cout << m6;
    cout<<"m6 = m2";
    m6 = m2;
    cout << m6;

    //Matrica d = m1 + m2;
    //cout << d;


    //Matrica m1(3, 3, elementi1);
    // Matrica m3(3, 3, elementi1, false);
    //Matrica m2(3, 2, elementi2);
    // Matrica m4(3, 2, elementi2, false);
    //cout << m1 * m1;
    //cout << m1.element(2, 1);
    //cout << m1 * m1;
    // cout << m2;
    // cout << m3;
    // cout << m4;
    //cout << m2;


    // m1.T();
    // cout << m1;



    //Matrica c = m1 * m1;
    //cout << c;




    // Matrica d = m1 - m2;
    // cout << d;

    // Matrica e = m1.transponuj();
    // cout << e;

    // Matrica f(m2);
    // cout << f;


    return 0;
}

