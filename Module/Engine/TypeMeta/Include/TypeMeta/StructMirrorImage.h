#pragma once

#include "TypeMeta/TypeMeta.h"
#include "TypeMeta/TypeMetaDictionary.h"

/*
 * 일단 미러이미지를 만들지 말지 고민하자.
 */
template <typename T>
class StructMirrorImage
{
	friend TypeMeta;
	explicit StructMirrorImage(T& obj);

public:
	// 이건 컨셉으로 만들어보자. propertyName이 문자열 컨셉이 되도록
	// 반환값 std::optional을 사용하자.
	template <typename TProp>
	TProp& GetProperty(const char* propertyName) const;

	template <typename TFn>
	TFn& GetFunction(const char* funcName) const;

private:
	T& mObject;
	const TypeMeta& mTypeMeta;
};

template <typename T>
StructMirrorImage<T>::StructMirrorImage(T& obj)
	: mObject(obj)
	, mTypeMeta()
{
}
