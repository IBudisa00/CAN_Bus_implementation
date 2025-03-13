#include <iostream>
#include <string>
#include "bus.hpp"
#include "define.hpp"
#include "node.hpp"

int main()
{
    Can* bus = new Can();
    Node node1 (bus,"node1", CAN_20A);
    Node node2 (bus,"node2", CAN_20A);
    Node node3 (bus,"node3", CAN_20B);

    delete bus;
    return 0;
}