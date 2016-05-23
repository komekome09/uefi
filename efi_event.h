// Event tyes
#define EVT_TIMER							0x80000000
#define EVT_RUNTIME							0x40000000
#define EVT_NOTIFY_WAIT						0x00001000
#define EVT_NOTIFY_SIGNAL					0x00002000
#define EVT_SIGNAL_EXIT_BOOT_SERVICES		0x00002010
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE	0x60002020

//EFI_TPL
typedef UINTN								EFI_TPL;

// Task Priority Level

#define TPL_APPLICATION						4
#define TPL_CALLBACK          				8
#define TPL_NOTIFY            				16
#define TPL_HIGH_LEVEL        				31

typedef enum{
	TimerCancel,
	TimerPeriodic,
	TimerRelative,
	TimerTypeMax
} EFI_TIMER_DELAY;

typedef
void
(EFIAPI *EFI_EVENT_NOTIFY) (
	IN EFI_EVENT	Event,
	IN void			*Context
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CREATE_EVENT) (
	IN UINT32				Type,
	IN EFI_TPL				NotifyTpl,
	IN EFI_EVENT_NOTIFY		NotifyFunction, OPTIONAL
	IN void					*NotifyContext, OPTIONAL
	OUT EFI_EVENT			*Event
	);

typedef
EFI_STATUS
(EFIAPI *EFI_CLOSE_EVENT) (
	IN EFI_EVENT	Event
	);

typedef
EFI_STATUS
(EFIAPI *EFI_WAIT_FOR_EVENT) (
	IN UINTN		NumberOfEvents,
	IN EFI_EVENT	*Event,
	OUT UINTN		*Index
	);

typedef
EFI_STATUS
(EFIAPI *EFI_SET_TIMER) (
	IN EFI_EVENT			Event,
	IN EFI_TIMER_DELAY		Type,
	IN UINT64				TriggerTime
	);

typedef struct {
	char					a[24];
	void					*b;
	void					*c;
	void					*d;
	void					*e;
	void					*f;
	void					*g;
	void					*h;
	EFI_CREATE_EVENT		CreateEvent;
	EFI_SET_TIMER			SetTimer;
	EFI_WAIT_FOR_EVENT		WaitForEvent;
	void					*i;
	EFI_CLOSE_EVENT			CloseEvent;
}EFI_BOOT_SERVICES;
