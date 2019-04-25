///************************************************************************
/// <copyrigth>2018-2019 Corporation. All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// ESC command for printer operation if you decide to use the class designed
/// by myself named LocalPrinter or NetPrinter
///</describe>
/// <date>2019/4/25</date>
///***********************************************************************
#ifndef PRINTERCMD_H
#define PRINTERCMD_H

namespace System
{
	namespace Printer
	{	
		const char ESC_INIT_RWX[] = { 0x1B,0x40 };            //初始化;              
		const char ESC_LINE_TAB[] = { 0x0A };                 //换行
		const char ESC_LINE_ADD[] = { 0x1B,0x21,0x28 };       //加粗
															
		const char ESC_LINE_H1[] = { 0x1D,0x21,0x01 };        //倍高 垂直（ 三位符(倍高度)  1 2 4 8 1-7 倍）
		const char ESC_LINE_H2[] = { 0x1D,0x21,0x02 };        //倍高 垂直（ 三位符(倍高度)  1 2 4 8 1-7 倍）
		const char ESC_LINE_H3[] = { 0x1D,0x21,0x04 };        //倍高 垂直（ 三位符(倍高度)  1 2 4 8 1-7 倍）

		const char ESC_LINE_W1[] = { 0x1D,0x21,0x10 };        //倍高 垂直（ 三位符(倍高度)  10 20 30 40 宽度 ）
		const char ESC_LINE_W2[] = { 0x1D,0x21,0x20 };        //倍高 垂直（ 三位符(倍高度)  10 20 30 40 宽度 ）
		const char ESC_LINE_W3[] = { 0x1D,0x21,0x30 };        //倍高 垂直（ 三位符(倍高度)  10 20 30 40 宽度 ）

		const char ESC_LINE_T1[] = { 0x1B,0x21,0x02 };        //原始高度
		const char ESC_LINE_T2[] = { 0x1D,0x21,0x11 };        //倍高 垂直（ 三位符(倍高度)  10 20 30 40 宽度 ）
		const char ESC_LINE_T3[] = { 0x1D,0x21,0x22 };        //倍高 垂直（ 三位符(倍高度)  10 20 30 40 宽度 ）
		const char ESC_LINE_T4[] = { 0x1D,0x21,0x34 };        //倍高 垂直（ 三位符(倍高度)  10 20 30 40 宽度 ）
		const char ESC_LINE_T5[] = { 0x1D,0x21,0x48 };        //倍高 垂直（ 三位符(倍高度)  10 20 30 40 宽度 ）
	}
}

#endif //PRINTERCMD_H