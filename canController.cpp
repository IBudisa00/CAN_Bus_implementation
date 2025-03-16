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
    calculateCRC(dataFrame, data);
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

void calculateCRC(std::vector<int>& dataFrame, const std::vector<int> data)
{
    std::bitset<16> initialValue(0xFFFF);
    int polinomSize = 17; // x^16 + x^12 + x^5 + 1
    std::vector<int> divisor{1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1};
    std::vector<int> inputSet;
    std::vector<int> dividend;
    std::vector<int> remainder;
    int inputSetCounter = polinomSize; // first to add

    for(int i = initialValue.size()-1; i >= 0; i--)
        inputSet.push_back(initialValue[i]);

    for(int i = 0; i < data.size(); i++)
        inputSet.push_back(data[i]);
    
    for(int i = 0; i < polinomSize-1; i++)
        inputSet.push_back(0);

    for(int i = 0; i < polinomSize; i++)
        dividend.push_back(inputSet[i]);
    
    while(inputSetCounter <= inputSet.size())
    {
        for(int i = 0; i < polinomSize; i++)
        {
            if(dividend[i] != divisor[i])
                remainder.push_back(1);
            else
                remainder.push_back(0);
        }
        dividend = remainder;
        if(inputSetCounter == inputSet.size())
            break;
        dividend.erase(dividend.begin());
        dividend.push_back(inputSet[inputSetCounter]);
        inputSetCounter++;
    }

    for(int i = 1; i < dividend.size(); i++)
        dataFrame.push_back(dividend[i]);
}