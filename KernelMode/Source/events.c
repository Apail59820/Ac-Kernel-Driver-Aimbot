#pragma warning (disable : 4047 4311 4100)

#include "Header\events.h"
#include "Header\msg.h"
#include "Header\data.h"



PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PCUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	if (wcsstr(FullImageName->Buffer, L"\\AssaultCube\\bin_win32\\libvorbisfile.dll"))
		ProcessID = (ULONG)ProcessId;
	return STATUS_SUCCESS;
}