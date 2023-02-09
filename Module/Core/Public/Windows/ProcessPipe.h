#pragma once

#include "Core/CoreDLL.h"

class CORE_API ProcessPipe
{
public:
	NON_COPYABLE(ProcessPipe)

	explicit ProcessPipe(bool bSender, bool bInherit = true);
	~ProcessPipe();

	HANDLE GetReadHandle() const { return mReadHandle; }
	HANDLE GetWriteHandle() const { return mWriteHandle; }
	bool IsSender() const { return mbSender; }
	bool IsInherit() const { return mbInherit; }

private:
	bool mbSender;
	bool mbInherit;
	HANDLE mReadHandle{ nullptr };
	HANDLE mWriteHandle{ nullptr };
};
