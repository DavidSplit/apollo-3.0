#!/usr/bin/env bash

###############################################################################
# Copyright 2017 The Apollo Authors. All Rights Reserved.
# Modifications Copyright (c) 2018 LG Electronics, Inc. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################


DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source "${DIR}/apollo_base.sh"

# run function from apollo_base.sh
# run command_name module_name
function start() {
	echo "start"
	python modules/tools/navigation/simulator/navigation_view_backend.py &
}

function stop() {
    echo "stop"
    pkill -SIGKILL -f navigation_view_backend.py
}

case $1 in
start)
    start
    ;;
help)
    echo "$0 start|stop|help"
    ;;
stop)
    stop
    ;;
*)
    stop
    start
    ;;
esac
