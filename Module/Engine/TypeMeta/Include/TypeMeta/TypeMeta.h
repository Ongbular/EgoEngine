#pragma once

using TypeId = uint32;

class TypeMeta
{
public:
	std::string_view GetName() const { return mName; }
	uint32 GetSize() const { return mSize; }

private:
	TypeId mId{ 0 };
	std::string mName{};
	uint32 mSize{ 0 };

public:
	TypeMeta(const TypeMeta&) = delete;
	TypeMeta(TypeMeta&&) = delete;
	virtual ~TypeMeta() = default;

	TypeMeta& operator=(const TypeMeta&) = delete;
	TypeMeta& operator=(TypeMeta&&) = delete;

	bool operator==(const TypeMeta& other) const { return mId == other.mId; }
	bool operator!=(const TypeMeta& other) const { return mId != other.mId; }
	
private:
	template <typename T>
	friend class TypeMetaGenerator;

	TypeMeta() = default;
};

#define META_NON_PUBLIC() // friend랑 태그를 만들어야겠다.
