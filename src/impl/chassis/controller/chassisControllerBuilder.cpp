/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/api/odometry/threeEncoderOdometry.hpp"
#include "okapi/api/chassis/model/threeEncoderSkidSteerModel.hpp"
#include <stdexcept>

namespace okapi {
ChassisControllerBuilder::ChassisControllerBuilder(const std::shared_ptr<Logger> &ilogger)
  : logger(ilogger) {
}

ChassisControllerBuilder &ChassisControllerBuilder::withMotors(const Motor &ileft,
                                                               const Motor &iright) {
  return withMotors(std::make_shared<Motor>(ileft), std::make_shared<Motor>(iright));
}

ChassisControllerBuilder &ChassisControllerBuilder::withMotors(const MotorGroup &ileft,
                                                               const MotorGroup &iright) {
  return withMotors(std::make_shared<MotorGroup>(ileft), std::make_shared<MotorGroup>(iright));
}

ChassisControllerBuilder &
ChassisControllerBuilder::withMotors(const std::shared_ptr<AbstractMotor> &ileft,
                                     const std::shared_ptr<AbstractMotor> &iright) {
  hasMotors = true;
  isSkidSteer = true;
  skidSteerMotors = {ileft, iright};

  if (!sensorsSetByUser) {
    leftSensor = ileft->getEncoder();
    rightSensor = iright->getEncoder();
  }

  return *this;
}

ChassisControllerBuilder &ChassisControllerBuilder::withMotors(const Motor &itopLeft,
                                                               const Motor &itopRight,
                                                               const Motor &ibottomRight,
                                                               const Motor &ibottomLeft) {
  return withMotors(std::make_shared<Motor>(itopLeft),
                    std::make_shared<Motor>(itopRight),
                    std::make_shared<Motor>(ibottomRight),
                    std::make_shared<Motor>(ibottomLeft));
}

ChassisControllerBuilder &ChassisControllerBuilder::withMotors(const MotorGroup &itopLeft,
                                                               const MotorGroup &itopRight,
                                                               const MotorGroup &ibottomRight,
                                                               const MotorGroup &ibottomLeft) {
  return withMotors(std::make_shared<MotorGroup>(itopLeft),
                    std::make_shared<MotorGroup>(itopRight),
                    std::make_shared<MotorGroup>(ibottomRight),
                    std::make_shared<MotorGroup>(ibottomLeft));
}

ChassisControllerBuilder &
ChassisControllerBuilder::withMotors(const std::shared_ptr<AbstractMotor> &itopLeft,
                                     const std::shared_ptr<AbstractMotor> &itopRight,
                                     const std::shared_ptr<AbstractMotor> &ibottomRight,
                                     const std::shared_ptr<AbstractMotor> &ibottomLeft) {
  hasMotors = true;
  isSkidSteer = false;
  xDriveMotors = {itopLeft, itopRight, ibottomRight, ibottomLeft};

  if (!sensorsSetByUser) {
    leftSensor = itopLeft->getEncoder();
    rightSensor = itopRight->getEncoder();
  }

  return *this;
}

ChassisControllerBuilder &ChassisControllerBuilder::withSensors(const ADIEncoder &ileft,
                                                                const ADIEncoder &iright) {
  return withSensors(std::make_shared<ADIEncoder>(ileft), std::make_shared<ADIEncoder>(iright));
}

ChassisControllerBuilder &ChassisControllerBuilder::withSensors(const okapi::ADIEncoder &ileft,
                                                                const okapi::ADIEncoder &iright,
                                                                const okapi::ADIEncoder &imiddle) {
  return withSensors(std::make_shared<ADIEncoder>(ileft),
                     std::make_shared<ADIEncoder>(iright),
                     std::make_shared<ADIEncoder>(imiddle));
}

ChassisControllerBuilder &ChassisControllerBuilder::withSensors(const IntegratedEncoder &ileft,
                                                                const IntegratedEncoder &iright) {
  return withSensors(std::make_shared<IntegratedEncoder>(ileft),
                     std::make_shared<IntegratedEncoder>(iright));
}

ChassisControllerBuilder &
ChassisControllerBuilder::withSensors(const okapi::IntegratedEncoder &ileft,
                                      const okapi::IntegratedEncoder &iright,
                                      const okapi::ADIEncoder &imiddle) {
  return withSensors(std::make_shared<IntegratedEncoder>(ileft),
                     std::make_shared<IntegratedEncoder>(iright),
                     std::make_shared<ADIEncoder>(imiddle));
}

ChassisControllerBuilder &
ChassisControllerBuilder::withSensors(const std::shared_ptr<ContinuousRotarySensor> &ileft,
                                      const std::shared_ptr<ContinuousRotarySensor> &iright) {
  sensorsSetByUser = true;
  leftSensor = ileft;
  rightSensor = iright;
  return *this;
}

ChassisControllerBuilder &ChassisControllerBuilder::withSensors(
  const std::shared_ptr<okapi::ContinuousRotarySensor> &ileft,
  const std::shared_ptr<okapi::ContinuousRotarySensor> &iright,
  const std::shared_ptr<okapi::ContinuousRotarySensor> &imiddle) {
  sensorsSetByUser = true;
  leftSensor = ileft;
  rightSensor = iright;
  middleSensor = imiddle;
  return *this;
}

ChassisControllerBuilder &
ChassisControllerBuilder::withGains(const IterativePosPIDController::Gains &idistanceGains,
                                    const IterativePosPIDController::Gains &iturnGains) {
  return withGains(idistanceGains, iturnGains, iturnGains);
}

ChassisControllerBuilder &
ChassisControllerBuilder::withGains(const IterativePosPIDController::Gains &idistanceGains,
                                    const IterativePosPIDController::Gains &iturnGains,
                                    const IterativePosPIDController::Gains &iangleGains) {
  hasGains = true;
  distanceGains = idistanceGains;
  turnGains = iturnGains;
  angleGains = iangleGains;
  return *this;
}

ChassisControllerBuilder &
ChassisControllerBuilder::withDerivativeFilters(std::unique_ptr<Filter> idistanceFilter,
                                                std::unique_ptr<Filter> iturnFilter,
                                                std::unique_ptr<Filter> iangleFilter) {
  distanceFilter = std::move(idistanceFilter);
  turnFilter = std::move(iturnFilter);
  angleFilter = std::move(iangleFilter);
  return *this;
}

ChassisControllerBuilder &
ChassisControllerBuilder::withTimeUtilFactory(const TimeUtilFactory &itimeUtilFactory) {
  controllerTimeUtilFactory = itimeUtilFactory;
  return *this;
}

ChassisControllerBuilder &ChassisControllerBuilder::withOdometry(const QLength &imoveThreshold,
                                                                 const QAngle &iturnThreshold,
                                                                 const QSpeed &iwheelVelDelta) {
  hasOdom = true;
  odometry = nullptr;
  moveThreshold = imoveThreshold;
  turnThreshold = iturnThreshold;
  wheelVelDelta = iwheelVelDelta;
  return *this;
}

ChassisControllerBuilder &
ChassisControllerBuilder::withOdometry(std::unique_ptr<Odometry> iodometry,
                                       const QLength &imoveThreshold,
                                       const QAngle &iturnThreshold) {
  if (iodometry == nullptr) {
    LOG_ERROR_S("ChassisControllerBuilder: Odometry cannot be null.");
    throw std::runtime_error("ChassisControllerBuilder: Odometry cannot be null.");
  }

  hasOdom = true;
  odometry = std::move(iodometry);
  moveThreshold = imoveThreshold;
  turnThreshold = iturnThreshold;
  return *this;
}

ChassisControllerBuilder &
ChassisControllerBuilder::withGearset(const AbstractMotor::GearsetRatioPair &igearset) {
  gearset = igearset;

  if (!maxVelSetByUser) {
    maxVelocity = toUnderlyingType(igearset.internalGearset);
  }

  return *this;
}

ChassisControllerBuilder &ChassisControllerBuilder::withDimensions(const ChassisScales &iscales) {
  scales = iscales;
  return *this;
}

ChassisControllerBuilder &ChassisControllerBuilder::withMaxVelocity(const double imaxVelocity) {
  maxVelSetByUser = true;
  maxVelocity = imaxVelocity;
  return *this;
}

ChassisControllerBuilder &ChassisControllerBuilder::withMaxVoltage(const double imaxVoltage) {
  maxVoltage = imaxVoltage;
  return *this;
}

ChassisControllerBuilder &
ChassisControllerBuilder::withLogger(const std::shared_ptr<Logger> &ilogger) {
  controllerLogger = ilogger;
  return *this;
}

std::shared_ptr<ChassisController> ChassisControllerBuilder::build() {
  if (!hasMotors) {
    LOG_ERROR_S("ChassisControllerBuilder: No motors given.");
    throw std::runtime_error("ChassisControllerBuilder: No motors given.");
  }

  if (hasOdom) {
    if (hasGains) {
      return buildOCCPID();
    } else {
      return buildOCCI();
    }
  } else {
    if (hasGains) {
      return buildCCPID();
    } else {
      return buildCCI();
    }
  }
}

std::shared_ptr<OdomChassisController> ChassisControllerBuilder::buildOdometry() {
  if (!hasMotors) {
    LOG_ERROR_S("ChassisControllerBuilder: No motors given.");
    throw std::runtime_error("ChassisControllerBuilder: No motors given.");
  }

  if (!hasOdom) {
    LOG_ERROR_S("ChassisControllerBuilder: No odometry information given.");
    throw std::runtime_error("ChassisControllerBuilder: No odometry information given.");
  }

  if (hasGains) {
    return buildOCCPID();
  } else {
    return buildOCCI();
  }
}

std::shared_ptr<OdomChassisControllerPID> ChassisControllerBuilder::buildOCCPID() {
  if (isSkidSteer) {
    auto model = makeSkidSteerModel();

    if (odometry == nullptr) {
      if (middleSensor == nullptr) {
        odometry = std::make_unique<Odometry>(
          TimeUtilFactory::create(), model, scales, wheelVelDelta, controllerLogger);
      } else {
        odometry = std::make_unique<ThreeEncoderOdometry>(
          TimeUtilFactory::create(), model, scales, wheelVelDelta, controllerLogger);
      }
    }

    auto out = std::make_shared<OdomChassisControllerPID>(
      TimeUtilFactory::create(),
      model,
      std::move(odometry),
      std::make_unique<IterativePosPIDController>(distanceGains,
                                                  controllerTimeUtilFactory.create(),
                                                  std::move(distanceFilter),
                                                  controllerLogger),
      std::make_unique<IterativePosPIDController>(
        angleGains, controllerTimeUtilFactory.create(), std::move(angleFilter), controllerLogger),
      std::make_unique<IterativePosPIDController>(
        turnGains, controllerTimeUtilFactory.create(), std::move(turnFilter), controllerLogger),
      gearset,
      scales,
      moveThreshold,
      turnThreshold,
      controllerLogger);
    out->startThread();
    return out;
  } else {
    LOG_ERROR_S("ChassisControllerBuilder: Odometry only support with skid-steer layout.");
    throw std::runtime_error(
      "ChassisControllerBuilder: Odometry only support with skid-steer layout.");
  }
}

std::shared_ptr<OdomChassisControllerIntegrated> ChassisControllerBuilder::buildOCCI() {
  if (isSkidSteer) {
    auto model = makeSkidSteerModel();

    if (odometry == nullptr) {
      if (middleSensor == nullptr) {
        odometry = std::make_unique<Odometry>(
          TimeUtilFactory::create(), model, scales, wheelVelDelta, controllerLogger);
      } else {
        odometry = std::make_unique<ThreeEncoderOdometry>(
          TimeUtilFactory::create(), model, scales, wheelVelDelta, controllerLogger);
      }
    }

    auto out = std::make_shared<OdomChassisControllerIntegrated>(
      TimeUtilFactory::create(),
      model,
      std::move(odometry),
      std::make_unique<AsyncPosIntegratedController>(skidSteerMotors.left,
                                                     gearset,
                                                     toUnderlyingType(gearset.internalGearset),
                                                     controllerTimeUtilFactory.create(),
                                                     controllerLogger),
      std::make_unique<AsyncPosIntegratedController>(skidSteerMotors.right,
                                                     gearset,
                                                     toUnderlyingType(gearset.internalGearset),
                                                     controllerTimeUtilFactory.create(),
                                                     controllerLogger),
      gearset,
      scales,
      moveThreshold,
      turnThreshold,
      controllerLogger);
    return out;
  } else {
    LOG_ERROR_S("ChassisControllerBuilder: Odometry only support with skid-steer layout.");
    throw std::runtime_error(
      "ChassisControllerBuilder: Odometry only support with skid-steer layout.");
  }
}

std::shared_ptr<ChassisControllerPID> ChassisControllerBuilder::buildCCPID() {
  if (isSkidSteer) {
    auto out = std::make_shared<ChassisControllerPID>(
      TimeUtilFactory::create(),
      makeSkidSteerModel(),
      std::make_unique<IterativePosPIDController>(distanceGains,
                                                  controllerTimeUtilFactory.create(),
                                                  std::move(distanceFilter),
                                                  controllerLogger),
      std::make_unique<IterativePosPIDController>(
        angleGains, controllerTimeUtilFactory.create(), std::move(angleFilter), controllerLogger),
      std::make_unique<IterativePosPIDController>(
        turnGains, controllerTimeUtilFactory.create(), std::move(turnFilter), controllerLogger),
      gearset,
      scales,
      controllerLogger);
    out->startThread();
    return out;
  } else {
    auto out = std::make_shared<ChassisControllerPID>(
      TimeUtilFactory::create(),
      makeXDriveModel(),
      std::make_unique<IterativePosPIDController>(distanceGains,
                                                  controllerTimeUtilFactory.create(),
                                                  std::move(distanceFilter),
                                                  controllerLogger),
      std::make_unique<IterativePosPIDController>(
        angleGains, controllerTimeUtilFactory.create(), std::move(angleFilter), controllerLogger),
      std::make_unique<IterativePosPIDController>(
        turnGains, controllerTimeUtilFactory.create(), std::move(turnFilter), controllerLogger),
      gearset,
      scales,
      controllerLogger);
    out->startThread();
    return out;
  }
}

std::shared_ptr<ChassisControllerIntegrated> ChassisControllerBuilder::buildCCI() {
  if (isSkidSteer) {
    auto out = std::make_shared<ChassisControllerIntegrated>(
      TimeUtilFactory::create(),
      makeSkidSteerModel(),
      std::make_unique<AsyncPosIntegratedController>(skidSteerMotors.left,
                                                     gearset,
                                                     toUnderlyingType(gearset.internalGearset),
                                                     controllerTimeUtilFactory.create(),
                                                     controllerLogger),
      std::make_unique<AsyncPosIntegratedController>(skidSteerMotors.right,
                                                     gearset,
                                                     toUnderlyingType(gearset.internalGearset),
                                                     controllerTimeUtilFactory.create(),
                                                     controllerLogger),
      gearset,
      scales,
      controllerLogger);
    return out;
  } else {
    auto out = std::make_shared<ChassisControllerIntegrated>(
      TimeUtilFactory::create(),
      makeXDriveModel(),
      std::make_unique<AsyncPosIntegratedController>(skidSteerMotors.left,
                                                     gearset,
                                                     toUnderlyingType(gearset.internalGearset),
                                                     controllerTimeUtilFactory.create(),
                                                     controllerLogger),
      std::make_unique<AsyncPosIntegratedController>(skidSteerMotors.right,
                                                     gearset,
                                                     toUnderlyingType(gearset.internalGearset),
                                                     controllerTimeUtilFactory.create(),
                                                     controllerLogger),
      gearset,
      scales,
      controllerLogger);
    return out;
  }
}

std::shared_ptr<SkidSteerModel> ChassisControllerBuilder::makeSkidSteerModel() {
  if (middleSensor != nullptr) {
    return std::make_shared<ThreeEncoderSkidSteerModel>(skidSteerMotors.left,
                                                        skidSteerMotors.right,
                                                        leftSensor,
                                                        middleSensor,
                                                        rightSensor,
                                                        maxVelocity,
                                                        maxVoltage);
  } else {
    return std::make_shared<SkidSteerModel>(skidSteerMotors.left,
                                            skidSteerMotors.right,
                                            leftSensor,
                                            rightSensor,
                                            maxVelocity,
                                            maxVoltage);
  }
}

std::shared_ptr<XDriveModel> ChassisControllerBuilder::makeXDriveModel() {
  return std::make_shared<XDriveModel>(xDriveMotors.topLeft,
                                       xDriveMotors.topRight,
                                       xDriveMotors.bottomRight,
                                       xDriveMotors.bottomLeft,
                                       leftSensor,
                                       rightSensor,
                                       maxVelocity,
                                       maxVoltage);
}
} // namespace okapi