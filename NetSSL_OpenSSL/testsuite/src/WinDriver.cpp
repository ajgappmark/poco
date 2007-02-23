//
// WinDriver.cpp
//
// $Id: //poco/Main/NetSSL_OpenSSL/testsuite/src/WinDriver.cpp#8 $
//
// Windows test driver for Poco OpenSSL.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "WinTestRunner/WinTestRunner.h"
#include "NetSSLTestSuite.h"
#include "Poco/Util/Application.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/HTTPSStreamFactory.h"


class NetSSLApp: public Poco::Util::Application
{
public:
	NetSSLApp()
	{
	}

	~NetSSLApp()
	{
	}

protected:	
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		Application::initialize(self);
	}
};


class TestDriver: public CppUnit::WinTestRunnerApp
{
	void TestMain()
	{
		CppUnit::WinTestRunner runner;
		Poco::Net::HTTPStreamFactory::registerFactory();
		Poco::Net::HTTPSStreamFactory::registerFactory();
		NetSSLApp app;
		std::string argv("OpenSSLTest");
		const char* pArgv = argv.c_str();
		try
		{
			app.init(1, (char**)&pArgv);
		}
		catch (Poco::Exception& exc)
		{
			app.logger().log(exc);
		}
		runner.addTest(NetSSLTestSuite::suite());
		runner.run();
	}
};


static TestDriver theDriver;
