global ENTRY_HERE
extern main
;ah! assembly again cant avoid it.
jmp ENTRY_HERE

ENTRY_HERE: 
	call GATE
	call main
	ret;never go here
	jmp $

GATE: 
	
	;check is in protect mode. if not u fuck up.
	mov eax, cr0
	test eax, 1 
	jz OH_MY_FUCKING_GOD__ARE_U_SERIOUS 
	;if in PMode
	;everything is fine, c language still work i think.
	ret

OH_MY_FUCKING_GOD__ARE_U_SERIOUS: 
	;i can do nothing
	call REST
