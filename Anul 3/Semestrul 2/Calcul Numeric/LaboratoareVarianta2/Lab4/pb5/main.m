[A, b] = generareSistem(7);
disp(rezolvareLUP(A, b))
disp(rezolvareQR(A, b))
% pentru o matrice mare, putem observa ca solutiile corespunzatoare celor 
% doua metode de rezolvare difera
% acest lucru se datoreaza faptului ca apar erori de precizie in rezolvarea
% folosind metoda LUP, matricea A fiind devenind o matrice rara atunci cand area 
% dimensiuni mari