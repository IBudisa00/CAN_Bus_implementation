#ifndef _cpu_HPP_
#define _cpu_HPP_

#include"bus.hpp"
#include"node.hpp"
#include<string>

class CPU : public Node
{
    private:
    std::vector<int> m_dataBuffer;
    public:
    CPU();
    ~CPU();
    void triggerSendData();
};

#endif // _cpu_HPP_