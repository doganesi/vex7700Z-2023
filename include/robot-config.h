using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Indexer;
extern motor RF;
extern motor LB;
extern motor RB;
extern inertial GyroSensor;
extern motor F1;
extern motor Intake;
extern digital_out Pneu1;
extern motor LF;
extern motor Roller;
extern digital_out Pneu2;
extern motor Expansion;
extern optical CS;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );