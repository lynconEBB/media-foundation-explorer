#include "pch.h"
#include <iostream>
#include "MainPage.h"
#include <mfapi.h>
#include <mfidl.h>
#include <iostream>
#include <sstream>
#include "MainPage.g.cpp"

namespace winrt::media_foundation_explorer::implementation
{
    void MainPage::HandleSearchButtonClick(IInspectable const& sender, RoutedEventArgs const& e)
    {
        SearchButton().Content(box_value(L"Searching..."));
        SearchMFTs();
    }

    MainPage::MainPage(): MainPageT()
    {
        m_mfts = single_threaded_observable_vector<media_foundation_explorer::MftDesc>();
    }

    IObservableVector<media_foundation_explorer::MftDesc> MainPage::MftList()
    {
        return m_mfts;
    }

    void MainPage::OnNavigatingFrom(NavigatingCancelEventArgs const& e)
    {
        check_hresult(MFShutdown());
    }

    hstring GUIDToString(GUID id)
    {
        wchar_t buffer[39];
        int length = StringFromGUID2(id, buffer, ARRAYSIZE(buffer));
        if (length == 0)
        {
            return hstring{};
        }
        return hstring{ buffer };       
    }

    hstring VariantToString(PROPVARIANT var)
    {
        std::wstringstream ss;
        switch (var.vt)
        {
        case VT_UI4:
            ss << var.ulVal;
            break;
        case VT_UI8:
            ss << var.uhVal.QuadPart;
            break;
        case VT_R8:
            ss << var.dblVal;
            break;
        case VT_CLSID:
            ss << GUIDToString(*var.puuid).c_str();
            break;
        case VT_LPWSTR:
            ss << var.pwszVal;
            break;
        case VT_BLOB:
            ss << L"(BLOB data)";
            break;
        default:
            ss << L"(Unknown type)";
            break;
        }

        return hstring{ss.str()};
    }

    void AddAttributesToMft(com_ptr<IMFAttributes>& attribute, media_foundation_explorer::MftDesc& mft) 
    {
        uint32_t count;
        check_hresult(attribute->LockStore());
        check_hresult(attribute->GetCount(&count));

        for (uint32_t i = 0; i < count; ++i)
        {
            GUID key;
            PROPVARIANT var;
            PropVariantInit(&var);

            check_hresult(attribute->GetItemByIndex(i, &key, &var));
        
            mft.Attributes().Append(make<media_foundation_explorer::implementation::AttributePair>(GUIDToString(key), VariantToString(var)));
        }
        check_hresult(attribute->UnlockStore());
    }
    
    void MainPage::SearchMFTs() 
    {
        try {
            check_hresult(MFStartup(MF_VERSION));
            MFT_REGISTER_TYPE_INFO outputType = { MFMediaType_Video, MFVideoFormat_H264 };
            IMFActivate** activators;
            uint32_t count;

            MFTEnumEx(
                MFT_CATEGORY_VIDEO_ENCODER,
                MFT_ENUM_FLAG_HARDWARE | MFT_ENUM_FLAG_SORTANDFILTER,
                nullptr,
                &outputType,
                &activators,
                &count
            );

            for (int i = 0; i < count; i++) {
                WCHAR* name;
                uint32_t nameSize;
                check_hresult(activators[i]->GetAllocatedString(MFT_FRIENDLY_NAME_Attribute, &name, &nameSize));
                hstring nameString(name);
                
                com_ptr<IMFTransform> transform;
                HRESULT hr = activators[i]->ActivateObject(IID_PPV_ARGS(transform.put()));

                if (!SUCCEEDED(hr)) {
                    m_mfts.Append(make<MftDesc>(L"fdsfds", true, SUCCEEDED(hr)));
                    continue;
                }
                
				com_ptr<IMFMediaType> mediaType;
				check_hresult(MFCreateMediaType(mediaType.put()));
                mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
                mediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_NV12);
                
                hr = transform->SetInputType(0, mediaType.get(), MFT_SET_TYPE_TEST_ONLY);
                media_foundation_explorer::MftDesc mft = make<MftDesc>(name, true, SUCCEEDED(hr));
                
                com_ptr<IMFAttributes> attributesPtr;
                activators[i]->QueryInterface(IID_PPV_ARGS(attributesPtr.put()));
                AddAttributesToMft(attributesPtr, mft);
                
                m_mfts.Append(mft);
                activators[i]->Release();
            }

        }
        catch (const hresult_error e) {
            OutputDebugString(e.message().c_str());
        }
    }


}