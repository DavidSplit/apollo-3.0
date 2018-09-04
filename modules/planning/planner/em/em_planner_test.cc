/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "modules/planning/planner/em/em_planner.h"

#include "gtest/gtest.h"

#include "modules/common/proto/drive_state.pb.h"
#include "modules/common/proto/pnc_point.pb.h"
#include "modules/map/hdmap/hdmap_common.h"
#include "modules/map/hdmap/hdmap_util.h"
#include "modules/planning/common/planning_gflags.h"

namespace apollo {
namespace planning {

TEST(EMPlannerTest, GenerateFallbackSpeedProfile) {
  EMPlanner em;
  ReferenceLineInfo reference_line_info;
  auto speed_data = em.GenerateFallbackSpeedProfile(reference_line_info);
  EXPECT_FALSE(speed_data.Empty());

  common::VehicleState vehicle_state;
  common::TrajectoryPoint adc_planning_point;
  ReferenceLine reference_line;
  hdmap::RouteSegments segments;
  adc_planning_point.set_v(FLAGS_polynomial_speed_fallback_velocity + 0.1);
  ReferenceLineInfo reference_line_info2(vehicle_state, adc_planning_point,
                                         reference_line, segments);
  auto speed_data2 = em.GenerateFallbackSpeedProfile(reference_line_info);
  EXPECT_FALSE(speed_data2.Empty());
}

}  // namespace planning
}  // namespace apollo
