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


#include "sri/ftsensor.h"
#include <iostream>
#include <algorithm>

namespace SRI {

    FTSensor::FTSensor(SensorComm *pcomm) : commPtr(pcomm) {
//        commPtr->initialize();
    }

    std::string FTSensor::generateCommandBuffer(const std::string &command,
                                                const std::string &parameter) {
        return AT + command + "=" + parameter + "\r\n";
    }

    std::string FTSensor::extractResponseBuffer(std::vector<char> &buf,
                                                const std::string &command,
                                                const std::string &parameter) {
        std::string s(buf.data(), buf.size());

        if (s.find(ACK) != 0)
            return "";
        if (s.find(command) == s.npos)
            return "";

        if(parameter == "?")
            return s.substr(s.find("=") + 1, s.find("\r\n"));
        else
            return s.substr(s.find("$") + 1, s.find("\r\n"));

    }

    IpAddr FTSensor::getIpAddress() {
        return SRI::IpAddr();
    }

} //namespace SRI