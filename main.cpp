#include "ActionUnit.h"
#include "Profile.h"
#include <stdlib.h> /* srand, rand */
#include <iostream>
#include <fstream>

using namespace std;

/* SCOTT'S CODE */

// assigns boolean values from file to vals
static void assignValsFromFile(bool* vals, int valsSize, int id /* , string fileName */ ) {
    /* TODO: add file reading here */
    // current implementation is for testing purposes ONLY and is NOT final
    for(int i = 0; i < valsSize; ++i) {
        vals[i] = rand() % 2; // generate random val
        cout << "vals[" << i << "] = " << vals[i] << endl;
    }
}

// prompts/inputs fileName, checks if valid, and returns csv file pointer
static ifstream* inputFile() {
    string fileName;

    /* Prompt and input */
    cout << "Please enter the file path (with .csv): ";
    cin >> fileName;

    /* Create file var and attempt to open */
    ifstream* file = new ifstream(fileName, ifstream::in);
    file->open(fileName);

    /* If file cannot be opened, loop until it does or quit */
    while (!file->is_open()) {
        cout << "ERROR: Invalid file path! Please try again." << endl;
        cout << "Enter new file path or 'q' to quit: ";
        cin >> fileName;

        if (fileName == "q")
            exit(1);
        else
            file->open(fileName);
    }

    return file;
}

/*------------------------------- MAIN METHOD -------------------------------*/

int main(int argc, char **argv) {
    //file stuff
    ifstream* testFile = inputFile();
    cout << testFile << endl;

    const int NUM_FRAMES = 16; // to be determined from CSV file
    const int NUM_ACTION_UNITS = 18;

    ActionUnit** aulist = new ActionUnit*[NUM_ACTION_UNITS];
    bool* vals;
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        vals = new bool[NUM_FRAMES];
        assignValsFromFile(vals, NUM_FRAMES, i /* , fileName */);
        aulist[i] = new ActionUnit(i, NUM_FRAMES, vals);
        vals = NULL;
    }

    Profile *p1 = new Profile("Donald Trump");
    p1->currNumFrames = NUM_FRAMES; // manually setting currNumFrames, will be read from file later
    p1->print();
    cout << "Calculating Probability Matrix..." << endl;
    p1->calcProbMatrix(aulist);
    p1->print();
    cout << "Updating Average Matrix..." << endl;
    p1->updateAvgMatrix();
    p1->print();

    /* --------- CLEAN UP --------- */

    delete testFile;
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        delete aulist[i];
    }
    delete[] aulist;
    delete vals;
    delete p1;

    return 0;
}
