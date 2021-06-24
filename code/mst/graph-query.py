import sys

if len(sys.argv) < 3:
	print ("python3 query_mst_to_group_info.py query.out result")
	exit()

query_out = sys.argv[1]
result = sys.argv[2]

dis = {}
with open(query_out) as fr:
	lines = fr.readlines()
for line in lines:
	s = line.rstrip().split("\t")
	for i in range(2, len(s), 2):
		if s[i] != s[1] and float(s[i+1]) >= 0.868:
			key1 = (s[1], s[i])
			if key1 not in dis:
				dis[key1] = 1 - float(s[i+1])
			key2 = (s[i], s[1])
			if key2 not in dis:
				dis[key2] = 1 - float(s[i+1])

with open(result, "w") as fw:
	for key in dis.keys():
		fw.write(key[0] + "\t" + key[1] + "\t" + str(dis[key]) + "\n")

