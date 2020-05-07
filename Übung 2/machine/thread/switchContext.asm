%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym switchContext

[GLOBAL switchContext]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; switchContext: Der Coroutinenwechsel
;
; C-Prototyp:
;
;     void switchContext (void*& from, void*& to);
;

switchContext:
;	fuegt hier Euren Code ein!
	push ebp
	mov esp, ebp
		
	push edi
	push esi
	push ebx
	
	mov eax, [ebp + 8]
	mov [eax], esp
	mov eax, [ebp + 12]
	mov esp, [eax] 
	
	pop ebx
	pop esi
	pop edi

;Ende
	ret		; Ruecksprung zum Aufrufer

