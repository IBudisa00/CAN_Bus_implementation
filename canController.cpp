#include "canController.hpp"

Controller::Controller() = delete;

Controller::Controller(Transceiver* transceiver)
{
    m_transceiver = transceiver;
}

Controller::~Controller()
{
}

void Controller::startSendingData(const int& msgId)
{
    m_transceiver->sendData(msgId);
}