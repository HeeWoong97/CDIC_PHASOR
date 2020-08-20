#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include "msg_data.h"

int main(void)
{
	key_t key = 12345;
	int msqid;
	struct message msg;
	
	while (1) {
		if ((msqid = msgget(key, IPC_CREAT | 0666)) == -1) {
			printf("msgget failed\n");
			exit(0);
		}
		
		if (msgrcv(msqid, &msg, sizeof(struct real_data), 0, 0) == -1) {
			printf("msgrcv failed\n");
			exit(0);
		}
		
		printf("message received\n");
		printf("num of face : %d\n\n", msg.data.numOfFace);

		if (msgctl(msqid, IPC_RMID, NULL) == -1) {
			printf("msgctl failed\n");
			exit(0);
		}
	}

	return 0;
}
