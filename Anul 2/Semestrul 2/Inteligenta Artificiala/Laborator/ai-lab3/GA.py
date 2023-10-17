from random import randint

from Chromosome import Chromosome


class GA:
    def __init__(self, param=None, problParam=None):
        self.__param = param
        self.__problParam = problParam
        self.__population = []

    @property
    def population(self):
        return self.__population

    def initialisation(self):
        """
            initializarea populatiei
        """
        for _ in range(self.__param['popSize']):
            c = Chromosome(self.__problParam)
            self.__population.append(c)

    def evaluation(self):
        """
            stabilirea fitness-ului cromozomilor populatiei
        """
        for c in self.__population:
            c.fitness = self.__problParam['function'](c.repres, self.__problParam)

    def bestChromosome(self):
        """
        :return: cel mai bun cromozom (cu fitness mare)
        """
        best = self.__population[0]
        for c in self.__population:
            if c.fitness > best.fitness:
                best = c
        return best

    def worstChromosome(self):
        """
        :return: cel mai rau cromozom (cu fitness mic)
        """
        best = self.__population[0]
        for c in self.__population:
            if c.fitness < best.fitness:
                best = c
        return best

    def selection(self):
        """
        :return: o parte din populatie (cea mai buna parte- cu fitness-ul mai bun)
        """
        pos1 = randint(0, self.__param['popSize'] - 1)
        pos2 = randint(0, self.__param['popSize'] - 1)
        if self.__population[pos1].fitness > self.__population[pos2].fitness:
            return pos1
        else:
            return pos2

    def selTurnir(self):
        """
        :return: cromozomul cu cel mai bun fitness din populatia din turnir
        """
        l = []
        for i in range(self.__param['turnirSize']):
            poz = randint(0, self.__param['popSize'] - 1)
            l.append(self.__population[poz])

        l_rez = sorted(l, key=lambda x: x.fitness, reverse=True)
        return l_rez[0]

    def oneGeneration(self):
        newPop = []
        for _ in range(self.__param['popSize']):
            p1 = self.selTurnir()
            p2 = self.selTurnir()
            off = p1.crossover(p2, self.__param['pc'])
            off.mutation(self.__param['pm'])
            newPop.append(off)
        self.__population = newPop
        self.evaluation()
