#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// VEXcode device constructors

//Motores de ruedas

//Derecha
motor RightDriveA = motor(PORT1, ratio18_1, true);
motor RightDriveB = motor(PORT2, ratio18_1, false);

//Izquierda
motor LeftDriveA = motor(PORT4, ratio18_1, false);
motor LeftDriveB = motor(PORT3, ratio18_1, true);


//Grupo de motores izquierdos
motor_group LeftDriveSmart = motor_group(LeftDriveA, LeftDriveB);

//Grupo de motores derechos
motor_group RightDriveSmart = motor_group(RightDriveA, RightDriveB);

//Drivetrain (compuesto por grupo derecho e izquierdo)
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

//Motores que levantan el brazo
motor ArmMotorA = motor(PORT5, ratio36_1, false);
motor ArmMotorB = motor(PORT6, ratio36_1, true);
motor_group ArmMotorGroup = motor_group(ArmMotorA, ArmMotorB);

//Motor de la mano
motor HandMotor(PORT11, ratio18_1, false);
controller Controller2 = controller(primary);

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
  HandMotor.resetRotation();
  while(true) {
    if(RemoteControlCodeEnabled)
    {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller2.Axis3.position() + Controller2.Axis1.position();
      int drivetrainRightSideSpeed = Controller2.Axis3.position() - Controller2.Axis1.position();
      
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
      
      // ArmMotor
      if (Controller2.ButtonUp.pressing()) {
        ArmMotorGroup.spinToPosition(-300,degrees,vel,rpm);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (Controller2.ButtonRight.pressing() || Controller2.ButtonLeft.pressing()) {
        ArmMotorGroup.spinToPosition(-100,degrees,vel-vel_bajada,rpm);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (Controller2.ButtonDown.pressing()) {
        ArmMotorGroup.spinToPosition(-10,degrees,vel-vel_bajada,rpm);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (!Controller1UpDownButtonsControlMotorsStopped) {
        ArmMotorGroup.stop(brakeType::hold);
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1UpDownButtonsControlMotorsStopped = true;
      }

      // HandMotor
      if (Controller2.ButtonL1.pressing()) {
        HandMotor.spinToPosition(0,degrees,vel,rpm);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (Controller2.ButtonR1.pressing()) {
        HandMotor.spinToPosition(140,degrees,vel-vel_bajada,rpm);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (!Controller1UpDownButtonsControlMotorsStopped) {
        HandMotor.stop(brakeType::hold);
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1UpDownButtonsControlMotorsStopped = true;
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