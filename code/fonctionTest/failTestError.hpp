#ifndef FAILTEST
#define FAILTEST

#include <exception>
#include <stdexcept>



/**
 * @brief Exception to report failed test
 */
class FailTestError : public std::logic_error
{
public:

    /// @brief Constructor
    /// @param[in] what_arg Description of the error
    explicit FailTestError(std::string const & what_arg) :
        std::logic_error(what_arg)
    { }

    /// @copydoc except::FailTestError::FailTestError(std::string const &)
    explicit FailTestError(char const * const what_arg) :
        std::logic_error(what_arg)
    { }

    /// @brief Return the description of the error
    /// @return the description of the error
    virtual char const * what() const noexcept
    {
        return std::logic_error::what();
    }
};


#endif
