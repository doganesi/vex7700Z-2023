#include "vex.h"

using namespace vex;

Janik::Janik(color allianceColor)
{
  cAllianceColor = allianceColor;
}

void Janik::spinRollerHalf() //starts with one color facing the field
{
  Intake.spin(fwd, -60, percent);
  wait(160, msec);
  Intake.stop(brake);
}


void Janik::spinRollerFull() //starts with one color facing up
{
  Intake.spin(fwd, -60, percent);
  wait(300, msec);
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

void Janik::diskLaunch(int DiskQuantity)
{
  F1.spin(fwd, -69, pct);
  wait(3000,  msec);

  for(int i = 0; i < DiskQuantity; i++) 
  {
    Indexer.spin(fwd, IndexerSpeed, pct);
    wait(IndexerActiveTime, msec);
    Indexer.stop();
    wait(IndexerBreak, msec);
  }
  
  wait(500, msec);

  F1.stop();
}
void Janik::deployExpansion() 
{
     Pneu1.set(true);
     Pneu2.set(true);
}

void Janik::driveForward(double target, double speed)
{
  double oneWheelDistance = target/xDriveCoeff;
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
  double oneWheelDistance = target/xDriveCoeff;
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



void Janik::moveDiagonally(int driveTime)
{
    LB.spin(reverse, 75, pct);
    RF.spin(reverse, 75, pct);

    wait(driveTime, msec);

  // wait(4500, msec); //across the diagonal

    LB.stop(brake);
    RF.stop(brake);
}