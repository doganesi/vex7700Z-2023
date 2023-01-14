/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*    Update:  updatem 8-20-22*/
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Indexer              motor         20              
// RF                   motor         4               
// LB                   motor         10              
// RB                   motor         11              
// GyroSensor           inertial      16              
// F1                   motor         6               
// Intake               motor         2               
// Pneu1                digital_out   A               
// CS                   optical       7               
// LF                   motor         1               
// Roller               motor         19              
// Pneu2                digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global Variables here
Janik janik(red);

enum AutonOption {ALL, RED_RIGHT, RED_FRONT, BLUE_RIGHT, BLUE_FRONT, PROG };

float dia=4.0;

float Pi = 3.14;
float D = 4.0;
float C = Pi * D;
// Custom Functions
color AllianceColor = white;
int AutonSelected = 0; 
AutonOption selectedOption = ALL;

double OldError = 0.0;
double TBHval = 0.0;
double FWDrive = 0.0;

int IndexerSpeed = 65;
int IndexerBreak = 1100;
int IndexerActiveTime = 375;//400;



void spinFlywheel(double speed) {
  speed = speed * 120; // speed is in percentage so convert to mV 100% = 12000
                       // mV
  F1.spin(forward, speed, voltageUnits::mV);
}

void controlFlywheelSpeed(double target) {
  double kI = .025;
  double speed = F1.velocity(percent);
  double error = target - speed;
  double fwDrive = FWDrive + kI * error;
  // :D
  Brain.Screen.printAt(1, 40, " speed = %.2f ", speed);
  // Keep drive between 0 to 100%
  if (fwDrive > 100)
    fwDrive = 100;
  if (fwDrive < 0)
    fwDrive = 0;
  // Check for zero crossing
  if (error * OldError < 0) {
    fwDrive = 0.5 * (fwDrive + TBHval);
    TBHval = fwDrive;
  }

  Brain.Screen.printAt(180, 40, "fwdrive %.1f  ", fwDrive);
  spinFlywheel(fwDrive);

  FWDrive = fwDrive;
  OldError = error;
}

void flywheelMonitor() {
  double current1 = F1.current();
  double t1 = F1.temperature(celsius);

  Brain.Screen.printAt(1, 60, "F1 current = %.1f   Temp = %.1f   ", current1,
                       t1);
}

void drive(int lspeed, int rspeed, int wt) {
  LF.spin(forward, lspeed, percent);
  LB.spin(forward, lspeed, percent);
  RF.spin(forward, rspeed, percent);
  RB.spin(forward, rspeed, percent);
  wait(wt, msec);
}

void xDrive(int speed, int strafe, int spin, int wt) {
  int spinSpeed = spin*0.75;
  LF.spin(forward, speed + strafe + spinSpeed, percent);
  LB.spin(forward, speed - strafe + spinSpeed, percent);
  RF.spin(forward, speed - strafe - spinSpeed, percent);
  RB.spin(forward, speed + strafe - spinSpeed, percent);
  wait(wt, msec);
}

// void driveMonitor() {
//   Brain.Screen.printAt(1, 20, "Drive Monitor");
//   float currentLF = LF.current();
//   float currentLB = LB.current();
//   float currentRF = RF.current();
//   float currentRB = RB.current();
//   float tempLF = LF.temperature(celsius);
//   float tempLB = LB.temperature(celsius);
//   float tempRF = RF.temperature(celsius);
//   float tempRB = RB.temperature(celsius);

//   Brain.Screen.printAt(1, 40, "LF current= %.2f   termperature = %.2f",
//                        currentLF, tempLF);
//   Brain.Screen.printAt(1, 60, "LB current= %.2f   termperature = %.2f",
//                        currentLB, tempLB);
//   Brain.Screen.printAt(1, 80, "RF current= %.2f   termperature = %.2f",
//                        currentRF, tempRF);
//   Brain.Screen.printAt(1, 100, "RB current= %.2f   termperature = %.2f",
//                        currentRB, tempRB);
// }


void inchDriveRight(float target, int speed)                 //takes target distance and speed as parameters
{
    float x=0;                                                         //variable that will be current distance
  
  while(x<=target)                                                //proportional control feedback loop for error
  {
    LF.spin(forward,speed,pct);
    RF.spin(reverse,speed,pct);
    RB.spin(forward,speed,pct);
    LB.spin(reverse,speed,pct);
    wait(10,msec);
    x=LF.rotation(rev)*3.14*dia; // pi D        //distance =total rotations * circumference of 1 rotation
  }
     LF.stop(brake);                                              //stops motors once target is reached and loop finishes
     RF.stop(brake);
     LB.stop(brake);
     RB.stop(brake);                                             //optional braking, will make motion more fluid
}

void inchDriveLeft(float target, int speed)                 //takes target distance and speed as parameters
{
    float x=0;                                                         //variable that will be current distance
  
  while(x<=target)                                                //proportional control feedback loop for error
  {
    LF.spin(reverse,speed,pct);
    RF.spin(forward,speed,pct);
    RB.spin(reverse,speed,pct);
    LB.spin(forward,speed,pct);
    wait(10,msec);
    x=LF.rotation(rev)*3.14*dia; // pi D        //distance =total rotations * circumference of 1 rotation
  }
     LF.stop(brake);                                              //stops motors once target is reached and loop finishes
     RF.stop(brake);
     LB.stop(brake);
     RB.stop(brake);                                             //optional braking, will make motion more fluid
}



void driveBrake() {
  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);
}








void ProgrammingSkills() 
{
  
  janik.diskLaunch(2); //Launch preloads

  //janik.inchDriveForward(25, 50);
  janik.turnRight(120, 50); //straighten
  janik.driveForward(27, 50);
  janik.turnLeft(1500, 50);
  
  janik.spinRollerFull(); //First Roller

  janik.driveBackwards(28, 50);
  janik.turnRight(1300, 50);
  janik.driveForward(13.5, 50);

  wait(100, msec);
  // janik.inchDriveForward(17, 50);

  janik.spinRollerFull(); //Second Roller

  janik.driveBackwards(22, 50);
  
  janik.turnLeft(1250, 50);

  // janik.moveDiagonally(4500); //4500 takes across the full diagonal
  // janik.inchDriveBackward(24.5, 30);
  // janik.turnLeft(1280, 50);
  
  // janik.spinRollerFull(); //Third Roller

  // janik.inchDriveBackward(13, 50);
  // janik.turnRight(1300, 50);
  // janik.inchDriveForward(17, 50);

  // janik.spinRollerFull(); //Fourth Roller

  // janik.inchDriveBackward(10,50);
  // janik.rotateLeft(600, 50);

  janik.deployExpansion(); //Expand

}


void autonRight()
{
  janik.diskLaunch(2);
  janik.turnLeft(120,50);

  janik.driveForward(26, 50);
  janik.turnRight(1300, 50);

  janik.spinRollerHalf();
}

void autonFront() 
{

  janik.diskLaunch(2);

  janik.turnRight(120, 50);
  janik.driveForward(26, 50);
  janik.turnLeft(1500, 50);
  
  janik.spinRollerHalf();  
}



void driver() {
  int count = 0;
  int targetSpeed = 0;
  driveBrake();
  // User control code here, inside the loop
  while (true) 
  {
    int speed = Controller1.Axis3.position();
    int strafe = Controller1.Axis4.position();
    int spin = Controller1.Axis1.position();

    if (Controller1.ButtonA.pressing()) {
      Pneu1.set(true);
      Pneu2.set(true);
      
    } else if (Controller1.ButtonB.pressing()) {
      Pneu1.set(false);
      Pneu2.set(false);
    }

    xDrive(speed, strafe, spin, 10);
    count++;
    if (count >= 50) {
      //driveMonitor();
      count = 0;
    }
    if (Controller1.ButtonLeft.pressing())
      F1.spin(fwd, -69, pct);
    if (Controller1.ButtonUp.pressing())
      targetSpeed = -60;
    if (Controller1.ButtonRight.pressing())
      targetSpeed = -90;
    if (Controller1.ButtonDown.pressing())
      F1.spin(fwd, 0, pct);
    //controlFlywheelSpeed(targetSpeed);
  

  if (Controller1.ButtonL1.pressing())
    Intake.spin(fwd, -75, pct);
  else if (Controller1.ButtonL2.pressing())
    Intake.spin(fwd, 75, pct);
  else
    Intake.spin(fwd, 0, pct);


  if (Controller1.ButtonR1.pressing())
    Indexer.spin(fwd, 50, pct);
  else if (Controller1.ButtonR2.pressing())
    Indexer.spin(fwd, -50, pct);
  else
    Indexer.spin(fwd, 0, pct);

  }




}
// dickase
// cucumber


void drawGUIAutonSelector() 
{
  // Draws 5 buttons to be used for selecting auton mode option
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(1, 40, "Select Starting Position then Press Go");
  //Brain.Screen.printAt(1, 200, "Auton Selected =  %d   ", autonSelect);

  // Red Front
  Brain.Screen.setFillColor(selectedOption == RED_FRONT || selectedOption == ALL ? red : black);
  Brain.Screen.drawRectangle(20, 50, 100, 50);
  Brain.Screen.printAt(25, 75, "RED Front");

  // Red Right
  Brain.Screen.setFillColor(selectedOption == RED_RIGHT || selectedOption == ALL ? red : black);
  Brain.Screen.drawRectangle(170, 50, 100, 50);
  Brain.Screen.printAt(175, 75, "RED Right");

  // Program
  Brain.Screen.setFillColor(selectedOption == PROG || selectedOption == ALL ? red : black);
  Brain.Screen.drawRectangle(320, 75, 100, 100);
  Brain.Screen.printAt(325, 125, "Program");

  // Blue Front
  Brain.Screen.setFillColor(selectedOption == BLUE_FRONT || selectedOption == ALL ? blue : black);
  Brain.Screen.drawRectangle(20, 150, 100, 50);
  Brain.Screen.printAt(25, 175, "BLUE Front");

  //Blue Right

  Brain.Screen.setFillColor(selectedOption == BLUE_RIGHT || selectedOption == ALL ? blue : black);
  Brain.Screen.drawRectangle(170, 150, 100, 50);
  Brain.Screen.printAt(175, 175, "BLUE Right");

  Brain.Screen.setFillColor(black);
}


void selectAuton() 
{
  
  int x = Brain.Screen.xPosition(); // get the x position of last touch of the screen
  int y = Brain.Screen.yPosition(); // get the y position of last touch of the screen
  // check to see if buttons were pressed

  if (x >= 20 && x <= 120 && y >= 50 && y <= 100) // RED FRONT button pressed
  {
    AllianceColor = red; //TurnRoller will turn the rollers to RED
    AutonSelected = 1;   //Robot starts auton to the left of the alliance high goal

    selectedOption = RED_FRONT;
    drawGUIAutonSelector();
    Brain.Screen.printAt(1, 210, "Red Front Selected");
  }

  if (x >= 20 && x <= 120 && y >= 150 && y <= 200) //BLUE FRONT  button pressed
  {
    AllianceColor = blue; //TurnRoller will turn the rollers to BLUE
    AutonSelected = 1;    //Robot starts auton to the left of the alliance high goal
    selectedOption = BLUE_FRONT;
    drawGUIAutonSelector();
    Brain.Screen.printAt(1, 210, "Blue Front Selected");
  }

  if (x >= 170 && x <= 270 && y >= 150 && y <= 200) //BLUE RIGHT  button pressed
  {
    AllianceColor = blue; //TurnRoller will turn the rollers to BLUE
    AutonSelected = 2;    //Robot starts auton to the right of the alliance high goal
    selectedOption=BLUE_RIGHT;
    drawGUIAutonSelector();
    Brain.Screen.printAt(1, 210, "Blue Right Selected");
  }

  if (x >= 170 && x <= 270 && y >= 50 && y <= 100) //RED RIGHT  button pressed
  {
    AllianceColor = red; //TurnRoller will turn the rollers to RED
    AutonSelected = 2;    //Robot starts auton to the right of the alliance high goal
    selectedOption=RED_RIGHT;
    drawGUIAutonSelector();
    Brain.Screen.printAt(1, 210, "Red Right Selected");
   }

  if (x >= 320 && x <= 420 && y >= 75 && y <= 175) //PROGRAMMING  button pressed
  {
    AllianceColor = red; //TurnRoller will turn the rollers to RED
    AutonSelected = 3;    //Robot starts programming skills run
    selectedOption=PROG;
    drawGUIAutonSelector();
    Brain.Screen.printAt(1, 210, "Programming Skills Selected");
   }
    
}


void auton()
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
{

  switch (AutonSelected)
  {
    case 0: // auton not selected

      break;
      
    case 1: //robot to the left of the alliance high goal  
     { 
      autonFront();
      break;
     }
    case 2: //robot to the right of the alliance high goal
      autonRight();
      break;
    case 3: //programming skills
      ProgrammingSkills();
      break;  
  }
}

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  drawGUIAutonSelector();
  Brain.Screen.pressed(selectAuton);

  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting initial positions, ...
}

int main() {

  // Set up callbacks for autonomous and driver control periods.
 Competition.autonomous(auton);
 Competition.drivercontrol(driver);
  

  // Run the pre-autonomous function.
 pre_auton();
 //auton();

 

  // Prevent main from exiting with an infinite loop.
  while (true) 

  {
     wait(100, msec);
  }
}
