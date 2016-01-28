import org.gicentre.utils.stat.*;   
import processing.serial.*;


XYChart scatterplot;
 
void setup()
{
  size(1000,800);   
  textFont(createFont("Arial",11),11);
 
  scatterplot = new XYChart(this);
  
   String[] data = loadStrings("counted.csv");
  float[] age  = new float[data.length-4];
  float[] date = new float[data.length-4];
      
  for (int i=0; i<data.length-4; i++)
  {
    String[] tokens = (data[i+1]).split("\",\"");
   
    age[i]  = Float.parseFloat(tokens[2]);
    String month = tokens[5];
    String day = tokens[6];
    Float[] dod = new Float[2];
     
    switch(month) {
      case "January":  
            dod[0] = 0.0;
            break;
      case "February": 
            dod[0] =31.0;
            break;
      case "March":  
            dod[0] = 59.0;
            break;
      case "April": 
            dod[0] =90.0;
            break;
      case "May":  
            dod[0] = 120.0;
            break;
      case "June": 
            dod[0] =151.0;
            break;
      case "July":  
            dod[0] = 181.0;
            break;
      case "August": 
            dod[0] =212.0;
            break;
      case "September":  
            dod[0] = 243.0;
            break;
      case "October": 
            dod[0] =273.0;
            break;
      case "November":  
            dod[0] = 304.0;
            break;
      case "December": 
            dod[0] =334.0;
            break;
    }
     dod[1] = Float.parseFloat(tokens[6]);

     date[i] = dod[1] + dod[0]; 
     println(tokens[0]);
     println(date[i]);

  }
  scatterplot.setData(date,age);
  
  scatterplot.showXAxis(true); 
  scatterplot.showYAxis(true); 
  scatterplot.setXFormat("");
  scatterplot.setXAxisLabel("date");
  scatterplot.setYAxisLabel("age");
 

  scatterplot.setPointColour(color(180,0,0,100));
  scatterplot.setPointSize(30);
}
 
// Draws the scatterplot.
void draw()
{
  background(255);
  scatterplot.draw(40,40,width-80,height-80);
}