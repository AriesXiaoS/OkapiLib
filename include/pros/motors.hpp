/**
 * \file motors.hpp
 *
 * \brief Contains prototypes for the motor-related thread-safe wrapper
 * functions.
 *
 * This file contains the header info for the functions used to modify the
 * status of vex motors.
 *
 * \copyright (c) 2017-2018, Purdue University ACM SIGBots.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * LIcense, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _PROS_MOTORS_HPP_
#define _PROS_MOTORS_HPP_

#include "pros/motors.h"

namespace pros {
class Motor {
	public:
	Motor(const uint8_t port,
	      const bool reverse = false,
	      const motor_encoder_units_e_t encoder_units = E_MOTOR_ENCODER_DEGREES,
	      const motor_gearset_e_t gearset = E_MOTOR_GEARSET_36);

	/******************************************************************************/
	/**                         Motor movement functions                         **/
	/**                                                                          **/
	/**          These functions allow programmers to make motors move           **/
	/******************************************************************************/
	/**
	 * \brief Sets the velocity for the motor from -128 to 127.
	 *
	 * This velocity corresponds to different actual speeds depending on the gearset
	 * used for the motor. The velocity is held with PID to ensure consistent speed,
	 * as opposed to setting the motor's voltage.
	 *
	 * \note This operator is equivalent to set_target_velocity and move_velocity
	 *
	 * \param velocity
	 *        The new motor velocity from -127 to 127
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t operator=(const int16_t velocity) const;

	/**
	 * \brief Sets the target absolute position for the motor to move to.
	 *
	 * This movement is relative to the position of the motor when initialized or
	 * the position when it was most recently reset with motor_reset_zero_position.
	 *
	 * \note This function is equivalent to motor_set_absolute_target_position
	 *
	 * \param position
	 *        The absolute position to move to in the motor's encoder units
	 * \param velocity
	 *        The maximum allowable velocity for the movement
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	virtual int32_t move_absolute(const double position, const int32_t velocity) const;

	/**
	 * \brief Sets the relative target position for the motor to move to.
	 *
	 * This movement is relative to the current position of the motor as given in
	 * motor_get_position. Providing 10.0 as the position parameter would result in the motor
	 * moving clockwise 10 units, no matter what the current position is.
	 *
	 * \note This function is equivalent to motor_set_relative_target_position
	 *
	 * \param position
	 *        The relative position to move to in the motor's encoder units
	 * \param velocity
	 *        The maximum allowable velocity for the movement
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	virtual int32_t move_relative(const double position, const int32_t velocity) const;

	/**
	 * \brief Sets the velocity for the motor from -128 to 127.
	 *
	 * This velocity corresponds to different actual speeds depending on the gearset
	 * used for the motor. The velocity is held with PID to ensure consistent speed,
	 * as opposed to setting the motor's voltage.
	 *
	 * \note This operator is equivalent to set_target_velocity
	 *
	 * \param velocity
	 *        The new motor velocity from -127 to 127
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	virtual int32_t move_velocity(const int16_t velocity) const;

	/**
	 * \brief Sets the voltage for the motor from -128 to 127.
	 *
	 * This voltage is controlled by PWM, and does not immediately correspond to
	 * the value returned by get_voltage (which is in Volts)
	 *
	 * \note This function is equivalent to set_target_voltage
	 *
	 * \param voltage
	 *        The new PWM value from -127 to 127
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	virtual int32_t move_voltage(const int16_t voltage) const;

	/**
	 * \brief Sets the target absolute position for the motor to move to.
	 *
	 * This movement is relative to the position of the motor when initialized or
	 * the position when it was most recently reset with motor_reset_zero_position.
	 *
	 * \note This function is equivalent to motor_move_absolute
	 *
	 * \param port
	 *        The V5 port number from 1-21
	 * \param position
	 *        The absolute position to move to in the motor's encoder units
	 * \param velocity
	 *        The maximum allowable velocity for the movement
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_absolute_target_position(const double position, const int32_t velocity) const;

	/**
	 * \brief Sets the relative target position for the motor to move to.
	 *
	 * This movement is relative to the current position of the motor as given in
	 * motor_get_position. Providing 10.0 as the position parameter would result in the motor
	 * moving clockwise 10 units, no matter what the current position is.
	 *
	 * \note This function is equivalent to motor_move_relative
	 *
	 * \param position
	 *        The relative position to move to in the motor's encoder units
	 * \param velocity
	 *        The maximum allowable velocity for the movement
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_relative_target_position(const double position, const int32_t velocity) const;

	/**
	 * \brief Sets the velocity for the motor from -128 to 127.
	 *
	 * This velocity corresponds to different actual speeds depending on the gearset
	 * used for the motor. The velocity is held with PID to ensure consistent speed,
	 * as opposed to setting the motor's voltage.
	 *
	 * \note This function is equivalent to motor_move_velocity and motor_set
	 *
	 * \param velocity
	 *        The new motor velocity from -127 to 127
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_target_velocity(const int16_t velocity) const;

	/**
	 * \brief Sets the voltage for the motor from -128 to 127.
	 *
	 * This voltage is controlled by PWM, and does not immediately correspond to
	 * the value returned by motor_get_voltage (which is in Volts)
	 *
	 * \note This function is equivalent to motor_move_voltage
	 *
	 * \param voltage
	 *        The new PWM value from -127 to 127
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_target_voltage(const int16_t voltage) const;

	/**
	 * \brief Gets the target position set for the motor by the user
	 *
	 * \return The target position in its encoder units or PROS_ERR_F if the
	 *         operation failed, setting errno.
	 */
	double get_target_position(void) const;

	/**
	 * \brief Gets the velocity commanded to the motor by the user
	 *
	 * \return The commanded motor velocity from -128 to 127 or PROS_ERR if the
	 *         operation failed, setting errno.
	 */
	int32_t get_target_velocity(void) const;

	/******************************************************************************/
	/**                        Motor telemetry functions                         **/
	/**                                                                          **/
	/**    These functions allow programmers to collect telemetry from motors    **/
	/******************************************************************************/
	/**
	 * \brief Gets the actual velocity of the motor
	 *
	 * \return The motor's actual velocity in motor_encoder_units_e_t per second
	 *         or PROS_ERR_F if the operation failed, setting errno.
	 */
	double get_actual_velocity(void) const;

	/**
	 * \brief Gets the current drawn by the motor in mA
	 *
	 * \return The motor's current in mA or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t get_current_draw(void) const;

	/**
	 * \brief Gets the direction of movement for the motor
	 *
	 * \return 1 for moving in the positive direction, -1 for moving in the
	 *         negative direction, and PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t get_direction(void) const;

	/**
	 * \brief Gets the efficiency of the motor in percent
	 *
	 * An efficiency of 100% means that the motor is moving electrically while
	 * drawing no electrical power, and an efficiency of 0% means that the motor
	 * is drawing power but not moving.
	 *
	 * \return The motor's efficiency in percent or PROS_ERR_F if the operation
	 *         failed, setting errno.
	 */
	double get_efficiency(void) const;

	/**
	 * \brief Detect if the motor is drawing over its current limit
	 *
	 * \return 1 if the motor's current limit is being exceeded and 0 if the current
	 *         limit is not exceeded, or PROS_ERR if the operation failed, setting
	 *         errno.
	 */
	int32_t is_over_current(void) const;

	/**
	 * \brief Gets the zero velocity flag for the motor
	 *
	 * \note Although this function forwards data from the motor, the motor presently
	 * does not provide any value. This function returns PROS_ERR with errno set to ENOSYS
	 *
	 * \return 1 if the motor is not moving, 0 if the motor is moving, or PROS_ERR
	 *         if the operation failed, setting errno
	 */
	int32_t is_stopped(void) const;

	/**
	 * \brief Gets the zero position flag for the motor
	 *
	 * \note Although this function forwards data from the motor, the motor presently
	 * does not provide any value. This function returns PROS_ERR with errno set to ENOSYS
	 *
	 * \return 1 if the motor is at zero absolute position, 0 if the motor has
	 *         moved from its absolute zero, or PROS_ERR if the operation failed,
	 *         setting errno
	 */
	int32_t get_zero_position_flag(void) const;

	/**
	 * \brief Gets the faults experienced by the motor
	 *
	 * \return A currently unknown bitfield containing the motor's faults.
	 *         0b00000100 = Current Limit Hit
	 */
	uint32_t get_faults(void) const;

	/**
	 * \brief Gets the flags set by the motor's operation
	 *
	 * \return A currently unknown bitfield containing the motor's flags. These seem
	 *         to be unrelated to the individual motor_get_specific_flag functions
	 */
	uint32_t get_flags(void) const;

	/**
	 * \brief Gets the raw encoder count of the motor at a given timestamp
	 *
	 * \param timestamp[in]
	 *        A pointer to a time in milliseconds for which the encoder count will be returned.
	 *        If NULL, the timestamp at which the encoder count was read will not be supplied
	 *
	 * \return The raw encoder count at the given timestamp or PROS_ERR if the
	 *         operation failed.
	 */
	int32_t get_raw_position(uint32_t* const timestamp) const;

	/**
	 * \brief Gets the temperature limit flag for the motor
	 *
	 * \return 1 if the temperature limit is exceeded and 0 if the the
	 *         temperature is below the limit, or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t is_over_temp(void) const;

	/**
	 * \brief Gets the absolute position of the motor in its encoder units.
	 *
	 * \return The motor's absolute position in its encoder units or PROS_ERR_F
	 *         if the operation failed, setting errno.
	 */
	double get_position(void) const;

	/**
	 * \brief Gets the power drawn by the motor in Watts
	 *
	 * \return The motor's power draw in Watts or PROS_ERR_F if the operation
	 *         failed, setting errno.
	 */
	double get_power(void) const;

	/**
	 * \brief Gets the temperature of the motor in degrees Celsius
	 *
	 * \return The motor's temperature in degrees Celsius or PROS_ERR_F if the
	 *         operation failed, setting errno.
	 */
	double get_temperature(void) const;

	/**
	 * \brief Gets the torque generated by the motor in Newton Metres (Nm)
	 *
	 * \return The motor's torque in NM or PROS_ERR_F if the operation failed,
	 *         setting errno.
	 */
	double get_torque(void) const;

	/**
	 * \brief Gets the voltage delivered to the motor in V
	 *
	 * \return The motor's voltage in V or PROS_ERR_F if the operation failed,
	 *         setting errno.
	 */
	double get_voltage(void) const;

	/******************************************************************************/
	/**                      Motor configuration functions                       **/
	/**                                                                          **/
	/**  These functions allow programmers to configure the behavior of motors   **/
	/******************************************************************************/

	/**
	 * \brief Sets the position for the motor in its encoder units.
	 *
	 * This will be the future reference point for the motor's "absolute" position.
	 *
	 * \param position
	 *        The new reference position in its encoder units
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t reset_position(const double position) const;

	/**
	 * \brief Sets the "absolute" zero position of the motor to its current position.
	 *
	 * This call is roughly equivalent to calling motor_reset_position(port, 0);
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *           setting errno.
	 */
	int32_t reset_zero_position(void) const;

	/**
	 * \brief Sets one of motor_brake_mode_e_t to the motor
	 *
	 * \param mode
	 *        The motor_brake_mode_e_t to set for the motor
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_brake_mode(const motor_brake_mode_e_t mode) const;

	/**
	 * \brief Sets the current limit for the motor in mA
	 *
	 * \param limit
	 *        The new current limit in mA
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_current_limit(const int32_t limit) const;

	/**
	 * \brief Sets one of motor_encoder_units_e_t for the motor encoder
	 *
	 * \param units
	 *        The new motor encoder units
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_encoder_units(const motor_encoder_units_e_t units) const;

	/**
	 * \brief Sets one of motor_gearset_e_t for the motor
	 *
	 * \param gearset
	 *        The new motor gearset
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_gearing(const motor_gearset_e_t gearset) const;

	/**
	 * \brief Sets the reverse flag for the motor.
	 *
	 * This will invert its movements and the values returned for its position.
	 *
	 * \param reverse
	 *        True reverses the motor, false is default
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_reverse(const bool reverse) const;

	/**
	 * \brief Sets the voltage limit for the motor in Volts
	 *
	 * \param limit
	 *        The new voltage limit in Volts
	 *
	 * \return 1 if the operation was successful or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t set_voltage_limit(const int32_t limit) const;

	/**
	 * \brief Gets the brake mode of the motor
	 *
	 * \return One of motor_brake_mode_e_t, according to what was set for the motor,
	 *          or E_MOTOR_BRAKE_INVALID if the operation failed, setting errno.
	 */
	motor_brake_mode_e_t get_brake_mode(void) const;

	/**
	 * \brief Gets the current limit for the motor in mA
	 *
	 * The default value is 2500 mA.
	 *
	 * \return The motor's current limit in mA or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t get_current_limit(void) const;

	/**
	 * \brief Gets the encoder units set for the motor
	 *
	 * \return One of motor_encoder_units_e_t according to what is set for the motor
	 *         or E_MOTOR_ENCODER_INVALID if the operation failed.
	 */
	motor_encoder_units_e_t get_encoder_units(void) const;

	/**
	 * \brief Gets the gearset that was set for the motor
	 *
	 * \return One of motor_gearset_e_t according to what is set for the motor,
	 *         or E_GEARSET_INVALID if the operation failed.
	 */
	motor_gearset_e_t get_gearing(void) const;

	/**
	 * \brief Gets the operation direction of the motor as set by the user
	 *
	 * \return 1 if the motor has been reversed and 0 if the motor was not reversed,
	 *         or PROS_ERR if the operation failed, setting errno.
	 */
	int32_t get_reverse(void) const;

	/**
	 * \brief Gets the voltage limit set by the user
	 *
	 * Default value is 0V, which I presume means that the limit does not exist.
	 *
	 * \return The motor's voltage limit in V or PROS_ERR if the operation failed,
	 *         setting errno.
	 */
	int32_t get_voltage_limit(void) const;

	private:
	const uint8_t _port;
};

inline namespace literals {
	const Motor operator"" _m(const unsigned long long int m);
	const Motor operator"" _rm(const unsigned long long int m);
}
}
#endif
