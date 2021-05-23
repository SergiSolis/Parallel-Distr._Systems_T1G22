import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

procs = [1, 2, 4, 8, 16]
axis = [str(procs[i]) for i in range(len(procs))]

times_case1 = [0.4121,0.2064,0.1039,0.0522,0.0258]
times_case2 = [0.3889,0.1948,0.0987,0.0490,0.0244]

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
