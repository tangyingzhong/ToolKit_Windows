///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It can accept any type characters and it is easily to be used
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef STRING_H
#define STRING_H

#include <vector>
#include "Tool/Common/SystemType.h"
#include "Tool/Buffer/Array.h"

using namespace std;
using namespace System;
using namespace System::Buffer;

namespace System
{
	namespace BasicType
	{
		class String
		{
		public:
			typedef Int32 Index;
			typedef Int32 Length;
			typedef Boolean BOOL;
			typedef Empty Empty;
			typedef Int32 Integer;
			typedef Character Character;
			typedef CharArray CharArray;
			typedef StdString StdString;
			typedef StringStream StringStream;
			typedef std::vector<String> StringTable;

		public:
			// Contruct an empty string
			String();

			// Destruct the string
			~String();
#ifdef UNICODE
			// Construct the string auto from ansi string
			String(const std::string strAnsiString);
#else
			// Construct the string auto from wide string from ansi string
			String(const std::wstring strWString);
#endif
			// Contruct a string with STL string
			String(StdString OtherStdString);

			// Contruct a string with C-type string
			String(const CharArray pString);

		public:
			// Allow the string copying
			String(const String& other);

			// Allow the string assignment
			String& operator=(const String& other);

		public:
			// Split the string by a seperator
			BOOL Split(String strSeperator, StringTable& vStringTable);

			// Sub the string to get a new string
			String SubString(Index iStartIndex, Length iSubLength);

			// Sub the string to the end
			String SubString(Index iStartIndex);

			// Get the string from the left
			String Left(Length iLength);

			// Get the string from the rigth
			String Right(Length iLength);

			// Find the appearance character in the string and return its's position,failed return -1
			Index Find(String strSpecialStr, Index iStartPos);

			// Find last character in the string,failed return -1
			Index FindLast(String strSpecialStr);

			// Replace the string by another one
			String& Replace(Index iReplacePos, Length iReplaceLength, String strReplaceString);

			// Fill the string with int placeholder(%s)
			String& Arg(String strPlaceholderValue);

			// Fill the string with int placeholder(%d)
			String& Arg(Integer iPlaceholderValue);

			// Fill the string with int placeholder(%f)
			String& Arg(Single fPlaceholderValue);

			// Fill the string with int placeholder(%lf)
			String& Arg(Real dPlaceholderValue);

			// Contain a sub string or not
			BOOL IsContain(String strSubString);

			// Contain how many character you want
			Integer Contains(SByte ch);

			// Append a new std string to the string
			String& Append(StdString& OtherStdString);

			// Get the wide string when you are in ANSI environment to program
			WByteArray AllocWideString();

			// Utf8 string ((UNICODE->ANSI->UTF8 or only ANSI->UTF8))
			std::string ToUtf8Data();

			// ANSI string ((UNICODE->ANSI or only ANSI))
			std::string ToAnsiData();

			// Unicode string
			std::wstring ToUnicodeData();

			// Make string upper
			String& MakeUpper();

			// Make string lower
			String& MakeLower();

			// Get a character from the string. Fialed return 'N'
			Character operator[](Index iPos);

			// Cohesion string to be a new string
			String& operator+(String OtherString);

			// Is string equals to the other one
			BOOL operator==(String OtherString);

			// Is string not equals to the other one
			BOOL operator!=(String OtherString);

			// Set empty string
			Empty SetEmpty();

			// Is empty string
			BOOL IsEmpty();

			// Get C-type string 
			LPCTSTR CStr();

			// Get string's length
			inline Length GetLength() const
			{
				return m_Length;
			}

			// Parse the string to base type number
			template <class BaseType>
			static BaseType Parse(String NumberString)
			{
				// Streaming the string
				StringStream Streamer;
				Streamer << NumberString.GetStdString();

				// Format the stream to number
				BaseType Number;
				Streamer >> Number;

				return Number;
			}

			// Make a number to string
			template <class BaseType>
			static String ToString(BaseType Number)
			{
				// Make number to be stream
				StringStream Streamer;
				Streamer << Number;

				// Stream the data to string
				StdString strInnerString = _T("");
				Streamer >> strInnerString;

				return strInnerString;
			}

			// Create GUID
			static String CreateGUID();

		private:
			// Initialize the String
			Empty Initialize(StdString OtherStdString);

			// Destory the String
			Empty Destroy();

			// Create a c type array
			Empty CreateCArray();

			// Destory the c type array
			Empty DestoryCArray();

			// Is the current string equals to the other one
			BOOL Equal(String& OtherString);

			// Fill the placeholder
			String& FillPlaceholder(String strPlaceholder, String strPlaceholderValue);

			// Guid to string
			static String ConvertGuid(const GUID& guid);

		private:
			// Get std string
			inline StdString GetStdString() const
			{
				return m_StdString;
			}

			// Set std string
			inline Empty SetStdString(StdString OtherStdString)
			{
				m_StdString = OtherStdString;
			}

			// Set string's length
			inline Empty SetLength(Length iLength)
			{
				m_Length = iLength;
			}

			// Get the C type array
			inline Array<Character>* GetCArray() const
			{
				return m_pCArray;
			}

			// Set the C type array
			inline Empty SetCArray(Array<Character>* pCArray)
			{
				m_pCArray = pCArray;
			}

			// Get the Disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the Disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// STL string
			StdString m_StdString;

			// String's length(bytes total)
			Length m_Length;

			// C type array 
			Array<Character>* m_pCArray;

			// Wide string's pointer
			Array<WByte> m_WideArray;

			// Dispoed status
			BOOL m_Disposed;
		};
	}
}

#endif // STRING_H