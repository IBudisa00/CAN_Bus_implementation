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
    void triggerSendData(const std::vector<int> msgId, const std::vector<int> data, const int identifierExtensionBit, const int reservedBit, const int rtrBit);
    inline Controller* getController();
};

#endif // CPU_HPP