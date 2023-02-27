#pragma once

class FieldMeta
{
public:
	std::string_view GetName() const { return mName; }
	
private:
	std::string mName{};
};
