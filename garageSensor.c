/**
 * Parking garage indicator light
 * Green light turns to red when a car is parked under it
 * @author Eitan, Hillel, Doron & Bryan Appleby
 */

#define GREEN_PIN 13
#define RED_PIN 12
#define PING_PIN 9

// Lower than this distance, the space is assumed "occupied"
const long boundary = 30 ; //cm

void setup() {
  // initialize LED digital pins as outputs
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  // initialize serial communication for debugging
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  long distance = getDistance(); // in cm
  
  if (distance > boundary){
    indicateFar();
  }
  else {
   indicateClose();
  }
  
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  delay(1000);                       // wait for a second
}


long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

long getDistance(){
  long duration, cm;

  // The ping is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(PING_PIN, OUTPUT);
  digitalWrite(PING_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(PING_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(PING_PIN, LOW);

	//Read the pulse
  pinMode(PING_PIN, INPUT);
  duration = pulseIn(PING_PIN, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  return cm;
}

int indicateFar() {
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  return 0;
}

int indicateClose() {
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(RED_PIN, HIGH);
  return 0;
}