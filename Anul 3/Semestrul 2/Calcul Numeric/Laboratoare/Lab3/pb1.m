A = [10, 7, 8, 7; 7, 5, 6, 5; 8, 6, 10, 9; 7, 5, 9, 10];
b = [32; 23; 33; 31];
x = A\b;

bp = [32.1; 22.9; 33.1; 30.9];
xp = A\bp;
err_in = norm(b-bp);
err_out = norm(x-xp);
raport = err_out/err_in;
disp('a:')
MSG = ['Eroare relativa la intrare: ', num2str(err_in)];
disp(MSG)
MSG = ['Eroare relativa la iesire: ', num2str(err_out)];
disp(MSG)
MSG = ['Raportul erorilor: ', num2str(raport)];
disp(MSG)
disp(' ')


disp('b:')
Ap = [10, 7, 8.1, 7.2; 7.08, 5.04, 6, 5; 8, 5.98, 9.89, 9; 6.99, 4.99, 9, 9.98];
xp = Ap\b;
err_in = norm(A-Ap);
err_out = norm(x-xp);
raport = err_out/err_in;
MSG = ['Eroare relativa la intrare: ', num2str(err_in)];
disp(MSG)
MSG = ['Eroare relativa la iesire: ', num2str(err_out)];
disp(MSG)
MSG = ['Raportul erorilor: ', num2str(raport)];
disp(MSG)

% perturbare mica si rezultat cu mult diferit => problema nu este bine conditionata
