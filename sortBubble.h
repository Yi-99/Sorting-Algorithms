/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    Yirang Lim
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
	for (int iPivot = num; iPivot > 1; iPivot--)
	{
		bool swapped = false;
		for (int iCheck = 0; iCheck < iPivot - 1; iCheck++)
		{
			if (array[iCheck] > array[iCheck + 1])
			{
				T buffer = array[iCheck];
				T buffer2 = array[iCheck + 1];
				array[iCheck] = buffer2;
				array[iCheck + 1] = buffer;
				swapped = true;
			}
		}

		if (!swapped)
			return;
	}
}


#endif // SORT_BUBBLE_H
