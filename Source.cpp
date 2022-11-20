// Abhijeet Chopra, Oct 26 2016
// ThreeSum

/*
Problem Description:
Running time of the programs is approximately N(N-1)(N-2)/6.

In your report, you need to run the problem for N = 1K, 2K, 4K, 8K, 64K, 256K,
and 1M 24K and see how you obtain similar execution time.

In each run, you can will dynamic array and fill out the array with random
numbers between -90000 and +90000.

In you report, you will plot running time with respect to N.
Please make sure that random number generation is not included in the analysis.
*/

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

// data declarations
int *a;
int n;

// function prototypes
int randomInt();            // returns a random number between -90,000 and 90,000
int randomInt2();           // returns a random number between 0 and 1
int randomInt3();           // returns a random number between 0 and 2

void populateMatrix();      // populates array a[]
void displayMatrix();       // displays array a[]
void algorithm();           // executes the given algorithm
void analyzer(int n);       // calculates writes the execution time on console and .txt / .csv files

int main()
{
    srand(time(0));

    // enter the values of n in the array below
    // running the problem for N = 1K, 2K, 4K, 8K, 64K, 256K, and 1M 24K
    int arr[] = {
        1,                            // 0.
        10,                           // 1.
        100,                          // 2.
        1000,                         // 3.    1K
        2000,                         // 4.    2K
        3000,                         // 5.
        4000,                         // 6.    4K
        5000,
        6000,
        7000,
        8000,                         // 7.    8K
        9000,
        10000,
        64000,                        // 8.    64K
        256000,                       // 9.    256K
        1024000                       // 10.   1M 24K
    };

    for (int i = 0; i < (sizeof(arr)/sizeof(arr[0])); i++)
    {
        cout << arr[i] << endl;
        cout << "" << endl;
        analyzer(arr[i]);
    }

    return 0;
}

int randomInt()
{
    //(max - min + 1) + min;
    int x = rand() % 30001; // random number between max and min

    // randomly making x = x / 2x / 3x
    int randAdd = rand() % 3; //(2 - 0 + 1) + 0);
    // if randAdd == 0 // x remains x (0-30000)
    if (randAdd == 1)
    {
        x = 2 * x;// x becomes 2x (0-60000)
    }
    else if (randAdd == 2)
    {
        x = 3 * x;// x becomes 3x (0-90000)
    }

    // randomly making x negative
    int randSign = rand() % 2; //(1 - 0 + 1) + 0);
    if (randSign == 0)
    {
        x = -x; // x becomes negative (-90000 to 90000)
    }

    return x;
}

void populateMatrix()
{
    for (int i = 0; i < n; i++)
    {
        a[i] = randomInt();
    }
}

void displayMatrix()
{
    int neg = 0; // negative number counter
    for (int i = 0; i < n; i++)
    {
        if (i < 10) cout << " ";
        cout << i << ". ";
        if (a[i] > -1) cout << "+";
        cout << a[i] << endl;
        if (a[i] < 0) neg++; // increment neg counter if x is negative
    }
    cout << endl << "Negative numbers generated : " << neg << "/100" << endl;
}

void algorithm()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (a[i] + a[j] + a[k] == 0)
                {
                    cout << a[i] << " " << a[j] << " " << a[k] << " ";
                }
            }
        }
    }
}

void analyzer(int n_)
{
    n = n_;
    a = new int[n];

    int start_s;
    int stop_s;
    int diff_s;
    double secs_s;

    populateMatrix();
    //displayMatrix(); //for testing

    start_s = clock(); // start time

    cout << "Starting loop for n = " << n << endl;
    cout << "---------------------" << endl;

    algorithm();

    cout << endl;
    cout << "---------------------" << endl;
    cout << "Ending loop for n = " << n << endl;

    stop_s = clock(); // stop time
    diff_s = stop_s - start_s;
    secs_s = diff_s / double(CLOCKS_PER_SEC);

    cout << endl;

    //cout << "clockes per sec: " << CLOCKS_PER_SEC << endl;
    //cout << "time start: " << start_s << endl;
    //cout << "time stop: " << stop_s << endl;

    cout << "Execution time: " << secs_s << " seconds" << endl;

    // writing results to .txt file
    string filename_txt = string("analysis_") + to_string(n) + ".txt";
    std::ofstream outfile(filename_txt);
    outfile << "Execution time: " << secs_s << " seconds" << std::endl;
    outfile.close();

    string filename_csv = string("analysis_") + "csv" + ".csv";

    // writing the results to .csv file
    // manually check if csv exits and make flag csv_exists true if found
    bool csv_exists = true;
    if(!csv_exists)
    {
        // file does not exist
        cout << "File not found! Creating new .csv file... " << endl;
        // writing results to .csv file
        std::ofstream outfile_csv(filename_csv);
        outfile_csv << "n" << "," << "t" << std::endl; // csv file header
        //outfile_csv << n << "," << secs_s << std::endl; // inserting first data row
        outfile_csv.close();
    }
    else
    {
        // file already exists
        cout << "File found! Appending results to existing file... " << endl;
		// appending results to .csv file
        std::ofstream outfile_csv;
        outfile_csv.open(filename_csv, std::ios_base::app); // opening existing file
        outfile_csv << n << "," << to_string(secs_s) << std::endl; // appending data row
    }
    cout << "---------------------" << endl << endl;
}