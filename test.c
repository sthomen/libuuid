#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "uuid.h"
#include <stdio.h>

void test_that_uuid_generate_random_follows_spec(void **state) {
	uuid_t uuid;
	uuid_generate_random(uuid);

	// NOTE: this implementation only supports version 4 variant 1 UUIDs

	assert_int_equal(uuid[6] & 0xf0, 0x40);
	assert_int_equal(uuid[8] & 0xf0, 0xa0);
}

void test_that_uuid_parse_can_load_an_uuid(void **state) {
	uuid_t uuid;
	char str[37]="6e207c1a-0f83-4f1b-ac8f-e33da5dd4d5e";

	uuid_parse(str, uuid);

	assert_int_equal(uuid[0], 0x6e);
	assert_int_equal(uuid[1], 0x20);
	assert_int_equal(uuid[2], 0x7c);
	assert_int_equal(uuid[3], 0x1a);
	assert_int_equal(uuid[4], 0x0f);
	assert_int_equal(uuid[5], 0x83);
	assert_int_equal(uuid[6], 0x4f);
	assert_int_equal(uuid[7], 0x1b);
	assert_int_equal(uuid[8], 0xac);
	assert_int_equal(uuid[9], 0x8f);
	assert_int_equal(uuid[10], 0xe3);
	assert_int_equal(uuid[11], 0x3d);
	assert_int_equal(uuid[12], 0xa5);
	assert_int_equal(uuid[13], 0xdd);
	assert_int_equal(uuid[14], 0x4d);
	assert_int_equal(uuid[15], 0x5e);
}

void test_that_uuid_unparse_creates_a_properly_formatted_string(void **state) {
	uuid_t uuid;
	uuid_generate_random(uuid);
	char str[37];

	uuid_unparse(uuid, str);

	// there should always be dashes here
	assert_int_equal(str[8], '-');
	assert_int_equal(str[13], '-');
	assert_int_equal(str[18], '-');
	assert_int_equal(str[23], '-');

	// verison 4, variant 1 (a)
	assert_int_equal(str[14], '4');
	assert_int_equal(str[19], 'a');
}

void test_uuid_copy(void **state) {
	uuid_t uuid1;
	uuid_t uuid2;

	uuid_generate_random(uuid1);
	uuid_copy(uuid2, uuid1);

	assert_int_equal(uuid1[0], uuid2[0]);
	assert_int_equal(uuid1[1], uuid2[1]);
	assert_int_equal(uuid1[2], uuid2[2]);
	assert_int_equal(uuid1[3], uuid2[3]);
	assert_int_equal(uuid1[4], uuid2[4]);
	assert_int_equal(uuid1[5], uuid2[5]);
	assert_int_equal(uuid1[6], uuid2[6]);
	assert_int_equal(uuid1[7], uuid2[7]);
	assert_int_equal(uuid1[8], uuid2[8]);
	assert_int_equal(uuid1[9], uuid2[9]);
	assert_int_equal(uuid1[10], uuid2[10]);
	assert_int_equal(uuid1[11], uuid2[11]);
	assert_int_equal(uuid1[12], uuid2[12]);
	assert_int_equal(uuid1[13], uuid2[13]);
	assert_int_equal(uuid1[14], uuid2[14]);
	assert_int_equal(uuid1[15], uuid2[15]);
}

int main(void) {
	struct CMUnitTest tests[] = {
		cmocka_unit_test(test_that_uuid_generate_random_follows_spec),
		cmocka_unit_test(test_that_uuid_parse_can_load_an_uuid),
		cmocka_unit_test(test_that_uuid_unparse_creates_a_properly_formatted_string),
		cmocka_unit_test(test_uuid_copy)
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}

