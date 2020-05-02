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
    mov ebp, esp
	push edi;register die flüchtig sind und gesichert werden müssen,
	push esi
	push ebx

;in ebp+8 from
;in ebp+12 to


	mov	eax, [ebp+8]
	mov [eax], esp
	mov eax, [ebp+12]
	mov esp,[eax]




	pop ebx
	pop esi
	pop edi
	pop ebp

	ret		; Ruecksprung zum Aufrufer

