from scipy import optimize
import numpy as np 
import os 
import glob
import matplotlib.pyplot as plt
import math 
import pandas as pd
import seaborn as sns	

#parâmetros de entreada 
#phi = [30, 60,90]
phi = [45,60,90]
pz1 = [2.5,3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9,9.5]
alpha = [3,5,7,9]

#get without B data

drt = os.getcwd()

data_p = pd.read_csv("{0}/0T/data_plus.dat".format(drt), sep='\s+', header=None,
             engine='python',
            names=['E1','E2_med','Sigma_E2','x1','y1','z1','x2','y2','z2','Sigma_x2','Sigma_y2','Sigma_z2','x_bar','y_bar','z_bar', 'alpha','phi', 'pz' ,'pzmed','N'])
data_p["B"] = 0
data_m = pd.read_csv("{0}/0T/data_minus.dat".format(drt),  sep='\s+', header=None,
            engine='python',
            names=['E1','E2_med','Sigma_E2','x1','y1','z1','x2','y2','z2','Sigma_x2','Sigma_y2','Sigma_z2','x_bar','y_bar','z_bar', 'alpha','phi', 'pz' ,'pzmed','N'])
data_m["B"] = 0
#get with B data


data_p_b = pd.read_csv("{0}/0.5T/data_plus.dat".format(drt), sep='\s+', header=None,
             engine='python',
            names=['E1','E2_med','Sigma_E2','x1','y1','z1','x2','y2','z2','Sigma_x2','Sigma_y2','Sigma_z2','x_bar','y_bar','z_bar', 'alpha','phi', 'pz','pzmed','N'])
data_p_b["B"] = 1
data_m_b = pd.read_csv("{0}/0.5T/data_minus.dat".format(drt),  sep='\s+', header=None,
            engine='python',
            names=['E1','E2_med','Sigma_E2','x1','y1','z1','x2','y2','z2','Sigma_x2','Sigma_y2','Sigma_z2','x_bar','y_bar','z_bar', 'alpha','phi', 'pz','pzmed','N'])
data_m_b["B"] = 1

def test_func(x, a, b):
    return a + b*x

pz1_red = [2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5]
fig = plt.figure(figsize=(10,10))
j= 0
for i in alpha:
   j +=1
   plt.subplot(2,2,j)
   df_alpha_p_b =  data_p_b[(data_p_b["alpha"] == i)& (data_p_b["phi"] == 45) ]
   df_alpha_p =  data_p[(data_p["alpha"] == i)& (data_p["phi"] == 45)]
   params, params_covariance = optimize.curve_fit(test_func, df_alpha_p["E2_med"], df_alpha_p_b["E2_med"],
                                               p0=[1, 1])
   
   sns.lineplot(x=df_alpha_p["E2_med"], y=test_func(df_alpha_p["E2_med"], params[0], params[1]),
         label=r'Fit $\alpha$ = {0}'.format(i))
   sns.scatterplot(x=df_alpha_p["E2_med"], y=df_alpha_p_b["E2_med"],label= r'$\alpha$ = {0}'.format(i), marker="+")
   plt.legend(loc="best",fontsize=8)

plt.tight_layout()
plt.savefig("E2_bXE2_fit.pdf", dpi=1000)
fig, ax1 = plt.subplots()
#plt.set_title("mu+")

fig = plt.figure(figsize=(10,10))
for i in alpha:
   
   df_alpha_p_b =  data_p_b[(data_p_b["alpha"] == i)& (data_p_b["phi"] == 45) ]
   df_alpha_p =  data_p[(data_p["alpha"] == i)& (data_p["phi"] == 45)]
   params, params_covariance = optimize.curve_fit(test_func, df_alpha_p["E2_med"], df_alpha_p_b["E2_med"],
                                               p0=[1, 1])
   
   sns.lineplot(x=df_alpha_p["E2_med"], y=test_func(df_alpha_p["E2_med"], params[0], params[1]),
         label=r'Fit $\alpha$ = {0}'.format(i))
   sns.scatterplot(x=df_alpha_p["E2_med"], y=df_alpha_p_b["E2_med"],label= r'$\alpha$ = {0}'.format(i), marker="+",)
   plt.legend(loc="best",fontsize=8)

plt.tight_layout()
plt.savefig("E2_bXE2_fit_all.pdf", dpi=1000)
fig, ax1 = plt.subplots()
#ax1.set_title("mu+")





fig = plt.figure(figsize=(10,10))
j= 0
for i in alpha:
   j +=1
   plt.subplot(2,2,j)
   df_alpha_p_b =  data_p_b[(data_p_b["alpha"] == i)& (data_p_b["phi"] == 45) ]
   df_alpha_p =  data_p[(data_p["alpha"] == i)& (data_p["phi"] == 45)]
   params, params_covariance = optimize.curve_fit(test_func, df_alpha_p["pzmed"], df_alpha_p_b["pzmed"],
                                               p0=[1, 1])
   
   sns.lineplot(x=df_alpha_p["pzmed"], y=test_func(df_alpha_p["pzmed"], params[0], params[1]),
         label=r'Fit $\alpha$ = {0}'.format(i))
   sns.scatterplot(x=df_alpha_p["pzmed"], y=df_alpha_p_b["pzmed"],label= r'$\alpha$ = {0}'.format(i), marker="+")
   plt.legend(loc="best",fontsize=8)

plt.tight_layout()
plt.savefig("pz_bXpz_fit.pdf", dpi=1000)
fig, ax1 = plt.subplots()
#ax1.set_title("mu+")

fig = plt.figure(figsize=(10,10))
for i in alpha:
   
   df_alpha_p_b =  data_p_b[(data_p_b["alpha"] == i)& (data_p_b["phi"] == 45) ]
   df_alpha_p =  data_p[(data_p["alpha"] == i)& (data_p["phi"] == 45)]
   params, params_covariance = optimize.curve_fit(test_func, df_alpha_p["pzmed"], df_alpha_p_b["pzmed"],
                                               p0=[1, 1])
   
   sns.lineplot(x=df_alpha_p["pzmed"], y=test_func(df_alpha_p["pzmed"], params[0], params[1]),
         label=r'Fit $\alpha$ = {0}'.format(i))
   sns.scatterplot(x=df_alpha_p["pzmed"], y=df_alpha_p_b["pzmed"],label= r'$\alpha$ = {0}'.format(i), marker="+")
   plt.legend(loc="best",fontsize=8)

plt.tight_layout()
plt.savefig("pz_bXpz_fit_all.pdf", dpi=1000)
fig, ax1 = plt.subplots()


