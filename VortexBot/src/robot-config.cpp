#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveA = motor(PORT3, ratio18_1, false);
motor LeftDriveB = motor(PORT4, ratio18_1, false);
motor RightDriveA = motor(PORT1, ratio18_1, true);
motor RightDriveB = motor(PORT2, ratio18_1, true);

motor MotorGroup1MotorA = motor(PORT5, ratio36_1, false);
motor MotorGroup1MotorB = motor(PORT6, ratio36_1, true);
motor_group MotorGroup1 = motor_group(MotorGroup1MotorA, MotorGroup1MotorB);

motor_group LeftDriveSmart = motor_group(LeftDriveA, LeftDriveB);
motor_group RightDriveSmart = motor_group(RightDriveA, RightDriveB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
controller Controller1 = controller(primary);

signature Vision5__ROJO = signature (1, 10417, 12529, 11473, -501, 1, -250, 3.8, 0);
signature Vision5__AZUL = signature (2, -2081, -1779, -1930, 8447, 9217, 8832, 11, 0);
vision Vision5 = vision (PORT19, 50, Vision5__ROJO, Vision5__AZUL);

motor BandMotor(PORT7, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

bool Controller1UpDownButtonsControlMotorsStopped = true;

//velocity in rpm
int vel = 30;
int vel_bajada = 5;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled)
    {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }

      if (Controller1.ButtonLeft.pressing() || Controller1.ButtonRight.pressing()) {
        MotorGroup1.spinToPosition(155,degrees,vel,rpm);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonX.pressing()) {
        MotorGroup1.spinToPosition(0,degrees,vel-vel_bajada,rpm);
        Controller1UpDownButtonsControlMotorsStopped = false;
      }else if (Controller1.ButtonDown.pressing()) {
        MotorGroup1.spinToPosition(320,degrees,vel-vel_bajada,rpm);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (!Controller1UpDownButtonsControlMotorsStopped) {
        MotorGroup1.stop(brakeType::hold);
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1UpDownButtonsControlMotorsStopped = true;
      }

      // BandMotor
      if (Controller1.ButtonR1.pressing()) {
        BandMotor.setVelocity(100, velocityUnits::pct); // pct or rpm
        BandMotor.spin(forward);
      } else if (Controller1.ButtonL1.pressing()) {
        BandMotor.setVelocity(-100, velocityUnits::pct);
        BandMotor.spin(forward);
      } else {
        BandMotor.stop(); // hold, coast, brake
      }

      

    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}