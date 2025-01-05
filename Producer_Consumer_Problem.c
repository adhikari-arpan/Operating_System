#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 10

int buffer[SIZE];
int in = 0, out = 0, mutex = 1, full = 0, empty = SIZE;

void producer(void) {
    int num = rand() % 100;

    --mutex;
    --empty;

    buffer[in] = num;
    in = (in + 1) % SIZE;
    printf("Produced: %d\n", num);

    ++mutex;
    ++full;
}

void consumer(void) {
    int item;

    --mutex;
    --full;

    item = buffer[out];
    out = (out + 1) % SIZE;
    printf("Consumed: %d\n", item);

    ++mutex;
    ++empty;
}

int main() {
int count = 10;
     while (count!=0) {
        if (empty > 0 && mutex == 1) { 
        producer();
        } else {
            printf("Buffer is full\n");
        }

        if (full > 0 && mutex == 1) { 
            consumer();
        } else {
            printf("Buffer is empty\n");
        }
    count --;
        sleep(1); 
    }

    return 0;
}