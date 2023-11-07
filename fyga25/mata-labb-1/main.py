import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math
import sklearn.metrics as skm

df = pd.read_csv("data.csv")

def createFig(x, y, title, xlabel, ylabel, filename, functionNumber, varName, expName):
    logx = np.log(x)
    logy = np.log(y)

    m, b = np.polyfit(logx, logy, 1)
    # ------------ start math soloution ------------
    # f = kl^n
    # ln(f) = ln(k)+n*ln(l)
    ## similar to
    # mx + b = y
    n = m

    # b = ln(k)
    # k = e^ln(b)
    k = math.exp(b)
    # ------------- end math soloution -------------

    fig, (ax1, ax2)= plt.subplots(2,1, figsize=(6, 6))

    # Plot lines
    ax1.plot(np.arange(math.floor(x.min()), math.ceil(x.max()), (x.max()-x.min())/5000), 
        [k*i**n for i in np.arange(math.floor(x.min()), math.ceil(x.max()), (x.max()-x.min())/5000)], 
        "--", color = "red", label = "Regressionline")
    ax2.axline((0, b), slope=m, color="red", linestyle="--", label = "Regressionline")

    # Plot datapoints
    ax1.scatter(x, y, label = "Data")
    ax2.scatter(logx, logy, label = "Data")

    # Set labels and legend
    fig.suptitle(title)
    ax1.set(xlabel=xlabel, ylabel=ylabel)
    ax1.legend(loc='upper right')
    ax2.set(xlabel=f"log({xlabel})", ylabel=f"log({ylabel})")
    ax2.legend(loc='upper right')
    

    props = dict(boxstyle='round', facecolor='white', alpha=0.25)

    textstr1 = "".join((
        f"f{functionNumber} = k{functionNumber}*{varName}^{expName}\n",
        f"k{functionNumber} = {k:.3f} \n", 
        f"{expName} = {n:.3f} \n", 
        f"R^2: {calcr2(x, y):.3f}"
        ))
    textstr2 = "".join((
        f"ln(f{functionNumber}) = ln(k{functionNumber})+{expName}*ln({varName})\n",
        f"k{functionNumber} = {k:.3f} \n", 
        f"{expName} = {n:.3f}"
        ))
    
    # ax1.text(0.03, 0.95, textstr1, transform=ax1.transAxes,
    #     verticalalignment='top', bbox=props)
    
    ax2.text(0.03, 0.95, textstr2, transform=ax2.transAxes,
        verticalalignment='top', bbox=props)

    ax1.title.set_text("First plot")
    ax2.title.set_text("Second plot")
    fig.tight_layout()

    # Set limits
    ax1.set_xlim([x.min() - (x.mean()/x.size/2), x.max() + (x.mean()/x.size/2)])
    ax1.set_ylim([y.min() - (y.mean()/y.size/2), y.max() + (y.mean()/y.size/2)])
    ax2.set_xlim([logx.min() - ((logx.max()-logx.min())/logx.size), logx.max() + ((logx.max()-logx.min())/logx.size)])
    ax2.set_ylim([logy.min() - ((logy.max()-logy.min())/logy.size), logy.max() + ((logy.max()-logy.min())/logy.size)])

    plt.show()
    fig.savefig(filename)

    return fig

def calcr2(x,y):
    model = np.polyfit(x, y, 1)
    predict = np.poly1d(model)
    predicted_Y = predict(x)
    r_square = skm.r2_score(y, predicted_Y)
    return r_square


w_df = df[
    (df["thickness"] == 5.10e-3) & 
    (df["length"] == 0.5)
    ]


t_df = df[
    (df["width"] == 4.10e-2) & 
    (df["length"] == 0.5)
    ]


l_df = df[
    (df["thickness"] == 6.40e-3) & 
    (df["width"] == 4.10e-2)
    ]



print(w_df)
print(t_df)
print(l_df)



createFig(
    l_df["length"],l_df["frequency"], 
    "Frequency depending on Length", 
    "Length (l/m)", 
    "Frequency (f/Hz)", 
    "length-figure.png",
    1,
    "l",
    "x"

)


createFig(
    w_df["width"],w_df["frequency"], 
    "Frequency depending on Width", 
    "Width (l/m)", 
    "Frequency (f/Hz)", 
    "width-figure.png",
    2,
    "w",
    "y"

)

createFig(
    t_df["thickness"],t_df["frequency"], 
    "Frequency depending on Thickness", 
    "Thickness (l/m)", 
    "Frequency (f/Hz)", 
    "thickness-figure.png",
    3,
    "t",
    "z"

)
