#pragma once

#include "AttributePair.g.h"

namespace winrt::media_foundation_explorer::implementation
{
    struct AttributePair : AttributePairT<AttributePair>
    {
        AttributePair() = default;
        AttributePair(winrt::hstring key, winrt::hstring value) : m_key(key), m_value(value) {}

        winrt::hstring Key() const { return m_key; }
        void Key(winrt::hstring value) { m_key = value; }

        winrt::hstring Value() const { return m_value; }
        void Value(winrt::hstring value) { m_value = value; }

    private:
        winrt::hstring m_key;
        winrt::hstring m_value;
    };
}

namespace winrt::media_foundation_explorer::factory_implementation
{
    struct AttributePair : AttributePairT<AttributePair, implementation::AttributePair>
    {
    };
}
