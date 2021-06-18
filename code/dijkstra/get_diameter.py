# coding: utf-8
from igraph import Graph as IGraph
import sys

if len(sys.argv) < 3:
	print("please execute \n\tpython get_diameter.py query_out_file result_file")
	exit(0)
 
edges = []
firstline = True
query_file = sys.argv[1]
result = sys.argv[2]

with open(query_file, 'r') as fr:
	lines = fr.readlines()
	for line in lines:
		s = line.rstrip().split("\t")
		for i in range(2, len(s), 2):
			edges.append((s[1], s[i], float(s[i+1])))

g = IGraph.TupleList(edges, directed=True, vertex_name_attr='name', edge_attrs=None, weights=True)
# print(g)

names = g.vs["name"]
weights = g.es["weight"]
samples = names
# print(names)
# print(weights)
# print(g.is_weighted())

# print(g.vcount()) # 角色数

# 网络直径：一个网络的直径（或者测地线）被定义为网络中的最长最短路径
with open(result, "w") as fw:
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

