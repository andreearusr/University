import random


def random_list(dim, start):
    l_rez = []
    l_rez.append(start)
    l = []
    for i in range(1, dim):
        if i != start:
            l.append(i)
    random.shuffle(l)

    for i in range(len(l)):
        l_rez.append(l[i])

    l_rez.append(start)
    return l_rez


class Chromosome:

    def __init__(self, dim, start):
        self.__dim = dim
        self.__start = start
        self.__repr = random_list(dim, start)
        self.__fitness = 0.0

    def calculate_fitness(self, dist_matrix):
        """
        calculeaza fitnessul unui cromozom
        :param dist_matrix: matricea distantelor in graf
        """
        chromosomeFit = 0
        for i in range(len(self.__repr) - 1):
            x = self.__repr[i]
            y = self.__repr[i + 1]
            chromosomeFit += dist_matrix[x][y]
        self.__fitness = chromosomeFit

    def get_fitness(self):
        return self.__fitness

    def get_repr(self):
        return self.__repr

    def set_fitness(self, value):
        self.__fitness = value

    def set_repr(self, value):
        self.__repr = value

    def crossover(self, c, crossover_rate):
        """

        :param c: un cromozom
        :param crossover_rate: rata de incrucisare
        :return: cromozomul rezultat in urma incrucisarii, daca aceasta se realizeaza,
                 altfel, se returneaza obiectul actual
        """
        if random.random() <= crossover_rate:
            r = random.randint(1, len(self.__repr) - 2)
            newrepres = []
            newrepres.append(self.__repr[0])

            for i in range(1, r):
                newrepres.append(self.__repr[i])
            for i in range(1, len(c.__repr) - 1):
                if newrepres.count(c.__repr[i]) == 0:
                    newrepres.append(c.__repr[i])

            newrepres.append(c.__repr[len(c.__repr) - 1])

            children = Chromosome(self.__dim, self.__start)
            children.repr = newrepres
            return children
        else:
            if self.__fitness < c.__fitness:
                return self
            else:
                return c

    def mutation(self, mutation_rate):
        """
        :param mutation_rate: rata de mutatie
        """
        if random.random() <= mutation_rate:
            pos1 = random.randint(1, len(self.__repr) - 2)
            pos2 = random.randint(1, len(self.__repr) - 2)
            while pos1 == pos2:
                pos1 = random.randint(1, len(self.__repr) - 2)
                pos2 = random.randint(1, len(self.__repr) - 2)
            self.__repr[pos1], self.__repr[pos2] = self.__repr[pos2], self.__repr[pos1]

    def __str__(self):
        return str(self.__repr)

    def __eq__(self, c):
        return self.__repr == c.__repr and self.__fitness == c.__fitness
