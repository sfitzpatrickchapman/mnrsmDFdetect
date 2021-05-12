//WORK IN PROGRESS

public class ActionUnit {
  public String name;
  private int x;
  private int y;
  private int z;
  private boolean central;
  
  public ActionUnit(String name, int x, int y, int z) {
    this.name = name;
    this.x = x;
    this.y = y;
    this.z = z;
    
    if (z == 0) {
      central = true;
    }
    else {
      central = false;
    }
  }
  
  public void drawPoint() {
    pushMatrix();
    //      forward,up,side
    translate(x,y,z);
    noStroke();
    sphere(5);
    popMatrix();
    
    if (!central) { //draw other side too
      pushMatrix();
      //      forward,up,side
      translate(x,y,-z);
      noStroke();
      sphere(5);
      popMatrix();
    }
  }
  
  public void connect(ActionUnit adjacentAU) {
    int[] adjCoords = adjacentAU.getCoords(); //[0]=x, [1]=y, [2]=z
    float thisX = (float)x;
    float thisY = (float)y;
    float thisZ = (float)z;
    float adjX = adjCoords[0];
    float adjY = adjCoords[1];
    float adjZ = adjCoords[2];
    
    //bezior params: xyz 1st anchor, xyz 1st ctrl pt, xyz 2nd ctrl pt, xyz 2nd anchor
    //bezier(thisX,thisY,thisZ, ,,, ,,, adjX,adjY,adjZ);
  }
  
  public int[] getCoords() {
    int[] coords = new int[3];
    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
    return coords;
  }
}
