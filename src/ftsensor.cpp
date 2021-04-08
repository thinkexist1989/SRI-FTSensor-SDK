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
#include <thread>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace SRI {

    FTSensor::FTSensor(SensorComm *pcomm) : commPtr(pcomm) {
        commPtr->initialize();
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
        commPtr->write(generateCommandBuffer(EIP, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, EIP, "?");

        return response;
    }

    bool FTSensor::setIpAddress(const IpAddr &ip) {
        commPtr->write(generateCommandBuffer(EIP, ip));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, EIP, ip);

        if (response == "OK")
            return true;
        else
            return false;
    }

    MacAddr FTSensor::getMacAddress() {
        commPtr->write(generateCommandBuffer(EMAC, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, EMAC, "?");

        return response;
    }

    bool FTSensor::setMacAddress(const MacAddr &mac) {
        commPtr->write(generateCommandBuffer(EMAC, mac));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, EIP, mac);

        if (response == "OK")
            return true;
        else
            return false;
    }

    GateAddr FTSensor::getGateWay() {
        commPtr->write(generateCommandBuffer(EGW, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, EGW, "?");

        return response;
    }

    bool FTSensor::setGateWay(const GateAddr &gate) {
        commPtr->write(generateCommandBuffer(EMAC, gate));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, EMAC, gate);

        if (response == "OK")
            return true;
        else
            return false;
    }

    NetMask FTSensor::getNetMask() {
        commPtr->write(generateCommandBuffer(ENM, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, ENM, "?");

        return response;
    }

    bool FTSensor::setNetMask(const NetMask &mask) {
        commPtr->write(generateCommandBuffer(ENM, mask));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, ENM, mask);

        if (response == "OK")
            return true;
        else
            return false;
    }

    Gains FTSensor::getChannelGains() {
        commPtr->write(generateCommandBuffer(CHNAPG, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, CHNAPG, "?");

        std::vector<std::string> resInString;
        try {
            boost::split(resInString, response, boost::is_any_of(";"));
        }
        catch (boost::bad_lexical_cast& e) {
            std::cout << "ERROR::FTSensor::getChannelGains():" << e.what() << std::endl;
        }
        Gains gains;

        for(auto& res : resInString) {
            gains.push_back(stof(res));
        }

        return gains;
    }


} //namespace SRI