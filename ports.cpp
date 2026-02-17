#include "ports.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
#include <cstddef>

// Motors
pros::MotorGroup right_side_mg({-19, 20, 18}, pros::v5::MotorGears::blue,
                               pros::v5::MotorUnits::degrees);
pros::MotorGroup left_side_mg({11, -12, -13}, pros::v5::MotorGears::blue,
                              pros::v5::MotorUnits::degrees);
pros::Motor intake_first_stage(9 /*change*/, pros::v5::MotorGears::blue);
pros::Motor intake_second_stage(8 /*change*/, pros::v5::MotorGears::blue);

// Pistons
pros::adi::Pneumatics descore('A', false);
pros::adi::Pneumatics willy('C', false);
pros::adi::Pneumatics intake_pull('B', true);

// Sensors
pros::Optical sortingSensor(11 /*change*/);
pros::IMU imu(16);
pros::Rotation verticalSensorOne(-14);
pros::Rotation horizontalSensorOne(-15);

// LemLib Setup
lemlib::Drivetrain drivetrain(&left_side_mg, &right_side_mg, 11.25,
                              lemlib::Omniwheel::NEW_275, 600, 2);

lemlib::TrackingWheel verticalTrackingOne(&verticalSensorOne,
                                          lemlib::Omniwheel::NEW_2, -1.5);

lemlib::TrackingWheel horizontalTrackingOne(&horizontalSensorOne,
                                            lemlib::Omniwheel::NEW_2, -3.5);
// Config
lemlib::OdomSensors sensors(&verticalTrackingOne, nullptr,
                            &horizontalTrackingOne, nullptr, &imu);
// Controllers
//  lateral PID controller
// lemlib::ControllerSettings
//     lateral_controller(5,  // proportional gain (kP)
//                        0,  // integral gain (kI)
//                        15, // derivative gain (kD)
//                        0,  // anti windup
//                        0,  // small error range, in inches
//                        0,  // small error range timeout, in milliseconds
//                        0,  // large error range, in inches
//                        0,  // large error range timeout, in milliseconds
//                        5   // maximum acceleration (slew)
//     );

// // angular PID controller
// lemlib::ControllerSettings
//     angular_controller(4,  // proportional gain (kP)
//                        0,  // integral gain (kI)
//                        40, // derivative gain (kD)
//                        0,  // anti windup
//                        0,  // small error range, in inches
//                        0,  // small error range timeout, in milliseconds
//                        0,  // large error range, in inches
//                        0,  // large error range timeout, in milliseconds
//                        0   // maximum acceleration (slew)
//     );

lemlib::ControllerSettings
    lateral_controller(8, // proportional gain (kP)
                       0,  // integral gain (kI)
                       6,  // derivative gain (kD)
                       0,  // anti windup
                       0,  // small error range, in inches
                       0,  // small error range timeout, in milliseconds
                       0,  // large error range, in inches
                       0,  // large error range timeout, in milliseconds
                       0   // maximum acceleration (slew)
    );

lemlib::ControllerSettings
    angular_controller(3.4,  // proportional gain (kP)
                       0,    // integral gain (kI)
                       16.1, // derivative gain (kD)
                       0,    // anti windup
                       0,    // small error range, in inches
                       0,    // small error range timeout, in milliseconds
                       0,    // large error range, in inches
                       0,    // large error range timeout, in milliseconds
                       0     // maximum acceleration (slew)
    );

// Chassis Setup
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        sensors);

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);