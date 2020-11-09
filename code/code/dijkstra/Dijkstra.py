# coding: utf-8

import csv
"""
with open("all_samples") as fr:
	line = fr.read()
	samples = line.split()
"""
edges = []
firstline = True
with open('samples0.csv', 'r') as f:
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
# print(names)
# print(weights)
# print(g.is_weighted())

# print(g.vcount()) 



f_value = open("shortest_path_value.txt", "w")
f_info = open("shortest_path_info.txt", "w")
for b in samples:
	f_value.write("\t" + b)
f_value.write("\n")
for a in samples:
	f_value.write(a)
	for b in samples:
		shortest_paths = g.shortest_paths(a, b)[0][0]
		f_value.write("\t" + str(shortest_paths))
		if shortest_paths == float("inf"):
			f_info.write("oo\t")
		else:
			get_shortest_paths = g.get_shortest_paths(a, b)[0]
			for i, x in enumerate(get_shortest_paths):
				if i == 0:
					f_info.write(names[x])
				else:
					f_info.write("->" + names[x])
			f_info.write("\t")
	f_info.write("\n")
	f_value.write("\n")
f_value.close()
f_info.close()

