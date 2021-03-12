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
#plot of E2_B x E2


#Lets concatenate de dataframes

data_p_concat = pd.concat([data_p,data_p_b])
data_m_concat = pd.concat([data_m,data_m_b])


pz1_red = [2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5]
fig, ax1 = plt.subplots()
ax1.set_title("mu+")
for i in alpha:
   df_alpha_p_b =  data_p_b[(data_p_b["alpha"] == i)& (data_p_b["phi"] == 45) ]
   df_alpha_p =  data_p[(data_p["alpha"] == i)& (data_p["phi"] == 45)]
   sns.scatterplot(x=df_alpha_p["E2_med"], y=df_alpha_p_b["E2_med"], ax=ax1,label= r'$\alpha$ = {0}'.format(i), marker="+")
   ax1.plot
   ax1.legend(loc="best",fontsize=5)
   
plt.tight_layout()
plt.savefig("E2_bXE2.pdf", dpi=1000)

fig, ax1 = plt.subplots()
ax1.set_title("mu+")
for i in alpha:
   df_alpha_p_b =  data_p_b[(data_p_b["alpha"] == i)& (data_p_b["phi"] == 45) ]
   df_alpha_p =  data_p[(data_p["alpha"] == i)& (data_p["phi"] == 45)]
   
   sns.scatterplot(x=df_alpha_p["pzmed"], y=df_alpha_p_b["pzmed"], ax=ax1,label= r'$\alpha$ = {0}'.format(i), marker="+")
   ax1.legend(loc="best",fontsize=5)
  
plt.tight_layout()
plt.savefig("pz_bXpz.pdf", dpi=1000)



