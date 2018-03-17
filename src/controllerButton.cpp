/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "okapi/device/controllerButton.hpp"

namespace okapi {
ControllerButton::ControllerButton(controller_id_e_t icontroller, controller_digital_e_t ibtn,
                                   const bool iinverted)
  : controller(icontroller), btn(ibtn), inverted(iinverted), wasPressedLast(false) {
}

bool ControllerButton::isPressed() {
  wasPressedLast = currentlyPressed();
  return wasPressedLast;
}

bool ControllerButton::edge() {
  const bool pressed = currentlyPressed();
  const bool out = pressed ^ wasPressedLast;
  wasPressedLast = pressed;
  return out;
}

bool ControllerButton::risingEdge() {
  return edge() && wasPressedLast;
}

bool ControllerButton::fallingEdge() {
  return edge() && !wasPressedLast;
}

bool ControllerButton::currentlyPressed() {
  const bool pressed = controller.get_digital(btn) != 0;
  return inverted ? !pressed : pressed;
}
} // namespace okapi