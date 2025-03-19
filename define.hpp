#include <mutex>
#include <condition_variable>
#include <atomic>

// --- Bit values ---
#define RECESSIVE 1
#define DOMINANT 0

// --- Device types ---
#define CAN_20A "can2.0a"
#define CAN_20B "can2.0b"
#define CAN_FD "canFD"

// --- Message IDs ---
#define MSG1 1
#define MSG2 2
#define MSG3 3
#define MSG4 4

std::mutex mtx;
std::condition_variable cv;
std::atomic_int threadsPrepared = 0;
const int expectingThreads = 3;