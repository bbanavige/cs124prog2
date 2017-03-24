import matplotlib.pyplot as plt
import numpy as np
import subprocess
from time import time
import math
from scipy import signal
from subprocess import call

# set style
plt.style.use('fivethirtyeight')

dims = [512, 513, 1024, 1025]
# dims = [1024, 1025]
# dims = [128]
n_trials = 4
n_dims = len(dims)
# n_dims = 1

times = [[[] for x in range(n_trials)] for z in range(n_dims)]

# for i in range(n_dims):
# 	n = dims[i]
# 	for j in range(n_trials):
# 		print("simulating")
# 		call(["./simulate", str(n), "1", "test.txt"])
# 		print("done\n\nTrial #{}".format(j+1))
# 		for k in [x for x in range(1, n) if x % 10 == 0]:
# 			if k % 250 == 0:
# 				print("iteration",k)
# 			cmd = ["./strassen", str(k), str(n), "test.txt"]
# 			proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
# 			output = proc.stdout.read()
# 			# times[i][j].append(call(["./strassen", str(k), str(n), "test.txt"]))
# 			# print("line", output.decode("utf-8"))
# 			if output[:-2].decode("utf-8") != "":
# 				times[i][j].append(float(output[:-2].decode("utf-8")))
# 			# print(output[:-2].decode("utf-8"))

for i in range(n_dims):
	n = dims[i]
	for j in range(n_trials):
		print("simulating")
		call(["./simulate", str(n), "1", "test.txt"])
		print("done\n\nTrial #{}".format(j+1))
		for k in [2 ** x + 1 for x in range(4, int(math.log2(n)) + 1)]:
			print("iteration",k)
			cmd = ["./strassen", str(k), str(n), "test.txt"]
			proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
			output = proc.stdout.read()
			# times[i][j].append(call(["./strassen", str(k), str(n), "test.txt"]))
			# print("line", output.decode("utf-8"))
			# if output[:-2].decode("utf-8") != "":
			times[i][j].append(float(output[:-2].decode("utf-8")))
			# print(output[:-2].decode("utf-8"))

titles = ["512 (even)", "513 (odd)", "1024 (even)", "1025 (odd)"]

plt.rcParams['ytick.labelsize'] = 8

plt.figure(figsize = (8,8))
for j,i in enumerate([0, 2, 3]):
	n = dims[i]
	trials = times[i]
	smooth = scipy.signal.savgol_filter([np.mean(x) for x in np.array(trials).T], 5, 3)
	plt.subplot(3,1,j + 1)
	plt.plot([x for x in range(1, n) if x % 10 == 0], smooth, lw = 1, color = 'blue', label = 'Smoothed')
	plt.title(titles[i], fontsize = 12)
	# plt.plot([x for x in range(1, n) if x % 10 == 0],[np.mean(x) for x in np.array(trials).T], lw = 1, color = 'red', label = 'Actual')

plt.show()

plt.figure(figsize = (12,6))
for i in range(n_dims):
	n = dims[i]
	trials = times[i]
	smooth = signal.savgol_filter([np.mean(x) for x in np.array(trials).T], 5, 3)
	plt.subplot(2,2,i + 1)
	plt.plot([2 ** x + 1 for x in range(4, int(math.log2(n)) + 1)], smooth, lw = 1, color = 'blue', label = 'Smoothed')
	plt.title(titles[i])
	# plt.plot([x for x in range(1, n) if x % 10 == 0],[np.mean(x) for x in np.array(trials).T], lw = 1, color = 'red', label = 'Actual')

min_vals = [np.argmin(x) for x in np.array(trials).T]

plt.show()









