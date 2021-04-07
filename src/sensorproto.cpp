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


#include "sri/sensorproto.h"

namespace SRI {
    // static member must be definition outside class
    std::shared_ptr<SensorProto> SensorProto::_instance;

    std::shared_ptr<SensorProto> SensorProto::getInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&]() {
            _instance.reset(new SensorProto);
        });

        return _instance->shared_from_this();
    }


} //namespace SRI
