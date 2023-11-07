import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import math
import sklearn.metrics as skm

df = pd.read_csv("data.csv")
df["inner"] = df["inner"]*10**-2
df["outer"] = df["outer"]*10**-2
df["length"] = df["length"]*10**-2
df["height"] = df["height"]*10**-2
df["width"] = df["width"]*10**-2



def createFig(x, y, title, xlabel, ylabel, filename, functionNumber, varName, expName, loglog = True, base = False, largek = False):
    print(x)
    print(y)

    logx = np.log(x)
    if base:
        logy = np.log(y-base)
    else:
        logy = np.log(y)

    print(logx)
    print(logy)

    fig, (ax1, ax2)= plt.subplots(2,1, figsize=(6, 6))


    # Plot datapoints
    ax1.scatter(x, y, label = "Data")
    if base:
        ax1.axline((0, 1.812), slope=0, color="green", label = "Ts")
    
    ax2.scatter(logx, logy, label = "Data")
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

    if not base:
        ax1.plot(np.arange(math.floor(x.min()), math.ceil(x.max()), (x.max()-x.min())/5000), 
            [k*i**n for i in np.arange(math.floor(x.min()), math.ceil(x.max()), (x.max()-x.min())/5000)], 
            "--", color = "red", label = "Regressionline")
    
    
    ax2.axline((0, b), slope=m, color="red", linestyle="--", label = "Regressionline")

    # Set labels and legend
    fig.suptitle(title)
    ax1.set(xlabel=xlabel, ylabel=ylabel)
    ax1.legend(loc='upper right')
    if loglog:
        ax2.set(xlabel=f"log({xlabel})", ylabel=f"log({ylabel if not base else '(Ti-Ts)/s'})")
    else:
        ax2.set(xlabel=xlabel, ylabel=f"log({ylabel if not base else '(Ti-Ts)/s'})")
    ax2.legend(loc='upper right')
    

    # Set textboxes
    props = dict(boxstyle='round', facecolor='white', alpha=0.25)
    ktext = "K" if largek else "k"
    textstr1 = "".join((
        f"f{functionNumber} = {ktext}{functionNumber}*{varName}^{expName}\n",
        f"{ktext}{functionNumber} = {k:.3f} \n", 
        f"{expName} = {n:.3f} \n", 
        f"R^2: {calcr2(x, y):.3f}"
        ))
    textstr2 = "".join((
        f"ln(f{functionNumber}) = ln({ktext}{functionNumber})+{expName}*ln({varName})\n",
        f"{ktext}{functionNumber} = {k:.3f} \n", 
        f"{expName} = {n:.3f}"
        ))
    
    ax1.text(0.03, 0.95, textstr1, transform=ax1.transAxes,
        verticalalignment='top', bbox=props)
    
    ax2.text(0.03, 0.95, textstr2, transform=ax2.transAxes,
        verticalalignment='top', bbox=props)



    ax1.title.set_text("First plot")
    ax2.title.set_text("Second plot")
    fig.tight_layout()

    # Set limits
    ax1.set_xlim([x.min() - (x.mean()/x.size/2), x.max() + (x.mean()/x.size/2)])
    ax1.set_ylim([y.min() - (y.mean()/y.size/2), y.max() + (y.mean()/y.size/2)])
    if loglog:
        ax2.set_xlim([logx.min() - ((logx.max()-logx.min())/logx.size), logx.max() + ((logx.max()-logx.min())/logx.size)])
    else:
        ax2.set_xlim([x.min() - ((x.max()-x.min())/x.size), x.max() + ((x.max()-x.min())/x.size)])
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


inner_df = df[
    (df["length"] == 150*10**-2) & 
    (df["angle"] == 5.25) & 
    (df["outer"] == 4*10**-2)
    ]
inner_df = inner_df.drop(17)
inner_df = inner_df.drop(0)

outer_df = df[
    (df["length"] == 150*10**-2) & 
    (df["angle"] == 5.25) & 
    (df["inner"] == 2*10**-2) 
    ]
outer_df = outer_df.drop(3)

length_df = df[
    (df["angle"] == 5.25) & 
    (df["inner"] == 0*10**-2) & 
    (df["outer"] == 4*10**-2)
    ]

angle_df = df[
    (df["length"] == 150*10**-2) & 
    (df["outer"] == 4*10**-2) & 
    (df["inner"] == 0*10**-2) 
    ]
solid_df = df[
    (df["length"] == 150*10**-2) & 
    (df["angle"] == 5.25) & 
    (df["inner"] == 0) 
    ]

# t = k * l^a * sin(alpha)^b * (R-r)^c
print(solid_df)
innerbase = [1.839,1.856,1.895,1.99]
outerbase = 1.839


createFig(
    2*solid_df["outer"],solid_df["time"], 
    "Time (T-Ts) depending on Outer radius of a solid cylinder", 
    "Outer diameter (l/m)", 
    "Time (t/s)", 
    "solid_figure.png",
    3,
    "Ds",
    "f",
)
createFig(
    2*inner_df["inner"],inner_df["time"], 
    "Time (T-Ts) depending on Inner radius of a hollow cylinder", 
    "Inner diameter (l/m)", 
    "Time (t/s)", 
    "inner_figure.png",
    1,
    "Di",
    "c",
    base = innerbase,
    largek=True
)
createFig(
    2*outer_df["outer"],outer_df["time"], 
    "Time (T-Ts) depending on Outer radius of a hollow cylinder", 
    "Outer diameter (l/m)", 
    "Time (t/s)", 
    "outer_figure.png",
    2,
    "Do",
    "d",
    base = outerbase,
    largek=True
)
createFig(
    np.abs(np.sin(angle_df["angle"]*np.pi / 180.)),angle_df["time"], 
    "Time depending on angle", 
    "Angle (degrees)", 
    "Time (t/s)", 
    "angle_figure.png",
    1,
    "sin(α)",
    "a"
)
createFig(
    length_df["length"],length_df["time"], 
    "Time depending on length", 
    "Length (cm)", 
    "Time (t/s)", 
    "length_figure.png",
    2,
    "l",
    "b"
)