#ifndef _canController_HPP_
#define _canController_HPP_

#include"bus.hpp"
#include"node.hpp"
#include "cpu.hpp"
#include<string>

class Controller : public CPU
{
    private:
    public:
    Controller();
    ~Controller();
    void startSendingData();
};

#endif // _canController_HPP_