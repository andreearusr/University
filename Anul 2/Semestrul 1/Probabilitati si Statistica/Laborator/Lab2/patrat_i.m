%2. generati N puncte uniform aleatoare intr-un patrat
% Afisati frecventa relativa apct care: 
%a) sunt in interiorul cercului tangent laturilor patratului (cerc)
%N=numarul de puncte generate

% 0 1  <- patrat
% 0 1
function patrat_i(N=500)
 clf;hold on;axis square; axis off;
 rectangle('Position',[0 0 1 1]); 
 count=0;
 for i=1:N
    x=rand;y=rand; % 0->1
    if pdist([x y;0.5 0.5])<0.5 %puncte mai aproape de centru
        plot(x,y,'dm','MarkerSize',7,'MarkerFaceColor','m');
        count++;
    endif
 endfor
 fprintf('Probabilitatea estimata, ceruta la i), este %3.2f.\n',count/N);