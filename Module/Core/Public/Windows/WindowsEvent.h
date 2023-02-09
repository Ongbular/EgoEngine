#pragma once

#include "Core/CoreDLL.h"

class CORE_API WindowsEvent
{
public:
	NON_COPYABLE(WindowsEvent)

	explicit WindowsEvent(bool bInherit = true);
	~WindowsEvent();

	void WaitForSignal();

	void Reset();

	std::wstring GetName() const { return mName; }
	HANDLE GetHandle() const { return mHandle; }
	bool IsSignaled() const { return mbSignaled; }
	
private:
	std::wstring mName{};
	HANDLE mHandle{ nullptr };
	bool mbSignaled{ false };
};

