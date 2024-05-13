#ifndef TESTPATIENT_H
#define TESTPATIENT_H

#include "Patient.h"
#include <iostream>

namespace seneca
{

    class TestPatient : public Patient
    {
    private:
        static int m_ticketNumber;

    public:
        /**
         * @brief Construct a new Test Patient object
         *
         */
        TestPatient();

        /**
         * @brief Destroy the Test Patient object
         *
         */
        virtual ~TestPatient();

        /**
         * @brief Get the type object
         *
         * @return char
         */
        virtual char type() const override;

        /**
         * @brief Read the object
         *
         * @param istr
         * @return std::istream&
         */
        virtual std::ostream &write(std::ostream &ostr) const override;

        /**
         * @brief Write the object
         *
         * @param ostr
         * @return std::ostream&
         */
        virtual std::istream &read(std::istream &istr) override;
    };
}

#endif
