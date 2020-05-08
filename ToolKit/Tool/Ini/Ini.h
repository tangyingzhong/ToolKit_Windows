///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Ini configure file's parsing tool
///</describe>
/// <date>2020/5/8</date>
///***********************************************************************
#ifndef INI_H
#define INI_H

#include "Tool/BaseType/String.h"
#include "Tool/BaseType/Bool.h"
#include "Tool/BaseType/Int.h"
#include "Tool/BaseType/Double.h"
#include "Tool/Common/SystemType.h"

using namespace System;
using namespace System::BasicType;

namespace System
{
	class Ini
	{
	public:
		// Construct the Ini
		Ini(String strIniFilePath);

		// Detructe the Ini
		virtual ~Ini();

	private:
		// Forbid the copy Ini
		Ini(const Ini& other){ };

		// Forbid the assigment of Ini
		Ini& operator=(const Ini& other) { return *this; };

	public:
		// Get key's value
		Boolean GetKeyValue(String strAppName, String strKey, String& strDefaultValue);

		// Get key's value
		Boolean GetKeyValue(String strAppName, String strKey, Int& iDefaultValue);

		// Get key's value
		Boolean GetKeyValue(String strAppName, String strKey, Double& dDefaultValue);

		// Get key's value
		Boolean GetKeyValue(String strAppName, String strKey, Bool& bDefaultValue);

		// Set key's value
		Boolean SetKeyValue(String strAppName, String strKey, String strValue);

		// Set key's value
		Boolean SetKeyValue(String strAppName, String strKey, Int iValue);

		// Set key's value
		Boolean SetKeyValue(String strAppName, String strKey, Double dValue);

		// Set key's value
		Boolean SetKeyValue(String strAppName, String strKey, Bool bValue);

		// Get error message
		String GetErrorMsg();

	private:
		// Get key's value
		Boolean GetValue(String strAppName, String strKey, String& strDefaultValue);

		// Set key's value
		Boolean SetValue(String strAppName, String strKey, String strValue);

	private:
		// Get the disposed status
		inline bool GetDisposed() const
		{
			return m_bDisposed;
		}

		// Set the disposed status
		inline void SetDisposed(bool bDisposed)
		{
			m_bDisposed = bDisposed;
		}

		// Get the ErrorText
		inline String GetErrorText() const
		{
			return m_strErrorText;
		}

		// Set the ErrorText
		inline void SetErrorText(String strErrorText)
		{
			m_strErrorText = strErrorText;
		}

		// Get the IniFilePath
		inline String GetIniFilePath() const
		{
			return m_strIniFilePath;
		}

		// Set the IniFilePath
		inline void SetIniFilePath(String strIniFilePath)
		{
			m_strIniFilePath = strIniFilePath;
		}

	private:
		// Ini file path
		String m_strIniFilePath;
		
		// Error message
		String m_strErrorText;
		
		// Disposed status
		bool m_bDisposed;
	};
}

#endif //INI_H
