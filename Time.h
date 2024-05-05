#ifndef TIME_H
#define TIME_H

#include <iostream>

namespace seneca
{
    
    /**
     * @class Time
     * @brief Represents a time value in minutes.
     * 
     * The Time class provides functionality to manipulate and perform operations on time values.
     */
    class Time {
        unsigned int m_minutes; 

    public:
        /**
         * @brief Resets the time value to zero.
         * @return A reference to the modified Time object.
         */
        Time &reset();

        /**
         * @brief Constructs a Time object with the specified time value.
         * @param min The time value in minutes (default is 0).
         */
        Time(unsigned int min = 0u);

        /**
         * @brief Writes the time value to the output stream.
         * @param ostr The output stream to write to (default is std::cout).
         * @return A reference to the output stream.
         */
        std::ostream &write(std::ostream &ostr = std::cout) const;

        /**
         * @brief Reads the time value from the input stream.
         * @param istr The input stream to read from (default is std::cin).
         * @return A reference to the input stream.
         */
        std::istream &read(std::istream &istr = std::cin);

        /**
         * @brief Converts the Time object to an unsigned integer representing the time value in minutes.
         * @return The time value in minutes as an unsigned integer.
         */
        operator unsigned int() const;

        /**
         * @brief Multiplies the time value by the specified integer.
         * @param val The integer value to multiply the time value by.
         * @return A reference to the modified Time object.
         */
        Time &operator*=(int val);

        /**
         * @brief Subtracts the specified Time object from the current Time object.
         * @param D The Time object to subtract.
         * @return A reference to the modified Time object.
         */
        Time &operator-=(const Time &D);

        /**
         * @brief Subtracts the specified Time object from the current Time object and returns the result as a new Time object.
         * @param T The Time object to subtract.
         * @return A new Time object representing the difference between the two Time objects.
         */
        Time operator-(const Time &T) const;

        /**
         * @brief Overloads the << operator to write the time value to the output stream.
         * @param ostr The output stream to write to.
         * @param time The Time object to write.
         * @return A reference to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &ostr, const Time &time);

        /**
         * @brief Overloads the >> operator to read the time value from the input stream.
         * @param istr The input stream to read from.
         * @param time The Time object to read into.
         * @return A reference to the input stream.
         */
        friend std::istream &operator>>(std::istream &istr, Time &time);
    };
}

#endif
