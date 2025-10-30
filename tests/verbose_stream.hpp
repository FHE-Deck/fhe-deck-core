#include <iostream>

extern bool verbose;

class VerboseStream {
public:
    VerboseStream(std::ostream& os) : os_(os) {}

    template<typename T>
    VerboseStream& operator<<(const T& value) {
        if (verbose)
            os_ << value;
        return *this;
    }

    // Support manipulators like std::endl, std::flush, etc.
    VerboseStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        if (verbose)
            manip(os_);
        return *this;
    }

private:
    std::ostream& os_;
};

// Define global instances for convenience
inline VerboseStream print_out(std::cout);
inline VerboseStream print_err(std::cerr);