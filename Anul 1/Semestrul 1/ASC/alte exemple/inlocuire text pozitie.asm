bits 32 ; assembling for the 32 bits architecture
global start        


extern exit,fopen,fclose,fprintf               
import exit msvcrt.dll   
import fopen msvcrt.dll
import fclose msvcrt.dll   
import fprintf msvcrt.dll      


segment data use32 class=data
    ; Se dau un nume de fisier si un text. Textul contine litere mici si spatii. Sa se inlocuiasca toate literele de pe
    ;pozitiile pare cu numarul pozitiei. Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut in fisier
    
        zece dw 10
        nume_fisier db "date.txt",0
        mod_acces db "w",0
        descriptor_fis dd -1
        text db "Ana merge la magazin",0
        l equ $-text-1
        text_prelucrat times 256 db 0


segment code use32 class=code
    start:
        
        push dword mod_acces
        push dword nume_fisier
        call[fopen]
        add ESP,4*2
        
        cmp EAX,0
        je final
        mov [descriptor_fis],EAX 
        
        mov ESI,text
        mov EDI, text_prelucrat
        mov ECX,l 
        cld 
        jecxz final 
        
        repeta:
            lodsb
            cmp AL, ' '
            je caz2 
            mov EBX,ESI
            sub EBX,text
            test EBX,l
            jnz caz2 
            caz1:
                push ECX
                mov ECX,0
                repeta2:
                    inc ECX 
                    push EBX 
                    pop AX 
                    pop DX 
                    div word[zece]
                    mov EBX,0
                    mov BX,AX
                    add DX,'0'
                    mov AL,DL
                    push EAX 
                    cmp EBX,0
                jnz repeta2
                repeta3:
                    pop EAX
                    stosb 
                loop repeta3
                pop ECX 
            jmp sf     
            caz2:
                stosb
            sf:
        loop repeta 
        
        push dword text_prelucrat
        push dword [descriptor_fis]
        call [fprintf]
        add ESP,4*2 
        
        push dword [descriptor_fis]
        call[fclose]
        add ESP,4*1
        
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
