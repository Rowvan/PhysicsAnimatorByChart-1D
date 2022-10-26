/*
 * Orion Mulgrew
 * P8 Kintzel
 * Project: U1 Motion
 * File: Cart Header
 * Start: 9/19/2022
 */

#ifndef CART_H
#define CART_H

#include <iostream>
#include "Table.h"
#include<Windows.h>
using namespace std;

class Cart
{
private:
    Table table;
    double time;
    double max_dist;
    double min_dist;
    double dist;
    string dist_label;

    double o_min_dist;
    double o_max_dist;

    bool anim_show_end_logs = true;
    bool anim_show_logs = false;
    bool show_anim_frames = true;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    int FPS = 25;
    const double TIME_WAIT = 1.0 / FPS;
    int TRACK_LEN = 100;

    int anim_cart_color = 12;
    int anim_track_color = 7;
    int anim_label_color = 7;
    int logs_color = 7;

    int getPos();
    string genDistLabel();

    double getTableMinDist();
    double getTableMaxDist();

public:
    Cart(Table, bool = true, bool = false, bool = true, int = 12, int = 7, int = 7, int = 25, int = 100, int = 7);
    void setup();
    void printGraph();
    void animate();
    double getMaxDist()
    {
        return max_dist;
    }
    double getMinDist()
    {
        return min_dist;
    }
};

#endif // CART_H