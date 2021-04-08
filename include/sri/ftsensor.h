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
#include <sri/types.h>

#include <memory>
#include <regex>


namespace SRI {
    class FTSensor {
    public:
        explicit FTSensor(SensorComm* pcomm);

        IpAddr      getIpAddress();
        bool        setIpAddress(const IpAddr &ip);

        MacAddr     getMacAddress();
        bool        setMacAddress(const MacAddr &mac);

        GateAddr    getGateWay();
        bool        setGateWay(const GateAddr &gate);

        NetMask     getNetMask();
        bool        setNetMask(const NetMask &mask);

        Gains       getChannelGains();

        SampleRate  getSamplingRate();
        bool        setSamplingRate(const SampleRate rate);

        Voltages    getExcitationVoltages();

        Sensitivities getSensorSensitivities();
        bool          setSensorSensitivities(const Sensitivities &sens);

        Offsets     getAmplifierZeroOffsets();
        bool        setAmplifierZeroOffsets(const Offsets &offsets);

        RTDataMode  getRealTimeDataMode();
        bool        setRealTimeDataMode(const RTDataMode &rtDataMode);

        RTDataValid getRealTimeDataValid();
        bool        setRealTimeDataValid(const RTDataValid &rtDataValid);

        RTData      getRealTimeDataOnce();

        void        startRealTimeDataRepeatedly(); // this function need a callback function
        void        stopRealTimeDataRepeatedly();

    public: // for test, need to be change to private
        std::shared_ptr<SensorComm> commPtr; //store the polymorphic pointer of communication
        bool isRepeatedly = false; // if start RT Data Repeatedly, set true

        /// Generate Command Buffer
        /// \param[in] Command      The CMD such as UARTCFG.
        /// \param[in] parameter    The parameters of the command.
        /// \return                 command buffer(string format).
        std::string generateCommandBuffer(const std::string &command, const std::string &parameter);

        /// Extract Response Buffer
        /// \param[in] recvbuf          The reference of received buffer.
        /// \param[in] expect_command   The expected command.
        /// \return                     The response from sensor(string format)
        std::string extractResponseBuffer(std::vector<char> &buf,
                                          const std::string &command,
                                          const std::string &parameter);


    }; // class FTSensor
} //namespace SRI


#endif //SRI_FTSENSOR_SDK_SRI_SENSOR_H
