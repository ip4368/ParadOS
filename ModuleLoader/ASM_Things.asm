Global REST
Global BRAIN_WASHING
;Global SWITCH_TO_LONG_MODE

REST:
	hlt
	jmp REST

BRAIN_WASHING:
	call DISABLE_PAGING
	

;SWITCH_TO_LONG_MODE:
;	call DISABLE_PAGING ;it might have paging already


DISABLE_PAGING:
	mov eax, cr0
	and eax, ~(1 << 31)
	mov cr0, eax
	ret
ENABLE_PAGING:
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax
	ret