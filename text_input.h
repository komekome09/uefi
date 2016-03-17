typedef struct {
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY) (
	IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL 	*This,
	OUT EFI_INPUT_KEY							*Key
	);

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	void							*a;
	EFI_INPUT_READ_KEY				ReadKeyStroke;
	void							*b;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
