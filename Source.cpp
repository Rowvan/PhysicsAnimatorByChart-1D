/*
 * Rowvan
 * Project: Animating Motion 1D
 * File: Main Function Definition
 * Start: 9/19/2022
 */

#include<iostream>
#include"Cart.h"
#include"Table.h"
#include<Windows.h>
#include<cmath>
#include<chrono>
#include<string>

using namespace std;

void awaitInput(string = "Press Enter Key To Continue. . .");
void contPrgm(bool&, Table&);
string endlXX(int);
void printColorChart();
string getTimeStr(double);

int main()
{
    cout << "Do you need a tutorial? (y/n): ";
    string tutorialq;
    cin >> tutorialq;

    if (tutorialq == "y" || tutorialq == "Y")
    {
        string tutorial = "1. Settings - Explore settings or ask Orion for how-to.";
        tutorial +=     "\n2. Table Input - Input your table to calculate unkowns and animate motions.";
        tutorial +=     "\n3. Table Input - If you want to make up your own values, make sure you know what it all means.";
        tutorial +=     "\n4. Animation - Sit back and relax.";
        tutorial +=     "\n5. Value Re-Input - Confirm your values re-input and put in new table data";
        cout << tutorial << endl;
        awaitInput();
    }
    system("cls");

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    bool anim_show_end_logs = true;
    bool general_show_logs = false;
    bool anim_show_logs = false;
    bool show_anim_frames = true;

    bool warn_anim_len = true;

    double warn_anim_len_min = 30.0;
    int logs_color = 7;
    int anim_cart_color = 9;
    int anim_track_color = 8;
    int anim_label_color = 14;
    int anim_fps = 25;
    int anim_track_len = 100;
    
    
    string temp;
    cout << "Edit Default Settings? Enter Letters Only, Not Words (y/n): ";
    cin >> temp;
    if (temp == "y" || temp == "Y")
    {
        system("cls");
        cout << "Show General Logs? Default: no (y/n): ";
        cin >> temp;
        if (temp == "y" || temp == "Y")
            general_show_logs = true;

        system("cls");
        cout << "Show Animation Logs? Default: no (y/n): ";
        cin >> temp;
        if (temp == "y" || temp == "Y")
            anim_show_logs = true;

        system("cls");
        cout << "Show Animation Frames? Default: yes (y/n): ";
        cin >> temp;
        if (temp == "n" || temp == "N")
            show_anim_frames = false;

        system("cls");
        cout << "Show End Animation Logs? Default: yes (y/n): ";
        cin >> temp;
        if (temp == "n" || temp == "N")
            anim_show_end_logs = false;

        system("cls");
        cout << "Warn Animation too Long? Default: yes (y/n): ";
        cin >> temp;
        if (temp == "n" || temp == "N")
            warn_anim_len = false;

        if (warn_anim_len)
        {
            system("cls");
            cout << "Warn Animation too Long Min. Default: 30 (number): ";
            cin >> temp;
            try
            {
                warn_anim_len_min = stod(temp);
            }
            catch (...)
            {
                cout << "Invalid Input...";
                Sleep(1500);
            }
        }

        system("cls");
        printColorChart();
        cout << "\nLogs Color. Default: 7 (integer): ";
        cin >> temp;
        try
        {
            logs_color = stoi(temp);
        }
        catch (...)
        {
            cout << "Invalid Input...";
            Sleep(1500);
        }

        system("cls");
        printColorChart();
        cout << "\nAnimation Cart Color. Default: 9 (integer): ";
        cin >> temp;
        try
        {
            anim_cart_color = stoi(temp);
        }
        catch (...)
        {
            cout << "Invalid Input...";
            Sleep(1500);
        }

        system("cls");
        printColorChart();
        cout << "\nAnimation Track Color. Default: 8 (integer): ";
        cin >> temp;
        try
        {
            anim_track_color = stoi(temp);
        }
        catch (...)
        {
            cout << "Invalid Input...";
            Sleep(1500);
        }

        system("cls");
        printColorChart();
        cout << "\nAnimation Label Color. Default: 14 (integer): ";
        cin >> temp;
        try
        {
            anim_label_color = stoi(temp);
        }
        catch (...)
        {
            cout << "Invalid Input...";
            Sleep(1500);
        }

        system("cls");
        cout << "Animation FPS (careful about changing, reccomend default). Default: 25 (integer): ";
        cin >> temp;
        try
        {
            anim_fps = stoi(temp);
        }
        catch (...)
        {
            cout << "Invalid Input...";
            Sleep(1500);
        }

        system("cls");
        cout << "Animation Track Length (does not affect animation, everything is a ratio). Default: 100 (integer): ";
        cin >> temp;
        try
        {
            anim_track_len = stoi(temp);
        }
        catch (...)
        {
            cout << "Invalid Input...";
            Sleep(1500);
        }
    }
    
    system("cls");

    bool do_repeat = true;
    bool use_last_table = false;
    Table table = Table();

    while (do_repeat)
    {
        if (!use_last_table)
        {
            table.reset();
            try
            {
                table.user_setValues();
            }
            catch (...)
            {
                MessageBox(
                    NULL,
                    TEXT("You Entered Invalid Data. Please Enter an Integer, Decimal, or a '?' For Unknown Values.\n\nIf you forget the proper usage, restart the program and read the instructions.\nThanks :)"),
                    TEXT("STOD ERROR : STRING NAN"),
                    MB_OK
                );
                contPrgm(do_repeat, table);
                continue;
            }
            if (table.getCollectedValues() <= 1)
            {
                cout << endlXX(2) << "Not Enough Knowns To Create Animation" << endl;
                contPrgm(do_repeat, table);
                continue;
            }
            if (!table.trySolveForUnknowns())
            {
                cout << endlXX(2) << "Not Enough Knowns For Animation" << endl;
                contPrgm(do_repeat, table);
                continue;
            }
            //table.print();
            if (!table.canBeDone())
            {
                cout << endlXX(2) << "Something is Wrong With Your Data, Equations Not Possible." << endl;
                contPrgm(do_repeat, table);
                continue;
            }
        }
        if (!use_last_table)
        {
            cout << endlXX(2) << "Table:" << endl;
            table.print();
            cout << endlXX(2);
        }
        else
            cout << endl;
        Cart cart = Cart(table,
            anim_show_end_logs,
            anim_show_logs,
            show_anim_frames,
            anim_cart_color,
            anim_track_color,
            anim_label_color,
            anim_fps,
            anim_track_len,
            logs_color
        );
        use_last_table = false;
        awaitInput("Press Enter To Start Animation. . .");
        system("cls");
        cout << "Loading..." << endlXX(2);
        cart.setup();
        if (table.getTime() >= warn_anim_len_min && warn_anim_len)
        {
            string user_choice;
            cout << "This animation is over " << warn_anim_len_min << "s (" << getTimeStr(table.getTime()) << ").Continue to animation ? (y/n) : ";
            cin >> user_choice;
            if (!(user_choice == "y" || user_choice == "Y"))
            {
                contPrgm(do_repeat, table);
                continue;
            }
            cout << "Loading..." << endlXX(2);
        }
        Sleep(500);
        cout << "Starting In 3 Seconds";
        Sleep(1000);
        cout << "\rStarting In 2 Seconds";
        Sleep(1000);
        cout << "\rStarting In 1 Seconds";
        Sleep(1000);
        cout << "\rStarting In 0 Seconds" << endl;
        system("cls");

        cart.animate();

        cout << endlXX(2) << "Animation Finished" << endlXX(2);
        cout << "Table:" << endl;
        table.print();

        contPrgm(do_repeat, table);
        cout << "Use Last Table? (y/n): ";
        cin >> temp;
        if (temp == "y" || temp == "Y")
            use_last_table = true;
    }
    awaitInput("Press Enter To Exit");
    
    return 0;
}

void awaitInput(string prompt)
{
    double time_taken = 0.0;
    cout << prompt;
    while (time_taken < 0.1)
    {
        chrono::time_point<chrono::system_clock> start = chrono::system_clock::now();
        cin.get();
        chrono::time_point<chrono::system_clock> end = chrono::system_clock::now();
        chrono::duration<double> elapsed_time = end - start;
        time_taken = elapsed_time.count();
    }
}

void contPrgm(bool &cont, Table &table)
{   
    cont = true;
    string temp;
    cout << endl << "Enter New Values? (y/n): ";
    cin >> temp;
    if (temp == "n" || temp == "N")
        cont = false;
    system("cls");
    if (cont && table.getCollectedValues() > 0)
    {
        cout << "Old Table:" << endl;
        table.print();
        cout << endl;
    }
}

string endlXX(int n)
{
    string temp = "";
    for (int x = 0; x < n; x++)
    {
        temp += "\n";
    }
    return temp;
}

void printColorChart()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "Color Codes:\n";
    SetConsoleTextAttribute(handle, 1);
    cout << "1 : Blue\n";
    SetConsoleTextAttribute(handle, 2);
    cout << "2 : Green\n";
    SetConsoleTextAttribute(handle, 3);
    cout << "3 : Cyan\n";
    SetConsoleTextAttribute(handle, 4);
    cout << "4 : Red\n";
    SetConsoleTextAttribute(handle, 5);
    cout << "5 : Purple\n";
    SetConsoleTextAttribute(handle, 6);
    cout << "6 : Yellow (Dark)\n";
    SetConsoleTextAttribute(handle, 7);
    cout << "7 : White\n";
    SetConsoleTextAttribute(handle, 8);
    cout << "8 : Gray\n";
    SetConsoleTextAttribute(handle, 9);
    cout << "9 : Blue (bright)\n";
    SetConsoleTextAttribute(handle, 10);
    cout << "10 : Green (bright)\n";
    SetConsoleTextAttribute(handle, 11);
    cout << "11 : Cyan (bright)\n";
    SetConsoleTextAttribute(handle, 12);
    cout << "12 : Red (bright)\n";
    SetConsoleTextAttribute(handle, 13);
    cout << "13 : Pink\n";
    SetConsoleTextAttribute(handle, 14);
    cout << "14 : Yellow\n";
    SetConsoleTextAttribute(handle, 15);
    cout << "15 : White (bright)\n";

    SetConsoleTextAttribute(handle, 7);
}

string getTimeStr(double time)
{
    int count_ = 0;
    string ret_str = "";
    int n_time = round(time);
    //cout << n_time << endl;
    while (count_ < 2)
    {
        if (n_time > 60)
        {
            n_time /= 60;
            if (n_time > 60)
            {
                n_time /= 60;
                if (n_time > 24)
                {
                    n_time /= 24;
                    ret_str += to_string(n_time) + "d";
                    //ret_str += to_string(n_time * 24) + "h, ";
                    count_ += 2;
                    continue;
                }
                ret_str += to_string(n_time) + "h";
                //ret_str += to_string(n_time * 60) + "m ";
                count_ += 2;
                continue;
            }
            ret_str += to_string(n_time) + "m";
            //ret_str += to_string(n_time * 60) + "s ";
            count_ += 2;
            continue;
        }
        ret_str += to_string(n_time) + "s";
        count_ += 2;
    }
    //cout << ret_str;
    return ret_str;
}