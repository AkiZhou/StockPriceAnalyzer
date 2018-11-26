/**
 * @file lab8demo.cpp
 * @author Shengcong Zhou * @Date 2018.Jul.20
 * @version 1.0
 * @section This is the driver program for the class Book
 */
// I declare that this assignment is my own work and that I have correctly
// acknowledged the work of others. I acknowledged that I have read and
// followed the Academic Honesty and
// Integrity related policies as outlined in the syllabus. //
// _____ Shengcong Zhou ____ _____2018.Jul.20______________ //
// ____ 301336141 ______ //

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

bool sortBySecAscending(const pair<string, double> &a, const pair<string, double> &b);
bool sortBySecDescending(const pair<string, double> &a, const pair<string, double> &b);

int main()
{
    // Declare the vector and the key and value variables
    vector< pair<string, double> > dailyHigh;
    string key;
    double high = 0.0;

    // Open the data file
    ifstream dataList;
    dataList.open("StockPrices.csv");
    if(dataList.fail())
    {
        cerr << "ERROR: failed opening the csv file\nTerminating\n";
        exit(0);
    }
int counter =0;
    // Obtain data from file
    while(! dataList.eof())
        //while(! dataList.eof())
    {
        dataList.ignore(1000,'\n');
        getline(dataList, key, ',');
        dataList.ignore(1000, ',');
        dataList >> high;//getline(dataList, high, ',');
        //dataList.ignore(1000, '\n');
counter++;
        // Insert into the vector
        dailyHigh.push_back(make_pair(key, high));
    }
    dataList.close();

    auto itr = dailyHigh.begin();

    for(auto itr = dailyHigh.begin(); itr != dailyHigh.end(); ++itr)
    {
        cout << itr->first << " , " << itr->second << endl;
    }

    // averagePricePerYear
    cout << "Average Price Per Year\n";
    int year = 0;
    int nextYear = 0;
    int dayCount = 0;
    double totalPrice = 0.0;

    for(auto itr = dailyHigh.begin(); itr != dailyHigh.end(); itr++)
    {
        if(itr == dailyHigh.begin())
        {
            stringstream convert(itr->first);
            convert.ignore(10,'/');
            convert.ignore(10,'/');
            convert >> year;
            dayCount++;
            totalPrice = itr->second;
        }
        else
        {
            stringstream convert(itr->first);
            convert.ignore(10,'/');
            convert.ignore(10,'/');
            convert >> nextYear;

            if(year == nextYear)
            {
                dayCount++;
                totalPrice = totalPrice + itr->second;
            }
            else if(year != nextYear)
            {
                cout << "The average price of " << year << " = "
                     << totalPrice/dayCount << endl;

                year = nextYear;
                dayCount = 1;
                totalPrice = itr->second;
            }
            else
            {
                cerr << "ERROR: something wrong happened\nTerminating\n";
                exit(0);
            }
        }
    }
    cout << "The average price of " << year << " = "
         << totalPrice/dayCount << endl << endl;

    // averagePricePerMonth
    cout << "Average Price Per Month\n";
    year = 0;
    nextYear = 0;
    int month = 0;
    int nextMonth = 0;
    dayCount = 0;
    totalPrice = 0.0;

    for(auto itr = dailyHigh.begin(); itr != dailyHigh.end(); itr++)
    {
        if(itr == dailyHigh.begin())
        {
            stringstream convert(itr->first);
            convert >> month;
            convert.ignore(10,'/');
            convert.ignore(10,'/');
            convert >> year;
            dayCount++;
            totalPrice = itr->second;
        }
        else
        {
            stringstream convert(itr->first);
            convert >> nextMonth;
            convert.ignore(10,'/');
            convert.ignore(10,'/');
            convert >> nextYear;

            if(month == nextMonth && year == nextYear)
            {
                dayCount++;
                totalPrice = totalPrice + itr->second;
            }
            else if(month != nextMonth || year != nextYear)
            {
                if(month != nextMonth && year != nextYear)
                {
                    cout << "The average price of month " << month << " of "
                         << year << " = " << totalPrice/dayCount << endl;

                    year = nextYear;
                    month = nextMonth;
                    dayCount = 1;
                    totalPrice = itr->second;
                }
                else if(month != nextMonth)
                {
                    cout << "The average price of month " << month << " of "
                         << year << " = " << totalPrice/dayCount << endl;

                    month = nextMonth;
                    dayCount = 1;
                    totalPrice = itr->second;
                }
                else if(year != nextYear)
                {
                    cout << "The average price of month " << month << " of "
                         << year << " = " << totalPrice/dayCount << endl;

                    year = nextYear;
                    dayCount = 1;
                    totalPrice = itr->second;
                }

            }
            else
            {
                cerr << "ERROR: something wrong happened\nTerminating\n";
                exit(0);
            }
        }
    }
    cout << "The average price of month " << month << " of "
         << year << " = " << totalPrice/dayCount << endl << endl;

    // HighestAndLowestPricesPerYear
    cout << "Highest and Lowest Prices Per Year\n";
    year = 0;
    nextYear = 0;
    double maxHigh = 0.0;
    double minHigh = 0.0;

    for(auto itr = dailyHigh.begin(); itr != dailyHigh.end(); itr++)
    {
        if(itr == dailyHigh.begin())
        {
            stringstream convert(itr->first);
            convert.ignore(10,'/');
            convert.ignore(10,'/');
            convert >> year;
            maxHigh = itr->second;
            minHigh =itr->second;
        }
        else
        {
            stringstream convert(itr->first);
            convert.ignore(10,'/');
            convert.ignore(10,'/');
            convert >> nextYear;

            if(year == nextYear)
            {
                if(itr->second > maxHigh)
                {
                    maxHigh = itr->second;
                }
                else if(itr->second < minHigh)
                {
                    minHigh = itr->second;
                }
            }
            else if(year != nextYear)
            {
                cout << "The highest price of " << year << " = "
                     << maxHigh << " : The lowest price of " << year << " = "
                     << minHigh << endl;

                year = nextYear;
                maxHigh = itr->second;
                minHigh =itr->second;
            }
            else
            {
                cerr << "ERROR: something wrong happened\nTerminating\n";
                exit(0);
            }
        }
    }
    cout << "The highest price of " << year << " = "
         << maxHigh << " : The lowest price of " << year << " = "
         << minHigh << endl << endl;

    // ListLowest2Highest
    // Create new file
    ofstream low2High;
    low2High.open("low2High.txt");
    if(low2High.fail())
    {
        cerr << "ERROR: failed creating a file\nTerminating\n";
        exit(0);
    }

    sort(dailyHigh.begin(), dailyHigh.end(), sortBySecAscending);

    for(auto itr = dailyHigh.begin(); itr != dailyHigh.end(); ++itr)
    {
        low2High << itr->first << " , " << itr->second << endl;
    }

    low2High.close();

    // ListHighest2Lowest
    // Create new file
    ofstream high2Low;
    high2Low.open("high2Low.txt");
    if(high2Low.fail())
    {
        cerr << "ERROR: failed creating a file\nTerminating\n";
        exit(0);
    }

    sort(dailyHigh.begin(), dailyHigh.end(), sortBySecDescending);

    for(auto itr = dailyHigh.begin(); itr != dailyHigh.end(); ++itr)
    {
        high2Low << itr->first << " , " << itr->second << endl;
    }

    high2Low.close();

    return 0;
}

/**
 * @brief This function is used to sort in ascending order according to
 *      the second element of a vector containing a pair
 */
bool sortBySecAscending(const pair<string, double> &a, const pair<string, double> &b)
{
    return (a.second < b.second);
}

/**
 * @brief This function is used to sort according in descending order to
 *      the second element of a vector containing a pair
 */
bool sortBySecDescending(const pair<string, double> &a, const pair<string, double> &b)
{
    return (a.second > b.second);
}