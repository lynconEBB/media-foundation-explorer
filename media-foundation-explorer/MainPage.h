#pragma once

#include "MainPage.g.h"
#include "Entities/MftDesc.h"

namespace winrt::media_foundation_explorer::implementation
{
    using namespace winrt;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Navigation;
    using namespace Windows::Foundation;
    using namespace winrt::Windows::Foundation::Collections;

    struct MainPage : MainPageT<MainPage>
    {
    private:
        IObservableVector<media_foundation_explorer::MftDesc> m_mfts  = single_threaded_observable_vector<media_foundation_explorer::MftDesc>();
    public:
        MainPage();

        IObservableVector<media_foundation_explorer::MftDesc> MftList();
        
        void OnNavigatingFrom(NavigatingCancelEventArgs const& e);
        void HandleSearchButtonClick(IInspectable const& sender, RoutedEventArgs const& e);
        void SearchMFTs();
    };
}

namespace winrt::media_foundation_explorer::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
