#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LOGGING 1

void wlog(const char *msg)
{
	#if LOGGING
	FILE *f;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	f = fopen("/tmp/blanket.log", "a");
	fprintf(f, "[%d:%d] %s\n", tm.tm_hour, tm.tm_min, msg);
	fclose(f);
	#endif
}

void die(const char *err, int code)
{
	wlog(err);
	exit(code);
}

void *ecalloc(size_t num, size_t size)
{
	void *p;

	if (!(p = calloc(num, size)))
		die("Failed to allocate space", 1);
	return p;
}

void *emalloc(size_t size)
{
    void *p;

    if(!(p = malloc(size)))
        die("Failed to allocate space", 1);
    return p;
}
