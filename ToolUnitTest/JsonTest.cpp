#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tool_UnitTest
{		
	TEST_CLASS(JsonTest)
	{
	public:
		TEST_METHOD(Test_FromJsonFile)
		{
			JsonDocument JsonDoc1 = JsonDocument::FromJsonFile(_T("D:\\data.json"));

			Boolean bRet1 = JsonDoc1.IsNull();

			Assert::IsTrue(bRet1 == false);
		}

		TEST_METHOD(Test_GetKeys)
		{
			JsonDocument JsonDoc = JsonDocument::FromJsonFile(_T("D:\\data.json"));

			JsonDocument::KeyTable Table;
			if (!JsonDoc.GetKeys(Table))
			{
				Assert::Fail(_T("Failed to get all keys under this root key"));
			}

			Assert::IsTrue(JsonDoc.IsContain(_T("systemName")));
		}

		TEST_METHOD(Test_FromJson)
		{
			String strJson = _T("{\"设备ID\": \"SHENGYANG-13-VCS2000-006C4004JV002B6F1\", \
				\"地址\" : \"http://192.168.0.101:48769\",\
				\"local_ip\" : \"192.168.0.196\",\
				\"orgName\" : \"广东省--深圳市香港中文大学研究院602\",\
				\"orgNo\" : \"132154625321\",\
				\"register_date_time\" : \"2019-10-31 16:13:21\",\
				\"register_finish_date_time\" : \"2019-10-31 16:13:30\",\
				\"systemName\" : \"SHENGYANG\",\
				\"wsdl_vpr_host\" : \"http://192.168.0.101:49090\"}");

			JsonDocument JsonDoc = JsonDocument::FromJson(strJson);

			String strAddr = JsonDoc.GetKeyValue(_T("地址")).ToString();

			Assert::IsTrue(strAddr == _T("http://192.168.0.101:48769"));

			String strEquipmentID = JsonDoc.GetKeyValue(_T("设备ID")).ToString();

			Assert::IsTrue(strEquipmentID == _T("SHENGYANG-13-VCS2000-006C4004JV002B6F1"));

			String strOrgName = JsonDoc.GetKeyValue(_T("orgName")).ToString();

			Assert::IsTrue(strOrgName == _T("广东省--深圳市香港中文大学研究院602"));

			String strRegTime = JsonDoc.GetKeyValue(_T("register_date_time")).ToString();

			DateTime RegTime = DateTime::FromString(strRegTime);

			String strDateTime = RegTime.ToString();

			Assert::IsTrue(strRegTime == strDateTime);
		}

		TEST_METHOD(Test_SetKeyValue)
		{
			JsonDocument JsonObject;

			JsonObject.SetKeyValue(_T("设备ID"), _T("1234586"));

			JsonObject.SetKeyValue(_T("Banana"), _T("香蕉"));

			JsonObject.SetKeyValue(_T("Person"), _T("Happy"));

			JsonObject.SetKeyValue(_T("Computers"), 3);

			JsonObject.SetKeyValue(_T("Result"), 5.62);

			JsonObject.SetKeyValue(_T("IsOpen"), false);

			JsonDocument JsonDoc;

			JsonDoc.SetKeyValue(_T("App"), JsonObject);

			JsonDoc.Flush(_T("D:\\data1.json"));
		}

		TEST_METHOD(Test_Append)
		{
			JsonDocument JsonObject;

			JsonObject.Append(_T("北京市"));

			JsonObject.Append(_T("天津市"));

			JsonObject.Append(_T("上海市"));

			JsonObject.Append(_T("重庆市"));

			JsonObject.Append(_T("贵州省"));

			JsonObject.Append(_T("广西壮族自治区"));

			JsonDocument JsonDoc;

			JsonDoc.SetKeyValue(_T("Province"), JsonObject);

			JsonDoc.Flush(_T("D:\\data2.json"));
		}

		TEST_METHOD(Test_GetKeyValue)
		{
			JsonDocument JsonDoc = JsonDocument::FromJsonFile(_T("D:\\Province.json"));

			Assert::IsTrue(!JsonDoc.IsNull());

			JsonDocument JsonObject = JsonDoc.GetKeyValue(_T("Province"));
			
			Assert::IsTrue(!JsonObject.IsNull());

			vector<String> NameTable;

			String strProName=_T("");

			if (JsonObject.IsArray())
			{
				Int32 iArraySize = JsonObject.Size();

				for (Int32 iIndex = 0; iIndex < iArraySize;++iIndex)
				{
					String strProvinceName = JsonObject[iIndex].ToString();

					NameTable.push_back(strProvinceName);

					strProName = strProName+strProvinceName+_T("\r\n");
				}
			}

			Assert::IsTrue(!NameTable.empty());

			File FileHelper;

			if (!FileHelper.Open(_T("D:\\AA.json"),File::FileMode::CREATE,File::FileAccess::READWRITE))
			{
				Assert::Fail(_T("Failed to create a file"));
			}

			FileHelper.Write((SByteArray)strProName.ToUTF8Data().c_str(), 0, static_cast<File::ArraySize>(strProName.ToUTF8Data().length()));

			FileHelper.Close();
		}

		TEST_METHOD(Test_ToJson)
		{
			JsonDocument JsonObject;

			JsonObject.Append(_T("北京市"));

			JsonObject.Append(_T("天津市"));

			JsonObject.Append(_T("上海市"));

			JsonObject.Append(_T("重庆市"));

			JsonObject.Append(_T("贵州省"));

			JsonObject.Append(_T("广西壮族自治区"));

			String strJson = JsonObject.ToJson();

			File FileHelper;

			if (!FileHelper.Open(_T("D:\\ToJson.json"), File::FileMode::CREATE, File::FileAccess::READWRITE))
			{
				Assert::Fail(_T("Failed to create a file"));
			}

			FileHelper.Write((SByteArray)strJson.ToUTF8Data().c_str(), 0, static_cast<File::ArraySize>(strJson.ToUTF8Data().length()));

			FileHelper.Close();
		}
	};
}