import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.util.Scanner; // Import the Scanner class to read text files

public class ReadFile {
  public String fileName;
  
  public float[][] processFile(String inputFile) {
    float[] AUarray = new float[324];
    float[][] AUmatrix = new float[18][18];
  
    //input text file into string arr and set name
    String[] lines = loadStrings(inputFile);
    fileName = lines[0];
    
    //create parse floats into AUarray
    for (int i = 1; i < lines.length; ++i) {
      AUarray[i - 1] = Float.parseFloat(lines[i]);
    }
    
    //1D AUarray into 2D AUmatrix
    for (int i = 0; i < 18; i++) { //rows
      for (int j = 0; j < 18; j++) { //columns
        AUmatrix[i][j] = AUarray[j*18+i]; //math to get respective matrix val
      }
    }
    
    return AUmatrix;
  }
}
