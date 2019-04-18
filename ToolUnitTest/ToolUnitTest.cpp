// 版权所有：(C)2019, 深圳市安健科技股份有限公司
// 文件名称：ToolUnitTest.cpp
// 编码作者：唐应忠
// 完成日期：2019-04-18
// 内容摘要：ToolUnitTest 模块单元测试初始化和清理的实现文件

#include "StdAfx.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ToolUnitTest
{
	TEST_MODULE_INITIALIZE(ToolUnitTestInitialize)
	{
		// TODO : 在此输入测试模块初始化代码，模块开始测试前将执行这段代码
	}

	TEST_MODULE_CLEANUP(ToolUnitTestCleanup)
	{
		// TODO : 在此输入测试模块清理代码，模块测试完毕后将执行这段代码
	}
}
