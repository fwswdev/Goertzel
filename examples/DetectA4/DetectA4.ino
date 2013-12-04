/*
  Blinks a light on a 16mhz Arduino when it detects an A4 (440 hz), tone
 the tuning fork pitch and something easily generated by the Tone library
  or a google search.

  The Goertzel algorithm is long standing so see 
  http://en.wikipedia.org/wiki/Goertzel_algorithm for a full description.
  It is often used in DTMF tone detection as an alternative to the Fast 
  Fourier Transform because it is quick with low overheard because it
  is only searching for a single frequency rather than showing the 
  occurrence of all frequencies.
  
  This work is entirely based on the Kevin Banks code found at
  http://www.eetimes.com/design/embedded/4024443/The-Goertzel-Algorithm 
  so full credit to him for his generic implementation and breakdown. I've
  simply massaged it into an Arduino library. I recommend reading his article
  for a full description of whats going on behind the scenes.

  See Contributors.md and add yourself for pull requests
  Released into the public domain.
*/
#include <Goertzel.h>

int sensorPin = A0;
int led = 13;


float sampling_freq=8800; 	//on 16mhz, ~8928.57142857143, on 8mhz ~44444 
							//But we want clean math so rounding to 8800 for a 4440 example
							// with a bucket the size of 20

float target_freq=440.0; //must be an integer of sampling_freq/N and be less than
                         //sampling_frequency/2 (thanks to Nyquist)
float n=20.0; 			

Goertzel goertzel = Goertzel(target_freq,n,sampling_freq);

void setup(){
  pinMode(led, OUTPUT);     
  Serial.begin(9600); 
}

void loop()
{
  goertzel.sample(sensorPin); //Will take n samples
  
  float magnitude = goertzel.detect();  //check them for target_freq
  
  if(magnitude>1000) //if you're getting false hits or no hits adjust this
    digitalWrite(led, HIGH); //if found, enable led
  else
    digitalWrite(led, LOW); //if not found, or lost, disable led
    
  Serial.println(magnitude);
}