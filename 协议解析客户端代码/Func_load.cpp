#include"Func_load.h"
#include<stdio.h>

void Message_print(u_char* message, int len) {
	for (int i = 0; i < len; i++) {
		printf("0x%.2x ", message[i]);
	}
}

int message_len(u_char* a) {
	int i = 0;
	while (a[i] != 204) {
		i++;
	}
	return i;
}