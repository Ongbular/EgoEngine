#pragma once

enum class EStructFieldFlag : uint16
{
	Static = 1,
	NonStatic = 2,
	Ctor = 4,
	Dtor = 8,
	Property = 16,
	Function = 32,
	NestedType = 64,
	Base = 128,
	Derived = 256
};

class StructMeta
{
};
