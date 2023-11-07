import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math

# Read data from csv file
df = pd.read_csv("testing-data.csv")

df["logx"] = np.log(df["x"])
df["logy"] = np.log(df["y"])

# Get linear regression line
m, b = np.polyfit(df["logx"], df["logy"], 1)

# Plot data in graph
plt.axline((0, b), slope=m, color="red", linestyle=(0, (5, 5)), label = "Linjär anpassning")

## Scatter the data into graph
plt.scatter(df["logx"], df["logy"], label = "Data")

print(f"Start val: {b:.2f}")
print(f"Slope: {m:.2f}")
print("ln(y)/ln()x: {:.2f}".format(df["logy"].sum()/df["logx"].sum()))
print("k: {}".format(math.exp(b))) # e^(lnk)



# Show graph
plt.show()
