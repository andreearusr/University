sumaCifre(0, 0).
sumaCifre(N, Sum) :- N > 0,
    N1 is N div 10,
    sumaCifre(N1, Sum1),
    Cif is N mod 10,
    Sum is Sum1 + Cif.
