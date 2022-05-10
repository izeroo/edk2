#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>

EFI_STATUS
EFIAPI
UefiMain(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable)
{
    UINTN NoHandles = 0;
    UINTN SizeOfInfo = 0;
    EFI_HANDLE *Buffer = NULL;
    EFI_STATUS Status = 0;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *Gop;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL RedPixel = {0, 0, 255, 0};
    // EFI_GRAPHICS_OUTPUT_BLT_PIXEL GreenPixel = {0, 255, 0, 0};
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL BluePixel = {255, 0, 0, 0};
    // EFI_GRAPHICS_OUTPUT_BLT_PIXEL WhitePixel = {255, 255, 255, 0};
    Status = gBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiGraphicsOutputProtocolGuid,
        NULL,
        &NoHandles,
        &Buffer);
    Print(L"Status = %d\n", Status);
    if (EFI_ERROR(Status))
    {
        Print(L"Failed to Locate Handle Buffer\n");
        return Status;
    }
    else
    {
        Print(L"Hello, Protocol!\n");
    }
    Print(L"NoHandles = %d\n", NoHandles);

    Status = gBS->OpenProtocol(
        Buffer[0],
        &gEfiGraphicsOutputProtocolGuid,
        (void **)&Gop,
        ImageHandle,
        NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    Print(L"Status = %d\n", Status);
    if (EFI_ERROR(Status))
    {
        Print(L"Failed to Open Protocol\n");
        return Status;
    }
    else
    {
        Print(L"Hello, Open Protocol!\n");
    }

    for (UINTN i = 0; i < Gop->Mode->MaxMode; i++)
    {
        Status = Gop->QueryMode(
            Gop,
            i,
            &SizeOfInfo,
            &Info);
        if (EFI_ERROR(Status))
        {
            Print(L"Failed to QueryMode.\n");
            return Status;
        }
        Print(L"Mode %d, H = %d, V = %d.\n",
              i,
              Info->HorizontalResolution,
              Info->VerticalResolution);
    }

    UINTN PixelPerScanLine = Gop->Mode->Info->PixelsPerScanLine;
    Gop->Blt(
        Gop,
        &RedPixel,
        EfiBltVideoFill,
        0, 0,
        0, 0,
        PixelPerScanLine * 8 / 10, 100,
        0);

    Gop->Blt(
        Gop,
        &BluePixel,
        EfiBltVideoFill,
        0, 100,
        0, 100,
        PixelPerScanLine * 7 / 10, 100,
        0);

    Gop->Blt(
        Gop,
        &RedPixel,
        EfiBltVideoFill,
        0, 200,
        0, 200,
        PixelPerScanLine * 6 / 10, 100,
        0);
    Gop->Blt(
        Gop,
        &BluePixel,
        EfiBltVideoFill,
        0, 300,
        0, 300,
        PixelPerScanLine * 1, 100,
        0);
    Gop->Blt(
        Gop,
        &RedPixel,
        EfiBltVideoFill,
        0, 400,
        0, 400,
        PixelPerScanLine * 4 / 10, 100,
        0);
    if (EFI_ERROR(Status))
    {
        Print(L"Failed to Blt.\n");
        return Status;
    };

    // EFI_PHYSICAL_ADDRESS GreenStart = Gop->Mode->FrameBufferBase
    //                                 + Gop->Mode->Info->PixelsPerScanLine * 100 * 4;
    // EFI_GRAPHICS_OUTPUT_BLT_PIXEL *VideoHandle = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)GreenStart;
    // UINTN NoPixels = Gop->Mode->Info->PixelsPerScanLine * 100;

    // for(UINTN i = 0; i < NoPixels; i++) {
    //     *VideoHandle = GreenPixel;
    //     VideoHandle++;
    // }
    // for(UINTN i = 0; i < NoPixels; i++) {
    //     *VideoHandle = BluePixel;
    //     VideoHandle++;
    // }
    // for(UINTN i = 0; i < NoPixels; i++) {
    //     *VideoHandle = RedPixel;
    //     VideoHandle++;
    // }
    // for(UINTN i = 0; i < NoPixels; i++) {
    //     *VideoHandle = WhitePixel;
    //     VideoHandle++;
    // }

    return 0;
}