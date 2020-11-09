import sys

if len(sys.argv) < 4:
	print "query_mst\tnode.list\tresult"
	exit()

query_mst = sys.argv[1]
node_list = sys.argv[2]
result = sys.argv[3]
if result == "query_mst_to_group_info.py":
	exit()

nodes = {} 
with open(node_list) as fr:
	while True:
		try:
			line = fr.next().strip()
			s = line.split()
			nodes[s[1]] = s[0]
		except StopIteration:
			break

meta = {}
with open("../all.meta") as fr:
	while True:
		try:
			line = fr.next().strip()
			s = line.split()
			meta[s[0]] = s[1]
		except StopIteration:
			break

dis = {}
count = {}
fw = open("query_mst.group", "w")
with open(query_mst) as fr:
	while True:
		try:
			line = fr.next().strip()
			s = line.split()
			if meta[nodes[s[0]]] == meta[nodes[s[1]]]:
				continue
			fw.write(meta[nodes[s[0]]] + "\t" + meta[nodes[s[1]]] + "\t" + s[2] + "\n")
			key = (meta[nodes[s[0]]], meta[nodes[s[1]]])
			if key not in count:
				count[key] = 1
				dis[key] = float(s[2])
			else:
				count[key] += 1
				dis[key] += float(s[2])
		except StopIteration:
			break
fw.close()

with open(result, "w") as fw:
	for key in count.keys():
		if count[key]:
			fw.write(key[0] + "\t" + key[1] + "\t" + str(dis[key]/count[key]) + "\n")

