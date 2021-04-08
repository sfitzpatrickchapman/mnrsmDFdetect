#include "Profile.h"

// default constructor: name = “”, probMatrix & avgMatrix is 2D ptr array initialized to length NUM_ACTION_UNITS, currNumFrames & totNumFrames & totNumVideos = 0 (unused)
Profile::Profile() {
    this->name = "";
    initializeEmptyMatrices();
    this->currNumFrames = 0;
    this->totNumFrames = 0;
    this->totNumVideos = 0;
}

// overloaded constructor: same as default but assigns the name (used when creating a new profile)
Profile::Profile(string name, int currNumFrames) {
    this->name = name;
    initializeEmptyMatrices();
    this->currNumFrames = currNumFrames;
    this->totNumFrames = 0;
    this->totNumVideos = 0;
}

// overloaded constructor: string of Profile info loaded from save file
Profile::Profile(string* saveData) {
    /* TODO: Implement saveData creating and reading methods */
    this->name = "";
    initializeEmptyMatrices();
    this->currNumFrames = 0;
    this->totNumFrames = 0;
    this->totNumVideos = 0;
}

// destructor: delete probMatrix and avgMatrix
Profile::~Profile() {
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        delete[] probMatrix[i];
        delete[] avgMatrix[i];
    }
    delete[] probMatrix;
    delete[] avgMatrix;
}


// takes in ptr to array of ptrs to action units, fills probMatrix with float values determined from action units
void Profile::calcProbMatrix(ActionUnit** au) {

    ActionUnit* au1; // ActionUnit comparison 1 ptr
    ActionUnit* au2; // ActionUnit comparison 2 ptr
    const int numFrames = au[0]->getNumFrames();
    int sum;
    float avg;

    // iterates over upper diagonal of matrix, excluding main diagonal
    for(int i = 0; i < NUM_ACTION_UNITS-1; ++i) {
        au1 = au[i];
        for(int j = i+1; j < NUM_ACTION_UNITS; ++j) {
            au2 = au[j];
            sum = 0;
            // iterate through currAU's activeVals and add up all equalities
            for(int k = 0; k < numFrames; ++k) {
                sum += ( au1->activeVals[k] == au2->activeVals[k] );
            }
            // calculate average number of equalities
            avg = (float) sum / (float) numFrames;
            // set corresponding matrix entry to calculated avg
            probMatrix[i][j] = avg;
        }
    }
}

// updates avgMatrix with new probMatrix values
void Profile::updateAvgMatrix() {
    // if profile has no previous data
    if(totNumVideos == 0) {
        // set avgMatrix equal to probMatrix
        for(int i = 0; i < NUM_ACTION_UNITS-1; ++i) {
            for(int j = i+1; j < NUM_ACTION_UNITS; ++j) {
                avgMatrix[i][j] = probMatrix[i][j];
            }
        }
    } else {
        // calculate new average for each matrix element
        for(int i = 0; i < NUM_ACTION_UNITS-1; ++i) {
            for(int j = i+1; j < NUM_ACTION_UNITS; ++j) {
                avgMatrix[i][j] = ((float) totNumFrames * avgMatrix[i][j] + probMatrix[i][j]) / (float)(totNumFrames + currNumFrames);
            }
        }
    }
    // update stats
    totNumFrames += currNumFrames;
    totNumVideos++;
}

 // compare two profiles' average matrices, returns similarity value
float Profile::compareTo(const Profile& other) {
    float simValue = 0;
    int comparisonCount = 0;
    for(int i = 0; i < NUM_ACTION_UNITS-1; ++i) {
        for(int j = i+1; j < NUM_ACTION_UNITS; ++j) {
            float diff = avgMatrix[i][j] - other.avgMatrix[i][j];
            simValue += 1 - abs(diff);
            comparisonCount++;
        }
    }
    simValue = simValue / (float)comparisonCount;
    return simValue;
}

// prints ActionUnit stats
void Profile::print() {
    cout << "|------------------------------- Profile Name: " << name << " -------------------------------|" << endl;
    cout << "Amount of frames in current video: " << currNumFrames << endl;
    cout << "Total amount of frames: " << totNumFrames << endl;
    cout << "Total amount of videos: " << totNumVideos << endl;

    cout << "\nProbability Matrix for current video:\n" << endl;
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        for(int j = 0; j < NUM_ACTION_UNITS; ++j) {
            printf("%.2f ", probMatrix[i][j]);
        }
        cout << "\n" << endl;
    }

    cout << "\nAverage Matrix for profile:\n" << endl;
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        for(int j = 0; j < NUM_ACTION_UNITS; ++j) {
            printf("%.2f ", avgMatrix[i][j]);
        }
        cout << "\n" << endl;
    }
    cout << "-----------------------------------------------------------------------------------------" << endl;
}

// called by default constructor and new profile constructor to initialize matrices to empty
void Profile::initializeEmptyMatrices() {
    this->probMatrix = new float*[NUM_ACTION_UNITS];
    this->avgMatrix = new float*[NUM_ACTION_UNITS];
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        probMatrix[i] = new float[NUM_ACTION_UNITS];
        avgMatrix[i] = new float[NUM_ACTION_UNITS];
        for(int j = 0; j < NUM_ACTION_UNITS; ++j) {
            probMatrix[i][j] = 0;
            avgMatrix[i][j] = 0;
        }
    }
}

// reads formatted string and assigns values (called from overloaded constructor)
void Profile::initializeFromFormattedString(string* str) {

}

// creates formatted string
string* Profile::createFormattedString() {

}
