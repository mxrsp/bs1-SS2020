;
;	to compile this code
;	first create an object file
;	nasm -f elf -o main.o main-nasm.asm
;
;	to create an executeable, link it
;	gcc -m32 -o run main.o
;
;	run it:
;	./run

global  getDivisorCount

[SECTION .text]

getDivisorCount:
	push	ebp
	mov	ebp, esp

;add code from here
   
   ; [ebp+8] = eax = Inputzahl
   ; [ebp+12] = Result
   ; ecx = Counter für Result
   ; ebx = Teilerzahl, durch die bei jeder Division geteilt wird
   
   mov ebx, 1               ; ebx wird 1 zugewiesen
   mov edx, 0               ; edx wird 0 zugewiesen
   mov ecx, 0               ; ecx wird 0 zugewiesen
   
   schleife:
   cmp ebx, eax             ; Vergleich Inputzahl mit TeilerZahl
   jg end                   ; wenn Teilerzahl größer als Inputzahl -> beenden
   div ebx                  ; eax(Inputzahl) / ebx 
   cmp edx, 0               
   je countup               ; wenn Rest der Division = 0 -> countup
   jne nocountup            ; ansonsten -> nocountup
   
   countup:
   inc ecx                  ; Counter wird um 1 erhöht
   mov eax, [ebp+8]         ; eax wird Inputzahl zugewiesen
   inc ebx                  ; TeilerZahl um 1 erhöht
   jmp schleife             ; schleife beginnt von vorne
   
   nocountup:
   inc ebx                  ; TeilerZahl um 1 erhöht
   mov edx, 0               ; Rest der Division wird 0 zugewiesen
   mov eax, [ebp+8]         ; eax wird Inputzahl zugewiesen
   jmp schleife             ; schleife beginnt von vorne
 
   end:
   mov ebx, 0               ; ebx wird 0 zugewiesen
   mov edx, 0               ; edx wird 0 zugewiesen
   mov edx, [ebp+12]        ; edx wird auf Result gesetzt
   mov [edx], ecx           ; Zeiger von edx wird Ergebnis zugewiesen
   mov ecx, 0
   
;to here
	mov eax, 0
	pop	ebp
	ret
