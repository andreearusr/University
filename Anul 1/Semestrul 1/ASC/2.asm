bits 32
global start
extern exit,printf               
import exit msvcrt.dll 
import printf msvcrt.dll    

segment data use32 class=data
   sir db 1Ah,1,8,2,4,10h,0F4h,20h,9
   len equ $-sir
   sir2 times len db 0
   max dw 0 
   ratie dw 1
   ratie_buna resw 1
   nr dw 0
   t db 0
   mem dw 0
   
   format db "%x ",0   

segment code use32 class=code
    start:
        mov bl,0
        sortare:
              mov esi,sir
              cmp bl,1
              je final
              mov bl,1
              mov ecx,len
              dec ecx
              sort:
                   mov edi,esi
                   lodsb
                   mov dl,al
                   lodsb
                   cmp al,dl
                   ja peste
                   stosb
                   mov al,dl
                   stosb
                   mov bl,0
                   peste:
                   dec esi
                   loop sort
              jmp sortare
        final:
        ;am sirul ordonat crescator
  
        
        mov edi,sir2
        mov edx,0
        mov ax,0
        
        repeta:
               repeta1:
                        dec byte [len]
                        mov esi,sir
                        add esi,edx
                        cmp edx,len
                        je terminat
                        inc byte [len]
                        lodsb
                        mov bl,al
                        inc edx
                        mov byte[t],0
                                
                        while1:
                              mov ecx,edx
                              add cl,[t]
                              inc byte[t]
                              cmp ecx,len
                              je repeta1
                              for1: 
                                 
                                cmp ecx,[len]
                                je while1
                                mov esi,[sir+edx]
                                lodsb
                                div bl
                                cmp ah,0
                                jne da
                                mov byte [mem],al
                                cmp word[ratie],1
                                jne bun
                                mov [ratie],al
                                mov al,bl
                                stosb
                            bun: 
                             cmp word [mem],ratie
                             jne continua
                             inc word [nr]
                             dec esi
                             movsb
                             cmp word [nr],max
                             jle continua
                             mov word [max],nr
                             mov word [ratie_buna],ratie
                  continua:
                  cmp word[mem],ratie
                  jnl da
                  mov word [nr],0
                  mov edi,sir2
                  mov ecx,[len]
                  da:
                  jmp for1
                  
        terminat:          
                     
              
        push dword 0      
        call [exit]       
              
                   