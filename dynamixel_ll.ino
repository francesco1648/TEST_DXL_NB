#include "Dynamixel_ll.h"

#define ProfileAcceleration 10
#define ProfileVelocity 20
// Create an instance that can be used for syncWrite (ID not used).
DynamixelLL dxl(Serial1, 0);

// Motor IDs for the two motors.
const uint8_t motorIDs[] = {210, 211};
const uint8_t numMotors = sizeof(motorIDs) / sizeof(motorIDs[0]);

// Arrays for positions, statuses, and LED settings.
int32_t homingOffset[numMotors];
uint16_t positions[numMotors];
int32_t getpositions[numMotors]= {0, 0}; // Initialize positions to 0
int16_t getLoads[numMotors];
bool setLED[numMotors];

int32_t pos_mot_2 = 0;
int32_t pos_mot_3 = 0;
int32_t pos_mot_4 = 0;
int32_t pos_mot_5 = 0;
int32_t pos_mot_6 = 0;
int32_t getpositions0[2] = {0, 0}; // Initialize positions to 0

// Create individual motor objects for setup (if needed for individual writes).
DynamixelLL mot_Left_1(Serial1, motorIDs[0]);
DynamixelLL mot_Right_1(Serial1, motorIDs[1]);
DynamixelLL mot_2(Serial1, 112);  // ID = 3
DynamixelLL mot_3(Serial1, 113);  // ID = 4
DynamixelLL mot_4(Serial1, 214);  // ID = 5
DynamixelLL mot_5(Serial1, 215);  // ID = 6
DynamixelLL mot_6(Serial1, 216);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial1.setTX(0);
  Serial1.setRX(1);
  dxl.begin(1000000);
  mot_Left_1.begin(1000000);
  mot_Right_1.begin(1000000);
  mot_2.begin(1000000);
  mot_3.begin(1000000);
  mot_4.begin(1000000);
  mot_5.begin(1000000);
  mot_6.begin(1000000);

  mot_Right_1.setTorqueEnable(false); // Disable torque for safety
  mot_Left_1.setTorqueEnable(false); // Disable torque for safety
  mot_2.setTorqueEnable(false); // Disable torque for safety
  mot_3.setTorqueEnable(false); // Disable torque for safety
  mot_4.setTorqueEnable(false); // Disable torque for safety
  mot_5.setTorqueEnable(false); // Disable torque for safety
  mot_6.setTorqueEnable(false);

   delay(10);
  mot_6.setStatusReturnLevel(2);

  // Set the operating mode to Position Control Mode (Mode 3).
  mot_Left_1.setOperatingMode(4);
  mot_Right_1.setOperatingMode(4);
  mot_2.setOperatingMode(4);
  mot_3.setOperatingMode(4);
  mot_4.setOperatingMode(4);
  mot_5.setOperatingMode(4);
  mot_6.setOperatingMode(4);

  delay(10);
  // Initialize a known present position for troubleshooting.
  homingOffset[0] = 500;
  homingOffset[1] = 1500;
  getpositions[0] = 0;
  getpositions[1] = 0;
  getLoads[0] = 0;
  getLoads[1] = 0;

  // Enable or disable debug mode for troubleshooting
  mot_Left_1.setDebug(false);
  mot_Right_1.setDebug(false);
  dxl.setDebug(false);

  // Factory Reset and Reboot
  //mot_Left_1.factoryReset(0x02);
  //delay(5000);
  //mot_Left_1.reboot();
  //delay(3000);
  //mot_Right_1.factoryReset(0x02);
  //delay(5000);
  //mot_Right_1.reboot();
  //delay(3000);

  // Enable sync mode for multiple motor control.
  dxl.enableSync(motorIDs, numMotors);

  // Configure Drive Mode for each motor:
  mot_Left_1.setDriveMode(false, false, false);
  mot_Right_1.setDriveMode(false, false, false);
  mot_2.setDriveMode(false, false, false);
  mot_3.setDriveMode(false, false, false);
  mot_4.setDriveMode(false, false, false);
  mot_5.setDriveMode(false, false, false);
  mot_6.setDriveMode(false, false, false);


  // Set Operating Mode for each motor:
  dxl.setOperatingMode(4); // Extended Position Mode
  mot_2.setOperatingMode(4);
  mot_3.setOperatingMode(4);
  mot_4.setOperatingMode(4);
  mot_5.setOperatingMode(4);
  mot_6.setOperatingMode(4);

  // Set Homing Offset for each motor:
  //dxl.setHomingOffset(homingOffset);

  // Enable torque for both motors.
 /* dxl.setTorqueEnable(true);
 mot_2.setTorqueEnable(true);
  mot_3.setTorqueEnable(true);
  mot_4.setTorqueEnable(true);
  mot_5.setTorqueEnable(true);
  mot_6.setTorqueEnable(true);
 */
/*
mot1a 1780  mot1b 2957
mot2 2122
mot3 -1951
mot4 1159
mot5 5164
mot6 -1098
*/



  delay(10);
  // Set Profile Velocity and Profile Acceleration for smooth motion.
mot_Left_1.setProfileVelocity(ProfileVelocity);
mot_Left_1.setProfileAcceleration(ProfileAcceleration);
mot_Right_1.setProfileVelocity(ProfileVelocity);
mot_Right_1.setProfileAcceleration(ProfileAcceleration);
mot_2.setProfileVelocity(ProfileVelocity);
mot_2.setProfileAcceleration(ProfileAcceleration);
mot_3.setProfileVelocity(ProfileVelocity);
mot_3.setProfileAcceleration(ProfileAcceleration);
mot_4.setProfileVelocity(ProfileVelocity);
mot_4.setProfileAcceleration(ProfileAcceleration);
mot_5.setProfileVelocity(ProfileVelocity);
mot_5.setProfileAcceleration(ProfileAcceleration);
mot_6.setProfileVelocity(ProfileVelocity);
mot_6.setProfileAcceleration(ProfileAcceleration);


getpositions0[0] = 1780; // Initialize positions to 0
getpositions0[1] = 2957; // Initialize positions to 0

/*getpositions0[0] = 1780; // Initialize positions to 0
getpositions0[1] = 2957; // Initialize positions to 0
 dxl.setHomingOffset(getpositions); // Set homing offset to 0 for all motors
  mot_2.setHomingOffset(2122);
  mot_3.setHomingOffset(-1951);
  mot_4.setHomingOffset(1159);
  mot_5.setHomingOffset(5164);
  mot_6.setHomingOffset(-1098);*/

  // Enable torque for all motors.
  dxl.setTorqueEnable(true);
  mot_Left_1.setTorqueEnable(true);
  mot_Right_1.setTorqueEnable(true);
  mot_2.setTorqueEnable(true);
  mot_3.setTorqueEnable(true);
  mot_4.setTorqueEnable(true);
  mot_5.setTorqueEnable(true);
  mot_6.setTorqueEnable(true);




  Serial.print("\nThe motors are initialised.");

  delay(2000);
}

void loop() {
dxl.setGoalPosition_EPCM(getpositions0); // Set goal position for both motors
mot_2.setGoalPosition_EPCM(2122); // Set goal position for motor 2
mot_3.setGoalPosition_EPCM(-1951); // Set goal position for motor 3
mot_4.setGoalPosition_EPCM(1159); // Set goal position for motor 4
mot_5.setGoalPosition_EPCM(5164); // Set goal position for motor 5
mot_6.setGoalPosition_EPCM(-1098); // Set goal position for motor 6


  dxl.getPresentPosition(getpositions);
  Serial.print(" first motor: \t");
  Serial.print(getpositions[0]);
  Serial.print(" second motor: \t");
  Serial.println(getpositions[1]);
  mot_2.getPresentPosition(pos_mot_2);
  mot_3.getPresentPosition(pos_mot_3);
  mot_4.getPresentPosition(pos_mot_4);
  mot_5.getPresentPosition(pos_mot_5);
  mot_6.getPresentPosition(pos_mot_6);
  Serial.print("Motor 2 Position: ");
  Serial.println(pos_mot_2);
  Serial.print("Motor 3 Position: ");
  Serial.println(pos_mot_3);
  Serial.print("Motor 4 Position: ");
  Serial.println(pos_mot_4);
  Serial.print("Motor 5 Position: ");
  Serial.println(pos_mot_5);
  Serial.print("Motor 6 Position: ");
  Serial.println(pos_mot_6);
  delay(1000);
  /*
  // Set initial positions and LED states.
  positions[0] = 0;
  positions[1] = 0;
  setLED[0] = 0;
  setLED[1] = 1;

  // Sync write Goal Position (register 116, 4 bytes) and LED (register 65, 1 byte) for all motors.
  dxl.setGoalPosition_PCM(positions);
  dxl.setLED(setLED);
  Serial.println("\nInitial Position sent to motors\n");
  delay(500);

  dxl.getCurrentLoad(getLoads);
  Serial.print("Initial Load of the first motor: ");
  Serial.println(getLoads[0]);
  Serial.print("Initial Load of the second motor: ");
  Serial.println(getLoads[1]);
  delay(2500);

  // Read and show present position from the both motors.
  dxl.getPresentPosition(getpositions);

  Serial.print("Initial Position of the first motor: ");
  Serial.println(getpositions[0]);
  Serial.print("Initial Position of the second motor: ");
  Serial.println(getpositions[1]);

  // Change positions and update LED states.
  positions[0] = 4095;
  positions[1] = 4095;
  setLED[0] = 1;
  setLED[1] = 0;
  dxl.setGoalPosition_PCM(positions);
  dxl.setLED(setLED);

  Serial.println("\nFinal Position sent to motors");
  delay(500);

  dxl.getCurrentLoad(getLoads);
  Serial.print("Final Load of the first motor: ");
  Serial.println(getLoads[0]);
  Serial.print("Final Load of the second motor: ");
  Serial.println(getLoads[1]);
  delay(2500);

  dxl.getPresentPosition(getpositions);
  Serial.print("Final Position of the first motor: ");
  Serial.println(getpositions[0]);
  Serial.print("Final Position of the second motor: ");
  Serial.println(getpositions[1]);

  // Read and display the moving status of the first motor.
  MovingStatus status = mot_Left_1.getMovingStatus();
  Serial.print("Profile Type: ");
  switch(status.profileType) {
      case TRAPEZOIDAL: Serial.println("Trapezoidal"); break;
      case TRIANGULAR:  Serial.println("Triangular"); break;
      case RECTANGULAR: Serial.println("Rectangular"); break;
      case PROFILE_NOT_USED: Serial.println("Not used (Step)"); break;
  }
  Serial.print("Following Error: ");
  Serial.println(status.followingError ? "Following" : "Not following");
  Serial.print("Profile Ongoing: ");
  Serial.println(status.profileOngoing ? "In progress" : "Completed");
  Serial.print("In-Position: ");
  Serial.println(status.inPosition ? "Arrived" : "Not arrived");


  delay(1000); // Wait for a bit before the next loop.

  // Repeat loop...*/


}
