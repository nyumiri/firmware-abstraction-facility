#ifndef UNIT_TEST_MEMORY_T_H
#define UNIT_TEST_MEMORY_T_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#ifdef __cplusplus
extern "C" {
#endif

void test_memory_corrupt(void);
void test_memory_malicious_assigned(void);

#ifdef __cplusplus
}
#endif

#endif // UNIT_TEST_MEMORY_T_H