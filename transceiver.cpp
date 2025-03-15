#include "transceiver.hpp"
#include "define.hpp"
#include <bitset>
#include "canController.hpp"

Transceiver::Transceiver(Can*& bus, Controller* controller, const std::string device_type)
{
    m_bus = bus;
    m_controller = controller;
    m_device_type = device_type;
    m_messageBeingSent = false;
    m_ownNodeSendingMsg = false;
    m_recessiveCounter = 0;
}

Transceiver::~Transceiver()
{
}

void Transceiver::sendData(const std::vector<int> dataFrame)
{
    m_messageBeingSent = true;
    m_ownNodeSendingMsg = true;
    for(auto bit : dataFrame)
        sendToBus(bit);
}

void Transceiver::sendToBus(const int bit)
{
    m_bus->setValue(bit);
}

void Transceiver::listenBus()
{
    int lineValue;

    lineValue = m_bus->getValue();
    if(lineValue == DOMINANT && !m_messageBeingSent)
    {
        m_recessiveCounter = 0;
        m_messageBeingSent = true;
        m_controller->setLineTaken(true);
    }
    else if(lineValue == DOMINANT && m_messageBeingSent)
    {
        m_recessiveCounter = 0;
        // njegov node ne salje al je neko krenia zapravo generalno neko salje
        // uzet u obzir da li njegov salje varijabla je m_ownNodeSendingMsg
        // provjera arbitrazom
    }
    else if(lineValue == RECESSIVE && m_messageBeingSent)
    {
        m_recessiveCounter++;
        if(m_recessiveCounter == 10)
        {
            m_controller->setLineTaken(false);
            m_recessiveCounter = 0;
            m_messageBeingSent = false;
            // check if this node has information to send on line in messageBuffer in controller
        }
    }
    else if(lineValue == RECESSIVE && !m_messageBeingSent)
    {
        // normal state, everything passive
        m_controller->setLineTaken(false);
    }
}
