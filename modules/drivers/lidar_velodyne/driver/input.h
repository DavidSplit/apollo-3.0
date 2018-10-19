/******************************************************************************
 * Modification Copyright 2017 The Apollo Authors. All Rights Reserved.
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

/* -*- mode: C++ -*-
 *
 *  Copyright (C) 2007 Austin Robot Technology, Yaxin Liu, Patrick Beeson
 *  Copyright (C) 2009, 2010 Austin Robot Technology, Jack O'Quin
 *  Copyright (C) 2015, Jack O'Quin
 *
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 */

/** @file
 *
 *  Velodyne 3D LIDAR data input classes
 *
 *    These classes provide raw Velodyne LIDAR input packets from
 *    either a live socket interface or a previously-saved PCAP dump
 *    file.
 *
 *  Classes:
 *
 *     velodyne::Input -- base class for accessing the data
 *                      independently of its source
 *
 *     velodyne::InputSocket -- derived class reads live data from the
 *                      device via a UDP socket
 *
 *     velodyne::InputPCAP -- derived class provides a similar interface
 *                      from a PCAP dump file
 */

#ifndef MODULES_DRIVERS_LIDAR_VELODYNE_COMMON_INPUT_H_
#define MODULES_DRIVERS_LIDAR_VELODYNE_COMMON_INPUT_H_

#include <netinet/in.h>
#include <unistd.h>
#include <cstdio>

#include <string>

#include "pcap/pcap.h"
#include "ros/ros.h"
#include "velodyne_msgs/VelodynePacket.h"

namespace apollo {
namespace drivers {
namespace lidar_velodyne {

static uint16_t DATA_PORT_NUMBER = 2368;      // default data port
static uint16_t POSITION_PORT_NUMBER = 8308;  // default position port

/** @brief Velodyne input base class */
class Input {
 public:
  Input(ros::NodeHandle private_nh, uint16_t port);
  virtual ~Input() {}

  /** @brief Read one Velodyne packet.
   *
   * @param pkt points to VelodynePacket message
   *
   * @returns 0 if successful,
   *          -1 if end of file
   *          > 0 if incomplete packet (is this possible?)
   */
  virtual int getPacket(velodyne_msgs::VelodynePacket *pkt,
                        const double time_offset) = 0;

 protected:
  ros::NodeHandle private_nh_;
  uint16_t port_;
  std::string devip_str_;
};

/** @brief Live Velodyne input from socket. */
class InputSocket : public Input {
 public:
  explicit InputSocket(ros::NodeHandle private_nh,
                       uint16_t port = DATA_PORT_NUMBER);
  virtual ~InputSocket();

  virtual int getPacket(velodyne_msgs::VelodynePacket *pkt,
                        const double time_offset);
  void setDeviceIP(const std::string &ip);

 private:
  int sockfd_;
  in_addr devip_;
};

/** @brief Velodyne input from PCAP dump file.
 *
 * Dump files can be grabbed by libpcap, Velodyne's DSR software,
 * ethereal, wireshark, tcpdump, or the \ref vdump_command.
 */
class InputPCAP : public Input {
 public:
  InputPCAP(ros::NodeHandle private_nh, uint16_t port = DATA_PORT_NUMBER,
            double packet_rate = 0.0, std::string filename = "",
            bool read_once = false, bool read_fast = false,
            double repeat_delay = 0.0);
  virtual ~InputPCAP();

  virtual int getPacket(velodyne_msgs::VelodynePacket *pkt,
                        const double time_offset);
  void setDeviceIP(const std::string &ip);

 private:
  ros::Rate packet_rate_;
  std::string filename_;
  pcap_t *pcap_;
  bpf_program pcap_packet_filter_;
  char errbuf_[PCAP_ERRBUF_SIZE];
  bool empty_;
  bool read_once_;
  bool read_fast_;
  double repeat_delay_;
};

}  // namespace lidar_velodyne
}  // namespace drivers
}  // namespace apollo

#endif  // MODULES_DRIVERS_LIDAR_VELODYNE_COMMON_INPUT_H_
