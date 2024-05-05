#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <ctime>
#include "Utils.h"
using namespace std;
namespace seneca
{
    // start provided code
    bool debug = false;
    Utils U;
    int Utils::getTime()
    {
        int mins = -1;
        if (debug)
        {
            int duration[]{3, 5, 9, 20, 30};
            mins = (m_testMins %= 1440);
            m_testMins += duration[m_testIndex++ % 5];
        }
        else
        {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            mins = lt.tm_hour * 60 + lt.tm_min;
        }
        return mins;
    }
    void Utils::setDebugTime(int hour, int min)
    {
        seneca::debug = true;
        m_testMins = hour * 60 + min;
    }

    int Utils::strcmp(const char *s1, const char *s2) const
    {
        int i;
        for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++)
            ;
        return s1[i] - s2[i];
    }

    int Utils::getIntRange(int min, int max, const char *prompt)
    {
        int selection;
        bool success = false;
        while (!success)
        {
            if (prompt)
                cout << prompt;
            cin >> selection;
            if (cin.fail())
            {
                cout << "Bad integer value, try again: ";
                cin.clear();
                cin.ignore(1000, '\n');
                success = false;
            }
            else if (cin.peek() != '\n')
            {
                cout << "Only enter an integer, try again: ";
                cin.ignore(1000, '\n');
                success = false;
            }
            else if (selection < 0 || selection > max)
            {
                cout << "Invalid value enterd, retry[" << min << " <= value <= " << max << "]: ";
                success = false;
            }
            else
            {
                success = true;
            }
        }

        return selection;
    }

    int Utils::getInt(int min, int max)
    {
        bool success = false;
        int in{};
        cin >> in;

        do
        {
            if (cin.fail())
            {
                cout << "Bad integer value, try again: ";
                cin.clear();
                cin.ignore(12000, '\n');
                cin >> in;
            }
            else if (in < min || in > max)
            {
                in = 0;
                cout << "Invalid value enterd, retry[" << min << " <= value <= " << max << "]: ";
                cin >> in;
            }
            else
            {
                success = true;
            }
        } while (success == false);

        return in;
    }

    int Utils::countLines(const char *text)
    {
        int count = 0;
        if (text)
        {
            count = 1;
            for (int i = 0; text[i] != '\0'; i++)
            {
                if (text[i] == '\n')
                {
                    count++;
                }
            }
        }
        return count;
    }
}