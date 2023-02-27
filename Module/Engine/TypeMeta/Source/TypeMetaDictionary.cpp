#include "PCH.h"
#include "TypeMeta/TypeMetaDictionary.h"

TypeMetaDictionary::TypeMetaDictionary()
{
	// TMT가 만든 json으로 전체 타입 갯수를 파악해서
	// map과 vector를 초기화.

	// 등록은 unique_ptr로 TypeMeta를 만들어서 Dictionary에 move로 넘겨주면 됨.
	// 포인터를 넘겨준 다음에 맵도 갱신해주면 되고.
}

TypeMetaDictionary* TypeMetaDictionary::Get()
{
	static TypeMetaDictionary instance;
	return &instance;
}

TypeId TypeMetaDictionary::getTypeId(const char* typeName) const
{
	assert(mTypeIdMap.contains(typeName));
	return mTypeIdMap.at(typeName);
}
