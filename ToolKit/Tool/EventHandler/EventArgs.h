///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Base event args
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************

#ifndef EVENTARGS_H
#define EVENTARGS_H

namespace System
{
	namespace EventArgument
	{
		class EventArgs
		{
		public:
			// Construct the EventArgs
			EventArgs() {	}

			// Detructe the EventArgs
			~EventArgs() {	}

			// Allow the object copying
			EventArgs(const EventArgs& other) {	}

			// Allow the object assignment
			EventArgs& operator=(const EventArgs& other) {	}

			// Get None object
			static EventArgs IsEmpty() {	}
		};
	}
}

#endif // EVENTARGS_H
