#ifndef CANCONTROLLER_HPP
#define CANCONTROLLER_HPP

#include "bus.hpp"
#include "node.hpp"
#include "cpu.hpp"
#include "transceiver.hpp"
#include <string>

class Controller
{
    private:
    Transceiver* m_transceiver;
    bool m_lineTaken;
    bool m_holdMessage = false;
    std::vector<int> m_messageBuffer;
    public:
    Controller() = delete;
    Controller(Transceiver* transceiver);
    ~Controller();
    std::vector<int> Controller::formDataFrame(const std::vector<int> msgId, const std::vector<int> data, const int identifierExtensionBit, const int reservedBit, const int rtrBit);
    void startSendingData(const std::vector<int> msgId, const std::vector<int> data, const int identifierExtensionBit, const int reservedBit, const int rtrBit);
    inline void setLineTaken(const bool& value);
};

#endif // CANCONTROLLER_HPP