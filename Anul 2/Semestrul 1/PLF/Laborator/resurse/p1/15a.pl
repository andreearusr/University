f([]) :- true.
f([_, _|T]) :- f(T).