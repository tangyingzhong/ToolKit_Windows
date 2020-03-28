///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// You can use it as common float you are similiar to.
/// And it supports transferring to/from string
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef FLOAT_H
#define FLOAT_H

#include "String.h"

namespace System
{
	namespace BasicType
	{
		class Float
		{
		public:
			// Contruct a Float 
			Float();

			// Contruct a Float with a value 
			Float(float fValue);

			// Destruct the Float
			~Float();

			// Allow the value copying
			Float(const Float& other);

			// Allow the obejct assignment
			Float& operator=(const Float& other);

		public:
			// Implement the + value
			Float operator+(Float& other);

			// Implement the + value
			Float operator+(float value);

			// Implement the += value
			Float operator+=(Float& other);

			// Implement the += value
			Float operator+=(float value);

			// Implement the -= value
			Float operator-=(Float& other);

			// Implement the -= value
			Float operator-=(float value);

			// Implement the - value
			Float operator-(Float& other);

			// Implement the - value
			Float operator-(float value);

			// Implement the * value
			Float operator*(Float& other);

			// Implement the * value
			Float operator*(float value);

			// Implement the / value
			Float operator/(Float& other);

			// Implement the / value
			Float operator/(float value);

			// Override the float type
			operator float() const;

			// Parse the string to value
			static Float Parse(String NumberString);

			// Make the value to string
			String ToString();

		private:
			// Get the Value
			inline float GetValue() const
			{
				return m_Value;
			}

			// Set the Value
			inline None SetValue(float fValue)
			{
				m_Value = fValue;
			}

		private:
			// Float value
			float m_Value;
		};
	}
}

#endif // FLOAT_H