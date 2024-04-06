#include "Queue.h"
#include "Vectors.h"

Vector2 queue[500];
int queueLength = 0;

void enqueue(Vector2 item) {
	queue[queueLength++] = item;
}

Vector2 dequeue() {
	if (queueLength < 1) {
		return;
	}
	Vector2 temp = queue[0];

	for (int i = 1; i <= queueLength; i++) {
		queue[i - 1] = queue[i];
	}

	queueLength--;
	return temp;
}

void clearQueue() {
	while (queueLength > 0)
	{
		dequeue();
	}
}

int getQueueLength() {
	return queueLength;
}