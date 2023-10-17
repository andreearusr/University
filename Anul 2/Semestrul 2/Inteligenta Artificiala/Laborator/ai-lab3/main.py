import random
import warnings

import networkx as nx
from matplotlib import pyplot as plt

from Chromosome import Chromosome
from GA import GA


def example(fileName):
    """

    :param fileName: un nume de fisier
    :return: lista cu numarul nodurilor din fiecare comunitate din fisier
    """
    nr_communities = []
    with open(fileName, "r") as f:
        lines = f.readlines()
        for line in lines:
            nr = 0
            line = line.strip()
            if line != "":
                parts = line.split(" ")
                nr = len(parts)
            nr_communities.append(nr)

    return sorted(nr_communities)


def main(fileName):
    warnings.simplefilter('ignore')

    print(fileName + ".gml -------------")
    nr_communities = 0

    if fileName == "dolphins":
        nr_communities = 2
    if fileName == "football":
        nr_communities = 12
    if fileName == "krebs":
        nr_communities = 3
    if fileName == "karate":
        G = nx.read_gml(fileName + "/" + fileName + ".gml", label=None, destringizer=None)
        nr_communities = 2
    elif fileName == "lesmis":
        G = nx.read_gml("student" + "/" + fileName + ".gml")
        nr_communities = 11
    elif fileName == "ex1":
        G = nx.read_gml("student" + "/" + fileName + ".gml", label=None, destringizer=None)
        nr_communities = 2
    elif fileName == "ex2":
        G = nx.read_gml("student" + "/" + fileName + ".gml", label=None, destringizer=None)
        nr_communities = 3
    elif fileName == "ex3":
        G = nx.read_gml("student" + "/" + fileName + ".gml", label=None, destringizer=None)
        nr_communities = 4
    else:
        G = nx.read_gml(fileName + "/" + fileName + ".gml")


    pos = nx.spring_layout(G)  # compute graph layout
    plt.figure(figsize=(4, 4))  # image is 8 x 8 inches
    nx.draw_networkx_nodes(G, pos, node_size=600, cmap=plt.cm.RdYlBu)
    nx.draw_networkx_edges(G, pos, alpha=0.3)
    plt.show()

    mat = nx.to_numpy_array(G)
    print(mat)

    degrees = []
    nr_nodes = nx.number_of_nodes(G)
    for i in range(nr_nodes):
        d = 0
        for j in range(nr_nodes):
            if mat[i][j] == 1:
                d += 1
        degrees.append(d)

    gaParam = {'popSize': 20, 'noGen': 15, 'pc': 0.8,
               'pm': 0.1, 'turnirSize': random.randint(1,20)}  # pop_size, nr_epoci(nr Generatii), rata_recomb(crossover), raata_mutatie
    # problem parameters
    problParam = {'min': 1, 'max': nr_communities, 'function': Chromosome.modularity, 'noDim': G.number_of_nodes(),
                  'mat': mat,
                  'degrees': degrees,
                  'noEdges': G.number_of_edges()}

    ga = GA(gaParam, problParam)
    ga.initialisation()
    ga.evaluation()

    B = []
    for g in range(gaParam['noGen']):
        ga.oneGeneration()

        bestChromo = ga.bestChromosome()
        B.append(bestChromo)
        print('Best solution in generation ' + str(g) + ' is: chr = ' + str(bestChromo.repres) + ' modularity = '
              + str(bestChromo.fitness))

    B1 = sorted(B, key=lambda x: x.fitness, reverse=True)
    print("Best fitness:" + str(B1[0].fitness))

    if fileName != "lesmis" and fileName != "ex1" and fileName != "ex2" and fileName != "ex3":
        l_ex = example(fileName + "/real.dat")
        print(l_ex)


    l_noi = []
    reprez = B1[0].repres
    for i in range(1, nr_communities + 1):
        c = reprez.count(i)
        l_noi.append(c)
    print(sorted(l_noi))

    # plot a particular division in communities
    pos = nx.spring_layout(G)  # compute graph layout
    plt.figure(figsize=(4, 4))  # image is 8 x 8 inches
    nx.draw_networkx_nodes(G, pos, node_size=600, cmap=plt.cm.RdYlBu, node_color=B1[0].repres)
    nx.draw_networkx_edges(G, pos, alpha=0.3)
    plt.show()



main("dolphins")
main("football")
main("karate")
main("krebs")
main("lesmis")

main("ex1")
main("ex2")
main("ex3")
