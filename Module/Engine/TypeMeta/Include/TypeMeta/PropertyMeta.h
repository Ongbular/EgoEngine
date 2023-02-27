#pragma once

#include "TypeMeta/FieldMeta.h"
#include "TypeMeta/TypeMeta.h"

class PropertyMeta : public FieldMeta
{

private:
	TypeMeta::Id mTypeId{ 0 };

};

