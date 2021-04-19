#include "ActionUnit.h"
#include "ProfileManager.h"
#include "Profile.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static const int NUM_ACTION_UNITS = 18; // constant number of action units

static ProfileManager* pm = new ProfileManager();

// user methods declarations
static void viewExistingProfiles();
static void createNewProfile(int choice = 0);
static void uploadFile(int choice = 0, string name = "");
static void compareProfiles();
static void saveAndQuit();

// assigns boolean values from file to vals
static void fillAUList(ActionUnit** auList, int auListSize, string fileName) {

    ifstream file;
    file.open(fileName);

    // get numFrames
    string currLine;
    cin.ignore();
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
static string getInputFileName(string path) {
    string input;
    string fileName;

    /* Prompt and input */
    if (path == "raw/")
        cout << "Enter name of .csv file (should be in \"raw\" directory) or \"quit\" to quit: ";
    else if (path == "proc/")
        cout << "Enter name of .txt file (should be in \"proc\" directory) or \"quit\" to quit: ";
    else {
        cout << "Something went wrong..." << endl;
        return "";
    }
    cin >> input;
    fileName = path + input;

    /* Create file var and attempt to open */
    ifstream file;
    file.open(fileName);

    /* If file cannot be opened, loop until it does or quit */
    while (!file.is_open()) {
        if (input == "Quit" || input == "quit" || input == "QUIT")
            return "quit";
        cout << "File could not be found." << endl;
        if (path == "raw/")
            cout << "Enter name of .csv file (should be in \"raw\" directory) or \"quit\" to quit: ";
        else
            cout << "Enter name of .txt file (should be in \"proc\" directory) or \"quit\" to quit: ";
        cin >> input;
        fileName = path + input;
        file.open(fileName);
    }
    file.close();

    return input;
}

// takes in a string array of choices and size of array, and returns the number selected by the user
static int getInput(string choices[], int size) {
    string input;
    cout << "Please select an option:" << endl;
    for(int i = 1; i <= size; ++i) {
        cout << (i) << ". " << choices[i-1] << endl;
    }
    cout << endl;
    cin >> input;
    bool isValidInput = !input.empty() && input.length() == 1 && isdigit(input[0]);
    while(!isValidInput || stoi(input) < 1 || stoi(input) > size) {
        cout << "Invalid input. Please enter a valid number 1-" << size << ": ";
        cin >> input;
        isValidInput = !input.empty() && input.length() == 1 && isdigit(input[0]);
    }
    return stoi(input);
}

static string getExistingName() {
    string input = "";
    while(!pm->contains(input)) {
        cout << "Please enter name of an existing profile or \"quit\" to quit: ";
        cin.ignore();
        getline(cin, input);
        if (input == "Quit" || input == "quit" || input == "QUIT") {
            input = "quit";
            break;
        }
    }
    return input;
}

////////////////////////////////////////////////////////////////////////////////
// USER METHODS

static void viewExistingProfiles() {
    /*
    display profiles list
    OPTION: select profile OR main menu
    if select profile, get existing name from user
    display profile data
    OPTION: select different profile OR upload file OR delete profile OR main menu
        if select different profile, go back up ^
        if upload file, call getExistingFile
        if delete profile, delete and save to database
    */
    cout << "\n\n---------- Profile List -----------\n" << endl;
    pm->printProfileList();
    if(pm->isEmpty())
        return;
    string choices[2] = {"Select a profile", "Main Menu"};
    int choice = getInput(choices, 2);
    if (choice == 1) {
        string name = getExistingName();
        if(name == "quit")
            return;
        Profile* p = pm->getProfile(name);
        cout << endl;
        p->print(1);
        string choices2[4] = {"Upload New File", "Delete Profile", "Select Different Profile", "Main Menu"};
        choice = getInput(choices2, 4);
        if (choice == 1) {
            uploadFile(1, p->name);
        } else if (choice == 2) {
            bool successful = pm->deleteProfile(name);
            if(successful)
                cout << "Successfully deleted " << name << "\'s profile." << endl;
            else
                cout << "Failed to delete " << name << "\'s profile." << endl;
        } else if (choice == 3) {
            viewExistingProfiles();
        } else if (choice == 4) {
            return;
        } else {
            cout << "Something went wrong..." << endl;
        }
    } else if (choice == 2) {
        return;
    } else {
        cout << "Something went wrong..." << endl;
    }
}

static void createNewProfile(int choice) {
    /*
    get new name from user
    OPTION: upload new file? Yes OR No
        if yes: call getExistingFile
        if no: return to main menu
    */
    string name;
    Profile* p = new Profile();

    cout << "\n\n------- Create New Profile --------\n" << endl;
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    p->name = name;
    pm->addProfile(p);
    cout << "\nProfile Created.\n" << endl;

    if (choice == 0) {
        string choices[2] = {"Upload New File", "Main Menu"};
        choice = getInput(choices, 2);
    }

    if (choice == 1) {
        uploadFile(1, p->name);
    } else if (choice == 2) {
        return;
    } else {
        cout << "Something went wrong..." << endl;
    }
}

static void uploadFile(int choice, string name) {
    /*
    OPTION: existing profile? Yes OR No
        if yes: getExistingName, getExistingFile, processFile, save to database
        if no: createNewProfile() (with option to automatically say yes to upload file)
    */
    string procFileName;
    Profile* p;

    cout << "\n\n----------- Upload File -----------" << endl;
    if (choice == 0) {
        string choices[2] = {"Upload to Existing Profile", "Upload to New Profile"};
        choice = getInput(choices, 2); // returns 1 or 2
    }

    if (choice == 1) {
        if(pm->isEmpty()) {
            cout << "No profiles exist, please create one first." << endl;
            return;
        }
        if(name == "") {
            name = getExistingName();
            if(name == "quit")
                return;
        }
        p = pm->getProfile(name);

        // get name for raw file
        string choices2[2] = {"Upload raw .csv file", "Upload processed .txt file"};
        choice = getInput(choices2, 2);
        if (choice == 1) {
            string rawFileName = getInputFileName("raw/");
            if(rawFileName == "quit" || rawFileName == "")
                return;
            // call fileProcessor
            string str = "python3 fileProcessor.py " + rawFileName;
            const char* command = str.c_str();
            system(command);
            procFileName = "proc/" + rawFileName.substr(0,rawFileName.size()-4) + "_proc.txt";

            // wait until file is processed
            ifstream file;
            file.open(procFileName);
            cout << "Processing file...";
            while (!file.is_open()) {
                file.open(procFileName);
            }
            file.close();
            cout << "done.\n" << endl;
        } else if (choice == 2) {
            procFileName = getInputFileName("proc/");
            if(procFileName == "quit" || procFileName == "")
                return;
            procFileName = "proc/" + procFileName;
        } else {
            cout << "Something went wrong..." << endl;
        }

        int numFrames = getNumFrames(procFileName);
        p->currNumFrames = numFrames;
        ActionUnit** auList = new ActionUnit*[NUM_ACTION_UNITS];
        fillAUList(auList, NUM_ACTION_UNITS, procFileName);

        p->calcProbMatrix(auList);
        // clean-up
        for(int i = 0; i < NUM_ACTION_UNITS; ++i)
            delete auList[i];
        delete[] auList;

        p->print(1);
        cout << endl;
        cout << "Data is %" << (p->compareMatrices()*100) << " similar to profile.\n" << endl;
        string choices3[2] = {"Update profile with this data", "Ignore data"};
        choice = getInput(choices3, 2);
        if (choice == 1) {
            p->updateAvgMatrix();
            cout << endl;
            p->print(1);
            cout << "\nProfile updated." << endl;
        } else if (choice == 2) {
            cout << "\nData ignored." << endl;
        } else {
            cout << "\nSomething went wrong..." << endl;
        }
        cout << endl;
        string choices4[2] = {"Input another file", "Main Menu"};
        choice = getInput(choices4, 2);
        if (choice == 1) {
            uploadFile(choice, name);
        } else if (choice == 2) {
            return;
        } else {
            cout << "Something went wrong..." << endl;
        }

    } else if (choice == 2) {
        createNewProfile(1);
    } else {
        cout << "Something went wrong..." << endl;
    }
}

static void compareProfiles() {
    /*
    get existing name 1
    get existing name 2
    compare profiles
    OPTION: compare another? Yes OR No
        if yes: repeat loop
        if no: return to main menu
    */
    string name1;
    string name2;
    Profile* p1;
    Profile* p2;

    cout << "\n\n-------- Compare Proiles ----------\n" << endl;
    cout << "Profile 1: ";
    name1 = getExistingName();
    if(name1 == "quit")
        return;
    cout << "Profile 2: ";
    name2 = getExistingName();
    if(name2 == "quit")
        return;

    p1 = pm->getProfile(name1);
    p2 = pm->getProfile(name2);

    cout << "\nComparing " << name1 << " to " << name2 << ":" << endl;
    float comparisonVal = p1->compareTo(*p2) * 100;
    cout << "Profiles are %" << comparisonVal << " similar.\n" << endl;

    string choices[2] = {"Make new comparison", "Main Menu"};
    int choice = getInput(choices, 2);
    if(choice == 1) {
        compareProfiles();
    } else if (choice == 2) {
        return;
    } else {
        cout << "Something went wrong..." << endl;
    }
}

static void saveAndQuit() {
    // save profile info to database/file
    pm->saveProfiles();
}

/*----------------------------------- MAIN -----------------------------------*/

int main(int argc, char **argv) {
    pm->loadProfiles();
    int choice = 0;
    while(choice != 5) {
        cout << "\n\n-------------------- DeepFake Detection Program --------------------\n" << endl;
        string choices[5] = {"View Existing Profiles", "Upload File", "Create New Profile", "Compare Profiles", "Save and Quit"};
        choice = getInput(choices, 5);
        if(choice == 1) {
            viewExistingProfiles();
        } else if (choice == 2) {
            uploadFile();
        } else if (choice == 3) {
            createNewProfile();
        } else if (choice == 4) {
            compareProfiles();
        } else if (choice == 5) {
            saveAndQuit();
        } else {
            cout << "Something went wrong..." << endl;
        }
    }
    cout << "\nProgram finished.\n" << endl;

    delete pm;

    return 0;
}
