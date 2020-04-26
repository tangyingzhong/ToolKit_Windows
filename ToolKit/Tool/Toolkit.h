///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Basic tools for using
///</describe>
/// <date>2019/3/5</date>
///***********************************************************************
#ifndef TOOLKIT_H
#define TOOLKIT_H

#include "Tool/BaseType/Bool.h"
#include "Tool/BaseType/Double.h"
#include "Tool/BaseType/Float.h"
#include "Tool/BaseType/Int.h"
#include "Tool/BaseType/String.h"
#include "Tool/Buffer/Array.h"
#include "Tool/Buffer/CircleBuffer.h"
#include "Tool/Buffer/SingleList.h"
#include "Tool/Buffer/DoubleList.h"
#include "Tool/Buffer/SharedMemory.h"
#include "Tool/Common/SystemType.h"
#include "Tool/DateTime/DateTime.h"
#include "Tool/Directory/Directory.h"
#include "Tool/DllLoader/DllLoader.h"
#include "Tool/Encoding/ANSI.h"
#include "Tool/Encoding/Unicode.h"
#include "Tool/Encoding/UTF8.h"
#include "Tool/EventHandler/EventArgs.h"
#include "Tool/EventHandler/EventHandler.h"
#include "Tool/Eventor/IEvent.h"
#include "Tool/Eventor/EventBase.h"
#include "Tool/ModuleLoader/ModuleLoader.h"
#include "Tool/File/File.h"
#include "Tool/Json/JsonDoc.h"
#include "Tool/Player/DirectShow/GeneralPlayer.h"
#include "Tool/Player/Wav/IBlockPlayer.h"
#include "Tool/Player/Wav/BlockPlayer.h"
#include "Tool/Player/Wav/IAudioPlayer.h"
#include "Tool/Player/Wav/AudioPlayer.h"
#include "Tool/Reflect/Reflect.h"
#include "Tool/Register/Register.h"
#include "Tool/Register/ExportConfig.h"
#include "Tool/Log/Log.h"
#include "Tool/Log/LogType.h"
#include "Tool/Log/SystemLog.h"
#include "Tool/SerialPort/PortType.h"
#include "Tool/SerialPort/SerialPort.h"
#include "Tool/Socket/Socket.h"
#include "Tool/Socket/SocketClient.h"
#include "Tool/Socket/SocketServer.h"
#include "Tool/Socket/SocketType.h"
#include "Tool/Sql/SqlCommand.h"
#include "Tool/Sql/SqlConnection.h"
#include "Tool/Sql/SqlParamenter.h"
#include "Tool/Thread/Event.h"
#include "Tool/Thread/MessageDistributor.h"
#include "Tool/Thread/Mutex.h"
#include "Tool/Thread/MutexLocker.h"
#include "Tool/Thread/Process.h"
#include "Tool/Thread/Semaphore.h"
#include "Tool/Timer/Counter.h"
#include "Tool/Timer/Delay.h"
#include "Tool/Timer/Timer.h"
#include "Tool/USB/USB.h"
#include "Tool/USB/USBType.h"

using namespace System;
using namespace System::BasicType;
using namespace System::Buffer;
using namespace System::Clock;
using namespace System::DataBase;
using namespace System::Encoding;
using namespace System::EventArgument;
using namespace System::IO;
using namespace System::Network;
using namespace System::Thread;

#endif // TOOLKIT_H 
