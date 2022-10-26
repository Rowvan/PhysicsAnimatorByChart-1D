/*
 * Orion Mulgrew
 * P8 Kintzel
 * Project: U1 Motion
 * File: Table Header
 * Start: 9/19/2022
 */

#ifndef TABLE_H
#define TABLE_H

#include <iostream>

using namespace std;

string trimZerosDouble(string, int = 0);

class Table
{
private:
    double distanceInitial, distanceFinal, velocityInitial, velocityFinal, acceleration, time, time2;

public:
    Table();
    void setDI(double);
    void setDF(double);
    void setVI(double);
    void setVF(double);
    void setAccel(double);
    void setTime(double);

    double getDI();
    double getDF();
    double getVI();
    double getVF();
    double getAccel();
    double getTime();

    void user_setValues();
    int getCollectedValues();
    bool trySolveForUnknowns();
    bool canBeDone();
    void print();
    void reset();
};

#endif // TABLE_H