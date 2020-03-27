#include "algorytmy.hh"
#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

template <typename T>
void WyswietlTab(T *tab, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << tab[i] << " ";
}

template <typename T>
T *StworzTab(int n)
{
    return new T[n];
}

template <typename T>
void UsunTab(T *table)
{
    delete[] table;
}

template <typename T>
void WypelnijTab(T *tab, int n)
{
    for (int i = 0; i < n; i++)
        tab[i] = rand() % 10000 + 1;
}

template <typename T>
void procentowanie(T *tab, int n, double procent)
{
    if (procent == 100) //sortuje w odwrotnej kolejności
    {
        std::sort(tab, tab + n, greater<T>());
        return;
    }
    std::sort(tab, tab + (int)((n * procent) / 100));
}
void otwieraniePliku(std::ofstream &file)
{
    if (!file.is_open())
    {
        std::cout << "Plik nie otworzył się :(";
        std::cin.get();
        exit(1);
    }
}

int main()
{
    std::ofstream file("Sortowanie.txt");

    otwieraniePliku(file);

    srand(time(NULL));

    int ntab[5] = {10000, 50000, 100000, 500000, 1000000};
    double procenttab[8] = {0, 25, 50, 75, 95, 99, 99.7, 100};

    int powtorzenia = 101;
    int lewa = 0;
    double suma = 0;
    double srednia = 0;

    // MERGE SORT
    for (double procent : procenttab) //dla każdego procenta
    {
        for (int n : ntab) // dla każdego rozmiaru
        {
            int *tab = StworzTab<int>(n);
            int *tmp = StworzTab<int>(n);
            for (int i = 1; i < powtorzenia; i++) // 100 tablic
            {
                int prawa = n - 1;
                WypelnijTab<int>(tab, n);
                procentowanie(tab, n, procent);

                auto t_start = chrono::high_resolution_clock::now();
                mergesort<int>(tab, tmp, lewa, prawa);
                auto t_end = chrono::high_resolution_clock::now();

                file << chrono::duration<double, std::milli>(t_end - t_start).count() << "     " << i << endl;
                suma += chrono::duration<double, std::milli>(t_end - t_start).count();
            }

            UsunTab<int>(tab);
            UsunTab<int>(tmp);

            srednia = suma / (powtorzenia - 1);

            file << endl
                 << srednia << "     ROZMIAR POSORTOWANY" << endl
                 << endl;

            srednia = 0;
            suma = 0;
        }
        file << procent << " % już posortowane!" << endl;
    }
    file << "             MERGE JESTEŚ JUŻ SKOŃCZONY!" << endl;

    //                      QUICK SORT
    for (double procent : procenttab) //dla każdego procenta
    {
        for (int n : ntab) // dla każdego rozmiaru
        {
            int *tab = StworzTab<int>(n);
            for (int i = 1; i < powtorzenia; i++)
            {
                int prawa = n - 1;
                WypelnijTab<int>(tab, n);
                procentowanie(tab, n, procent);

                auto t_start = chrono::high_resolution_clock::now();
                quicksort<int>(tab, lewa, prawa);
                auto t_end = chrono::high_resolution_clock::now();

                file << chrono::duration<double, std::milli>(t_end - t_start).count() << "     " << i << endl;
                suma += chrono::duration<double, std::milli>(t_end - t_start).count();
            }
            UsunTab<int>(tab);

            srednia = suma / (powtorzenia - 1);

            file << endl
                 << srednia << "     ROZMIAR POSORTOWANY" << endl
                 << endl;

            srednia = 0;
            suma = 0;
        }
        file << procent << " % już posortowane!" << endl;
    }
    file << "             QUICKSORT JESTEŚ JUŻ SKOŃCZONY!" << endl;

    //                      INTRO SORT
    for (double procent : procenttab) //dla każdego procenta
    {
        for (int n : ntab) // dla każdego rozmiaru
        {
            int *tab = StworzTab<int>(n);
            for (int i = 1; i < 101; i++)
            {
                int prawa = n - 1;
                WypelnijTab<int>(tab, n);
                procentowanie(tab, n, procent);

                auto t_start = chrono::high_resolution_clock::now();
                introWywolanie<int>(tab, lewa, prawa, 2 * log(n));
                auto t_end = chrono::high_resolution_clock::now();

                file << chrono::duration<double, std::milli>(t_end - t_start).count() << "     " << i << endl;
                suma += chrono::duration<double, std::milli>(t_end - t_start).count();
            }
            UsunTab<int>(tab);

            srednia = suma / (powtorzenia - 1);

            file << endl
                 << srednia << "     ROZMIAR POSORTOWANY" << endl
                 << endl;

            srednia = 0;
            suma = 0;
        }
        file << procent << " % już posortowane!" << endl;
    }
    file << "             INTRO JESTEŚ JUŻ SKOŃCZONY!" << endl;

    cin.get();
    file.close();
    return 0;
}