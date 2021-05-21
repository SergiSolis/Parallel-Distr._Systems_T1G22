import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

procs = [1, 2, 4, 8, 16]
axis = [str(procs[i]) for i in range(len(procs))]

times_case1 = [1.0,1.0,1.0,1.0,1.0]
times_case2 = [1.0,0.9,0.8,0.7,0.6]

ideal_speedup = procs
experimental_speedup_case1 = [ times_case1[0]/x for x in times_case1 ]
experimental_speedup_case2 = [ times_case2[0]/x for x in times_case2 ]

fig, ax = plt.subplots()

ax.set_xlabel('processes')
ax.set_ylabel('speedup')
ax.set_title('speedup')
ax.set_xscale('log', basex=2)
ax.set_yscale('log', basey=2)

plt.plot(procs, ideal_speedup, label='ideal')
plt.plot(procs, experimental_speedup_case1, label="pi code. continuous distr.")
plt.plot(procs, experimental_speedup_case2, label="pi code. distr. with gaps")
ax.legend(loc='upper left')

ax.yaxis.set_major_formatter(ticker.FuncFormatter(lambda y,pos: ('{{:.{:1d}f}}'.format(int(np.maximum(-np.log10(y),0)))).format(y)))
ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda y,pos: ('{{:.{:1d}f}}'.format(int(np.maximum(-np.log10(y),0)))).format(y)))


plt.savefig("speedup.png")
