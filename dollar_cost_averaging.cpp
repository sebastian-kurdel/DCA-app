#include <iostream>
#include <conio.h>
#include <fstream>
#include <cmath>
#include <fstream>

using namespace std;

int ilosc;
char opcja1, opcja2, opcja3;
float cena, pozycja, procent, profit, czynnik;
double cel, suma, suma_krypto, lista1[100], lista2[100], krypto[100];
string nazwa;
fstream plik1;

void zapis(string n) {
    n += ".txt";
    fstream plik;
    plik.open(n.c_str(), ios::out);
    plik << "DOLLAR COST AVERAGING v1.0.0" << endl;
    plik << "----------------------------" << endl;
    plik << "Wielkość pozycji: " << pozycja << endl;
    plik << "Interwał cenowy: " << procent << "%" << endl;
    plik << "Procent profitu: " << profit << "%" << endl;
    plik << "Ilość pozycji: " << ilosc << endl;
    plik << "Współczynnik zwiększania: " << czynnik << "%" << endl;
    plik << "----------------------------" << endl;
    for(int i = 0; i < ilosc; i++) {
        if (czynnik == 0) plik << "Safety order " << i << " = " << lista1[i] << endl;
        else plik << "(" << pozycja * pow(1 + czynnik * 0.01, i) << ") Safety order " << i << " = " << lista1[i] << endl;
    }
    plik << "----------------------------" << endl;
    for(int i = 0; i < ilosc; i++) {
        plik << "Próg dla " << lista1[i] << " = " << lista2[i] << endl;
    }
    plik.close();
}

void settings() {
    plik1.open("settings.txt", ios::in);
    plik1 >> procent >> profit >> ilosc >> czynnik;
    plik1.close();
}

int main() {

    settings();
    while (opcja1 != '3') {
        cena = 1;
        pozycja = 1;
        opcja2 = 1;
        system("cls");
        cout << "DOLLAR COST AVERAGING v1.0.0" << endl;
        cout << "----------------------------" << endl;
        cout << "1: Handel" << endl;
        cout << "2: Ustawienia" << endl;
        cout << "3: Wyj\230cie" << endl;
        opcja1 = getch();
        switch(opcja1) {
            case '1':    
                suma = 0;
                suma_krypto = 0;
                system("cls");
                cout << "DOLLAR COST AVERAGING v1.0.0" << endl;
                cout << "----------------------------" << endl;
                cout << "Podaj cen\251 wej\230cia: ";
                cin >> cena;
                cout << "Podaj wielko\230\206 pozycji: ";
                cin >> pozycja;
                system("cls");
                cout << "DOLLAR COST AVERAGING v1.0.0" << endl;
                cout << "----------------------------" << endl;

                for(int i = 0; i < ilosc; i++) {
                    lista1[i] = cena - (cena * procent * 0.01) * i;
                    krypto[i] = pozycja * pow(1 + czynnik * 0.01, i) / lista1[i];
                    if (czynnik == 0) cout << "Safety order " << i << " = " << lista1[i] << endl;
                    else cout << "(" << pozycja * pow(1 + czynnik * 0.01, i) << ") Safety order " << i << " = " << lista1[i] << endl;
                }
                cout << "----------------------------" << endl;

                for(int i = 0; i < ilosc; i++) {
                    suma_krypto += krypto[i];
                    suma += pozycja * pow(1 + czynnik * 0.01, i); //(pozycja * 1.05) ^ i
                    cel = suma * (1 + profit * 0.01);
                    lista2[i] = cel / suma_krypto;
                    cout << "Pr\242g dla " << lista1[i] << " = " << lista2[i] << endl;
                }
                cout << "----------------------------" << endl;
                cout << "Zapisa\206 plik?" << endl;
                cout << "1: Tak" << endl;
                opcja3 = getch();
                if(opcja3 == '1') {
                    cout << "Podaj nazw\251: ";
                    cin >> nazwa;
                    zapis(nazwa);
                }
                break;
            case '2':
                while(opcja2 != '5') {    
                    system("cls");
                    cout << "DOLLAR COST AVERAGING v1.0.0" << endl;
                    cout << "----------------------------" << endl;
                    cout << "1: Interwa\210 cenowy = " << procent << "%" << endl;
                    cout << "2: Wysoko\230\206 profitu = " << profit << "%" << endl;
                    cout << "3: Ilo\230\206 safety orders = " << ilosc << endl;
                    cout << "4: Wsp\242\210czynnik zwi\251kszania pozycji = " << czynnik <<  "%" << endl;
                    cout << "5: Cofnij" << endl;
                    opcja2 = getch();
                    switch(opcja2) {
                        case '1':
                            system("cls");
                            cout << "Wprowad\253 warto\230\206 interwa\210u cenowego: ";
                            cin >> procent;
                            plik1.open("settings.txt", ios::out);
                            plik1 << procent << endl << profit << endl << ilosc << endl << czynnik;
                            plik1.close(); break;
                        case '2':
                            system("cls");
                            cout << "Wprowad\253 warto\230\206 profitu: ";
                            cin >> profit;
                            plik1.open("settings.txt", ios::out);
                            plik1 << procent << endl << profit << endl << ilosc << endl << czynnik;
                            plik1.close(); break;
                        case '3':
                            system("cls");
                            cout << "Wprowad\253 ilo\230\206 safety orders: ";
                            cin >> ilosc;
                            plik1.open("settings.txt", ios::out);
                            plik1 << procent << endl << profit << endl << ilosc << endl << czynnik;
                            plik1.close(); break;
                        case '4':
                            system("cls");
                            cout << "Wprowad\253 wsp\242\210czynnik zwi\251kszania: ";
                            cin >> czynnik;
                            plik1.open("settings.txt", ios::out);
                            plik1 << procent << endl << profit << endl << ilosc << endl << czynnik;
                            plik1.close(); break;
                    }
                }
            case '3': break;
        }
    }
}