//
// ParserWriterTest.cpp
//
// $Id: //poco/1.3/XML/testsuite/src/ParserWriterTest.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#include "ParserWriterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/SAX/InputSource.h"
#include "Poco/XML/XMLWriter.h"
#include <sstream>
#include <fstream>


using Poco::XML::DOMParser;
using Poco::XML::DOMWriter;
using Poco::XML::XMLReader;
using Poco::XML::XMLWriter;
using Poco::XML::Document;
using Poco::XML::AutoPtr;
using Poco::XML::InputSource;


ParserWriterTest::ParserWriterTest(const std::string& name): CppUnit::TestCase(name)
{
}


ParserWriterTest::~ParserWriterTest()
{
}


void ParserWriterTest::testParseWriteXHTML()
{
	std::ostringstream ostr;
	
	DOMParser parser;
	parser.setFeature(XMLReader::FEATURE_NAMESPACE_PREFIXES, false);
	DOMWriter writer;
	AutoPtr<Document> pDoc = parser.parseString(XHTML);
	writer.writeNode(ostr, pDoc);
	
	std::string xml = ostr.str();
	assert (xml == XHTML);
}


void ParserWriterTest::testParseWriteXHTML2()
{
	std::ostringstream ostr;
	
	DOMParser parser;
	parser.setFeature(XMLReader::FEATURE_NAMESPACE_PREFIXES, true);
	DOMWriter writer;
	AutoPtr<Document> pDoc = parser.parseString(XHTML2);
	writer.writeNode(ostr, pDoc);
	
	std::string xml = ostr.str();
	assert (xml == XHTML2);
}


void ParserWriterTest::testParseWriteWSDL()
{
	std::istringstream istr(WSDL);
	std::ostringstream ostr;

	DOMParser parser;
	parser.setFeature(DOMParser::FEATURE_WHITESPACE, false);
	parser.setFeature(XMLReader::FEATURE_NAMESPACE_PREFIXES, false);
	DOMWriter writer;
	writer.setOptions(XMLWriter::CANONICAL | XMLWriter::PRETTY_PRINT);
	writer.setNewLine(XMLWriter::NEWLINE_LF);
	InputSource source(istr);
	AutoPtr<Document> pDoc = parser.parse(&source);
	writer.writeNode(ostr, pDoc);
	
	std::string xml = ostr.str();
	assert (xml == WSDL);
}


void ParserWriterTest::setUp()
{
}


void ParserWriterTest::tearDown()
{
}


CppUnit::Test* ParserWriterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ParserWriterTest");

	CppUnit_addTest(pSuite, ParserWriterTest, testParseWriteXHTML);
	CppUnit_addTest(pSuite, ParserWriterTest, testParseWriteXHTML2);
	CppUnit_addTest(pSuite, ParserWriterTest, testParseWriteWSDL);

	return pSuite;
}


const std::string ParserWriterTest::XHTML =
	"<!--\n"
	"\tThis is a comment.\n"
	"-->"
	"<ns1:html xml:lang=\"en\" xmlns:ns1=\"http://www.w3.org/1999/xhtml\">\n"
	"\t<ns1:head>\n"
	"\t\t<ns1:link href=\"styles.css\" rel=\"stylesheet\" type=\"text/css\"/>\n"
	"\t\t<?xml-stylesheet href=\"styles.css\" type=\"text/css\"?>\n"
	"\t\t<ns1:title>A XHTML Example</ns1:title>\n"
	"\t</ns1:head>\n"
	"\t<ns1:body>\n"
	"\t\t<ns1:h1>XHTML Example</ns1:h1>\n"
	"\t\t<ns1:p>This is a XHTML example page.</ns1:p>\n"
	"\t\t<ns1:img alt=\"Example Picture\" border=\"0\" height=\"192\" src=\"example.gif\" width=\"256\"/>\n"
	"\t\t<![CDATA[\n"
	"\t\tThe following <tag attr=\"value\">is inside a CDATA section</tag>.\n"
	"\t\t]]>\n"
	"\t</ns1:body>\n"
	"</ns1:html>";


const std::string ParserWriterTest::XHTML2 =
	"<!--\n"
	"\tThis is a comment.\n"
	"-->"
	"<xns:html xml:lang=\"en\" xmlns:xns=\"http://www.w3.org/1999/xhtml\">\n"
	"\t<xns:head>\n"
	"\t\t<xns:link href=\"styles.css\" rel=\"stylesheet\" type=\"text/css\"/>\n"
	"\t\t<?xml-stylesheet href=\"styles.css\" type=\"text/css\"?>\n"
	"\t\t<xns:title>A XHTML Example</xns:title>\n"
	"\t</xns:head>\n"
	"\t<xns:body>\n"
	"\t\t<xns:h1>XHTML Example</xns:h1>\n"
	"\t\t<xns:p>This is a XHTML example page.</xns:p>\n"
	"\t\t<xns:img alt=\"Example Picture\" border=\"0\" height=\"192\" src=\"example.gif\" width=\"256\"/>\n"
	"\t\t<![CDATA[\n"
	"\t\tThe following <tag attr=\"value\">is inside a CDATA section</tag>.\n"
	"\t\t]]>\n"
	"\t</xns:body>\n"
	"</xns:html>";


const std::string ParserWriterTest::WSDL =
	"<!-- WSDL description of the Google Web APIs.\n"
	"     The Google Web APIs are in beta release. All interfaces are subject to\n"
	"     change as we refine and extend our APIs. Please see the terms of use\n"
	"     for more information. -->\n"
	"<!-- Revision 2002-08-16 -->\n"
	"<ns1:definitions name=\"GoogleSearch\" targetNamespace=\"urn:GoogleSearch\" xmlns:ns1=\"http://schemas.xmlsoap.org/wsdl/\">\n"
	"\t<!-- Types for search - result elements, directory categories -->\n"
	"\t<ns1:types>\n"
	"\t\t<ns2:schema targetNamespace=\"urn:GoogleSearch\" xmlns:ns2=\"http://www.w3.org/2001/XMLSchema\">\n"
	"\t\t\t<ns2:complexType name=\"GoogleSearchResult\">\n"
	"\t\t\t\t<ns2:all>\n"
	"\t\t\t\t\t<ns2:element name=\"documentFiltering\" type=\"xsd:boolean\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"searchComments\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"estimatedTotalResultsCount\" type=\"xsd:int\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"estimateIsExact\" type=\"xsd:boolean\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"resultElements\" type=\"typens:ResultElementArray\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"searchQuery\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"startIndex\" type=\"xsd:int\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"endIndex\" type=\"xsd:int\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"searchTips\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"directoryCategories\" type=\"typens:DirectoryCategoryArray\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"searchTime\" type=\"xsd:double\"/>\n"
	"\t\t\t\t</ns2:all>\n"
	"\t\t\t</ns2:complexType>\n"
	"\t\t\t<ns2:complexType name=\"ResultElement\">\n"
	"\t\t\t\t<ns2:all>\n"
	"\t\t\t\t\t<ns2:element name=\"summary\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"URL\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"snippet\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"title\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"cachedSize\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"relatedInformationPresent\" type=\"xsd:boolean\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"hostName\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"directoryCategory\" type=\"typens:DirectoryCategory\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"directoryTitle\" type=\"xsd:string\"/>\n"
	"\t\t\t\t</ns2:all>\n"
	"\t\t\t</ns2:complexType>\n"
	"\t\t\t<ns2:complexType name=\"ResultElementArray\">\n"
	"\t\t\t\t<ns2:complexContent>\n"
	"\t\t\t\t\t<ns2:restriction base=\"soapenc:Array\">\n"
	"\t\t\t\t\t\t<ns2:attribute ns1:arrayType=\"typens:ResultElement[]\" ref=\"soapenc:arrayType\"/>\n"
	"\t\t\t\t\t</ns2:restriction>\n"
	"\t\t\t\t</ns2:complexContent>\n"
	"\t\t\t</ns2:complexType>\n"
	"\t\t\t<ns2:complexType name=\"DirectoryCategoryArray\">\n"
	"\t\t\t\t<ns2:complexContent>\n"
	"\t\t\t\t\t<ns2:restriction base=\"soapenc:Array\">\n"
	"\t\t\t\t\t\t<ns2:attribute ns1:arrayType=\"typens:DirectoryCategory[]\" ref=\"soapenc:arrayType\"/>\n"
	"\t\t\t\t\t</ns2:restriction>\n"
	"\t\t\t\t</ns2:complexContent>\n"
	"\t\t\t</ns2:complexType>\n"
	"\t\t\t<ns2:complexType name=\"DirectoryCategory\">\n"
	"\t\t\t\t<ns2:all>\n"
	"\t\t\t\t\t<ns2:element name=\"fullViewableName\" type=\"xsd:string\"/>\n"
	"\t\t\t\t\t<ns2:element name=\"specialEncoding\" type=\"xsd:string\"/>\n"
	"\t\t\t\t</ns2:all>\n"
	"\t\t\t</ns2:complexType>\n"
	"\t\t</ns2:schema>\n"
	"\t</ns1:types>\n"
	"\t<!-- Messages for Google Web APIs - cached page, search, spelling. -->\n"
	"\t<ns1:message name=\"doGetCachedPage\">\n"
	"\t\t<ns1:part name=\"key\" type=\"xsd:string\"/>\n"
	"\t\t<ns1:part name=\"url\" type=\"xsd:string\"/>\n"
	"\t</ns1:message>\n"
	"\t<ns1:message name=\"doGetCachedPageResponse\">\n"
	"\t\t<ns1:part name=\"return\" type=\"xsd:base64Binary\"/>\n"
	"\t</ns1:message>\n"
	"\t<ns1:message name=\"doSpellingSuggestion\">\n"
	"\t\t<ns1:part name=\"key\" type=\"xsd:string\"/>\n"
	"\t\t<ns1:part name=\"phrase\" type=\"xsd:string\"/>\n"
	"\t</ns1:message>\n"
	"\t<ns1:message name=\"doSpellingSuggestionResponse\">\n"
	"\t\t<ns1:part name=\"return\" type=\"xsd:string\"/>\n"
	"\t</ns1:message>\n"
	"\t<!-- note, ie and oe are ignored by server; all traffic is UTF-8. -->\n"
	"\t<ns1:message name=\"doGoogleSearch\">\n"
	"\t\t<ns1:part name=\"key\" type=\"xsd:string\"/>\n"
	"\t\t<ns1:part name=\"q\" type=\"xsd:string\"/>\n"
	"\t\t<ns1:part name=\"start\" type=\"xsd:int\"/>\n"
	"\t\t<ns1:part name=\"maxResults\" type=\"xsd:int\"/>\n"
	"\t\t<ns1:part name=\"filter\" type=\"xsd:boolean\"/>\n"
	"\t\t<ns1:part name=\"restrict\" type=\"xsd:string\"/>\n"
	"\t\t<ns1:part name=\"safeSearch\" type=\"xsd:boolean\"/>\n"
	"\t\t<ns1:part name=\"lr\" type=\"xsd:string\"/>\n"
	"\t\t<ns1:part name=\"ie\" type=\"xsd:string\"/>\n"
	"\t\t<ns1:part name=\"oe\" type=\"xsd:string\"/>\n"
	"\t</ns1:message>\n"
	"\t<ns1:message name=\"doGoogleSearchResponse\">\n"
	"\t\t<ns1:part name=\"return\" type=\"typens:GoogleSearchResult\"/>\n"
	"\t</ns1:message>\n"
	"\t<!-- Port for Google Web APIs, \"GoogleSearch\" -->\n"
	"\t<ns1:portType name=\"GoogleSearchPort\">\n"
	"\t\t<ns1:operation name=\"doGetCachedPage\">\n"
	"\t\t\t<ns1:input message=\"typens:doGetCachedPage\"/>\n"
	"\t\t\t<ns1:output message=\"typens:doGetCachedPageResponse\"/>\n"
	"\t\t</ns1:operation>\n"
	"\t\t<ns1:operation name=\"doSpellingSuggestion\">\n"
	"\t\t\t<ns1:input message=\"typens:doSpellingSuggestion\"/>\n"
	"\t\t\t<ns1:output message=\"typens:doSpellingSuggestionResponse\"/>\n"
	"\t\t</ns1:operation>\n"
	"\t\t<ns1:operation name=\"doGoogleSearch\">\n"
	"\t\t\t<ns1:input message=\"typens:doGoogleSearch\"/>\n"
	"\t\t\t<ns1:output message=\"typens:doGoogleSearchResponse\"/>\n"
	"\t\t</ns1:operation>\n"
	"\t</ns1:portType>\n"
	"\t<!-- Binding for Google Web APIs - RPC, SOAP over HTTP -->\n"
	"\t<ns1:binding name=\"GoogleSearchBinding\" type=\"typens:GoogleSearchPort\">\n"
	"\t\t<ns3:binding style=\"rpc\" transport=\"http://schemas.xmlsoap.org/soap/http\" xmlns:ns3=\"http://schemas.xmlsoap.org/wsdl/soap/\"/>\n"
	"\t\t<ns1:operation name=\"doGetCachedPage\" xmlns:ns3=\"http://schemas.xmlsoap.org/wsdl/soap/\">\n"
	"\t\t\t<ns3:operation soapAction=\"urn:GoogleSearchAction\"/>\n"
	"\t\t\t<ns1:input>\n"
	"\t\t\t\t<ns3:body encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" namespace=\"urn:GoogleSearch\" use=\"encoded\"/>\n"
	"\t\t\t</ns1:input>\n"
	"\t\t\t<ns1:output>\n"
	"\t\t\t\t<ns3:body encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" namespace=\"urn:GoogleSearch\" use=\"encoded\"/>\n"
	"\t\t\t</ns1:output>\n"
	"\t\t</ns1:operation>\n"
	"\t\t<ns1:operation name=\"doSpellingSuggestion\" xmlns:ns3=\"http://schemas.xmlsoap.org/wsdl/soap/\">\n"
	"\t\t\t<ns3:operation soapAction=\"urn:GoogleSearchAction\"/>\n"
	"\t\t\t<ns1:input>\n"
	"\t\t\t\t<ns3:body encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" namespace=\"urn:GoogleSearch\" use=\"encoded\"/>\n"
	"\t\t\t</ns1:input>\n"
	"\t\t\t<ns1:output>\n"
	"\t\t\t\t<ns3:body encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" namespace=\"urn:GoogleSearch\" use=\"encoded\"/>\n"
	"\t\t\t</ns1:output>\n"
	"\t\t</ns1:operation>\n"
	"\t\t<ns1:operation name=\"doGoogleSearch\" xmlns:ns3=\"http://schemas.xmlsoap.org/wsdl/soap/\">\n"
	"\t\t\t<ns3:operation soapAction=\"urn:GoogleSearchAction\"/>\n"
	"\t\t\t<ns1:input>\n"
	"\t\t\t\t<ns3:body encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" namespace=\"urn:GoogleSearch\" use=\"encoded\"/>\n"
	"\t\t\t</ns1:input>\n"
	"\t\t\t<ns1:output>\n"
	"\t\t\t\t<ns3:body encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" namespace=\"urn:GoogleSearch\" use=\"encoded\"/>\n"
	"\t\t\t</ns1:output>\n"
	"\t\t</ns1:operation>\n"
	"\t</ns1:binding>\n"
	"\t<!-- Endpoint for Google Web APIs -->\n"
	"\t<ns1:service name=\"GoogleSearchService\">\n"
	"\t\t<ns1:port binding=\"typens:GoogleSearchBinding\" name=\"GoogleSearchPort\">\n"
	"\t\t\t<ns4:address location=\"http://api.google.com/search/beta2\" xmlns:ns4=\"http://schemas.xmlsoap.org/wsdl/soap/\"/>\n"
	"\t\t</ns1:port>\n"
	"\t</ns1:service>\n"
	"</ns1:definitions>\n";
