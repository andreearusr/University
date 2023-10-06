bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,scanf,fopen,fclose,fprintf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    cititor dd 0
    n db 0
    s dw 0
    numar dw 0
    format db "%d",0
    format_afi db "%d ",0
    
    nume_fisier db "out.txt", 0  
    mod_acces db "w", 0                                     
    descriptor dd 0
    
    contor dd 0
   
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2 ; deschidem fisierul in modul "w"
        
        mov [descriptor],eax
        cmp eax,0
        je final ; verificam daca fisierul a fost deschis corect
        
        push dword cititor
        push dword format
        call [scanf]
        add esp,4*2 ; citim valoare pentru n, folosim cititor pt ca functia scanf va citi un 
                    ; dword indiferent de tipul de data a lui n si ar suprapune peste alte adrese
        
        mov eax,[cititor]
        mov byte [n],al ; mutam in n al, octetul inferior din cititor
        
        mov ecx,0
        mov cl,[n] ; initializam ecx cu 0 si punem in cl valoarea octetului n
        
        citire:
            pushad
                push dword cititor
                push dword format
                call [scanf]
                add esp,4*2
            popad
            mov eax,[cititor]
            add word [s],ax ; folosim cititor din acelasi motiv ca mai sus
        
        loop citire
        
        mov ecx,0
        mov cx,[s] ; punem in ecx valoarea din s
        mov word [numar],0 ; initializam numar cu 0
        afisare:
            pushad
            mov eax,0
            mov ax,[numar] ; transformam word-ul numar in dword pt a putea fi afisat
            push eax
            push dword format_afi
            push dword [descriptor]
            call [fprintf]
            add esp,4*3
            
            popad
            add word [numar],1 ; incrementare
        loop afisare
            
        

        push dword [descriptor]
        call [fclose]
        add esp, 4        
        final:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program




