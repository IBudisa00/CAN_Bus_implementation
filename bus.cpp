#include <iostream>
#include <bus.hpp>
#include "define.hpp"
#include "canController.hpp" 

Can::Can()
{
    std::cout<<"Bus line initialized."<<std::endl;
    m_value = RECESSIVE;
}

Can::~Can()
{
    std::cout<<"Bus line destroyed."<<std::endl;
}

inline void Can::setValue(const int value)
{
    m_value = value;
}

inline int Can::getValue()
{
    return m_value;
}

void Can::arbitration()
{
    // will be done
}