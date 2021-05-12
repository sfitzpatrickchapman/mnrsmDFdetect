/* This Processing program is in Java. To add input files, simply drag them into this window and
change the inputs on lines 5 and 6. Make sure the inputs are our .txt format. Modify the other
parameters below for other options. */

//VISUALIZATION PARAMETERS HERE; from more important to less important
String realProfileFile = "Billie Eilish.txt"; //KNOWN PROFILE INPUT
String susProfileFile = "Billie Eilish Fake 3.txt"; //SUS PROFILE INPUT
boolean visualizeKnownProfile = false;
boolean visualizeSuspectProfile = true;
boolean visualizeProfileDifference = false;
boolean showFloatVal = true; //TODO
double profileOpacity = 1.14; //the higher the less opaque
double profileDifferenceOpacity = 1.18; //these are exp.
float spacing = 2.5; //spacing between boxes


//vars you don't need to worry about
float[][] knownProfile;
float[][] susProfile;
float[][] profileDifference;

void setup() {
  size(1150, 1150); //canvas size
  ReadFile reader = new ReadFile();
  knownProfile = reader.processFile(realProfileFile); //inputfile
  susProfile = reader.processFile(susProfileFile); 
  noLoop(); //draw just once (not a gif)
}

void draw() {
  background(0); //background color
  translate(250, 250); //positioning of visual
  //translate(width/2, height/2);

  if (visualizeKnownProfile && !visualizeSuspectProfile) {
    profileDraw(knownProfile, #0DF205, profileOpacity); //#blue
    textDraw("Profile: Billie Eilish Real");
  }
  else if (!visualizeKnownProfile && visualizeSuspectProfile) {
    profileDraw(susProfile, #0DF205, profileOpacity); //#red
    textDraw("Profile: Billie Eilish Deepfake");
  }
  else if (visualizeProfileDifference) {
    profileDifference  = matrixDifference(knownProfile, susProfile);
    profileDraw(profileDifference, #00FF00, profileDifferenceOpacity); //#purple
    textDraw("Known/Suspect Profile Difference");
  }
}

void profileDraw(float[][] inputMatrix, color coloring, double opacity) {
  for (int x = 0; x < 360; x += 20) { //increment by spacing
    for (int y = 0; y < 360; y += 20) {
      pushMatrix();
      
      double percentage = inputMatrix[x/20][y/20]*510; //create rgb percentage with float (*2)
      percentage = Math.pow(percentage, opacity); //opacity increase; exp for more contrast
      int intensity = (int)percentage;
      
      if (intensity > 0) { //only print valid vals (not -1)
        color c = color(coloring, intensity); //color w/ custom intensity
        fill(c); //fills squares with this color
        square(x*spacing, y*spacing, 45);
      }
      
      if (showFloatVal && percentage > 0) { //show float value on each box if not "-1"
        String valRep = nf(inputMatrix[x/20][y/20], 1, 3);
        translate(8, 27); //11,26 is positioning of floats
        fill(255); //font white
        text(valRep, x*spacing, y*spacing);
      }
      
      popMatrix();
    }
  }
}

float[][] matrixDifference(float[][] realMatrix, float[][] fakeMatrix) {
  float[][] profileDifference = new float[18][18];
  
  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 18; j++) {
      //if invalid val, then ignore
      if ((realMatrix[i][j] == -1) && (fakeMatrix[i][j] == -1)) {
        profileDifference[i][j] = -1;
      }
      else { //otherwise calc difference and add pos val to new matrix
        profileDifference[i][j] = realMatrix[i][j] - fakeMatrix[i][j];
        
        if (profileDifference[i][j] < 0) { //make pos if neg
          profileDifference[i][j] *= -1;
        }
      }
    }
  }
  return profileDifference;
}

void textDraw(String matrixName) {
  String[] AUName = {"Inner Brow Raiser", "Outer Brow Raiser", "Brow Lowerer", "Upper Lid Raiser", "Cheek Rasier", "Lid Tightener", "Nose Wrinkler", "Upper Lip Raiser", "Lip Corner Puller", "Dimpler", "Lip Corner Depressor", "Chin Raiser", "Lip Stretcher", "Lip Tightener", "Lips part**", "Jaw Drop", "Lip Suck", "Blink"};
  
  //Title-------------------------
  push();
  textSize(50);
  text(matrixName, -225, -200);
  fill(255);
  pop();
  
  //Info Key----------------------
  push();
  textSize(13);
  text("The less opaque the box is, the more likely the two action units occur", -215, -170);
  text("at the same time for a trusted database profile or a suspect profile.", -215, -152);
  fill(255);
  pop();
  
  //Print AUs vertically----------
  push();
  for (int i = 0; i < AUName.length; i++) {
    textAlign(RIGHT);
    textSize(14);
    text(AUName[i], 0, i*50+30); 
  }
  pop();
  
  //Print AUs horizontally--------
  push();
  rotate(4.713); //no clue why it is 4.714 (maybe radians)
  for (int i = 0; i < AUName.length; i++) {
    textAlign(LEFT);
    textSize(14);
    
    text(AUName[i], 10, i*50+30);
  }
  pop();
}
