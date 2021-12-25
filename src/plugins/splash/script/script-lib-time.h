#ifndef SCRIPT_LIB_TIME_H
#define SCRIPT_LIB_TIME_H

#include "script.h"

typedef struct
{
        script_op_t *script_main_op;
} script_lib_time_data_t;

script_lib_time_data_t *script_lib_time_setup (script_state_t *state);
void script_lib_time_destroy (script_lib_time_data_t *data);

#endif /* SCRIPT_LIB_TIME_H */
