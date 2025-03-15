#ifndef BUS_HPP
#define BUS_HPP

#include <vector>

class Can
{
    private:
    int m_value;
    public:
    Can();
    ~Can();
    inline void setValue(const int value);
    inline int getValue();
    inline Controller* getController();
    void arbitration();
};

#endif // BUS_HPP 