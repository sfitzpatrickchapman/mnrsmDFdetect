#include "ActionUnit.h"
#include "Profile.h"
#include <iostream>
#include <fstream>

using namespace std;

const string PATH = "proc/";

// assigns boolean values from file to vals
static void fillAUList(ActionUnit** auList, int auListSize, string fileName) {

    ifstream file;
    file.open(fileName);

    // get numFrames
    string currLine;
    getline(file, currLine);
    int numFrames = stoi(currLine);

    // initialize vals
    bool** vals = new bool*[auListSize];
    for(int i = 0; i < auListSize; ++i) {
        vals[i] = new bool[numFrames];
    }

    // read data from file into vals
    for(int i = 0; i < numFrames; ++i) {
        getline(file, currLine);
        for(int j = 0; j < auListSize; ++j) {
            vals[j][i] = (currLine[j] == '1');
        }
    }

    // fill au list
    for(int i = 0; i < auListSize; ++i) {
        auList[i] = new ActionUnit(i, numFrames, vals[i]);
    }
}

// returns first line of processedFile, which is the number of frames
static int getNumFrames(string fileName) {
    string currLine;
    ifstream file;
    file.open(fileName);
    getline(file, currLine);
    return stoi(currLine);
}

// prompts/inputs fileName, checks if valid, and returns fileName
static string getInputFileName() {
    string fileName;

    /* Prompt and input */
    cout << "Please enter the processed file path (should end in _proc.txt): ";
    cin >> fileName;
    fileName = PATH + fileName;

    /* Create file var and attempt to open */
    ifstream file;
    file.open(fileName);

    /* If file cannot be opened, loop until it does or quit */
    while (!file.is_open()) {
        cout << "ERROR: Invalid file path! Please try again." << endl;
        cout << "Enter new file path or 'q' to quit: ";
        cin >> fileName;

        if (fileName == "q")
            exit(1);
        else
            file.open(fileName);
    }
    file.close();

    return fileName;
}

////////////////////////////////////////////////////////////////////////////////
// USER METHODS

static void viewExistingProfiles() {
    /*
    display profiles list
    OPTION: select profile OR main menu
    if select profile, get existing name from user
    display profile data
    OPTION: select different profile OR upload file OR delete profile OR main menu
        if select different profile, go back up ^
        if upload file, call getExistingFile
        if delete profile, delete and save to database
    */
}

static void createNewProfile() {
    /*
    get new name from user
    OPTION: upload new file? Yes OR No
        if yes: call getExistingFile
        if no: return to main menu
    */
}

static void uploadFile() {
    /*
    OPTION: existing profile? Yes OR No
        if yes: getExistingName, getExistingFile, processFile, save to database
        if no: createNewProfile() (with option to automatically say yes to upload file)
    */
}

static void compareProfiles(/*TEMPORARY PARAMETERS!*/ Profile* p1, Profile* p2) {
    /*
    get existing name 1
    get existing name 2
    compare profiles
    OPTION: compare another? Yes OR No
        if yes: repeat loop
        if no: return to main menu
    */
    cout << "\n\n----------------------------------------" << endl;
    cout << "Comparing " << p1->name << " to " << p2->name << ":" << endl;
    float comparisonVal = p1->compareTo(*p2) * 100;
    cout << "Profiles are %" << comparisonVal << " similar." << endl;
    cout << "----------------------------------------\n" << endl;
}

static void saveAndQuit() {

}

/*----------------------------------- MAIN -----------------------------------*/

int main(int argc, char **argv) {

    int numFrames = 0;
    const int NUM_ACTION_UNITS = 18; // constant number of action units

    Profile *p1 = new Profile("AOC");

    string input = "";
    cout << "-------------------- DeepFake Detection Program --------------------\n\n" << endl;
    cout << "Input new file for AOC? \'Y\' or \'N\'" << endl;
    cin >> input;

    while(input == "Y") {
        string processedFileName = getInputFileName();
        numFrames = getNumFrames(processedFileName); // to be determined from CSV file
        p1->currNumFrames = numFrames;
        ActionUnit** auList = new ActionUnit*[NUM_ACTION_UNITS];
        fillAUList(auList, NUM_ACTION_UNITS, processedFileName);

        p1->calcProbMatrix(auList);
        p1->print();
        cout << "Add matrix to average? \'Y\' or \'N\'" << endl;
        cin >> input;
        if(input == "Y") {
            p1->updateAvgMatrix();
            p1->print();
        }

        // clean-up
        for(int i = 0; i < NUM_ACTION_UNITS; ++i)
            delete auList[i];
        delete[] auList;

        // prompt user again
        cout << "-------------------- DeepFake Detection Program --------------------\n\n" << endl;
        cout << "Input new file for AOC? \'Y\' or \'N\'" << endl;
        cin >> input;
    }

    cout << "Final profile:" << endl;
    p1->print();

    cout << "\n\n\nProgram finished." << endl;


    /* --------- CLEAN UP --------- */

    delete p1;

    return 0;
}
