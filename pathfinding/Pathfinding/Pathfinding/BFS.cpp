#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include "LinkedList.h"
#include "Data.h"
#include "BFS.h"
using namespace std;

// --------------------------------------- init ----------------------------------------------

// Variables to be passed in: 
// - start [row, col]
// - target location [row, col]
// - map [][]
//int startloc[2] = { 2, 2 };

//int startlocR = 1;
//int startlocC = 1;

//int targetloc[2] = { 3, 10 };

//int targetlocR = 13;
//int targetlocC = 3;

//int map[15][19];


// -----------------------------------------------------------------------------------------


int** bfs(int startlocR, int startlocC, int targetlocR, int targetlocC) {
    // --------------------------------------- init ----------------------------------------------
    // create new 2d array
    int** path = 0;
    path = new int* [2];

    // Size of map
    const int rowSize = 15;
    const int colSize = 19;

    // Queue initialiations
    LinkedList rowQ;
    LinkedList colQ;

    // Visited 3d matrix (same size as map) 
    int Visited[rowSize][colSize] = { 0 };

    // Directions when exploring:
    int rD[4] = { -1, 1, 0 , 0 };
    int cD[4] = { 0, 0, 1, -1 };
    // -----------------------------------------------------------------------------------------

    int indx = 1;
    rowQ.Insert(0);
    colQ.Insert(0);
    rowQ.Insert(startlocR);
    colQ.Insert(startlocC);
    Visited[startlocR][startlocC] = 1;

    struct Node* r = rowQ.Head();
    struct Node* c = colQ.Head();

    while (r->next != NULL) {

        r = r->next;
        c = c->next;
        indx++;


        if (r->data == targetlocR && c->data == targetlocC) {
            /*cout << "reached end! \n";
            cout << "Row: \n";
            int* returnR = rowQ.Return(rowQ.Popindx(indx));
            cout << "Col: \n";
            int* returnC = colQ.Return(colQ.Popindx(indx));
            cout << "\n";

            int steps = 0;
            while (returnR[steps] != NULL) {
                steps++;
            }

            for (int i = 0; i < steps - 1; i++) {
                map[returnR[i]][returnC[i]] = 5;
            }

            for (int i = 0; i < rowSize; i++) {
                for (int j = 0; j < colSize; j++) {
                    cout << map[i][j];
                    if (j == colSize - 1) {
                        cout << "\n";
                    }

                }
            }*/

            int* returnR = rowQ.Return(rowQ.Popindx(indx));
            int* returnC = colQ.Return(colQ.Popindx(indx));

            int steps = 0;
            while (returnR[steps] != NULL) {
                steps++;
            }

            for (int i = 0; i < 2; i++)
            {
                path[i] = new int[steps];

                for (int j = 0; j < steps; j++)
                {
                    if (i == 0) {
                        path[i][j] = returnR[j];
                    }
                    else {
                        path[i][j] = returnC[j];
                    }

                }
            }

            return path;
        }

        int count = 0;
        int newR = 0;
        int newC = 0;
        for (int i = 0; i < 4; i++) {
            newR = r->data + rD[i];
            newC = c->data + cD[i];

            if (newR <= 0 || newC <= 0) {
                count++;
            }
            else if (newR < 0 || newC < 0 || newR >= rowSize || newC >= colSize || Visited[newR][newC] == 1 || map[newR][newC] == 1) {
                count++;
            }

            if (count <= 0) {
                rowQ.Insert(newR);
                rowQ.Tail()->setPrev(r);
                colQ.Insert(newC);
                colQ.Tail()->setPrev(c);
                Visited[newR][newC] = 1;
            }
            count = 0;
        }

    }
}

// ==========================================================================================
