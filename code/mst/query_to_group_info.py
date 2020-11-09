import sys

if len(sys.argv) < 3:
	print "query.out\tresult"
	exit()

query_out = sys.argv[1]
result = sys.argv[2]
if result == "query_mst_to_group_info.py":
	exit()

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
fw = open("query.group", "w")
with open(query_out) as fr:
	while True:
		try:
			line = fr.next().strip()
			s = line.split()
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
		except StopIteration:
			break
fw.close()

with open(result, "w") as fw:
	for key in count.keys():
		if count[key]:
			fw.write(key[0] + "\t" + key[1] + "\t" + str(dis[key]/count[key]) + "\n")

