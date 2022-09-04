#include <stdio.h>

int var = 0x8; // 1A
//extern int var; // 2A

int increment();

int main() {
	printf("%d\n", var);
	var++;
	increment();	
	printf("%d\n", var);	
}
