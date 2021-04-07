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

#ifndef SRI_FTSENSOR_SDK_SENSORCOMM_H
#define SRI_FTSENSOR_SDK_SENSORCOMM_H

#include <vector>

namespace SRI {
    class SensorComm {
    public:
        virtual bool isValid();        // Get the valid status of the sensor

        virtual bool initialize();     // Initialize the communication

        /// Write Data Buffer to Sensor
        /// \param buf The data need to send
        /// \return       The number of chars have been sent
        virtual size_t write(std::vector<char>& buf);

        /// Read Data Buffer from Sensor
        /// \param[out] buf The data received
        /// \return            The number of chars have been received
        virtual size_t read(std::vector<char>& buf);

        SensorComm();

        virtual ~SensorComm();     // Pure virtual deconstructor for polymorphism

        bool _validStatus = false;     // The status of the communication with the sensor

    }; // class SensorComm
} //namespace SRI


#endif //SRI_FTSENSOR_SDK_SENSORCOMM_H
