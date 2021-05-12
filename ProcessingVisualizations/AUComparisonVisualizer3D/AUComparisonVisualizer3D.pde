float itr = 0;
PShape head;

void setup() {
  size (1000, 1000, P3D);
  camera(width/2.0, height/2.0, (height/2.0) / tan(PI*30.0 / 180.0), width/2.0, height/2.0, 0, 0, 1, 0); //default
  //                      dist    
  //camera(width/2,height/2,1500,   width/2.0,height/2.0,5,   0, 1, 0);
  head = loadShape("annaRaw.obj");
}

void draw() {
  itr += 0.01;
  
  //background(240,130,20);
  background(20);
  //lights(); //?
  directionalLight(255, 255, 255, 1, 0, 0);
  directionalLight(255, 255, 255, -1, 0, 0);
  ambientLight(30, 30, 30, 0, 0, 0); //(rgb),(coords)
  
  //translate(width/2, height/2, 0);
  translate(width/2, height+400, 0);
  rotateZ(-PI); //idk
  
  //rotateY(itr); //spin
  //rotateY(PI*1.5); //face camera
  rotateY(map(mouseX, mouseY, width, 2.5, -2.5)); //rotate with mouse
  
  pushMatrix();
  scale(300,300,300);
  shape(head);
  popMatrix();
  
  drawAUCoords();
}

void drawAUCoords() {
  // declare action units with:---------------------name------------x----y----z--
  ActionUnit innerBrowRaiser = new ActionUnit("Inner Brow Raiser", 220, 985, 45);
  ActionUnit outerBrowRaiser = new ActionUnit("Outer Brow Raiser", 183, 990, 130);
  ActionUnit browLowerer = new ActionUnit("Brow Lowerer", 203, 983, 90);
  ActionUnit upperLidRaiser = new ActionUnit("Upper Lid Raiser", 187, 940, -84);
  ActionUnit cheekRaiser = new ActionUnit("Cheek Raiser", 187, 870, 115);
  ActionUnit lidTightener = new ActionUnit("Lid Tightener", 189, 920, 96);
  ActionUnit noseWrinkler = new ActionUnit("Nose Wrinkler", 285, 870, 0);
  ActionUnit levatorLabiiSuper = new ActionUnit("Levator Labii Superioris", 215, 860, 72);
  ActionUnit lipCornerPuller = new ActionUnit("Lip Corner Puller", 202, 766, 69);
  ActionUnit dimpler = new ActionUnit("Dimpler", 183, 770, 95);
  ActionUnit lipCornerDepressor = new ActionUnit("Lip Corner Depressor", 200, 750, 72);
  ActionUnit chinRaiser = new ActionUnit("Chin Raiser", 223, 700, 0);
  ActionUnit lipStretecher = new ActionUnit("Lip Stretcher", 189, 760, 87);
  ActionUnit lipTightener = new ActionUnit("Lip Tightener", 233, 770, 0);
  ActionUnit lipsPart = new ActionUnit("Lips part**", 238, 756, 0);
  ActionUnit jawDrop = new ActionUnit("Jaw Drop", 226, 667, 0);
  ActionUnit lipSuck = new ActionUnit("Lip Suck", 227, 772, 27);
  ActionUnit blink = new ActionUnit("Blink", 196, 918, 70);
  
  //draw the location point of each
  innerBrowRaiser.drawPoint();
  outerBrowRaiser.drawPoint();
  browLowerer.drawPoint();
  upperLidRaiser.drawPoint();
  cheekRaiser.drawPoint();
  lidTightener.drawPoint();
  noseWrinkler.drawPoint();
  levatorLabiiSuper.drawPoint();
  lipCornerPuller.drawPoint();
  dimpler.drawPoint();
  lipCornerDepressor.drawPoint();
  chinRaiser.drawPoint();
  lipStretecher.drawPoint();
  lipTightener.drawPoint();
  lipsPart.drawPoint();
  jawDrop.drawPoint();
  lipSuck.drawPoint();
  blink.drawPoint();
}
