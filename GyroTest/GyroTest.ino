#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20.h>
#include <Adafruit_L3GD20_U.h>

#include <ArduinoJson.h>

const float RAD_2_DEG = 180.0 / PI;

// Average amounts that each axis is off by.
const float x_offset = -0.01;
const float y_offset = -0.09;
const float z_offset = -0.01;

const int period = 20; //milliseconds

Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

void displaySensorDetails(void)
{
  sensor_t sensor;
  gyro.getSensor(&sensor);
  Serial.print  ("Sensor:\t");     Serial.println(sensor.name);
  Serial.print  ("Driver Ver:\t"); Serial.println(sensor.version);
  Serial.print  ("Unique ID:\t");  Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:\t");  Serial.print(sensor.max_value); Serial.println(" rad/s");
  Serial.print  ("Min Value:\t");  Serial.print(sensor.min_value); Serial.println(" rad/s");
  Serial.print  ("Resolution:\t"); Serial.print(sensor.resolution); Serial.println(" rad/s");
  Serial.println("");
  delay(500);
}

void setup(void)
{
  Serial.begin(9600);
  while(!Serial) { /* Block until serial port is initialized */ }
  
  gyro.enableAutoRange(true);
  
  if(!gyro.begin()) // BUG: This will block if there is no gyro attached!
  {
    Serial.println("No gyro detected. Check your wiring!");
    while(1);
  }
  
  //displaySensorDetails();
}

float round_to_nearest_tenth(float n)
{
  return ((float) round(n * 10)) / 10.0;
}

float accumulated_x = 0.0;
float accumulated_y = 0.0;
float accumulated_z = 0.0;

StaticJsonBuffer<200> json_buffer;
JsonObject& root = json_buffer.createObject();
JsonObject& gyro_data = root.createNestedObject("gyro");

void loop(void)
{
  sensors_event_t event;
  gyro.getEvent(&event);
  
  accumulated_x += (round_to_nearest_tenth(event.gyro.x - x_offset) * RAD_2_DEG) / period;
  accumulated_y += (round_to_nearest_tenth(event.gyro.y - y_offset) * RAD_2_DEG) / period;
  accumulated_z += (round_to_nearest_tenth(event.gyro.z - z_offset) * RAD_2_DEG) / period;
    
  gyro_data["x"] = accumulated_x;
  gyro_data["y"] = accumulated_y;
  gyro_data["z"] = accumulated_z;
  
  root.printTo(Serial);
  Serial.println();
  
  delay(1000 / period);
}
