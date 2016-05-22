#include "main.h"

#define STRLEN 20

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
	CHAR16 option[STRLEN] = {0x0000};
	UINTN column = 0, row = 0;
	int a = 8, start = 8, count = 10;

	SystemTable->ConOut->QueryMode(SystemTable->ConOut, (UINTN)0, &column, &row);
	SystemTable->ConOut->EnableCursor(SystemTable->ConOut, TRUE);
	SystemTable->ConOut->Reset(SystemTable->ConOut, FALSE);

	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"option: ");
	SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
    
	int len = 0;
	UINTN Index;
	EFI_EVENT Event;
	while(1){
		status = SystemTable->BootService->WaitForEvent(1, &Event, &Index);
		ASSERT(!(status > 0));
		ASSERT(Index == 0);

		status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key);
		ASSERT(!(status > 0));

		if(key.UnicodeChar == '\r' || key.UnicodeChar == '\n'){
			break;
		}

		if(key.UnicodeChar >= ' '){
			if(len < STRLEN - 1){
				option[len] = key.UnicodeChar;
				SystemTable->ConOut->OutputString(SystemTable->ConOut, &option[len]);
				len++;
			}
			continue;
		}
	}
	/*
	while(1){
		status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key);

		if(status != EFI_NOT_READY){
			continue;
			if(i < 19){
				option[i] = key.UnicodeChar;
				i++;
				CHAR16 tmp[2] = {key.UnicodeChar, 0x0000};
				SystemTable->ConOut->OutputString(SystemTable->ConOut, tmp);
			}
		}else if(status > 0){
			SystemTable->ConOut->OutputString(SystemTable->ConOut, L"error.");
			break;
		}
		if(key.UnicodeChar == '\n' || key.UnicodeChar == '\r') break;
		SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(key.UnicodeChar, num));
	}
	*/
	//SystemTable->ConOut->OutputString(SystemTable->ConOut, option);

	while(a < column){
		int disp_flag[80] = {0};
		SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 10);
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

		CHAR16 disp[80] = {0x0000};
		for(int i = 0; i < a && i < (int)column; i++){
			if(disp_flag[i]){
				disp[i] = 0x002d;// -;
			}else{
				switch(i){
					case 2:
					case 6:
						disp[i] = 0x006f; // o
						break;
					case 0:
					case 8:
						disp[i] = 0x007c; // |
						break;
					default:
						disp[i] = 0x0020; //" "
						break;
				}
			}
		}

		SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 10);
		SystemTable->ConOut->OutputString(SystemTable->ConOut, disp);

		a++;
	}
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(column, num));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(row, num));

    SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE);
	while(1){
		status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key);

		if(status != EFI_NOT_READY && status > 0){
			SystemTable->ConOut->OutputString(SystemTable->ConOut, L"error.");
			break;
		}
		if(key.UnicodeChar == '\n' || key.UnicodeChar == '\r') break;
	}
    return status;
}
