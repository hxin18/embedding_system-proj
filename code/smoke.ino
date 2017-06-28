float temp;   
int speakerPin = 9;
int length = 15; 
char notes[] = "ccggaagffeeddc ";
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;
int length1;

// definition of the frequency of some basic notes
#define Do 262  
#define Re 294  
#define Mi 330  
#define Fa 349  
#define Sol 392  
#define La 440  
#define Si 494  
#define Do_h 523  
#define Re_h 587  
#define Mi_h 659  
#define Fa_h 698  
#define Sol_h 784  
#define La_h 880  
#define Si_h 988  

//definition of the list of the notes in the song <Happy Birthday> 
int scale[]={
Sol,Sol,La,Sol,Do_h,Si,  
             Sol,Sol,La,Sol,Re_h,Do_h,  
             Sol,Sol,Sol_h,Mi_h,Do_h,Si,La,  
             Fa_h,Fa_h,Mi_h,Do_h,Re_h,Do_h
}; 
 
// function to produces a tone with a certain frequency
void playTone(int tone, int duration) 
{
  for (long i = 0; i < duration * 1000L; i += tone * 2) 
{
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

// function to play the tone corresponding to the note name
void playNote(char note, int duration) 
{
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  for (int i = 0; i < 8; i++) 
  {
    if (names[i] == note) 
    {
      playTone(tones[i], duration);
    }
  }
}

void setup()
{
  length1=sizeof(scale)/sizeof(scale[0]);        
  Serial.begin(9600);     
  pinMode(speakerPin, OUTPUT);
}

void loop()
{
  // read the analog signal from the gas sensor
  int V1 = analogRead(A0);                    
  float vol = V1*(5.0 / 1023.0);               
  if (vol == temp)                             
  {
    temp = vol;                               
  }
  else
  { 
    Serial.print(vol);                         
    Serial.println(" V");                    
    temp = vol;
    delay(1000);                           
  }
  // judge if the gas concentration overpasses the threshold 1 (1.0)
  if (vol>1.0 && vol<1.2)
  {
 //if yes, play the song <Little Star>
 for (int i = 0; i < length; i++)
{
if (notes[i] == ' ')
{
      delay(beats[i] * tempo);
}
 else 
{
      playNote(notes[i], beats[i] * tempo);
    }
    delay(tempo / 2); 
    } 
  }
//judge if the gas concentration overpasses the threshold 2 (1.2)
  else if (vol>1.2)
  {
//if yes, play the song <Happy Birthday>
for(int i=0;i<length1;i++)
{             
    tone(speakerPin,scale[i]);  
    delay(250);  
    noTone(speakerPin);  
    delay(250);  
  }  
    
  }
  
  else
  {
    digitalWrite(speakerPin,LOW);
  }
}

