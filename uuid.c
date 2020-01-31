#include <stdlib.h>
#include <time.h>

#include "uuid.h"
#include "config.h"

void uuid_generate_random(uuid_t out) {
	int i, j, rnd;

	srand(time(NULL));

	for (i=0;i<(16/RAND_LENGTH);i++) {
		rnd = rand();

		for (j=0;j<RAND_LENGTH;j++) {
			out[i+j+i] = (0xff & rnd >> (8*j));
		}
	}
}

void uuid_unparse(const uuid_t uuid, char *out) {
	const unsigned char hex[16]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	int i, j;

	i=j=0;

	do {
		switch (j) {
			case 4:
			case 6:
			case 8:
			case 10:
				out[i++]='-';
		}

		out[i++]=hex[(uuid[j] >> 4)];
		out[i++]=hex[(0xf & uuid[j])];

		j++;
	} while (j < 16);

	out[36]=0;
}

void uuid_copy(uuid_t dst, const uuid_t src) {
	int i;
	for (i=0;i<sizeof(uuid_t);i++) {
		dst[i]=src[i];
	}
}
