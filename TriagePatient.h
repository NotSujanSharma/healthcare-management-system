#ifndef TRIAGEPATIENT_H
#define TRIAGEPATIENT_H

#include "Patient.h"
namespace seneca
{
    class TriagePatient : public Patient
    {
    private:
        char *m_symptom;
        static int m_ticketNumber;

    public:
        /**
         * @brief Construct a new Triage Patient object
         *
         */
        TriagePatient();

        /**
         * @brief Construct a new Triage Patient object
         *
         * @param other
         */
        TriagePatient(const TriagePatient &other);

        /**
         * @brief Assignment operator
         *
         * @param other
         * @return TriagePatient&
         */
        TriagePatient &operator=(const TriagePatient &other);

        /**
         * @brief Destroy the Triage Patient object
         *
         */

        virtual ~TriagePatient();

        /**
         * @brief Get the type object
         *
         * @return char
         */
        virtual char type() const override;

        /**
         * @brief Write the object
         *
         * @param ostr
         * @return std::ostream&
         */
        virtual std::istream &read(std::istream &istr) override;

        /**
         * @brief Read the object
         *
         * @param ostr
         * @return std::ostream&
         */
        virtual std::ostream &write(std::ostream &ostr) const override;
    };
}

#endif
