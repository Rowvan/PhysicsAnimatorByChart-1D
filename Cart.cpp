/*
 * Rowvan
 * Project: Animating Motion 1D
 * File: Cart Implementation
 * Start: 9/19/2022
 */

// :)

#include "Cart.h"
#include "Table.h"
#include<Windows.h>
#include<string>
#include<chrono>
#include<conio.h>
#include<windows.h>
#include<string>
using namespace std;

double Cart::getTableMaxDist()
{
    double max_dist = INT_MIN;
    double v_time = 0;
    for (int x = 0; x < (int)(table.getTime() / (1.0 / FPS)); x++)
    {
        v_time = x * TIME_WAIT;
        max_dist = max(max_dist, (table.getDI() + (table.getVI() * v_time) + (table.getAccel() * (v_time * v_time) / 2)));
        //if (max_dist > table.getDF())
            //cout << x << " -> " << max_dist << " meters, " << v_time << " seconds" << endl;
    }
    return max(max_dist, table.getDF());
}

double Cart::getTableMinDist()
{
    double min_dist = INT_MAX;
    double v_time = 0;
    for (int x = 0; x < (int)(table.getTime() / (1.0 / FPS)); x++)
    {
        v_time += TIME_WAIT;
        min_dist = min(min_dist, (table.getDI() + (table.getVI() * v_time) + (table.getAccel() * (v_time * v_time) / 2)));
    }
    return min(min_dist, min(table.getDI(), table.getDF()));
}

Cart::Cart(Table table, bool anim_show_end_logs,
                        bool anim_show_logs,
                        bool show_anim_frames,
                        int anim_cart_color,
                        int anim_track_color,
                        int anim_label_color,
                        int anim_fps,
                        int anim_track_len,
                        int logs_color
)
{
    this->table = table;
    this->anim_show_end_logs = anim_show_end_logs;
    this->anim_show_logs = anim_show_logs;
    this->show_anim_frames = show_anim_frames;
    
    this->anim_cart_color = anim_cart_color;
    this->anim_track_color = anim_track_color;
    this->anim_label_color = anim_label_color;
    this->FPS = anim_fps;
    this->TRACK_LEN = anim_track_len;
    this->logs_color = logs_color;
    time = 0.0;
    dist = 0.0;
    max_dist = 0.0;
    min_dist = 0.0;
    o_min_dist = 0.0;
    o_max_dist = 0.0;
}

void Cart::setup()
{
    double old_di = table.getDI();
    double old_df = table.getDF();
    bool df_pos = old_df >= 0;
    bool di_pos = old_di >= 0;

    //cout << "Di: " << old_di << endl <<
            //"Df: " << old_df << endl;
    

    double new_df;
    double new_di;

    max_dist = getTableMaxDist();
    min_dist = getTableMinDist();

    o_max_dist = getTableMaxDist();
    o_min_dist = getTableMinDist();

    //cout << "\n---------------------------\n" << endl;

    if (df_pos && di_pos)
    {
        if (old_di < old_df)
        {
            new_di = 0.0;
            new_df = old_df - old_di;

            dist = (old_df - old_di) / TRACK_LEN;
        }
        else
        {
            new_di = old_di - old_df;
            new_df = 0.0;

            dist = (old_di + old_df) / TRACK_LEN;
        }
    }
    else if (df_pos && !di_pos)
    {
        new_di = 0.0;
        new_df = abs(old_df) + abs(old_di);

        min_dist = old_di;
        max_dist = old_df;

        dist = (abs(old_di) + abs(old_df)) / TRACK_LEN;
    }
    else if (!df_pos && di_pos)
    {
        new_di = abs(old_df) + abs(old_di);
        new_df = 0.0;

        dist = (abs(min_dist) + abs(max_dist)) / TRACK_LEN;
        //dist = (abs(50) + abs(-100)) / TRACK_LEN;
        //cout << "v_Dist: " << new_di << endl << 
                //"a_Dist: " << dist << endl;
    }
    else if (!df_pos && !di_pos)
    {
        if (old_di < old_df)
        {
            new_di = 0.0;
            new_df = abs(old_di) - abs(old_df);

            dist = (abs(old_di) - abs(old_df)) / TRACK_LEN;
        }
        else
        {
            new_di = abs(old_df) - abs(old_di);
            new_df = 0.0;

            dist = (abs(old_df) - abs(old_di)) / TRACK_LEN;
        }
    }

    //cout << "Initial Min: " << min_dist << endl <<
            //"Initial Max: " << max_dist << endl;
    
    // dist = (abs(max_dist) + abs(min_dist)) / TRACK_LEN;
    //cout << min_dist << " | " << max_dist << endl;
    dist_label = genDistLabel();

    //cout << "New Di: " << new_di << endl << "new Df: " << new_df << endl;

    table.setDI(new_di);
    table.setDF(new_df);

    max_dist = getTableMaxDist();
    min_dist = getTableMinDist();

    //cout << "Initial Min: " << min_dist << endl <<
        //"Initial Max: " << max_dist << endl;
    //system("pause");
}

void Cart::printGraph()
{
    //system("cls");
    int pos = getPos();
    string placement = "", track = "";
    for (int x = 0; x <= TRACK_LEN; x++)
    {
        placement += (x == pos ? "0" : " ");
        track += "-";
    }
    SetConsoleTextAttribute(handle, anim_cart_color);
    cout << placement << endl;
    SetConsoleTextAttribute(handle, anim_track_color);
    cout << track << endl;
    SetConsoleTextAttribute(handle, anim_label_color);
    cout << dist_label << endl;
    SetConsoleTextAttribute(handle, 7);
    // cout << getDistLabel() << endl;
    time += TIME_WAIT;
}

int Cart::getPos()
{
    double current_dist;
    int nextINDX;
    if (table.getDI() < table.getDF())
    {
        current_dist = abs(table.getDI() + (table.getVI() * time) + (table.getAccel() * (time * time) / 2)) + min_dist;
        nextINDX = (int)round(current_dist / max_dist * TRACK_LEN);
    }
    else
    {
        current_dist = abs(table.getDI() + (table.getVI() * time) + (table.getAccel() * (time * time) / 2)) + min_dist;
        nextINDX = (int)round(current_dist / max_dist * TRACK_LEN);
    }

    if (anim_show_logs)
    {
        SetConsoleTextAttribute(handle, logs_color);
        cout << "Current Dist: " << (current_dist - abs(o_min_dist)) << " meters" <<
                "\nCurrent INDX: " << nextINDX <<
                "\nTime: " << time << endl;
        SetConsoleTextAttribute(handle, 7);
    }
    return abs(nextINDX);
}

void Cart::animate()
{
    string prnt_str = "";
    for (int x = 0; x < 10000; x++)
    {
        prnt_str += "\n";
    }
    cout << prnt_str;
    chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
    int iterations = (int)(table.getTime() / (1.0 / FPS));
    //cout << table.getTime() << " / " << (1.0 / FPS) << " = " << iterations << endl << endl;
    for (int x = 0; x < iterations; x++)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        if (show_anim_frames)
        {
            SetConsoleTextAttribute(handle, logs_color);
            cout << "Current Frame: " << x << "/" << iterations << "  (" << trimZerosDouble(to_string((int)(100.0 * (double)x / (double)(iterations)))) << "%)" << endl;
            SetConsoleTextAttribute(handle, 7);
        }
        printGraph();
        Sleep(1000 / FPS / 1.48);
        //system("cls");
    }
    time = table.getTime();
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    
    if (show_anim_frames)
    {
        SetConsoleTextAttribute(handle, logs_color);
        cout << "Current Frame: " << iterations << "/" << iterations << "  (" << 100 << "%)" << endl;
        SetConsoleTextAttribute(handle, 7);
    }
    printGraph();
    chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    if (anim_show_end_logs)
    {
        SetConsoleTextAttribute(handle, logs_color);
        cout << endl << endl << "end animation ->\n    elapsed time: " << elapsed_time.count() << "s\n    req time: " << table.getTime() << "\n    time as percent: " << (elapsed_time.count() / table.getTime()) * 100 << "%" << endl;
        SetConsoleTextAttribute(handle, 7);
    }
}

string Cart::genDistLabel()
{
    string label = "";
    string to_add;
    int len;
    double v_dist = min_dist;

    double mid_dist = (min_dist + max_dist) / 2.0;
    
    string min_dist_str = trimZerosDouble(to_string(min_dist), 2) + "m";
    string max_dist_str = trimZerosDouble(to_string(max_dist), 2) + "m";
    string mid_dist_str = trimZerosDouble(to_string(mid_dist), 2) + "m";
    string zero_dist_str = "";
    if (min_dist != 0 && max_dist != 0 && mid_dist != 0)
        zero_dist_str = "0m";

    //cout << "Min: " << min_dist_str << endl <<
            //"Mid: " << mid_dist_str << endl <<
            //"Max: " << max_dist_str << endl << 
            //"Dist: " << dist << endl;

    bool min_dist_str_added = false;
    bool mid_dist_str_added = false;
    bool max_dist_str_added = false;
    bool zero_dist_str_added = false;

    int total_str_len = min_dist_str.length() + mid_dist_str.length();

    for (int x = 0; x < TRACK_LEN - total_str_len; x++)
    {
        //cout << x << " -> " << v_dist << endl;
        if (v_dist >= min_dist && !min_dist_str_added)
        {
            label += min_dist_str;
            min_dist_str_added = true;
            zero_dist_str_added = (min_dist == 0 ? true : false);
        }
        else if (v_dist >= 0 && min_dist != 0 && !zero_dist_str_added && min_dist < 0)
        {
            label += zero_dist_str;
            zero_dist_str_added = true;
        }
        else if (v_dist >= mid_dist && !mid_dist_str_added)
        {
            //cout << endl << "added mid" << endl << endl;
            label += mid_dist_str;
            mid_dist_str_added = true;
        }
        else
        {
            label += " ";
        }
        v_dist += dist;
    }
    while (label.length() <= TRACK_LEN)
    {
        label += " ";
    }
    for (int x = 0; x < max_dist_str.length(); x++)
    {
        label.pop_back();
    }
    label += max_dist_str;
    //cout << label << endl;
    //system("pause");
    return label;
}