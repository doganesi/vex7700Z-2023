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

    void spinRoller();
    void diskLaunch(int diskQuantity);
    void inchDriveForward(float target, int speed);
    void inchDriveBackward(float target, int speed);

    void turnToRoller1();
    void turnToRoller2();
    void moveDiagonally(int driveTime);
};
