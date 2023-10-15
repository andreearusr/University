%1. probab ca intr-un grup de 23 pers, cel putin doua
% sa aiba aceeasi zi de nastere
function p=samebirthday(n=23,N=1000)
  count=0;
  for i=1:N
    birthdays=randi(365,1,n); %vector de 23 val aleatoare intre 1->365
    if length(unique(birthdays))<n
      count++;
    endif
  endfor
  p=count/N;
