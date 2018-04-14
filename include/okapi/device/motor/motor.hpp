/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _OKAPI_MOTOR_HPP_
#define _OKAPI_MOTOR_HPP_

#include "api.h"
#include "okapi/device/motor/abstractMotor.hpp"

namespace okapi {
class Motor : public AbstractMotor, public pros::Motor {
  public:
  Motor(const uint8_t port, const bool reverse = false,
        const motor_encoder_units_e_t encoder_units = E_MOTOR_ENCODER_DEGREES,
        const motor_gearset_e_t gearset = E_MOTOR_GEARSET_36);

  /**
   * Get the encoder associated with this motor.
   *
   * @return encoder for this motor
   */
  virtual IntegratedEncoder getEncoder() const override;

  /**
   * Writes the value of the controller output. This method might be automatically called in another
   * thread by the controller.
   *
   * @param ivalue the controller's output
   */
  virtual void controllerSet(const double ivalue) override;
};

inline namespace literals {
/**
 * Non-reversed motor.
 **/
okapi::Motor operator"" _m(const unsigned long long iport);

/**
 * Reversed motor.
 **/
okapi::Motor operator"" _rm(const unsigned long long iport);
} // namespace literals
} // namespace okapi

#endif
