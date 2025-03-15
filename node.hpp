#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "bus.hpp"
#include <string>
#include "transceiver.hpp"
#include "cpu.hpp"
#include "canController.hpp"

class Node
{
    private:
    Can* m_bus;
    std::string m_device_type;
    std::string m_device_name;
    std::vector<int> m_buffer;
    CPU* m_cpu;
    Transceiver* m_transceiver;
    bool m_connectedToLine;
    public:
    Node() = delete;
    Node(Can*& busLine, const std::string& name, const std::string& type);
    ~Node();
    int checkDeviceType(const std::string& type);
    void bitStuffing();
    void sendData(const std::vector<int> msgId, const std::vector<int> data, const int identifierExtensionBit, const int reservedBit, const int rtrBit);
};

#endif // NODE_HPP