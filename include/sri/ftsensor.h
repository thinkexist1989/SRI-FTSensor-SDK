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

#include <iostream>
#include <algorithm>
#include <numeric> // std::accumulate
#include <thread>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/crc.hpp> //crc32

#define DELAY_US 500 //tcp delay in us


namespace SRI {
    class FTSensor {
    public:
        explicit FTSensor(SensorComm *pcomm);

        IpAddr getIpAddress();

        bool setIpAddress(const IpAddr &ip);

        MacAddr getMacAddress();

        bool setMacAddress(const MacAddr &mac);

        GateAddr getGateWay();

        bool setGateWay(const GateAddr &gate);

        NetMask getNetMask();

        bool setNetMask(const NetMask &mask);

        Gains getChannelGains();

        SampleRate getSamplingRate();

        bool setSamplingRate(SampleRate rate);

        Voltages getExcitationVoltages();

        Sensitivities getSensorSensitivities();

        bool setSensorSensitivities(const Sensitivities &sens);

        Offsets getAmplifierZeroOffsets();

        bool setAmplifierZeroOffsets(const Offsets &offsets);

        RTDataMode getRealTimeDataMode();

        bool setRealTimeDataMode(const RTDataMode &rtDataMode);

        RTDataValid getRealTimeDataValid();

        bool setRealTimeDataValid(const RTDataValid &rtDataValid);

        template<typename T>
        std::vector<RTData<T>>
        getRealTimeDataOnce(const RTDataMode &rtMode = RTDataMode(), const RTDataValid &rtValid = "SUM") {
            commPtr->write("AT+GOD\r\n");
            while (commPtr->available() == 0) {
                std::this_thread::sleep_for(std::chrono::microseconds(DELAY_US));
            }
            std::vector<int8_t> recvbuf;
            commPtr->read(recvbuf);

            //parse the received buffer
            uint32_t paritybit = 1;
            if (rtValid == "SUM") {
                paritybit = 1;
            } else if (rtValid == "CRC32") {
                paritybit = 4;
            }

            if (((uint8_t)recvbuf[0] != 0xAA) || ((uint8_t)recvbuf[1] != 0x55)) { // FRAME HEADER FAULT
                std::cout << "SRI::REAL-TIME-ERROR::Frame header is fault. " << std::endl;
                return std::vector<RTData<T>>();
            }

            uint32_t PackageLength = recvbuf[2] * 256 + recvbuf[3];
            if (PackageLength != recvbuf.size() - 4) {
                std::cout << "SRI::REAL-TIME-ERROR::Package Length is fault. " << std::endl;
                return std::vector<RTData<T>>();
            }

            uint32_t dataLen = PackageLength - paritybit - 2;
            if (dataLen != rtMode.channelOrder.size() * sizeof(T) * rtMode.PNpCH) {
                std::cout << "SRI::REAL-TIME-ERROR::Expected Data Length is fault. Maybe Data Mode need update "
                          << std::endl;
                return std::vector<RTData<T>>();
            }

            //TODO:
            if (rtValid == "SUM") {
                if ((uint8_t)recvbuf.back() != getChecksum(&(recvbuf[6]), dataLen)) {
                    std::cout << "SRI::REAL-TIME-ERROR::Checksum is incorrect. " << std::endl;
                    return std::vector<RTData<T>>();
                }
            } else if (rtValid == "CRC32") {
                uint32_t crc32 = getCRC32(&(recvbuf[6]), dataLen);
                int8_t *pCRC = &(recvbuf[recvbuf.size() - 4]);
                for (int i = 0; i < 4; i++) {
                    if (pCRC[i] != ((int8_t *) &crc32)[i]) {
                        std::cout << "SRI::REAL-TIME-ERROR::CRC32 is incorrect. " << std::endl;
                        return std::vector<RTData<T>>();
                    }
                }
            }

            std::vector<RTData<T>> rtData(rtMode.PNpCH);
            // i*nChannel*sizeof(T) + sizeof(T)*j
            size_t nChannel = rtMode.channelOrder.size();
            for (int i = 0; i < rtMode.PNpCH; i++) {
                for (int j = 0; j < nChannel; j++) {
                    T val = *((T *) (&(recvbuf[6]) + i * nChannel * sizeof(T) + sizeof(T) * j));
                    rtData[i][j] = val;
                }
            }

            return rtData;
        };

        void startRealTimeDataRepeatedly(); // this function need a callback function
        void stopRealTimeDataRepeatedly();

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
        std::string extractResponseBuffer(std::vector<int8_t> &buf,
                                          const std::string &command,
                                          const std::string &parameter);

        uint8_t getChecksum(int8_t *pData, size_t len);

        uint32_t getCRC32(int8_t *pData, size_t len);


    }; // class FTSensor
} //namespace SRI


#endif //SRI_FTSENSOR_SDK_SRI_SENSOR_H
