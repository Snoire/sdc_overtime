//#define _GNU_SOURCE    // 这有啥用？不加也行
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
	FILE *out, *in;
	int v, s;
	size_t size;
	char *ptr;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s '<num>...'\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	in = fmemopen(argv[1], strlen(argv[1]), "r");
	if (in == NULL)
		handle_error("fmemopen");

	out = open_memstream(&ptr, &size);
	if (out == NULL)
		handle_error("open_memstream");

	for (;;) {
		s = fscanf(in, "%d", &v);
		if (s <= 0)
			break;

		s = fprintf(out, "%d ", v * v);
		if (s == -1)
			handle_error("fprintf");
	}

#if 1
	fclose(in);

    fflush(out);      // 这个不写就没法用
	printf("size=%zu; ptr=%s\n", size, ptr);

//	fclose(out);      // 奇怪，这里关掉也能用。。
    rewind(out);
    printf("strlen(ptr): %zu, size: %zu\n", strlen(ptr), size);
    memset(ptr, 0, strlen(ptr));
    fprintf(out, "test string..\n");

//	printf("size=%zu; ptr=%s\n", size, ptr);
//    fflush(out);     // 这个就不需要，不知道为什么
	printf("after fflush, size=%zu; ptr=%s\n", size, ptr);

	fclose(out);
#else
	fclose(in);
	fclose(out);

	printf("size=%zu; ptr=%s\n", size, ptr);
#endif

	free(ptr);
	exit(EXIT_SUCCESS);
}

