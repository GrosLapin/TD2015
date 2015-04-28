#ifndef ILLEGALARG
#define ILLEGALARG

#include <exception>
#include <stdexcept>


namespace except
{
    /**
     * @brief Exception to report incomplete implementation
     *
     * @code
       #include <hopp/except.hpp>
       @endcode
     */
    class IllegalArgumentError : public std::logic_error
    {
    public:

        /// @brief Constructor
        /// @param[in] what_arg Description of the error
        explicit IllegalArgumentError(std::string const & what_arg) :
            std::logic_error(what_arg)
        { }

        /// @copydoc except::IllegalArgumentError::IllegalArgumentError(std::string const &)
        explicit IllegalArgumentError(char const * const what_arg) :
            std::logic_error(what_arg)
        { }

        /// @brief Return the description of the error
        /// @return the description of the error
        virtual char const * what() const noexcept
        {
            return std::logic_error::what();
        }
    };
}

#endif
