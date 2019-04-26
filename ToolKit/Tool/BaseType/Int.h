///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// You can use it as common int you are similiar to.
/// And it supports transferring to/from String
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef INT_H
#define INT_H

#include "String.h"

namespace System
{
	namespace BasicType
	{
		///*********************************************************
		/// <class> Int </class>
		/// <summary>
		/// Make it as an value we used to,so that we can make it powerful
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///*********************************************************/
		class Int
		{
		public:
			typedef System::Empty Empty;
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
			Int& operator++(int);

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
			// Get the Value
			inline int GetValue() const
			{
				return m_Value;
			}

			// Set the Value
			inline Empty SetValue(int iValue)
			{
				this->m_Value = iValue;
			}

		private:
			// Int value
			int m_Value;
		};
	}
}

#endif //INT_TANG_H_