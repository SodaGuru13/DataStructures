#include "maxheap20.h"

// default constructor
heap::heap(int n)
{
   	arr = new int[n];
    last = -1;
}
void heap::upheap()
{
    int i = last;
    while (i != 0 && arr[parent(i)] < arr[i])
    {
        swapArrayPos(&arr[parent(i)], &arr[i]);
        i = parent(i);
    }

}
void heap::add(int x)
{
    last++;
    arr[last] = x;
    upheap();
}



// print the array  ( use <= last if you go that route )
void heap::printArray()
{
    int i;
	for (i = 0; i <= last; ++i)
        cout << setw(4) << arr[i];
	cout << "--> heap";
	cout << endl;
}


void heap::swapArrayPos(int *pos1, int *pos2)
{
    int tmp = *pos1;
    *pos1 = *pos2;
    *pos2 = tmp;
}

void heap::bubbleSort()
{
    for (int i = 0; i <= last; ++i)
    {
        for (int j = 0; j <= last - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swapArrayPos(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// start at item last, move it up until
//   heap property is restored

void heap::addRandomHeapNumbers(int j)
{
    last = -1;
    srand(1);
    for (int i = 0; i < j; i++)
    {
        add(rand() % 100 + 1);
    }
}

void heap::addRandomArrayNumbers(int j)
{
    last = -1;
    srand(1);
    for (int i = 0; i < j; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    last = j-1;
}
void heap::downheap(int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l <= last && arr[i] < arr[l])
        largest = l;
    if (r <= last && arr[largest] < arr[r])
        largest = r;
    if (largest != i)
    {
        swapArrayPos(&arr[i], &arr[largest]);
        downheap(largest);
    }
}

int heap::deleteMax()
{
    if (last < 0)
        return -1;
    int val = arr[0];
    arr[0] = arr[last];
	last--;
    downheap(0);
    return val;
}

void heap::printDescSortList()
{
    int max;
	printArray();
    max = deleteMax();
    while (max > 0)
    {
        cout << setw(4) << max;
        max = deleteMax();
    }
	cout << "--> list";
    cout << endl;
}
