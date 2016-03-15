#include "main.h"

EFI_STATUS
EFIAPI
EfiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
	CHAR16 *hoge[4] = {L"-", L"\\", L"|", L"/"}, test[2] = {0x0030, 0x0000};
	CHAR16 num[20];
	UINTN column = 0, row = 0;

	SystemTable->ConOut->QueryMode(SystemTable->ConOut, (UINTN)0, &column, &row);

	SystemTable->ConOut->ClearScreen(SystemTable->ConOut);

	for(int i = 0; i < 10000; i++){
    	SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 0);
    	SystemTable->ConOut->OutputString(SystemTable->ConOut, hoge[i%4]);
		//test[0] = test[0]++;
	}
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(column, num));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(row, num));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\nHello World!\n");
    while(1);
    return EFI_SUCCESS;
}
