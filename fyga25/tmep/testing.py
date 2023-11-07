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

outerbase = df[
    (df["length"] == 150*10**-2) & 
    (df["angle"] == 5.25) & 
    (df["inner"] == 2*2*10**-2)
    ]
outerbase = outerbase.drop(3)

outerbase["angle"] = np.abs(np.sin(outerbase["angle"]*np.pi / 180.))
print(outerbase["angle"])

lst = [math.sqrt((dfi["length"])/(dfi["angle"]*9.82))*1.64 for index, dfi in outerbase.iterrows()]
print(lst)

