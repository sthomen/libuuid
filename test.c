#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "uuid.h"

int main(int argc, char **argv) {
	uuid_t uuid, copy;
	char str[37];

	uuid_generate_random(uuid);
	uuid_unparse(uuid, str);

	printf("generated = %s\n", str);

	uuid_copy(copy, uuid);
	uuid_unparse(copy, str);

	printf("copy      = %s\n", str);

	return 0;
}

