/***********************************************************************
* Module:
*    Week 11, Sort Heap
*    Brother Helfrich, CS 235
* Author:
*    Yirang LIm
* Summary:
*    This program will implement the Heap Sort
************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

#include <iostream>

using namespace std;

template <class T>
class Heap
{
public:
	Heap();
	Heap(T array[], int num);

	T getMax() const;

	void sort();
	void deleteMax();
private:
	T * array;
	int num;

	void percolateDown(int index);
	void swap(int i1, int i2);
};

template <class T>
Heap<T>::Heap()
{
	array = NULL;
	num = 0;
}

template <class T>
Heap<T>::Heap(T array[], int num)
{
	this->array = array;
	this->num = num - 1;

	for (int i = num / 2 - 1; i > 1; i--)
		percolateDown(i);
}

template <class T>
T Heap<T>::getMax() const
{
	T max;

	for (int i = 0; i < num; i++)
	{
		max = array[0];

		if (array[i] > max)
			max = array[i];
	}

	return max;
}

template <class T>
void Heap<T>::swap(int x, int y)
{
	T temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

template <class T>
void Heap<T>::sort()
{
	while (num > 1)
	{
		swap(1, num);
		num--;
		percolateDown(1);
	}
}

template <class T>
void Heap<T>::percolateDown(int index)
{
	int indexLeft = index * 2;		// getting the index of the left child node
	int indexRight = indexLeft + 1; // getting the index of the right child node

	if (indexLeft < num)
	{
		if (indexRight <= num && array[indexRight] > array[indexLeft] && array[indexRight] > array[index])
		{
			swap(index, indexRight);
			percolateDown(indexRight);
		}
		else if (indexLeft <= num && array[indexLeft] > array[index])
		{
			swap(index, indexLeft);
			percolateDown(indexLeft);
		}
	}
}

/*****************************************************
* SORT HEAP
* Perform the heap sort
****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
	Heap<T>* h = new Heap<T>(array, num);
	h->sort();
}


#endif // SORT_HEAP_H
