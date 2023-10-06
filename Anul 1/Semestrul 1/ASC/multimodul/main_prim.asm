bits 32
global start

extern exit,scanf,printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

extern prim


segment data use32 class=data public
    x dd 0
    nr_de_numere_prime dd 0
    
    decimal db "%d",0
    mesaj_afisare db "Numarul de numere prime din sir este: %d",0
    

segment code use 32 class=code public
    start:
        mov ebx,2
        
        citeste_x:
            push dword x
            push dword decimal
            call [scanf]
            add ESP,4*2
            
            cmp dword[x],0
            je sfarsit_citeste_x
            
            push dword [x]
            call prim
            pop ecx
            add esp,4*1
            
            cmp ecx,0
        je citeste_x
            
        inc dword[nr_de_numere_prime]
        jmp citeste_x
        
        sfarsit_citeste_x:
            push dword [nr_de_numere_prime]
            push dword mesaj_afisare
            call [printf]
            add ESP,4*2
            
        push dword 0
        call [exit]
            
   