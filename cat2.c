#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Notes on system operaters from the man 2 pages
 * open("file name", operation) operation can be O_RDONLY | O_WRONLY | O_RDWR...
 * write(file descripter(int), message string, sizeof the message string)
 * lseek(file descripter(int), 0, SEEK_SET)
 * read(file descripter(int), buffer(this is where the message will be stored), sizeof buffer);
 * close(file descripter(int))
 * */

/*Resources I used for help:
 * https://c-for-dummies.com/blog/?p=4711
 * https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
 * https://www.youtube.com/watch?v=CHs9WwvEKdg
 * */

#define STDIN 0
#define STDOUT 1

static void filecopy(int ifd, int ofd);
static void error(char *fmt, ...);

int main(int argc, char *argv[]) {
	int fd;

	if (argc == 1)
		filecopy(STDIN, STDOUT);
	else
		while (--argc > 0)
			if ((fd = open(*++argv, O_RDONLY)) == -1) // -1 since int not FILE*
			{
				error("can't open %s", *argv);
			}
			else
			{
				filecopy(fd, STDOUT);
				close(fd);
			}
	return 0;
}

void filecopy(int ifd, int ofd) {
	int c;
	char buffer[BUFSIZ];

	while ((c = read(ifd, buffer, BUFSIZ)) > 0)
		if (write(ofd, buffer, c) != c) {
			error("write error");
		}
}

void error(char *fmt, ...) {
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}
