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

#ifndef SRI_FTSENSOR_SDK_TYPES_HPP
#define SRI_FTSENSOR_SDK_TYPES_HPP

#include <string>
#include <vector>
#include <map>

namespace SRI {
    /* FRAME HEADERS */
    const std::string AT = "AT+";     // Frame Header when sending data.
    const std::string ACK = "ACK+";    // Frame Header when receiving data.
    /* RESPONSE CODE */
    const std::string RES_OK = "OK";      // Response code，OK
    const std::string RES_ERROR = "ERROR";   // Response code，ERROR
    /* CONFIGURATIONS COMMAND */
    const std::string UARTCFG = "UARTCFG"; // (RW) To read or set parameters of RS232
    const std::string CRATE = "CRATE";   // (RW) To read or set baud rate of CAN Bus
    const std::string CIDT = "CIDT";    // (RW) To read or set ID type of CAN Bus
    const std::string CFIDL = "CFIDL";   // (RW) To read or set ID of CAN Bus
    const std::string CFI = "CFI";     // (RW) To set (or read) interval time between frames of CAN Bus
    const std::string EIP = "EIP";     // (RW) To read or set Ethernet IP address.
    const std::string EMAC = "EMAC";    // (RW) To read or set Ethernet MAC address
    const std::string EGW = "EGW";     // (RW) To read or set Ethernet gateway
    const std::string ENM = "ENM";     // (RW) To read or set Ethernet netmask
    /* SENSOR PARAMETERS COMMAND */
    const std::string CHNAPG = "CHNAPG";  // (RO) To read the gain of each channel
    const std::string SMPR = "SMPR";    // (RW) To read or set sampling rate
    const std::string EXMV = "EXMV";    // (RO) To read excitation voltage of sensor
    const std::string SENS = "SENS";    // (RW) To read or set the sensitivity of sensor
    const std::string AMPZ = "AMPZ";    // (RO) To read amplifier zero offset of each channel
    const std::string DCPM = "DCPM";    // (WO) Set the decoupling matrix to M8128 by command DCPM
    /* REAL-TIME DATA COMMAND */
    const std::string SGDM = "SGDM";    // (WO) To set the mode to receive data
    const std::string DCKMD = "DCKMD";   // (WO) To set the data validation method
    const std::string GSD = "GSD";     // To get data from M8128 repeatedly
    const std::string GOD = "GOD";     // To get one package data from M8128


    /* CONFIGURATIONS TYPE DEFINES */
    struct UartCfg {
        uint32_t Rate;       // 115200bps(default), 921600bps,460800bps,256000bps,230400bps, 57600bps, 56000bps, 38400bps, 19200bps, 14400bps or 9600bps.
        uint32_t DataBit;    // 5, 6, 7, 8(default)
        float StopBit;    // 0.5, 1.0(default), 1.5, 2.0
        uint8_t ParityBit;  // 'N' - none(default), 'O' - odd, 'E' - even
    };

    typedef std::string CanIdType; // The Type can be STD or EXT.STD denotes the standard 11 bits ID and EXT denotes the extended 29 bits ID.

    typedef std::vector<uint32_t> CanIds; //One M8128 can have maximum 14 IDs. It will be available after M8128 is restarted.

    struct CanRate {
        uint16_t BS1;
        uint16_t BS2;
        uint16_t Prescaler;

        inline uint32_t rate() {
            return 36.0 / ((1.0 + BS1 + BS2) * (1 + Prescaler));
        }
    };

    typedef uint32_t IntervalTime;      // Interval time in us. The default value in firmware is 0us.
    typedef std::string IpAddr;         // IP address, eg. IpAddr ip = "192.168.0.108"
    typedef std::string MacAddr;        // Ethernet MAC address, eg. MacAddr mac = "12-13-14-15-16-17"
    typedef std::string GateAddr;       // Ethernet gateway address, eg. GateAddr gateway = "192.168.0.1"
    typedef std::string NetMask;        // Ethernet netmask,eg. NetMask mask = "255.255.255.0"

    /* SYSTEM PARAMETERS TYPE DEFINES */
    typedef std::vector<float> Gains;   // The actual gains of each channel in float.
    typedef uint16_t SampleRate;   // Sampling rate in Hz. For example, 200.
    typedef std::vector<float> Voltages;// Excitation voltage of each channel in float.
    typedef std::vector<float> Sensitivities; // the sensitivity of each channel in float.
    typedef std::vector<float> Offsets; // Read amplifier zero offset of each channel.

    /* REAL-TIME DATA TYPE DEFINES */
    struct RTDataMode {
        std::vector<uint16_t> channelOrder = {1, 2, 3, 4, 5, 6}; // The relevant analog channels.
        char DataUnit = 'C';     // The unit of data uploaded from M8128.
                                 // E, V, M or C which denote Engineering unit, mV/V, mV or AD Counts respectively.
        uint16_t PNpCH = 1;        // Number of data which are desired.
        std::string FM = "WMA";   // Filter model. Set to WMA.
        std::vector<uint16_t> filterWeights = {1};// WMA's relevant parameters, default 1.

        const std::map<char, uint16_t> UnitLength = {{'E', 4},
                                                     {'V', 4},
                                                     {'M', 4},
                                                     {'C', 2}};
    };

    typedef std::string RTDataValid; // data validation method when getting one package data from M8128. SUM or CRC32

    template<typename T>
    struct RTData {
        uint16_t DataNumber;
        std::vector<T> Data;
//        uint8_t FrameHeader[2] = {0xAA, 0x55};
//        uint16_t PackLength;
//        uint8_t Checksum;
//        uint32_t CRC32;

        T& operator[](int index) {
            if(Data.size() <= index) {
                Data.resize(index + 1);
                return Data[index];
            }
            else {
                return Data[index];
            }
        }
    };

}

#endif //SRI_FTSENSOR_SDK_TYPES_HPP
