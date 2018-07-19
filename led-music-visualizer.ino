//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1 

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7]; 
int i;

/********************Setup Loop*************************/
void setup() {
  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);
  
  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
}

/**************************Main Function Loop*****************************/
void loop() {
  
  readFrequencies();
  printFrequenciesOne();
  printFrequenciesTwo();
  delay(50);
 
}

/*******************Pull frquencies from Spectrum Shield********************/
void readFrequencies(){
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two); 
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}

void printFrequenciesOne(){
  Serial.print("Freq 1: ");
  for(int i = 0; i<7; i++){
    Serial.print(" ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(Frequencies_One[i]);
  }
  Serial.println("");
}

void printFrequenciesTwo(){
  Serial.print("Freq 1: ");
  for(int i = 0; i<7; i++){
    Serial.print(" ");
    Serial.print(i);
    Serial.print(":");
    Serial.print(Frequencies_Two);
  }
  Serial.println("");
}
