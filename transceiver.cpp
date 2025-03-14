#include "transceiver.hpp"
#include "define.hpp"

Transceiver::Transceiver(const std::string device_type)
{
    m_device_type = device_type;
}

Transceiver::~Transceiver()
{
}

void Transceiver::sendData(const int& msgId)
{
    // transform msgId into bits coorespodning to that particular message
    // send transformed bits
}

std::vector<int> Transceiver::transformMsgToBits(const int& msgId)
{
    // transform msgId to bits
    
    std::vector<int> dataFrame;

    dataFrame.push_back(RECESSIVE); // start of frame
    // insert to data frame transformed msgId
    dataFrame.push_back(DOMINANT); // RTR bit
    
    // 2.0b and fd choose their identifier based on "needs" of message, basically device decides that 
    if(m_device_type == CAN_20A)
        dataFrame.push_back(DOMINANT);
    else if(m_device_type == CAN_20B)
        dataFrame.push_back(RECESSIVE);
    else
        dataFrame.push_back(DOMINANT);
    
    dataFrame.push_back(DOMINANT); // reserved bit
    for(int i = 0; i < 4; i++)
    {
        // get msg and divide by 8 to get number of bits and use it to set dominant or recessive
        dataFrame.push_back(DOMINANT); // data length code (numeber of bytes of data)
    }
}