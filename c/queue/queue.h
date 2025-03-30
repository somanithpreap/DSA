#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct QueueNode {
    char* data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue();
bool queueIsEmpty(Queue* queue);
void enqueue(Queue** queue, char* data);
char* dequeue(Queue* queue);
char* peekQueue(Queue* queue);

void reverseQueue(Queue* queue);
void clearQueue(Queue* queue);
void destroyQueue(Queue** queue);

#endif
