#include "Graf.h"

double** shrink(double** matrix, int size, int rowToErase) {
    double** resultMatrix = (double**)malloc((size - 1) * sizeof(double*));

    for (int i = 0; i < size - 1; ++i) {
        resultMatrix[i] = (double*)malloc((size - 1) * sizeof(double));
    }

    for (int i = 0; i < size; ++i) {
        int newI = i;
        if (newI == rowToErase) {
            continue;
        }
        else if (newI > rowToErase) {
            --newI;
        }

        for (int p = 0; p < size; ++p) {
            int newP = p;
            if (newP == rowToErase) {
                continue;
            }
            else if (newP > rowToErase) {
                --newP;
            }
            resultMatrix[newI][newP] = matrix[i][p];
        }
    }
    return resultMatrix;
}

int nadjiIndkes(string s, string* lista, int bC) {

    
    for (int k = 0; k<bC; k++) {
        if (lista[k] == s) {
            return k;
        }
    }
}

bool Posecen(bool* poseceni, int index, int Bc) {


    if (poseceni[index] == false) {
        poseceni[index] == true;
        return false;
    }
    else return true;
}


double nadjiMax(double* dist, int Bc, bool* poseceni) {

    double max = 0;
    int index = 0;

    for (int i = 0; i < Bc; i++)
    {   
        if (dist[i] > max && !Posecen(poseceni, i, Bc))
        {
            max = dist[i];
            index = i;
        }
    }

    return index;
}


void Graf::CitajDatoteku() 
{
    fstream datoteka;
    string imeDat;
    cout << "Unesite ime datoteke: " << endl;
    cin >> imeDat;
    datoteka.open(imeDat);
    if (!datoteka) {
        cout << "Uneto je nepostojece ime datoteke." << endl;
        return;
    }

    string bC;
    getline(datoteka, bC); // brojCvorova
    brojCvorova = stoi(bC);
    string bG;
    getline(datoteka, bG); //brojGrana
    int brojGrana = stoi(bG);

    string nC;
    getline(datoteka, nC);

    listaCvorova = new string[brojCvorova];
    int index = 0;

    string rec = "";
    for (auto x : nC)
    {
        if (x == ' ')
        {
             listaCvorova[index] = rec;
             index++;
             rec = "";
        }
        else {
            rec = rec + x;

        }
    }

    listaCvorova[index] = rec;
  
    matricaGrafa = (double**)calloc(brojCvorova, sizeof(double*));

    for (int num = 0; num < brojCvorova; num++) {
        matricaGrafa[num] =(double*)calloc(brojCvorova, sizeof(double));
    }

    int m = 0;
    while (datoteka) {
        if (m == brojGrana) break;
        Podaci podaci;
        datoteka >> podaci.rec1 >> podaci.rec2 >> podaci.odnos;
        matricaGrafa[nadjiIndkes(podaci.rec1, listaCvorova, brojCvorova)][nadjiIndkes(podaci.rec2, listaCvorova, brojCvorova)] = podaci.odnos;
        m++;
    }  

    datoteka.close();
}

void Graf::pisiGraf() const
{

    for (int i = 0; i < this->brojCvorova; i++) {
        for (int j = 0; j < this->brojCvorova; j++) {
            if (j != this->brojCvorova - 1) {
                if (this->matricaGrafa[i][j] > 0) { cout << this->matricaGrafa[i][j] << " "; }
                else { cout << this->matricaGrafa[i][j] << "    "; }

            }
            else {
                cout << this->matricaGrafa[i][j];
            }
        }
        putchar('\n');
    }
}

void Graf::dodajCvor()
{

    cout << "Unesite naziv cvora koji se dodaje: ";
    string noviCvor;
    cin >> noviCvor;
    brojCvorova = brojCvorova + 1;
  
    string* listaCvorov = new string[brojCvorova];

    for (int i = 0; i < brojCvorova-1; i++)
    {
        listaCvorov[i] = listaCvorova[i];
    }

    listaCvorov[brojCvorova - 1] = noviCvor;

    delete []  listaCvorova;
    listaCvorova = listaCvorov;

    matricaGrafa = (double**)realloc(matricaGrafa, brojCvorova * sizeof(double*));
    for (int num = 0; num < brojCvorova-1; num++) {
        matricaGrafa[num] = (double*)realloc(matricaGrafa[num], brojCvorova * sizeof(double));
    }
        

    matricaGrafa[brojCvorova-1] = (double*)calloc(brojCvorova, sizeof(double));

    for (int i = 0; i < brojCvorova; ++i) {

        matricaGrafa[i][brojCvorova - 1] = 0;
        matricaGrafa[brojCvorova-1][i] = 0;
       
    }

}

void Graf::dodajGranu()
{
    Podaci p;
    cout << "Unesite dva cvora i tezinu grane: " << endl;
    cin >> p.rec1 >> p.rec2 >> p.odnos;
    
    bool stringFound1 = false;
    bool stringFound2 = false;

    for (int i = 0; i < brojCvorova; i++) {
        if (listaCvorova[i] == p.rec1) {
            stringFound1 = true;
            break;
        }
    }

    for (int i = 0; i < brojCvorova; i++) {
        if (listaCvorova[i] == p.rec2) {
            stringFound2 = true;
            break;
        }
    }

    if ((stringFound1 && stringFound2) == false) {
        cout << "Uneli ste nepostojeci cvor." << endl;
        return;
    }
    int i1 = nadjiIndkes(p.rec1, listaCvorova, brojCvorova);
    int i2 = nadjiIndkes(p.rec2, listaCvorova, brojCvorova);
    matricaGrafa[i1][i2] = p.odnos;

}

void Graf::ukloniCvor()
{
    string zadatCvor;
    cout << "Upisite cvor koji se brise ";
    cin >> zadatCvor;
    

    bool stringFound1 = false;
    for (int i = 0; i < brojCvorova; i++) {
        if (listaCvorova[i] == zadatCvor) {
            stringFound1 = true;
            break;
        }
    }
    if (stringFound1 == false) {
        cout << "Izabrali ste nepostojeci cvor.";
        return;
    }

    int indexReciuListi = nadjiIndkes(zadatCvor, listaCvorova, brojCvorova);

    double** res = shrink(matricaGrafa, brojCvorova, indexReciuListi);

    for (int i = 0; i < brojCvorova; i++) {
        free(matricaGrafa[i]);
    }

    free(matricaGrafa);

    matricaGrafa = res;

    brojCvorova = brojCvorova - 1;
      
}

void Graf::ukloniGranu()
{
    string rec1;
    string rec2;
    cout << "Unesite cvorove izmedju kojih zelite da uklonite grane: " << endl;
    cin >> rec1 >> rec2;

    bool stringFound1 = false;
    bool stringFound2 = false;

    for (int i = 0; i < brojCvorova; i++) {
        if (listaCvorova[i] == rec1) {
            stringFound1 = true;
            break;
        }
    }

    for (int i = 0; i < brojCvorova; i++) {
        if (listaCvorova[i] == rec2) {
            stringFound2 = true;
            break;
        }
    }


    if ((stringFound1 && stringFound2) == false) {
        cout << "Uneli ste nepostojeci cvor." << endl;
        return;
    }
    matricaGrafa[nadjiIndkes(rec1, listaCvorova, brojCvorova)][nadjiIndkes(rec2, listaCvorova, brojCvorova)] = 0;
}

void Graf::ocisti()
{

    for (int i = 0; i < brojCvorova; i++) {
        free(matricaGrafa[i]);
    }

    free(matricaGrafa);

    delete[] listaCvorova;

    //delete[] prethodnik;

    //delete[] poseceni;

    //delete[] dist;

}


void Graf::Dijkstra1()
{
    int brojSlicnih;
    string pocetniCvor;
    cout << "Unesite pocetni cvor i broj k: " << endl;
    cin >> pocetniCvor >> brojSlicnih;

    bool stringFound1 = false;
    for (int i = 0; i < brojCvorova; i++) {
        if (listaCvorova[i] == pocetniCvor) {
            stringFound1 = true;
            break;
        }
    }

    if (stringFound1 == false) {
        cout << "Uneli ste nepostojeci cvor, nemoguce je izvrsiti zeljenu operaciju." << endl;
        return;
    }

    int indexPC = nadjiIndkes(pocetniCvor, listaCvorova, brojCvorova);

    dist = new double[brojCvorova];

    poseceni = new bool[brojCvorova];

    prethodnik = new int[brojCvorova];

    for (int i = 0; i < brojCvorova; i++) {
        poseceni[i] = false;
    }

    poseceni[indexPC] = true;

    dist[indexPC] = -9999;

    prethodnik[indexPC] = -9999;

    for (int i = 0; i < brojCvorova; i++) {

        if (i == indexPC) continue;
        dist[i] = matricaGrafa[indexPC][i];
        if (matricaGrafa[indexPC][i] != 0) {
            prethodnik[i] = indexPC;
        }
        else { 
            prethodnik[i] = -9999;
        }
    }
    
    for (int k = 0; k<brojCvorova - 1; k++) {

        int indeks = nadjiMax(dist, brojCvorova, poseceni);
        if (dist[indeks] == -9999) break;

        for (int j = 0; j<brojCvorova; j++) {
            if (dist[indeks] * matricaGrafa[indeks][j] > dist[j]) {

                dist[j] = dist[indeks] * matricaGrafa[indeks][j];

                prethodnik[j] = indeks;

            }
        }
    }

    int* indexes = new int[brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        indexes[i] = i; 
    }


    for (int i = 0; i < brojCvorova; i++) {
        for (int j = i + 1; j < brojCvorova; j++) {
            if (dist[indexes[i]] > dist[indexes[j]]) {
                int temp = indexes[i];
                indexes[i] = indexes[j];
                indexes[j] = temp;
            }
        }
    }

    int temp = brojSlicnih;

    for (int i = brojCvorova - 1; i >= 0; i--) {
        if (temp == 0) break;
        if (listaCvorova[indexes[i]] == pocetniCvor) continue;
        cout << listaCvorova[indexes[i]] << " " << dist[indexes[i]] << endl;
        temp--;
    }

    delete[] poseceni;
    delete[] prethodnik;
    delete[] dist;
    
}

void Graf::nadjiJakoPovezane()
{


}
