#include "DSM501.h"

#define DSM501_PM1_0    D6
#define DSM501_PM2_5    D7
#define SAMPLE_TIME     30 // seconds

DSM501 dsm501;

void setup()
{
  // Debug console
  Serial.begin(500000);
  Serial.println();
  
  // Initialize DSM501
  //           PM1.0 pin     PM2.5 pin     sampling duration in seconds
  dsm501.begin(DSM501_PM1_0, DSM501_PM2_5, SAMPLE_TIME); // collect sensor data every SAMPLE_TIME

  // Wait 60s for DSM501 to warm up
  Serial.println("Wait 60s for DSM501 to warm up"); 
  for (int i = 1; i <= 60; i++)
  {
    delay(1000); // 1s
    Serial.print(i);
    Serial.println(" s (wait 60s for DSM501 to warm up)");
  }

  Serial.println("DSM501 is ready!");
  Serial.println();
}

void loop()
{
  // wait until the sample time (i.e 30s) is reached before reading the sensor data
  if (dsm501.update())
  { 
    // get PM particle count over 1.0 μm
    Serial.print("PM1.0 particle count: ");
    Serial.print(dsm501.getParticleCount(0));
    Serial.println(" parts/283mL");

    // get PM particle count over 2.5 μm
    Serial.print("PM2.5 particle count: ");
    Serial.print(dsm501.getParticleCount(1));
    Serial.println(" parts/283mL");

    // get PM2.5 concentration of particles between 1.0~2.5 μm
    float concentration = dsm501.getConcentration();
    Serial.print("PM1.0 ~ PM2.5 concentration: ");
    Serial.print(concentration);
    Serial.println(" ug/m3");

    Serial.println();
  } 
}
