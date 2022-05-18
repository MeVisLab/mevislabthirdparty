#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <iostream>

XERCES_CPP_NAMESPACE_USE

class XStr
{
public :
    XStr(const char* const toTranscode)
    {
        fUnicodeForm = XMLString::transcode(toTranscode);
    }

    ~XStr()
    {
        XMLString::release(&fUnicodeForm);
    }

    const XMLCh* unicodeForm() const
    {
        return fUnicodeForm;
    }

private:
    XMLCh*   fUnicodeForm;
};

#define X(str) XStr(str).unicodeForm()



int main(int argC, char**)
{
    try
    {
        XMLPlatformUtils::Initialize();
    }

    catch(const XMLException& toCatch)
    {
        char *pMsg = XMLString::transcode(toCatch.getMessage());
        XERCES_STD_QUALIFIER cerr << "Error during Xerces-c Initialization.\n"
             << "  Exception message:"
             << pMsg;
        XMLString::release(&pMsg);
        return 1;
    }

    // Watch for special case help request
    int errorCode = 0;
    if (argC > 1)
    {
        XERCES_STD_QUALIFIER cout << "\nUsage:\n"
                "    CreateDOMDocument\n\n"
                "This program creates a new DOM document from scratch in memory.\n"
                "It then prints the count of elements in the tree.\n"
             << XERCES_STD_QUALIFIER endl;
        errorCode = 1;
    }
    if(errorCode) {
        XMLPlatformUtils::Terminate();
        return errorCode;
    }

   {
       DOMImplementation* impl =  DOMImplementationRegistry::getDOMImplementation(X("Core"));

       if (impl != NULL)
       {
           try
           {
               DOMDocument* doc = impl->createDocument(
                           0,                    // root element namespace URI.
                           X("company"),         // root element name
                           0);                   // document type object (DTD).

               DOMElement* rootElem = doc->getDocumentElement();

               DOMElement*  prodElem = doc->createElement(X("product"));
               rootElem->appendChild(prodElem);

               DOMText*    prodDataVal = doc->createTextNode(X("Xerces-C"));
               prodElem->appendChild(prodDataVal);

               DOMElement*  catElem = doc->createElement(X("category"));
               rootElem->appendChild(catElem);

               catElem->setAttribute(X("idea"), X("great"));

               DOMText*    catDataVal = doc->createTextNode(X("XML Parsing Tools"));
               catElem->appendChild(catDataVal);

               DOMElement*  devByElem = doc->createElement(X("developedBy"));
               rootElem->appendChild(devByElem);

               DOMText*    devByDataVal = doc->createTextNode(X("Apache Software Foundation"));
               devByElem->appendChild(devByDataVal);

               unsigned int elementCount = doc->getElementsByTagName(X("*"))->getLength();
               XERCES_STD_QUALIFIER cout << "The tree just created contains: " << elementCount
                    << " elements." << XERCES_STD_QUALIFIER endl;

               doc->release();
           }
           catch (const OutOfMemoryException&)
           {
               XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
               errorCode = 5;
           }
           catch (const DOMException& e)
           {
               XERCES_STD_QUALIFIER cerr << "DOMException code is:  " << e.code << XERCES_STD_QUALIFIER endl;
               errorCode = 2;
           }
           catch (...)
           {
               XERCES_STD_QUALIFIER cerr << "An error occurred creating the document" << XERCES_STD_QUALIFIER endl;
               errorCode = 3;
           }
       }  // (inpl != NULL)
       else
       {
           XERCES_STD_QUALIFIER cerr << "Requested implementation is not supported" << XERCES_STD_QUALIFIER endl;
           errorCode = 4;
       }
   }

   XMLPlatformUtils::Terminate();
   return errorCode;
}
