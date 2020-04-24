;
;	to compile this code
;	first create an object file
;	nasm -g -f elf -o main.o main-nasm.asm
;
;	to create an executeable, link it
;	gcc -m32 -o run main.o
;
;	run it:
;	./run

global getDivisorCount

getDivisorCount:

	push	ebp
	mov	ebp, esp

;add code from here

[SECTION .text]

                    ; eax = InputZahl
                    ; ebx = Counter für Anzahl der Teiler

                    mov edx, 0              ; Wert, der div-Ergebnis speichert
    
                    mov ebx, 0              ; Zähler, für die Anzahl der Teiler
    
                    mov ecx, eax            ; ecx wird Wert von InputZahl zugewiesen
    
    modulo:         mov eax, [esp+8]        ; eax wird auf Ausgangswert gesetzt
                    div ecx                 ; InputZahl / ecx
                    cmp edx, 0              
                    je erhoeheTeiler        ; wenn Rest der Division = 0, dann gehe zu schleife2 
                    cmp ecx, 0              
                    je end                  ; wenn die teilende Zahl 0 ist, Programm beenden
                    mov edx, 0              ; Ergebnis der Division zurücksetzen
                    loop modulo             ; zurückspringen auf schleife
                
    erhoeheTeiler:  inc ebx                 ; Erhöhung der Anzahl der Teiler um 1
                    dec ecx                 ; Dekrementierung der Zahl, durch die geteilt wird
                    cmp ecx, 0              
                    je end                  ; wenn diese Zahl gleich 0 wird, Programm beenden
                    mov edx, 0              ; Wert der Division wird geresettet
                    jmp modulo              ; ansonsten zurück zum Schleifenanfang
    end:        
                
;to here
	mov eax, ebx
	pop	ebp
	ret
