#include <PDM.h>
#include <arduinoFFT.h>

#define SAMPLES 256
#define SAMPLING_FREQUENCY 16000

ArduinoFFT<double> FFT = ArduinoFFT<double>();

short sampleBuffer[SAMPLES];
volatile int samplesRead = 0;

double vReal[SAMPLES];
double vImag[SAMPLES];

unsigned long lastDetection = 0;


// Microphone interrupt
void onPDMdata()
{
  int bytesAvailable = PDM.available();

  PDM.read(sampleBuffer, bytesAvailable);

  samplesRead = bytesAvailable / 2;
}


// LED Control
void setLED(String color)
{
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  if(color == "RED")
    digitalWrite(LEDR, LOW);

  else if(color == "GREEN")
    digitalWrite(LEDG, LOW);

  else if(color == "BLUE")
    digitalWrite(LEDB, LOW);
}


// Note Detection
String getNote(double frequency)
{

  if(frequency > 240 && frequency < 270)
    return "C4";

  else if(frequency >=270 && frequency <300)
    return "D4";

  else if(frequency >=300 && frequency <350)
    return "E4";

  else if(frequency >=350 && frequency <390)
    return "F4";

  else if(frequency >=390 && frequency <430)
    return "G4";

  else if(frequency >=430 && frequency <470)
    return "A4";

  else if(frequency >=470 && frequency <520)
    return "B4";

  else
    return "Unknown";
}



void setup()
{

  Serial.begin(115200);
  while(!Serial);


  pinMode(LEDR,OUTPUT);
  pinMode(LEDG,OUTPUT);
  pinMode(LEDB,OUTPUT);

  setLED("OFF");


  PDM.onReceive(onPDMdata);


  if(!PDM.begin(1,SAMPLING_FREQUENCY))
  {
    Serial.println("Microphone Error");
    while(1);
  }


  Serial.println("==============================");
  Serial.println("       SMART MUSIC ANALYZER");
  Serial.println("==============================");
  Serial.println("Waiting for instrument...");
}



void loop()
{

  if(samplesRead >= SAMPLES)
  {

    long volume = 0;


    for(int i=0;i<SAMPLES;i++)
    {
      vReal[i] = sampleBuffer[i];
      vImag[i] = 0;

      volume += abs(sampleBuffer[i]);
    }


    volume = volume / SAMPLES;


    // Ignore background noise
    if(volume < 300)
    {
      samplesRead = 0;
      return;
    }



    FFT.windowing(vReal,SAMPLES,FFT_WIN_TYP_HAMMING,FFT_FORWARD);

    FFT.compute(vReal,vImag,SAMPLES,FFT_FORWARD);

    FFT.complexToMagnitude(vReal,vImag,SAMPLES);



    double frequency = FFT.majorPeak(vReal,SAMPLES,SAMPLING_FREQUENCY);



    // Print only after delay
    if(millis()-lastDetection > 2000)
    {

      String note = getNote(frequency);


      Serial.println();
      Serial.println("==============================");
      Serial.println("       NOTE DETECTED");
      Serial.println("==============================");


      Serial.print("Frequency : ");
      Serial.print(frequency,1);
      Serial.println(" Hz");


      Serial.print("Note      : ");
      Serial.println(note);



      Serial.print("Detected Frequency: ");
      Serial.println(frequency);

      setLED("GREEN");


      Serial.println("==============================");


      delay(500);

      setLED("OFF");


      lastDetection = millis();

    }


    samplesRead = 0;
  }
}