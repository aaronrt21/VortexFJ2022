using namespace vex;

extern brain Brain;
//VEXcode devices
extern drivetrain Drivetrain;
extern motor LeftDriveA;
extern motor LeftDriveB;
extern motor RightDriveA;
extern motor RightDriveB;

extern motor ArmMotorA;
extern motor ArmMotorB;
extern motor_group ArmMotorGroup;
extern motor HandMotor;

extern controller Controller2;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
