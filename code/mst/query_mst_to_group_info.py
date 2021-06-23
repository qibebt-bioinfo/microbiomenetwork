import sys

if len(sys.argv) < 5:
	print ("python3 query_mst_to_group_info.py mst node.list meta result")
	exit()

query_mst = sys.argv[1]
node_list = sys.argv[2]
meta_file = sys.argv[3]
result = sys.argv[4]

nodes = {} 
with open(node_list) as fr:
	lines = fr.readlines()
for line in lines:
	s = line.rstrip().split("\t")
	nodes[s[1]] = s[0]

meta = {}
with open(meta_file) as fr:
	lines = fr.readlines()
for line in lines:
	s = line.rstrip().split("\t")
	meta[s[0]] = s[1]

dis = {}
count = {}
#fw = open("query_mst.group", "w")
with open(query_mst) as fr:
	lines = fr.readlines()
for line in lines:
	s = line.rstrip().split("\t")
	if meta[nodes[s[0]]] == meta[nodes[s[1]]]:
		continue
	#fw.write(meta[nodes[s[0]]] + "\t" + meta[nodes[s[1]]] + "\t" + s[2] + "\n")
	key = (meta[nodes[s[0]]], meta[nodes[s[1]]])
	if key not in count:
		count[key] = 1
		dis[key] = float(s[2])
	else:
		count[key] += 1
		dis[key] += float(s[2])
#fw.close()

with open(result, "w") as fw:
	for key in count.keys():
		if count[key]:
			fw.write(key[0] + "\t" + key[1] + "\t" + str(dis[key]/count[key]) + "\n")

