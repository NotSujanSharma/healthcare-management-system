#ifndef SENECA_PATIENT_H
#define SENECA_PATIENT_H
#include "IOAble.h"
#include "Ticket.h"
namespace seneca

{
	const int MIN = 100000000;
	const int MAX = 999999999;
	class Patient : public IOAble
	{
		char *m_patient_name{};
		int m_OHIP_number{};
		Ticket m_ticket = 0;

	protected:
		bool m_normalPrint = false;

	public:
		/**
		 * @brief Construct a new Patient object
		 *
		 * @param number
		 */

		Patient(int number);

		/**
		 * @brief Construct a new Patient object
		 *
		 * @param patient
		 */
		Patient(const Patient &patient);

		/**
		 * @brief Copy assignment operator
		 *
		 * @param patient
		 * @return Patient&
		 */
		Patient &operator=(const Patient &patient);

		/**
		 * @brief Destroy the Patient object
		 *
		 */
		virtual ~Patient();

		/**
		 * @brief Returns the type of the patient
		 *
		 * @return char
		 */

		virtual char type() const = 0;

		/**
		 * @brief Compare the patient with a char
		 *
		 * @param ch
		 * @return true
		 * @return false
		 */

		virtual bool operator==(const Patient &p) const;

		/**
		 * @brief Compare the patient with another patient
		 *
		 * @param ch
		 * @return true
		 * @return false
		 */
		virtual bool operator==(const char ch) const;

		/**
		 * @brief Returns the arrival time of the patient
		 *
		 * @return Time
		 */

		Time time() const;

		/**
		 * @brief Returns the name of the patient
		 *
		 * @return const char*
		 */
		operator const char *() const;

		/**
		 * @brief Returns the OHIP number of the patient
		 *
		 * @return int
		 */
		operator bool() const;

		/**
		 * @brief Returns the ticket number of the patient
		 *
		 * @return unsigned int
		 */
		unsigned int number() const;

		/**
		 * @brief Sets the arrival time of the patient
		 *
		 */
		void setArrivalTime();

		void normalPrint(bool value);

		/**
		 * @brief Writes the patient information to the output stream
		 *
		 * @param ostr
		 * @return std::ostream&
		 */
		std::ostream &write(std::ostream &ostr = std::cout) const override;

		/**
		 * @brief Reads the patient information from the input stream
		 *
		 * @param istr
		 * @return std::istream&
		 */
		std::istream &read(std::istream &istr = std::cin) override;
	};
}
#endif