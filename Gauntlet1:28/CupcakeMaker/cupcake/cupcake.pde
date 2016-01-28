PShape frosting;
PShape shadow;
PShape stripes;

void setup() {
  //background color
  float r = random(200, 255);
  float g = random(200, 255);
  float b = random(200, 255);
  
  //frosting
  float rF = random(200, 255);
  float gF = random(200, 255);
  float bF = random(200, 255);
  
  //cupcake
  float rC = random(100, 255);
  float gC = random(0, 200);
  float bC = random(0, 200);
  
  //wrapper
  float rW = random(150, 240);
  float gW = random(150, 240);
  float bW = random(150, 240);
  
  //Sprinklethings
   float rS = random(100, 255);
   float gS = random(100, 255);
   float bS = random(100, 255);
  
    //Topping
   float rT = random(100, 255);
   float gT = random(100, 255);
   float bT = random(100, 255);
  
  //background
  size(400, 400);
  background(r, g, b);    
  strokeWeight(6);
  stroke(70); 
  
  //cupcake
  fill(rC,gC,bC);
  ellipse(200, 200, 250, 100);
  
  //cupcake wrapper
  fill(rW, gW, bW);          // Setting the interior of a shape (fill) to grey 
  quad(70,200,330,200, 300, 350, 100, 350); // Drawing the rectangle
  stripes = loadShape("wrapper.svg");
  stripes.disableStyle(); 
  stripes.strokeWeight(0);
  fill(rW + 15, gW + 15, bW + 15);       
  shape(stripes, -10, -25, 430, 430);


  
  //frosting
  frosting = loadShape("frosting.svg");
  frosting.disableStyle(); 
  fill(rF, gF, bF);       
  shape(frosting, -10, -25, 430, 430);

  //sprinklethings
  float sprinkle = random(0,1);
  if (sprinkle == 1) {
    frosting = loadShape("frosting.svg");
    frosting.disableStyle(); 
    fill(rF, gF, bF);       
    shape(frosting, -10, -25, 430, 430);
  }
  
   //topping
   float topping = random(0,3);
  if (topping == 1) {
  }
  if (topping == 2) {
  }
  
  save("output.png");
  exit();
}