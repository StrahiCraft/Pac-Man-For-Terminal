#include "Vectors.h"
#include <math.h>

int distance(Vector2 a, Vector2 b) {
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

Vector2 getOffset(Vector2 a, Vector2 b) {
	Vector2 offset;
	offset.x = a.x - b.x;
	offset.y = a.y - b.y;

	return offset;
}