#ifndef VECTORS_H_
#define VECTORS_H_

typedef struct Vector2 {
	int x;
	int y;
}Vector2;

int distance(Vector2 a, Vector2 b);
Vector2 getOffset(Vector2 a, Vector2 b);

#endif
