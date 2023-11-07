import numpy as np
import scipy
import matplotlib.pyplot as plt
import math
import pandas as pd


df = pd.read_csv("data.csv")
df["inner"] = 2*df["inner"]*10**-2
df["outer"] = 2*df["outer"]*10**-2
df["length"] = df["length"]*10**-2
df["height"] = df["height"]*10**-2
df["width"] = df["width"]*10**-2

hollow_df = df[
    (df["length"] == 150*10**-2) & 
    (df["angle"] == 5.25) & 
    (df["outer"] == 2*4*10**-2)
    ]
print(hollow_df)
hollow_df = hollow_df.drop(17)
hollow_df = hollow_df.drop(0)

solid_df = df[
    (df["length"] == 150*10**-2) & 
    (df["angle"] == 5.25) & 
    (df["inner"] == 0) 
    ]



k_s = [dfi["time"]/math.sqrt(dfi["length"]*math.sin(dfi["angle"] * np.pi / 180.)* scipy.constants.g) for index, dfi in solid_df.iterrows()]
k_s_avg = np.average(k_s)
k_s_std = math.sqrt(1/(len(k_s)*(len(k_s)-1))*sum([(x-k_s_avg)**2 for x in k_s]))

k_h = [dfi["time"]/math.sqrt(dfi["length"]*math.sin(dfi["angle"] * np.pi / 180. )* scipy.constants.g)*dfi["inner"]**2/dfi["outer"]**2 for index, dfi in hollow_df.iterrows()]
k_h_avg = sum(k_h)/len(k_h)
k_h_std = math.sqrt(1/(len(k_h)*(len(k_h)-1))*sum([(x-k_h_avg)**2 for x in k_h]))

print("k_s:",k_s)
print("k_s_avg:",k_s_avg)
print("k_s_std:",k_s_std)

print("k_h:",k_h)
print("k_h_avg:",k_h_avg)
print("k_h_std:",k_h_std)


print()