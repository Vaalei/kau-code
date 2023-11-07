import pandas as pd
import numpy as np

df = pd.read_csv("data.csv")

calck = [row["frequency"]*row["length"]**2/row["thickness"] for index, row in df.iterrows()]
print(calck)
print("Average", np.average(calck))
print("Standard deviation:", np.std(calck))