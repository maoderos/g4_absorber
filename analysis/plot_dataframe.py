import pandas as pd 
import matplotlib.pyplot as plt 
import numpy as np 

#angle = [2.5,3,4,7]
angle=[7.0]

# load dataframe
df = pd.read_csv("sim_dataframe.csv")

# position

plt.figure(figsize=(15, 5))
plt.title("Kinetic_energy_plot")

plt.subplot(121)

for i in angle:
    df_filt = df[(df['angle'] == i) & (df['pz1_mean'] > 2.0)]
    plt.plot(df_filt["pz1_mean"],df_filt["x2_std"], 'o',label=r'$\alpha$ = {0}'.format(i))
    plt.ylabel(r"$\sigma_x$")
    plt.xlabel("pz")
    plt.legend()

plt.subplot(122)


for i in angle:
    df_filt = df[(df['angle'] == i) & (df['pz1_mean'] > 2.0)]
    y = df_filt["y2_mean"] - df_filt["y1_mean"]
    plt.plot(df_filt["pz1_mean"],df_filt["y2_std"], 'o',label=r'$\alpha$ = {0}'.format(i))
    plt.ylabel(r"$\sigma_y$")
    plt.xlabel("pz")
    plt.legend()

    
plt.subplots_adjust(top = 0.92,
                   bottom = 0.08,
                   left = 0.1,
                   hspace = 0.55,
                   wspace=0.5)

plt.title("Position plots")
plt.savefig("xy_plot.pdf")

# Kinetic energy

plt.figure()

for i in angle:
    df_filt = df[(df['angle'] == i) & (df['pz1_mean'] > 2.0)]
    y = abs(df_filt["kinEn2_mean"] - df_filt["kinEn1_mean"])
    plt.plot(df_filt["pz1_mean"],y, 'o',label=r'$\alpha$ = {0}'.format(i))
    plt.ylabel(r"$\Delta K$")
    plt.xlabel("pz")
    plt.legend()

    
plt.subplots_adjust(top = 0.92,
                   bottom = 0.08,
                   left = 0.1,
                   hspace = 0.55,
                   wspace=0.5)

plt.savefig("Ken_plot.pdf")


# Pz,Py,Pz, N



# angle





