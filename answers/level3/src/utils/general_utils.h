#include <string>

namespace utils {
    using FD = int;
    static constexpr FD HIGHEST_INVALID_FD = -1;
    
    bool is_valid_fd(FD fd);
    
    inline std::string get_env_or_default(const std::string &key, const std::string &default_value) {
        auto value = getenv(key.c_str());
        if (value == NULL) {
            return default_value;
        }
        return std::string(value);
    }
}