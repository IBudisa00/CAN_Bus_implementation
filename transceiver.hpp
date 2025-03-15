#ifndef TRANSCEIVER_HPP
#define TRANSCEIVER_HPP

#include "bus.hpp"
#include "node.hpp"
#include <string>
#include <vector>

class Transceiver
{
    private:
    Can* m_bus;
    Controller* m_controller;
    std::string m_device_type;
    bool m_messageBeingSent; // trigger is anything is on line being sent by anybody
    bool m_ownNodeSendingMsg; // trigger if this node is sending smth to line
    unsigned int m_recessiveCounter;
    public:
    Transceiver() = delete;
    Transceiver(Can*& bus, Controller* controller, const std::string device_type);
    ~Transceiver();
    void sendData(const std::vector<int> dataFrame);
    void sendToBus(const int bit);
    void listenBus();
};

#endif // TRANSCEIVER_HPP