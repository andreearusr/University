bits 32 
global dest 

segment data use32 class=data public
    patru dd 4
segment code use32 class=code public

    dest:
; [ESP] <- adresa de revenire
; [ESP+4] <- valoarea nr_citite 
; [ESP+8] <- adresa sirului sir_final
; [ESP+12] <- adresa sirului sir 

        mov EAX,0
        
        mov EDI,[ESP+8]
        mov ECX,[ESP+4]
        
        mov EAX,[ESP+4]
        dec EAX
        mul dword[patru]     ;EDX:EAX<-rezultatul

        mov ESI,[ESP+12]
        add ESI,EAX
        
        repeta:
            mov EAX,0
        
            std
            lodsd
            add EAX,EAX   
    
            cld
            stosd
            
        loop repeta 
        
        ret 
    