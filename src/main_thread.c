#if defined(__unix__)
    #include <unistd.h>
    #include <errno.h>
#endif

typedef signed int i32;
_Static_assert(sizeof (i32) == 4, "Sizeof integer is different from 4,"
    " this may lead for various errors and undefined behaviors");

typedef enum event_level {
    EVENT_LE_SUCCESS,
    EVENT_LE_ERROR

} event_level_e;

// Trapdoor communication between the log system and the stdout printable format
typedef enum event_status {
    EVENT_ST_PROC_INIT_ERROR,
    EVENT_ST_PROC_INITIALIZED

} event_status_e;

typedef struct droidcat_ctx {

} droidcat_ctx_t;

i32 main_cerberus([[maybe_unused]] const i32 event_level, [[maybe_unused]] droidcat_ctx_t* droidcat_ctx, 
    [[maybe_unused]] const char* fmt_local, ...) {
    
    return 0;
}

i32 cerberus_to_main([[maybe_unused]] const i32 event_id, [[maybe_unused]] droidcat_ctx_t* droidcat_ctx_t, 
    [[maybe_unused]] const char* message_terminator, [[maybe_unused]] const size_t message_len) {

    return 0;
}

i32 main() {
    #if defined (__OpenBSD__)
    // Restricting the process operation for a enhanced security!
    const i32 proc_contract = pledge("stdio", NULL);
    /*
    if (proc_contract == -1) {
        cerberus_log_error(NULL, "#*_ BSD pledge has failed because: %s\n", "");
    }
    */
    #endif

    return 0;
}
