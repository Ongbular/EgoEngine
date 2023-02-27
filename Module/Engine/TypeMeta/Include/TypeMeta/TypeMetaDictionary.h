#pragma once
#include "TypeMeta.h"

class TypeMetaDictionary
{
	TypeMetaDictionary();

	template <typename T>
	friend class TypeMetaGenerator;

public:
	static TypeMetaDictionary* Get();

	template <typename T>
	const TypeMeta& GetTypeMeta() const;
	const TypeMeta& GetTypeMeta(auto obj) const;

private:
	TypeId getTypeId(const char* typeName) const;

	std::unordered_map<std::string, TypeId> mTypeIdMap;
	std::vector<std::unique_ptr<TypeMeta>> mTypeMetas;

#define TYPE_ID(typeName) (getTypeId(#typeName))
};

template <typename T>
const TypeMeta& TypeMetaDictionary::GetTypeMeta() const
{
	const auto& typeMetaPtr = mTypeMetas[TYPE_ID(T)];
	return *typeMetaPtr;
}

const TypeMeta& TypeMetaDictionary::GetTypeMeta(auto obj) const
{
	return GetTypeMeta<decltype(obj)>();
}

