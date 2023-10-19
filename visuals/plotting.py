import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

info = pd.read_csv('debug/liquid256temp6.txt')
plt.plot(info['Time'], info['Metric'])
plt.xlabel('Time')
plt.ylabel('x-Momentum')
plt.title('x-Momentum of System over Time')
# plt.ylim(-1059.2, -1059.0)
plt.show()