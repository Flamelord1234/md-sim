import matplotlib.pyplot as plt
import pandas as pd

run = 'liquid256'
metric = 'temp10'

info = pd.read_csv(f'debug/{run}{metric}.txt')
plt.plot(info['Time'], info['Metric'])
plt.xlabel('Time')
plt.ylabel(f'{metric}')
plt.title(f'{metric} over Time')
# plt.ylim(-1059.2, -1059.0)
plt.show()