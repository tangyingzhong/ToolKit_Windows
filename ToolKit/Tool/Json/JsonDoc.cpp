#include <fstream>
#include "Tool/Encoding/ANSI.h"
#include "Tool/Encoding/Unicode.h"
#include "Tool/Encoding/UTF8.h"
#include "Tool/BaseType/Int.h"
#include "Tool/BaseType/Double.h"
#include "Tool/BaseType/Bool.h"
#include "Tool/File/File.h"
#include "JsonDoc.h"

using namespace System;
using namespace System::IO;

// Construct the JsonDocument with json file
JsonDocument::JsonDocument() :
	m_strErrorText(""),
	m_bDisposed(false)
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
JsonDocument::JsonDocument(const JsonDocument& other)
{
	JsonObject obj = other.m_JsonObject;

	SetJsonObject(obj);

	SetDisposed(other.GetDisposed());
}

// Assign the object
JsonDocument& JsonDocument::operator=(const JsonDocument& other)
{
	if (this != &other)
	{
		JsonObject obj = other.m_JsonObject;

		SetJsonObject(obj);

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
		SetErrorText("Input file path is empty !");

		return false;
	}

	std::ifstream FileStream;

	FileStream.open(strJsonFilePath.ToANSIData(), std::ios::binary);

	JsonReader Reader;

	if (!Reader.parse(FileStream, GetJsonObject()))
	{
		std::string strErrorText = Reader.getFormatedErrorMessages();

		SetErrorText(String(strErrorText, ENCODE_UTF8));

		FileStream.close();

		return false;
	}

	FileStream.close();

	return true;
}

// Is the object null or not
Boolean JsonDocument::IsNull()
{
	if (GetJsonObject().isNull())
	{
		SetErrorText("Json object is empty !");

		return true;
	}

	return false;
}

// Is Object
Boolean JsonDocument::IsObject()
{
	if (!GetJsonObject().isObject())
	{
		SetErrorText("Json is not an object !");

		return false;
	}

	return true;
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
		SetErrorText("File path is empty !");

		return false;
	}

	String strJson = ToJson();

	File FileHelper;

	if (!FileHelper.Open(strFileName, File::FileMode::CREATE, File::FileAccess::READWRITE))
	{
		SetErrorText("Failed to create the file !");

		return false;
	}

	FileHelper.Write((SByteArray)strJson.ToUTF8Data().c_str(), 
		0, 
		static_cast<File::ArraySize>(strJson.ToUTF8Data().length()));

	FileHelper.Close();

	return true;
}

// Flush the json to file
Boolean JsonDocument::Flush(JsonString strFilePath)
{
	if (strFilePath.IsEmpty())
	{
		SetErrorText("File path is empty !");

		return false;
	}

	return WriteToFile(strFilePath);
}

// Json file to obejct
JsonDocument JsonDocument::FromJsonFile(JsonString strFilePath, JsonString& strErrorMsg)
{
	if (strFilePath.IsEmpty())
	{
		return JsonDocument();
	}

	JsonDocument JsonDoc;

	if (!JsonDoc.ParseFromFile(strFilePath))
	{
		strErrorMsg = JsonDoc.GetErrorMsg();

		return JsonDocument();
	}

	return JsonDoc;
}

// Parse from the string
Boolean JsonDocument::ParseFromData(String strData, JsonDocument& JsonDoc)
{
	JsonReader Reader;

	if (!Reader.parse(strData.ToUTF8Data(), JsonDoc.GetJsonObject()))
	{
		std::string strErrorText = Reader.getFormatedErrorMessages();

		SetErrorText(String(strErrorText, ENCODE_UTF8));

		return false;
	}

	return true;
}

// String to object
JsonDocument JsonDocument::FromJson(JsonString& strJson, JsonString& strErrorMsg)
{
	JsonDocument JsonParser;

	JsonDocument JsonDoc;

	if (!JsonParser.ParseFromData(strJson,JsonDoc))
	{
		strErrorMsg = JsonParser.GetErrorMsg();

		return JsonDocument();
	}

	return JsonDoc;
}

// Is contain the key
Boolean JsonDocument::IsContain(JsonString strKey)
{
	if (strKey.IsEmpty())
	{
		SetErrorText("Key is empty");

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
		String strFinalKey = String(KeyList[iIndex],ENCODE_UTF8);

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
		String strMember = String(*Iter,ENCODE_UTF8);

		JsonDocument CurObject = GetKeyValue(strMember);

		Json::ValueType Type = CurObject.GetJsonObject().type();

		switch (Type)
		{
		case Json::objectValue:
		{
			CurObject.ToMap(MapTable);
		}
			break;
		case Json::stringValue:
		{
			MapTable[strMember.ToANSIData()] = CurObject.ToString().ToANSIData();
		}
			break;

		case Json::intValue:
		{
			Int iValue = CurObject.ToInt();

			MapTable[strMember.ToANSIData()] = iValue.ToString().ToANSIData();
		}
			break;

		case Json::realValue:
		{
			Double dValue = CurObject.ToDouble();

			MapTable[strMember.ToANSIData()] = dValue.ToString().ToANSIData();
		}
			break;

		case Json::booleanValue:
		{
			Bool bValue = CurObject.ToBool();

			MapTable[strMember.ToANSIData()] = bValue.ToString().ToANSIData();
		}
			break;

		case Json::arrayValue:
		{
			String strArrayValue;

			for (int iIndex = 0; iIndex < (int)m_JsonObject.size();++iIndex)
			{
				strArrayValue = strArrayValue + CurObject.ToString();

				strArrayValue = strArrayValue + ",";
			}

			if (!strArrayValue.IsEmpty())
			{
				strArrayValue = strArrayValue.Left(strArrayValue.GetLength()-1);
			}

			MapTable[strMember.ToANSIData()] = strArrayValue.ToANSIData();
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

	std::string strJson = GetJsonObject().toStyledString();

	String strData = String(strJson,ENCODE_UTF8);

	return strData;
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
	m_JsonObject.append(strValue.ToUTF8Data());

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
	if (iIndex < 0)
	{
		SetErrorText("Failed to remove object ,index you input is irrlegal,check it please !");

		return *this;
	}

	GetJsonObject().removeAt(iIndex);

	return *this;
}

// Get key's value
JsonDocument::JsonObject& JsonDocument::Get(JsonString strKey)
{
	std::string strFinalKey = strKey.ToUTF8Data();

	return m_JsonObject[strFinalKey];
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
		SetErrorText("Key is empty !");

		return JsonDocument();
	}

	return Get(strKey);
}

// Is Obejct IsEmpty
Boolean JsonDocument::IsEmpty()
{
	if (GetJsonObject().IsEmpty())
	{
		SetErrorText("Json object is empty !");

		return true;
	}

	return false;
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
		SetKeyValue(strKey, Doc.GetJsonObject().asBool());
	}
	else if (Doc.IsInt())
	{
		SetKeyValue(strKey, Doc.GetJsonObject().asInt());
	}
	else if (Doc.IsString())
	{
		SetKeyValue(strKey, Doc.GetJsonObject().asString());
	}
	else if (Doc.IsDouble())
	{
		SetKeyValue(strKey, Doc.GetJsonObject().asDouble());
	}
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
None JsonDocument::SetKeyValue(JsonString strKey, Boolean bValue, Boolean bIsBoolValue)
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
	if (iIndex < 0)
	{
		SetErrorText("Index you input is irrlegal,check it please !");

		return JsonDocument();
	}

	JsonDocument JsonDoc;

	JsonDoc.SetJsonObject(m_JsonObject[iIndex]);

	return JsonDoc;
}

// Get error message
String JsonDocument::GetErrorMsg()
{
	return GetErrorText();
}
