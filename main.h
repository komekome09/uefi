#define IN
#define OUT
#define EFIAPI

// return code
#define EFI_SUCCESS 0
#define EFI_DEVICE_ERROR 1
#define EFI_UNSUPPORTED 2

// boolean
#define TRUE 1
#define FALSE 0

typedef unsigned short CHAR16;
typedef unsigned long long UINTN;
typedef UINTN EFI_STATUS;
typedef void *EFI_HANDLE;
typedef unsigned char BOOLEAN;

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct _EFI_GRAPHICS_OUTPUT_PROTOCOL;

#include "text_output.h"
//#include "graphics_output.h"

typedef struct {
    char                             a[52];
    EFI_HANDLE                       ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;
} EFI_SYSTEM_TABLE;

CHAR16* num_to_ucs2(UINTN num, CHAR16 *res){
	UINTN digits[20];
	int i = 0, k = 0, j = 0;

	while(num != 0){
		digits[i] = num % 10;
		num /= 10;
		i++;
	}

	for(k = i - 1, j = 0; k >= 0; k--, j++){
		res[j] = 0x0030 + digits[k];
	}

	if(i == 0) res[j] = 0x0030;

	res[j+1] = 0x0000;

	return res;
}
