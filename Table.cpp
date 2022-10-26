/*
 * Orion Mulgrew
 * P8 Kintzel
 * Project: U1 Motion
 * File: Table Implementation
 * Start: 9/19/2022
 */

#include "Table.h"
#include <iostream>
#include <cmath>
#include<string>
using namespace std;

string trimZerosDouble(string str, int len)
{
    int str_len = str.length();
    bool hasPD = false;
    for (int x = 0; x < str.length(); x++)
    {
        if (str[x] == '.')
        {
            hasPD = true;
            break;
        }
    }
    if ((str[str_len - 1] == '0' && hasPD) || str[str_len - 1] == '.')
    {
        str.pop_back();
        return trimZerosDouble(str);
    }
    if (str.empty())
        str = "0";
    if (len != 0)
    {
        bool pd_in_str = false;
        for (int x = 0; x < str.length(); x++)
        {
            if (str[x] == '.')
                pd_in_str = true;
        }
        if (pd_in_str)
        {
            int index = str.find('.');
            string nstr = "";
            for (int x = 0; x < str.length(); x++)
            {
                if (x == index + len)
                    break;
                nstr += str[x];
            }
        }
    }
    return str;
}

Table::Table()
{
    distanceInitial = INT_MAX;
    distanceFinal = INT_MAX;
    velocityInitial = INT_MAX;
    velocityFinal = INT_MAX;
    acceleration = INT_MAX;
    time = INT_MAX;
    time2 = INT_MAX;
}

void Table::setDI(double di)
{
    distanceInitial = di;
}

void Table::setDF(double df)
{
    distanceFinal = df;
}

void Table::setVI(double vi)
{
    velocityInitial = vi;
}

void Table::setVF(double vf)
{
    velocityFinal = vf;
}

void Table::setAccel(double a)
{
    acceleration = a;
}

void Table::setTime(double t)
{
    time = t;
}

double Table::getDI()
{
    return distanceInitial;
}

double Table::getDF()
{
    return distanceFinal;
}

double Table::getVI()
{
    return velocityInitial;
}

double Table::getVF()
{
    return velocityFinal;
}

double Table::getAccel()
{
    return acceleration;
}

double Table::getTime()
{
    return time;
}

void Table::user_setValues()
{
    string gets[] = { "Di", "Df", "Vi", "Vf", "a", "t" };
    string label[] = { "m", "m", "m/s", "m/s", "m/s/s", "s" };
    string user_input;

    for (int x = 0; x < 6; x++)
    {
        cout << "Enter " << gets[x] << " in " << label[x] << ": ";


        cin >> user_input;
        switch (x) {
        case 0:
            distanceInitial = (user_input != "?" ? stod(user_input) : INT_MAX);
            break;

        case 1:
            distanceFinal = (user_input != "?" ? stod(user_input) : INT_MAX);
            break;

        case 2:
            velocityInitial = (user_input != "?" ? stod(user_input) : INT_MAX);
            break;

        case 3:
            velocityFinal = (user_input != "?" ? stod(user_input) : INT_MAX);
            break;

        case 4:
            acceleration = (user_input != "?" ? stod(user_input) : INT_MAX);
            break;

        case 5:
            time = (user_input != "?" ? stod(user_input) : INT_MAX);
            break;

        default:
            cout << "something funky happened..." << endl;
            break;
        }
    }
}

int Table::getCollectedValues()
{
    int total = 0;

    if (distanceInitial != INT_MAX)
    {
        total++;
    }
    if (distanceFinal != INT_MAX)
    {
        total++;
    }
    if (velocityInitial != INT_MAX)
    {
        total++;
    }
    if (velocityFinal != INT_MAX)
    {
        total++;
    }
    if (acceleration != INT_MAX)
    {
        total++;
    }
    if (time != INT_MAX)
    {
        total++;
    }
    return total;
}

bool Table::trySolveForUnknowns()
{
    for (int x = 0; x < 3; x++)
    {
        // try to solve for Di
        if (distanceInitial == INT_MAX)
        {
            // using equation: Df = Di + Vi(t) + a(t^2) / 2
            if (distanceFinal != INT_MAX && velocityInitial != INT_MAX && time != INT_MAX && acceleration != INT_MAX) {
                distanceInitial = distanceFinal - (velocityInitial * time) - (acceleration * (time * time) / 2);
            }
            // using equation: Vf^2 = Vi^2 + 2a(Df - Di)
            else if (distanceFinal != INT_MAX && velocityInitial != INT_MAX && velocityFinal != INT_MAX && acceleration != INT_MAX) {
                distanceInitial = -1 * ((((velocityFinal * velocityFinal) - (velocityInitial * velocityInitial)) / (2 * acceleration)) - distanceFinal);
            }
            else if (distanceFinal == INT_MAX)
            {
                cout << "Setting Di to 0 Since no Di or Df was provided" << endl;
                distanceInitial = 0;
            }
        }
        // try to solve for Df
        if (distanceFinal == INT_MAX)
        {
            // using equation: Df = Di + Vi(t) + a(t^2) / 2
            if (distanceInitial != INT_MAX && velocityInitial != INT_MAX && time != INT_MAX && acceleration != INT_MAX) {
                distanceFinal = distanceInitial + (velocityInitial * time) + (acceleration * (time * time) / 2);
            }
            // using equation: Vf^2 = Vi^2 + 2a(Df - Di)
            else if (distanceInitial != INT_MAX && velocityInitial != INT_MAX && velocityFinal != INT_MAX && acceleration != INT_MAX)
            {
                distanceFinal = (((velocityFinal * velocityFinal) - (velocityInitial * velocityInitial)) / (2 * acceleration)) + distanceInitial;
            }
        }
        // try to solve for Vi
        if (velocityInitial == INT_MAX)
        {
            //using equation: Vf = Vi + a(t)
            if (velocityFinal != INT_MAX && acceleration != INT_MAX && time != INT_MAX)
            {
                velocityInitial = velocityFinal - (acceleration * time);
            }
            // using equation: Df = Di + Vi(t) + a(t^2) / 2
            if (distanceFinal != INT_MAX && distanceInitial != INT_MAX && time != INT_MAX && acceleration != INT_MAX)
            {
                velocityInitial = (((distanceFinal - distanceInitial) - (acceleration * (time * time) / 2)) / time);
            }
            // using equation: Vf^2 = Vi^2 + 2a + (Df - Di)
            if (velocityFinal != INT_MAX && acceleration != INT_MAX && distanceFinal != INT_MAX && distanceInitial != INT_MAX)
            {
                velocityInitial = sqrt((velocityFinal * velocityFinal) - (2 * acceleration) - (distanceFinal - distanceInitial));
            }
        }
        // try to solve for Vf
        if (velocityFinal == INT_MAX)
        {
            //cout << "calcing Vf" << endl;
            //using equation: Vf = Vi + a(t)
            if (velocityInitial != INT_MAX && acceleration != INT_MAX && time != INT_MAX)
            {
                velocityFinal = velocityInitial + (acceleration * time);
            }
            // using equation: Df = Di + Vi(t) + a(t^2) / 2
            if (distanceFinal != INT_MAX && distanceInitial != INT_MAX && time != INT_MAX && acceleration != INT_MAX)
            {
                velocityFinal = sqrt(((distanceFinal - distanceInitial) - (acceleration * (time * time) / 2)) / time);
            }
            // using equation: Vf^2 = Vi^2 + 2a * (Df - Di)
            if (velocityInitial != INT_MAX && acceleration != INT_MAX && distanceFinal != INT_MAX && distanceInitial != INT_MAX)
            {
                velocityFinal = sqrt((velocityInitial * velocityInitial) + ((2 * acceleration) * (distanceFinal - distanceInitial)));
            }
            //cout << (velocityFinal != INT_MAX ? "solved: " + to_string(velocityFinal) : "unsolved") << endl;
        }
        // try to solve for accel
        if (acceleration == INT_MAX)
        {
            // using Vf = Vi + a(t)
            if (velocityFinal != INT_MAX && velocityInitial != INT_MAX && time != INT_MAX)
            {
                acceleration = ((velocityFinal - velocityInitial) / time);
            }
            // using equation: Vf^2 = Vi^2 + 2a(Df - Di)
            if (velocityFinal != INT_MAX && velocityInitial != INT_MAX && distanceFinal != INT_MAX && distanceInitial != INT_MAX)
            {
                acceleration = ((((velocityFinal * velocityFinal) - (velocityInitial * velocityInitial)) / (distanceFinal - distanceInitial)) / 2);
            }
        }
        // try to solve for time
        if (time == INT_MAX)
        {
            // using Vf = Vi + a(t)
            if (velocityFinal != INT_MAX && velocityInitial != INT_MAX && acceleration != INT_MAX)
            {
                time = ((velocityFinal - velocityInitial) / acceleration);
                time2 = (((- 1.0 * velocityFinal) - velocityInitial) / acceleration);
            }
            /* using alg for Vf = Vi + a(t)
            if (velocityInitial != INT_MAX && acceleration != INT_MAX)
            {

            }
            // using alg for Vf = Vi + a(t)
            if (velocityFinal != INT_MAX && acceleration != INT_MAX)
            {

            }
            // using Df = Di + Vi(t) + a(t^2) / 2
            if (distanceFinal != INT_MAX && distanceInitial != INT_MAX && velocityInitial != INT_MAX && acceleration != INT_MAX)
            {
                time = 0;
            }
            */
        }
    }
    if (time < 0 && time != INT_MAX && velocityFinal != INT_MAX)
    {
        velocityFinal *= -1;
        time = abs(time);
    }
    //cout << velocityFinal << endl;
    return (this->getCollectedValues() >= 4);
}

bool Table::canBeDone()
{
    int total_done = 0;

    if (velocityFinal != INT_MAX && velocityInitial != INT_MAX && acceleration != INT_MAX && time != INT_MAX)
    {
        total_done++;
        if (abs((velocityInitial + (acceleration * time)) - velocityFinal) >= 1)
        {
            if (abs((velocityInitial + (acceleration * time2)) - velocityFinal) >= 1)
            {
                //cout << "Calc Vf: " << (velocityInitial + (acceleration * time)) << endl;
                //cout << "Orig Vf: " << velocityFinal << endl;
                //cout << "Equation 'Vf = Vi + a(t)' Failed" << endl;
                return false;
            }
            else
            {
                time = time2;
            }
        }
    }
    if (distanceFinal != INT_MAX && distanceInitial != INT_MAX && velocityInitial != INT_MAX && time != INT_MAX && acceleration != INT_MAX)
    {
        total_done++;
        if (abs((distanceInitial + (velocityInitial * time) + (acceleration * (time * time)) / 2) - distanceFinal) >= 1)
        {
            cout << "Equation 'Df = Di + Vi(t) + a(t^2) / 2' Failed" << endl;
            return false;
        }
    }
    if (velocityFinal != INT_MAX && velocityInitial != INT_MAX && acceleration != INT_MAX && distanceFinal != INT_MAX && distanceInitial != INT_MAX)
    {
        total_done++;
        if (abs((((velocityInitial * velocityInitial) + ((2 * acceleration) * (distanceFinal - distanceInitial))) - (velocityFinal * velocityFinal))) >= 1)
        {
            cout << "Equation 'Vf^2 = Vi^2 + 2(a) * (Df - Di)' Failed" << endl;
            return false;
        }
    }

    return (total_done > 1);
}

void Table::print()
{
    string names[] = { "Di", "Df", "Vi", "Vf", "a", "t" };
    string values[] = {
                    (distanceInitial    == INT_MAX ? "?" : to_string(distanceInitial)),
                    (distanceFinal      == INT_MAX ? "?" : to_string(distanceFinal)),
                    (velocityInitial    == INT_MAX ? "?" : to_string(velocityInitial)),
                    (velocityFinal      == INT_MAX ? "?" : to_string(velocityFinal)),
                    (acceleration       == INT_MAX ? "?" : to_string(acceleration)),
                    (time               == INT_MAX ? "?" : to_string(time))
    };
    string label[] = { "m", "m", "m/s", "m/s", "m/s/s", "s" };
    cout << "-------------" << endl;
    for (int x = 0; x < 6; x++)
    {
        cout << names[x] << ": " << (trimZerosDouble(values[x]) == "?" ? trimZerosDouble(values[x]) : "" + trimZerosDouble(values[x]) + label[x]) << endl;
    }
    cout << "-------------" << endl;
}

void Table::reset()
{
    distanceInitial = INT_MAX;
    distanceFinal = INT_MAX;
    velocityInitial = INT_MAX;
    velocityFinal = INT_MAX;
    acceleration = INT_MAX;
    time = INT_MAX;
    time2 = INT_MAX;
}