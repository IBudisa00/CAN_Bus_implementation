#ifndef BUS_HPP
#define BUS_HPP

#include <vector>

class Can
{
    private:
    std::vector<int> m_buffer;
    public:
    Can();
    ~Can();
    void arbitration();
};

#endif // BUS_HPP
