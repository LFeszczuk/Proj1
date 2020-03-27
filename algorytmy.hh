
#ifndef ALGORYTMY_HH
#define ALGORYTMY_HH
#pragma once
#include <algorithm>


template<typename T>
void mergesort(T *tab, T *tmp, int lewa, int prawa);

template<typename T>
void quicksort(T *tab, int lewa, int prawa);

template<typename T>
void introWywolanie(T *tab, int lewa, int prawa, int maxdepth);


#endif