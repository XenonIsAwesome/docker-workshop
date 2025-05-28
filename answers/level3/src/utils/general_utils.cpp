#include "general_utils.h"

namespace utils {
    bool is_valid_fd(FD fd) {
        return fd > HIGHEST_INVALID_FD;
    };
}