# coding: utf-8
from igraph import Graph as IGraph
import sys

if len(sys.argv) < 3:
        print("please execute \n\tpython Dijkstra.py query_out_file result_file")
        exit(0)

edges = []
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


# 最短路径
f_value = open(result + ".value", "w")
f_info = open(result + ".info", "w")
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

