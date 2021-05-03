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

#ifndef SRI_FTSENSOR_SDK_COMMETHERNET_HPP
#define SRI_FTSENSOR_SDK_COMMETHERNET_HPP

#include <sri/sensorcomm.hpp>
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
        CommEthernet(std::string ip = "192.168.1.108", uint16_t port = 4008) : _socket(_io) {
            _ip = _ip.from_string(ip);
            _port = port;
            _endpoint.address(_ip);
            _endpoint.port(_port);
        }

        ~CommEthernet() override {

        }

        bool isValid() override {
            return _validStatus;
        }

        bool initialize() override {
            try {
                _socket.connect(_endpoint); // connect to endpoint
                _validStatus = true;
            }
            catch (boost::system::system_error &error) {
                std::cout << "SRI::ETHERNET::Error connecting to sensors: " << error.what() << std::endl;
                _validStatus = false;
            }

            return _validStatus;
        }

        size_t write(std::vector<int8_t> &buf) override {
            if (!_validStatus) {
                return 0;
            }
            return _socket.write_some(buffer(buf));
        }

        size_t write(const std::string &buf) override {
            if (!_validStatus) {
                return 0;
            }
            return _socket.write_some(buffer(&buf[0], buf.size()));
        }

        size_t write(char *buf, size_t n) override {
            if (!_validStatus) {
                return 0;
            }
            return _socket.write_some(buffer(buf, n));
        }

        size_t read(std::vector<int8_t> &buf) override {
            if (!_validStatus) {
                return 0;
            }

            buf.resize(available());

            return _socket.read_some(buffer(buf));
        }

        size_t read(char *buf, size_t n) override {
            if (!_validStatus) {
                return 0;
            }

            size_t num = n < available() ? n : available();

            return _socket.read_some(buffer(buf, num));
        }

        size_t read(std::string &buf) override {
            if (!_validStatus) {
                return 0;
            }

            buf.resize(available());

            return _socket.read_some(buffer(&buf[0], buf.size()));
        }

        size_t available() override {
            return _socket.available();
        }

        std::string getRemoteAddress() {
            return _socket.remote_endpoint().address().to_string();
        }

    private:
        io_service _io;             // asio must have an io_service object
        endpoint_type _endpoint;    // connected endpoint
        socket_type   _socket;      // socket object
        address_type  _ip;          // ip address
        uint16_t      _port;        // port number

    };
} //namespace SRI


#endif //SRI_FTSENSOR_SDK_COMMETHERNET_HPP
