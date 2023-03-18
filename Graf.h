#ifndef _graf_h_
#define _graf_h_


#include <limits.h>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class Graf {
private:
    double** matricaGrafa;
    int* prethodnik;
    bool* poseceni;
    double* dist;

    string* listaCvorova;
    int brojCvorova;

public:

    struct Podaci {
        string rec1;
        string rec2;
        double odnos;
    };

    Graf() = default;
    Graf(const Graf&) = delete;
    Graf(Graf&&) = delete;


	void CitajDatoteku();
    void pisiGraf() const;

    void dodajCvor();
    void dodajGranu();
    
    void ukloniCvor();
    void ukloniGranu();

    void ocisti();


    void nadjiJakoPovezane();

    void Dijkstra1();

};
#endif