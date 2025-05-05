#pragma once

#include <winrt/Windows.Foundation.h>
#include "AttributePair.h"
#include "MftDesc.g.h"

namespace winrt::media_foundation_explorer::implementation
{
    struct MftDesc : MftDescT<MftDesc>
    {
	private:
		bool m_canBeActivated;
		hstring m_name;
		bool m_supportOutput;
    	Windows::Foundation::Collections::IObservableVector<media_foundation_explorer::AttributePair> m_attributes{
    		single_threaded_observable_vector<media_foundation_explorer::AttributePair>()
		};

	public:
		MftDesc() = delete;
		MftDesc(hstring const& name, bool canBeActivated, bool supportOutput);

		bool CanBeActivated() const;
		void CanBeActivated(bool value);

		// Property: Name
		hstring Name() const;
		void Name(hstring const& value);

		// Property: SupportOutput
		bool SupportOutput() const;
		void SupportOutput(bool value);
    	
    	Windows::Foundation::Collections::IObservableVector<media_foundation_explorer::AttributePair> Attributes() const;
    };
}

namespace winrt::media_foundation_explorer::factory_implementation
{
    struct MftDesc : MftDescT<MftDesc, implementation::MftDesc>
    {
    };
}
