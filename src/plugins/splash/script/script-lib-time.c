#include "config.h"

#include "ply-utils.h"
#include "script.h"
#include "script-parse.h"
#include "script-execute.h"
#include "script-object.h"
#include "script-lib-time.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "script-lib-time.script.h"

static script_return_t script_lib_time_gettimeformat (script_state_t *state,
                                               void           *user_data)
{
        char substring[100];

        char *stringFormat = script_obj_hash_get_string (state->local, "stringFormat");

        time_t t = time(NULL);
        struct tm* time = localtime(&t);

        strftime(substring, 100, stringFormat, time);
        free(stringFormat);

        return script_return_obj (script_obj_new_string (substring));
}

script_lib_time_data_t *script_lib_time_setup (script_state_t *state)
{
        script_lib_time_data_t *data = malloc (sizeof(script_lib_time_data_t));

        script_obj_t *time_hash = script_obj_hash_get_element (state->global, "Time");
        script_add_native_function (time_hash,
                                    "GetTimeFormat",
                                    script_lib_time_gettimeformat,
                                    NULL,
                                    "stringFormat",
                                    NULL);
        script_obj_unref (time_hash);

        data->script_main_op = script_parse_string (script_lib_time_string, "script-lib-time.script");
        script_return_t ret = script_execute (state, data->script_main_op);
        script_obj_unref (ret.object);

        return data;
}

void script_lib_time_destroy (script_lib_time_data_t *data)
{
        script_parse_op_free (data->script_main_op);
        free (data);
}
