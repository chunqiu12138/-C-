#include<stdio.h>

int rec_fibonacci(int n) {
	if (n == 0 || n == 1) return n;
	return rec_fibonacci(n-2)+rec_fibonacci(n-1);
}

int main() {
	int n;
	scanf("%d",&n);
	printf("%d",rec_fibonacci(n));
}