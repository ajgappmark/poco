//
// HTTPSClientSession.h
//
// $Id: //poco/Main/NetSSL_OpenSSL/include/Poco/Net/HTTPSClientSession.h#6 $
//
// Library: NetSSL_OpenSSL
// Package: HTTPSClient
// Module:  HTTPSClientSession
//
// Definition of the HTTPSClientSession class.
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


#ifndef NetSSL_HTTPSClientSession_INCLUDED
#define NetSSL_HTTPSClientSession_INCLUDED


#include "Poco/Net/NetSSL.h"
#include "Poco/Net/Utility.h"
#include "Poco/Net/HTTPClientSession.h"


namespace Poco {
namespace Net {


class SecureStreamSocket;
class HTTPRequest;
class HTTPResponse;


class NetSSL_API HTTPSClientSession: public HTTPClientSession
	/// This class implements the client-side of
	/// a HTTPS session.
	///
	/// To send a HTTPS request to a HTTPS server, first
	/// instantiate a HTTPSClientSession object and
	/// specify the server's host name and port number.
	///
	/// Then create a HTTPRequest object, fill it accordingly,
	/// and pass it as argument to the sendRequst() method.
	///
	/// sendRequest() will return an output stream that can
	/// be used to send the request body, if there is any.
	///
	/// After you are done sending the request body, create
	/// a HTTPResponse object and pass it to receiveResponse().
	///
	/// This will return an input stream that can be used to
	/// read the response body.
	///
	/// See RFC 2616 <http://www.faqs.org/rfcs/rfc2616.html> for more
	/// information about the HTTP protocol.
{
public:
	HTTPSClientSession();
		/// Creates an unconnected HTTPSClientSession.

	HTTPSClientSession(const SecureStreamSocket& socket);
		/// Creates a HTTPSClientSession using the given socket.
		/// The socket must not be connected. The session
		/// takes ownership of the socket.

	HTTPSClientSession(const std::string& host, Poco::UInt16 port = Utility::HTTPS_PORT);
		/// Creates a HTTPSClientSession using the given host and port.

	~HTTPSClientSession();
		/// Destroys the HTTPSClientSession and closes
		/// the underlying socket.
		
	std::ostream& sendRequest(HTTPRequest& request);
		/// Sends the header for the given HTTPS request to
		/// the server.
		///
		/// The HTTPSClientSession will set the request's
		/// Host and Keep-Alive headers accordingly.
		///
		/// The returned output stream can be used to write
		/// the request body. The stream is valid until
		/// receiveResponse() is called or the session
		/// is destroyed.
		
	std::istream& receiveResponse(HTTPResponse& response);
		/// Receives the header for the response to the previous 
		/// HTTPS request.
		///
		/// The returned input stream can be used to read
		/// the response body. The stream is valid until
		/// sendRequest() is called or the session is
		/// destroyed.
	
protected:
	void connect(const SocketAddress& address);
		// Connects the socket to the server.
	
	std::string getHostInfo() const;
		/// Returns the target host and port number for proxy requests.
};


} } // namespace Poco::Net


#endif // Net_HTTPSClientSession_INCLUDED
