//
// ConsoleCertificateHandler.cpp
//
// $Id: //poco/Main/NetSSL_OpenSSL/src/ConsoleCertificateHandler.cpp#9 $
//
// Library: NetSSL_OpenSSL
// Package: SSLCore
// Module:  ConsoleCertificateHandler
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


#include "Poco/Net/ConsoleCertificateHandler.h"
#include <iostream>
#include "Poco/Net/CertificateHandlerFactory.h"


namespace Poco {
namespace Net {


ConsoleCertificateHandler::ConsoleCertificateHandler(bool server):InvalidCertificateHandler(server)
{
}


ConsoleCertificateHandler::~ConsoleCertificateHandler()
{
}


void ConsoleCertificateHandler::onInvalidCertificate(const void*, VerificationErrorArgs& errorCert)
{
	const X509Certificate& aCert = errorCert.certificate();
	std::cout << " Certificate:\n";
	std::cout << "----------------\n";
	std::cout << "  IssuerName: \t" << aCert.issuerName() << "\n";
	std::cout << "  SubjectName:\t" << aCert.subjectName() << "\n\n";
	std::cout << "The certificate yielded the error: " << errorCert.errorMessage() << "\n\n";
	std::cout << "The error occurred at in the certificate chain at position " << errorCert.errorDepth() << "\n";
	std::cout << "Accept the certificate? (y,n)";
	char c;
	std::cin >> c;
	if (c == 'y' || c == 'Y')
		errorCert.setIgnoreError(true);
	else
		errorCert.setIgnoreError(false);
}


POCO_REGISTER_CHFACTORY(NetSSL_API, ConsoleCertificateHandler)


} } // namespace Poco::Net
