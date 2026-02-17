#include "driver_control.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "liblvgl/misc/lv_types.h"
#include "liblvgl\lvgl.h" // IWYU pragma: keep
#include "main.h"
#include "ports.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <format>
#include <iostream> // IWYU pragma: keep

void autonomous() {
  // chassis.setPose(0, 0, -180);
  // chassis.moveToPoint(0, 48, 10000, {.forwards = false});

  // // L 7Ball Project 1
  // chassis.setPose(2, 0, 0);
  // outtake_storage();
  // chassis.moveToPose(-8, 24, -75, 2500, {.forwards = true, .maxSpeed = 125});
  // chassis.turnToHeading(-120, 1200);
  // chassis.moveToPoint(-36.5, 8, 1800, {.maxSpeed = 150});
  // chassis.turnToHeading(-180, 950);
  // chassis.waitUntilDone();
  // outtake_stop();
  // chassis.moveToPose(-36.5, 30, -180, 1350, {.forwards = false, .maxSpeed =
  // 125}); chassis.waitUntilDone(); outtake_top(); pros::delay(1800);
  // willy.set_value(true);
  // outtake_storage();
  // chassis.setPose(0, 0, -180);
  // chassis.waitUntilDone();
  // pros::delay(75);
  // chassis.moveToPose(0, -41.5, -180, 1650, {.forwards = true, .maxSpeed =
  // 55}); chassis.waitUntilDone(); chassis.moveToPose(0, 1, -180, 1800,
  // {.forwards = false, .minSpeed = 60}); chassis.waitUntilDone();
  // outtake_top();
  // // end

  // // L Center Rush Project 2
  // chassis.setPose(2, 0, 0);
  // // outtake_storage();
  // chassis.moveToPose(-16, 25, -75, 2500, {.forwards = true, .maxSpeed = 80});
  // // outtake_storage();
  // chassis.turnToHeading(-130, 1000);
  // chassis.moveToPoint(-44.5, -2, 1400, {.maxSpeed = 75});
  // chassis.turnToHeading(-180, 950);
  // chassis.waitUntilDone();
  // // outtake_stop();
  // chassis.moveToPoint(-44.5, 30, 1000, {.forwards = false});
  // chassis.moveToPose(-44.5, 30, -180, 1000,
  //                    {.forwards = false, .maxSpeed = 90});
  // chassis.waitUntilDone();
  // // outtake_top();
  // pros::delay(1600);

  // chassis.setPose(0, 0, -180);
  // chassis.moveToPose(2, -6, -180, 1200);
  // chassis.waitUntilDone();
  // outtake_stop();
  // // chassis.swingToHeading(0, lemlib::DriveSide::LEFT, 1200);
  // chassis.turnToHeading(0, 1000);
  // chassis.moveToPose(4, 38, 0, 3000);
  // chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
  // chassis.turnToHeading(20, 2000);

  // // Skils
  chassis.setPose(0, 0, -90);
  chassis.moveToPose(-28, 0, -90, 2000);
  chassis.turnToHeading(-180, 900, {.maxSpeed = 110});
  willy.set_value(true);
  chassis.waitUntilDone();
  outtake_storage();
  chassis.moveToPose(-24, -26, -180, 4000, {.minSpeed = 60});
  chassis.moveToPose(-28, 26, 0, 5000, {.forwards = false});
  chassis.waitUntilDone();
  outtake_top();
}