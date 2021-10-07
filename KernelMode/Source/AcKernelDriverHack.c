#pragma warning (disable : 4100 4047 4024)

#include "Header\AcKernelDriverHack.h"
#include "Header\msg.h"
#include "Header\events.h"
#include "Header\data.h"
#include "Header\communication.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);
	pDriverObject->DriverUnload = UnloadDriver;

	PsSetLoadImageNotifyRoutine(ImageLoadCallback);

	RtlInitUnicodeString(&dev, L"\\Device\\AcAimbot");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\AcAimbot");

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;

	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	UNREFERENCED_PARAMETER(pDriverObject);

	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);

	DebugMessage("Bye !\n");
	return STATUS_SUCCESS;
}
