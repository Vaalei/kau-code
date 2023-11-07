import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math

# Create subplots in figure
fig, (ax1, ax2) = plt.subplots(2, 1)

# Read data from csv file
df = pd.read_csv("b-data.csv")
# Create new data column using log values from amount
df["log_amount"] = np.log(df["amount"])

# Plot data in graph
ax1.scatter(df["time"], df["amount"], label = "Data")
ax2.scatter(df["time"], df["log_amount"], label = "Data")

# Use linear regression to calculate m and b values where b = N0 and m = λ
m, b = np.polyfit(df["time"], df["log_amount"], 1)

# Plot data from linear regression
ax2.axline((0, b), slope=m, color="red", linestyle=(0, (5, 5)), label = "Linjär anpassning")

# formula: math.exp(b)*math.exp(m*x)
ax1.plot(np.arange(0, math.ceil(df["time"].iloc[-1]), 0.02), 
        [math.exp(b)*math.exp(m*t) for t in np.arange(0, math.ceil(df["time"].iloc[-1]), 0.02)], 
        "--", color = "red")

# Calculate half-life using  th = log(2)/λ
halflife = abs(np.log(2)/m)
print(f"Halveringstid: {halflife:.2f} dagar")

# Set labels
fig.suptitle("Radioaktivt sönderfall")
ax1.set(ylabel='Mängd(kg)')
ax2.set(xlabel='Tid(d)', ylabel='log(Mängd(kg))')

# Set limits
ax1.set_xlim((0,20))
ax1.set_ylim((0,550))
ax2.set_xlim((0,20))

# Show graph
plt.show()
fig.savefig("b-figure.png")