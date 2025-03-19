#include <iostream>
#include <string>
#include "bus.hpp"
#include "define.hpp"
#include "node.hpp"
#include <condition_variable>
#include <mutex>
#include <thread>

void idleState(Node* node);

int main()
{
    std::vector<std::thread> threads;
    Can* bus = new Can();

    Node node1 (bus,"node1", CAN_20A);
    Node node2 (bus,"node2", CAN_20A);
    Node node3 (bus,"node3", CAN_20B);

    threads.push_back(std::thread(idleState, node1));
    threads.push_back(std::thread(idleState, node2));
    threads.push_back(std::thread(idleState, node3));

    for(auto& thread : threads)
        thread.join();
    
    delete bus;
    return 0;
}

void idleState(Node* node)
{
    std::unique_lock lk(mtx);
    threadsPrepared++;
    if(threadsPrepared != expectingThreads)
        cv.wait(lk);
    else
        cv.notify_all();

    while(1)
    {
        node->getTransceiver()->listenBus();
    }
}