#include "pch.h"
#include "MftDesc.h"
#if __has_include("MftDesc.g.cpp")
#include "MftDesc.g.cpp"
#endif

namespace winrt::media_foundation_explorer::implementation
{
	MftDesc::MftDesc(winrt::hstring const& name, bool canBeActivated, bool supportOutput)
		: m_name(name), m_canBeActivated(canBeActivated), m_supportOutput(supportOutput) {
	}

	// Property: CanBeActivated
	bool MftDesc::CanBeActivated() const 
	{
		return m_canBeActivated;
	}
	void MftDesc::CanBeActivated(bool value)
	{
		m_canBeActivated = value;
	}

	// Property: Name
	winrt::hstring MftDesc::Name() const 
	{ 
		return m_name; 
	}
	void MftDesc::Name(winrt::hstring const& value)
	{
		m_name = value;
	}

	// Property: SupportOutput
	bool MftDesc::SupportOutput() const 
	{ 
		return m_supportOutput; 
	}
	void MftDesc::SupportOutput(bool value)
	{
		m_supportOutput = value;
	}

	Windows::Foundation::Collections::IObservableVector<media_foundation_explorer::AttributePair> MftDesc::Attributes() const
	{
		return m_attributes;
	}
}
