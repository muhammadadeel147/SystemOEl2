#include <iostream>
#include <thread> 
#include <mutex> 
#include <semaphore.h>

std::mutex lock;
sem_t sem;
int buffer[10];
int count = 0;

void produce() {
for (int i = 0; i < 5; i++) {
    sem_wait(&sem);
    lock.lock();
    buffer[count++] = i;
    std::cout << "Produced: " << i << std::endl;
    lock.unlock();
    sem_post(&sem);
  }
}

void consume() {
for (int i = 0; i < 5; i++) {
    sem_wait(&sem);
    lock.lock();
    std::cout << "Consumed: " << buffer[--count] << std::endl;
    lock.unlock();
    sem_post(&sem);
  }
}

int main() {
sem_init(&sem, 0, 1);

std::thread t1(produce);
std::thread t2(consume);

t1.join();
t2.join();

sem_destroy(&sem);
return 0;
}
