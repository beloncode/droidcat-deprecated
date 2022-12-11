#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>

typedef int32_t i32;

typedef struct user_options
{
  bool    interactive_mode;
  bool    display_welcome;

  int     argc_value;
  char**  argv_stack_location;
  char**  env_variables_process;
} user_options_t;

typedef struct droidcat_ctx
{
  user_options_t* user_interact;
} droidcat_ctx_t;

#define DROID_CALLOC_SAFE(type_inference, elements_count)\
  (type_inference*)calloc(elements_count, sizeof(type_inference))

i32 droidcat_init(droidcat_ctx_t* droidcat_ctx) 
{
  if (droidcat_ctx == NULL) return -1;

  droidcat_ctx->user_interact = DROID_CALLOC_SAFE(user_options_t, 1);
  
  if (droidcat_ctx->user_interact == NULL) return -1;

  return 0;
}

i32 droidcat_deinit(droidcat_ctx_t* droidcat_ctx)
{
  if (droidcat_ctx == NULL) return -1;

  if (droidcat_ctx->user_interact != NULL)
  {
    free(droidcat_ctx->user_interact);
  }

  return 0;
}

typedef enum scenario_mode
{
  DEF_PROG_STARTUP = 0
} scenario_mode_e;

i32 user_options_init(int save_argc, char** save_argv, char** save_env, int scenario, droidcat_ctx_t* droidcat_ctx)
{
  static const user_options_t s_def_scene_00 = {
    .interactive_mode = false, 
    .display_welcome = true
  };

  user_options_t* user_options = droidcat_ctx->user_interact;

  const user_options_t* l_copy_default = NULL;

  if (save_argc != 0)
  {
    user_options->argc_value = save_argc;
    user_options->argv_stack_location = save_argv;
    user_options->env_variables_process = save_env;
  }

  switch (scenario)
  {
  case DEF_PROG_STARTUP: l_copy_default = &s_def_scene_00; break;
  }

  if (l_copy_default == NULL) return -1;

  user_options->interactive_mode = l_copy_default->interactive_mode;
  user_options->display_welcome = l_copy_default->display_welcome;

  return 0;
}

i32 main(int argc_list, char** argv_list, char** envrionment_list)
{
  droidcat_ctx_t* droidcat_proc_ctx = DROID_CALLOC_SAFE(droidcat_ctx_t, 1);
  i32 droidcat_status = 0;

  if ((droidcat_status = droidcat_init(droidcat_proc_ctx)) != 0)
  {
    free(droidcat_proc_ctx);
    return droidcat_status;
  }

  user_options_init(argc_list, argv_list, envrionment_list, DFT_PROG_STARTUP, droidcat_proc_ctx);

  droidcat_deinit(droidcat_proc_ctx);

  free(droidcat_proc_ctx);
  return 0;
  
}
