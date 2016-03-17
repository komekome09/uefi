#define EFI_TEXT_ATTR(ForeGround, BackGround) ((ForeGround) | ((BackGround) << 4))

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_RESET) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN BOOLEAN								   ExtendedVerification
	);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_STRING) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN CHAR16                                   *String
    );

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_QUERY_MODE) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN						   ModeNumber,
	OUT UINTN						   *Columns,
	OUT UINTN						   *Rows
	);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_ATTRIBUTE) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This,
	IN UINTN									Attribute
	);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_CLEAR_SCREEN) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This
	);

typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION) (
	IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
	IN UINTN								   Column,
	IN UINTN								   Row
	);

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	EFI_TEXT_RESET 					Reset;
    EFI_TEXT_STRING  				OutputString;
	void							*a;
	EFI_TEXT_QUERY_MODE 			QueryMode;
	void							*b;
	EFI_TEXT_SET_ATTRIBUTE			SetAttribute;
	EFI_TEXT_CLEAR_SCREEN			ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION	SetCursorPosition;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
