import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression

info = pd.read_csv(f'debug/liquid256disp9.txt')
X = np.array(info['Time']).reshape(-1, 1)
y = np.array(info['Metric'])
reg = LinearRegression().fit(X, y)
print(reg.coef_ / 6)