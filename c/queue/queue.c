#include "queue.h"

Queue* createQueue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (!queue) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	queue->front = NULL;
	queue->rear = NULL;
	return queue;
}

bool queueIsEmpty(Queue* queue) {
	if (!queue) return true;
	return queue->front == NULL;
}

void enqueue(Queue** queue, char* data) {
	if (!queue) return;

	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (!newNode) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	newNode->data = data;
	newNode->next = NULL;

	if (!*queue)
		*queue = createQueue();

	if (queueIsEmpty(*queue))
		(*queue)->front = newNode;
	else
		(*queue)->rear->next = newNode;
	(*queue)->rear = newNode;
}

char* dequeue(Queue* queue) {
	if (!queue) return NULL;
	if (queueIsEmpty(queue)) {
		free(queue);
		printf("The queue is empty; there is no element to dequeue.\n");
		exit(1);
	}

	QueueNode* temp = queue->front;
	queue->front = queue->front->next;
	if (!queue->front)
		queue->rear = NULL;
	char* popped = temp->data;
	free(temp);
	return popped;
}

char* peekQueue(Queue* queue) {
	if (!queue) return NULL;
	if (queueIsEmpty(queue)) {
		printf("The queue is empty; there is no element to peek.\n");
		exit(1);
	}
	return queue->front->data;
}

void clearQueue(Queue* queue) {
	if (!queue) return;
	while (!queueIsEmpty(queue))
		free(dequeue(queue));
}

void destroyQueue(Queue** queue) {
	clearQueue(*queue);
	free(*queue);
	*queue = NULL;
}

void reverseQueue(Queue* queue) {
	QueueNode* temp = queue->front;

	QueueNode* prev = NULL;
	QueueNode* current = queue->front;
	QueueNode* next = NULL;

	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	queue->front = prev;
	queue->rear = temp;
}
