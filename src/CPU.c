#include "CPU.h"

#include <cpuid.h>

static const unsigned int CPUID_BRAND_STRING = 0x80000002;

const char* get_cpu_name(void) {
    if (cpu_name[0] == '\0') {
        for (int i = 0; i <= 2; i++) {
            int offset = 16 * i;
            unsigned int* const base = (unsigned int*)(cpu_name + offset);
            __get_cpuid(CPUID_BRAND_STRING + i, base, base + 1, base + 2, base + 3);
        }
    }
    return cpu_name;
}