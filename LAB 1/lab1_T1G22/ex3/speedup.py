import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

cores = [1, 2, 4, 8, 16]
axis = [str(cores[i]) for i in range(len(cores))]

times_case1 = [1.195749,0.612853,0.350251,0.178575,0.102071]
times_case2 = [1.204177,0.602798,0.305378,0.150893,0.075828]
times_case3 = [1.215422,0.608129,0.308467,0.15208,0.076178]
times_case4 = [1.203511,0.602032,0.305212,0.150697,0.07544]
times_case5 = [1.204272,0.621136,0.305287,0.150923,0.07547]
times_case6 = [1.20645,0.621145,0.305748,0.150894,0.075576]

ideal_speedup = cores
experimental_speedup_case1 = [ times_case1[0]/x for x in times_case1 ]
experimental_speedup_case2 = [ times_case2[0]/x for x in times_case2 ]
experimental_speedup_case3 = [ times_case3[0]/x for x in times_case3 ]
experimental_speedup_case4 = [ times_case4[0]/x for x in times_case4 ]
experimental_speedup_case5 = [ times_case5[0]/x for x in times_case5 ]
experimental_speedup_case6 = [ times_case6[0]/x for x in times_case6 ]

fig, ax = plt.subplots()

ax.set_xlabel('cores')
ax.set_ylabel('speedup')
ax.set_title('speedup')
ax.set_xscale('log', basex=2)
ax.set_yscale('log', basey=2)

plt.plot(cores, ideal_speedup, label='ideal')
plt.plot(cores, experimental_speedup_case1, label="static")
plt.plot(cores, experimental_speedup_case2, label="static 1")
plt.plot(cores, experimental_speedup_case3, label="dynamic")
plt.plot(cores, experimental_speedup_case4, label="dynamic 2")
plt.plot(cores, experimental_speedup_case5, label="guided")
plt.plot(cores, experimental_speedup_case6, label="guided 2")
ax.legend(loc='upper left')

ax.yaxis.set_major_formatter(ticker.FuncFormatter(lambda y,pos: ('{{:.{:1d}f}}'.format(int(np.maximum(-np.log10(y),0)))).format(y)))
ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda y,pos: ('{{:.{:1d}f}}'.format(int(np.maximum(-np.log10(y),0)))).format(y)))


plt.savefig("speedup_ex3.png")
