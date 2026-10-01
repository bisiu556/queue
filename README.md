# Projekt: Kolejka Uczniów w C++ (Program Konsolowy)

Projekt konsolowy w języku C++, który realizuje zarządzanie listą osób (uczniów) przy użyciu klas, wskaźników, dynamicznej alokacji pamięci oraz operacji na plikach tekstowych.

## Spis treści
1. [Opis programu](#opis-programu)
2. [Struktura projektu i kluczowe elementy](#struktura-projektu-i-kluczowe-elementy)
3. [Dostępne funkcjonalności (Menu)](#dostepne-funkcjonalnosci-menu)
4. [Wymagania systemowe i kompilacja](#wymagania-systemowe-i-kompilacja)
5. [Struktura plików wejściowych i wyjściowych](#struktura-plikow-wejsciowych-i-wyjsciowych)

---

## Opis programu

Aprogram zarządza kolekcją danych za pomocą dedykowanej klasy **`Kolejka`**. Wykorzystuje dynamiczną tablicę obiektów struktury `osoba`, co pozwala na elastyczne zarządzanie pamięcią w czasie wykonywania programu. Pamięć jest automatycznie czyszczona przy użyciu destruktora (`delete[]`), co zapobiega wyciekom pamięci.

---

## Struktura projektu i kluczowe elementy

* **Struktura `osoba`**: Przechowuje podstawowe dane o uczniu:
  * `int nr` – numer porządkowy / identyfikator,
  * `string imie` – imię ucznia,
  * `string nazwisko` – nazwisko ucznia.
* **Klasa `Kolejka`**:
  * **Pola prywatne**: `ile` (aktualna liczba elementów), `maxRozmiar` (maksymalny rozmiar), `tablica` (wskaźnik na dynamiczną tablicę typu `osoba`).
  * **Konstruktor (`Kolejka(int rozmiar)`)**: Alokuje pamięć dla określonej liczby elementów (domyślnie 30) i inicjalizuje zmienne.
  * **Destruktor (`~Kolejka()`)**: Zwalnia zaalokowaną pamięć dynamiczną po zakończeniu pracy obiektu.

---

## Dostępne funkcjonalności (Menu)

Po uruchomieniu aplikacji pojawia się interaktywne menu konsolowe z następującymi opcjami:

1. **Wczytaj z pliku** – pobiera dane uczniów z pliku tekstowego (np. `dane.txt`) do pamięci dynamicznej.
2. **Wypisz dane** – wyświetla aktualną listę uczniów w konsoli w czytelnym formacie.
3. **Zapisz do pliku** – eksportuje aktualny stan kolejki do pliku tekstowego (np. `wynik.txt`).
4. **Dodaj** – pozwala dopisać nową osobę (podając numer, imię i nazwisko), o ile nie przekroczono maksymalnego rozmiaru kolejki.
5. **Posortuj** – porządkuje elementy w kolejności alfabetycznej na podstawie nazwisk (wykorzystuje algorytm `std::sort` oraz wyrażenie lambda).
6. **Usuń po numerze** – szuka osoby o podanym numerze `nr`, usuwa ją z tablicy i przesuwa pozostałe elementy w lewo.
7. **Koniec** – zamyka program (wywołując automatycznie destruktor i zwalniając pamięć).

---

## Wymagania systemowe i kompilacja

* Kompilator obsługujący standard **C++11** lub nowszy (np. GCC/G++, Clang, MSVC).
* System operacyjny: Windows, Linux lub macOS.

### Przykład kompilacji za pomocą g++:
```bash
g++ -std=c++11 main.cpp -o program_kolejka
./program_kolejka
