//
// Created by think on 2021/4/7.
//

#include "sri/commethernet.h"

namespace SRI {

    CommEthernet::CommEthernet(std::string ip, uint16_t port) : _socket(_io) {

        _ip = _ip.from_string(ip);
        _port = port;
        _endpoint.address(_ip);
        _endpoint.port(_port);

    }

    CommEthernet::~CommEthernet() {

    }

    bool CommEthernet::isValid() {
        return _validStatus;
    }

    bool CommEthernet::initialize() {

        _socket.connect(_endpoint); // connect to endpoint

        if (_socket.is_open())
            return true;
        else
            return false;
    }

    size_t CommEthernet::write(std::vector<int8_t> &buf) {
        if (!_socket.is_open()) {
            _validStatus = false;
            return 0;
        }
        return _socket.write_some(buffer(buf));
    }

    size_t CommEthernet::write(char *buf, size_t n) {
        if (!_socket.is_open()) {
            _validStatus = false;
            return 0;
        }
        return _socket.write_some(buffer(buf, n));
    }

    size_t CommEthernet::write(const std::string &buf) {
        if (!_socket.is_open()) {
            _validStatus = false;
            return 0;
        }
        return _socket.write_some(buffer(buf));
    }

    size_t CommEthernet::read(std::vector<int8_t> &buf) {
        if (!_socket.is_open()) {
            _validStatus = false;
            return 0;
        }

        buf.resize(available());

        return _socket.read_some(buffer(buf));
    }

    size_t CommEthernet::read(char *buf, size_t n) {
        if (!_socket.is_open()) {
            _validStatus = false;
            return 0;
        }

        size_t num = n < available() ? n : available();

        return _socket.read_some(buffer(buf, num));
    }

    size_t CommEthernet::read(std::string &buf) {
        if (!_socket.is_open()) {
            _validStatus = false;
            return 0;
        }

        buf.resize(available());

        return _socket.read_some(buffer(buf));
    }

    size_t CommEthernet::available() {
        return _socket.available();
    }

    std::string CommEthernet::getRemoteAddress() {
        return _socket.remote_endpoint().address().to_string();
    }

} //namespace SRI

