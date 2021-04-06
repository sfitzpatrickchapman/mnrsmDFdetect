#include "ActionUnit.h"
#include "Profile.h"
#include <iostream>
#include <fstream>

using namespace std;

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
    cout << "Please enter the processed file path (should end in _PROCESSED.txt): ";
    cin >> fileName;

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

/*------------------------------- MAIN METHOD -------------------------------*/

int main(int argc, char **argv) {

    string processedFileName = getInputFileName();

    const int NUM_FRAMES = getNumFrames(processedFileName); // to be determined from CSV file
    const int NUM_ACTION_UNITS = 18; // constant number of action units

    ActionUnit** auList = new ActionUnit*[NUM_ACTION_UNITS];
    fillAUList(auList, NUM_ACTION_UNITS, processedFileName);

    Profile *p1 = new Profile("Donald Trump", NUM_FRAMES);
    p1->calcProbMatrix(auList);
    p1->updateAvgMatrix();
    p1->print();

    /* --------- CLEAN UP --------- */

    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        delete auList[i];
    }
    delete[] auList;
    delete p1;

    return 0;
}
