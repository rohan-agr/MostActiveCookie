#include <iostream>
#include <getopt.h>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;


//Driver class to read command line
class Driver
{
    public:

    string get_filename(int argc, char** argv)
    {
        string fname = argv[1];
        return fname;
    }

    string get_options(int argc, char** argv) 
    {
            //Code formatted to be adjustable in the case that more options are needed
            //Can add cases to the switch statement

            int option_index = 0, option = 0;
            opterr = false;
            struct option longOpts[] = {{ "date", required_argument, nullptr, 'd' }};
        
            while ((option = getopt_long(argc, argv, "d:", longOpts, &option_index)) != -1) 
            {
                switch (option) 
                {
                    case 'd':
                        return optarg;
                        break;

                    cout << "Invalid argument" << "\n";
                    exit(1);
                }
            }

            return "";
    }
};


/*
Hash Table
    - Implements hashing function
    - Implements finding index in array
    - Utilizes quadratic probing for collision handling
    - Takes inputs by reference for efficiency and so that inputs can be modified
*/
class HashTable
{
    public:
    int hashVal(string &cookie)
    {
        int val = 0;
        char letter;

        for (int i = 0; i < 3; i++)
        {
            letter = cookie[i];
            val += letter;
        }

        return val;
    }

    //If cookie ID is present in table, increments frequency counter
    //If not, pushes cookie to the correct position with frequency 1
    //Returns frequency to compare with max
    int find_and_push(vector<pair<string, int> > &cookieTable, string &cookie)
    {
        int i = 0;
        int val = hashVal(cookie);

        int mapIdx = (val + i*i) % cookieTable.size();

        while(cookieTable[mapIdx].first != "")
        {
            if (cookieTable[mapIdx].first.compare(cookie) == 0)
            {
                cookieTable[mapIdx].second++;
                return cookieTable[mapIdx].second;
            }
            else
            {
                i++;
                mapIdx = (val + i*i) % cookieTable.size();
            }
        }

        cookieTable[mapIdx].first = cookie;
        cookieTable[mapIdx].second = 1;

        return 1;
    }

};


int main (int argc, char** argv)
{    
    Driver theDriver;
    string fname = theDriver.get_filename(argc, argv);
    string cookieDate = theDriver.get_options(argc, argv);

    //Opens file
    ifstream fin(fname);
    if (fin.is_open() == 0)
    {
        cout << "Error: file could not be opened.";
        return 1;
    }

    string line;

    //Take in the top of the input file (cookies, timestamp)
    getline(fin, line);

    //Main solution
    /*
        Takes in the input csv file, line by line. 
            - Does not do anything in the case that the cookie log date is 
              more recent than the argument date
            - Breaks from the loop if the cookie log date is older 
            - If cookie is from the correct date, adds/increments frequency
              counter in a hash map from cookie id to frequency. Augments the 
              max_frequency variable as necessary
            - Finally, iterates through unordered map, printing the IDs of the
              most accessed cookies
    */

   //Boolean variable to record if we have accessed records from the correct date
   //If we have, and then we don't get a match between cookieDate and date,
   //we have passed the range of cookies and can break out of the loop.
    bool dateRange = 0; 

    HashTable cookieHash;
    vector<pair<string, int> > cookieTable;
    cookieTable.resize(500);

    int max_frequency = 0;

    while(getline(fin, line))
    {
        string id = line.substr(0, 16);
        string date = line.substr(17, 10);

        if ((cookieDate.compare(date)) != 0)
        {
            if (dateRange == 1){break;}
        }
        else
        {
            dateRange = 1;
            int tempMax = cookieHash.find_and_push(cookieTable, id);
            if (tempMax > max_frequency){max_frequency = tempMax;}
        }
    }


    for(size_t i = 0; i < cookieTable.size(); i++)
    {
        if (cookieTable[i].second == max_frequency && max_frequency != 0)
        {
            cout << cookieTable[i].first << "\n";
        }
    }

    fin.close();
    return 1;

}