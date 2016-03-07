#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>

//Hashing Algorithm Console Application
//Written by Benjamin Malinowski
//
//This console application implements a closed hash table, with both linear and quadratic probing variants.
//The hash function is:  h(data) = (a*data[0] + b*data[1] + c*data[2] + d*data[3])mod hashValue.
//hashValues of 65 and 150 have been selected.  Both will be used in linear and quadratic runs.
//The values of a,b,c,d are given in the first line of the text file.
//The data to be added to the table from the text file are the names of the 50 United States.
//In addition to a printout of the table slot the state name occupies, the number of collisions it went through is printed next to it.
//Also, the average number of collisions for each variant is printed at the end of the run.
//

using namespace std;

int hashMaker (int a, int b, int c, int d, int modulusNumber, string stateName)           //Hash Function
{
    int hashAnswer = (a*stateName[0])+(b*stateName[1])+(c*stateName[2])+(d*stateName[3]); //Hash equation
    int hashFinal = hashAnswer%modulusNumber;
    return hashFinal;                                                                     //Return hash value
}

int main() //MAIN PROGRAM************************************************************************************///
{
    cout << "Hashing Program v1.0" << endl << endl;
    int i = 0, y = 1, dataCount = 0, SIZE = 65, a, b, c, d, tempSlot;  //Integer Variable declarations
    string stateNames[50], temp, abcdStr;                              //String variable declarations
    bool check = false;                                                //Bool check declaration
    ifstream dataList("a4.txt");                                       //Sets text I/O

    if (dataList.is_open())             //If file open
    {
        while (getline(dataList,temp))  //Gets next line
        {
            stateNames[i] = temp;       //Stores into state name array
            i++;                        //Increments counter
        }
    dataCount = i;                      //Total dataCount is i-1
    dataList.close();                   //Close file
    }
    abcdStr = stateNames[0];            //First line of file is a b c d hash values
    a = atoi(abcdStr.c_str());          //Convert first number to int value a
    abcdStr.erase(0,2);                 //Removes the first two characters from first line of file (number and blank space)
    b = atoi(abcdStr.c_str());          //Convert second number to int value b
    abcdStr.erase(0,2);                 //Remove the next two characters from first line
    c = atoi(abcdStr.c_str());          //Convert third number to int value c
    abcdStr.erase(0,2);                 //Remove the next two characters from first line
    d = atoi(abcdStr.c_str());          //Convert fourth number to int value d
    cout << "Hashing for->" << endl;    //Print the four hash values
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;

//Hash Table 1 Code:  Linear Probing with Hash Value of 65 ******************************************************************************///

    int  hashNum1[SIZE], hashTable1[SIZE], hashCount1[SIZE], tempVal = 0;  //Declare arrays
    string  hashString1[SIZE];                                             //Declare string array
    for (i = 0; i < SIZE; i++)                                             //For i less than 65
    {
        hashNum1[i] = -1;                                                  //Sets empty value of -1 for hash nums
        hashTable1[i] = -1;                                                //Sets empty value of -1 for hash table slots
    }
    i = 1;
    while (i < dataCount)                                                  //While less than datacount
        {
          hashNum1[i] = hashMaker(a, b, c, d, SIZE, stateNames[i]);        //Creates hash values for each state
          i++;                                                             //Increments counter
        }
    cout << endl;
    cout << "<--- Hash Table 1: Linear Probing w/ 65 Hashing Value --->" << endl << endl;
    i = 1;
    while(i < 50)                                           //While hashNum are valid numbers...
    {
        tempVal = hashNum1[i];                              //Stores current hash val into temp
        if (hashTable1[tempVal] == -1)                      //If the next table slot is open
        {
            hashString1[tempVal] = stateNames[i];           //Place state name into string slot
            hashTable1[tempVal] = 1;                        //Count for movements equals 1
            i++;                                            //Increment counter
        }
        else
        {
            y = 1;
            while (check != true)                           //While false...
                {
                tempSlot = ((y+tempVal)%SIZE);              //Slot is (tempval + y) % 65
                if (hashTable1[tempSlot] == -1)             //If slot is empty
                  {
                    hashString1[tempSlot] = stateNames[i];  //Place state name into string slot(y+tempVal)%SIZE
                    hashTable1[tempSlot] = y+1;             //Count for movements equals y
                    check = true;                           //Break loop
                    i++;
                  }
                else
                    y++;                                    //Else increment movement counter
                }
        }
        check = false;
    }
       i = 0;
       while (i < SIZE)                                                             //While less than 65
       {
            if (i%4 == 0)                                                           //If i is divisible completely by 4 and doesnt equal 0
            {
                cout << endl;
                if (i < 10)                                                         //If i is smaller than 10
                {
                    cout << "0";                                                    //Place '0' in front of number
                    cout << i << ": ";
                }
                else
                    cout << i << ": ";                                              //Else print number
            }
            if (hashTable1[i] != -1)                                                //If not an empty table slot
            {
                cout << setw(13) << hashString1[i] << "(" << hashTable1[i] << ")";  //Print state name and movement count
            }
            else
            {
                cout << setw(16) << "               ";                              //Else print invalid
            }
            i++;                                                                    //Increment counter
        }
     cout << endl;

//Hash Table 2 Code: Linear Probing with Hash Value of 150 ******************************************************************************///

    SIZE = 150;
    tempVal = 0;
    tempSlot = 0;
    int  hashNum2[SIZE], hashTable2[SIZE], hashCount2[SIZE];          //Declare arrays
    string  hashString2[SIZE];                                        //Declare string array
    for (i = 0; i < SIZE; i++)                                        //For i less than 65
    {
        hashNum2[i] = -1;                                             //Sets empty value for hash nums
        hashTable2[i] = -1;                                           //Sets empty value for hash table slots
    }
    i = 1;
    while (i < dataCount)                                             //While less than datacount
        {
          hashNum2[i] = hashMaker(a, b, c, d, SIZE, stateNames[i]);   //Creates hash values for each state
          i++;                                                        //Increments counter
        }
    cout << endl;
    cout << "<--- Hash Table 2: Linear Probing w/ 150 Hashing Value --->" << endl << endl;
    i = 1;
    while(i < 50)                                           //While hashNum are valid numbers...
    {
        tempVal = hashNum2[i];                              //Stores current hash val into temp
        if (hashTable2[tempVal] == -1)                      //If the next table slot is open
        {
            hashString2[tempVal] = stateNames[i];           //Place state name into string slot
            hashTable2[tempVal] = 1;                        //Count for movements equals 1
            i++;                                            //Increment counter
        }
        else
        {
            y = 1;
            while (check != true)                           //While false
                {
                tempSlot = ((y+tempVal)%SIZE);              //Slot is (tempval + y) % 65
                if (hashTable2[tempSlot] == -1)             //If slot is empty
                  {
                    hashString2[tempSlot] = stateNames[i];  //Place state name into string slot(y+tempVal)%SIZE
                    hashTable2[tempSlot] = y+1;             //Count for movements equals y
                    check = true;                           //Break loop
                    i++;
                  }
                else
                    y++;                                    //else increment movement counter
                }
        }
        check = false;
    }
       i = 0;
       while (i < SIZE)                                                             //While less than 65
        {
            if (i%4 == 0)                                                           //If i is divisible completely by 4 and doesnt equal 0
            {
                cout << endl;
                if (i < 10)                                                         //If i is smaller than 10
                {
                    cout << "00";                                                   //Place '00' in front of number
                    cout << i << ": ";
                }
                else if (i < 100)                                                   //If smaller than 100
                {
                    cout << "0";                                                    //Place '0' in front of number
                    cout << i << ": ";
                }
                else
                    cout << i << ": ";                                              //Else print number
            }
            if (hashTable2[i] != -1)                                                //If not an empty table slot
            {
                cout << setw(13) << hashString2[i] << "(" << hashTable2[i] << ")";  //Print state name and movement count
            }
            else
            {
                cout << setw(16) << "               ";                               //Else print invalid
            }
            i++;                                                                     //Increment counter
        }
    cout << endl;

//Hash Table 3 Maker Code: Quadratic Probing with Hash Value of 65 **********************************************************************///

    SIZE = 65;
    tempVal = 0;
    tempSlot = 0;
    int  hashNum3[SIZE], hashTable3[SIZE], hashCount3[SIZE];          //Declare arrays
    string  hashString3[SIZE];                                        //Declare string array
    for (i = 0; i < SIZE; i++)                                        //For i less than 65
    {
        hashNum3[i] = -1;                                             //Sets empty value for hash nums
        hashTable3[i] = -1;                                           //Sets empty value for hash table slots
    }
    i = 1;
    while (i < dataCount)                                             //While less than datacount
        {
          hashNum3[i] = hashMaker(a, b, c, d, SIZE, stateNames[i]);   //Creates hash values for each state
          i++;                                                        //Increments counter
        }
    cout << endl;
    cout << "<--- Hash Table 3: Quadratic Probing w/ 65 Hashing Value --->" << endl << endl;
    i = 1;
    while(i < 50)                                           //While hashNum are valid numbers
    {
        tempVal = hashNum3[i];                              //Stores current hash val into temp
        if (hashTable3[tempVal] == -1)                      //If the next table slot is open
        {
            hashString3[tempVal] = stateNames[i];           //Place state name into string slot
            hashTable3[tempVal] = 1;                        //Count for movements equals 1
            i++;                                            //Increment counter
        }
        else
        {
            y = 1;
            int x = 1;
            while (check != true)                           //While false
                {
                y = pow(x,2);
                tempSlot = ((y+tempVal)%SIZE);              //Slot is (tempval + y) % 65
                if (hashTable3[tempSlot] == -1)             //If slot is empty
                  {
                    hashString3[tempSlot] = stateNames[i];  //Place state name into string slot(y+tempVal)%SIZE
                    hashTable3[tempSlot] = x+1;             //Count for movements equals y
                    check = true;                           //Break loop
                    i++;
                  }
                else
                    x++;                                    //else increment movement counter
                }
        }
        check = false;
    }
       i = 0;
       while (i < SIZE)                                                             //While less than 65
        {
            if (i%4 == 0)                                                           //If i is divisible completely by 4 and doesnt equal 0
            {
                cout << endl;
                if (i < 10)                                                         //If i is smaller than 10
                {
                    cout << "0";                                                    //Place '0' in front of number
                    cout << i << ": ";
                }
                else
                    cout << i << ": ";                                              //Else print number
            }
            if (hashTable3[i] != -1)                                                //If not an empty table slot
            {
                cout << setw(13) << hashString3[i] << "(" << hashTable3[i] << ")";  //Print state name and movement count
            }
            else
            {
                cout << setw(16) << "               ";                              //Else print invalid
            }
            i++;                                                                    //Increment counter
        }
    cout << endl;

//Hash Table 4 Code: Quadratic with Hash Value of 150 ***********************************************************************************///

    SIZE = 150;
    tempVal = 0;
    tempSlot = 0;
    int  hashNum4[SIZE], hashTable4[SIZE], hashCount4[SIZE];          //Declare arrays
    string  hashString4[SIZE];                                        //Declare string array
    for (i = 0; i < SIZE; i++)                                        //For i less than 150
    {
        hashNum4[i] = -1;                                             //Sets empty value for hash nums
        hashTable4[i] = -1;                                           //Sets empty value for hash table slots
    }
    i = 1;
    while (i < dataCount)                                             //While less than datacount
        {
          hashNum4[i] = hashMaker(a, b, c, d, SIZE, stateNames[i]);   //Creates hash values for each state
          i++;                                                        //Increments counter
        }
    cout << endl;
    cout << "<--- Hash Table 4: Quadratic Probing w/ 150 Hashing Value --->" << endl << endl;
    i = 1;
    while(i < 50)                                           //While hashNum are valid numbers
    {
        tempVal = hashNum4[i];                              //Stores current hash val into temp
        if (hashTable4[tempVal] == -1)                      //If the next table slot is open
        {
            hashString4[tempVal] = stateNames[i];           //Place state name into string slot
            hashTable4[tempVal] = 1;                        //Count for movements equals 1
            i++;                                            //Increment counter
        }
        else
        {
            y = 1;
            int z = 1;
            while (check != true)                           //While false
                {
                y = pow(z,2);
                tempSlot = (((y)+tempVal)%SIZE);            //Slot is (tempval + y) % 150
                if (hashTable4[tempSlot] == -1)             //If slot is empty
                  {
                    hashString4[tempSlot] = stateNames[i];  //Place state name into string slot(y+tempVal)%SIZE
                    hashTable4[tempSlot] = z+1;             //Count for movements equals y
                    check = true;                           //Break loop
                    i++;
                  }
                else
                    z++;                                    //else increment movement counter
                }
        }
        check = false;
    }
       i = 0;
       while (i < SIZE)                                                             //While less than 150
        {
            if (i%4 == 0)                                                           //If i is divisible completely by 4 and doesnt equal 0
            {
                cout << endl;
                if (i < 10)                                                         //If i is smaller than 10
                {
                    cout << "00";                                                   //Place '00' in front of number
                    cout << i << ": ";
                }
                else if (i < 100)                                                   //If smaller than 100
                {
                    cout << "0";                                                    //Place '0' in front of number
                    cout << i << ": ";
                }
                else
                    cout << i << ": ";                                              //Else print number
            }
            if (hashTable4[i] != -1)                                                //If not an empty table slot
            {
                cout << setw(13) << hashString4[i] << "(" << hashTable4[i] << ")";  //Print state name and movement count
            }
            else
            {
                cout << setw(16) << "               ";                              //Else print invalid
            }
            i++;                                                                    //Increment counter
        }
    cout << endl;

//Averages Section **********************************************************************************************************************///

    float avgPart1 = 0, avgPart2 = 0, avgPart3 = 0, avgPart4 = 0, tempAvg = 0;
    for (i = 0; i < 65; i++)
    {
        if (hashTable1[i] != -1)
        {
            tempAvg = tempAvg + hashTable1[i];
        }

    }
    avgPart1 = tempAvg/50;

    //Calculate average of Linear Hashing with Hash Value 150
    tempAvg = 0;
    for (i = 0; i < 150; i++)
    {
        if (hashTable2[i] != -1)
        {
            tempAvg = tempAvg + hashTable2[i];
        }
    }
    avgPart2 = tempAvg/50;

    //Calculate average of Quadratic Hashing with Hash Value 65
    tempAvg = 0;
    for (i = 0; i < 65; i++)
    {
        if (hashTable3[i] != -1)
            tempAvg = tempAvg + hashTable3[i];
    }
    avgPart3 = tempAvg/50;

    //Calculate average of Quadratic Hashing with Hash Value 150
    tempAvg = 0;
    for (i = 0; i < 150; i++)
    {
        if (hashTable4[i] != -1)
            tempAvg = tempAvg + hashTable4[i];
    }
    avgPart4 = tempAvg/50;

    cout << endl << "          Averages of Each Type of Hashing: " << endl;    //Print out formatted table at end of run
    cout << "     |****************************************|" << endl;
    cout << "     |    Case    ||   Linear   ||  Quadratic |" << endl;
    cout << "     |****************************************|" << endl;
    cout << "     | 65 Hashing ||    " << avgPart1 << "    ||     " << avgPart3 << "   |" << endl;
    cout << "     |----------------------------------------|" << endl;
    cout << "     |150 Hashing ||     " << avgPart2 << "    ||     " << avgPart4 << "   |" << endl;
    cout << "     |----------------------------------------|" << endl;
    return 0;
}












