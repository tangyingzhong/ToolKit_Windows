///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Basic type with the value:true or false
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef BOOL_H
#define BOOL_H

#include "String.h"

namespace System
{
	namespace BasicType
	{
		class Bool
		{
		public:
			// Construct the Bool
			Bool();

			// Construct the Bool with value
			Bool(bool bValue);

			// Detructe the Bool
			~Bool();

			// Allow the object copying
			Bool(const Bool& Another);

			// Allow the obejct assignment
			Bool& operator=(const Bool& Another);

		public:
			// Get the opposite result
			Bool operator!();

			// Wether they are eqauled or not
			Bool operator==(const Bool& Another);

			// Wether they are eqauled or not
			Bool operator==(const bool bValue);

			// Wether they are eqauled or not
			Bool operator!=(const Bool& Another);

			// Wether they are eqauled or not
			Bool operator!=(const bool bValue);

			// Override the bool type
			operator bool() const;

			// Parse the "true" or "false" to bool
			static Bool Parse(String& BoolString);

			// Bool value converts to be string
			String ToString();

		private:
			// Equal to another one
			Bool Equal(Bool bValue);

		private:
			// Get the bool value
			inline bool GetValue() const
			{
				return m_Value;
			}

			// Set the bool value
			inline None SetValue(bool bValue)
			{
				m_Value = bValue;
			}

		private:
			// Bool value
			bool m_Value;
		};
	}
}

#endif // BOOL_H