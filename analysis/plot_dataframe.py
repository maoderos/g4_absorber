import pandas as pd 
import matplotlib.pyplot as plt 
import numpy as np 

angle = [2.5,3,4,7]


# load dataframe
df = pd.read_csv("sim_dataframeDispersion.csv")

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


# Px,Py,N
plt.figure()
# N
for i in angle:
    df_filt = df[(df['angle'] == i) & (df['pz1_mean'] > 2.0)] 
    plt.plot(df_filt["pz1_mean"],df_filt["N"], 'o',label=r'$\alpha$ = {0}'.format(i))
    plt.ylabel("Number of transmitted particles")
    plt.xlabel("pz")
    plt.legend()

# angle

plt.savefig("n_transmisison.pdf")


# px,py, pz
plt.figure(figsize=(15,10))
plt.subplot(221)

for i in angle:
    df_filt = df[(df['angle'] == i) & (df['pz1_mean'] > 2.0)]
    plt.plot(df_filt["pz1_mean"],df_filt["px2_std"], 'o',label=r'$\alpha$ = {0}'.format(i))
    plt.ylabel(r"$\sigma_{p_x}$")
    plt.xlabel("pz")
    plt.legend()

plt.subplot(222)

for i in angle:
    df_filt = df[(df['angle'] == i) & (df['pz1_mean'] > 2.0)]
    plt.plot(df_filt["pz1_mean"],df_filt["py2_std"], 'o',label=r'$\alpha$ = {0}'.format(i))
    plt.ylabel(r"$\sigma_{p_y}$")
    plt.xlabel("pz")
    plt.legend()

plt.subplot(223)
    
for i in angle:
    df_filt = df[(df['angle'] == i) & (df['pz1_mean'] > 2.0)]
    plt.plot(df_filt["pz1_mean"],df_filt["pz2_std"], 'o',label=r'$\alpha$ = {0}'.format(i))
    plt.ylabel(r"$\sigma_{p_z}$")
    plt.xlabel("pz")
    plt.legend()

plt.subplot(224)

for i in angle:
    df_filt = df[(df['angle'] == i) & (df['pz1_mean'] > 2.0)]
    plt.plot(df_filt["pz1_mean"],df_filt["N"], 'o',label=r'$\alpha$ = {0}'.format(i))
    plt.ylabel("N")
    plt.xlabel("pz")
    plt.legend()
    
plt.subplots_adjust(
                   bottom = 0.08,
                   left = 0.1,
                   wspace=0.5)

plt.savefig("disp_momentum.pdf")


