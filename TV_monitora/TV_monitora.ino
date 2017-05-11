/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>
#include <ASCII.h>

const int chipSelect = 10;
const double numMin = 1; //try to keep this an int value so the ascii converter works

int numLines = 0;
String string = "" ;
int myData;
ASCII ascii;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  if (SD.exists("TVa.txt")) {
    File dataFile = SD.open("TVa.txt");
    //make sure file pointer name is different from other variable names
    Serial.println("TVa.txt exists.");
    while(dataFile.available()){
      Serial.println(ascii.conAscii(dataFile.read()));
      myData = ascii.conAscii(dataFile.read())+ myData;
    }
    Serial.println(myData);
    Serial.println(myData);
    dataFile.close();
  } else {
    Serial.println("TVa.txt doesn't exist.");
  }
  
   File dataFile = SD.open("TVa.txt", FILE_WRITE);
  dataFile.println("1");
  Serial.println("1");
  //Serial.println("1");
  //Serial.println("1");
  
  
    dataFile.close();
    myData=0;
}

void loop() {
  // make a string for assembling the data to log:
  //String dataString = "5";
    delay(numMin*60*1000);
    //myData=0;
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
   if (SD.exists("TVa.txt")) {
    Serial.println("TVa.txt exists.");
    File dataFile = SD.open("TVa.txt", FILE_WRITE);
    while(dataFile.available()){
      Serial.println(ascii.conAscii(dataFile.read()));
      myData=ascii.conAscii(dataFile.read())+ myData;
    }
    Serial.println(myData);
    SD.remove("TVa.txt");
    Serial.println("that file is now gone");
  } else {
    Serial.println("TVa.txt doesn't exist.");
  }
  File dataFile = SD.open("TVa.txt", FILE_WRITE);
  myData=myData+numMin;
  dataFile.println(myData);
  Serial.println(myData);
  
    dataFile.close();
 
   
}










