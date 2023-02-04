#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Indexer = motor(PORT20, ratio18_1, false);
motor RF = motor(PORT4, ratio18_1, true);
motor LB = motor(PORT10, ratio18_1, false);
motor RB = motor(PORT11, ratio18_1, true);
inertial GyroSensor = inertial(PORT16);
motor F1 = motor(PORT6, ratio18_1, false);
motor Intake = motor(PORT2, ratio18_1, false);
digital_out Pneu1 = digital_out(Brain.ThreeWirePort.A);
motor LF = motor(PORT1, ratio18_1, false);
motor Roller = motor(PORT19, ratio18_1, false);
digital_out Pneu2 = digital_out(Brain.ThreeWirePort.C);
motor Expansion = motor(PORT15, ratio18_1, false);
optical CS = optical(PORT7);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}