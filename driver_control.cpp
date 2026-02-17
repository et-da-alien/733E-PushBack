#include "driver_control.h"
#include "auton_selector.h"
#include "global_var.h"
#include "ports.h"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include <iostream>

void outtake_storage() {
  intake_first_stage.move_velocity(2275);
  intake_second_stage.move_velocity(-0);
}

void outtake_top() {
  intake_first_stage.move_velocity(600);
  intake_second_stage.move_velocity(550);
}

void outtake_middle() {
  // PLEASE CHECK IF ACTIVATE PNEUMATICS DURING MIDDLE GOAL
  intake_first_stage.move_velocity(300);
  intake_second_stage.move_velocity(-500);
}

void outtake_bottom() {
  intake_first_stage.move_velocity(-600);
  intake_second_stage.move_velocity(-200);
}

void outtake_stop() {
  intake_first_stage.move_velocity(0);
  intake_second_stage.move_velocity(0);
}

void intake_buttons() {
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    // Intake Storage
    outtake_storage();
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    // Top Goal
    outtake_top();
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    // Middle Goal
    outtake_middle();
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    // Bottom Goal
    outtake_bottom();

  } else {
    outtake_stop();
  }
}

bool middle_intake_bool() {
  static bool middle_intaking = true;
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
    middle_intaking = !middle_intaking;
  return middle_intaking;
}

void middle_piston_actuation() {
  if (middle_intake_bool()) {
    intake_pull.set_value(middle_intake_bool());
  } else {
    intake_pull.set_value(middle_intake_bool());
  }
}

bool little_will_bool() {
  static bool matchloading = false;
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
    matchloading = !matchloading;
  return matchloading;
}

void little_will_actuation() {
  if (little_will_bool()) {
    willy.set_value(little_will_bool());
  } else {
    willy.set_value(little_will_bool());
  }
}

bool double_parked_bool() {
  static bool parked = false;
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B))
    parked = !parked;
  return parked;
}

void double_park_pistons() {
  if (double_parked_bool())
    descore.set_value(double_parked_bool());
  else
    descore.set_value(double_parked_bool());
}

bool dt_flipped() {
  static bool flipped = false;
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))
    flipped = !flipped;
  return flipped;
}
void drive_train_controls() {
  if (dt_flipped()) {
    left_side_mg.move(-master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    right_side_mg.move(-master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));

  } else {
    left_side_mg.move(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    right_side_mg.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
  }
}
void controller_rumble() {
  if (pros::battery::get_capacity() <= 35) {
    master.rumble(".-");
  }
}

void driver_controls() {
  // Drivetrain Functions
  drive_train_controls();
  // Other Bot Functions
  intake_buttons();
  double_park_pistons();
  little_will_actuation();
  middle_piston_actuation();
  controller_rumble();
}