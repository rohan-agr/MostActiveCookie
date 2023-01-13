#include <iostream>
#include <getopt.h>
#include <string>
#include <fstream>
#include <sstream>

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


int main (int argc, char** argv)
{    
    Driver theDriver;
    string fname = theDriver.get_filename(argc, argv);
    string cookieDate = theDriver.get_options(argc, argv);

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
            - Does not do anything in the case that the cookie log date is more recent than the argument date
            - Breaks from the loop if the cookie log date is older 

    */
    while(getline(fin, line))
    {
        stringstream ss(line);
        string id;
        string date;
        string time;

        ss >> id >> date >> time;

        cout << id << date << time << endl;
    }

    fin.close();
    return 1;

}