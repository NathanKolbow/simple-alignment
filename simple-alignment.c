#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

	while(1) {
		sleep(1);

		FILE *fp;
		fp = popen("/bin/stty size", "r");

		if(fp == NULL) {
			printf("Failed to run command.\n");
			exit(1);
		}

		char out[10];
		fgets(out, sizeof(out)-1, fp);

		int i, sindex, eindex;
		for(i = 0; i < 10; i++) {
			if(out[i] == '\0') {
				eindex = i;
				break;
			}
			if(out[i] == ' ')
				sindex = i;
		}

		char val[5];
		memcpy(val, &out[sindex+1], eindex-sindex);
		val[4] = '\0';

		char *leftText = "Left aligned.";
		char *rightText = "Right aligned.";

		printf("\r%s%*s", leftText, (int)(atoi(val) - strlen(leftText)), "Right aligned.");
		fflush(stdout);
	}
}
