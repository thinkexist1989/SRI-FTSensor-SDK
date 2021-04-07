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

#ifndef SRI_FTSENSOR_SDK_SRI_SENSOR_H
#define SRI_FTSENSOR_SDK_SRI_SENSOR_H

#include <sri/sensorcomm.h>
#include <sri/commethernet.h>
#include <sri/types.h>

#include <memory>


namespace SRI {
    class FTSensor {
    public:
        FTSensor();


    private:
        std::shared_ptr<SensorComm> commPtr;

    }; // class FTSensor
} //namespace SRI


#endif //SRI_FTSENSOR_SDK_SRI_SENSOR_H
