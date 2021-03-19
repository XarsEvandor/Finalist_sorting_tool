//NOTE: REMEMBER TO USE THE SORTING METHODS BEFORE THE OPTIONS METHODS IN THE MENU!!!

#include <iostream> //Used for IO
#include <ctime>    //Used to obtain CPU clock
#include <fstream>  //Used for file manipulation
#include <iomanip>  //Required for setw()
#include <limits>   //Required for error trapping: numeric_limits<streamsize>::max()
#include <math.h>   //Required for some math operations

using namespace std;

static float sortedArr[12] = {0}; //Universal arrays. Made them static to ensure there will be no garbage data during the executions of muliple methods.
static string stringSortedArr[12];

//Declaring all methods.
int perPostData(string lName[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12], int posts[12]);

int display(string lName[12], int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12]);

int likeppFilter(string fName[12], string lName[12], string origin[12], string sex[12],
                 int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12]);

int numSort(float array[12], string fName[12], string lName[12], string origin[12], string sex[12],
            int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12], int order);

int stringSort(string array[12], string fName[12], string lName[12], string origin[12], string sex[12],
               int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12], int order);

int newMetric(string fName[12], string lName[12], string origin[12], string sex[12],
              int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12]);

int userSort(string fName[12], string lName[12], string origin[12], string sex[12],
             int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12]);

int genderStatistics(string sex[12], int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12]);

int finalScore(string fName[12], string lName[12], string origin[12], string sex[12],
               int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12]);

// Note: It would be relatively easy to make this application adaptable to any number of data inserted (more than 12 rows). This would require a counter to be set
// that will increase for every line read from the file. We would set the loop that reads from the file to while(!eof) and we would later initialize everything
// using the counter. The reason I chose not to use this method is that it would drastically change the taught format of coding, as all global vars and methods would have
// to be intialized after the main, something that would make the code harder to read and correct, especially considering the size of it.
int main()
{
    //Declare and initialize all needed variables and arrays. String arrays should NOT be initialized with null cause they are filled with garbage. Need to be careful with 
    //their usage.
    int xtraFollowers[12] = {0}, posts[12] = {0}, views[12] = {0}, engagements[12] = {0}, likes[12] = {0}, comments[12] = {0}, shares[12] = {0};
    string fName[12], lName[12], origin[12], sex[12], header;
    int option(0);
    bool menubool(1);
    ifstream dataFile;

    while (menubool)
    {
        //Open the data file
        dataFile.open("data.txt");

        //Check if the data file can be found.
        if(!dataFile){
            cout << "Data file not found. Please make sure a data file named 'data.txt' is placed inside the folder of the main executable.";
            return 0;
        }
        getline(dataFile, header);

        //Read data from the data file
        for (int i = 0; i < 12; i++)
        {
            dataFile >> fName[i] >> lName[i] >> origin[i] >> sex[i] >> xtraFollowers[i] >> posts[i] >> views[i] >> engagements[i] >> likes[i] >> comments[i] >> shares[i];
        }

        dataFile.close();


        //Menu starts here.
        cout << endl;

        cout << "===============================================" << endl
             << "USER MENU: SOCIAL MEDIA CONTEST DATA STATISTICS" << endl
             << "===============================================" << endl;

        cout
            << endl
            << "Please make your selection." << endl
            << "1. Display contest stats for the 12 finalists." << endl
            << "2. Calculate and display per post data values." << endl
            << "3. Filter and sort data by likes/post." << endl
            << "4. Calculate and display sorted data for a new performance metric." << endl
            << "5. Parametrized sorting, display and saving of processed data" << endl
            << "6. Sort and display data by applicant origin." << endl
            << "7. Calculate and display stats per gender." << endl
            << "8. Calculate and display the final score of all candidates." << endl
            << "9. EXIT" << endl;

        cout << "Input: ";

        cin >> option;

        cout << endl;

        cin.sync(); // Clears the cin buffer

        while (cin.fail()) // Error trapping begins
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // helps survive text char input
            cout << "Invalid entry. Try again: ";
            cin >> option;
            cin.sync(); // Clears the cin buffer
        }

        //Trapping for out of bounds user error
        while (true)
        {
            if (option > 9 || option < 1)
            {
                cout << "Please remain within the specified margins." << endl;
                cout << "Input: ";
                cin >> option;
                cin.sync(); // Clears the cin buffer
            }
            else
                break;
        }

        //Call the methods corresponding to the menu choice
        switch(option)
        {
        case 1:
            display(lName, xtraFollowers, posts, views, engagements, likes, comments, shares);
            break;

        case 2:
            perPostData(lName, views, engagements, likes, comments, shares, posts);
            break;
        
        case 3:
            likeppFilter(fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares);
            break;

        case 4:
            newMetric(fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares);
            break;
        
        case 5:
            userSort(fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares);
            break;
        
        case 6:
            //Sort by origin and display the resulting table.
            stringSort(origin, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, 1);
            cout << left
                    << setw(10) << setfill(' ') << "FIRST"
                    << setw(10) << setfill(' ') << "LAST"
                    << setw(8) << setfill(' ') << "ORG"
                    << setw(8) << setfill(' ') << "SEX"
                    << setw(8) << setfill(' ') << "FOL"
                    << setw(8) << setfill(' ') << "PST"
                    << setw(8) << setfill(' ') << "VIW"
                    << setw(8) << setfill(' ') << "ENG"
                    << setw(8) << setfill(' ') << "LIK"
                    << setw(8) << setfill(' ') << "CMT"
                    << setw(8) << setfill(' ') << "SHR"
                    << endl
                    << "----------------------------------------------------------------------------------------"
                    << endl;

            for (int i = 0; i < 12; i++)
            {
                cout << left
                        << setw(10) << setfill(' ') << fName[i]
                        << setw(10) << setfill(' ') << lName[i]
                        << setw(8) << setfill(' ') << origin[i]
                        << setw(8) << setfill(' ') << sex[i]
                        << setw(8) << setfill(' ') << xtraFollowers[i]
                        << setw(8) << setfill(' ') << posts[i]
                        << setw(8) << setfill(' ') << views[i]
                        << setw(8) << setfill(' ') << engagements[i]
                        << setw(8) << setfill(' ') << likes[i]
                        << setw(8) << setfill(' ') << comments[i]
                        << setw(8) << setfill(' ') << shares[i]
                        << endl;
            }
            break;
            
        case 7:
            genderStatistics(sex, xtraFollowers, posts, views, engagements, likes, comments, shares);
            break;
        
        case 8:
            finalScore(fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares);
            break;

        default:
            //Due to the margin trap from before the only possible value for default will be 8, and thus we exit
            menubool = 0;
            break;
        }
    }

    return 0;
}

int perPostData(string lName[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12], int posts[12])
{
    //Initialize and declare local arrays and variables
    float viewspp[12] = {0}, engagementspp[12] = {0}, likespp[12] = {0}, commentspp[12] = {0}, sharespp[12] = {0};

    //Calculate per post metrics
    for (int i = 0; i < 12; i++){
        viewspp[i] = views[i] / posts[i];
        engagementspp[i] = engagements[i] / posts[i];
        likespp[i] = likes[i] / posts[i];
        commentspp[i] = comments[i] / posts[i];
        sharespp[i] = shares[i] / posts[i];
    }

    //Display data
    cout << "Here are the 'per-post' statistics." << endl << endl;

    cout << left
         << setw(12) << setfill(' ') << "LAST"
         << setw(6) << setfill(' ') << "PST"
         << setw(10) << setfill(' ') << "VIW/PST"
         << setw(10) << setfill(' ') << "ENG/PST"
         << setw(10) << setfill(' ') << "LIK/PST"
         << setw(10) << setfill(' ') << "CMT/PST"
         << setw(10) << setfill(' ') << "SHR/PST"
         << endl
         << "-------------------------------------------------------------"
         << endl;

    for (int i = 0; i < 12; i++)
    {
        cout << left
             << setw(12) << setfill(' ') << lName[i]
             << setw(6) << setfill(' ') << posts[i]
             << setw(10) << setfill(' ') << viewspp[i]
             << setw(10) << setfill(' ') << engagementspp[i]
             << setw(10) << setfill(' ') << likespp[i]
             << setw(10) << setfill(' ') << commentspp[i]
             << setw(10) << setfill(' ') << sharespp[i]
             << endl;
    }

    return 0;
}

int display(string lName[12], int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12])
{   
    //Display the data
    cout << left 
            << setw(10) << setfill(' ') << "LAST"
            << setw(8) << setfill(' ') << "FOL"
            << setw(8) << setfill(' ') << "PST"
            << setw(8) << setfill(' ') << "VIW"
            << setw(8) << setfill(' ') << "ENG"
            << setw(8) << setfill(' ') << "LIK"
            << setw(8) << setfill(' ') << "CMT"
            << setw(8) << setfill(' ') << "SHR"
            << endl
            << "-------------------------------------------------------------"
            << endl;

    for (int i = 0; i < 12; i++){
        cout << left
             << setw(10) << setfill(' ') << lName[i]
             << setw(8) << setfill(' ') << xtraFollowers[i]
             << setw(8) << setfill(' ') << posts[i]
             << setw(8) << setfill(' ') << views[i]
             << setw(8) << setfill(' ') << engagements[i]
             << setw(8) << setfill(' ') << likes[i]
             << setw(8) << setfill(' ') << comments[i]
             << setw(8) << setfill(' ') << shares[i]
             << endl;
    }

    return 0;
}

int likeppFilter(string fName[12], string lName[12], string origin[12], string sex[12],
                 int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12])
{
    //Initialize and declare local variables and arrays
    float likespp[12] = {0};
    int lowerLim(0);

    //Populate the likes per post array.
    for (int i = 0; i < 12; i++){
        likespp[i] = (float)likes[i] / (float)posts[i];
    }

    //set  cout formatting
    cout.setf(ios::showpoint);
    cout.setf(ios::fixed);
    cout.precision(2);

    //Sort based on likespp
    numSort(likespp, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, 0);

    //Request user input
    cout << "Please set a lower limit. The program will display only the candidates that have achieved more likes per post than the set limit." << endl;

    cout << "The unfiltered data will be displayed to help you make your decision." << endl
         << endl;

    cout << left
         << setw(12) << setfill(' ') << "FIRST"
         << setw(12) << setfill(' ') << "LAST"
         << setw(10) << setfill(' ') << "ORG"
         << setw(10) << setfill(' ') << "SEX"
         << setw(10) << setfill(' ') << "LIK"
         << setw(10) << setfill(' ') << "PST"
         << setw(10) << setfill(' ') << "LIK/PST"
         << endl
         << "-----------------------------------------------------------------------"
         << endl;

    for (int i = 0; i < 12; i++)
    {
        cout << left
             << setw(12) << setfill(' ') << fName[i]
             << setw(12) << setfill(' ') << lName[i]
             << setw(10) << setfill(' ') << origin[i]
             << setw(10) << setfill(' ') << sex[i]
             << setw(10) << setfill(' ') << likes[i]
             << setw(10) << setfill(' ') << posts[i]
             << setw(10) << setfill(' ') << likespp[i]
             << endl;
    }

    cout << "You can view the unfiltered data again by entering '505'" << endl << "Please note that the limit must be an integer." << endl
         << "Input: ";

    cin >> lowerLim;

    cout << endl;

    cin.sync(); // Clears the cin buffer

    while (cin.fail()) // Error trapping begins
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // helps survive text char input
        cout << "Invalid entry. Try again: ";
        cin >> lowerLim;
        cin.sync(); // Clears the cin buffer
    }

    //Margin trapping. If the user enters 505 the unfiltered data will be re-displayed
    while (true)
    {
        if(lowerLim == 505)
        {
            cout << left
                 << setw(12) << setfill(' ') << "FIRST"
                 << setw(12) << setfill(' ') << "LAST"
                 << setw(10) << setfill(' ') << "ORG"
                 << setw(10) << setfill(' ') << "SEX"
                 << setw(10) << setfill(' ') << "LIK"
                 << setw(10) << setfill(' ') << "PST"
                 << setw(10) << setfill(' ') << "LIK/PST"
                 << endl
                 << "-----------------------------------------------------------------------"
                 << endl;

            for (int i = 0; i < 12; i++)
            {
                cout << left
                     << setw(12) << setfill(' ') << fName[i]
                     << setw(12) << setfill(' ') << lName[i]
                     << setw(10) << setfill(' ') << origin[i]
                     << setw(10) << setfill(' ') << sex[i]
                     << setw(10) << setfill(' ') << likes[i]
                     << setw(10) << setfill(' ') << posts[i]
                     << setw(10) << setfill(' ') << likespp[i]
                     << endl;
            }

            cout << "Input: ";

            cin.sync();
            cin >> lowerLim;

            while (cin.fail()) // Error trapping begins
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // helps survive text char input
                cout << "Invalid entry. Try again: ";
                cin >> lowerLim;
                cin.sync(); // Clears the cin buffer
            }
        }

        if (lowerLim < 0)
        {
            cout << "Please enter a positive integer." << endl;
            cout << "Input: ";
            cin >> lowerLim;

            while (cin.fail()) // Error trapping begins
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // helps survive text char input
                cout << "Invalid entry. Try again: ";
                cin >> lowerLim;
                cin.sync(); // Clears the cin buffer
            }
        }
        else if (lowerLim == 0)
        {
            cout << "You can do better than that. Try higher." << endl;
            cout << "Input: ";
            cin >> lowerLim;

            while (cin.fail()) // Error trapping begins
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // helps survive text char input
                cout << "Invalid entry. Try again: ";
                cin >> lowerLim;
                cin.sync(); // Clears the cin buffer
            }
        }
        else if (lowerLim > 500)
        {
            cout << "That's asking for a lot. Please lower your expectations" << endl;
            cout << "Input: ";
            cin >> lowerLim;

            while (cin.fail()) // Error trapping begins
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // helps survive text char input
                cout << "Invalid entry. Try again: ";
                cin >> lowerLim;
                cin.sync(); // Clears the cin buffer
            }
        }
        else
            break;
    }

    cout << endl
         << "Here are the filtered results." << endl
         << endl;

    cout << left
         << setw(12) << setfill(' ') << "FIRST"
         << setw(12) << setfill(' ') << "LAST"
         << setw(10) << setfill(' ') << "ORG"
         << setw(10) << setfill(' ') << "SEX"
         << setw(10) << setfill(' ') << "LIK"
         << setw(10) << setfill(' ') << "PST"
         << setw(10) << setfill(' ') << "LIK/PST"
         << endl
         << "-----------------------------------------------------------------------"
         << endl;
    
    for (int i = 0; i < 12; i++)
    {
        if(likespp[i] > lowerLim)
        {
            cout << left
             << setw(12) << setfill(' ') << fName[i]
             << setw(12) << setfill(' ') << lName[i]
             << setw(10) << setfill(' ') << origin[i]
             << setw(10) << setfill(' ') << sex[i]
             << setw(10) << setfill(' ') << likes[i]
             << setw(10) << setfill(' ') << posts[i]
             << setw(10) << setfill(' ') << likespp[i]
             << endl;
        }
        
    }

    return 0;
}

int numSort(float array[12], string fName[12], string lName[12], string origin[12], string sex[12],
            int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12], int order)
{
    //Declare and initialize local varibles
    float king(0);
    int pos(0);
    float temp(0);
    string tempString;

    //Populate sortedArr before actually sorting it
    for (int i = 0; i < 12; i++)
    {
        sortedArr[i] = array[i];
    }

    //Simple selection sort that takes into consideration the order variable to sort scending or descending. 
    for (int k = 0; k < 12; k++){

        for (int i = 0 + k; i < 12; i++)
        {
            if (i == 0 + k)
            {
                king = sortedArr[i];
                pos = i;
            }

            if(order == 0){
                if (king < sortedArr[i])
                {
                    king = sortedArr[i];
                    pos = i;
                }
            }
            else if(order == 1){
                if (king > sortedArr[i])
                {
                    king = sortedArr[i];
                    pos = i;
                }
            }
            else{
                cout << "There was a problem, please contact IT with the following code: OB-0023-HOW-DID-THIS-HAPPEN-1232";
                throw("What even");
            }
        }

        //Swap the values of the array to place the correct numbers in the correct positions
        temp = sortedArr[k];
        sortedArr[k] = sortedArr[pos];
        sortedArr[pos] = temp;

        //Repeat the process for all arrays in order to short them along.

        tempString = fName[k];
        fName[k] = fName[pos];
        fName[pos] = tempString;

        tempString = lName[k];
        lName[k] = lName[pos];
        lName[pos] = tempString;

        tempString = origin[k];
        origin[k] = origin[pos];
        origin[pos] = tempString;

        tempString = sex[k];
        sex[k] = sex[pos];
        sex[pos] = tempString;

        temp = xtraFollowers[k];
        xtraFollowers[k] = xtraFollowers[pos];
        xtraFollowers[pos] = temp;

        temp = posts[k];
        posts[k] = posts[pos];
        posts[pos] = temp;

        temp = views[k];
        views[k] = views[pos];
        views[pos] = temp;

        temp = engagements[k];
        engagements[k] = engagements[pos];
        engagements[pos] = temp;

        temp = likes[k];
        likes[k] = likes[pos];
        likes[pos] = temp;

        temp = comments[k];
        comments[k] = comments[pos];
        comments[pos] = temp;

        temp = shares[k];
        shares[k] = shares[pos];
        shares[pos] = temp;
    }

    //we now re-populate array using sortedArr
    for (int i = 0; i < 12; i++)
    {
        array[i] = sortedArr[i];
    }
    
    return 0;
}

int stringSort(string array[12], string fName[12], string lName[12], string origin[12], string sex[12],
               int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12], int order)
{
    //Declare and initialize local varibles
    int pos(0);
    int temp(0);
    string tempString; 
    string king;

    //Populate stringSortedArr before actually sorting it
    for (int i = 0; i < 12; i++)
    {
        stringSortedArr[i] = array[i];
    }

    for (int k = 0; k < 12; k++)
    {

        for (int i = 0 + k; i < 12; i++)
        {
            if (i == 0 + k)
            {
                king = stringSortedArr[i];
                pos = i;
            }

            if(order == 0){
                if (king < stringSortedArr[i])
                {
                    king = stringSortedArr[i];
                    pos = i;
                }
            }
            else if(order == 1){
                if (king > stringSortedArr[i])
                {
                    king = stringSortedArr[i];
                    pos = i;
                }
            }
            else{
                cout << "There was a problem, please contact IT with the following code: OB-0023-HOW-DID-THIS-HAPPEN-1232";
                throw "What even";
            }
        }

        //Swap the values of the array to place the correct numbers in the correct positions
        tempString = stringSortedArr[k];
        stringSortedArr[k] = stringSortedArr[pos];
        stringSortedArr[pos] = tempString;

        //Repeat the process for all arrays in order to short them along.

        tempString = fName[k];
        fName[k] = fName[pos];
        fName[pos] = tempString;

        tempString = lName[k];
        lName[k] = lName[pos];
        lName[pos] = tempString;

        tempString = origin[k];
        origin[k] = origin[pos];
        origin[pos] = tempString;

        tempString = sex[k];
        sex[k] = sex[pos];
        sex[pos] = tempString;

        temp = xtraFollowers[k];
        xtraFollowers[k] = xtraFollowers[pos];
        xtraFollowers[pos] = temp;

        temp = posts[k];
        posts[k] = posts[pos];
        posts[pos] = temp;

        temp = views[k];
        views[k] = views[pos];
        views[pos] = temp;

        temp = engagements[k];
        engagements[k] = engagements[pos];
        engagements[pos] = temp;

        temp = likes[k];
        likes[k] = likes[pos];
        likes[pos] = temp;

        temp = comments[k];
        comments[k] = comments[pos];
        comments[pos] = temp;

        temp = shares[k];
        shares[k] = shares[pos];
        shares[pos] = temp;
    }
    return 0;
}

int newMetric(string fName[12], string lName[12], string origin[12], string sex[12],
              int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12])
{
    //Declare and initialize local varibles
    float newMetric[12] = {0};
    ofstream newMetricOut;
    ifstream newMetricIn;

    //Populate the newMetric array
    for (int i = 0; i < 12; i++){
        //Since some people have 0 shares and this metric relies on multiplication, we will increase their number of shares by one so as to get sensible and comparable
        //results when it comes to the other factors in the calculation.
        if(shares[i] == 0)
            shares[i]++;
        newMetric[i] = (likes[i] * comments[i] * shares[i]) / posts[i];
    }

    //Sort on newMetric
    numSort(newMetric, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, 0);

    //Save the results in the file
    newMetricOut.open("social_media_contest_processed_data.txt");

    cout << endl
         << endl
         << "Note: Applicants with 0 shares have been given a pity share so that the calculations can be executed properly." 
         << endl
         << endl;

    newMetricOut << left
         << setw(10) << setfill(' ') << "FIRST"
         << setw(10) << setfill(' ') << "LAST"
         << setw(8) << setfill(' ') << "ORG"
         << setw(8) << setfill(' ') << "SEX"
         << setw(8) << setfill(' ') << "FOL"
         << setw(8) << setfill(' ') << "PST"
         << setw(8) << setfill(' ') << "VIW"
         << setw(8) << setfill(' ') << "ENG"
         << setw(8) << setfill(' ') << "LIK"
         << setw(8) << setfill(' ') << "CMT"
         << setw(8) << setfill(' ') << "SHR"
         << setw(8) << setfill(' ') << "NEW"
         << endl
         << "-------------------------------------------------------------------------------------------------"
         << endl;

    for (int i = 0; i < 12; i++)
    {
        newMetricOut << left
            << setw(10) << setfill(' ') << fName[i]
            << setw(10) << setfill(' ') << lName[i]
            << setw(8) << setfill(' ') << origin[i]
            << setw(8) << setfill(' ') << sex[i]
            << setw(8) << setfill(' ') << xtraFollowers[i]
            << setw(8) << setfill(' ') << posts[i]
            << setw(8) << setfill(' ') << views[i]
            << setw(8) << setfill(' ') << engagements[i]
            << setw(8) << setfill(' ') << likes[i]
            << setw(8) << setfill(' ') << comments[i]
            << setw(8) << setfill(' ') << shares[i]
            << setw(8) << setfill(' ') << newMetric[i]
            << endl;
    }

    newMetricOut.close();
    newMetricIn.open("social_media_contest_processed_data.txt");

    cout << "The  data have been saved in social_media_contest_processed_data.txt. Here is a compact display." << endl
         << endl;

    //Variable used to skip unneeded data when reading from the file.
    int numDataSkipper(0);
    string headerSkipper;

    //We could just display the values of these arrays immedietly but the project description requires we read them from the file.
    string fNameDisplay[12];
    string lNameDisplay[12];
    string originDisplay[12];
    string sexDisplay[12];
    int newMetricDisplay[12] = {0};

    //Skip the header and the dashes
    getline(newMetricIn, headerSkipper);
    getline(newMetricIn, headerSkipper);

    //read data from the file and populate local arrays
    for (int i = 0; i < 12; i++){
        newMetricIn >> fNameDisplay[i] >> lNameDisplay[i] >> originDisplay[i] >> sexDisplay[i] >>
            numDataSkipper >> numDataSkipper >> numDataSkipper >> numDataSkipper >> numDataSkipper >> numDataSkipper >> numDataSkipper >>
            newMetricDisplay[i];
    }

    //Display local arrays
    cout << left
        << setw(10) << setfill(' ') << "FIRST"
        << setw(10) << setfill(' ') << "LAST"
        << setw(8) << setfill(' ') << "ORG"
        << setw(8) << setfill(' ') << "SEX"
        << setw(8) << setfill(' ') << "NEW"
        << endl
        << "---------------------------------------"
        << endl;

    for (int i = 0; i < 12; i++)
    {
        cout << left
            << setw(10) << setfill(' ') << fNameDisplay[i]
            << setw(10) << setfill(' ') << lNameDisplay[i]
            << setw(8) << setfill(' ') << originDisplay[i]
            << setw(8) << setfill(' ') << sexDisplay[i]
            << setw(8) << setfill(' ') << newMetricDisplay[i]
            << endl;
    }

    return 0;
}

int userSort(string fName[12], string lName[12], string origin[12], string sex[12],
             int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12])
    {
        //Declare and initialize local varibles
        float viewspp[12] = {0}, engagementspp[12] = {0}, likespp[12] = {0}, commentspp[12] = {0}, sharespp[12] = {0}, newMetric[12] = {0};
        int option(0), orderOption(0);
        bool menubool(1);
        ofstream dataOut;

        //Set formatting for dataOut
        dataOut.open("social_media_sorted_stats.txt");
        dataOut.setf(ios::fixed);
        dataOut.setf(ios::showpoint);
        dataOut.precision(2);

        //Populate local arrays
        for (int i = 0; i < 12; i++)
        {
            //Since some people have 0 shares and the new metric relies on multiplication, we will increase their number of shares by one so as to get sensible and comparable
            //results when it comes to the other factors in the calculation.
            if (shares[i] == 0)
                shares[i]++;

            newMetric[i] = ((float)likes[i] * (float)comments[i] * (float)shares[i]) / (float)posts[i];
            viewspp[i] = (float)views[i] / (float)posts[i];
            engagementspp[i] = (float)engagements[i] / (float)posts[i];
            likespp[i] = (float)likes[i] / (float)posts[i];
            commentspp[i] = (float)comments[i] / (float)posts[i];
            sharespp[i] = (float)shares[i] / (float)posts[i];
        }

        //Menu starts
        cout << endl
             << endl
             << "Note: Applicants with 0 shares have been given a pity share so that the calculations can be executed properly."
             << endl
             << endl;

        cout << "Please select the column that will be the basis for the sorting procedure." << endl
             << "To help you choose, the unfiltered statistics will be displayed." << endl << endl;

        cout << "Here are the 'per-post' statistics." << endl
             << endl;

        cout << left
             << setw(12) << setfill(' ') << "LAST"
             << setw(6) << setfill(' ') << "PST"
             << setw(10) << setfill(' ') << "VIW/PST"
             << setw(10) << setfill(' ') << "ENG/PST"
             << setw(10) << setfill(' ') << "LIK/PST"
             << setw(10) << setfill(' ') << "CMT/PST"
             << setw(10) << setfill(' ') << "SHR/PST"
             << setw(10) << setfill(' ') << "NEW"
             << endl
             << "---------------------------------------------------------------------------"
             << endl;

        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(2);

        for (int i = 0; i < 12; i++)
        {
            cout << left
                 << setw(12) << setfill(' ') << lName[i]
                 << setw(6) << setfill(' ') << posts[i]
                 << setw(10) << setfill(' ') << viewspp[i]
                 << setw(10) << setfill(' ') << engagementspp[i]
                 << setw(10) << setfill(' ') << likespp[i]
                 << setw(10) << setfill(' ') << commentspp[i]
                 << setw(10) << setfill(' ') << sharespp[i]
                 << setw(10) << setfill(' ') << newMetric[i]
                 << endl;
        }

        while(menubool){
            //Ask for user input
            cout << endl << "Please make your selection." << endl
                << "1. Sort by VIW/PST" << endl
                << "2. Sort by ENG/PST" << endl
                << "3. Sort by LIK/PST" << endl
                << "4. Sort by CMT/PST" << endl
                << "5. Sort by SHR/PST" << endl
                << "6. Sort by NEW" << endl
                << "7. EXIT" << endl;

            cout << "Input: ";

            cin >> option;

            cout << endl;

            cin.sync(); // Clears the cin buffer

            while (cin.fail()) // Error trapping begins
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // helps survive text char input
                cout << "Invalid entry. Try again: ";
                cin >> option;
                cin.sync(); // Clears the cin buffer
            }

            //Margin trapping
            while (true)
            {
                if (option > 7 || option < 1)
                {
                    cout << "Please remain within the specified margins." << endl;
                    cout << "Input: ";
                    cin >> option;
                    cin.sync(); // Clears the cin buffer
                }
                else
                    break;
            }

            //If the user does not want to exit the menu he will be asked to provide the order for sorting
            if(option != 7){
                cout << endl
                     << "Please select if the data will be sorted in ascending or descending order." << endl;
                cout << "0. Descending" << endl
                     << "1. Ascending" << endl;

                cout << "Input: ";

                cin >> orderOption;

                cout << endl;

                cin.sync(); // Clears the cin buffer

                while (cin.fail()) // Error trapping begins
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // helps survive text char input
                    cout << "Invalid entry. Try again: ";
                    cin >> orderOption;
                    cin.sync(); // Clears the cin buffer
                }

                while (true)
                {
                    if (orderOption > 1 || orderOption < 0)
                    {
                        cout << "Please remain within the specified margins." << endl;
                        cout << "Input: ";
                        cin >> orderOption;
                        cin.sync(); // Clears the cin buffer
                    }
                    else
                        break;
                }
            }
            
            switch (option)
            {
            case 1:
                //For all options, we sort based on the desired array and in the chosen order and we display the data as well as write them in the datafile
                numSort(viewspp, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, orderOption);

                for (int i = 0; i < 12; i++)
                {
                    newMetric[i] = ((float)likes[i] * (float)comments[i] * (float)shares[i]) / (float)posts[i];
                    viewspp[i] = (float)views[i] / (float)posts[i];
                    engagementspp[i] = (float)engagements[i] / (float)posts[i];
                    likespp[i] = (float)likes[i] / (float)posts[i];
                    commentspp[i] = (float)comments[i] / (float)posts[i];
                    sharespp[i] = (float)shares[i] / (float)posts[i];
                }

                cout << "Here are the results." << endl
                     << endl;

                cout << left
                     << setw(12) << setfill(' ') << "LAST"
                     << setw(6) << setfill(' ') << "PST"
                     << setw(10) << setfill(' ') << "VIW/PST"
                     << setw(10) << setfill(' ') << "ENG/PST"
                     << setw(10) << setfill(' ') << "LIK/PST"
                     << setw(10) << setfill(' ') << "CMT/PST"
                     << setw(10) << setfill(' ') << "SHR/PST"
                     << setw(10) << setfill(' ') << "NEW"
                     << endl
                     << "---------------------------------------------------------------------------"
                     << endl;

                for (int i = 0; i < 12; i++)
                {
                    cout << left
                         << setw(12) << setfill(' ') << lName[i]
                         << setw(6) << setfill(' ') << posts[i]
                         << setw(10) << setfill(' ') << viewspp[i]
                         << setw(10) << setfill(' ') << engagementspp[i]
                         << setw(10) << setfill(' ') << likespp[i]
                         << setw(10) << setfill(' ') << commentspp[i]
                         << setw(10) << setfill(' ') << sharespp[i]
                         << setw(10) << setfill(' ') << newMetric[i]
                         << endl;
                }

                dataOut << left
                     << setw(12) << setfill(' ') << "LAST"
                     << setw(6) << setfill(' ') << "PST"
                     << setw(10) << setfill(' ') << "VIW/PST"
                     << setw(10) << setfill(' ') << "ENG/PST"
                     << setw(10) << setfill(' ') << "LIK/PST"
                     << setw(10) << setfill(' ') << "CMT/PST"
                     << setw(10) << setfill(' ') << "SHR/PST"
                     << setw(10) << setfill(' ') << "NEW"
                     << endl
                     << "---------------------------------------------------------------------------"
                     << endl;

                for (int i = 0; i < 12; i++)
                {
                    dataOut << left
                         << setw(12) << setfill(' ') << lName[i]
                         << setw(6) << setfill(' ') << posts[i]
                         << setw(10) << setfill(' ') << viewspp[i]
                         << setw(10) << setfill(' ') << engagementspp[i]
                         << setw(10) << setfill(' ') << likespp[i]
                         << setw(10) << setfill(' ') << commentspp[i]
                         << setw(10) << setfill(' ') << sharespp[i]
                         << setw(10) << setfill(' ') << newMetric[i]
                         << endl;
                }

                cout << endl << "File social_media_sorted_stats.txt has been overwritten" << endl;
                break;

            case 2:
                numSort(engagementspp, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, orderOption);

                for (int i = 0; i < 12; i++)
                {
                    newMetric[i] = ((float)likes[i] * (float)comments[i] * (float)shares[i]) / (float)posts[i];
                    viewspp[i] = (float)views[i] / (float)posts[i];
                    engagementspp[i] = (float)engagements[i] / (float)posts[i];
                    likespp[i] = (float)likes[i] / (float)posts[i];
                    commentspp[i] = (float)comments[i] / (float)posts[i];
                    sharespp[i] = (float)shares[i] / (float)posts[i];
                }

                cout << "Here are the results." << endl
                     << endl;

                cout << left
                     << setw(12) << setfill(' ') << "LAST"
                     << setw(6) << setfill(' ') << "PST"
                     << setw(10) << setfill(' ') << "VIW/PST"
                     << setw(10) << setfill(' ') << "ENG/PST"
                     << setw(10) << setfill(' ') << "LIK/PST"
                     << setw(10) << setfill(' ') << "CMT/PST"
                     << setw(10) << setfill(' ') << "SHR/PST"
                     << setw(10) << setfill(' ') << "NEW"
                     << endl
                     << "---------------------------------------------------------------------------"
                     << endl;

                for (int i = 0; i < 12; i++)
                {
                    cout << left
                         << setw(12) << setfill(' ') << lName[i]
                         << setw(6) << setfill(' ') << posts[i]
                         << setw(10) << setfill(' ') << viewspp[i]
                         << setw(10) << setfill(' ') << engagementspp[i]
                         << setw(10) << setfill(' ') << likespp[i]
                         << setw(10) << setfill(' ') << commentspp[i]
                         << setw(10) << setfill(' ') << sharespp[i]
                         << setw(10) << setfill(' ') << newMetric[i]
                         << endl;
                }

                dataOut << left
                        << setw(12) << setfill(' ') << "LAST"
                        << setw(6) << setfill(' ') << "PST"
                        << setw(10) << setfill(' ') << "VIW/PST"
                        << setw(10) << setfill(' ') << "ENG/PST"
                        << setw(10) << setfill(' ') << "LIK/PST"
                        << setw(10) << setfill(' ') << "CMT/PST"
                        << setw(10) << setfill(' ') << "SHR/PST"
                        << setw(10) << setfill(' ') << "NEW"
                        << endl
                        << "---------------------------------------------------------------------------"
                        << endl;

                for (int i = 0; i < 12; i++)
                {
                    dataOut << left
                            << setw(12) << setfill(' ') << lName[i]
                            << setw(6) << setfill(' ') << posts[i]
                            << setw(10) << setfill(' ') << viewspp[i]
                            << setw(10) << setfill(' ') << engagementspp[i]
                            << setw(10) << setfill(' ') << likespp[i]
                            << setw(10) << setfill(' ') << commentspp[i]
                            << setw(10) << setfill(' ') << sharespp[i]
                            << setw(10) << setfill(' ') << newMetric[i]
                            << endl;
                }

                cout << endl << "File social_media_sorted_stats.txt has been overwritten" << endl;
                break;

            case 3:
                numSort(likespp, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, orderOption);

                for (int i = 0; i < 12; i++)
                {
                    newMetric[i] = ((float)likes[i] * (float)comments[i] * (float)shares[i]) / (float)posts[i];
                    viewspp[i] = (float)views[i] / (float)posts[i];
                    engagementspp[i] = (float)engagements[i] / (float)posts[i];
                    likespp[i] = (float)likes[i] / (float)posts[i];
                    commentspp[i] = (float)comments[i] / (float)posts[i];
                    sharespp[i] = (float)shares[i] / (float)posts[i];
                }

                cout << "Here are the results." << endl
                     << endl;

                cout << left
                     << setw(12) << setfill(' ') << "LAST"
                     << setw(6) << setfill(' ') << "PST"
                     << setw(10) << setfill(' ') << "VIW/PST"
                     << setw(10) << setfill(' ') << "ENG/PST"
                     << setw(10) << setfill(' ') << "LIK/PST"
                     << setw(10) << setfill(' ') << "CMT/PST"
                     << setw(10) << setfill(' ') << "SHR/PST"
                     << setw(10) << setfill(' ') << "NEW"
                     << endl
                     << "---------------------------------------------------------------------------"
                     << endl;

                for (int i = 0; i < 12; i++)
                {
                    cout << left
                         << setw(12) << setfill(' ') << lName[i]
                         << setw(6) << setfill(' ') << posts[i]
                         << setw(10) << setfill(' ') << viewspp[i]
                         << setw(10) << setfill(' ') << engagementspp[i]
                         << setw(10) << setfill(' ') << likespp[i]
                         << setw(10) << setfill(' ') << commentspp[i]
                         << setw(10) << setfill(' ') << sharespp[i]
                         << setw(10) << setfill(' ') << newMetric[i]
                         << endl;
                }

                dataOut << left
                        << setw(12) << setfill(' ') << "LAST"
                        << setw(6) << setfill(' ') << "PST"
                        << setw(10) << setfill(' ') << "VIW/PST"
                        << setw(10) << setfill(' ') << "ENG/PST"
                        << setw(10) << setfill(' ') << "LIK/PST"
                        << setw(10) << setfill(' ') << "CMT/PST"
                        << setw(10) << setfill(' ') << "SHR/PST"
                        << setw(10) << setfill(' ') << "NEW"
                        << endl
                        << "---------------------------------------------------------------------------"
                        << endl;

                for (int i = 0; i < 12; i++)
                {
                    dataOut << left
                            << setw(12) << setfill(' ') << lName[i]
                            << setw(6) << setfill(' ') << posts[i]
                            << setw(10) << setfill(' ') << viewspp[i]
                            << setw(10) << setfill(' ') << engagementspp[i]
                            << setw(10) << setfill(' ') << likespp[i]
                            << setw(10) << setfill(' ') << commentspp[i]
                            << setw(10) << setfill(' ') << sharespp[i]
                            << setw(10) << setfill(' ') << newMetric[i]
                            << endl;
                }

                cout << endl << "File social_media_sorted_stats.txt has been overwritten" << endl;
                break;

            case 4:
                numSort(commentspp, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, orderOption);

                for (int i = 0; i < 12; i++)
                {
                    newMetric[i] = ((float)likes[i] * (float)comments[i] * (float)shares[i]) / (float)posts[i];
                    viewspp[i] = (float)views[i] / (float)posts[i];
                    engagementspp[i] = (float)engagements[i] / (float)posts[i];
                    likespp[i] = (float)likes[i] / (float)posts[i];
                    commentspp[i] = (float)comments[i] / (float)posts[i];
                    sharespp[i] = (float)shares[i] / (float)posts[i];
                }

                cout << "Here are the results." << endl
                     << endl;

                cout << left
                     << setw(12) << setfill(' ') << "LAST"
                     << setw(6) << setfill(' ') << "PST"
                     << setw(10) << setfill(' ') << "VIW/PST"
                     << setw(10) << setfill(' ') << "ENG/PST"
                     << setw(10) << setfill(' ') << "LIK/PST"
                     << setw(10) << setfill(' ') << "CMT/PST"
                     << setw(10) << setfill(' ') << "SHR/PST"
                     << setw(10) << setfill(' ') << "NEW"
                     << endl
                     << "---------------------------------------------------------------------------"
                     << endl;

                for (int i = 0; i < 12; i++)
                {
                    cout << left
                         << setw(12) << setfill(' ') << lName[i]
                         << setw(6) << setfill(' ') << posts[i]
                         << setw(10) << setfill(' ') << viewspp[i]
                         << setw(10) << setfill(' ') << engagementspp[i]
                         << setw(10) << setfill(' ') << likespp[i]
                         << setw(10) << setfill(' ') << commentspp[i]
                         << setw(10) << setfill(' ') << sharespp[i]
                         << setw(10) << setfill(' ') << newMetric[i]
                         << endl;
                }

                dataOut << left
                        << setw(12) << setfill(' ') << "LAST"
                        << setw(6) << setfill(' ') << "PST"
                        << setw(10) << setfill(' ') << "VIW/PST"
                        << setw(10) << setfill(' ') << "ENG/PST"
                        << setw(10) << setfill(' ') << "LIK/PST"
                        << setw(10) << setfill(' ') << "CMT/PST"
                        << setw(10) << setfill(' ') << "SHR/PST"
                        << setw(10) << setfill(' ') << "NEW"
                        << endl
                        << "---------------------------------------------------------------------------"
                        << endl;

                for (int i = 0; i < 12; i++)
                {
                    dataOut << left
                            << setw(12) << setfill(' ') << lName[i]
                            << setw(6) << setfill(' ') << posts[i]
                            << setw(10) << setfill(' ') << viewspp[i]
                            << setw(10) << setfill(' ') << engagementspp[i]
                            << setw(10) << setfill(' ') << likespp[i]
                            << setw(10) << setfill(' ') << commentspp[i]
                            << setw(10) << setfill(' ') << sharespp[i]
                            << setw(10) << setfill(' ') << newMetric[i]
                            << endl;
                }

                cout << endl << "File social_media_sorted_stats.txt has been overwritten" << endl;
                break;

            case 5:
                numSort(sharespp, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, orderOption);

                for (int i = 0; i < 12; i++)
                {
                    newMetric[i] = ((float)likes[i] * (float)comments[i] * (float)shares[i]) / (float)posts[i];
                    viewspp[i] = (float)views[i] / (float)posts[i];
                    engagementspp[i] = (float)engagements[i] / (float)posts[i];
                    likespp[i] = (float)likes[i] / (float)posts[i];
                    commentspp[i] = (float)comments[i] / (float)posts[i];
                    sharespp[i] = (float)shares[i] / (float)posts[i];
                }

                cout << "Here are the results." << endl
                     << endl;

                cout << left
                     << setw(12) << setfill(' ') << "LAST"
                     << setw(6) << setfill(' ') << "PST"
                     << setw(10) << setfill(' ') << "VIW/PST"
                     << setw(10) << setfill(' ') << "ENG/PST"
                     << setw(10) << setfill(' ') << "LIK/PST"
                     << setw(10) << setfill(' ') << "CMT/PST"
                     << setw(10) << setfill(' ') << "SHR/PST"
                     << setw(10) << setfill(' ') << "NEW"
                     << endl
                     << "---------------------------------------------------------------------------"
                     << endl;

                for (int i = 0; i < 12; i++)
                {
                    cout << left
                         << setw(12) << setfill(' ') << lName[i]
                         << setw(6) << setfill(' ') << posts[i]
                         << setw(10) << setfill(' ') << viewspp[i]
                         << setw(10) << setfill(' ') << engagementspp[i]
                         << setw(10) << setfill(' ') << likespp[i]
                         << setw(10) << setfill(' ') << commentspp[i]
                         << setw(10) << setfill(' ') << sharespp[i]
                         << setw(10) << setfill(' ') << newMetric[i]
                         << endl;
                }

                dataOut << left
                        << setw(12) << setfill(' ') << "LAST"
                        << setw(6) << setfill(' ') << "PST"
                        << setw(10) << setfill(' ') << "VIW/PST"
                        << setw(10) << setfill(' ') << "ENG/PST"
                        << setw(10) << setfill(' ') << "LIK/PST"
                        << setw(10) << setfill(' ') << "CMT/PST"
                        << setw(10) << setfill(' ') << "SHR/PST"
                        << setw(10) << setfill(' ') << "NEW"
                        << endl
                        << "---------------------------------------------------------------------------"
                        << endl;

                for (int i = 0; i < 12; i++)
                {
                    dataOut << left
                            << setw(12) << setfill(' ') << lName[i]
                            << setw(6) << setfill(' ') << posts[i]
                            << setw(10) << setfill(' ') << viewspp[i]
                            << setw(10) << setfill(' ') << engagementspp[i]
                            << setw(10) << setfill(' ') << likespp[i]
                            << setw(10) << setfill(' ') << commentspp[i]
                            << setw(10) << setfill(' ') << sharespp[i]
                            << setw(10) << setfill(' ') << newMetric[i]
                            << endl;
                }

                cout << endl << "File social_media_sorted_stats.txt has been overwritten" << endl;
                break;

            case 6:
                numSort(newMetric, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, orderOption);

                for (int i = 0; i < 12; i++)
                {
                    newMetric[i] = ((float)likes[i] * (float)comments[i] * (float)shares[i]) / (float)posts[i];
                    viewspp[i] = (float)views[i] / (float)posts[i];
                    engagementspp[i] = (float)engagements[i] / (float)posts[i];
                    likespp[i] = (float)likes[i] / (float)posts[i];
                    commentspp[i] = (float)comments[i] / (float)posts[i];
                    sharespp[i] = (float)shares[i] / (float)posts[i];
                }

                cout << "Here are the results." << endl
                     << endl;

                cout << left
                     << setw(12) << setfill(' ') << "LAST"
                     << setw(6) << setfill(' ') << "PST"
                     << setw(10) << setfill(' ') << "VIW/PST"
                     << setw(10) << setfill(' ') << "ENG/PST"
                     << setw(10) << setfill(' ') << "LIK/PST"
                     << setw(10) << setfill(' ') << "CMT/PST"
                     << setw(10) << setfill(' ') << "SHR/PST"
                     << setw(10) << setfill(' ') << "NEW"
                     << endl
                     << "---------------------------------------------------------------------------"
                     << endl;

                for (int i = 0; i < 12; i++)
                {
                    cout << left
                         << setw(12) << setfill(' ') << lName[i]
                         << setw(6) << setfill(' ') << posts[i]
                         << setw(10) << setfill(' ') << viewspp[i]
                         << setw(10) << setfill(' ') << engagementspp[i]
                         << setw(10) << setfill(' ') << likespp[i]
                         << setw(10) << setfill(' ') << commentspp[i]
                         << setw(10) << setfill(' ') << sharespp[i]
                         << setw(10) << setfill(' ') << newMetric[i]
                         << endl;
                }

                dataOut << left
                        << setw(12) << setfill(' ') << "LAST"
                        << setw(6) << setfill(' ') << "PST"
                        << setw(10) << setfill(' ') << "VIW/PST"
                        << setw(10) << setfill(' ') << "ENG/PST"
                        << setw(10) << setfill(' ') << "LIK/PST"
                        << setw(10) << setfill(' ') << "CMT/PST"
                        << setw(10) << setfill(' ') << "SHR/PST"
                        << setw(10) << setfill(' ') << "NEW"
                        << endl
                        << "---------------------------------------------------------------------------"
                        << endl;

                for (int i = 0; i < 12; i++)
                {
                    dataOut << left
                            << setw(12) << setfill(' ') << lName[i]
                            << setw(6) << setfill(' ') << posts[i]
                            << setw(10) << setfill(' ') << viewspp[i]
                            << setw(10) << setfill(' ') << engagementspp[i]
                            << setw(10) << setfill(' ') << likespp[i]
                            << setw(10) << setfill(' ') << commentspp[i]
                            << setw(10) << setfill(' ') << sharespp[i]
                            << setw(10) << setfill(' ') << newMetric[i]
                            << endl;
                }

                cout << endl << "File social_media_sorted_stats.txt has been overwritten" << endl;
                break;

            default:
                cout << "Returning to the main menu...";
                menubool = 0;
                break;
            }
        }

        dataOut.close();

        return 0;
    }

    int genderStatistics(string sex[12], int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12])
    {
        //Declare and initialize local varibles
        int mXtraFollowers(0), mPosts(0), mViews(0), mEngagements(0), mLikes(0), mComments(0), mShares(0), mApplicants(0),
            fXtraFollowers(0), fPosts(0), fViews(0), fEngagements(0), fLikes(0), fComments(0), fShares(0), fApplicants(0);

        //Calculate statistics per gender
        for (int i = 0; i < 12; i++){
            if(sex[i] == "M"){
                mXtraFollowers += xtraFollowers[i];
                mPosts += posts[i];
                mViews += views[i];
                mEngagements += engagements[i];
                mLikes += likes[i];
                mComments += comments[i];
                mShares += shares[i];
                mApplicants++;
            }
            else if(sex[i] == "F"){
                fXtraFollowers += xtraFollowers[i];
                fPosts += posts[i];
                fViews += views[i];
                fEngagements += engagements[i];
                fLikes += likes[i];
                fComments += comments[i];
                fShares += shares[i];
                fApplicants++;
            }
            else{
                cout << "Non-specified value.";
            }
        }

        //Display the results.
        cout << "Here are the results. Note: APP stands for 'APPLICANTS'." << endl
             << endl;

        cout << left
             << setw(12) << setfill(' ') << "MEN:" << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "FOL:"
             << setw(10) << setfill(' ') << mXtraFollowers << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "PST:"
             << setw(10) << setfill(' ') << mPosts << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "VIW:"
             << setw(10) << setfill(' ') << mViews << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "ENG:"
             << setw(10) << setfill(' ') << mEngagements << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "LIK:"
             << setw(10) << setfill(' ') << mLikes << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "CMT:"
             << setw(10) << setfill(' ') << mComments << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "SHR:"
             << setw(10) << setfill(' ') << mShares << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "APP:"
             << setw(10) << setfill(' ') << mApplicants << endl
             << "---------------------------------------------"
             << endl;

        cout << left
             << setw(12) << setfill(' ') << "WOMEN:" << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "FOL:"
             << setw(10) << setfill(' ') << fXtraFollowers << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "PST:"
             << setw(10) << setfill(' ') << fPosts << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "VIW:"
             << setw(10) << setfill(' ') << fViews << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "ENG:"
             << setw(10) << setfill(' ') << fEngagements << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "LIK:"
             << setw(10) << setfill(' ') << fLikes << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "CMT:"
             << setw(10) << setfill(' ') << fComments << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "SHR:"
             << setw(10) << setfill(' ') << fShares << endl
             << setw(6) << setfill(' ') << "    "
             << setw(10) << setfill(' ') << "APP:"
             << setw(10) << setfill(' ') << fApplicants << endl
             << "---------------------------------------------"
             << endl;

        return 0;
    }

    int finalScore(string fName[12], string lName[12], string origin[12], string sex[12],
                  int xtraFollowers[12], int posts[12], int views[12], int engagements[12], int likes[12], int comments[12], int shares[12])
    {
        //Declare and initialize local varibles
        float score[12] = {0};
        ofstream scoreOut;

        //Populate the score array
        for (int i = 0; i < 12; i++)
        {
            score[i] = nearbyint((views[i] * 0.5 + engagements[i] * 0.6 + likes[i] * 0.7+ xtraFollowers[i] * 1.5  + comments[i] * 3 + shares[i] * 4) / posts[i]);
        }

        //Sort on score
        numSort(score, fName, lName, origin, sex, xtraFollowers, posts, views, engagements, likes, comments, shares, 0);

        cout << "Here is an overview of the scoring proccess." << endl << endl;
        cout << "The most basic form of interaction and so every view is worth 0.5 points." << endl;
        cout << "Next, engagements prove that the post attracted the viewer's attention briefly and so they are worth a bit more at 0.6 points." << endl;
        cout << "Likes show that the user enjoyed the content of the post, however they are still 'low effort' interactions so they are worth 0.7 points." << endl;
        cout << "Following is also a low effort interaction, however it opens the door to further and consistent interaction between the user and future posts. 1.5 points." << endl;
        cout << "Comments are the life-line of any post, sparking convertation and often heated debates that massively boost the relevancy of the post in large time spans" << endl;
        cout << "Shares are the most 'high effort' form of interaction, and most often shows the willingess of users to gather attraction to the post." << endl;
        cout << "Furthermore, it is the rarest form of interaction with some applicants not managing to gain a single share. Thus they are worth the most at 4 points." << endl;
        cout << "Finally, we divide the sum of the points with the number of posts, since we are more interested in per post performance than the sheer ammount of interactions" 
                << endl << endl;

        cout << "Here are the results. The data have also been saved in 'social_media_contest_final_score.txt'" << endl
             << endl;

        //Save the results in the file
        scoreOut.open("social_media_contest_final_score.txt");

        scoreOut << left
                     << setw(10) << setfill(' ') << "FIRST"
                     << setw(10) << setfill(' ') << "LAST"
                     << setw(8) << setfill(' ') << "ORG"
                     << setw(8) << setfill(' ') << "SEX"
                     << setw(8) << setfill(' ') << "FOL"
                     << setw(8) << setfill(' ') << "PST"
                     << setw(8) << setfill(' ') << "VIW"
                     << setw(8) << setfill(' ') << "ENG"
                     << setw(8) << setfill(' ') << "LIK"
                     << setw(8) << setfill(' ') << "CMT"
                     << setw(8) << setfill(' ') << "SHR"
                     << setw(8) << setfill(' ') << "SCORE"
                     << endl
                     << "-------------------------------------------------------------------------------------------------"
                     << endl;

        for (int i = 0; i < 12; i++)
        {
            scoreOut << left
                         << setw(10) << setfill(' ') << fName[i]
                         << setw(10) << setfill(' ') << lName[i]
                         << setw(8) << setfill(' ') << origin[i]
                         << setw(8) << setfill(' ') << sex[i]
                         << setw(8) << setfill(' ') << xtraFollowers[i]
                         << setw(8) << setfill(' ') << posts[i]
                         << setw(8) << setfill(' ') << views[i]
                         << setw(8) << setfill(' ') << engagements[i]
                         << setw(8) << setfill(' ') << likes[i]
                         << setw(8) << setfill(' ') << comments[i]
                         << setw(8) << setfill(' ') << shares[i]
                         << setw(8) << setfill(' ') << score[i]
                         << endl;
        }

        scoreOut.close();

        cout << left
                 << setw(10) << setfill(' ') << "FIRST"
                 << setw(10) << setfill(' ') << "LAST"
                 << setw(8) << setfill(' ') << "ORG"
                 << setw(8) << setfill(' ') << "SEX"
                 << setw(8) << setfill(' ') << "FOL"
                 << setw(8) << setfill(' ') << "PST"
                 << setw(8) << setfill(' ') << "VIW"
                 << setw(8) << setfill(' ') << "ENG"
                 << setw(8) << setfill(' ') << "LIK"
                 << setw(8) << setfill(' ') << "CMT"
                 << setw(8) << setfill(' ') << "SHR"
                 << setw(8) << setfill(' ') << "SCORE"
                 << endl
                 << "-------------------------------------------------------------------------------------------------"
                 << endl;

        for (int i = 0; i < 12; i++)
        {
            cout << left
                     << setw(10) << setfill(' ') << fName[i]
                     << setw(10) << setfill(' ') << lName[i]
                     << setw(8) << setfill(' ') << origin[i]
                     << setw(8) << setfill(' ') << sex[i]
                     << setw(8) << setfill(' ') << xtraFollowers[i]
                     << setw(8) << setfill(' ') << posts[i]
                     << setw(8) << setfill(' ') << views[i]
                     << setw(8) << setfill(' ') << engagements[i]
                     << setw(8) << setfill(' ') << likes[i]
                     << setw(8) << setfill(' ') << comments[i]
                     << setw(8) << setfill(' ') << shares[i]
                     << setw(8) << setfill(' ') << score[i]
                     << endl;
        }

        return 0;
    }