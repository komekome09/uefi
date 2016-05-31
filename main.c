#include "main.h"

#define STRLEN 20

EFI_STATUS
EFIAPI
EfiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
	EFI_STATUS status = EFI_SUCCESS;

	CHAR16 num[20];
	CHAR16 option[STRLEN] = {0x0000}, num_count[STRLEN] = {0x0000};
	UINTN column = 0, row = 0;
	int a = 8, start = 8, count = 10;
	int wait = 80000;
	BOOLEAN isGirl = FALSE, isShape = FALSE, isWave = FALSE;

	SystemTable->ConOut->QueryMode(SystemTable->ConOut, (UINTN)0, &column, &row);
	SystemTable->ConOut->EnableCursor(SystemTable->ConOut, TRUE);
	SystemTable->ConOut->Reset(SystemTable->ConOut, FALSE);

	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"option: ");
	tmp_input(SystemTable->ConIn, SystemTable->ConOut, SystemTable->BootService, STRLEN, option);

	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\ninput: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, option);

	for(int i = 0; option[i] != 0x0000; i++){
		switch(option[i]){
			case 'c': 
				SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x05);
				break;
			case 'f': wait = 40000; break;
			case 'g': isGirl = TRUE; break;
			case 'h': show_help(); break;
			case 'n':
				SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\ncount: ");
				tmp_input(SystemTable->ConIn, SystemTable->ConOut, SystemTable->BootService, STRLEN, num_count);
				count = ch16_to_int(num_count);
				SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\ninput: ");
				SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(count, num));
				break;
			case 's': isShape = TRUE; break;
			case 'w': isWave = TRUE; break;
		}
	}

	CHAR16 nipple[4][11] = {L"| o   o |",
							L"( o   o )",
							L"| *   * |",
							L"( *   * )"};

	while(a < column){
		int disp_flag[80] = {0};
		SystemTable->ConOut->SetCursorPosition(SystemTable->ConOut, 0, 10);
		SystemTable->ConOut->OutputString(SystemTable->ConOut, nipple[0+isGirl+2*isShape]);

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
				if(isWave) disp[i] = '~';
				else disp[i] = 0x002d;// -;
			}else{
				switch(i){
					case 2:
					case 6:
						if(isShape) disp[i] = 0x002A; // *
						else disp[i] = 0x006f; // o
						break;
					case 0:
						if(isGirl) disp[i] = 0x0028; // (
						else disp[i] = 0x007c; // |
						break;
					case 8:
						if(isGirl) disp[i] = 0x0029; // (
						else disp[i] = 0x007c; // |
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
		for(int i = 0; i < wait; i++);
	}
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(column, num));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, num_to_ucs2(row, num));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

	tmp_input(SystemTable->ConIn, SystemTable->ConOut, SystemTable->BootService, 0, NULL);
    return status;
}
