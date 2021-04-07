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

#ifndef SRI_FTSENSOR_SDK_COMMETHERNET_H
#define SRI_FTSENSOR_SDK_COMMETHERNET_H

#include <sri/sensorcomm.h>
#include <boost/asio.hpp>
#include <string>

namespace SRI {
    using namespace boost::asio;

    class CommEthernet : public SensorComm {
    public:
//        typedef ip::tcp::acceptor acceptor_type;
        typedef ip::tcp::endpoint endpoint_type;
        typedef ip::tcp::socket   socket_type;
        typedef ip::address       address_type;

    public:
        CommEthernet(std::string ip = "192.168.1.108", uint16_t port = 4008);

        bool isValid() override;

        bool initialize() override;

        size_t write(std::vector<char> &buf) override;

        size_t read(std::vector<char> &buf) override;

        ~CommEthernet() override;

        size_t available();

        std::string getRemoteAddress();

    private:
        io_service _io;             // asio must have an io_service object
        endpoint_type _endpoint;    // connected endpoint
        socket_type   _socket;      // socket object
        address_type  _ip;          // ip address
        uint16_t      _port;        // port number

    };
} //namespace SRI


#endif //SRI_FTSENSOR_SDK_COMMETHERNET_H
