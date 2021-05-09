import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

cores = [1, 2, 4, 8, 16]
axis = [str(cores[i]) for i in range(len(cores))]

times_case1 = [0.608571,0.305467,0.152663,0.077339,0.038933]
times_case2 = [0.849875,0.414260,0.207567,0.096535,0.048264]

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
plt.plot(cores, experimental_speedup_case1, label="case for")
plt.plot(cores, experimental_speedup_case2, label="case no for")
ax.legend(loc='upper left')

ax.yaxis.set_major_formatter(ticker.FuncFormatter(lambda y,pos: ('{{:.{:1d}f}}'.format(int(np.maximum(-np.log10(y),0)))).format(y)))
ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda y,pos: ('{{:.{:1d}f}}'.format(int(np.maximum(-np.log10(y),0)))).format(y)))


plt.savefig("speedup.png")
