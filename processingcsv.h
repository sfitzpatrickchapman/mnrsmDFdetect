#ifndef PROCESSINGCSV
#define PROCESSINGCSV

using namespace std;

class ProcessingCSV
{
public:
  void deleteRows(); //iterate through rows and look at success column (column index 4, contains boolean values)
  void deleteColumns(); //delete all columns, except save frame and AU_c values
  void storeProcessedFiles(); //Send raw CSV files into the function and store processed files in “processedFiles”
};
#endif
