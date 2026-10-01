#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Definicja struktury osoba
struct osoba
{
    string imie;
    string nazwisko;
    int nr;
};

// Klasa Kolejka oparta na strukturze osoba
class Kolejka
{
private:
    int ile;          // aktualna liczba elementów w kolejce
    int maxRozmiar;   // maksymalny rozmiar tablicy
    osoba* tablica;   // wskaŸnik na dynamiczn¹ tablicê obiektów osoba

public:
    // Konstruktor alokuje pamiêæ i inicjalizuje zmienne
    // Parametr:
    // - int rozmiar: maksymalna pojemnoœæ kolejki (domyœlnie ustawiona na 30)
    Kolejka(int rozmiar = 30)
    {
        maxRozmiar = rozmiar;
        ile = 0;
        tablica = new osoba[maxRozmiar];
    }

    // Destruktor, który zwalnia pamiêæ dynamiczn¹
    ~Kolejka()
    {
        delete[] tablica;
        cout << "Pamiec zostala zwolniona (destruktor)." << endl;
    }

    // 1. Funkcja wczytuj¹ca dane z pliku
    // Parametr:
    // - const string& nazwaPliku: nazwa lub œcie¿ka do pliku tekstowego, z którego pobieramy dane
    void wczytaj_z_pliku(const string& nazwaPliku)
    {
        ifstream plik(nazwaPliku);
        if (!plik.is_open())
        {
            cout << "Nie mozna otworzyc pliku!" << endl;
            return;
        }

        ile = 0;
        while (ile < maxRozmiar && plik >> tablica[ile].nr >> tablica[ile].imie >> tablica[ile].nazwisko)
        {
            ile++;
        }
        plik.close();
        cout << "Wczytano " << ile << " rekordow z pliku." << endl;
    }

    // 2. Wypisz dane na ekranie (brak parametrów)
    void wypisz()
    {
        if (ile == 0)
        {
            cout << "Kolejka jest pusta." << endl;
            return;
        }
        cout << "\n--- LISTA UCZNIOW ---" << endl;
        for (int i = 0; i < ile; i++)
        {
            cout << "Nr: " << tablica[i].nr << " | Imie: " << tablica[i].imie << " | Nazwisko: " << tablica[i].nazwisko << endl;
        }
        cout << "---------------------" << endl;
    }

    // 3. Funkcja zapisuj¹ca dane do pliku
    // Parametr:
    // - const string& nazwaPliku: nazwa pliku docelowego, w którym zapiszemy aktualny stan kolejki
    void zapisz_do_pliku(const string& nazwaPliku)
    {
        ofstream plik(nazwaPliku);
        if (!plik.is_open())
        {
            cout << "Nie mozna otworzyc pliku do zapisu!" << endl;
            return;
        }
        for (int i = 0; i < ile; i++)
        {
            plik << tablica[i].nr << " " << tablica[i].imie << " " << tablica[i].nazwisko << endl;
        }
        plik.close();
        cout << "Zapisano dane do pliku: " << nazwaPliku << endl;
    }

    // 4. Funkcja dodaj¹ca element (brak parametrów, dane pobierane s¹ wewn¹trz od u¿ytkownika)
    void dodaj()
    {
        if (ile >= maxRozmiar)
        {
            cout << "Kolejka jest pelna, nie mozna dodac wiecej osob." << endl;
            return;
        }

        osoba nowa;
        cout << "Podaj numer: ";
        cin >> nowa.nr;
        cout << "Podaj imie: ";
        cin >> nowa.imie;
        cout << "Podaj nazwisko: ";
        cin >> nowa.nazwisko;

        tablica[ile] = nowa;
        ile++;
        cout << "Dodano pomyslnie!" << endl;
    }

    // 5. Funkcja która sortuje po nazwisku alfabetycznie
    void posortuj()
    {
        // Parametry w wyra¿eniu lambda (kryterium porównania):
        // - const osoba& a: pierwszy obiekt osoby brany do porównania
        // - const osoba& b: drugi obiekt osoby brany do porównania
        sort(tablica, tablica + ile, [](const osoba& a, const osoba& b) {
            return a.nazwisko < b.nazwisko;
        });
        cout << "Kolejka zostala posortowana alfabetycznie po nazwisku." << endl;
    }

    // 6. Funkcja która usuwa po numerze (brak parametrów, szukany numer pobierany z konsoli)
    void usun_nr()
    {
        if (ile == 0)
        {
            cout << "Kolejka jest pusta." << endl;
            return;
        }

        int szukanyNr;
        cout << "Podaj numer osoby do usuniecia: ";
        cin >> szukanyNr;

        int index = -1;
        for (int i = 0; i < ile; i++)
        {
            if (tablica[i].nr == szukanyNr)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Nie znalecono osoby o takim numerze." << endl;
            return;
        }

        // Przesuniêcie elementów w lewo w tablicy
        for (int i = index; i < ile - 1; i++)
        {
            tablica[i] = tablica[i + 1];
        }
        ile--;
        cout << "Usunieto osobe o numerze " << szukanyNr << endl;
    }

    // Obs³uga menu g³ównego (brak parametrów)
    void menu()
    {
        int wybor;
        do
        {
            cout << "\n=== MENU KOLEJKI ===" << endl;
            cout << "1. Wczytaj z pliku" << endl;
            cout << "2. Wypisz dane" << endl;
            cout << "3. Zapisz do pliku" << endl;
            cout << "4. Dodaj" << endl;
            cout << "5. Posortuj" << endl;
            cout << "6. Usun po numerze" << endl;
            cout << "7. Koniec" << endl;
            cout << "Wybierz opcje (1-7): ";
            cin >> wybor;

            switch (wybor)
            {
            case 1:
                wczytaj_z_pliku("dane.txt");
                break;
            case 2:
                wypisz();
                break;
            case 3:
            {
                zapisz_do_pliku("wynik.txt");
                break;
            }
            case 4:
                dodaj();
                break;
            case 5:
                posortuj();
                break;
            case 6:
                usun_nr();
                break;
            case 7:
                cout << "Koniec programu." << endl;
                break;
            default:
                cout << "Nieznana opcja. Wybierz ponownie." << endl;
            }
        } while (wybor != 7);
    }
};

int main()
{
    // Tworzenie obiektu kolejki o maksymalnym rozmiarze 30
    // Przekazany argument w nawiasie:
    // - 30: inicjalizuje parametr 'rozmiar' w konstruktorze klasy Kolejka
    Kolejka k(30);

    // Uruchomienie menu programu
    k.menu();

    // Pamiêæ zostanie automatycznie zwolniona w destruktorze po zakoñczeniu funkcji main
    return 0;
}
