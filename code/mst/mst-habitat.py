import sys

if len(sys.argv) < 4:
	print ("python3 query_mst_to_group_info.py mst meta result")
	exit()

query_mst = sys.argv[1]
meta_file = sys.argv[2]
result = sys.argv[3]


meta = {}
with open(meta_file) as fr:
	lines = fr.readlines()
for line in lines:
	s = line.rstrip().split("\t")
	meta[s[0]] = s[1]

dis = {}
count = {}
with open(query_mst) as fr:
	lines = fr.readlines()
for line in lines:
	s = line.rstrip().split("\t")
	if meta[s[0]] == meta[s[1]]:
		continue
	key1 = (meta[s[0]], meta[s[1]])
	if key1 not in count:
		count[key1] = 1
		dis[key1] = float(s[2])
	else:
		count[key1] += 1
		dis[key1] += float(s[2])
	key2 = (meta[s[1]], meta[s[0]])
	if key2 not in count:
		count[key2] = 1
		dis[key2] = float(s[2])
	else:
		count[key2] += 1
		dis[key2] += float(s[2])

with open(result, "w") as fw:
	for key in count.keys():
		if count[key]:
			fw.write(key[0] + "\t" + key[1] + "\t" + str(dis[key]/count[key]) + "\n")

