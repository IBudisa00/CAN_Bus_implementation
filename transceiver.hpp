#ifndef TRANSCEIVER_HPP
#define TRANSCEIVER_HPP

#include "bus.hpp"
#include "node.hpp"
#include <string>
#include <vector>

class Transceiver
{
    private:
    std::string m_device_type;
    public:
    Transceiver(const std::string device_type);
    ~Transceiver();
    void sendData(const int& msgId);
    std::vector<int> transformMsgToBits(const int& msgId);
};

#endif // TRANSCEIVER_HPP