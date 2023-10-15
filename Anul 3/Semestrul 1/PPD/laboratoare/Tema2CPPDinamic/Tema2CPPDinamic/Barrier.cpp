
#include <mutex>
using namespace std;

class my_barrier {

private:
    mutex m;
    condition_variable cv;
    int counter;
    int waiting;
    int thread_count;

public:
    my_barrier(int count) : thread_count(count), counter(0), waiting(0)
    {}

    void wait() {
        //fence mechanism
        unique_lock<mutex> lk(m);
        ++counter;
        ++waiting;
        cv.wait(lk, [&] {
            return counter >= thread_count;
            }
        );
        cv.notify_one();
        --waiting;

        if (waiting == 0) {
            //reset barrier
            counter = 0;
        }
        lk.unlock();
    }
};
