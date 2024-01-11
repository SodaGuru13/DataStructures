#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class heap
{
public:
    heap(int n);
    void add(int x);
    void printArray();
    int  deleteMax();
    void addRandomHeapNumbers(int i);
    void addRandomArrayNumbers(int i);
    void printDescSortList();
    void bubbleSort();
    void clearArray() { last = -1; }
private:
    int* arr;
    int last;
    void upheap();
    void downheap(int i);
    void swapArrayPos(int *pos1, int *pos2);
    int  parent(int i) { return (i - 1) / 2; }
    int  left(int i) { return (2 * i + 1); }
    int  right(int i) { return (2 * i + 2); }
};
