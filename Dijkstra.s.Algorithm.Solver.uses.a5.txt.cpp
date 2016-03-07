#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <vector>

//Dijkstra's Algorithm Solver Console Application
//Written by Benjamin Malinowski
//
//This application is an implementation of Dijkstra's shortest path cost algorithm.
//The algorithm is written as D[v] = min(D[v], D[w] + cost[w,v]).
//v is the cost of going directly to the destination node from the source node (if not connected, result is inf).
//w is the lowest cost from the source to a connecting node, and cost[w,v] is the cost from that connecting node to the original destination.
//The initial algorithm is then repeated with each successive result, until the lowest cost from the source to the destination is found.
//NOTE: There is a known bug with this application: 2 of the results (specifically, for city E) give an incorrect lowest cost path.  
//		    I am looking into this anomaly to try and find the issue.
//

using namespace std;

//Dijkstra's Algorithm********************************************************************************************///
//Path cost sorting algorithm*************************************************************************************///

void Dijkstra(string citySTART, int numCities, string beginningCities[], string endingCities[], int prices[], int length, string cities[])
{
	//Declarations
    int counter, D[length], W = 99999, tempCost, i = 0, z = 0, cityRemaining = 0, usedCityCount, minCostL[100], minCostR[100], lowestCostPath, lowestPosition;
    string tempCity, wCity, previousWCity = "", finalPathStart, finalPathEnd[100], betweenPath[100], usedCities[numCities];
    vector<string> remainingCities(numCities - 2);
    vector<int> remainingCosts(length), remainingCosts2(length), pathCost(3);
    bool validCheck = false, alreadyInVector = false;

    for (i = 0; i < 100; i++)
    {
        betweenPath[i] = "";  //Fill path array with empty values
    }

//Valid city check************************************************************************************************///
//Checks to make sure if a user-entered city is a valid starting position*****************************************///

    for (i = 0; i < length; i++)
    {
        tempCity = beginningCities[i];
        if (tempCity.compare(citySTART) == 0)   //If found to be a valid city
        {
            validCheck = true;                  //Check is true
        }
    }

    if (validCheck != true)                     //If check is false
    {
        cout << "Origin city not found. ";
    }
    else
    {

//Algorithm start*************************************************************************************************///
//Finds smallest cost (W) from data*******************************************************************************///

    for (counter = 0; counter < length; counter++)            //For length of data
    {
        tempCity = beginningCities[counter];                  //tempCity is next in beginnings array
        tempCost = prices[counter];                           //tempCost is next in prices array

        if (tempCity.compare(citySTART) == 0 && tempCost < W) //If tempCity is cityStart and tempCost is smaller than W
        {
            W = tempCost;                                     //New W set
            wCity = endingCities[counter];                    //New W city set
        }
    }
    cout << endl;
    cout << "Lowest cost from " << citySTART << " -> " << wCity << " = " << W << endl << endl;

//With the lowest city W set, now begin using Dijkstra's Algorithm to find the paths.*************************************///
//First, place remaining cities into an array****************************************************************************///

    for (i = 0; i < numCities; i++)                                              //For the total number of cities being looked at
    {
        if (cities[i].compare(citySTART) != 0 && cities[i].compare(wCity) != 0)  //If a given city is neither the starting city or the lowest cost city
        {
          for (counter = 0; counter < remainingCities.size(); counter++)         //For length of remaining cities vector
            {
                if (cities[i].compare(remainingCities[counter]) == 0 || cities[i].compare(usedCities[counter]) == 0)  //If city from array is already in vector or has been used
                {
                    alreadyInVector = true;
                }
            }
            if (alreadyInVector == false)
            {
                remainingCities[cityRemaining] = cities[i];  //If not already in vector, then added to vector
                cityRemaining++;
            }
        }
    }

//Now start the algorithm to create the paths*****************************************************************************///
//Start with getting the costs from start to each remaining city**********************************************************///

while(remainingCities.size() > 0)
    {
    for (i = 0; i < remainingCities.size(); i++)
    {
        remainingCosts[i] = 99999;                                                    //Sets large number for cost initially if paths arent connected
        for (counter = 0; counter < length; counter++)
        {
            if(citySTART.compare(beginningCities[counter]) == 0 && remainingCities[i].compare(endingCities[counter]) == 0) //If beginning City is connected to remaining City
            {
                remainingCosts[i] = prices[counter];
            }
        }
    }

//Next, the second cost is needed: *****************************************************************************************///
//The cost from the W city to the current city******************************************************************************///

    for (i = 0; i < remainingCities.size(); i++)
    {
        remainingCosts2[i] = 99999;                             //Sets large number for cost initially if paths are not connected
        for (counter = 0; counter < length; counter++)
        {
            if (wCity.compare(beginningCities[counter]) == 0 && remainingCities[i].compare(endingCities[counter]) == 0) //If wCity connected to remaining city
            {
                remainingCosts2[i] = prices[counter];  //Cost from wCity to city set
            }
        }
    }

//Next, begin making the algorithm equations******************************************************************************///
//D[city] = min(Cost START to city, W + Cost W to City)*******************************************************************///
//finalPathStart, finalPathEnd[100], betweenPath[100]*********************************************************************///

    finalPathStart = citySTART;
    for (i = 0; i < remainingCities.size(); i++)
    {
        minCostL[i] = remainingCosts[i];                                                     //Left cost in min (cost from start to city)
        minCostR[i] = W + remainingCosts2[i];                                                //Right cost in min (cost from Start to wCity + cost from wCity to City)
    }
    for (i = 0; i < remainingCities.size(); i++)
    {
        if (minCostL[i] < minCostR[i] || minCostL[i] == minCostR[i])                         //If the left number is larger than the right or if they're equal
        {
            pathCost[i] = minCostL[i];                                                       //Cheapest path is left value
            finalPathEnd[i] = remainingCities[i];                                            //End of path is the city
        }
        if (minCostL[i] > minCostR[i])                                                       //If the right number is larger than the left
        {
            pathCost[i] = minCostR[i];                     	                                 //Cheapest path is the right value
            finalPathEnd[i] = remainingCities[i];                                            //End of path is city
            if (previousWCity != "")
                betweenPath[i] = previousWCity + " -> " + wCity + " -> " + betweenPath[i];   //wCity added to between path
            else
                betweenPath[i] = wCity + " -> " + betweenPath[i];
        }
    }
    cout << endl;

//Now that all the paths have been calculated along with their costs: *********************************************************///
//Compare each cost to find the minimum cost, which will become the new W and print********************************************///

    if (remainingCities.size() == 1)
    {
        lowestCostPath = pathCost[i-1];
        i = remainingCities.size();
    }
    for (i = 0; i < remainingCities.size(); i++)       //For remaining cities
    {
        tempCost = pathCost[i];
        for (z = 0; z < remainingCities.size(); z++)   //For remaining cities
        {
            if (pathCost[z] < pathCost[i])             //If other path cost is lower than current minimum
            {
                lowestCostPath = pathCost[z];          //Set to lowest
                lowestPosition = z;                    //Position of the lowest path set
            }
        }
    }
    cout << "Lowest cost from " << finalPathStart << " -> " << betweenPath[lowestPosition] << finalPathEnd[lowestPosition] << " = " << lowestCostPath << endl;

//Now that the lowest cost path has been printed: *****************************************************************************///
//Remove the used city from the remaining cities vector, set new wCity and new W value*****************************************///

    if (minCostL[lowestPosition] < minCostR[lowestPosition])                     //If the left lower value was used
        previousWCity = "";                                                      //Get rid of current previous city slot
    else                                                                         //Else if right value was used
        previousWCity = wCity;                                                   //previous city equals current wCity
    wCity = remainingCities[lowestPosition];                                     //Sets new W city
    W = lowestCostPath;                                                          //Sets new W value
    remainingCities.erase(remainingCities.begin() + lowestPosition);             //Erases used city from array

    for (i = 0; i < 100; i++)
    {
        betweenPath[i] = "";
    }
        cout << endl;
    }
  }
}

int main() //MAIN PROGRAM******************************************************************************************************///
{

    cout << "Travel Route/Cost Calculation v1.0" << endl << endl;
    ifstream dataList("a5.txt");                                                   //Sets I/O
    string temp;
    int N = 0, counter = 0, A = 0, B = 0, cityCount = 0;
    while (getline(dataList, temp))                                                //Gets the array size as needed
    {
        if (temp == "Q")
            ios::end;                                                              //Goes to end of file if Q terminator is hit
        else
            N++;                                                                   //Increment N size
    }

    dataList.clear();
    dataList.seekg(0, ios::beg);                                                   //Returns to the beginning of the file

    string *travelRoutes = NULL;                                                   //Sets up dynamic string array
    travelRoutes = new string[N];                                                  //Creates string array to hold data lines

    string start[N], destination[N], delimiter = " ", s, START, cityNames[100000]; //String declaration
    char ANSWER;
    int i = 0, cost[N], stepCount[N], dataCount, routeCount;

    while (counter != N)                  //Sets -1 as the empty value for the arrays
    {
        cost[counter] = -1;
        stepCount[counter] = -1;
        counter++;
    }
    if (dataList.is_open())               //If file open
    {
        while (getline(dataList, temp))   //Gets next line
        {
            if (temp == "Q")              //If Q termination
            {
               dataList.close();          //Close the file
            }
            else
            {
            travelRoutes[i] = temp;       //Stores into state name array
            i++;                          //Increments counter
            }
        }
    dataCount = i-1;                      //Total dataCount is i-1
    dataList.close();                     //Close file
    }
    for (i = 0; i <= dataCount; i++)
    {
        s = travelRoutes[i];                            //temp string 's'
        start[i] = s.substr(0,s.find(delimiter));       //First city name set to start
        s.erase(0,s.find(delimiter)+1);                 //Deletes used part of string
        destination[i] = s.substr(0,s.find(delimiter)); //Second city name set to destination
        s.erase(0,s.find(delimiter)+1);                 //Deletes used part of string
        cost[i] = atoi(s.c_str());                      //Cost set
    }

    bool CHECK3 = false;
    routeCount = i;

//Begins asking for inputs*****************************************************************************************************///

    cityNames[0] = start[0];                               //City name set to first starting city
    cityCount = 1;
    cout << endl;
    bool alreadyInArray;
    for (i=1; i < N; i++)                                  //For when i is less than length of data
    {
        for (counter = 0; counter < cityCount; counter++)  //For size of cities array
        {
            alreadyInArray = false;                        //Already in array check
            if (start[i] == cityNames[counter])            //If starting city is already in city name array
            {
                alreadyInArray = true;                     //Check is true
            }
        }
            if (alreadyInArray == false)                   //If check is false
            {
                cityNames[cityCount] = start[i];           //City added to array
                cityCount++;                               //Total number of cities incremented
            }
    }
    i = 0;
    cout << "Costs For Each Travel Route--->" << endl << endl;
    while (i < routeCount)
    {
        cout << "Cost to travel from " << start[i] << " to " << destination[i] << " = " << cost[i] << endl; //Prints initial cost values
        i++;
    }
    cout << endl;
    cout << "Please enter a starting city from the list above: ";           //Asks user to select a starting city
    cin >> START;
    Dijkstra(START, cityCount, start, destination, cost, N, cityNames);     //Execute algorithm.
    cout << "Calculate another route?: ";
    cin >> ANSWER;
    cout << endl;
    while (ANSWER == 'Y' || ANSWER == 'y')                                  //Allows for other starting cities to be chosen
    {
        cout << endl;
        cout << "Please enter a starting city from the list above: ";
        cin >> START;
        Dijkstra(START, cityCount, start, destination, cost, N, cityNames);
        cout << "Calculate another route?: ";
        cin >> ANSWER;
        cout << endl;
    }
    cout << "Program Complete.";
    return 0;
}













