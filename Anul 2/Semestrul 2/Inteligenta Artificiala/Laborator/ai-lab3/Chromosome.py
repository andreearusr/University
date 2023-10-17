import random
from random import randint


class Chromosome:
    def __init__(self, problParam=None):
        self.__problParam = problParam
        self.__repres = [randint(problParam['min'], problParam['max']) for _ in range(problParam['noDim'])]
        self.__fitness = 0.0

    @property
    def repres(self):
        return self.__repres

    @property
    def fitness(self):
        return self.__fitness

    @repres.setter
    def repres(self, l=[]):
        self.__repres = l

    @fitness.setter
    def fitness(self, fit=0.0):
        self.__fitness = fit

    def crossover(self, c, crossover_rate):
        """

        :param c: un cromozom
        :param crossover_rate: rata de incrucisare
        :return: cromozomul rezultat in urma incrucisarii, daca aceasta se realizeaza,
                 altfel, se returneaza obiectul actual
        """
        if random.random() <= crossover_rate:
            r = randint(0, len(self.__repres) - 1)
            newrepres = []
            for i in range(r):
                newrepres.append(self.__repres[i])
            for i in range(r, len(self.__repres)):
                newrepres.append(c.__repres[i])
            offspring = Chromosome(c.__problParam)
            offspring.repres = newrepres
            return offspring
        else:
            if self.__fitness > c.__fitness:
                return self
            else:
                return c

    def mutation(self, mutation_rate):
        """
        :param mutation_rate: rata de mutatie
        """
        if random.random() <= mutation_rate:
            pos = randint(0, len(self.__repres) - 1)
            self.__repres[pos] = randint(self.__problParam['min'], self.__problParam['max'])

    def modularity(communities, param):
        """

        :param param: parametrii problemei
        :return: modularitatea grafului
        """
        noNodes = param['noDim']  # noNodes
        mat = param['mat']
        degrees = param['degrees']
        noEdges = param['noEdges']
        M = 2 * noEdges
        Q = 0.0
        for i in range(0, noNodes):
            for j in range(0, noNodes):
                if communities[i] == communities[j]:
                    Q += (mat[i][j] - degrees[i] * degrees[j] / M)
        return Q * 1 / M

    def __str__(self):
        return '\nChromo: ' + str(self.__repres) + ' has fit: ' + str(self.__fitness)

    def __repr__(self):
        return self.__str__()

    def __eq__(self, c):
        return self.__repres == c.__repres and self.__fitness == c.__fitness
