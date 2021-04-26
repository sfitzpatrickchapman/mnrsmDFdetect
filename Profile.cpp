#include "Profile.h"

// default constructor: name = “”, probMatrix & avgMatrix is 2D ptr array initialized to length NUM_ACTION_UNITS, currNumFrames & totNumFrames & totNumVideos = 0 (unused)
Profile::Profile() {
    this->name = "";
    initializeEmptyMatrices();
    this->currNumFrames = 0;
    this->totNumFrames = 0;
    this->totNumVideos = 0;
}

// overloaded constructor: Profile info loaded from save file
Profile::Profile(string saveFileName) {
    ifstream file;
    string line;
    float cell;
    file.open(saveFileName);
    getline(file, this->name);
    this->currNumFrames = 0;
    getline(file, line);
    this->totNumFrames = stoi(line);
    getline(file, line);
    this->totNumVideos = stoi(line);
    initializeEmptyMatrices();
    for(int i = 0; i < NUM_ACTION_UNITS-1; ++i) {
        for(int j = i+1; j < NUM_ACTION_UNITS; ++j) {
            getline(file, line);
            cell = stof(line);
            avgMatrix[i][j] = cell;
        }
    }
    file.close();
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
    int sum = 0; // increments when au1 and au2 both equal 1 simultaneously
    int total = 0; // increments when at least one of au1 or au2 equal 1
    float avg; // final calculation of sum / total

    // iterates over upper diagonal of matrix, excluding main diagonal
    for(int i = 0; i < NUM_ACTION_UNITS-1; ++i) {
        au1 = au[i];
        for(int j = i+1; j < NUM_ACTION_UNITS; ++j) {
            au2 = au[j];
            // iterate through currAU's activeVals and add up all equalities
            for(int k = 0; k < numFrames; ++k) {
                sum += (au1->activeVals[k] && au2->activeVals[k]);
                total += au1->activeVals[k] || au2->activeVals[k];
            }
            // calculate average number of equalities
            avg = (float) sum / (float) total;
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
                avgMatrix[i][j] = ((float) totNumFrames * avgMatrix[i][j] + currNumFrames * probMatrix[i][j]) / (float)(totNumFrames + currNumFrames);
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

float Profile::compareMatrices() {
    float simValue = 0;
    int comparisonCount = 0;
    for(int i = 0; i < NUM_ACTION_UNITS-1; ++i) {
        for(int j = i+1; j < NUM_ACTION_UNITS; ++j) {
            float diff = avgMatrix[i][j] - probMatrix[i][j];
            simValue += 1 - abs(diff);
            comparisonCount++;
        }
    }
    simValue = simValue / (float)comparisonCount;
    return simValue;
}

// prints ActionUnit stats
/*
    type 0: prints only profile header
    type 1: prints header and average matrix
    type 2: prints full profile info (header, avg matrix, and current matrix)
*/

void Profile::print(int type) {
    if (type == 0) {
        cout<<"| "<<name<<" | "<<totNumVideos<<" videos total | "<<totNumFrames<<" frames total"<<endl;
    } else {
        cout << "\n" << endl;
        cout << "|------------------------------------ Profile Name: " << name << " ------------------------------------|\n" << endl;
        cout << "Total amount of videos: " << totNumVideos << endl;
        cout << "Total amount of frames: " << totNumFrames << endl;

        cout << "\nAverage Matrix for profile:\n" << endl;
        printMatrix(avgMatrix);

        if(type == 2) {
            cout << "\nProbability Matrix for current video:" << endl;
            cout << "Amount of frames in current video: " << currNumFrames << "\n" << endl;
            printMatrix(probMatrix);
        }
        cout << "------------------------------------------------------------------------------------------------\n" << endl;
    }
}

// save data to a file in profiles directory
void Profile::saveProfileToFile() {
    ofstream file;
    string path = "profiles/" + name + ".txt";
    file.open(path);
    file << name << endl;
    file << totNumFrames << endl;
    file << totNumVideos << endl;
    for(int i = 0; i < NUM_ACTION_UNITS-1; ++i) {
        for(int j = i+1; j < NUM_ACTION_UNITS; ++j) {
            file << avgMatrix[i][j] << endl;
        }
    }
    file.close();
}

// save data to a file in profiles directory
void Profile::saveDataToFile() {
    // save to other directory
    ofstream file;
    string path = "data/other/" + name + ".txt";
    file.open(path);
    file << name << endl;
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        for(int j = 0; j < NUM_ACTION_UNITS; ++j) {
            if(avgMatrix[i][j] == 0)
                file << "-1" << endl;
            else
                file << avgMatrix[i][j] << endl;
        }
    }
    file.close();

    // save to csv directory
    path = "data/csv/" + name + ".csv";
    file.open(path);
    file << name << "," << endl;
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        for(int j = 0; j < NUM_ACTION_UNITS; ++j) {
            if(avgMatrix[i][j] == 0)
                file << "-1" << ",";
            else
                file << avgMatrix[i][j] << ",";
        }
        file << endl;
    }
    file.close();
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

void Profile::printMatrix(float** m) {
    cout << "       ";
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        cout << AU_LIST[i] << " ";
    }
    cout << "\n     +------------------------------------------------------------------------------------------";
    for(int i = 0; i < NUM_ACTION_UNITS; ++i) {
        cout << "\n     |\n" << AU_LIST[i] << " | ";
        for(int j = 0; j < NUM_ACTION_UNITS; ++j) {
            printf("%.2f ", m[i][j]);
        }
    }
    cout << "\n\n";
}
