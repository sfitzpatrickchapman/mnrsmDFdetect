#ifndef ACTIONUNIT
#define ACTIONUNIT

#include <iostream>

using namespace std;

class ActionUnit {

    public:
        ActionUnit(); // default constructor: assigns id = -1, numFrames = 0, and initializes activeVals to an array of length 0 (unused)
        ActionUnit(int id, int numFrames); // overloaded constructor: assigns id and numFrames, and initializes activeVals to an empty array of length numFrames
        ActionUnit(int id, int numFrames, bool* vals); // overloaded constructor: assigns id and numFrames, initializes activeVals to an empty array of length numFrames and fills it with vals
        ~ActionUnit(); // destructor: delete activeVals

        void setActiveVals(bool* vals); // assigns activeVals
        void print(); // prints ActionUnit stats
        int getID(); // returns ID
        int getNumFrames(); // returns numFrames

        bool* activeVals; // ptr to array of booleans containing this Action Unit’s values. Length of array is the number of frames.

    private:
        int id; // number given to specific action unit (ex. AU01_c’s id is 0, and AU45_c’s id is 17, because there are skipped numbers and only 18 AUs total)
        int numFrames; // total number of frames used from the video. Used to decide the length of activeVals
};

#endif
