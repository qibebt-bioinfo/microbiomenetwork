# coding: utf-8

import sys
import csv


line_count = int(sys.argv[1])

edges = []
firstline = True
with open("samples_without_" + str(line_count) + ".csv", 'r') as f:
	for row in csv.reader(f.read().splitlines()):
		if firstline == True:
			firstline = False
			continue
		u, v, weight = [i for i in row]
		edges.append((u, v, float(weight)))

from igraph import Graph as IGraph

g = IGraph.TupleList(edges, directed=True, vertex_name_attr='name', edge_attrs=None, weights=True)
# print(g)

names = g.vs["name"]
weights = g.es["weight"]
samples = names

with open("new_net_diameter_"+ str(line_count) +".txt", "w") as fw:
	fw.write(str(g.diameter()) + '\n')
	names = g.vs["name"]
	diameter = g.get_diameter()
	"""
	for data in diameter:
		fw.write(str(data) + '\t')
	fw.write('\n')
	"""
	for x in diameter:
		fw.write(names[x] + "\t")
	fw.write('\n')

