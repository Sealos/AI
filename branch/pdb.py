def calcular_manhattan( val1,  val2,  val3,  val4,  pos1,  pos2,  pos3,  pos4):
	val = 0;

	if (val1 != 0):
		x = (val1) % 4;
		y = (val1) / 4;
		xs = (pos1) % 4;
		ys = (pos1) / 4;
		val += abs(x - xs) + abs(y - ys);

	if (val2 != 0):
		x = (val2) % 4;
		y = (val2) / 4;
		xs = (pos2) % 4;
		ys = (pos2) / 4;
		val += abs(x - xs) + abs(y - ys);

	if (val3 != 0):
		x = (val3) % 4;
		y = (val3) / 4;
		xs = (pos3) % 4;
		ys = (pos3) / 4;
		val += abs(x - xs) + abs(y - ys);
	
	if (val4 != 0):
		x = (val4) % 4;
		y = (val4) / 4;
		xs = (pos4) % 4;
		ys = (pos4) / 4;
		val += abs(x - xs) + abs(y - ys);

	return val;


r = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
m = [0,1,2,3]
val = [[[[[0 for x in m] for x in r] for x in r] for x in r] for x in r]
for i in r:
	for j in r:
		if i != j:
			for k in r:
				if k != j and k != i:
					for l in r:
						if l != k and l != j and l != i:
							val[i][j][k][l][0] = calcular_manhattan(i, j, k, l, 0, 1, 4, 5);
							val[i][j][k][l][1] = calcular_manhattan(i, j, k, l, 2, 3, 6, 7);
							val[i][j][k][l][2] = calcular_manhattan(i, j, k, l, 8, 9, 12, 13);
							val[i][j][k][l][3] = calcular_manhattan(i, j, k, l, 10, 11, 14, 15);
							#print "{"+str(i)+", "+str(j)+", "+str(k)+", "+str(l)+"}, {"+str(val[i][j][k][l][0])+", "+str(val[i][j][k][l][1])+", "+str(val[i][j][k][l][2])+", "+str(val[i][j][k][l][3])+"}"

print val
