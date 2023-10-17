import networkx as nx
from matplotlib import pyplot as plt


def edge_to_remove(G):
    """

    :param G: graful dat
    :return: muchia ce trebuie stearsa
    """
    G_dict = nx.edge_betweenness_centrality(G)
    list_of_tuples = G_dict.items()
    l = sorted(list_of_tuples, key=lambda x: x[1], reverse=True)

    return l[0][0]


def girvan_newman(G, nr_com):
    """

    :param G: graful dat
    :param nr_com: numarul de comunitati cin care trebuie sa se imparta graful G
    :return: comunitatile din graf
    """
    comp = nx.connected_components(G)
    n_comp = nx.number_connected_components(G)

    while n_comp < nr_com:
        edge = edge_to_remove(G)
        G.remove_edge(edge[0], edge[1])
        comp = nx.connected_components(G)
        n_comp = nx.number_connected_components(G)

    return [len(c) for c in sorted(comp, key=len, reverse=False)]


def draw(G):
    """
    deseneaza graful corespunzator lui G
    :param G: un graf
    """
    nx.draw(G, with_labels=True)
    plt.show()


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


def test(fileName):
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
    else:
        G = nx.read_gml(fileName + "/" + fileName + ".gml")


    # draw(G)

    communities = girvan_newman(G, nr_communities)

    # draw(G)
    l_ex = example(fileName + "/real.dat")  # lista cu numarul nodurilor din fiecare comunitate din exemplu
    l_det = communities  # lista cu numarul nodurilor din fiecare comunitate determinata de noi
    print("Exemplu:" + str(l_ex))
    print("Noi:" + str(l_det))
    for i in range(len(l_ex)):
        assert (abs(l_ex[i] - l_det[i]) <= 10)


test("dolphins")
test("football")
test("karate")
test("krebs")


def t():
    G = nx.read_gml("student/lesmis.gml")
    communities = girvan_newman(G, 11)
    print("Noi:" + str(communities))
    #draw(G)


def a():
    G = nx.read_gml("student/polbooks.gml")
    communities = girvan_newman(G, 3)
    print("Noi:" + str(communities))
    #draw(G)


def b():
    G = nx.read_gml("student/adjnoun.gml")
    communities = girvan_newman(G, 5)
    print("Noi:" + str(communities))
    #draw(G)


def c():
    G = nx.read_gml("student/ex4.gml", label=None, destringizer=None)
    #draw(G)
    communities = girvan_newman(G, 2)
    print("Noi:" + str(communities))
    #draw(G)


def d():
    G = nx.read_gml("student/ex5.gml", label=None, destringizer=None)
    #draw(G)
    communities = girvan_newman(G, 3)
    print("Noi:" + str(communities))
    #draw(G)


def e():
    G = nx.read_gml("student/ex6.gml", label=None, destringizer=None)
    draw(G)
    communities = girvan_newman(G, 4)
    print("Noi:" + str(communities))
    draw(G)


t()
a()
b()
c()
d()
e()
