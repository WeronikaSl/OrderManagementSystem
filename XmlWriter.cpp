#include "XmlWriter.hpp"

#include "xmllite.h"
#include "Shlwapi.h"

void XmlWriter::writeToFile(const std::vector<std::string>& data) const
{
    // Create XmlLite object
    IXmlWriter* pWriter = nullptr;
    CreateXmlWriter(__uuidof(IXmlWriter), reinterpret_cast<void**>(&pWriter), nullptr); //reinterpret cast used on microsoft's side as example

    // Create a stream for output
    IStream* pStream = nullptr;
    HRESULT hr = SHCreateStreamOnFile(L"output.xml", STGM_CREATE | STGM_WRITE, &pStream);

    // Set output to the stream
    pWriter->SetOutput(pStream);

    // Start writing XML
    pWriter->WriteStartDocument(XmlStandalone_Omit);

    std::wstring root(data[0].begin(), data[0].end()); //TODO ORDERS, PRODUCTS OR CUSTOMERS. Change to better variable name later, can i change it to {}?
    pWriter->WriteStartElement(nullptr, root.c_str(), nullptr);

    //Used two pointers algorithm to avoid using nested loops to optimize time and space complexity
    int j{ 1 };
    int k{ 2 };

    while (k < data.size())
    {
        std::wstring elem1(data[j].begin(), data[j].end());
        pWriter->WriteStartElement(nullptr, elem1.c_str(), nullptr);
        std::wstring elem2(data[k].begin(), data[k].end());
        pWriter->WriteString(elem2.c_str());
        pWriter->WriteEndElement();

        j += 2;
        k += 2;
    }

    // End writing XML
    pWriter->WriteEndElement(); // Close root element
    pWriter->WriteEndDocument();

    // Release resources
    pWriter->Release();
    pStream->Release(); //TODO use RAII?
}
