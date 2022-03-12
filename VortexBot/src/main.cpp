/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    15, 16, 17, 18, 20
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  //Avanza hasta el goal amarillo
  Drivetrain.setDriveVelocity(65, pct);
  Drivetrain.setTurnVelocity(25, pct);
  Drivetrain.driveFor(reverse, 700.0, mm, true);
  Drivetrain.setDriveVelocity(30, pct);
  Drivetrain.driveFor(reverse, 300.0, mm, true);

  //Levanta el brazo para agarrar el goal amarillo
  MotorGroup1.spinToPosition(-165, deg);

  Drivetrain.setDriveVelocity(65, pct);
  //Avanza de reversa para traer el goal amarillo a nuestra zona
  Drivetrain.driveFor(forward, 450.00, mm, true);

  //Gira hacia el centro para dejar el goal amarillo
  Drivetrain.turnFor(100, deg, true);

  Drivetrain.driveFor(reverse, 100.00, mm, true);
  MotorGroup1.spinToPosition(0, deg);

  Drivetrain.driveFor(forward, 300.00, mm, true);

  MotorGroup1.spinToPosition(-165, deg, true);
  Drivetrain.turnFor(-180, deg, true);
  Drivetrain.driveFor(forward, 100.00, mm, true);
  MotorGroup1.spinToPosition(0, deg);
  

  
/*
  //Avanza de reverza para alejarse del goal amarillo
  Drivetrain.driveFor(forward, 300.00, mm, true);

  //Levanta el brazo para evitar chocar con el goal rojo durante el siguiente giro
  MotorGroup1.spinToPosition(-165, deg, false);

  //Gira para encarar el goal rojo
  Drivetrain.turnFor(-75, deg, true);

  //Baja el brazo
  MotorGroup1.spinToPosition(0, deg, false);

  //Se aleja un poco del goal rojo
  Drivetrain.driveFor(forward, 200.00, mm, true);
  */
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
 
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  pre_auton();
  autonomous();


}
