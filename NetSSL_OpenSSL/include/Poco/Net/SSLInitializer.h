//
// SSLInitializer.h
//
// $Id: //poco/Main/NetSSL_OpenSSL/include/Poco/Net/SSLInitializer.h#6 $
//
// Library: NetSSL_OpenSSL
// Package: SSLCore
// Module:  SSLInitializer
//
// Definition of the SSLInitializer class.
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


#ifndef NetSSL_SSLInitializer_INCLUDED
#define NetSSL_SSLInitializer_INCLUDED


#include "Poco/Net/NetSSL.h"
#include "Poco/Mutex.h"


extern "C"
{
	struct CRYPTO_dynlock_value
	{
		Poco::FastMutex _mutex;
	};
}


namespace Poco {
namespace Net {


class NetSSL_API SSLInitializer
	/// Initalizes the OpenSSL library.
	///
	/// The class ensures the earliest initialization and the
	/// latest shutdown of the OpenSSL library.
{
public:
	SSLInitializer();
		/// Automatically initialize OpenSSL on startup.
		
	~SSLInitializer();
		/// Automatically shut down OpenSSL on exit.
	
	static void initialize();
		/// Initializes the OpenSSL machinery.

	static void uninitialize();
		/// Shuts down the OpenSSL machinery.

protected:
	enum
	{
		SEEDSIZE = 256
	};
	
	// OpenSSL multithreading support
	static void lock(int mode, int n, const char* file, int line);
	static unsigned long id();
	static struct CRYPTO_dynlock_value* dynlockCreate(const char* file, int line);
	static void dynlock(int mode, struct CRYPTO_dynlock_value* lock, const char* file, int line);
	static void dynlockDestroy(struct CRYPTO_dynlock_value* lock, const char* file, int line);

private:
	static Poco::FastMutex* _mutexes;
	static int _rc;
};


} } // namespace Poco::Net


#endif // NetSSL_SSLInitializer_INCLUDED
