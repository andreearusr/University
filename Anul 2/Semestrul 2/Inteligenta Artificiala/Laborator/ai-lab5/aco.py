import random

import matplotlib.pyplot as plt


class Graph(object):
    def __init__(self, cost_matrix, dim):
        """
        :param cost_matrix: matricea costurilor/distantelor
        :param dim: dimensiunea matricii costurilor
        """
        self.matrix = cost_matrix
        self.dim = dim

        self.pheromone = [[1 / (dim * dim) for j in range(dim)] for i in range(dim)]


class ACO(object):
    def __init__(self, ant_count, generations, alpha, beta, coeficient):
        """
        :param ant_count: numarul de furnici
        :param generations: numarul de generatii
        :param alpha: importanta feromonului
        :param beta: importanta vizibilitatii, cat de aproape este celalat nod
        :param coeficient: coeficientul rezidual al feromonului = (1-fi) = 1-coef de evaporare a urmei de feromon
        """

        self.coeficient = coeficient
        self.beta = beta
        self.alpha = alpha
        self.ant_count = ant_count
        self.generations = generations

    def _update_pheromone(self, graph, ants):
        for i, row in enumerate(graph.pheromone):
            for j, col in enumerate(row):
                graph.pheromone[i][j] *= self.coeficient
                for ant in ants:
                    graph.pheromone[i][j] += ant.pheromone_delta[i][j]

    def solve(self, graph):
        """
        :param graph: un graf
        """
        best_cost = float('inf')
        best_solution = []
        lx = []
        ly = []
        for gen in range(self.generations):
            ants = [Ant(self, graph) for i in range(self.ant_count)]
            for ant in ants:
                for i in range(graph.dim - 1):
                    ant._select_next()
                ant.total_cost += graph.matrix[ant.tsp_list[-1]][ant.tsp_list[0]]
                if ant.total_cost < best_cost:
                    best_cost = ant.total_cost
                    best_solution = [] + ant.tsp_list

                ant._update_pheromone_delta()
            self._update_pheromone(graph, ants)
            lx.append(gen)
            ly.append(best_cost)
            print('generation ' + str(gen) + ' best cost:' + str(best_cost) + ' path:' + str(best_solution))
        plt.plot(lx, ly)
        plt.show()

        return best_solution, best_cost


class Ant(object):
    def __init__(self, aco, graph):
        self.colony = aco
        self.graph = graph
        self.total_cost = 0.0
        self.tsp_list = []  # lista noduri vizitate
        self.pheromone_delta = []  # cresterea locala a feromonului
        self.allowed = [i for i in range(graph.dim)]  # noduri permise pentru urmatoarea selectie
        self.eta = [[0 if i == j else 1 / graph.matrix[i][j] for j in range(graph.dim)] for i in
                    range(graph.dim)]  # vizibilitatea oraselor
        start = random.randint(0, graph.dim - 1)
        self.tsp_list.append(start)
        self.current = start
        self.allowed.remove(start)

    def _select_next(self):
        denominator = 0
        for i in self.allowed:
            denominator += self.graph.pheromone[self.current][i] ** self.colony.alpha * self.eta[self.current][
                i] ** self.colony.beta

        probabilities = [0 for i in range(self.graph.dim)]  # probabilitatile de a se muta pe un alt nod
        for i in range(self.graph.dim):
            try:
                self.allowed.index(i)  # verificam daca lista il contine pe i
                probabilities[i] = (self.graph.pheromone[self.current][i] ** self.colony.alpha) * (
                        self.eta[self.current][i] ** self.colony.beta) / denominator
            except ValueError:
                pass

        selected = 0
        rand = random.random()
        for i, probability in enumerate(probabilities):
            rand -= probability
            if rand <= 0:
                selected = i
                break
        self.allowed.remove(selected)
        self.tsp_list.append(selected)
        self.total_cost += self.graph.matrix[self.current][selected]
        self.current = selected

    def _update_pheromone_delta(self):
        self.pheromone_delta = [[0 for j in range(self.graph.dim)] for i in range(self.graph.dim)]
        for k in range(1, len(self.tsp_list)):
            i = self.tsp_list[k - 1]
            j = self.tsp_list[k]
            self.pheromone_delta[i][j] = 1 / self.total_cost
