/*
Copyright 2021, Yang Luo"
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

@Author
Yang Luo, PHD
Shenyang Institute of Automation, Chinese Academy of Sciences.
 email: luoyang@sia.cn

@Created on: 2021.04.06
*/

#include "sri/sensorcomm.h"

namespace SRI {

    SensorComm::SensorComm() {

    }

    SensorComm::~SensorComm() {
    }

    bool SensorComm::isValid() {
        return false;
    }

    bool SensorComm::initialize() {
        return false;
    }

    size_t SensorComm::write(std::vector<char> &buf) {
        return 0;
    }

    size_t SensorComm::read(std::vector<char> &buf) {
        return 0;
    }

} //namespace SRI


