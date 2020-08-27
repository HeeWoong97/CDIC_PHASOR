#include <stdio.h>

int main(void)
{
	FILE* fp = fopen("../module/detect.txt", "a");
	if(fp == NULL) {
		printf("file open failed\n");
		return -1;
	}

	fprintf(fp, "detect!\n");

	fclose(fp);

	return 0;
}
