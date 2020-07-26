#pragma once

#ifdef __cplusplus
extern "C" {
#endif

static char cpu_name[49] = {0}; // NOLINT(*-c-arrays,*-magic-numbers-*)

const char* get_cpu_name(void);

#ifdef __cplusplus
}
#endif