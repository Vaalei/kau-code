import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math

# Create subplots in figure
fig, (ax1, ax2) = plt.subplots(2, 1)

# Set labels
fig.suptitle("Resistance of a ceramic conductor as a function of current")
ax1.set(xlabel= 'I (A)', ylabel='R (Ω)')
ax2.set(xlabel= 'log(I (A))', ylabel='log(R (Ω))')

# Read data from csv file
df = pd.read_csv("c-data.csv")

# Create new data column using log values from res
df["log_res"] = np.log(df["res"])
df["log_amp"] = np.log(df["amp"])

# Plot data in graph
ax1.scatter(df["amp"], df["res"], label = "Data")
ax2.scatter(df["log_amp"], df["log_res"], label = "Data")

# Use linear regression to calculate m and b values
# mx + b = y
m, b = np.polyfit(df["log_amp"], df["log_res"], 1)
ax2.axline((0, b), slope=m, color="red", linestyle=(0, (5, 5)), label = "Linjär anpassning")

# ------------ start math soloution ------------
# R = kI^n
# ln(R) = ln(k)+n*ln(I)
## similar to
# mx + b = y
n = m

# b = ln(k)
# k = e^ln(b)
k = math.exp(b)
# ------------- end math soloution -------------

print(f"n: {n:.3f}")
print(f"k: {k:.3f}")

ax1.plot(np.arange(0, math.ceil(df["amp"].iloc[-1]), 0.02), 
        [k*i**n for i in np.arange(0, math.ceil(df["amp"].iloc[-1]), 0.02)], 
        "--", color = "red")

# Show graph
plt.show()
fig.savefig("c-figure.png")