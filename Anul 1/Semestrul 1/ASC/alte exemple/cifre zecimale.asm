bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,fopen,fclose,fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        nume_fisier db "fisier1.txt",0
        mod_acces db "w",0
        format db "%d",10,0
        nr dw 5463
        descriptor_fis dd -1

; our code starts here
segment code use32 class=code
    start:
        ; Se da numele unui fisier si un numar pe cuvant scris in memorie. Se considera numarul in repr fara semn.
        ;Sa se scrie cifrele zecimale ale acestui nr ca text in fisier,fiecare cifra pe o linie separata
        
        push dword mod_acces
        push dword nume_fisier
        call[fopen]
        add ESP, 4*2
        
        mov [descriptor_fis],EAX
        
        cmp EAX,0
        je final
        
        mov DX,0
        mov AX, word[nr]
        
        bucla:
            mov BX,10
            div BX
            
            PUSHAD
            
            push EDX
            push dword format
            push dword [descriptor_fis]
            call [fprintf]
            add ESP, 4*3
            
            POPAD
            
            mov DX,0
            cmp AX,0
            jnz bucla
            
        push dword [descriptor_fis]
        call [fclose]
        add ESP, 4*1
        
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
