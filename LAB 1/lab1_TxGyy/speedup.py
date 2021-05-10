import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

cores = [1, 2, 4, 8, 16]
axis = [str(cores[i]) for i in range(len(cores))]

times_case1 = [1.559899,11.717006,10.572478,9.250940,15.676591]
times_case2 = [0.851890,0.426449,0.215667,0.108237,0.053565]

ideal_speedup = cores
experimental_speedup_case1 = [ times_case1[0]/x for x in times_case1 ]
experimental_speedup_case2 = [ times_case2[0]/x for x in times_case2 ]

fig, ax = plt.subplots()

ax.set_xlabel('cores')
ax.set_ylabel('speedup')
ax.set_title('speedup')
ax.set_xscale('log', basex=2)
ax.set_yscale('log', basey=2)

plt.plot(cores, ideal_speedup, label='ideal')
plt.plot(cores, experimental_speedup_case1, label="synchronized")
plt.plot(cores, experimental_speedup_case2, label="not synchronized")
ax.legend(loc='upper left')

ax.yaxis.set_major_formatter(ticker.FuncFormatter(lambda y,pos: ('{{:.{:1d}f}}'.format(int(np.maximum(-np.log10(y),0)))).format(y)))
ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda y,pos: ('{{:.{:1d}f}}'.format(int(np.maximum(-np.log10(y),0)))).format(y)))


plt.savefig("speedup_ex2.png")
