import sys

if len(sys.argv) < 4:
	print ("python3 query_mst_to_group_info.py query.out meta result")
	exit()

query_out = sys.argv[1]
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
fw = open("query.group", "w")
with open(query_out) as fr:
	lines = fr.readlines()
for line in lines:
	s = line.rstrip().split("\t")
	i, l = 2, len(s)
	while i < l:
		if s[i] != s[1] and float(s[i+1]) >= 0.868:
			fw.write(meta[s[1]] + "\t" + meta[s[i]] + "\t" + s[i+1] + "\n")
			key = (meta[s[1]], meta[s[i]])
			if key not in count:
				count[key] = 1
				dis[key] = 1 - float(s[i+1])
			else:
				count[key] += 1
				dis[key] += 1 - float(s[i+1])
		i += 2
fw.close()

with open(result, "w") as fw:
	for key in count.keys():
		if count[key]:
			fw.write(key[0] + "\t" + key[1] + "\t" + str(dis[key]/count[key]) + "\n")

