#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>

typedef int32_t i32;

typedef struct user_options
{
  bool interactive_mode;
  bool display_welcome;

} user_options_t;

typedef struct droidcat_ctx
{
  user_options_t* user_interact;

} droidcat_ctx_t;

#define DROID_ALLOCATE_SAFE(type_inference, elements_count)\
  (type_inference*)calloc(elements_count, sizeof(type_inference))

i32 droidcat_init(droidcat_ctx_t* droidcat_ctx) 
{
  if (droidcat_ctx == NULL) return -1;

  droidcat_ctx->user_interact = DROID_ALLOCATE_SAFE(user_options_t, 1);
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

i32 main(void)
{
  droidcat_ctx_t* droidcat_proc_ctx = DROID_ALLOCATE_SAFE(droidcat_ctx_t, 1);
  i32 droidcat_status = 0;

  if ((droidcat_status = droidcat_init(droidcat_proc_ctx)) != 0)
  {
    free(droidcat_proc_ctx);
    return droidcat_status;
  }

  droidcat_deinit(droidcat_proc_ctx);

  free(droidcat_proc_ctx);
  return 0;
  
}
