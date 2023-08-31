// you need to include -lrt flag (i.e., real-time libraries or librt) 
// to compile this code 

#include <stdio.h>	
#include <stdlib.h>	
#include <stdint.h>	/* for uint64 definition */
#include <time.h>	/* for clock_gettime */
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

#define STDIN 0
#define STDOUT 1
#define BILLION 1000000000L


void filecopy(FILE*, FILE*);
static void filecopycathw(int ifd, int ofd);
static void error(char *fmt, ...);

main_cathw(int argc, char *argv[]) {
 	// your implementation for cathw
        int fd;

        if (argc == 1)
                filecopycathw(STDIN, STDOUT);
        else
                while (--argc > 0)
                        if ((fd = open(*++argv, O_RDONLY)) == -1) // -1 since int not FILE*
                        {
                                error("can't open %s", *argv);
                        }
                        else
                        {
                                filecopycathw(fd, STDOUT);
                                close(fd);
                        }
        return 0;
}

main_cat(int argc, char*argv[]) {
	FILE *fp;

        if (argc == 1) // No args; copy standard input
                filecopy(stdin, stdout);
        else
                while (--argc > 0)
                        if ((fp = fopen(*++argv, "r")) == NULL)
                        {
                                printf("cat: can't open %s\n", *argv);
                                return 1;
                        }
                        else
                        {
                                filecopy(fp, stdout);
                                fclose(fp);
                        }
        return 0;
}

int main(int argc, char **argv) {
	uint64_t diff;
	struct timespec start, end;
	int i;

  	// measure time
	clock_gettime(CLOCK_MONOTONIC, &start);	// mark start time 
	main_cathw(argc, argv);	// call cat routine
	clock_gettime(CLOCK_MONOTONIC, &end);	// mark the end time 

  	// calcuate difference
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("Run time of cathw = %llu nanoseconds\n", (long long unsigned int) diff);

	return 0;
}

void filecopycathw(int ifd, int ofd) {
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


