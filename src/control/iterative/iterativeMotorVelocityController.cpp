/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "okapi/control/iterative/iterativeMotorVelocityController.hpp"

namespace okapi {
IterativeMotorVelocityControllerArgs::IterativeMotorVelocityControllerArgs(
  const AbstractMotor &imotor, std::shared_ptr<IterativeVelocityController> icontroller)
  : motor(imotor), controller(icontroller) {
}

IterativeMotorVelocityController::IterativeMotorVelocityController(
  const AbstractMotor &imotor, std::shared_ptr<IterativeVelocityController> icontroller)
  : motor(imotor), controller(icontroller) {
}

IterativeMotorVelocityController::IterativeMotorVelocityController(
  const IterativeMotorVelocityControllerArgs &iparams)
  : motor(iparams.motor), controller(iparams.controller) {
}

double IterativeMotorVelocityController::step(const double ireading) {
  controller->step(ireading);
  motor.move_velocity(static_cast<int>(controller->getOutput()));
  return controller->getOutput();
}

void IterativeMotorVelocityController::setTarget(const double itarget) {
  controller->setTarget(itarget);
}

double IterativeMotorVelocityController::getOutput() const {
  return controller->getOutput();
}

double IterativeMotorVelocityController::getError() const {
  return controller->getError();
}

double IterativeMotorVelocityController::getDerivative() const {
  return controller->getDerivative();
}

bool IterativeMotorVelocityController::isSettled() {
  return controller->isSettled();
}

void IterativeMotorVelocityController::setSampleTime(const uint32_t isampleTime) {
  controller->setSampleTime(isampleTime);
}

void IterativeMotorVelocityController::setOutputLimits(double imax, double imin) {
  controller->setOutputLimits(imax, imin);
}

void IterativeMotorVelocityController::reset() {
  controller->reset();
}

void IterativeMotorVelocityController::flipDisable() {
  controller->flipDisable();
}

uint32_t IterativeMotorVelocityController::getSampleTime() const {
  return controller->getSampleTime();
}
} // namespace okapi