#pragma once

#include <cstdint>
#include <functional>
#include <memory>

#include "Hypodermic/ITypeAlias.h"
#include "Hypodermic/TypeAlias.h"
#include "Hypodermic/TypeInfo.h"


namespace Hypodermic
{

    class TypeAliasKey
    {
    public:
        explicit TypeAliasKey(const std::shared_ptr< ITypeAlias >& typeAlias)
            : m_typeAlias(typeAlias)
        {
        }

        bool operator==(const TypeAliasKey& rhs) const
        {
            return *m_typeAlias == *rhs.m_typeAlias;
        }

        std::size_t hashCode() const
        {
            return m_typeAlias->hashCode();
        }

        const ITypeAlias& typeAlias() const
        {
            return *m_typeAlias;
        }

    private:
        std::shared_ptr< ITypeAlias > m_typeAlias;
    };


    template <class T>
    inline TypeAliasKey createKeyForType()
    {
        return createKeyForType(Utils::getMetaTypeInfo< T >());
    }

    inline TypeAliasKey createKeyForType(const TypeInfo& typeInfo)
    {
        return TypeAliasKey(std::make_shared< TypeAlias >(typeInfo));
    }

} // namespace Hypodermic


namespace std
{

    template <>
    struct hash< Hypodermic::TypeAliasKey > : public unary_function< Hypodermic::TypeAliasKey, size_t >
    {
        size_t operator()(const Hypodermic::TypeAliasKey& key) const
        {
            return key.hashCode();
        }
    };

} // namespace std