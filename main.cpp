/*********
 * Program 4: Restaurant Inspections
 * Code uses classes to analyze and present real-world data about inspections
 * of restaurants (and bars and similar entities)
 * in certain neighborhoods in Chicago

 * The user has a choice of four options:
 * 1) Display Overall Inspection Information
 * 2) Display risk percentages
 * 3) Display passing numbers by neighborhood
 * 4) Search for restaurant by name
 * The user can press 5 to quit the program.

 * Class: CS 141, Fall 2023
 * System: CLion IDE *
 * @author Antwon Walls
 * @version October 15, 2023
 * *******/

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class Restaurant {
public:
    ///Declares Accessors (getters) for the private data members
    string getName() { return name; }
    string getAddress() { return address; }
    string getInspectionDate() { return inspectionDate; }
    char getRisk() { return risk; }
    string getPassOrFail() { return passOrFail; }
    string getNeighborhood() { return neighborhood; }

    ///Declares Mutators (setters) for the data members
    void setName(string restaurantName);
    void setAddress(string resAddress);
    void setInspectionDate(string resInspectionDate);
    void setRisk(char restaurantRisk);
    void setPassOrFail(string resPassOrFail);
    void setNeighborhood(string resNeighborhood);

private:
    string name;
    string address;
    string inspectionDate;
    char risk;
    string passOrFail;
    string neighborhood;
};

class Date {
public:
    ///Default constructor for the date
    Date() { month = 01; day = 01; year = 2000; }

    /**Creates and defines a parameterized constructor
     * that lets the user set the month, day, and year**/
    Date(int month, int day, int year) {
        this->month = month;
        this->day = day;
        this->year = year;
    }

    ///declares public Date functions
    bool isGreater(Date date);
    string getMonth();
    string getDay();

    int getYear() { return year; }
private:
    int day;
    int month;
    int year;
};

///defines getter for the date's month
string Date::getMonth() {
    /**puts it in MM format instead of the singular M. e.g. 08-25-2023**/
    if (month < 10) {
        return "0" + to_string(month);
    } else {
        return to_string(month);
    }
}

///defines getter for the date's day
string Date::getDay() {
    /**puts it in DD format instead of the singular D. e.g. 12-08-2023**/
    if (day < 10) {
        return "0" + to_string(day);
    } else {
        return to_string(day);
    }
}

///Defines isGreater function
bool Date::isGreater(Date date) {
    /**If the year of the inspection date for this restaurant
     * is greater than that of input date**/
    if (this->year > date.year) {
        return true;
    }
    /**If the inspection date year is the same for both restaurants
     * but the month of one restaurant is greater than that of the other**/
    else if (this->year == date.year && this->month > date.month) {
        return true;
    }
    /**If both restaurants have the same year and month for the inspection date
     * but the day of one restaurant is greater than that of the other**/
    else if (this->year == date.year && this->month == date.month && this->day > date.day) {
        return true;
    }
    else {
        return false;
    }
}


///Defines Mutator for the name
void Restaurant::setName(string restaurantName) {
    name = restaurantName;
}
///Defines Mutator for the address
void Restaurant::setAddress(string resAddress) {
    address = resAddress;
}
///Defines Mutator for the inspection date
void Restaurant::setInspectionDate(string resInspectionDate) {
    inspectionDate = resInspectionDate;
}

///Defines Mutator for the risk
void Restaurant::setRisk(char restaurantRisk) {
    risk = restaurantRisk;
}

///Defines Mutator for pass or fail
void Restaurant::setPassOrFail(string resPassOrFail) {
    passOrFail = resPassOrFail;
}

///Defines Mutator for the neighborhood
void Restaurant::setNeighborhood(string resNeighborhood) {
    neighborhood = resNeighborhood;
}

void menuOption1(vector<Restaurant> listOfRestaurants) {
    int restaurantCounter = 0;
    int passCounter = 0;
    ///Loop that goes through the number of restaurants
    for (int i = 0; i < listOfRestaurants.size(); i++) {
        restaurantCounter++;
    }
    ///Loop that goes through the number inspections that Passed
    for (int i = 0; i < listOfRestaurants.size(); i++) {
        if (listOfRestaurants.at(i).getPassOrFail() == "Pass" || listOfRestaurants.at(i).getPassOrFail() == "Conditional") {
            passCounter++;
        }
    }
    cout << "Number of restaurants: " << restaurantCounter << endl
         << "Number that pass: " << passCounter << endl;

    /**Second part of menu option 1 displays the most recent passing inspection**/
    /**Creates the month, day, and year portions of an
     * inspection date in the list of restaurants**/
    int month;
    int day;
    int year;
    string restaurantNameOfMaxDate;

    /**creates a maxDate object to provide the latest date of passing inspection
     * Because no parameters are given, the default constructor is automatically
     * called.**/
    Date maxDate;
    for (int i = 0; i < listOfRestaurants.size(); i++) {
        if (listOfRestaurants.at(i).getPassOrFail() == "Pass" || listOfRestaurants.at(i).getPassOrFail() == "Conditional") {
            ///Splits up the month, day, and year portions of each passing or conditional passing restaurant
            month = stoi(listOfRestaurants.at(i).getInspectionDate().substr(0, 2));
            day = stoi(listOfRestaurants.at(i).getInspectionDate().substr(3, 2));
            year = stoi(listOfRestaurants.at(i).getInspectionDate().substr(6, 4));
        }
        /**Creates another date object (d2) and (gives inputs) specifies the object
         * with its respected month, day, and year
         * for each passing or conditional passing restaurant
         * Hence, the default constructor not being called for this one.**/
        Date d2(month, day, year);

        /**Calls the isGreater function for each passing or conditional inspection date
         * and compares each date to to the maxDate. If d2 has a more recent date than
         * maxDate, then that date becomes the new maxDate.**/
        if (d2.isGreater(maxDate)) {
            maxDate = d2;
            restaurantNameOfMaxDate = listOfRestaurants.at(i).getName();
        }
    }

    cout << "Most recent passing inspection was of " << restaurantNameOfMaxDate << " on "
    << maxDate.getMonth() << "-" << maxDate.getDay() << "-" << maxDate.getYear();
}

///percentage risk calculation for menu option 2
double percentageRiskCalculation(vector<Restaurant> listOfRestaurants, double riskCounter) {
    /**The *100 converts the calculation to a double and the percentage format.
     * I divided them by listOfRestaurants.size() because each restaurant contains some risk
     * (H, M, or L), so it would be unnecessary to do highRiskCounter + mediumRiskCounter + lowRiskCounter
     * each time.**/
    double percentageRisk = 100.0 * (riskCounter / listOfRestaurants.size());
    return percentageRisk;
}
void menuOption2(vector<Restaurant> listOfRestaurants) {
    double highRiskCounter = 0;
    double mediumRiskCounter = 0;
    double lowRiskCounter = 0;

    /**Loops through all of the restaurants and gets the risk for each one,
     * then adds to the risk counter depending on the type of risk**/
    for (int i = 0; i < listOfRestaurants.size(); i++) {
        listOfRestaurants.at(i).getRisk();
        if (listOfRestaurants.at(i).getRisk() == 'H') {
            highRiskCounter++;
        }
        if (listOfRestaurants.at(i).getRisk() == 'M') {
            mediumRiskCounter++;
        }
        if (listOfRestaurants.at(i).getRisk() == 'L') {
            lowRiskCounter++;
        }
    }

    cout << "High risk: " << fixed << setprecision(1);
    cout << percentageRiskCalculation(listOfRestaurants, highRiskCounter) << "%" << endl;

    cout << "Medium risk: " << fixed << setprecision(1);
    cout << percentageRiskCalculation(listOfRestaurants, mediumRiskCounter) << "%" << endl;

    cout << "Low risk: " << fixed << setprecision(1);
    cout << percentageRiskCalculation(listOfRestaurants, lowRiskCounter) << "%" << endl;

}

void menuOption3(vector<Restaurant> listOfRestaurants) {
    /**For each condition type, creates a map of the neighborhoods. Stores the neighborhood
     * and the number of restaurants in that neighborhood attributed to its state of passing
     * (pass, conditional pass, failed)**/
    map<string, int> passNeighborHoodsMap;
    map<string, int> condNeighborHoodsMap;
    map<string, int> failedNeighborHoodsMap;

    ///Sets up the display
    cout << "Neighborhood" << setw(22) << "Passed ";
    cout << "Cond. Pass" << setw(11) << "Failed"
         << endl << "============" << setw(22) << "====== " << "=========="
         << setw(11) << "======" << endl;

    /**For each condition (pass, conditional, failed),
     * First, initializes every neighborhood to 0 count**/
    for (int i = 0; i < listOfRestaurants.size(); i++) {
        string neighborhoodName = listOfRestaurants.at(i).getNeighborhood();
        passNeighborHoodsMap[neighborhoodName] = 0;
        condNeighborHoodsMap[neighborhoodName] = 0;
        failedNeighborHoodsMap[neighborhoodName] = 0;
    }

    /**Then, populates the count of every restaurant's
     * neighborhood by condition**/
    for (int i = 0; i < listOfRestaurants.size(); i++) {
        string neighborhoodName = listOfRestaurants.at(i).getNeighborhood();
        string passStatus = listOfRestaurants.at(i).getPassOrFail();
        if (passStatus == "Pass") {
            passNeighborHoodsMap[neighborhoodName]++;
        }
        if (passStatus == "Conditional") {
            condNeighborHoodsMap[neighborhoodName]++;
        }
        if (passStatus == "Fail") {
            failedNeighborHoodsMap[neighborhoodName]++;
        }
    }
     /**For each condition, returns an iterator to the first element
      * in the map**/
    map<string, int>::iterator pass = passNeighborHoodsMap.begin();
    map<string, int>::iterator condPass = condNeighborHoodsMap.begin();
    map<string, int>::iterator failed = failedNeighborHoodsMap.begin();
    int width = 33;
    /**Iterates through the map and sets the appropriate spaces
     * before printing the neighborhood (pass->first) and then prints out
     * the count of every neighborhood's respective condition
     * (# of passed, # of conditional, # of failed),
     * as long as the map hasn't reached its end yet**/
    while(pass != passNeighborHoodsMap.end()) {
        int wordLength = pass->first.length();
        int spaces = width - wordLength;
        cout << pass->first << setw(spaces) << pass->second << setw(11);
        cout << condPass->second << setw(11);
        cout << failed->second << endl;
        pass++;
        condPass++;
        failed++;
    }
}

void menuOption4(vector<Restaurant> listOfRestaurants) {
    string userInput;
    cout << "Enter restaurant to search for: ";
    cin >> userInput;
    /**All of the restaurants are upper-case, so the user's input needs to match
     * this format to properly search**/
    for(int i = 0; i < userInput.length(); i++){
        userInput.at(i) = toupper(userInput.at(i));
    }

    /**Loop that searches for the restaurant the user inputs.
     * If a match is found, displays some attributes of that restaurant**/
    for (int i = 0; i < listOfRestaurants.size(); i++) {
        string restaurantName = listOfRestaurants.at(i).getName();
        if (restaurantName.find(userInput) != string::npos) {
            cout << "Restaurant: " << listOfRestaurants.at(i).getName() << endl
                 << "Address: " << listOfRestaurants.at(i).getAddress() << endl
                 << "Inspection Date: " << listOfRestaurants.at(i).getInspectionDate() << endl
                 << "Inspection Result: " << listOfRestaurants.at(i).getPassOrFail() << endl << endl;
        }
    }
}

int main() {
    string filename;

    ///variable for each line (row) in the file
    string line;
    string dataMember;

    /**Creates a list of restaurants that contains all
     * the attributes of a restaurant, hence the type Restaurant **/
    vector<Restaurant> listOfRestaurants;

    /**contains each line of (1) name, (2) address, (3) date of inspection,
     * (4) risk, (5) whether the restaurant passed inspection, and
     * (6) neighborhood**/
    vector<string> row;

    cout << "Enter the data file to use: ";
    cin >> filename;
    ifstream infile(filename);
    if (infile.is_open()) {
        ///first while loop reads in each line
        while (getline(infile,line)) {
            stringstream str(line);
            /**reads in each specific data member (column) for that given line
             * separated by column, and populates the row vector with it, for each row of
             * restaurants**/
            while (getline(str, dataMember, ',')) {
                row.push_back(dataMember);
            }

            /**After reading in each data member and populating it in each row,
             * Creates a restaurant object and
             * sets the specification for the data member in each column.
             * These specifications apply to each row (line), hence it being inside the
             * getline() while loop.
             * Each row is its own restaurant object**/
            Restaurant newRestaurant;
            newRestaurant.setName(row.at(0));
            newRestaurant.setAddress(row.at(1));
            newRestaurant.setInspectionDate(row.at(2));
            /**For setRisk, I had to do row.at(3).at(0) here because row.at(3)
             * by itself is just a string with a size of 1.
             * For a string size of 1, there can only be one index, index 0.
             * So the risk is actually at index 0 of the string at row.at(3)**/
            newRestaurant.setRisk(row.at(3).at(0));
            newRestaurant.setPassOrFail(row.at(4));
            newRestaurant.setNeighborhood(row.at(5));

            /**Populates the LIST of restaurants with a restaurant object for
             * each line being read in**/
            listOfRestaurants.push_back(newRestaurant);
            row.clear();
        }
    }

    cout << "Select a menu option:" << endl;
    cout << "   1. Display overall inspection information" << endl;
    cout << "   2. Display risk percentages" << endl;
    cout << "   3. Display passing numbers by neighborhood" << endl;
    cout << "   4. Search for restaurant by name" << endl;
    cout << "   5. Exit" << endl;
    cout << "Your choice: " << endl;

    int menuOption;
    cin >> menuOption;

    if (menuOption == 1) {
        ///Displays overall inspection information
        menuOption1(listOfRestaurants);
    } else if (menuOption == 2) {
        ///Displays risk portfolio of the restaurants
        menuOption2(listOfRestaurants);
    } else if (menuOption == 3) {
        ///Displays passing, conditional pass, and failed numbers by neighborhood
        menuOption3(listOfRestaurants);
    } else if (menuOption == 4) {
        ///Lets the user search for a restaurant by name
        menuOption4(listOfRestaurants);
    } else if (menuOption == 5) {
        ///Lets the user quit the program
        exit(0);
    }

    return 0;
}
