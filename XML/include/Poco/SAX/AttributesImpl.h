//
// AttributesImpl.h
//
// $Id: //poco/1.3/XML/include/Poco/SAX/AttributesImpl.h#1 $
//
// Library: XML
// Package: SAX
// Module:  SAX
//
// Implementation of the SAX2 Attributes Interface.
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


#ifndef SAX_AttributesImpl_INCLUDED
#define SAX_AttributesImpl_INCLUDED


#include "Poco/XML/XML.h"
#include "Poco/SAX/Attributes.h"
#include <vector>


namespace Poco {
namespace XML {


class XML_API AttributesImpl: public Attributes
	/// This class provides a default implementation of the SAX2 Attributes interface, 
	/// with the addition of manipulators so that the list can be modified or reused.
	/// 
	/// There are two typical uses of this class:
	///     1. to take a persistent snapshot of an Attributes object in a startElement event; or
	///     2. to construct or modify an Attributes object in a SAX2 driver or filter.
{
public:
	AttributesImpl();
		/// Creates the AttributesImpl.
		
	AttributesImpl(const Attributes& attributes);
		/// Creates the AttributesImpl by copying another one.

	AttributesImpl(const AttributesImpl& attributes);
		/// Creates the AttributesImpl by copying another one.

	~AttributesImpl();
		/// Destroys the AttributesImpl.

	AttributesImpl& operator = (const AttributesImpl& attributes);
		/// Assignment operator.

	int getIndex(const XMLString& name) const;
	int getIndex(const XMLString& namespaceURI, const XMLString& localName) const;
	int getLength() const;
	XMLString getLocalName(int i) const;
	XMLString getQName(int i) const;
	XMLString getType(int i) const;
	XMLString getType(const XMLString& qname) const;
	XMLString getType(const XMLString& namespaceURI, const XMLString& localName) const;
	XMLString getValue(int i) const;
	XMLString getValue(const XMLString& qname) const;
	XMLString getValue(const XMLString& namespaceURI, const XMLString& localName) const;
	XMLString getURI(int i) const;

	bool isSpecified(int i) const;
		/// Returns true unless the attribute value was provided by DTD defaulting.
		/// Extension from Attributes2 interface.

	bool isSpecified(const XMLString& qname) const;
		/// Returns true unless the attribute value was provided by DTD defaulting.
		/// Extension from Attributes2 interface.

	bool isSpecified(const XMLString& namespaceURI, const XMLString& localName) const;
		/// Returns true unless the attribute value was provided by DTD defaulting.
		/// Extension from Attributes2 interface.

	void setValue(int i, const XMLString& value);
		/// Sets the value of an attribute.

	void setValue(const XMLString& qname, const XMLString& value);
		/// Sets the value of an attribute.

	void setValue(const XMLString& namespaceURI, const XMLString& localName, const XMLString& value);
		/// Sets the value of an attribute.

	void setAttributes(const Attributes& attributes);
		/// Copies the attributes from another Attributes object.

	void setAttribute(int i, const XMLString& namespaceURI, const XMLString& localName, const XMLString& qname, const XMLString& type, const XMLString& value);
		/// Sets an attribute.

	void addAttribute(const XMLString& namespaceURI, const XMLString& localName, const XMLString& qname, const XMLString& type, const XMLString& value);
		/// Adds an attribute to the end of the list.

	void addAttribute(const XMLString& namespaceURI, const XMLString& localName, const XMLString& qname, const XMLString& type, const XMLString& value, bool specified);
		/// Adds an attribute to the end of the list.

	void addAttribute(const XMLChar* namespaceURI, const XMLChar* localName, const XMLChar* qname, const XMLChar* type, const XMLChar* value, bool specified);
		/// Adds an attribute to the end of the list.

	void removeAttribute(int i);
		/// Removes an attribute.

	void removeAttribute(const XMLString& qname);
		/// Removes an attribute.

	void removeAttribute(const XMLString& namespaceURI, const XMLString& localName);
		/// Removes an attribute.

	void clear();
		/// Removes all attributes.

	void setLocalName(int i, const XMLString& localName);
		/// Sets the local name of an attribute.

	void setQName(int i, const XMLString& qname);
		/// Sets the qualified name of an attribute.

	void setType(int i, const XMLString& type);
		/// Sets the type of an attribute.

	void setURI(int i, const XMLString& namespaceURI);
		/// Sets the namespace URI of an attribute.

	struct Attribute
	{
		XMLString localName;
		XMLString namespaceURI;
		XMLString qname;
		XMLString value;
		XMLString type;
		bool      specified;
	};
	typedef std::vector<Attribute> AttributeVec;
	typedef AttributeVec::const_iterator iterator;

	iterator begin() const;
		/// Iterator support.
		
	iterator end() const;
		/// Iterator support.

protected:	
	Attribute* find(const XMLString& qname) const;
	Attribute* find(const XMLString& namespaceURI, const XMLString& localName) const;

private:
	AttributeVec _attributes;
};


//
// inlines
//
inline AttributesImpl::iterator AttributesImpl::begin() const
{
	return _attributes.begin();
}


inline AttributesImpl::iterator AttributesImpl::end() const
{
	return _attributes.end();
}


} } // namespace Poco::XML


#endif // SAX_AttributesImpl_INCLUDED
