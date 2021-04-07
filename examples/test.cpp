//
// Created by think on 2021/4/7.
//

#include <sri/ftsensor.h>
#include <sri/commethernet.h>

#include <iostream>

int main() {
    std::cout << "Hello World" << std::endl;

    SRI::CommEthernet ce("192.168.3.181", 4008);
    ce.initialize();

    std::string s = "Hello World!";
    std::vector<char> buf;
    buf.assign(s.begin(), s.end());
    ce.write(buf);
    while(1) {
        if(ce.available() > 0) {
            std::cout << "Avaliable data bits: " << ce.available() << std::endl;
            std::vector<char> buf(ce.available());

            uint32_t i = ce.read(buf);
            std::string s(buf.begin(), buf.end());
            std::cout << "Received from: " << ce.getRemoteAddress() <<"  Length is: " << i << "   Data is: " << s << std::endl;
        }
    }

}