// data type
typedef unsigned short 					CHAR16;
typedef	CHAR16							UINT16;
typedef unsigned long long 				UINTN;
typedef UINTN 							EFI_STATUS;
typedef void 							*EFI_HANDLE;
typedef unsigned char 					BOOLEAN;

// boolean
#define TRUE							1
#define FALSE 							0

// EFI parameters
#define IN
#define OUT
#define EFIAPI

// return code
#define EFI_SUCCESS 					0
#define EFI_DEVICE_ERROR 				1
#define EFI_UNSUPPORTED 				2
#define EFI_NOT_READY					3

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

#include "text_output.h"
#include "text_input.h"

typedef struct {
    char                             	a[36];
	EFI_HANDLE							ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL		*ConIn;
    EFI_HANDLE                       	ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  	*ConOut;
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
