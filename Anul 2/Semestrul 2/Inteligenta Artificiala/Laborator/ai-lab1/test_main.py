import math

from p1 import pr1
from p10 import pr10
from p2 import pr2
from p3 import pr3
from p4 import pr4
from p5 import pr5
from p6 import pr6
from p7 import pr7
from p8 import pr8
from p9 import pr9


def teste():
    assert (pr1("Ana are mere rosii si galbene") == "si")
    assert (pr1("Maine mergem la bunica") == "mergem")
    assert (pr1("Astazi este o petrecere frumoasa") == "petrecere")
    assert (pr1("Stam sa supraveghem surprizele") == "surprizele")

    assert (pr2((1, 5), (4, 1)) == 5)
    assert (pr2((0, 0), (0, 0)) == 0)
    assert (pr2((1, 0), (1, 0)) == 0)
    assert (pr2((-2, 5), (-4, 1)) == math.sqrt(20))

    assert (pr3([[1, 0, 2, 0, 3]], [[1, 2, 0, 3, 1]]) == 4)
    assert (pr3([[1, 0, 2], [2, 3, 0]], [[1, 0, 0], [1, 0, 1]]) == 3)

    assert (pr4("ana are ana are mere rosii ana")[0] == "mere")
    assert (pr4("ana are ana are mere rosii ana")[1] == "rosii")
    assert (pr4("maine soare este soare este cald cald")[0] == "maine")
    assert (pr4("da sigur da sigur") == [])

    assert (pr5([1, 2, 3, 4, 2]) == 2)
    assert (pr5([1, 1, 2]) == 1)
    assert (pr5([1, 2, 3, 5, 4, 5]) == 5)

    assert (pr6([2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]) == 2)
    assert (pr6([3, 1, 3, 3, 2]) == 3)
    assert (pr6([1, 1, 1, 1, 1]) == 1)
    assert (pr6([1, 1, 2, 2]) == -100000000)

    assert (pr7([7, 4, 6, 3, 9, 1], 2) == 7)
    assert (pr7([7, 4, 6, 3, 9, 1], 1) == 9)
    assert (pr7([1, 1, 1, 1], 3) == 1)
    assert (pr7([10, -3, 6, 15, -9], 4) == -3)

    assert (pr8(4) == [[1], [1, 0], [1, 1], [1, 0, 0]])
    assert (pr8(6) == [[1], [1, 0], [1, 1], [1, 0, 0], [1, 0, 1], [1, 1, 0]])
    assert (pr8(1) == [[1]])

    assert (pr9([[0, 2, 5, 4, 1], [4, 8, 2, 3, 7], [6, 3, 4, 6, 2], [7, 3, 1, 8, 3], [1, 5, 7, 9, 4]],
                [((1, 1), (3, 3)), ((2, 2), (4, 4)), ((1, 2), (2, 4)), ((3, 4), (1, 2)), ((0, 2), (2, 1)),
                 ((0, 1), (0, 3)), ((0, 3), (0, 3))]) == [38, 44, 24, 36, 24, 11, 4])

    assert (pr10([[0, 0, 0, 1, 1], [0, 1, 1, 1, 1], [0, 0, 1, 1, 1]]) == 2)
    assert (pr10([[0, 0, 0, 1], [0, 0, 1, 1], [1, 1, 1, 1]]) == 3)
    assert (pr10([[0, 0, 0], [0, 0, 0], [0, 0, 0]]) == 0)
    print("teste rulate cu succes")
