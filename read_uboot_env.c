#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_READ 65536

static int ifMatch(FILE* fin, const char* target)
{
	char buff[MAX_READ + 1];
	const char* state = target;
	int found = 0;

	while (!feof(fin) && (0 == found)) {
		size_t bytes = fread(buff, 1, MAX_READ, fin);
		buff[bytes] = '\0';

		for (int i = 0; i < bytes; ++i) {
			if(1 == found)
				if(buff[i] != '\0') {
					printf("%c", buff[i]);
				} else {
					break;
				}

			if (*state == buff[i]) {
				++state;
				if (*state == '\0') {
					found = 1;
					fputs(target, stdout);
				}
			} else {
				state = target;
			}
		}
	}

	return found;
}

int main(int argc, char *argv[])
{
	FILE *uboot = fopen( "uboot.img", "rb");

	if (uboot)
		ifMatch(uboot, argv[1]);

	fclose(uboot);

	return 0;
}
