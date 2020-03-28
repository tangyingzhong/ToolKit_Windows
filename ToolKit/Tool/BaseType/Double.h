///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Double class which can support conversion with string
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef DOUBLE_H
#define DOUBLE_H

#include "String.h"

namespace System
{
	namespace BasicType
	{
		class Double
		{
		public:
			// Contruct a Double 
			Double();

			// Contruct a Double with a value 
			Double(double dValue);

			// Destruct the Double
			~Double();

			// Allow the object copying
			Double(const Double& Another);

			// Allow the obejct assignment
			Double& operator=(const Double& Another);

		public:
			// Implement the + object
			Double operator+(Double& Another);

			// Implement the + value
			Double operator+(double dValue);

			// Implement the += object
			Double operator+=(Double& Another);

			// Implement the += value
			Double operator+=(double dValue);

			// Implement the -= object
			Double operator-=(Double& Another);

			// Implement the -= value
			Double operator-=(double dValue);

			// Implement the - object
			Double operator-(Double& Another);

			// Implement the - value
			Double operator-(double dValue);

			// Implement the * object
			Double operator*(Double& Another);

			// Implement the * value
			Double operator*(double dValue);

			// Implement the / object
			Double operator/(Double& Another);

			// Implement the / value
			Double operator/(double dValue);

			// Override the double type
			operator double() const;

			// Parse the string to the value
			static Double Parse(String NumberString);

			// Make the value to string
			String ToString();

		private:
			// Get the Value
			inline double GetValue() const
			{
				return m_Value;
			}

			// Set the Value
			inline None SetValue(double dValue)
			{
				m_Value = dValue;
			}

		private:
			// Double value
			double m_Value;
		};
	}
}

#endif // DOUBLE_H