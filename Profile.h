#ifndef PROFILE
#define PROFILE

#include "ActionUnit.h"
#include <iostream>

using namespace std;

class Profile {

    public:
        Profile(); // default constructor: name = “”, probMatrix is empty 2D ptr array, totNumFrames & totNumVideos = 0 (unused)
        Profile(string name, int currNumFrames); // overloaded constructor: same as default but assigns the name (used when creating a new profile) and numFrames
        Profile(string* saveData); // overloaded constructor: string array of Profile info loaded from save file, calls initializeFromFormattedString
        ~Profile(); // destructor: delete probMatrix and avgMatrix

        void calcProbMatrix(ActionUnit** au); // takes in ptr to array of ptrs to action units, fills probMatrix with float values determined from action units (####more detailed description below#####)
        void updateAvgMatrix(); // updates avgMatrix with new probMatrix values (calculation: avgMatrix[i][j] =(totNumFrames * avgMatrix[i][j] + probMatrix[i][j]) / (totNumFrames + currNumFrames);

        void print(); // prints ActionUnit stats

        static const int NUM_ACTION_UNITS = 18; // number of action units used, which is 18 currently (if a static const int is not possible, delete static and keep const)


        // MEMBER VARIABLES
        string name; // name of the person to whom the profile belongs

        float** probMatrix; // 2D ptr array where the the pair-probability values are stored (used for current file upload)
        float** avgMatrix; // 2D ptr array where the average of all pair-probability values are stored (used for displaying and can be added to by the probMatrix to make new average)

        int currNumFrames; // how many frames are in the current video used by probMatrix (used for calculating average)
        int totNumFrames; // stat of how many total frames used in the entire Profile (used for calculating average and displaying to user)
        int totNumVideos; // stat of how many total videos have been used in the entire Profile (only for simply displaying to the user)

    private:
        void initializeEmptyMatrices(); // called by default constructor and new profile constructor to initialize matrices to empty
        void initializeFromFormattedString(string* str); // reads formatted string array and assigns values (called from overloaded constructor)
        string* createFormattedString(); // creates formatted string
};

#endif
