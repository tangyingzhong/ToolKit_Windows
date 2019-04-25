///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// It can accept any type characters and it is easily to be used
///</describe>
/// <date>2019/3/2</date>
///***********************************************************************
#ifndef STRING_H
#define STRING_H

#include "Tool\Buffer\Array.h"

using namespace System::Buffer;

namespace System
{
	namespace BasicType
	{
		///*********************************************************
		/// <class> String </class>
		/// <summary>
		/// We use it casually and it can change to fix the current project encoding
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		class String
		{
		public:
			typedef System::Int32 Index;
			typedef System::Int32 Length;
			typedef System::Boolean BOOL;
			typedef System::Empty Empty;
			typedef System::Character Character;
			typedef System::CharArray CharArray;
			typedef System::StdString StdString;
			typedef System::StringStream StringStream;
			typedef std::vector<String> StringTable;

		public:
			// Contruct an empty string
			String();

			// Destruct the string
			~String();

			// Contruct a string with STL string
			String(StdString& OtherStdString);

			// Contruct a string with C-type string
			String(CharArray pString);

			// Allow the string copying
			String(const String& other);

			// Allow the string assignment
			String& operator=(const String& other);

		public:
			// Split the string by a seperator
			BOOL Split(String strSeperator, StringTable& vStringTable);

			// Sub the string to get a new string
			String SubString(Index iStartIndex, Length iSubLength);

			// Find the appearance character in the string and return its's position
			Index Find(String strSpecialStr, Index iStartPos);

			// Find last character in the string
			Index FindLast(String strSpecialStr);

			// Replace the string by another one
			String& Replace(Index iReplacePos, Length iReplaceLength, String strReplaceString);

			// Get the wide string when you are in ASCII environment to program
			WByteArray AllocWideString();

			// Make string upper
			String& MakeUpper();

			// Make string lower
			String& MakeLower();

			// Get a character from the string at special position
			Character operator[](Index iPos);

			// Cohesion string to be a new string
			String& operator+(String& OtherString);

			// Cohesion std string to be a new string
			String& operator+(StdString& OtherStdString);

			// Cohesion C-type string to be a new string
			String& operator+(CharArray pString);

			// Is string equals to the other one
			BOOL operator==(String& OtherString);

			// Is string not equals to the other one
			BOOL operator!=(String& OtherString);

			// Is std string not equals to the string
			BOOL operator!=(StdString& OtherStdString);

			// Get C-type string 
			operator LPCTSTR() const;

			// Get string's length
			inline Length GetLength() const
			{
				return m_Length;
			}

			// Parse the string to number
			template <class BaseType>
			static BaseType Parse(String NumberString, BaseType Data = 0)
			{
				// Streaming the string
				StringStream Streamer;
				Streamer << NumberString;

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

		private:
			// Initialize the String
			Empty Initialize(StdString OtherStdString);

			// Destory the String
			Empty Destroy();

			// Append a new std string to the string
			String& Append(StdString& OtherStdString);

			// Is the current string equals to the other one
			BOOL Equal(String& OtherString);

		private:
			// Get std string
			inline StdString GetStdString() const
			{
				return m_StdString;
			}

			// Set std string
			inline Empty SetStdString(StdString OtherStdString)
			{
				this->m_StdString = OtherStdString;
			}

			// Set string's length
			inline Empty SetLength(Length iLength)
			{
				this->m_Length = iLength;
			}

			// Get the Disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the Disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// STL string
			StdString m_StdString;

			// String's length(bytes total)
			Length m_Length;

			// Wide string's pointer
			Array<WByte> m_WideArray;

			// Dispoed status
			BOOL m_Disposed;
		};
	}
}

#endif //!STRING_H_