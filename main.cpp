#include "..\include\main.h"
#include "auton_selector.h"
#include "driver_control.h"
#include "global_var.h"
#include "ports.h"
#include "pros/motors.h"
#include <iostream> // IWYU pragma: keep

// PLEASE CHECK IF ACTIVATE PNEUMATICS DURING MIDDLE GOAL

void on_center_button() {}

void initialize() {
  sortingSensor.set_led_pwm(0);
  sortingSensor.set_integration_time(20);
  // Auto Set Up
  chassis.calibrate();
  left_side_mg.tare_position_all();
  right_side_mg.tare_position_all();
  chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
  global::selectedAuton = states::autonStates::noAuto;
  verticalSensorOne.reset_position();
  horizontalSensorOne.reset_position();
  lv_init();
  pros::lcd::initialize();

  pros::Task screen_task([&]() {
    while (true) {
      // print robot location to the brain screen
      pros::lcd::print(0, "X: %f", chassis.getPose().x);         // x
      pros::lcd::print(1, "Y: %f", chassis.getPose().y);         // y
      pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
      // delay to save resources
      pros::delay(20);
    }
  });
}

void disabled() {}

void competition_initialize() { selectorInit(); }

void opcontrol() {
  willy.set_value(true);
  while (true) {

    driver_controls();
    pros::delay(15);
  }
}