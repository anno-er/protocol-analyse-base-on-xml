#include"test.h"
int add(int a, int b) {
	return a + b;
}
int(*padd)(int, int) = &add;
