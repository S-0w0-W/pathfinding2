#include "FindFood.h"
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include "LinkedList.h"
#include "Data.h"
#include "BFS.h"
using namespace std;

int** FindFood(int startR, int startC) {
    int foodListSize = 0;
    while (food_list[foodListSize][0] != NULL) {
        foodListSize++;
    }
    int** foodPath = new int* [2]; 


    int** path;
    int start[2] = { startC, startR };
    int stepsList[999];
    int eaten[999] = { 0 };
    LinkedList finalPathR;
    LinkedList finalPathC;
    int stepCount = 0;

    // find shortest path from starting pos to all foods
    for (int l = 0; l < foodListSize; l++) {
        //cout << "eaten array: ";
        for (int i = 0; i < foodListSize; i++) {
            //cout << eaten[i];
            //cout << " ";
        }
        //cout << "\n";
        for (int j = 0; j < foodListSize; j++) {
            if (eaten[j] != 1) {
                stepCount = 0;
                path = bfs(start[0], start[1], food_list[j][1], food_list[j][0]);
                while (path[0][stepCount] > 0) {
                    stepCount++;
                }
                stepsList[j] = stepCount;
            }
        }
        int smallest = 999;
        int indxSmallest;
        //cout << "\nList of steps from current location to all other foods:\n";
        for (int i = 0; i < foodListSize; i++) {
            if (stepsList[i] < smallest && eaten[i] != 1) {
                smallest = stepsList[i];
                indxSmallest = i;
            }
            //cout << stepsList[i];
            //cout << " ";
        }
        //cout << "\nSmallest number of steps: ";
        //cout << smallest;
        //cout << "\nIndex of smallest index: ";
        //cout << indxSmallest;
        //cout << "\n";

        eaten[indxSmallest] = 1;
        stepsList[indxSmallest] = 999;
        path = bfs(start[0], start[1], food_list[indxSmallest][1], food_list[indxSmallest][0]);

        stepCount = 0;
        while (path[0][stepCount] > 0) {
            stepCount++;
        }
        for (int i = stepCount -1; i >= 0; i--) {
            finalPathR.Insert(path[0][i]);
            finalPathC.Insert(path[1][i]);
        }
        if (l > 0 && l < foodListSize - 1) {
            finalPathR.DequeueTail();
            finalPathC.DequeueTail();
        }
        
        start[0] = food_list[indxSmallest][1];
        start[1] = food_list[indxSmallest][0];

    }

    int* returnR = finalPathR.ReturnReverse(finalPathR.Popindx(finalPathR.Size()));
    int* returnC = finalPathC.ReturnReverse(finalPathC.Popindx(finalPathC.Size()));

    for (int i = 0; i < finalPathR.Size(); i++) {
        map[returnR[i]][returnC[i]] = 5;
    }
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 19; j++) {
            cout << map[i][j];
            if (j == 19 - 1) {
                cout << "\n";
            }

        }
    }

    for (int i = 0; i < 2; i++)
    {
        foodPath[i] = new int[finalPathR.Size()];

        for (int j = 0; j < finalPathR.Size(); j++)
        {
            if (i == 0) {
                foodPath[i][j] = returnR[j];
            }
            else {
                foodPath[i][j] = returnC[j];
            }

        }
    }
    return foodPath;
}

