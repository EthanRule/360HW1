// cathw.c

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void filecopy(int ifd, int ofd);
static void error(char *fmt, ...); // can be used to generate error message

int main(int argc, char *argv[]) {
	// complete your code
	return 0;
}

void filecopy(int ifd, int ofd) {
	// complete your code
}

// no modification needed
void error(char *fmt, ...) {
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}
