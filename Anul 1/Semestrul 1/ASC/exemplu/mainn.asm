bits 32

global start

extern exit, printf, fopen, fscanf, fclose
import exit msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    act_num dd 0                    ; numarul de intregi cititi
    max_num equ 100                 ; numarul maxim de intregi
    sir_numere times max_num db 0   ; sirul de numere intregi
    
    descr_fis dd -1                 ; descriptorul fisierului
    mod_acces db "r", 0             ; modul de acces la fisier
    nume_fisier db "input.txt", 0   ; numele fisierului
    
    n dd 0                          ; numarul intreg citit din fisier
    format db '%d', 0               ; formatul de citire din fisier
    
    mesaj db 'Sirul de numere intregi citit este:', 0
    format_afisare db ' %d', 0      ; formatul de afisare la consola
    
; Citirea unui sir de numere intregi cu semn dintr-un fisier de tip text folosind functia fscanf().
segment code use32 class=code
    start:
        ; apelam functia fopen() pentru a deschide fisierul
        ; functia va returna in EAX descriptorul fisierului sau 0 in caz de eroare
        ; eax = fopen(nume_fisier, mod_acces)
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2

        ; verificam daca functia fopen a deschis cu succes fisierul (EAX != 0)
        cmp eax, 0
        je final                    ; daca a aparut o eroare (EAX = 0), terminam executia programului
        
        ; stocam descriptorul de fisier (valoarea returnata de functia fopen())
        mov [descr_fis], eax
        
        ; citim numerele intregi din fisier unul cate unul
        mov ecx, max_num            ; citim maximum 100 de numere intregi
        ;jecxz final
        cld
        mov ebx, 0                  ; in EBX vom contoriza numarul actual de intregi cititi din fisier
        mov edi, sir_numere
    citire:
        ; apelam functia fscanf() pentru a citi din fisier
        ; functia va returna in EAX valoarea 1 (daca a citit cu succes un numar intreg) sau 0 in caz de eroare
        ; eax = fscanf(descr_fis, format, n)
        push dword n                ; adresa la care stocam numarul intreg citit
        push dword format           ; formatul de citire
        push dword [descr_fis]      ; descriptorul fisierului
        call [fscanf]
        add esp, 4*3
        
        cmp eax, 1                  ; verificam daca citirea a avut loc cu succes (EAX = 1)
        jne stop                    ; in caz contrar (EAX != 1), incheiem citirea
        
        ; stocam numarul citit in sirul de numere
        mov eax, [n]
        stosd
        inc ebx                     ; am mai citit un numar intreg
        loop citire
        
    stop:
        ; stocam numarul actual de intregi cititi din fisier
        mov [act_num], ebx
        
        ; apelam functia fclose() pentru a inchide fisierul
        ; fclose(descr_fis)
        push dword [descr_fis]
        call [fclose]
        add esp, 4*1
        
        ; afisam mesajul 'Sirul de numere ...'
        push dword mesaj
        call [printf]
        add esp, 4*1
    
        ; afisam numerele intregi din sir unul cate unul
        mov ecx, [act_num]  ; numarul actual de intregi care au fost cititi
        jecxz final
        cld
        mov esi, sir_numere
    afisare:
        push ecx
        
        lodsd
        push eax
        push dword format_afisare
        call [printf]
        add esp, 4*2
        
        pop ecx
        loop afisare
        
    final:                  ; incheiem executia programului
        ; exit(0)
        push dword 0        ; push the parameter for exit onto the stack
        call [exit]         ; call exit to terminate the program