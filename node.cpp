#include <iostream>
#include "node.hpp"
#include "define.hpp"

Node::Node(Can*& busLine, const std::string& name, const std::string& type)
{
    m_device_name = name;
    if(checkDeviceType(type))
    {
        m_device_type = type;
        m_connectedToLine = true;
    }
    else
    {
        m_connectedToLine = false;
        std::cout<<m_device_name<<": Unknown device type!"<<std::endl;
    }

    if(m_bus == NULL)
        m_bus = new Can();
    else
        m_bus = busLine;
    
    m_cpu = new CPU(m_transceiver);
    m_transceiver = new Transceiver(busLine, m_cpu->getController(), m_device_type);
}

Node::~Node()
{
    delete m_transceiver;
    delete m_cpu;
    std::cout<<"Device "<<m_device_name<<" destroyed."<<std::endl;
}

int Node::checkDeviceType(const std::string& type)
{
    if(type != CAN_20A && type != CAN_20B && type != CAN_FD)
        return 0;
    return 1;
}

void Node::bitStuffing()
{
    // will be done
}

void Node::sendData(const std::vector<int> msgId, const std::vector<int> data, const int identifierExtensionBit, const int reservedBit, const int rtrBit)
{
    m_cpu->triggerSendData(msgId, data, identifierExtensionBit, reservedBit, rtrBit);
}