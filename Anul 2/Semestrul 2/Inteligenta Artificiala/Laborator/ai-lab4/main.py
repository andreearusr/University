import sys

import matplotlib.pyplot as plt

from GA import GA


def example(fileName):
    inf = sys.maxsize
    dist_matrix = []

    with open(fileName, "r") as f:
        dim = int(f.readline().strip())

        for i in range(dim + 1):
            camp = []
            for j in range(dim + 1):
                camp.append(0)
            dist_matrix.append(camp)

        for i in range(1, dim + 1):
            line = f.readline().strip()
            parts = line.split(",")

            for j in range(1, len(parts) + 1):
                if int(parts[j - 1]) == 1000000:
                    dist_matrix[i][j] = 1000000
                else:
                    dist_matrix[i][j] = int(parts[j - 1])

        source = int(f.readline().strip())

    return dim, dist_matrix, source


def main():
    # dim, dist_matrix, source = example("easy_01_tsp.txt")
    # dim, dist_matrix, source = example("ex1redusa.txt")
    # dim, dist_matrix, source = example("ex2redusa.txt")
    #dim, dist_matrix, source = example("ex1medie.txt")
    #dim, dist_matrix, source = example("ex2medie.txt")
    #dim, dist_matrix, source = example("ex1mare.txt")
    dim, dist_matrix, source = example("ex2mare.txt")

    popSize = 400
    noGen = 100
    turnirSize = 100
    crossover_rate = 0.8
    mutation_rate = 0.5

    gaParam = {'popSize': popSize, 'noGen': noGen, 'crossover_rate': crossover_rate,
               'mutation_rate': mutation_rate, 'turnirSize': turnirSize, 'dim': dim + 1, 'start': source,
               'dist_matrix': dist_matrix}

    ga = GA(gaParam)
    ga.initialisation()
    ga.evaluation()

    B = []
    l = []
    for g in range(gaParam['noGen']):
        # ga.oneGeneration()
        ga.oneGenerationElitism()

        bestChromo = ga.bestChromosome()
        B.append(bestChromo)

        if g == gaParam['noGen'] - 1:
            for c in ga.get_population():
                if c.get_fitness() == bestChromo.get_fitness() and l.count(c) == 0:
                    l.append(c)

        # print('Best solution in generation ' + str(g) + ' is: chr = ' + str(bestChromo.get_repr()) + ' fitness = '
        #      + str(bestChromo.get_fitness()))

    B1 = sorted(B, key=lambda x: x.get_fitness())
    if B1[0].get_fitness() >= 1000000:
        print('algoritmul nu a gasit o cale')
    else:
        print("Best fitness:" + str(B1[0].get_fitness()))
        for el in l:
            print(str(el) + "fit" + str(el.get_fitness()))
        x = []
        y = []

        for el in ga.get_population():
            x.append(el.get_fitness())
        for el in x:
            nr = 0
            for e in ga.get_population():
                if e.get_fitness() == el:
                    nr += 1
            y.append(nr)
        plt.scatter(x, y, color='red', marker='o', s=30)

        plt.ylim(0, popSize-250)
        plt.xlim(0, popSize-250)

        plt.xlabel('fitness - axis')
        plt.ylabel('noChr - axis')
        plt.show()

main()
