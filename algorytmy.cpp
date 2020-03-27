#include "algorytmy.hh"

// MERGE SORT
template <typename T>
void merge(T *tab, T *tmp, int lewa, int srodek, int prawa)
{
	for (int i = lewa; i <= prawa; i++)
		tmp[i] = tab[i];

	int i = lewa;
	int j = srodek + 1;
	int q = lewa;

	while (i <= srodek && j <= prawa)
	{
		if (tmp[i] < tmp[j])
			tab[q++] = tmp[i++];
		else
			tab[q++] = tmp[j++];
	}
	while (i <= srodek)
		tab[q++] = tmp[i++];
}
template <typename T>
void mergesort(T *tab, T *tmp, int lewa, int prawa)
{
	if (lewa < prawa)
	{
		int srodek = (lewa + prawa) / 2;

		mergesort(tab, tmp, lewa, srodek);

		mergesort(tab, tmp, srodek + 1, prawa);

		merge(tab, tmp, lewa, srodek, prawa);
	}
}

//QUICK SORT
template <typename T>
int partition(T *tab, int left, int right)
{
	int pivot = tab[(left + right) / 2], i = left, j = right; //pivot selection is always middle

	while (true)
	{
		while (tab[j] > pivot)
			j--;

		while (tab[i] < pivot)
			i++;

		if (i < j)
			std::swap(tab[i++], tab[j--]);
		else
			return j;
	}
}
template <typename T>
void quicksort(T *tab, int lewa, int prawa)
{
	if (lewa < prawa)
	{
		int q = partition(tab, lewa, prawa);
		quicksort(tab, lewa, q);
		quicksort(tab, q + 1, prawa);
	}
}

// INTRO SORT
template <typename T>
void insertionsort(T *tab, int lewa, int prawa)
{
	for (int i = lewa + 1; i <= prawa; i++)
	{
		int klucz = tab[i];
		int j = i;

		while (j > lewa && tab[j - 1] > klucz)
		{
			tab[j] = tab[j - 1];
			j--;
		}
		tab[j] = klucz;
	}
}
template <typename T>
void heapsort(T *lewa, T *prawa)
{
	std::make_heap(lewa, prawa);
	std::sort_heap(lewa, prawa);
}

template <typename T>
void introsort(T *tab, T *lewa, T *prawa, int maxdepth)
{
	if ((prawa - lewa) < 16)
		insertionsort(tab, lewa - tab, prawa - tab);
	else if (maxdepth == 0)
		heapsort(lewa, prawa + 1);
	else
	{
		int pivot = partition(tab, lewa - tab, prawa - tab);
		introsort(tab, lewa, tab + pivot, maxdepth - 1);
		introsort(tab, tab + pivot + 1, prawa, maxdepth - 1);
	}
}
template <typename T>
void introWywolanie(T *tab, int lewa, int prawa, int maxdepth)
{
	introsort(tab, tab, tab + prawa, maxdepth);
}

template void mergesort<int>(int *, int *, int, int);
template void quicksort<int>(int *, int, int);
template void introWywolanie<int>(int *, int, int, int);