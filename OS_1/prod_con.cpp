#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>

using namespace std;

class GCDSemaphore {
    public: 
        GCDSemaphore(int count = 0) : count(count) {}
        void wait(){
            unique_lock<mutex> lock(mtx);
            if(count == 0){
                cv.wait(lock);
            }
            count--;

        }
        void signal(){
            unique_lock<mutex> lock(mtx);
            count++;
            cv.notify_one();

        }

    private:
        mutex mtx;
        condition_variable cv;
        int count;

};

int item_count;
int buffer_size = 10;
queue<int> buffer;
mutex bufferMutex;
GCDSemaphore full(0);
GCDSemaphore empty(buffer_size);

void producer(){
    for (int i = 0; i < item_count; ++i)
    {
        empty.wait();
        {unique_lock<mutex> lock(bufferMutex);
                buffer.push(i);
                cout << "Produced item: " << i << endl;}
        full.signal();
    }
}

void consumer(){
    int item;
    for (int i = 0; i < item_count; ++i)
    {
        full.wait();
        {unique_lock<mutex> lock(bufferMutex);
            item = buffer.front();
            buffer.pop();
            cout << "Consumed item: " << item << endl;}
        empty.signal();
    }
}

int main(int argc, char const *argv[])
{
    cout << "Enter number of items to produce/consume: ";
    cin >> item_count;

    thread producerThread(producer);
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();
    return 0;
}