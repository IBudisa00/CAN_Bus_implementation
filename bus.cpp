#include <iostream>
#include <bus.hpp>

Can::Can()
{
    std::cout<<"Bus line initialized."<<std::endl;
}

Can::~Can()
{
    std::cout<<"Bus line destroyed."<<std::endl;
}

void Can::arbitration()
{
    // will be done
}