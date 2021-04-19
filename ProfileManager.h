#ifndef PROFILEMANAGER
#define PROFILEMANAGER

#include "Profile.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace std;

class ProfileManager {
    public:
        ProfileManager();
        ~ProfileManager();

        void loadProfiles();
        void saveProfiles();

        bool contains(string name);
        Profile* getProfile(string name);

        void addProfile(Profile* p);
        bool deleteProfile(string name);

        void printProfileList();
        bool isEmpty();

    private:
        vector<Profile*>* profiles; // array of all Profile pointers

        int getProfileIndex(string name);
};


#endif
