#include "canController.hpp"
#include <bitset>
#include "define.hpp"

Controller::Controller(Transceiver* transceiver)
{
    m_transceiver = transceiver;
    m_lineTaken = false;
    m_holdMessage = false;
}

Controller::~Controller()
{
}

std::vector<int> Controller::formDataFrame(const std::vector<int> msgId, const std::vector<int> data, const int identifierExtensionBit, const int reservedBit, const int rtrBit)
{
    std::vector<int> dataFrame;

    dataFrame.push_back(RECESSIVE); // start of frame
    for(int i = 0; i < msgId.size(); i++)
    {
        dataFrame.push_back(msgId[i]); // identifier bits
    }
    dataFrame.push_back(rtrBit); // RTR bit
    dataFrame.push_back(identifierExtensionBit); // IDE bit
    dataFrame.push_back(reservedBit); // reserved bit
    for(int i = 1; i <= 4; i++)
        dataFrame.push_back(data[data.size()-i]); // dataBytes
    for(int i = 0; i < data.size(); i++)
        dataFrame.push_back(data[i]); // data bits
    // 1 bits for CRC (gotta calculate it) 
    dataFrame.push_back(RECESSIVE); // CRC delimiter must be 1
    dataFrame.push_back(RECESSIVE); // ack slot - sender(1), receiver(0)
    dataFrame.push_back(RECESSIVE); // ack delimiter - must be 1
    for(int i = 0; i < 7; i++)
        dataFrame.push_back(RECESSIVE); // EOF bits (1111111)
    for(int i = 0; i < 3; i++)
        dataFrame.push_back(RECESSIVE); // IFC bits (111) - time between two frames to avoid data corruption
    return dataFrame;
}


void Controller::startSendingData(const std::vector<int> msgId, const std::vector<int> data, const int identifierExtensionBit, const int reservedBit, const int rtrBit)
{
    std::vector<int> dataFrame;
    dataFrame = formDataFrame(msgId, data, identifierExtensionBit, reservedBit, rtrBit);
    m_messageBuffer = dataFrame;

    if(!m_lineTaken)
        m_transceiver->sendData(dataFrame);
    else
    {
        while(m_lineTaken)
        {
            // wait till line is free
        }
        m_transceiver->sendData(dataFrame);
    }
}

inline void Controller::setLineTaken(const bool& value)
{
    m_lineTaken = value;
    if(value == true)
        m_holdMessage = true;
    else
        m_holdMessage = false;
}