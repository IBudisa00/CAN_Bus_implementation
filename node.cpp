#include <iostream>
#include "node.hpp"
#include "define.hpp"

Node::Node(Can*& busLine, const std::string& name, const std::string& type)
{
    m_device_name = name;
    if(checkDeviceType(type))
        m_device_type = type;
    else
        std::cout<<"Unknown device type!"<<std::endl;

    if(m_bus == NULL)
        m_bus = new Can();
    else
        m_bus = busLine;
    
    m_transceiver = new Transceiver(m_device_type);
    m_cpu = new CPU(m_transceiver);
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

void Node::sendData(const int& msgId)
{
    m_cpu->triggerSendData(msgId);
}