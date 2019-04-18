///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// You can get the local time from the class
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef DATETIME_H
#define DATETIME_H

#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	///*********************************************************
	/// <class> DateTime </class>
	/// <summary>
	/// Supported time getting
	/// </summary>
	/// <version>V1.0.0 </version>
	/// <goup> C++ </group>
	/// <author>tangyingzhong</author>
	/// <contact>tangyz114987@outlook.com</contact>
	///**********************************************************/
	class DateTime
	{
	public:
		typedef System::Boolean BOOL;
		typedef System::Empty Empty;
		

	public:
		// Construct the DateTime
		DateTime() {	}

		// Destrcut the DateTime
		~DateTime() {	}

		// Allow the object copying
		DateTime(const DateTime& other) {	}

		// Allow the obejct assignment
		DateTime& operator=(DateTime& other) {	}

	
	};
	
}

#endif //!DATETIME_H_