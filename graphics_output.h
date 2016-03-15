typedef struct {
	UINT32		RedMask;
	UINT32		GreenMask;
	UINT32		BlueMask;
	UINT32		ReservedMask;
} EFI_PIXEL_BITMASK

typedef enum {
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT
	
typedef struct {
	UINT32									Version;
	UINT32									HorizontalResolution;
	UINT32									VerticalResolution;
	EFI_GRAPHICS_PIXEL_FORMAT				PixelFormat;
	EFI_PIXEL_BITMASK						PixelInformation;
	UINT32									PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
	UINT32									MaxMode;
	UINT32									Mode;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION	*Info;
	UINTN									SizeOfInfo;
	EFI_PHYSICAL_ADDRESS					FrameBufferBase;
	UINTN									FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
	EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE	SetMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT		Blt;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE		*Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;
