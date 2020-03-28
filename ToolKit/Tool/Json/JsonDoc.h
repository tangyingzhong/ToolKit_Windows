///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It is responsible for JsonDocument's parsing
///</describe>
/// <date>2019/7/29</date>
///***********************************************************************
#ifndef JsonDocument_H
#define JsonDocument_H

#include "Tool/Common/SystemType.h"
#include "Tool/BaseType/String.h"
#include "Tool/Encoding/EncodeType.h"
#include "Tool/Json/json.h"

using namespace System::BasicType;
using namespace System::Encoding;

namespace System
{
	class JsonDocument
	{
	public:
		typedef Json::Value JsonObject;
		typedef Json::Reader JsonReader;
		typedef Json::ValueType ValueType;
		typedef String JsonString;
		typedef vector<JsonString> KeyTable;
		typedef UInt32 JsonSize;
		typedef UInt32 Index;

	public:
		// Construct the JsonDocument with json file
		JsonDocument();

		// Construct the JsonDocument with json object
		JsonDocument(JsonObject Value);
		
		// Detructe the JsonDocument
		~JsonDocument();

		// Copy the constructure
		JsonDocument(JsonDocument& other);

		// Assign the object
		JsonDocument& operator=(JsonDocument& other);

	public:
		// Json file to obejct
		static JsonDocument FromJsonFile(JsonString strFilePath);

		// String to object
		static JsonDocument FromJson(JsonString& strJson);

		// To map
		None ToMap(std::map<std::string,std::string>& MapTable);

		// Object to string
		JsonString ToJson();

		// Get all keys
		Boolean GetKeys(KeyTable& FinalKeyTable);

		// Is contain the key
		Boolean IsContain(JsonString strKey);

		// Get array element
		JsonDocument operator[](Index iIndex);

		// Append the data
		JsonDocument& Append(JsonDocument JsonObject);

		// Append the data
		JsonDocument& Append(JsonString strValue);

		// Append the data
		JsonDocument& Append(Int32 iValue);

		// Append the data
		JsonDocument& Append(Real dValue);

		// Remove one element
		JsonDocument& RemoveAt(Int32 iIndex);

		// Get the value of key
		JsonDocument GetKeyValue(JsonString strKey);

		// Set the key's value
		None SetKeyValue(JsonString strKey, JsonDocument& Doc);

		// Set the key's value
		None SetKeyValue(JsonString strKey, JsonString strValue);

		// Set the key's value
		None SetKeyValue(JsonString strKey, Int32 iValue);

		// Set the key's value
		None SetKeyValue(JsonString strKey, Real dValue);

		// Set the key's value
		None SetKeyValue(JsonString strKey, Boolean bValue);

		// Set array
		None SetArray(JsonDocument& JsonDoc);

		// Size of the json object
		JsonSize Size();
		
		// Flush the json to file
		Boolean Flush(JsonString strFilePath);

		// To string
		JsonString ToString();

		// To int 
		Int32 ToInt();

		// To double
		Real ToDouble();

		// To boolean
		Boolean ToBool();

		// Is the object null or not
		Boolean IsNull();

		// Is Obejct None
		Boolean IsEmpty();

		// Is Object
		Boolean IsObject();

		// Is the object bool value
		Boolean IsBool();

		// Is Double
		Boolean IsDouble();

		// Is the object int value
		Boolean IsInt();

		// Is the object string value
		Boolean IsString();

		// Is the object to be an array
		Boolean IsArray();

	private:
		// Initialize the library
		None Initialize();

		// Destory the library
		None Destory();

		// Write the object to file
		Boolean WriteToFile(JsonString strFileName);

		// Get key's value
		JsonObject& Get(JsonString strKey);

		// Set the key's value
		None Set(JsonString strKey, JsonObject Value);

		// Parse the json file
		Boolean ParseFromFile(JsonString strJsonFilePath);

	private:		
		// Get the JsonObject
		inline JsonObject& GetJsonObject()
		{
			return m_JsonObject;
		}

		// Set the JsonObject
		inline None SetJsonObject(JsonObject& Object)
		{
			m_JsonObject = Object;
		}

		// Set the disposed status
		inline None SetDisposed(Boolean bDisposed)
		{
			m_bDisposed = bDisposed;
		}
		
		// Get the disposed status
		inline Boolean GetDisposed() const
		{
			return m_bDisposed;
		}

	private:
		// Json value
		JsonObject m_JsonObject;

		// Disposed status
		Boolean m_bDisposed;	
	};
}

#endif //JsonDocument_H