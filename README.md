# Ac-Kernel-Driver-Aimbot
Aimbot for assaultcube using a kernel driver and IOCTL communication.

This project demonstrates a way to access a process virtual memory using a driver and IOCTL communication method.
The driver itself has 3 different control codes : Get Process ID, ReadMemory and WriteMemory.

Instead of using the windows functions like ReadProcessMemory, we use the driver control code through its handle to get these values from it.

In a case where the game uses a kernel anti-cheat, this would still suck because : 

AC's Drivers can detect handle & thread creations through kernel, to hide them we could unregister the AC's callback.
Anti cheats also use KTHREAD ThreadListEntry, PspCidTable, KPROCESS and EPROCESS structures.

Using IOCTL also doesn't bypass 99% of anticheats (if we assume the driver is unsigned and manually mapped into kernel using vulnerable driver's IOCTL like iqvw64e.sys (kdmapper) or capcom.sys)
