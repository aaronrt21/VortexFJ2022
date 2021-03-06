using namespace vex;

extern brain Brain;

// VEXcode devices
extern drivetrain Drivetrain;
extern motor LeftDriveA;
extern motor LeftDriveB;
extern motor RightDriveA;
extern motor RightDriveB;
extern motor BandMotor;
extern controller Controller1;
extern motor_group MotorGroup1;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );