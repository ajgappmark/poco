//
// DOMSerializer.h
//
// $Id: //poco/1.3/XML/include/Poco/DOM/DOMSerializer.h#1 $
//
// Library: XML
// Package: DOM
// Module:  DOMSerializer
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


#ifndef DOM_DOMSerializer_INCLUDED
#define DOM_DOMSerializer_INCLUDED


#include "Poco/XML/XML.h"
#include "Poco/SAX/XMLReader.h"


namespace Poco {
namespace XML {


class Node;
class Element;
class Text;
class Comment;
class ProcessingInstruction;
class Entity;
class CDATASection;
class Notation;
class Document;
class DocumentType;
class DocumentFragment;
class DeclHandler;
class LexicalHandler;


class XML_API DOMSerializer: public XMLReader
	/// The DOMSerializer serializes a DOM document
	/// into a sequence of SAX events which are
	/// reported to the registered SAX event
	/// handlers.
	///
	/// The DOMWriter uses a DOMSerializer with an
	/// XMLWriter to serialize a DOM document into
	/// textual XML.
{
public:
	DOMSerializer();
		/// Creates the DOMSerializer.
		
	~DOMSerializer();
		/// Destroys the DOMSerializer.
		
	void serialize(const Node* pNode);
		/// Serializes a DOM node and its children
		/// into a sequence of SAX events, which are
		/// reported to the registered SAX event
		/// handlers.

	// XMLReader
	void setEntityResolver(EntityResolver* pResolver);
	EntityResolver* getEntityResolver() const;
	void setDTDHandler(DTDHandler* pDTDHandler);
	DTDHandler* getDTDHandler() const;
	void setContentHandler(ContentHandler* pContentHandler);
	ContentHandler* getContentHandler() const;
	void setErrorHandler(ErrorHandler* pErrorHandler);
	ErrorHandler* getErrorHandler() const;

	void setFeature(const XMLString& featureId, bool state);
	bool getFeature(const XMLString& featureId) const;
	void setProperty(const XMLString& propertyId, const XMLString& value);
	void setProperty(const XMLString& propertyId, void* value);
	void* getProperty(const XMLString& propertyId) const;

protected:
	void parse(InputSource* pSource);
		/// The DOMSerializer cannot parse an InputSource,
		/// so this method simply throws an XMLException when invoked.
		
	void parse(const XMLString& systemId);
		/// The DOMSerializer cannot parse from a system identifier,
		/// so this method simply throws an XMLException when invoked.

	void iterate(const Node* pNode) const;
	void handleNode(const Node* pNode) const;
	void handleElement(const Element* pElement) const;
	void handleCharacterData(const Text* pText) const;
	void handleComment(const Comment* pComment) const;
	void handlePI(const ProcessingInstruction* pPI) const;
	void handleCDATASection(const CDATASection* pCDATA) const;
	void handleDocument(const Document* pDocument) const;
	void handleDocumentType(const DocumentType* pDocumentType) const;
	void handleFragment(const DocumentFragment* pFragment) const;
	void handleNotation(const Notation* pNotation) const;
	void handleEntity(const Entity* pEntity) const;

private:
	EntityResolver* _pEntityResolver;
	DTDHandler*     _pDTDHandler;
	ContentHandler* _pContentHandler;
	ErrorHandler*   _pErrorHandler;
	DeclHandler*    _pDeclHandler;
	LexicalHandler* _pLexicalHandler;
	
	static const XMLString CDATA;
};


} } // namespace Poco::XML


#endif // DOM_DOMSerializer_INCLUDED
