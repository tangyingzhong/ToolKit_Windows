#include <fstream>
#include "Tool/Encoding/ANSI.h"
#include "Tool/Encoding/UTF16.h"
#include "Tool/Encoding/UTF8.h"
#include "Tool/BaseType/Int.h"
#include "Tool/BaseType/Double.h"
#include "JsonDoc.h"

using namespace System;

// Construct the JsonDocument with json file
JsonDocument::JsonDocument() :m_bDisposed(false)
{
	Initialize();
}

// Construct the JsonDocument with json object
JsonDocument::JsonDocument(JsonObject Value) :m_JsonObject(Value),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the JsonDocument
JsonDocument::~JsonDocument()
{
	Destory();
}

// Copy the constructure
JsonDocument::JsonDocument(JsonDocument& other)
{
	SetJsonObject(other.GetJsonObject());

	SetDisposed(other.GetDisposed());
}

// Assign the object
JsonDocument& JsonDocument::operator=(JsonDocument& other)
{
	if (this != &other)
	{
		SetJsonObject(other.GetJsonObject());

		SetDisposed(other.GetDisposed());
	}

	return *this;
}

// Initialize the library
None JsonDocument::Initialize()
{
	
}

// Destory the library
None JsonDocument::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Parse the json file
Boolean JsonDocument::ParseFromFile(JsonString strJsonFilePath)
{
	if (strJsonFilePath.IsEmpty())
	{
		return false;
	}

	std::ifstream FileStream;

	FileStream.open(strJsonFilePath.ToANSIData(), std::ios::binary);

	if (!JsonReader().parse(FileStream, GetJsonObject()))
	{
		FileStream.close();

		return false;
	}

	FileStream.close();

	return true;
}

// Is the object null or not
Boolean JsonDocument::IsNull()
{
	return GetJsonObject().isNull();
}

// Is Object
Boolean JsonDocument::IsObject()
{
	return GetJsonObject().isObject();
}

// Is the object bool value
Boolean JsonDocument::IsBool()
{
	return GetJsonObject().isBool();
}

// Is the object int value
Boolean JsonDocument::IsInt()
{
	return GetJsonObject().isInt();
}

// Is Double
Boolean JsonDocument::IsDouble()
{
	return GetJsonObject().isDouble();
}

// Is the object string value
Boolean JsonDocument::IsString()
{
	return GetJsonObject().isString();
}

// Is the object to be an array
Boolean JsonDocument::IsArray()
{
	return GetJsonObject().isArray();
}

// Write the object to file
Boolean JsonDocument::WriteToFile(JsonString strFileName)
{
	if (strFileName.IsEmpty())
	{
		return false;
	}

	std::ofstream Streamer;

	Streamer.open(strFileName.ToANSIData(), std::ios::out | std::ios::trunc);

	if (!Streamer.is_open())
	{
		return false;
	}

	Streamer << GetJsonObject().toStyledString();

	Streamer.close();

	return Streamer.good();
}

// Flush the json to file
Boolean JsonDocument::Flush(JsonString strFilePath)
{
	if (strFilePath.IsEmpty())
	{
		return false;
	}

	return WriteToFile(strFilePath);
}

// Json file to obejct
JsonDocument JsonDocument::FromJsonFile(JsonString strFilePath)
{
	if (strFilePath.IsEmpty())
	{
		return JsonDocument();
	}

	JsonDocument JsonDoc;

	if (!JsonDoc.ParseFromFile(strFilePath))
	{
		return JsonDocument();
	}

	return JsonDoc;
}

// String to object
JsonDocument JsonDocument::FromJson(JsonString& strJson)
{
	JsonReader Read;

	JsonDocument JsonDoc;

	if (!Read.parse(strJson.ToUTF8Data(), JsonDoc.GetJsonObject()))
	{
		return JsonDocument();
	}

	return JsonDoc;
}

// Is contain the key
Boolean JsonDocument::IsContain(JsonString strKey)
{
	if (strKey.IsEmpty())
	{
		return false;
	}

	KeyTable KeyList;
	if (!GetKeys(KeyList))
	{
		return false;
	}

	for (Index iIndex = 0; iIndex < (Index)KeyList.size();++iIndex)
	{
		if (strKey == KeyList[iIndex])
		{
			return true;
		}
	}

	return false;
}

// Get all root keys
Boolean JsonDocument::GetKeys(KeyTable& FinalKeyTable)
{
	if (!IsObject())
	{
		return false;
	}

	vector<std::string> KeyList;

	KeyList = GetJsonObject().getMemberNames();

	for (Int32 iIndex = 0; iIndex < (Int32)KeyList.size();++iIndex)
	{
		std::string strAnsi = ANSI::GetString(KeyList[iIndex], ENCODE_UTF8);

		String strFinalKey = strAnsi;

		FinalKeyTable.push_back(strFinalKey);
	}

	return true;
}

// To map
None JsonDocument::ToMap(std::map<std::string, std::string>& MapTable)
{
	JsonObject::Members Mem = GetJsonObject().getMemberNames();

	for (JsonObject::Members::iterator Iter = Mem.begin();
		Iter != Mem.end();
		++Iter)
	{
		Json::ValueType Type = GetJsonObject()[*Iter].type();

		switch (Type)
		{
		case Json::stringValue:
		{
			MapTable.insert(pair<std::string, std::string>(*Iter,m_JsonObject[*Iter].asString()));
		}
			break;

		case Json::intValue:
		{
			Int iValue = m_JsonObject[*Iter].asInt();

			MapTable.insert(pair<std::string, std::string>(*Iter, iValue.ToString().ToANSIData()));
		}
			break;

		case Json::realValue:
		{
			Double dValue = m_JsonObject[*Iter].asDouble();

			MapTable.insert(pair<std::string, std::string>(*Iter, dValue.ToString().ToANSIData()));
		}
			break;

		case Json::booleanValue:
		{
			bool bValue = m_JsonObject[*Iter].asBool();

			std::string strBValue = bValue == true ? "true" : "false";

			MapTable.insert(pair<std::string, std::string>(*Iter, strBValue));
		}
			break;

		case Json::arrayValue:
		{
			std::string strArrayValue;

			for (int iIndex = 0; iIndex < (int)m_JsonObject.size();++iIndex)
			{
				strArrayValue += m_JsonObject[*Iter].asString();

				strArrayValue += ",";
			}

			if (!strArrayValue.empty())
			{
				strArrayValue = strArrayValue.substr(0, strArrayValue.length() - 1);
			}

			MapTable.insert(pair<std::string, std::string>(*Iter, strArrayValue));
		}
			break;

		default:

			break;
		}
	}
}

// Object to string
JsonDocument::JsonString JsonDocument::ToJson()
{
	if (IsNull())
	{
		return _T("");
	}

	std::string strUtf8Json = GetJsonObject().toStyledString();

	std::string strAnsiJson = ANSI::GetString(strUtf8Json, ENCODE_UTF8);

	String strJson = strAnsiJson;

	return strJson;
}

// Append the data
JsonDocument& JsonDocument::Append(JsonDocument JsonObject)
{
	if (JsonObject.IsObject())
	{
		m_JsonObject.append(JsonObject.GetJsonObject());
	}
	else if (JsonObject.IsBool())
	{
		m_JsonObject.append(JsonObject.ToBool());
	}
	else if (JsonObject.IsInt())
	{
		m_JsonObject.append(JsonObject.ToInt());
	}
	else if (JsonObject.IsString())
	{
		m_JsonObject.append(JsonObject.GetJsonObject().asString());
	}
	else if (JsonObject.IsDouble())
	{
		m_JsonObject.append(JsonObject.ToDouble());
	}

	return *this;
}

// Append the data
JsonDocument& JsonDocument::Append(JsonString strValue)
{
	m_JsonObject.append(strValue.ToANSIData());

	return *this;
}

// Append the data
JsonDocument& JsonDocument::Append(Int32 iValue)
{
	m_JsonObject.append(iValue);

	return *this;
}

// Append the data
JsonDocument& JsonDocument::Append(Real dValue)
{
	m_JsonObject.append(dValue);

	return *this;
}

// Remove one element
JsonDocument& JsonDocument::RemoveAt(Int32 iIndex)
{
	if (iIndex<0)
	{
		return *this;
	}

	GetJsonObject().removeAt(iIndex);

	return *this;
}

// Get key's value
JsonDocument::JsonObject& JsonDocument::Get(JsonString strKey)
{
	return m_JsonObject[strKey.ToUTF8Data()];
}

// Set the key's value
None JsonDocument::Set(JsonString strKey, JsonObject Value)
{
	if (strKey.IsEmpty())
	{
		return;
	}

	m_JsonObject[strKey.ToUTF8Data()] = Value;
}

// Get the value of key
JsonDocument JsonDocument::GetKeyValue(JsonString strKey)
{
	if (strKey.IsEmpty())
	{
		return JsonDocument();
	}

	return Get(strKey);
}

// Set the key's value
None JsonDocument::SetKeyValue(JsonString strKey, JsonString strValue)
{
	if (strKey.IsEmpty())
	{
		return;
	}

	Set(strKey, strValue.ToUTF8Data());
}

// Is Obejct IsEmpty
Boolean JsonDocument::IsEmpty()
{
	return GetJsonObject().IsEmpty();
}

// Set array
None JsonDocument::SetArray(JsonDocument& JsonDoc)
{
	if (JsonDoc.IsNull())
	{
		return;
	}

	if (!JsonDoc.IsArray())
	{
		return;
	}

	if (JsonDoc.IsEmpty())
	{
		return;
	}

	for (Int32 iIndex = 0; iIndex < (Int32)JsonDoc.Size(); ++iIndex)
	{
		Append(JsonDoc[iIndex]);
	}
}

// Set the key's value
None JsonDocument::SetKeyValue(JsonString strKey, JsonDocument& Doc)
{
	if (strKey.IsEmpty())
	{
		return;
	}

	if (Doc.IsObject() || Doc.IsArray())
	{
		Set(strKey, Doc.GetJsonObject());
	}
	else if (Doc.IsBool())
	{
		Set(strKey, Doc.GetJsonObject().asBool());
	}
	else if (Doc.IsInt())
	{
		Set(strKey, Doc.GetJsonObject().asInt());
	}
	else if (Doc.IsString())
	{
		Set(strKey, Doc.GetJsonObject().asString());
	}
	else if (Doc.IsDouble())
	{
		Set(strKey, Doc.GetJsonObject().asDouble());
	}
}

// Set the key's value
None JsonDocument::SetKeyValue(JsonString strKey, Int32 iValue)
{
	if (strKey.IsEmpty())
	{
		return;
	}

	Set(strKey, iValue);
}

// Set the key's value
None JsonDocument::SetKeyValue(JsonString strKey, Boolean bValue)
{
	if (strKey.IsEmpty())
	{
		return;
	}

	Set(strKey, bValue);
}

// Set the key's value
None JsonDocument::SetKeyValue(JsonString strKey, Real dValue)
{
	if (strKey.IsEmpty())
	{
		return;
	}

	Set(strKey, dValue);
}

// To string
JsonDocument::JsonString JsonDocument::ToString()
{
	std::string strUtf8Data = GetJsonObject().asString();

	std::string strAnsi = ANSI::GetString(strUtf8Data, ENCODE_UTF8);

	String strFinalData = strAnsi;

	return strFinalData;
}

// To int 
Int32 JsonDocument::ToInt()
{
	return GetJsonObject().asInt();
}

// To double
Real JsonDocument::ToDouble()
{
	return GetJsonObject().asDouble();
}

// To boolean
Boolean JsonDocument::ToBool()
{
	return GetJsonObject().asBool();
}

// Size of the json object
JsonDocument::JsonSize JsonDocument::Size()
{
	return GetJsonObject().size();
}

// Get array element
JsonDocument JsonDocument::operator[](Index iIndex)
{
	if (iIndex<0)
	{
		return JsonDocument();
	}

	JsonDocument JsonDoc;

	JsonDoc.SetJsonObject(m_JsonObject[iIndex]);

	return JsonDoc;
}