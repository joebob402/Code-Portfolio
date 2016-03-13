#include <iostream>  
#include <fstream>  
#include <string>  

//Employee Records System Console Application
//Written by Benjamin Malinowski
//
//This console application is a simple employee records system.
//The records are stored within a text file, and are initially read in and sorted into order by SSN.
//The user is then given the option to add a new employee's information to the file.
//Once all necessary information is given, the system prints the new entry, correctly formatted to match other entries.
//The user may then enter another set of information, or decline to move to the search function.
//The user may then search through all employees (by last name) to find an entry.
//The found results are then printed (multiple employee entries having the same last name will both be printed).
//The user may keep searching the records for more employee information, or decline to move on.
//The system then prints the results from all successful searches, and the program ends.
//

using namespace std;
//Structure Information********************************************************************//
struct PersonInformation   //Defines structure
{
    char firstName[12];
    char lastName[13];
    long SSN;
    int age;
    string address;

}person;
//Sort Function****************************************************************************//
void SortData (int start)
{
    int i=0, y, dataMAX=0, x, z;    //Counters
    string data[125];               //String array to store the lines from the text
    string line, temp;              //Placeholder for each line in the text
    ifstream PersonInfo ("a1.txt"); //Open text file
    if (PersonInfo.is_open())
    {
        while (getline(PersonInfo,line)) //Reads in the data from the text and writes to an array
        {
            data[i]=line;        //Stores each line as an array string
            i=i++;               //Increments the counter that increments which array slot the line is stored in
            dataMAX=dataMAX++;   //Counts the number of lines entered
        }
     PersonInfo.close();      //Closes the file
    }
    for (i=1; i<=dataMAX; i=i+5) //i begins at first SS# line; shifts to next line once if statement is complete
    {
        for (y=6+i-1; y<=dataMAX; y=y+5)
        {
        if (data[y]<data[i])  //Compares SS#'s
          {
          temp=data[i-1];     //Name#1 held in temp
     data[i-1]=data[y-1];     //Name#2 moved into Name#1 slot
          data[y-1]=temp;     //Name#1 moved into slot 2
            temp=data[i];     //SS#1 held in temp
         data[i]=data[y];     //SS#2 moved into SS#1 slot
            data[y]=temp;     //SS#1 moved into slot 2
          temp=data[i+1];     //Age#1 held in temp
     data[i+1]=data[y+1];     //Age#2 moved into Age#1 slot
          data[y+1]=temp;     //Age#1 moved into slot 2
          temp=data[i+2];     //Address#1 held in temp
     data[i+2]=data[y+2];     //Address#2 moved into Address#1 slot
          data[y+2]=temp;     //Address#1 moved into slot 2
          }
        }
    }
    for(i=0; i<dataMAX; i++)  //Prints all of the data once sorted
        {
          cout << data[i] << endl;
        }
}
//New Person's Information Collector Function**********************************************//
void AddNewPerson (char CON)
{
    if (CON == 'Y' || CON == 'y')                                        //Condition to add new person
    {
       int i=0;   //Sets counter
       ofstream NewPerson ("a1.txt", ios::ate | ios::app);               //Opens text and sets output
           while (CON == 'Y' || CON == 'y')
           {
           NewPerson << '\n' << '\n';
           cout << "Please enter the person's first name:";                             //Asks for first name from user
              cin >> person.firstName;                                                  //Takes in first name from user
           cout << "Please enter the person's last name:";                              //Asks for last name from user
              cin >> person.lastName;                                                   //Takes in last name from user
              NewPerson << person.lastName << ',';                                      //Adds last name to text
              NewPerson << person.firstName << '\n';                                    //Adds first name to text
           cout <<"Please enter the person's Social Security number (no dashes):";      //Asks for social security number from user
              cin >> person.SSN;                                                        //Takes in SSN from user
              NewPerson << person.SSN << '\n';                                          //Writes SSN to text
           cout <<"Please enter the person's age:";                                     //Asks for persons age from user
              cin >> person.age;                                                        //Takes in age from user
              NewPerson << person.age << '\n';                                          //Adds age to text
           cout <<"Please enter the person's address:";                                 //Asks user for address
              cin.ignore();                                                             //Ignores enter from previous cin
              getline(cin, person.address);                                             //Gets address line from user
              NewPerson << person.address;                                              //Writes address to text
              cout << endl << person.lastName << "," << person.firstName << endl;       //Prints the new entry data to console...
              cout << person.SSN << endl;
              cout << person.age << endl;
              cout << person.address << endl;
           cout << endl << "Would you like to add another new person? (Y/N):";
              cin >> CON;
           }
        NewPerson.close();                                                  //Closes the file
      }
}
//Search Function*************************************************************************//
void SearchFile (char LOOK)
{
    ifstream SearchResult ("a1.txt");
    int i=0, counter=0, counter2=0, z=0, resultFound=0;
    string line, LastName, names[125], delimiter = ",", found[125], token, temp;
    if (SearchResult.is_open())
    {
        while (getline(SearchResult,line)) //Reads in the data from the text and writes to an array
        {
            names[i]=line;            //Stores each line as an array string
            i=i++;
            counter=counter++;        //Increments the counter that increments which array the line is stored in
        }
           SearchResult.close();      //Closes the file
    }
        while (LOOK == 'Y' || LOOK == 'y')                        //Search Start Condition
        {
        cout << "Please enter a last name to search for:";        //Tells user to input last name
                 cin >> LastName;                                 //Takes last name to search as user input
                 cout << endl;
         for (i=0; i<=counter; i++)                                //Search condition
         {
            temp = names[i];                                      //Line stored in array is stored in temp
            string token = temp.substr(0, temp.find(delimiter));  //Delimiter is applied
              if (LastName == token)                              //If the delimited line is the same as last name
              {
                  resultFound=1;                                       //Check variable set when result is found
                  cout << names[i] << endl;                            //Print line
                  found[counter2]=names[i];                            //Store line
                  counter2=counter2++;                                 //Increment counter
                  cout << names[i+1] << endl;                          //Print next line
                  found[counter2]=names[i+1];                          //Store next line
                  counter2=counter2++;                                 //Increment counter
                  cout << names[i+2] << endl;                          //Print next line
                  found[counter2]=names[i+2];                          //Store next line
                  counter2=counter2++;                                 //Increment counter
                  cout << names[i+3] << endl << endl;                  //Print next line
                  found[counter2]=names[i+3];                          //Store next line
                  counter2=counter2++;                                 //Increment counter
                  found[counter2]='\n';                                //Add blank line after printed data
                  counter2=counter2++;                                 //Increment counter
              }
         }
          if (resultFound==0)
          {
              cout << "No results found." << endl << endl;  //If no match is found, print message stating as such
          }
          else resultFound=0;              //Reset check variable
          cout << "Search again? (Y/N):";  //Condition to continue searching
          cin >> LOOK;                     //User input for condition
         }
        SearchResult.close();            //Close text file
        cout << endl << endl << "Results of all searches ->" << endl << endl;   //Insert blank line
        for (i=0; i<counter2; i++)
        {
            cout << found[i] << endl;    //Prints the searched for data
        }
}
//Main Program****************************************************************************//
int main()
{
cout << "Persons Information Database v1.0" << endl << endl;
        SortData(1); //Sorts and prints the data
cout << endl;
//Entering a New Person's Information*****************************************************//
        char NewAnswer;
cout << "Would you like to enter a new person's information? (Y/N):";
        cin >> NewAnswer;
        AddNewPerson (NewAnswer);  //Calls function to add new person
//Search Function Called******************************************************************//
        char SearchAns;
cout << "Would you like to search for a person's information? (Y/N):";
        cin >> SearchAns;
        SearchFile(SearchAns);    //Calls function to search file
cout << "Program complete.";
    return 0;
}
