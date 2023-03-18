#include <iostream>
#include "Graf.h"
#include <cstdlib>
#include <cmath>



int main()
{
    Graf g;

    int n;
    bool program = true;
    int i = 0;
  

    while (program) {
        cout << endl;
        cout << "Unesite sta zelite da uradite. Ukoliko zelite da zaustavite program pritisnite nulu. Unosite iskljucivo brojeve, u suprotnom program prestaje sa radom. \n1.";
        cout << "Ucitaj graf iz tekstualnog fajla zadatog formata. \n";
        cout << "2.Dodajte cvor u graf.";
        cout << "\n3.Dodajte granu u graf \n4.Uklonite granu iz grafa.";
        cout << " \n5.Obrisite zauzetu memoriju. \n6.Ispisite graf. \n7.Uklonite cvor iz grafa. \n8.Nadjite k najslicnijih reci zadatoj u opadajucem poretku. " <<  endl << endl;


        cin >> n;
        cout << endl;
        if (n == 0) exit(1);


        if (i == 0 && n != 1 && n<=8) { 
            cout << "Datu operacije je nemoguce izvrsiti jer graf nije ucitan, pokusajte ponovo. \n Za kraj rada porgrama stisnite 0." << endl;
            continue;
        }

        switch (n) {
        case 0:

            exit(1);

        case 1:
            g.CitajDatoteku();
            cout << endl << "Graf uspesno ucitan." << endl;
            break;
        case 2:
            g.dodajCvor();
            break;
        case 3:
            g.dodajGranu();
            break;
        case 4:
            g.ukloniGranu();
            break;
        case 5:
            g.ocisti();
            cout << endl << "Zauzeta memorija je uspesno oslobodjena." << endl;
            break;
        case 6:
            g.pisiGraf();
            break;

        case 7:
            g.ukloniCvor();
            break;

        case 8:
            g.Dijkstra1();
            break;

        default:
            cout << "Nazalost, niste uneli nijednu od navedenih opcija, pokusajte ponovo ili pritisnite nulu za kraj programa." << endl;
            break;
        }
        i++;

    }
     
}
