// cathw.c

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * open("file name", operation) operation can be O_RDONLY | O_WRONLY | O_RDWR...
 * write(file descripter(int), message string, sizeof the message string)
 * lseek(file descripter(int), 0, SEEK_SET)
 * read(file descripter(int), buffer(this is where the message will be stored), sizeof buffer);
 * close(file descripter(int))
 *
 *
 * */



static void filecopy(int ifd, int ofd);
static void error(char *fmt, ...); // can be used to generate error message

int main(int argc, char *argv[]) {
	// complete your code
	
	int fd;
	char buffer[80];
	char msg[50] = "Hello!";

	fd = open("in1.txt", O_RDWR)
	printf("fd = %d", fd);

	if (fd != -1) // check to see if the file is valid/opened
	{
		printf("in1.txt opened for read write access\n");
		write(fd, msg, sizeof(msg));
		lseek(fd, 0, SEEK_SET);
		read(fd, buffer, sizeof(msg));
		printf("\n %s was written to my file\n", buffer);
		close(fd);
	}
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
