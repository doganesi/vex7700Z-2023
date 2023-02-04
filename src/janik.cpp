#include "vex.h"
#include <cmath>
#include <algorithm>

using namespace vex;

Janik::Janik(color allianceColor)
{
  cAllianceColor = allianceColor;
}

void Janik::spinRollerHalf() //starts with one color facing the field
{
  Intake.spin(fwd, 60, percent);
  wait(200, msec);
  Intake.stop(brake);
}


void Janik::spinRollerFull() //starts with one color facing up
{
  Intake.spin(fwd, 60, percent);
  wait(400, msec);
  Intake.stop(brake);
}

void Janik::spinRoller() //Use optical sensor
{
  CS.setLightPower(100);
  wait(500, msec);
  //Brain.Screen.clearScreen();
  Intake.spin(fwd, -60, percent);
     
    if(cAllianceColor == red)
    {
      while(CS.color() != red)
      {
        wait(5, msec);
      } 
    }
    else
    {
      while(CS.color() != blue)
      {
        wait(5, msec);
      }
    }
  
    Intake.stop(brake);
    CS.setLightPower(0);
}

void Janik::diskLaunch(int DiskQuantity, int indexerBreak)
{
  F1.spin (fwd, 600, rpm);
  wait(2800,  msec); //was 3000

  for(int i = 0; i < DiskQuantity; i++) 
  {
    Indexer.spin(fwd, IndexerSpeed, pct);
    wait(IndexerActiveTime, msec);
    Indexer.stop();
    //Indexer.spin(reverse, 80, pct);
    //Indexer.stop();
    wait(indexerBreak, msec);
  }
  
  wait(500, msec);

  F1.stop();
}
void Janik::deployExpansion() 
{
  Expansion.spin(reverse, 100, pct);
  wait(5, sec);
  Expansion.stop();
     
}

void Janik::driveForward(double target, double speed)
{
  double oneWheelDistance = target/xDriveCoeff + distanceError;
   double motorRotations = oneWheelDistance/ (PI * wheelDiameter);

  double fwdSpeed  = speed * 200.0 / 100.0;
  double backSpeed = speed * 0.95 * 200.0 / 100.0;
  
  RF.spinFor(fwd, motorRotations, rev, fwdSpeed, rpm, false);
  LF.spinFor(fwd, motorRotations, rev, backSpeed, rpm, false);
  RB.spinFor(fwd, motorRotations, rev, fwdSpeed, rpm, false);
  LB.spinFor(fwd, motorRotations, rev, backSpeed, rpm, false);

  while (RF.isSpinning() && LF.isSpinning() && RB.isSpinning() && LB.isSpinning())
  {
    wait(5, msec);
  }

  RF.stop(brake);
  LF.stop(brake);                                            
  RB.stop(brake);
  LB.stop(brake);

}

void Janik::driveBackwards(double target, double speed)
{
  double oneWheelDistance = target/xDriveCoeff + distanceError;
  double motorRotations = oneWheelDistance/ (PI * wheelDiameter);

  double fwdSpeed  = speed * 200.0 / 100.0;
  double backSpeed = speed * 0.95 * 200.0 / 100.0;
  
  RB.spinFor(reverse, motorRotations, rev, backSpeed, rpm, false);
  LB.spinFor(reverse, motorRotations, rev, fwdSpeed, rpm, false);
  RF.spinFor(reverse, motorRotations, rev, backSpeed, rpm, false);
  LF.spinFor(reverse, motorRotations, rev, fwdSpeed, rpm, false);


  while (RF.isSpinning() && LF.isSpinning() && RB.isSpinning() && LB.isSpinning())
  {
    wait(10, msec);
  }

  LF.stop(brake);                                            
  RF.stop(brake);
  LB.stop(brake);
  RB.stop(brake);
}

void Janik::resetMotors()
{
  RB.resetPosition();
  RB.resetRotation();
  RF.resetPosition();
  RF.resetRotation();
  LF.resetPosition();
  LF.resetRotation();
  LB.resetPosition();
  LB.resetRotation();
}

void Janik::driveLeftP(double target, double speed)
{
  double oneWheelDistance = target/xDriveCoeff+distanceError;
  double motorRotations = oneWheelDistance/ (PI * wheelDiameter);
  double fwdSpeed  = speed * 200.0 / 100.0;
  double revSpeed = speed * 200.0 / 100.0;

  resetMotors();
  double rotationsTraveled = 0;

  //prime the motors
  RB.spin(reverse,1,rpm);
  RF.spin(fwd, 10, pct);
  LF.spin(reverse, 15, pct);
  LB.spin(fwd, 3, pct);
  wait(125, msec);
  
    double effectiveFwdSpeed = fwdSpeed;
    double effectiveRevSpeed = revSpeed;

  while (rotationsTraveled < motorRotations)
  {

    if (rotationsTraveled > (motorRotations*0.75))
    {
      //F1.spin(fwd, 50, pct);
      effectiveFwdSpeed = fwdSpeed * (1 - rotationsTraveled/motorRotations)*3;
      effectiveRevSpeed = revSpeed * (1 - rotationsTraveled/motorRotations)*3;

    }

    if (effectiveFwdSpeed < 5)
    {
        RF.stop(brake);
        LF.stop(brake);                                            
        RB.stop(brake);
        LB.stop(brake);
        return;
    } 
     else 
    {

    RB.setVelocity(-effectiveFwdSpeed,rpm);
    LB.setVelocity(effectiveFwdSpeed,rpm);
    RF.setVelocity(effectiveRevSpeed,rpm);
    LF.setVelocity(-effectiveRevSpeed,rpm);

    }

    // RB.spin(reverse, effectiveSpeed, pct);
    // RF.spin(fwd, effectiveSpeed, pct);
    // LF.spin(reverse, effectiveSpeed, pct);
    // LB.spin(fwd, effectiveSpeed, pct);
    rotationsTraveled = RF.rotation(rev);

 //   Brain.Screen.printAt(20, 20, "traveled = %f", rotationsTraveled); 

   
  }
 

}

void Janik::driveLeft(double target, double speed)
{
  double oneWheelDistance = target/xDriveCoeff+distanceError;
  double motorRotations = oneWheelDistance/ (PI * wheelDiameter);

  double fwdSpeed  = speed * 0.94* 200.0 / 100.0;
  double backSpeed = speed * 200.0 / 100.0;

  RB.spin(reverse, 1, pct);
  RF.spin(fwd, 1, pct);
  LF.spin(reverse, 1, pct);
  LB.spin(fwd, 1, pct);


  // RF.spinFor(fwd, 0.25, rev, 1, rpm, false);
  // RB.spinFor(reverse, 0.25, rev, 1, rpm, false);

  // LF.spinFor(reverse, 0.25, rev, 1, rpm, false);
  // LB.spinFor(fwd, 0.25, rev, backSpeed, rpm, true);

  
  RF.spinFor(fwd, motorRotations, rev, fwdSpeed, rpm, false);
  RB.spinFor(reverse, motorRotations, rev, backSpeed, rpm, false);

  LF.spinFor(reverse, motorRotations, rev, fwdSpeed, rpm, false);
  LB.spinFor(fwd, motorRotations, rev, backSpeed, rpm, true);
  

  // while (RF.isSpinning() || LF.isSpinning() || RB.isSpinning() || LB.isSpinning())
  // {
  //   wait(5, msec);
  // }

  // RB.stop(coast);
  // RF.stop(coast);
  // LF.stop(coast);                                            
  // LB.stop(coast);

}

void Janik::driveRight(double target, double speed)
{
  double oneWheelDistance = target/xDriveCoeff;
  double motorRotations = oneWheelDistance/ (PI * wheelDiameter);

  double fwdSpeed  = speed * 200.0 / 100.0;
  double backSpeed = speed * 0.95 * 200.0 / 100.0;
  
  RF.spinFor(fwd, motorRotations, rev, fwdSpeed, rpm, false);
  LF.spinFor(reverse, motorRotations, rev, backSpeed, rpm, false);
  RB.spinFor(fwd, motorRotations, rev, fwdSpeed, rpm, false);
  LB.spinFor(reverse, motorRotations, rev, backSpeed, rpm, false);

  while (RF.isSpinning() && LF.isSpinning() && RB.isSpinning() && LB.isSpinning())
  {
    wait(5, msec);
  }

  RF.stop(brake);
  LF.stop(brake);                                            
  RB.stop(brake);
  LB.stop(brake);

}


void Janik::inchDriveForward(double target, int speed)                 //takes target distance and speed as parameters
{
  double x = 0;                                                         //variable that will be current distance
  
  double revStart = LF.rotation(rev);
  while(x <= target)                                                //proportional control feedback loop for error
  {
    RF.spin(forward, speed, pct);
    LF.spin(forward, speed * 0.89, pct);
    RB.spin(forward, speed, pct);
    LB.spin(forward ,speed * 0.89, pct);
    wait(10, msec);
    x = (LF.rotation(rev) - revStart) * PI * wheelDiameter; // pi D        //distance =total rotations * circumference of 1 rotation
  }
  LF.stop(brake);                                              //stops motors once target is reached and loop finishes
  RF.stop(brake);
  LB.stop(brake);
  RB.stop(brake);                                             //optional braking, will make motion more fluid
}

void Janik::inchDriveBackward(double target, int speed)                 //takes target distance and speed as parameters
{
  double x = 0;       
                                                    //variable that will be current distance
  double revStart = -RF.rotation(rev);
  while(x <= target)                                                //proportional control feedback loop for error
  {
    LF.spin(reverse, speed, pct);
    RF.spin(reverse, speed * 0.89, pct);
    RB.spin(reverse, speed * 0.89, pct);
    LB.spin(reverse, speed, pct);
    wait(10, msec);
    x=(-RF.rotation(rev) - revStart) * PI * wheelDiameter; // pi D        //distance =total rotations * circumference of 1 rotation
  }
  LF.stop(brake);                                              //stops motors once target is reached and loop finishes
  RF.stop(brake);
  LB.stop(brake);
  RB.stop(brake);                                             //optional braking, will make motion more fluid
}

void Janik::rotateLeft(int rotationTime, int speed) // 600 rotates 90 degrees at 50 speed
{
    RF.spin(fwd, speed, pct);
    RB.spin(fwd, speed, pct);
    LF.spin(reverse, speed, pct);
    LB.spin(reverse, speed, pct);
    wait(rotationTime, msec);
    LF.stop(brake);                                              //stops motors once target is reached and loop finishes
    RF.stop(brake);
    LB.stop(brake);
    RB.stop(brake);  

}

void Janik::rotateRight(int rotationTime, int speed) // 585? rotates 90 degrees at 50 speed
{
    LF.spin(fwd, speed, pct);
    LB.spin(fwd, speed, pct);
    RF.spin(reverse, speed, pct);
    RB.spin(reverse, speed, pct);
    wait(rotationTime, msec);
    LF.stop(brake);                                              //stops motors once target is reached and loop finishes
    RF.stop(brake);
    LB.stop(brake);
    RB.stop(brake);  
}

void Janik::turnLeft(int turnTime, int speed)
{
    RF.spin(fwd, speed, pct);
    RB.spin(fwd, speed, pct);
    wait(turnTime, msec);
    RB.stop(brake);
    RF.stop(brake);
}



void Janik::turnRight(int turnTime, int speed)
{
    LF.spin(fwd, speed, pct);
    LB.spin(fwd, speed, pct);
    wait(turnTime, msec);
    LB.stop(brake);
    LF.stop(brake);
}

void Janik::turnLeftStoppedWheel(motor stoppedMotor, double degrees, double speed)
{
  stoppedMotor.stop(brake);

 // double oppositeWheelDistance = PI*2* baseDiameter*degrees/360; // + distanceError;
  double adjacentWheelDistance = PI *2* 12 *degrees/360;
  double motorRotations = adjacentWheelDistance/(PI*wheelDiameter);
  double fwdSpeed  = speed * 200.0 / 100.0;
  
if (stoppedMotor.index() != RF.index() && stoppedMotor.index() !=LB.index())
{
   RF.spinFor(forward, motorRotations, rev, fwdSpeed, rpm, false);
}

if (stoppedMotor.index() != LF.index() && stoppedMotor.index() != RB.index())
{
   LF.spinFor(reverse, motorRotations, rev, fwdSpeed, rpm, false);
}

if (stoppedMotor.index() != RB.index() && stoppedMotor.index() != LF.index())
{
   RB.spinFor(forward, motorRotations, rev, fwdSpeed, rpm, false);
}

if (stoppedMotor.index() != LB.index() && stoppedMotor.index() != RF.index())
{
   LB.spinFor(reverse, motorRotations, rev, fwdSpeed, rpm, false);
}

  while (RF.isSpinning() || LF.isSpinning() || RB.isSpinning() || LB.isSpinning())
  {
    wait(10, msec);
  }

  LF.stop(brake);                                            
  RF.stop(brake);
  LB.stop(brake);
  RB.stop(brake);
  //  RF.spin(fwd, speed, pct);
  //   RB.spin(fwd, speed, pct);
  //   LF.spin(reverse, speed, pct);
  //   LB.spin(reverse, speed, pct);
  //   wait(rotationTime, msec);
  //   LF.stop(brake);                                              //stops motors once target is reached and loop finishes
  //   RF.stop(brake);
  //   LB.stop(brake);
  //   RB.stop(brake);  
}

void Janik::turnLeftArc(LeadingSide leadingSide, double innerRadius, double degrees, double speed)

{

 // double oppositeWheelDistance = PI*2* baseDiameter*degrees/360; // + distanceError;
  double innerWheelDistance = 2* PI * innerRadius * degrees /360;
  double outerWheelDistance = PI *2* (innerRadius + 12) *degrees/360;
  double innerMotorRotations = innerWheelDistance/(PI*wheelDiameter);
  double outerMotorRotations = outerWheelDistance/(PI*wheelDiameter);
  double outerSpeed  = speed * 200.0 / 100.0;
  double innerSpeed = outerSpeed * innerMotorRotations / outerMotorRotations;

  
if ( leadingSide == FRONT)
{
 //prime the motors
  RF.spin(forward,10,rpm);
  RB.spin(reverse, 1, pct);
  LF.spin(reverse, 15, pct);
  //LB.spin(reverse, 3, pct);
  wait(150, msec);


   RF.spinFor(forward, outerMotorRotations, rev, outerSpeed, rpm, false);
   LF.spinFor(reverse, outerMotorRotations, rev, outerSpeed, rpm, false);
   //RB.spinFor(forward, innerMotorRotations, rev, innerSpeed, rpm, false);
   LB.spinFor(forward, innerMotorRotations, rev, innerSpeed, rpm, false);
  
}


  while (RF.isSpinning() || LF.isSpinning() || RB.isSpinning() || LB.isSpinning())
  {
    wait(10, msec);
  }

  LF.stop(brake);                                            
  RF.stop(brake);
  LB.stop(brake);
  RB.stop(brake);
}

void Janik::turnRightArc(LeadingSide leadingSide, double innerRadius, double degrees, double speed)

{

 // double oppositeWheelDistance = PI*2* baseDiameter*degrees/360; // + distanceError;
  double innerWheelDistance = 2* PI * innerRadius * degrees /360;
  double outerWheelDistance = PI *2* (innerRadius + 12.5) *degrees/360;
  double innerMotorRotations = innerWheelDistance/(PI*wheelDiameter);
  double outerMotorRotations = outerWheelDistance/(PI*wheelDiameter);
  double outerSpeed  = speed * 200.0 / 100.0;
  double innerSpeed = outerSpeed * innerMotorRotations / outerMotorRotations;

  
if ( leadingSide == FRONT)
{
 //prime the motors
  RF.spin(reverse,10,rpm);
  RB.spin(forward, 1, pct);
  LF.spin(forward, 15, pct);
  LB.spin(reverse, 1, pct);
  wait(150, msec);


   RF.spinFor(reverse, outerMotorRotations, rev, outerSpeed, rpm, false);
   LF.spinFor(forward, outerMotorRotations, rev, outerSpeed, rpm, false);
   //RB.spinFor(forward, innerMotorRotations, rev, innerSpeed, rpm, false);
   LB.spinFor(reverse, innerMotorRotations, rev, innerSpeed, rpm, false);
  
}


  while (RF.isSpinning() || LF.isSpinning() || RB.isSpinning() || LB.isSpinning())
  {
    wait(10, msec);
  }

  LF.stop(brake);                                            
  RF.stop(brake);
  LB.stop(brake);
  RB.stop(brake);
}


void Janik::moveDiagonally(int driveTime)
{
    LB.spin(reverse, 75, pct);
    RF.spin(reverse, 75, pct);

    wait(driveTime, msec);

  // wait(4500, msec); //across the diagonal

    LB.stop(brake);
    RF.stop(brake);
}