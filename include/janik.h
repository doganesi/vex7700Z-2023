using namespace vex;

class Janik
{
  int IndexerSpeed = 65;
  int IndexerBreak = 1100;
  int IndexerActiveTime = 375;//400;
  float dia=4.0;

  public:
    color cAllianceColor;

    Janik(color allianceColor);

// Game functions

    void spinRoller(); //when color sensor works
    void spinRollerHalf(); //starts with one color facing the field
    void spinRollerFull(); //starts with one color facing up
    void diskLaunch(int diskQuantity); //starts the flywheel, launches the passed number of discs, and stops the flywheel
    void deployExpansion();

// Movement functions

    void inchDriveForward(float target, int speed);
    void inchDriveBackward(float target, int speed);

    void turnLeft(int turnTime, int speed);
    void turnRight(int turnTime, int speed);
    void rotateLeft(int rotationTime, int speed);
    void rotateRight(int rotationTime, int speed);
    
    void moveDiagonally(int driveTime);
};
