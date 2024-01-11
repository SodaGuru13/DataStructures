#include <iostream>
#include <iomanip>
#include <time.h>
#include <fstream>
#include "maxheap20.h"
using namespace std;

void ProcessCommandFile(heap& h, string filename)
{
    h.clearArray();
    ifstream inputFile;
    inputFile.open(filename);

    if (!inputFile.is_open())
        cout << "Unable to open file" << endl;
    else
    {
        int input;
        inputFile >> input;
        while (!inputFile.eof() && input != 0)
        {
            switch (input)
            {
            case 1:    // Add
                inputFile >> input;
                h.add(input);
                break;
            case -1:  // Delete
                h.deleteMax();
                break;
            case 3:   // Print
                h.printArray();
                break;
            }
            inputFile >> input;
        }
        inputFile.close();
    }
}

void Heap1(heap& h)
{
    int cmd;
    cout << "Enter 1-read command file or (0 to stop): ";
    cin >> cmd;
    while (cmd != 0)
    {
        string filename;
        cout << "Enter command file name : ";
        cin >> filename;
        ProcessCommandFile(h, filename);
        cout << "Enter 1-read command file or (0 to stop): ";
        cin >> cmd;
    }
}
int main(int argc, char* argv[])
{
    heap h(150);
    if (argc == 2)
    {
        ProcessCommandFile(h, argv[1]);
        return 0;
    }
    int cmd;
    cout << "Enter 1-Heap, 2-HeapDescSort, 3-Heap, 4-Bubble, 0-Exit: ";
    cin >> cmd;
    while (cmd != 0)
    {
        switch (cmd)
        {
            case 1:
                Heap1(h);
                break;
            case 2:
                h.addRandomHeapNumbers(15);
                h.printDescSortList();
                break;
            case 3:
                h.addRandomHeapNumbers(15);
                h.printArray();
                break;
            case 4:
                h.addRandomArrayNumbers(15);
                h.bubbleSort();
                h.printArray();
                break;
        }
        cout << "Enter 1-Heap, 2-HeapDescSort, 3-Heap, 4-Bubble, 0-Exit: ";
        cin >> cmd;
    }

    return 0;
}

