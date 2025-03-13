#ifndef _bus_HPP_
#define _bus_HPP_

#include<vector>

class Can
{
    private:
        std::vector<int> m_buffer;
    public:
        Can();
        ~Can();
        void arbitration();
};

#endif // _bus_HPP_
