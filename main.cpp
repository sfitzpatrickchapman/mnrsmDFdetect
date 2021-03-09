#include "ActionUnit.h"
#include "Profile.h"
#include <stdlib.h> /* srand, rand */

using namespace std;

// assigns boolean values from file to vals
static void assignValsFromFile(bool* vals, int valsSize, int id /* , string fileName */ ) {
    /* TODO: add file reading here */
    // current implementation is for testing purposes ONLY and is NOT final
    for(int i = 0; i < valsSize; ++i) {
        vals[i] = rand() % 2; // generate random val
        cout << "vals[" << i << "] = " << vals[i] << endl;
    }
}

/*------------------------------- MAIN METHOD -------------------------------*/

int main(int argc, char **argv) {

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

    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        delete aulist[i];
    }
    delete[] aulist;
    delete vals;
    delete p1;

    return 0;
}
