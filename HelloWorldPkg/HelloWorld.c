#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Uefi.h>

EFI_STATUS
EFIAPI
UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    Print(L"Hello, Brand New World\n");
    return 0;
}