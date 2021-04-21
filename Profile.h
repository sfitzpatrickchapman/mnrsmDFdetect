#ifndef PROFILE
#define PROFILE

#include "ActionUnit.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Profile {

    public:
        Profile(); // default constructor: name = “”, probMatrix is empty 2D ptr array, totNumFrames & totNumVideos = 0 (unused)
        Profile(string saveFileName); // overloaded constructor: Profile info loaded from save file
        ~Profile(); // destructor: delete probMatrix and avgMatrix

        void calcProbMatrix(ActionUnit** au); // takes in ptr to array of ptrs to action units, fills probMatrix with float values determined from action units (####more detailed description below#####)
        void updateAvgMatrix(); // updates avgMatrix with new probMatrix values (calculation: avgMatrix[i][j] =(totNumFrames * avgMatrix[i][j] + probMatrix[i][j]) / (totNumFrames + currNumFrames);

        float compareTo(const Profile& other); // compare two profiles' average matrices, returns similarity value
        float compareMatrices(); // compares probMatrix to avgMatrix (purpose is to show the user how similar the new file is to the existing data for the profile)
        void print(int type); // prints ActionUnit stats

        void saveToFile(); // save data to a file in profiles directory

        const int NUM_ACTION_UNITS = 18; // number of action units used, which is 18 currently (if a static const int is not possible, delete static and keep const)
        const string FILE_PATH = "profiles/";
        const string AU_LIST[18] = {"AU01","AU02","AU04","AU05","AU06","AU07","AU09","AU10","AU12","AU14","AU15","AU17","AU20","AU23","AU25","AU26","AU28","AU45"};


        // MEMBER VARIABLES
        int id; // id from database, might not be needed?
        string name; // name of the person to whom the profile belongs

        float** probMatrix; // 2D ptr array where the the pair-probability values are stored (used for current file upload)
        float** avgMatrix; // 2D ptr array where the average of all pair-probability values are stored (used for displaying and can be added to by the probMatrix to make new average)

        int currNumFrames; // how many frames are in the current video used by probMatrix (used for calculating average)
        int totNumFrames; // stat of how many total frames used in the entire Profile (used for calculating average and displaying to user)
        int totNumVideos; // stat of how many total videos have been used in the entire Profile (only for simply displaying to the user)

    private:
        void initializeEmptyMatrices(); // called by default constructor and new profile constructor to initialize matrices to empty
        void printMatrix(float** m);
};

#endif
