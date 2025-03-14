#ifndef CPU_HPP
#define CPU_HPP

#include "bus.hpp"
#include "node.hpp"
#include "transceiver.hpp"
#include <string>

class CPU
{
    private:
    std::vector<int> m_dataBuffer;
    Controller* m_controller;
    public:
    CPU(Transceiver* transceiver);
    ~CPU();
    void triggerSendData(const int& msgId);
};

#endif // CPU_HPP