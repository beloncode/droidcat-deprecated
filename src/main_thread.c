#if defined(__unix__)
    #include <unistd.h>
    #include <errno.h>
#endif

typedef signed int i32;

_Static_assert(sizeof (i32) == 4, "Sizeof integer is different from 4,"
    " this may lead for various errors and undefined behaviors");

typedef enum cerberus_level {
    CERBERUS_LE_SUCCESS,

    CERBERUS_LE_ERROR

} cerberus_level_e;

// Trapdoor communication between the log system and the stdout printable format
typedef enum cerberus_status {
    CERBERUS_ST_PROC_INIT_ERROR,

    CERBERUS_PROC_INITIALIZED

} cerberus_status_e;

typedef enum cerberus_err_spec {
    CERBERUS_ERR_SPEC_SYSCALL = 1

} cerberus_err_spec_e;

typedef struct cerberus_msg_location {
    int local_line;
    
    const char* local_filename;

} cerberus_msg_location_t;

typedef struct cerberus_msg_info {
    cerberus_level_e msg_level;

    cerberus_status_e msg_status;

    cerberus_err_spec_e msg_error_advanced;
    
    cerberus_msg_location_t* msg_location;

} cerberus_msg_info_t;

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

i32 cerberus_prepare([[maybe_unused]] const cerberus_msg_info_t* msg_info, [[maybe_unused]] droidcat_ctx_t* droidcat_ctx, 
    [[maybe_unused]] const char* restrict format, ...) {

    return 0;
}

// This expression will be compressing inside only once line, this mean that:
// __LINE__ and __FILE_NAME__ will pointer to the correct location!
#define cerberus_log(level, status, special, droidcat_ctx, format, ...)\
    do {\
        \
        cerberus_msg_location_t stack_msg_location = {\
            __LINE__, __FILE_NAME__\
        };\
        \
        cerberus_msg_info_t stack_msg_info = {\
            CERBERUS_LE_ERROR, status, special, &stack_msg_location\
        };\
        \
        cerberus_prepare((const cerberus_msg_info_t*)&stack_msg_info, droidcat_ctx, format, __VA_ARGS__);\
        \
    } while (0)

#define cerberus_log_error(status, special, droidcat_ctx, format, ...)\
    cerberus_log(CERBERUS_LE_ERROR, status, special, droidcat_ctx, format, __VA_ARGS__)

i32 main() {
    #if defined (__OpenBSD__)
    // Restricting the process operation for a enhanced security!
    const i32 proc_contract = pledge("stdio", NULL);

    if (proc_contract == -1) {
        cerberus_log_error(CERBERUS_ST_PROC_INIT_ERROR, CERBERUS_ERR_SPEC_SYSCALL, NULL, 
            "BSD pledge has failed because: %s\n", "");
    }

    #endif

    return 0;
}
