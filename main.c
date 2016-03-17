#include "main.h"

EFI_STATUS
EFIAPI
EfiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
	EFI_STATUS status;
	EFI_INPUT_KEY key;

	CHAR16 num[20];
	UINTN column = 0, row = 0;
	int a = 8, start = 8, count = 10;

	SystemTable->ConOut->QueryMode(SystemTable->ConOut, (UINTN)0, &column, &row);
	SystemTable->ConOut->ClearScreen(SystemTable->ConOut);

	while(a < column){
		int disp_flag[80] = {0};
		SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 0);
		SystemTable->ConOut->OutputString(SystemTable->ConOut, L"| o   o |");

		int b = a;
		while(count-- && b > start - 1){
			if(b == start){
				disp_flag[b-1] = 1; disp_flag[b-5] = 1;
			}else if(b == start + 1){
				disp_flag[b-1] = disp_flag[b-2] = 1;
				disp_flag[b-5] = disp_flag[b-6] = 1;
			}else{
				disp_flag[b-1] = disp_flag[b-2] = disp_flag[b-3] = 1;
				disp_flag[b-5] = disp_flag[b-6] = disp_flag[b-7] = 1;
			}

			b -= 15;
		}

		for(int i = 0; i < a && i < (int)column; i++){
			SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, (UINTN)i, 0);
			if(disp_flag[i]){
				SystemTable->ConOut->OutputString(SystemTable->ConOut, L"-");
			}else{
				switch(i){
					case 2:
					case 6:
						SystemTable->ConOut->OutputString(SystemTable->ConOut, L"o");
						break;
					case 0:
					case 8:
						SystemTable->ConOut->OutputString(SystemTable->ConOut, L"|");
						break;
					default:
						SystemTable->ConOut->OutputString(SystemTable->ConOut, L" ");
						break;
				}
			}
		}
		a++;
	}
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(column, num));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(row, num));

    while((status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key)) == EFI_NOT_READY);
    return status;
}
