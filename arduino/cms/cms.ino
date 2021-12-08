// EG-207, SNHU
// Team Gold


// Public libraries
#include <Arduino.h>
#include <Servo.h>
#include <DHT.h>
#include <EEPROM.h>

// Config/Build
#include "constants.h"
#include "version.h"
#include "memory.h"

// Sensors
#include "sensors/WaterLevelSensor.cpp"
#include "sensors/CDS55.cpp"
#include "sensors/ParallaxUVSensor.cpp"

// Construct Sensor Objects
WaterLevelSensor rainFlow = WaterLevelSensor(ANALOG_WATER, ENABLE_WATER);
UVSensor uvSensor = UVSensor(ANALOG_UVSENSOR);
CDS55 cds55 = CDS55(ANALOG_CDS55);
DHT dht(DATA_DHT11, DHT_TYPE);

// Other objects
Servo lightSensorDoorServo;


void setup() {
  // Init serial
  Serial.begin(115200);

  // Initialize sensors
  dht.begin();

  // Initalize others
  lightSensorDoorServo.attach(LIGHT_SENSOR_SERVO);

  // Setup Status LEDs
  pinMode(STATUS_LED, OUTPUT);
  pinMode(WARN_LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);

  // Initalize RAM values
  pos = MIN_DOOR_ANGLE;
}


void loop() {
  // Update RAM values
  EEPROM.get(WARN_ADDR, warn);
  EEPROM.get(ERROR_ADDR, error);

  // Move this somewhere else
  temp = dht.readTemperature();
  lightSensorDoorServo.write(pos);

  // Blink Status LEDs with loop counter
  if (LC < 84 && COMMAND){digitalWrite(STATUS_LED, HIGH);}else{digitalWrite(STATUS_LED, LOW);}
  if (LC == 84){COMMAND = false;} // Clears command at end of STATUS_LED cycle.
  if (LC >= 84 && LC < 168 && warn != 0){digitalWrite(WARN_LED, HIGH);}else {digitalWrite(WARN_LED, LOW);}
  if (LC >= 168 && error != 0){digitalWrite(ERROR_LED, HIGH);}else {digitalWrite(ERROR_LED, LOW);}

  // Cleanup mainloop.
  cleanup();

  // This is one of the few holding commands in our program, it scales excecution speed.
  delay(4);
}


void cleanup() {
  // Cleanup tasks to be run at the END of the mainloop

  // Check for ACK at end of instruction.
  if (ACK) {
    Serial.println("ok"); // Send ACK.
    ACK = false; // Reset ACK flag.
  }

  // Handlers
  // Handler for wet_cond_while_sensor_door open should go here, and it should set pos to MIN

  // Timeout Control
  if (pos == MAX_DOOR_ANGLE && LC == 254){door_ajar_timeout++;} // Increment once per loop
  if (door_ajar_timeout == door_ajar_wait && pos != MIN_DOOR_ANGLE){pos = MIN_DOOR_ANGLE; EEPROM.put(WARN_ADDR, 15); door_ajar_timeout = 0;} // Close door on timeout, raise warning, etc

  // Increment LC
  LC++;
}


void serialEvent() {
  // Serial event is called when the serial buffer has an instruction.
  //noInterrupts(); // Do not be interrupted

  // As long as serial data is available
  while (Serial.available()) {
    COMMAND = true; // Raise the command flag.

    // Switch on serial.read single instruction.
    int instruct = Serial.read();

    switch (instruct) {
      case 0x76: // Instruction v
        Serial.println(VERSION); // Print Version
        break;
      
      case 0x65: // Instruction e
        Serial.println(error); // Print the error
        break;
      
      case 0x77: // Instruction w
        Serial.println(warn); // Print the warning
        break;
      
      case 0x45: // Instruction E
        EEPROM.put(ERROR_ADDR, 0); // Clear EEPROM Error
        Serial.println(error); // Print the error we just cleared.
        break;
      
      case 0x57: // Instruction W
        EEPROM.put(WARN_ADDR, 0); // Clear EEPROM warning
        Serial.println(warn); // Print the warning we just cleared.
        break;
      
      case 0x74: // Instruction t
        // Returns the instant temp of the dht 11

        if (!isnan(temp)) {
          Serial.print("T");Serial.println(temp);
        } else {
          Serial.println("?");
          EEPROM.put(WARN_ADDR, 10);
        }
        break;
      
      case 0x72: // Instruction r
        // Returns the instant water flow rate

        inst_flow = rainFlow.getRawValue();

        if (!isnan(inst_flow)) {
          Serial.print("R");Serial.println(inst_flow);
        } else {
          Serial.println("?");
          EEPROM.put(WARN_ADDR, 10);
        }
        break;
      
      // All these for light door sensor
      case 0x2b:
        pos++;
        Serial.println(pos);
        break;

      case 0x2d:
        pos--;
        Serial.println(pos);
        break;
      
      case 0x3d:
        pos = MAX_DOOR_ANGLE;
        Serial.println(pos);
        break;
    
      case 0x5f:
        pos = MIN_DOOR_ANGLE;
        Serial.println(pos);
        break;
      
      case 0x6c: // Instruction l
        // Returns the instant lux level

        inst_lux = cds55.getRawValue();

        if (!isnan(inst_lux)) {
          Serial.print("L");Serial.println(inst_lux);
        } else {
          Serial.println("?");
          EEPROM.put(WARN_ADDR, 10);
        }
        break;
      
      case 0x75: // Instruction u
        // Returns the instant uv index

        inst_uv = uvSensor.getRawValue();

        if (!isnan(inst_uv)) {
          Serial.print("U");Serial.println(inst_uv);
        } else {
          Serial.println("?");
          EEPROM.put(WARN_ADDR, 10);
        }
        break;
      
      default:
        // Bad or unknown instruction
        Serial.println("x");

        // Check eeprom
        if (error != 0) {
          Serial.print("E");Serial.println(error);
        }
        else if (warn != 0) {
          Serial.print("W");Serial.println(warn);
        }
        else {
          Serial.print("?");Serial.println(instruct, HEX);
        }
        break;
    }

    ACK = true; // Raise ACK flag.
  }

  //interrupts(); // Resume being interrupted.
}
