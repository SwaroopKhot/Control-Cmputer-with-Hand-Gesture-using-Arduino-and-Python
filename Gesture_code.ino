// setup for APDS9930 sensor :

//#include <Wire.h>

// Setup for ULtrasonic sensors :
const int trigger1 = 3; //Trigger pin of 1st Sesnor
const int echo1 = 4; //Echo pin of 1st Sesnor
const int trigger2 = 5; //Trigger pin of 2nd Sesnor
const int echo2 = 6; //Echo pin of 2nd Sesnor

long time_taken;
int dist,distL,distR;


void setup() {
Serial.begin(9600);
// ULtrasonic sensor :
pinMode(trigger1, OUTPUT);
pinMode(echo1, INPUT);

pinMode(trigger2, OUTPUT);
pinMode(echo2, INPUT);


}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
 
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;

if (dist>50)
dist = 50;
}

void loop() {
// Ultra-sonic sensor actions code :
// Left Sensor :
calculate_distance(trigger1,echo1);
distL =dist; //get distance of left sensor

String LName = "L:";
String LValue = LName + distL ;
Serial.println(LValue);
//delay(500);

// Right Sensor :
calculate_distance(trigger2,echo2);
distR =dist; //get distance of left sensor

String RName = "R:";
String RValue = RName + distR;
Serial.println(RValue);
// delay(1200);


// Action : Pause/Play 
if ((distL >40 && distR>40) && (distL <50 && distR<50)) //Detect both hands
{Serial.println("Play/Pause"); delay(300);}

calculate_distance(trigger1,echo1);
distL =dist;

calculate_distance(trigger2,echo2);
distR =dist;

//Control Modes for Left Sensor :

// Action  : Escape
if (distL <= 7){
  Serial.println("Escape"); delay(300);
}

// Action  : Control Rewind 1x
if (distL >= 10 && distL <= 15){
 while(distL <= 18 )
  {
    calculate_distance(trigger1,echo1);
    distL = dist;
    if (distL >= 10 && distL <= 15){
      String LName = "L:";
      String LValue = LName + distL ;
      Serial.println(LValue);
      Serial.println("CTabs"); delay(300);
    }
  }
}


// Action : Increase/Decrease Volume 
if (distL >= 20 && distL <= 30){
  delay(200);

  while(distL <= 30 )
  {
    calculate_distance(trigger1,echo1);
    distL = dist;

    // Decrease Volume :
    if (distL < 25 && distL > 20) 
    {
      Serial.println(distL);
      Serial.println("Vdown"); delay(300);
    }

    // Increase Volume :
    if (distL < 30 && distL > 25)
    {
       Serial.println(distL);
       Serial.println("Vup"); delay(300);
    }
    
  }
}

// -------------------------------------------------------

//Control Modes for Right Sensor :

// Action  : Enter
if (distR <= 7){
  Serial.println("Enter"); delay(300);
}

// Action  : Control Forward 1x
if (distR >= 10 && distR <= 15){
  Serial.println("Tab"); delay(300);
}


// Action : Continuous Fast Forwar/Rewind Volume 
if (distR >= 20 && distR <= 30){

  while(distR <= 30 )
  {
    calculate_distance(trigger2,echo2);
    distR = dist;

    // Decrease Volume :
    if (distR < 25 && distR > 20) 
    {
      Serial.println(distR);
      Serial.println("FForward");  delay(300);
    }

    // Increase Volume :
    if (distR < 30 && distR > 25)
    {
       Serial.println(distR);
       Serial.println("FRewind"); delay(300);
    }
    
  }
}




// Wait second before next reading
delay(1000);
}
