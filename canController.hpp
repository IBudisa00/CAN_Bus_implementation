#ifndef CANCONTROLLER_HPP
#define CANCONTROLLER_HPP

#include "bus.hpp"
#include "node.hpp"
#include "cpu.hpp"
#include "transceiver.hpp"
#include <string>

class Controller
{
    private:
    Transceiver* m_transceiver;
    public:
    Controller() = delete;
    Controller(Transceiver* transceiver);
    ~Controller();
    void startSendingData(const int& msgId);
};

#endif // CANCONTROLLER_HPP