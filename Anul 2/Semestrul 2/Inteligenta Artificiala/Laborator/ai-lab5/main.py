import math

from aco import ACO, Graph
from plot import plot


def distance(city1, city2):
    return math.sqrt((city1['x'] - city2['x']) ** 2 + (city1['y'] - city2['y']) ** 2)


def main(filename):
    cities = []
    points = []
    with open(filename) as f:
        for line in f.readlines():
            city = line.split(' ')
            cities.append(dict(index=int(city[0]), x=float(city[1]), y=float(city[2])))
            points.append((float(city[1]), float(city[2])))
    cost_matrix = []
    dim = len(cities)
    for i in range(dim):
        row = []
        for j in range(dim):
            row.append(distance(cities[i], cities[j]))
        cost_matrix.append(row)
    aco = ACO(10, 150, 1.0, 10.0, 0.5)
    graph = Graph(cost_matrix, dim)
    path, cost = aco.solve(graph)
    print('cost:' + str(cost) + '\npath:' + str(path))
    plot(points, path)


if __name__ == '__main__':
    #main('berlin.tsp')
    #main('xqg237.tsp') #1019 optimal
    #main('dj38.tsp') #6656 optimal
    main('xqf131.tsp') #564 optimal
