/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 * Modifications Copyright (c) 2018 LG Electronics, Inc. All Rights Reserved.
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

/**
 * @file
 **/

#ifndef MODULES_PLANNING_TOOLKITS_DECIDERS_TRAFFIC_RULE_H_
#define MODULES_PLANNING_TOOLKITS_DECIDERS_TRAFFIC_RULE_H_

#include <string>

#include "modules/planning/proto/traffic_rule_config.pb.h"

#include "modules/planning/common/frame.h"
#include "modules/planning/common/reference_line_info.h"

namespace apollo {
namespace planning {

class TrafficRule {
 public:
  explicit TrafficRule(const TrafficRuleConfig& config) : config_(config) {}
  virtual ~TrafficRule() = default;
  virtual TrafficRuleConfig::RuleId Id() const { return config_.rule_id(); }
  const TrafficRuleConfig& GetConfig() const { return config_; }
  virtual common::Status ApplyRule(Frame* const frame,
                         ReferenceLineInfo* const reference_line_info) = 0;

 protected:
  TrafficRuleConfig config_;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_TOOLKITS_DECIDERS_TRAFFIC_RULE_H_
