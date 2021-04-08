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

        size_t nStart;
        if(parameter == "?")
            nStart = s.find("=") + 1;
        else
            nStart = s.find("$") + 1;

        size_t nEnd   = s.find("\r\n");
        return s.substr(nStart, nEnd-nStart);
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
            boost::split(resInString, response, boost::is_any_of(";"), boost::algorithm::token_compress_on);
        }
        catch (boost::bad_lexical_cast& e) {
            std::cout << "ERROR::FTSensor::getChannelGains():" << e.what() << std::endl;
        }
        Gains gains;

        for(auto& res : resInString) {
            gains.push_back(std::stof(res));
        }

        return gains;
    }

    SampleRate FTSensor::getSamplingRate() {
        commPtr->write(generateCommandBuffer(SMPR, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, SMPR, "?");

        return std::stoi(response);
    }

    bool FTSensor::setSamplingRate(const SampleRate rate) {
        commPtr->write(generateCommandBuffer(SMPR, boost::lexical_cast<std::string>(rate)));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, SMPR, boost::lexical_cast<std::string>(rate));

        if (response == "OK")
            return true;
        else
            return false;
    }

    Voltages FTSensor::getExcitationVoltages() {
        commPtr->write(generateCommandBuffer(EXMV, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, EXMV, "?");

        std::vector<std::string> resInString;
        try {
            boost::split(resInString, response, boost::is_any_of(";"), boost::algorithm::token_compress_on);
        }
        catch (boost::bad_lexical_cast& e) {
            std::cout << "ERROR::FTSensor::getExcitationVoltages():" << e.what() << std::endl;
        }
        Voltages voltages;

        for(auto& res : resInString) {
            voltages.push_back(std::stof(res));
        }

        return voltages;
    }

    Sensitivities FTSensor::getSensorSensitivities() {
        commPtr->write(generateCommandBuffer(SENS, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, SENS, "?");

        std::vector<std::string> resInString;
        try {
            boost::split(resInString, response, boost::is_any_of(";"), boost::algorithm::token_compress_on);
        }
        catch (boost::bad_lexical_cast& e) {
            std::cout << "ERROR::FTSensor::getSensorSensitivities():" << e.what() << std::endl;
        }
        Sensitivities sens;

        for(auto& res : resInString) {
            sens.push_back(std::stof(res));
        }

        return sens;
    }

    bool FTSensor::setSensorSensitivities(const Sensitivities &sens) {
        std::string parameters;
        for(auto& s : sens) {
            parameters += boost::lexical_cast<std::string>(s) + ";";
        }
        parameters = parameters.substr(0, parameters.find_last_of(';'));

        commPtr->write(generateCommandBuffer(SENS, parameters));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, SENS, parameters);

        if (response == "OK")
            return true;
        else
            return false;
    }

    Offsets FTSensor::getAmplifierZeroOffsets() {
        commPtr->write(generateCommandBuffer(AMPZ, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, AMPZ, "?");

        std::vector<std::string> resInString;
        try {
            boost::split(resInString, response, boost::is_any_of(";"), boost::algorithm::token_compress_on);
        }
        catch (boost::bad_lexical_cast& e) {
            std::cout << "ERROR::FTSensor::getAmplifierZeroOffsets():" << e.what() << std::endl;
        }
        Offsets offsets;

        for(auto& res : resInString) {
            offsets.push_back(std::stof(res));
        }

        return offsets;
    }

    bool FTSensor::setAmplifierZeroOffsets(const Offsets &offsets) {
        std::cout << "SRI::FTSensor::setAmplifierZeroOffsets::Has not been implemented." << std::endl;
        return false;
    }

    RTDataMode FTSensor::getRealTimeDataMode() {
        commPtr->write(generateCommandBuffer(SGDM, "?"));
        while (commPtr->available() == 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(500));
        }
        std::vector<char> recvbuf;
        commPtr->read(recvbuf);
        std::string response = extractResponseBuffer(recvbuf, SGDM, "?");

        std::vector<std::string> resInString;
        try {
            boost::split(resInString, response, boost::is_any_of(";"), boost::algorithm::token_compress_on);
        }
        catch (boost::bad_lexical_cast& e) {
            std::cout << "ERROR::FTSensor::getRealTimeDataMode():" << e.what() << std::endl;
        }

        if(resInString.size() != 4)
            std::cout << "ERROR::FTSensor::getRealTimeDataMode():Parse Data False" << std::endl;


        RTDataMode rtDataMode;
        //1. Get the relevant analog channels. format: (A01,A02,A03,A04,A05,A06)
        std::vector<std::string> channelsInString;
        boost::trim_if(resInString[0], boost::is_any_of("()"));
        boost::split(channelsInString, resInString[0], boost::is_any_of("(),"), boost::algorithm::token_compress_on);
        rtDataMode.channelOrder.clear(); //rtDataMode has default value 1,2,3,4,5,6
        for(auto& cs : channelsInString) {
            auto c = std::stoi(cs.substr(cs.find('A') + 1));
            rtDataMode.channelOrder.push_back(c);
        }
        //2. The unit of data uploaded from M8128.
        rtDataMode.DataUnit = resInString[1][0];
        //3. Number of data which are desired.
        rtDataMode.PNpCH = std::stoi(resInString[2]);
        //4. Filter model. Set to WMA.
        std::vector<std::string> fmInString;
        boost::trim_if(resInString[3], boost::is_any_of("()"));
        boost::split(fmInString, resInString[3], boost::is_any_of("():"), boost::algorithm::token_compress_on);

        rtDataMode.FM = fmInString[0];
        //5. WMA's relevant parameters, default 1.
        std::vector<std::string> weightsInString;
        boost::split(weightsInString, fmInString[1], boost::is_any_of(","), boost::algorithm::token_compress_on);
        for(auto& ws : weightsInString) {
            auto w = std::stoi(ws);
            rtDataMode.filterWeights.push_back(w);
        }

        return rtDataMode;

    }


} //namespace SRI