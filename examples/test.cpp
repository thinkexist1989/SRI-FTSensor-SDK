//
// Created by think on 2021/4/7.
//

#include <sri/ftsensor.h>
#include <sri/commethernet.h>

#include <iostream>

using namespace SRI;

int main() {

    SRI::CommEthernet* ce = new SRI::CommEthernet("127.0.0.1", 4008);

    SRI::FTSensor sensor(ce);
    sensor.generateCommandBuffer(SRI::EIP,"?");

//    std::string s = ACK + EIP + "=" + "127.0.0.1\r\n";
    std::string s = ACK + EIP + "=" + "127.0.0.1$ERROR\r\n";
    std::vector<char> buf(s.begin(), s.end());
    std::string res = sensor.extractResponseBuffer(buf, EIP, "127.0.0.1");
    std::cout << res << std::endl;

//    std::cout << "IP Address: " << sensor.getIpAddress() << std::endl;

//    std::cout << sensor.setIpAddress("192.168.3.3") << std::endl;

//    Gains gains = sensor.getChannelGains();
//    for(auto& gain : gains) {
//        std::cout << gain << " ; ";
//    }
//    std::cout << std::endl;

//    Sensitivities sens = {123.321, 234.432, 345.543, 654.234, 234.53};
//    std::cout << sensor.setSensorSensitivities(sens) << std::endl;

//      auto rtMode = sensor.getRealTimeDataMode();
//      for(auto& c : rtMode.channelOrder) {
//          std::cout << c << " , ";
//      }
//      std:: cout << std::endl;
//
//      std::cout << "DataUnit: " << rtMode.DataUnit << std::endl;
//      std::cout << "PNpCH: " << rtMode.PNpCH << std::endl;
//      std::cout << "FM: " << rtMode.FM  << std::endl;
//
//      for(auto& w : rtMode.filterWeights) {
//          std::cout << w << " , ";
//      }
//      std::cout << std::endl;

    RTDataMode rtDataMode;
    std::cout << sensor.setRealTimeDataMode(rtDataMode) << std::endl;



//    std::string s = "Hello World!";
//    std::vector<char> buf;
//    buf.assign(s.begin(), s.end());
//    ce.write(buf);
//    while(1) {
//        if(ce.available() > 0) {
//            std::cout << "Avaliable data bits: " << ce.available() << std::endl;
//            std::vector<char> buf(ce.available());
//
//            uint32_t i = ce.read(buf);
//            std::string s(buf.begin(), buf.end());
//            std::cout << "Received from: " << ce.getRemoteAddress() <<"  Length is: " << i << "   Data is: " << s << std::endl;
//        }
//    }

}