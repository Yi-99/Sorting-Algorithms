/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    Yirang Lim
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

#include <iostream>

using namespace std;

template <class T>
void merge(T* array, int low, int mid, int high);
template <class T>
void mergeSort(T* array, int low, int high);

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
	// code extracted from https://github.com/zahidalidev/MergeSort-using-cpp/blob/master/mergeSort.cpp

	int low = 0;
	int high = num;

	mergeSort(array, 0, num - 1);
}

template <class T>
void mergeSort(T* array, int low, int high)
{
	if (low >= high)
		return;
	else
	{
		int mid = floor((low + high) / 2);
		//divide the array at mid and sort independently using merge sort
		mergeSort(array, low, mid);
		mergeSort(array, mid + 1, high);
		//merge or conquer sorted arrays
		merge(array, low, mid, high);
	}
}

template <class T>
void merge(T* array, int low, int mid, int high)
{

	T temp[100];
	int low1, low2, buffer;
	low1 = low;
	buffer = low;
	low2 = mid + 1;

	while (low1 <= mid && low2 <= high)
	{
		if (array[low1] < array[low2])
		{
			temp[buffer] = array[low1];
			buffer++;
			low1++;
		}
		else
		{
			temp[buffer] = array[low2];
			buffer++;
			low2++;
		}
	}
	while (low1 <= mid)
	{
		temp[buffer++] = array[low1++];
	}
	while (low2 <= high)
	{
		temp[buffer++] = array[low2++];
	}
	for (low1 = low; low1 <= high; low1++) // copy in the sorted values
	{
		array[low1] = temp[low1];
	}
}

#endif // SORT_MERGE_H
