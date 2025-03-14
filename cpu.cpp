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

void CPU::triggerSendData(const int& msgId)
{
    m_controller->startSendingData(msgId);
}