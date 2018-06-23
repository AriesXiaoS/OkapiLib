/**
 * @author Ryan Benasutti, WPI
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "okapi/impl/filter/velMathFactory.hpp"
#include "okapi/api/filter/averageFilter.hpp"
#include "okapi/impl/util/timer.hpp"

namespace okapi {
VelMath VelMathFactory::create(const double iticksPerRev) {
  return VelMath(iticksPerRev, std::make_shared<AverageFilter<2>>(), std::make_unique<Timer>());
}

VelMath VelMathFactory::create(const double iticksPerRev, std::shared_ptr<Filter> ifilter) {
  return VelMath(iticksPerRev, ifilter, std::make_unique<Timer>());
}
} // namespace okapi
