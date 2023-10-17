from random import randint

from Chromosome import Chromosome

class GA:

    def __init__(self, params):
        self.__params = params
        self.__population = []

    def get_population(self):
        return self.__population


    def initialisation(self):
        """
        functie pentru initializarea populatiei
        """
        for i in range(self.__params['popSize']):
            c = Chromosome(self.__params['dim'], self.__params['start'])
            self.__population.append(c)

    def evaluation(self):
        """
        stabilirea fitnessului fiecarui cromozom din populatie
        """
        for c in self.__population:
            c.calculate_fitness(self.__params['dist_matrix'])

    def bestChromosome(self):
        """
        :return: cel mai bun cromozom (fitness mic)
        """
        best = self.__population[0]
        for c in self.__population:
            if c.get_fitness() < best.get_fitness():
                best = c
        return best

    def worstChromosome(self):
        """
        :return: cel mai rau cromozom (fitness mare)
        """
        best = self.__population[0]
        for c in self.__population:
            if c.get_fitness() > best.get_fitness():
                best = c
        return best

    def selTurnir(self):
        """
        :return: cromozomul cu cel mai mic fitness(cel mai bun cromozom) din populatia din turnir
        """
        l = []
        for i in range(self.__params['turnirSize']):
            poz = randint(0, self.__params['popSize'] - 1)
            l.append(self.__population[poz])

        l_rez = sorted(l, key=lambda x: x.get_fitness())
        return l_rez[0]

    def oneGeneration(self):
        newPop = []
        for _ in range(self.__params['popSize']):
            p1 = self.selTurnir()
            p2 = self.selTurnir()
            off = p1.crossover(p2, self.__params['crossover_rate'])
            off.mutation(self.__params['mutation_rate'])
            newPop.append(off)
        self.__population = newPop
        self.evaluation()

    def oneGenerationElitism(self):
        newPop = [self.bestChromosome()]
        for _ in range(self.__params['popSize'] - 1):
            p1 = self.selTurnir()
            p2 = self.selTurnir()
            off = p1.crossover(p2, self.__params['crossover_rate'])
            off.mutation(self.__params['mutation_rate'])
            newPop.append(off)
        self.__population = newPop
        self.evaluation()

    '''
    def oneGenerationSteadyState(self):
        for _ in range(self.__param['popSize']):
            p1 = self.__population[self.selection()]
            p2 = self.__population[self.selection()]
            off = p1.crossover(p2)
            off.mutation()
            off.fitness = self.__problParam['function'](off.repres)
            worst = self.worstChromosome()
            if (off.fitness < worst.fitness):
                worst = off
    '''
