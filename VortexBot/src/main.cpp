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


/*---------------------------------------------------------------------------
/ Funciones para cambiar la posición del brazo
/
/ Up: Los brazos están hasta arriba (pose inicial para pasar la inspección)
/ Mid: Los brazos están a medias (a la altura de llevar el goal)
/ Down: Los brazos están hasta abajo (para poder meter las tenazas debajo del goal)
/
---------------------------------------------------------------------------*/
void up2down(bool wait)
{
  MotorGroup1.resetRotation();
  MotorGroup1.spinToPosition(320, deg, wait);
}

void down2up(bool wait)
{
  MotorGroup1.resetRotation();
  MotorGroup1.spinToPosition(-320, deg, wait);  
}

void up2mid(bool wait)
{
  MotorGroup1.resetRotation();
  MotorGroup1.spinToPosition(155, deg, wait);  
}

void mid2up(bool wait)
{
  MotorGroup1.resetRotation();
  MotorGroup1.spinToPosition(-155, deg, wait);
}

void mid2down(bool wait)
{
  MotorGroup1.resetRotation();
  MotorGroup1.spinToPosition(165, deg, wait);    
}

void down2mid(bool wait)
{
  MotorGroup1.resetRotation();
  MotorGroup1.spinToPosition(-165, deg, wait);
}
//-----------------------------------------------------------------------------


void autonomous(void) {
  // setDriveVelocity: Cambia la velocidad de manejo a un (cantidad, pct)
  // driveFor: Maneja una distancia de (cantidad, unidades_distancia)
  // turnFor: Gira el robot sobre su eje (cantidad, unidades_angulo)
  // x2y (down2mid, mid2down, etc.): Cambia la posición del brazo de x a y
  
  Drivetrain.setDriveVelocity(65, pct);
  
  
  //Ajuste de la velocidad de giro
  Drivetrain.setTurnVelocity(35, pct);

  //Baja el brazo para poder levantar el goal amarillo
  up2down(true);

  //Avanza hacia el goal amarillo
  
  Drivetrain.driveFor(reverse, 700, mm, true);  
  Drivetrain.setDriveVelocity(25, pct);
  Drivetrain.driveFor(reverse, 190, mm, true);

  //Levanta el goal amarillo
  down2mid(true);

  //Retrocede con el goal amarillo para traerlo a nuestra zona
  Drivetrain.setDriveVelocity(65, pct);
  Drivetrain.driveFor(forward, 400, mm, true);  
  
  //Gira hacia el centro de nuestra zona para dejar el goal amarillo
  Drivetrain.turnFor(115, deg);

  //Se mueve hacia el centro de nuestra zona
  Drivetrain.driveFor(reverse, 200, mm, true);

  //Deja el goal amarillo
  mid2down(true);
  Drivetrain.driveFor(forward, 170, mm, true);

  //Gira para encarar nuestro goal
  down2mid(true);
  Drivetrain.driveFor(reverse, 30, mm, true);
  Drivetrain.turnFor(-150, deg, true);
  Drivetrain.driveFor(forward, 240, mm, true);
  mid2down(true);

  //Recoge nuestro goal
  Drivetrain.driveFor(reverse, 300, mm, true);
  Drivetrain.setDriveVelocity(25, pct);
  Drivetrain.driveFor(reverse, 80, mm, true);

  down2mid(true);
  Drivetrain.driveFor(forward, 300, mm, true);
  
  //Anota (idealmente)
  BandMotor.spin(forward, 100, pct);
  



  //Al final subir el brazo a 90° para el periodo de control
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
  //autonomous();

}
