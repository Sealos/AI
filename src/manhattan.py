k = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
val = [[0 for x in k] for x in k] 
for i in k:
	for j in k:
		x = (i) % 4
		y = (i) / 4
		xs = (j) % 4
		ys = (j) / 4
		val[i][j] = abs(x - xs) + abs(y - ys)

print val