#include "XmlWriter.hpp"

#include "xmllite.h"
#include "Shlwapi.h"

void XmlWriter::writeToFile(const std::vector<std::string>& data) const
{
    // Create XmlLite object
    IXmlWriter* pWriter{ nullptr };
    CreateXmlWriter(__uuidof(IXmlWriter), reinterpret_cast<void**>(&pWriter), nullptr); //reinterpret cast used on microsoft's side as example, normally shouldn't be used

    // Create a stream for output
    IStream* pStream{ nullptr };
    HRESULT hr{ SHCreateStreamOnFile(L"output.xml", STGM_CREATE | STGM_WRITE, &pStream) };

    // Set output to the stream
    pWriter->SetOutput(pStream);

    // Start writing XML
    pWriter->WriteStartDocument(XmlStandalone_Omit);

    std::wstring rootOfXmlFile(data[0].begin(), data[0].end());
    pWriter->WriteStartElement(nullptr, rootOfXmlFile.c_str(), nullptr);

    //Used two pointers algorithm to avoid using nested loops to optimize time and space complexity
    int j{ 1 };
    int k{ 2 };

    while (k < data.size())
    {
        std::wstring xmlTag(data[j].begin(), data[j].end());
        pWriter->WriteStartElement(nullptr, xmlTag.c_str(), nullptr);
        std::wstring text(data[k].begin(), data[k].end());
        pWriter->WriteString(text.c_str());
        pWriter->WriteEndElement();

        j += 2;
        k += 2;
    }

    // End writing XML
    pWriter->WriteEndElement(); // Close root element
    pWriter->WriteEndDocument();

    // Release resources
    pWriter->Release();
    pStream->Release();
}
