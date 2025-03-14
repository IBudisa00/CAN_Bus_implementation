#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "bus.hpp"
#include <string>
#include "transceiver.hpp"
#include "cpu.hpp"

class Node
{
    private:
    Can* m_bus;
    std::string m_device_type;
    std::string m_device_name;
    std::vector<int> m_buffer;
    CPU* m_cpu;
    Transceiver* m_transceiver;
    public:
    Node() = delete;
    Node(Can*& busLine, const std::string& name, const std::string& type);
    ~Node();
    int checkDeviceType(const std::string& type);
    void bitStuffing();
    void sendData(const int& msgId);
};

#endif // NODE_HPP