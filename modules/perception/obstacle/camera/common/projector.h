/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
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

#ifndef MODULES_PERCEPTION_OBSTACLE_CAMERA_COMMON_PROJECTOR_H_
#define MODULES_PERCEPTION_OBSTACLE_CAMERA_COMMON_PROJECTOR_H_

#include <Eigen/Core>

#include <string>
#include <vector>

namespace apollo {
namespace perception {

class BaseProjector {
 public:
  virtual ~BaseProjector() = default;
  virtual bool project(std::vector<float>* feature) = 0;
};

class MatrixProjector : public BaseProjector {
 public:
  explicit MatrixProjector(const std::string& weight_file);

  bool project(std::vector<float>* feature) override;

 private:
  Eigen::MatrixXf matrix_;
};

}  // namespace perception
}  // namespace apollo

#endif  // MODULES_PERCEPTION_OBSTACLE_CAMERA_COMMON_PROJECTOR_H_
