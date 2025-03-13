#ifndef _node_HPP_
#define _node_HPP_

#include<vector>
#include"bus.hpp"
#include<string>

class Node
{
    private:
    Can* m_bus;
    std::string m_device_type;
    std::string m_device_name;
    std::vector<int> m_buffer;
    public:
    Node() = delete;
    Node(Can*& busLine, const std::string& name, const std::string& type);
    ~Node();
    int checkDeviceType(const std::string& type);
    void bitStuffing();
    void sendData();
};

#endif // _node_HPP_