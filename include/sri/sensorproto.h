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

#ifndef SRI_FTSENSOR_SDK_SENSORPROTO_H
#define SRI_FTSENSOR_SDK_SENSORPROTO_H

#include <string>
#include <memory>
#include <mutex>

#include <vector>

namespace SRI {
    /* SensorProto is design for the implementation of sensors' protocol.
     * which can generate the sendbuf according to the protocol.
     * and also can parse the recvbuf to extract the expected information.
     * It is designed via the design pattern —— Singleton
     */
    class SensorProto : public std::enable_shared_from_this<SensorProto> {
    public:
        /* FRAME HEADERS */
        const std::string AT = "AT+";     // Frame Header when sending data.
        const std::string ACK = "ACK+";    // Frame Header when receiving data.
        /* RESPONSE CODE */
        const std::string OK = "OK";      // Response code，OK
        const std::string ERROR = "ERROR";   // Response code，ERROR
        /* CONFIGURATIONS COMMAND */
        const std::string UARTCFG = "UARTCFG"; // To read or set parameters of RS232
        const std::string CRATE = "CRATE";   // To read or set baud rate of CAN Bus
        const std::string CIDT = "CIDT";    // To read or set ID type of CAN Bus
        const std::string CFIDL = "CFIDL";   // To read or set ID of CAN Bus
        const std::string EIP = "EIP";     // Ethernet IP address
        const std::string EMAC = "EMAC";    // Ethernet MAC address
        const std::string EGW = "EGW";     // Ethernet gateway
        const std::string ENM = "ENM";     // Ethernet netmask
        /* SENSOR PARAMETERS COMMAND */
        const std::string CHNAPG = "CHNAPG";  // To read the gain of each channel
        const std::string SMPR = "SMPR";    // To read or set sampling rate
        const std::string SENS = "SENS";    // To read or set the sensitivity of sensor
        const std::string AMPZ = "AMPZ";    // To read amplifier zero offset of each channel
        /* REAL-TIME DATA COMMAND */
        const std::string SGDM = "SGDM";    // To set the mode to receive data
        const std::string DCKMD = "DCKMD";   // To set the data validation method
        const std::string GSD = "GSD";     // To get data from M8128 repeatedly
        const std::string GOD = "GOD";     // To get one package data from M8128
    private:
        SensorProto() = default; // prevent external construct

        SensorProto(const SensorProto &) = delete; // prevent copy construct

        SensorProto &operator=(const SensorProto &) = delete; // prevent copy assignment

    public:
        static std::shared_ptr<SensorProto> getInstance();

        /// Generate Command Buffer
        /// \param[in] Command      The CMD such as UARTCFG.
        /// \param[in] parameter    The parameters of the command.
        /// \return                 command buffer(string format).
        std::string generateCommandBuffer(std::string &command, std::string &parameter);

        /// Extract Response Buffer
        /// \param[in] recvbuf          The reference of received buffer.
        /// \param[in] expect_command   The expected command.
        /// \return                     The response from sensor(string format)
        std::string extractResponseBuffer(std::vector<char> &recvbuf,
                                          std::string &command,
                                          std::string &parameter);



    private:
        static std::shared_ptr<SensorProto> _instance;

    }; //class SensorProto
} //namespace SRI


#endif //SRI_FTSENSOR_SDK_SENSORPROTO_H
