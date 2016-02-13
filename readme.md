Goertzel
========

Arduino Library implementation of the Goertzel algorithm



Example
-------

```cpp
void loop()
{
  goertzel.sample(sensorPin); //Will take n samples
  
  float magnitude = goertzel.detect();  //check them for target_freq
  
  if(magnitude>THRESHOLD) //if you're getting false hits or no hits adjust this
    digitalWrite(led, HIGH); //if found, enable led
  else
    digitalWrite(led, LOW); //if not found, or lost, disable led
    
  Serial.println(magnitude);
}
```



Dual Tone Detection Example (by jeff):

```cpp
Goertzel goertzel = Goertzel(TARGET_FREQUENCY, N, SAMPLING_FREQUENCY);

void setup(){
  pinMode(led, OUTPUT);     
  Serial.begin(9600); 
}

void loop()
{
  goertzel.sample(sensorPin);


  goertzel.ChangeParameters(TARGET_FREQUENCY, N, SAMPLING_FREQUENCY);
  float magnitude = goertzel.detect();  //check them for target_freq
  goertzel.ChangeParameters(400, N, SAMPLING_FREQUENCY);
  float magnitude2 = goertzel.detect();  //check them for target_freq
  

  static char buffer[256];  // make sure this is big enough!!!
  snprintf(buffer, sizeof(buffer), "magnitude %d", (u16)magnitude);
   
  Serial.print(buffer);
  snprintf(buffer, sizeof(buffer), "magnitude2 %d \n", (u16)magnitude2);  
  Serial.print(buffer);
  delay(500);
}
```

