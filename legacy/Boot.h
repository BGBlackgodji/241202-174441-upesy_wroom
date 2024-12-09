#include "SPIFFS.h"
void SPIFFMemoryInitial() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    //    return;
  }
  Serial.println("An Error has occurred while mounting SPIFFS");
  //    return;
}

void Save2Memory() {
  // Open the file in write mode
  File file = SPIFFS.open("/data.bin", FILE_WRITE);

  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  // Write the buffer to the file
  size_t bytesWritten = file.write((uint8_t*)ServoTimer, sizeof(ServoTimer));

  if (bytesWritten == sizeof(ServoTimer)) {
    Serial.println("Data written to SPIFFS successfully");
  } else {
    Serial.println("Error writing data to SPIFFS");
  }

  // Close the file
  file.close();

  // Unmount SPIFFS
  SPIFFS.end();
}

void ReadFromMemory() {
  // Open the file in read mode
  File file = SPIFFS.open("/data.bin", FILE_READ);

  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  // Read the data from the file into the buffer
  size_t bytesRead = file.read((uint8_t*)ServoTimer, sizeof(ServoTimer));

  if (bytesRead == sizeof(ServoTimer)) {
    Serial.println("Data read from SPIFFS successfully");
  } else {
    Serial.println("Error reading data from SPIFFS");
  }

  // Close the file
  file.close();

  // Unmount SPIFFS
  SPIFFS.end();
}