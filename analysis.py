import matplotlib.pyplot as plt
import numpy as np
import subprocess
from time import time
import math

# set style
plt.style.use('fivethirtyeight')

dims = [512, 513, 1024, 1025]
# dims = [1024, 1025]
# dims = [128]
n_trials = 3
n_dims = len(dims)
# n_dims = 1

times = [[[] for x in range(n_trials)] for z in range(n_dims)]

for i in range(n_dims):
	n = dims[i]
	for j in range(n_trials):
		print("simulating")
		call(["./simulate", str(n), "1", "test.txt"])
		print("done\n\nTrial #{}".format(j+1))
		for k in [x for x in range(1, n) if x % 10 == 0]:
			if k % 250 == 0:
				print("iteration",k)
			cmd = ["./strassen", str(k), str(n), "test.txt"]
			proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
			output = proc.stdout.read()
			# times[i][j].append(call(["./strassen", str(k), str(n), "test.txt"]))
			# print("line", output.decode("utf-8"))
			if output[:-2].decode("utf-8") != "":
				times[i][j].append(float(output[:-2].decode("utf-8")))
			# print(output[:-2].decode("utf-8"))


plt.figure(figsize = (8,8))
for i in range(n_dims):
	n = dims[i]
	plt.subplot(2,2,i + 1)
	trials = times[i]
	plt.plot([x for x in range(1, n) if x % 10 == 0], [np.mean(x) for x in np.array(trials).T], lw = 1)

plt.show()