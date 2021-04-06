#include "ActionUnit.h"

// default constructor: assigns id = -1, numFrames = 0, and initializes activeVals to an array of length 0 (unused)
ActionUnit::ActionUnit() {
    this->id = -1;
    this->numFrames = 0;
    this->activeVals = new bool[0];
}

// overloaded constructor: assigns id and numFrames, and initializes activeVals to an empty array of length numFrames
ActionUnit::ActionUnit(int id, int numFrames) {
    this->id = id;
    this->numFrames = numFrames;
    this->activeVals = new bool[numFrames];
}

// overloaded constructor: assigns id and numFrames, initializes activeVals to an empty array of length numFrames and fills it with vals
ActionUnit::ActionUnit(int id, int numFrames, bool* vals) {
    this->id = id;
    this->numFrames = numFrames;
    this->activeVals = new bool[numFrames];
    setActiveVals(vals);
}

// destructor: delete activeVals
ActionUnit::~ActionUnit() {
    delete[] activeVals;
}


// assigns activeVals
void ActionUnit::setActiveVals(bool* vals) {
    /* TODO: implement error checking for vals size != numFrames */
    for(int i = 0; i < numFrames; ++i) {
        activeVals[i] = vals[i];
    }
}

// prints ActionUnit stats
void ActionUnit::print() {
    cout << "|------- Action Unit: " << id << " -------|" << endl;
    cout << "Number of frames: " << numFrames << endl;
    cout << "\nActive Values" << endl;
    for(int i = 0; i < numFrames; ++i) {
        if(i % 16 == 0)
            cout << endl;
        cout << activeVals[i] << " ";
    }
    cout << endl << "--------------------------------" << endl;
}

// returns ID
int ActionUnit::getID() {
    return id;
}

// returns numFrames
int ActionUnit::getNumFrames() {
    return numFrames;
}
