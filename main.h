#include <stdint.h>
#include <assert.h>

// data type
typedef uint8_t 						UINT8;
typedef UINT8							BOOLEAN;
typedef uint16_t 						CHAR16;
typedef	CHAR16							UINT16;
typedef uint32_t						UINT32;
typedef uint64_t						UINTN;
typedef UINTN 							EFI_STATUS;
typedef UINTN							UINT64;
typedef void 							*EFI_HANDLE;
typedef void							*EFI_EVENT;
typedef struct {
	UINT32								Data1;
	UINT16								Data2;
	UINT16								Data3;
	UINT8								Data4[8];
} EFI_GUID;

// boolean
#define TRUE							(BOOLEAN)1
#define FALSE 							(BOOLEAN)0

// EFI parameters
#define IN
#define OUT
#define EFIAPI
#define OPTIONAL

// return code
#define EFI_SUCCESS 					(EFI_STATUS)0
#define EFI_DEVICE_ERROR 				(EFI_STATUS)1
#define EFI_UNSUPPORTED 				(EFI_STATUS)2
#define EFI_NOT_READY					(EFI_STATUS)3
#define EFI_INVALID_PARAMETER			(EFI_STATUS)4
#define EFI_OUT_OF_RESOURCES			(EFI_STATUS)5

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

#include "text_output.h"
#include "text_input.h"
#include "efi_event.h"

typedef struct {
    char                             	a[36];
	EFI_HANDLE							ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL		*ConIn;
    EFI_HANDLE                       	ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  	*ConOut;
	char								b[24];
	EFI_BOOT_SERVICES					*BootService;
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
