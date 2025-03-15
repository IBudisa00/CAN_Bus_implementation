#include "cpu.hpp"
#include "canController.hpp"

CPU::CPU(Transceiver* transceiver)
{
    m_controller = new Controller(transceiver);
}

CPU::~CPU()
{
    delete m_controller;
}

void CPU::triggerSendData(const std::vector<int> msgId, const std::vector<int> data, const int identifierExtensionBit, const int reservedBit, const int rtrBit)
{
    m_controller->startSendingData(msgId, data, identifierExtensionBit, reservedBit, rtrBit);
}

inline Controller* CPU::getController()
{
    return m_controller;
}