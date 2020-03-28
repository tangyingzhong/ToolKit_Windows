///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// You can use it as common int you are similiar to.
/// And it supports transferring to/from String
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef INT_H
#define INT_H

#include "String.h"

namespace System
{
	namespace BasicType
	{
		class Int
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;

		public:
			// Contruct a int 
			Int();

			// Contruct an int with a value 
			Int(int iValue);

			// Destruct the int
			~Int();

			// Allow the value copying
			Int(const Int& other);

			// Allow the obejct assignment
			Int& operator=(const Int& other);

		public:
			// Implement the + value
			Int operator+(Int& other);

			// Implement the + value
			Int operator+(int value);

			// Implement the += value
			Int operator+=(Int& other);

			// Implement the += value
			Int operator+=(int value);

			// Implement the -= value
			Int operator-=(Int& other);

			// Implement the -= value
			Int operator-=(int value);

			// Implement the - value
			Int operator-(Int& other);

			// Implement the - value
			Int operator-(int value);

			// Implement the * value
			Int operator*(Int& other);

			// Implement the * value
			Int operator*(int value);

			// Implement the / value.Failed return -1
			Int operator/(Int& other);

			// Implement the / value.Failed return -1
			Int operator/(int value);

			// Implement the % value
			Int operator%(Int& other);

			// Implement the % value
			Int operator%(int value);

			// Implement the == value
			BOOL operator==(Int& other);

			// Implement the % value
			BOOL operator==(int value);

			// Implement the != value
			BOOL operator!=(Int& other);

			// Implement the % value
			BOOL operator!=(int value);

			// Implement the << value
			Int operator<<(Int& other);

			// Implement the << value
			Int operator<<(int value);

			// Implement the >> value
			Int operator >> (Int& other);

			// Implement the >> value
			Int operator >> (int value);

			// Implement the ! value
			BOOL operator!();

			// Implement the value++ 
			Int& operator++();

			// Implement the ++value
			Int operator++(int);

			// Implement the >value
			BOOL operator>(Int& other);

			// Implement the > value
			BOOL operator>(int value);

			// Implement the >=value
			BOOL operator>=(Int& other);

			// Implement the >= value
			BOOL operator>=(int value);

			// Implement the <value
			BOOL operator<(Int& other);

			// Implement the < value
			BOOL operator<(int value);

			// Implement the <=value
			BOOL operator<=(Int& other);

			// Implement the < value
			BOOL operator<=(int value);

			// Override the int type
			operator int() const;

			// Parse the string to value
			static Int Parse(String NumberString);

			// Make the value to string
			String ToString();

		private:
			// Equal to another one
			BOOL Equal(Int Another);

		private:
			// Get the Value
			inline int GetValue() const
			{
				return m_Value;
			}

			// Set the Value
			inline None SetValue(int iValue)
			{
				m_Value = iValue;
			}

		private:
			// Int value
			int m_Value;
		};
	}
}

#endif // INT_H