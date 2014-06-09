k = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24]
val = [[0 for x in k] for x in k]
for i in k:
	for j in k:
		x = (i) % 5
		y = (i) / 5
		xs = (j) % 5
		ys = (j) / 5
		val[i][j] = abs(x - xs) + abs(y - ys)

print val
