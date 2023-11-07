import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Read data from csv file
df = pd.read_csv("a-data.csv")

# Get linear regression line
m, b = np.polyfit(df["temp"], df["res"], 1)

# Plot data in graph
## Create and plot line from (0*m+b, 0) to (100, 100*m+b)
plt.plot([0, 100], [0*m+b, 100*m+b], "--.", color="red", label = "Linjär anpassning")
## Scatter the data into graph
plt.scatter(df["temp"], df["res"], label = "Data")

# Set labels
plt.title("Resistans och temperatur av ett järnprov")
plt.xlabel("Temperatur (◦C)")
plt.ylabel("Resistans (Ω)")
plt.legend(loc='upper left')

# Set limits
plt.xlim((0,100))
plt.ylim((5,8))

# Add 5.2 tick to vertical axle
plt.yticks(np.append(plt.yticks()[0], 5.2))

print("Resistans vid 0◦C: {}".format(0*m+b))
print(f"Slope: {m:.2f}")

# Show graph
plt.show()
