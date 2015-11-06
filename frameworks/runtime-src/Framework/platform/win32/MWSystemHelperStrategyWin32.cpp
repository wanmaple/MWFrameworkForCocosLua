#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

#include "MWSystemHelperStrategyWin32.h"

#include <windows.h>
#include <psapi.h>
#include <WinInet.h>

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "WinInet.lib")

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

void MWSystemHelperStrategyWin32::copyToPasteBoard(const std::string &content)
{
	HWND hWnd = nullptr;
	// open clip board
	if (!::OpenClipboard(hWnd))
	{
		return;
	}
	// empty the clipboard
	if (!::EmptyClipboard())
	{
		::CloseClipboard();
		return;
	}
	int len = content.size();

	// allocation
	HANDLE hClip = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, (len + 1) * sizeof(char));
	if (!hClip)
	{
		::CloseClipboard();
		return;
	}
	// locks a global memory object and returns a pointer to the first byte of the object's memory block
	char *buf = (char *)::GlobalLock(hClip);
	if (!buf)
	{
		::GlobalFree(hClip);
		::CloseClipboard();
		return;
	}

	::memcpy(buf, content.c_str(), len * sizeof(char));
	buf[len] = 0;

	::GlobalUnlock(hClip);

	if (!::SetClipboardData(CF_TEXT, hClip))
	{
		::GlobalFree(hClip);
		::CloseClipboard();
		return;
	}

	::CloseClipboard();
}

double MWSystemHelperStrategyWin32::getCurrentUsedMemory()
{
	HANDLE handle = ::GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	::GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	return (double)pmc.WorkingSetSize / 1024 / 1024;
}

ENetStatus MWSystemHelperStrategyWin32::checkNetStatus()
{
	if (::InternetCheckConnectionA("http://www.baidu.com", FLAG_ICC_FORCE_CONNECTION, 0))
	{
		return ENetStatus::WIFI;
	}
	return ENetStatus::NO_NETWORK;
}

MW_FRAMEWORK_END

#endif