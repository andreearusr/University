%b) simulati de m ori o astfel de depl. cu k pasi, prob p(0,1)
% afisati histograma pozitiilor finale
% care este poz finala cea mai frecventa?
%c) estimati val medie a nr de pasi la dreapta
function mers_axa_b_c(p=0.7,k=5,m=2000)
positions_end=[];
steps2right=[];
for i=1:m
   [pos,steps]=mers_axa_a(p,k);
   positions_end=[positions_end;pos(end)];
   steps2right=[steps2right,steps];
end

%nr. de el. ale lui pos_end care se încadreaz? în casetele de histograme definite de -k:k
N=histc(positions_end,-k:k)
bar(-k:k,N/m,'hist','FaceColor','b'); %bar din 2 vectori
set(gca,'XTick',-k:k); grid on;
xlim([-k-1 k+1]);

fprintf('Poz. finale cele mai frecvente: %d.\n',find(N==max(N))-k-1);

fprintf('Media nr. de pasi la dr.: %3.2f.\n',mean(steps2right));