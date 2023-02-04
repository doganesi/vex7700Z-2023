#include <cmath>

using namespace vex;

enum LeadingSide {RIGHT, FRONT, BACK, LEFT};

class Janik
{
  int IndexerSpeed = 100;
  //int IndexerBreak = 1300; //was 1100
  int IndexerActiveTime = 150;//400; then 300
  double wheelDiameter = 4.0;
  double PI  = 3.1415926;
  double xDriveCoeff = sqrt(2.0);
  double baseDiameter = 17; //distance between opposinbg wheels
  double distanceError = 1;


  public:
    color cAllianceColor;

    Janik(color allianceColor);

// Game functions

    void spinRoller(); //when color sensor works
    void spinRollerHalf(); //starts with one color facing the field
    void spinRollerFull(); //starts with one color facing up
    void diskLaunch(int diskQuantity, int indexerBreak); //starts the flywheel, launches the passed number of discs, and stops the flywheel
    void deployExpansion();

// Movement functions

    void inchDriveForward(double target, int speed); //obsolete
    void inchDriveBackward(double target, int speed); //obsolete

    void driveForward(double target, double speed); //target = distance in inches
    void driveBackwards(double target, double speed);
    void driveLeft(double target, double speed); //target = distance in inches
    void driveLeftP(double target, double speed); //target = distance in inches
    void driveRight(double target, double speed);


    void resetMotors();
    void turnLeft(int turnTime, int speed);
    void turnRight(int turnTime, int speed);
    void rotateLeft(int rotationTime, int speed);
    void rotateRight(int rotationTime, int speed);

       
    void moveDiagonally(int driveTime);

    void turnLeftStoppedWheel(motor stoppedMotor, double degrees, double speed);

    void turnRightArc(LeadingSide leadingSide, double innerRadius, double degrees, double speed);
    void turnLeftArc(LeadingSide leadingSide, double innerRadius, double degrees, double speed);
};
