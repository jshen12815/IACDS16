
/* Drawing with sound
* Jessica Shen 
* jshen1
* 51-482 Interactive Art and Computational Design 
* February 11, 2016
*
* 
*/


import ddf.minim.*;
import ddf.minim.analysis.*;
 
Minim minim;
AudioInput in;
FFT fft;



int p; //points
int mod;
int maxim;
points P[];

//Sound stuff
int sampleRate= 44100;
float [] max= new float [sampleRate/2];//amp values
float maximum;//the maximum amplitude of the max array
int amp;
float freq;



int time;

float ceny;
float cenx;
float cenxd;
float cenyd;

float phi = (sqrt(5)+1)/2 - 1;            
float golden_angle = phi * TWO_PI;        
float lg_rad = 200;
float sm_rad = 2;
float cx = 350;
float cy = 450;
  

 
void setup()
{
  background(0);
  size(1500, 1000);
  
  //points
  mod = 5000;
  P = new points[mod];
  maxim = 50;
  minim = new Minim(this);

  //sound
  in = minim.getLineIn(Minim.MONO, 4096, sampleRate);
  fft = new FFT(in.left.size(), sampleRate);
  time = 0;
}
 
void draw()
{

  fill(0);
  rect(0, 0, 200, 100);
  fill(255);
  strokeWeight(0.5);
  stroke(int((amp+1)*5),(int((freq/2))%255) + 50,(int(freq))%255 +50);
  ampMax(); //find note function
  
  P[p]=new points(p);
  P[p].makeLine();
  p=(p+1)%mod;

  textSize(10); 
  text (amp, 50, 50);
  text (int(freq), 50, 70);
  
  text (int(time), 50, 90);
  time = time + 1;
 // if (mousePressed == true) {
    spiral();
 // }
  if (time == 4000) {
    time = 0;
    background(0);   
  }
}



void spiral(){
    float ratio = time/(float)800;
    float angle = time*golden_angle;
    float spiral_rad = ratio * lg_rad;
    cenx = cos(angle) * spiral_rad;
    ceny = sin(angle) * spiral_rad;


    float sm_rad = ratio ;
    cenxd = cos(angle) * sm_rad;
    cenyd = sin(angle) * sm_rad;
    

  
  
  
}
 
void ampMax() {
 
  fft.forward(in.left);
  for (int f=0;f<sampleRate/2;f++) { 
    max[f]=fft.getFreq(float(f)); 
  }
  maximum=max(max);
 
  for (int i=0; i<max.length; i++) {
    if (max[i] == maximum) {
      freq= i;
    }
  }
  amp = int(maximum);
}


class points {
  int id;
  int px, py;
  
  int[] stretch;
  int line;
   
  points(int p) {
    id=p;
    py = (amp ) + int(ceny + cy) ;
    px = int(freq) + int(cx + cenx);
    stretch=new int[id];
   for (int i=0; i<id; i++) {
      float tdist = dist(P[i].px, P[i].py, px, py);
       if (tdist<maxim && tdist>5) {
        stretch[line]=i;
        line++;
      }
    } }
  void makeLine() {
    for (int i=0; i<line; i++) {
      line(px, py, P[stretch[i]].px, P[stretch[i]].py);
    }}}
  
 
void stop()
{
  // always close Minim audio classes when you are done with them
  in.close();
  minim.stop();
 
  super.stop();
}