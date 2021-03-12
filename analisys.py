import numpy as np 
import os 
import glob
import matplotlib.pyplot as plt
import math 
import pandas as pd
import seaborn as sns		


charge = ['plus','minus']

#parâmetros de entreada 
#phi = [30, 60,90]
phi = [45,60,90]
pz1 = [2.5,3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9,9.5]
alpha = [3,5,7,9]

#function that calculates and write in file    
def make_calculus(file1,file2,pz,alpha,data,phi):
    
    #loading files to numpy
    A = np.loadtxt(file1, dtype=float)
    B = np.loadtxt(file2, dtype=float)

    px1,py1,pz1,pxmed,pymed,pzmed, DeltaPx,DeltaPy,DeltaPz,Sigma_px,Sigma_py,Sigma_pz,E1,Sigma_E2,Sigma_x2,Sigma_y2,Sigma_z2 = 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0
    Delta_x,Delta_y,Delta_z,E2_med = 0.0,0.0,0.0,0.0
    x1,y1,z1,x2,y2,z2 = 0.0,0.0,0.0,0.0,0.0,0.0
    N=0
    if A.shape[1] == 1:
        px1,py1,pz1,E1 = A[4],A[5],A[6],A[3]
        x1,y1,z1 = A[0],A[1],A[2]
        
    else:
        px1_arr,py1_arr,pz1_arr,E1_arr = A[:,4],A[:,5],A[:,6],A[:,3]
        px1 = px1_arr[0]; py1 = py1_arr[0]; pz1 = pz1_arr[0]
        E1 = E1_arr[0]
        x1_ar,y1_ar,z1_ar = A[:,0],A[:,1],A[:,2]
        x1 = x1_ar[0]; y1 = y1_ar[0]; z1 = z1_ar[0] 

    if B.shape[1] == 1:
        px2,py2,pz2,E2 = B[4],B[5],B[6],B[3]
        pxmed = px2; pymed = py2; pzmed = pz2; E2_med = E2
        #Sigma_px,Sigma_py,Sigma_pz = 0,0,0
        x2,y2,z2 = B[0],B[1],B[2]

    else:
        px2,py2,pz2,E2 = B[:,4],B[:,5],B[:,6],B[:,3]
        pxmed = np.mean(px2); pymed = np.mean(py2); pzmed = np.mean(pz2)
        E2_med = np.mean(E2)
        N = np.size(px2)
        x2_a,y2_a,z2_a = B[:,0],B[:,1],B[:,2]
        x2 = np.mean(x2_a); y2 = np.mean(y2_a); z2 = np.mean(z2_a) 
        Delta_x = x2 -x1; Delta_y = y2 - y1; Delta_z=z2-z1
        Sigma_px = 3*np.std(px2); Sigma_py = 3*np.std(py2); Sigma_pz = 3*np.std(pz2); Sigma_E2 = 3*np.std(E2)
        #print(Sigma_E2)
        Sigma_x2 = 3*np.std(x2_a); Sigma_y2 = 3*np.std(y2_a); Sigma_z2 = 3*np.std(z2_a)
   
    #print(E1)
    ##calculando Delta
    #DeltaPx = pxmed - px1; DeltaPy = pymed - py1; DeltaPz = pzmed - pz1 
    
    ## x1,y1,z1,x2,y2,z2 
    x_bar = x1 + Delta_z*np.tan(np.deg2rad(alpha))
    y_bar = y1 + Delta_z*np.tan(np.deg2rad(alpha))
    z_bar = z1 + Delta_z*np.tan(np.deg2rad(alpha))

    line = "{0} {1} {2} {3} {4} {5} {6} {7} {8} {9} {10} {11} {12} {13} {14} {15} {16} {17} {18} {19}".format(E1,E2_med,Sigma_E2,x1,y1,z1,x2,y2,z2,Sigma_x2,Sigma_y2,Sigma_z2,x_bar,y_bar,z_bar, alpha,phi, pz,pzmed, N)    
    #print("##########ENERGY {0} ANGLE {1} ###########  in phi = {2}\n".format(pz,alpha,phi))
    #print(line)
    data.write(line + "\n")





#Enter in files and see if one of them is blanck
def enter_files(drt,pz,alpha,phi,data,c):
    filename1 = "{0}/phi{4}/{3}1/Energy{1}_Angle_{2}.dat".format(drt,pz,alpha,c,phi)
    filename2 = "{0}/phi{4}/{3}2/Energy{1}_Angle_{2}.dat".format(drt,pz,alpha,c,phi)
    file1 = open(filename1)
    file2 = open(filename2)
    if(os.stat(filename1).st_size == 0 or os.stat(filename2).st_size==0):
        print("Energy{0}_Angle{1}.dat EM BRANCO - phi = {2}".format(pz,alpha,phi))
        return

    make_calculus(file1,file2, pz,alpha,data,phi)


drt = os.getcwd()
data_plus = open("{0}/data_plus.dat".format(drt), "w")
data_minus = open("{0}/data_minus.dat".format(drt),"w")
files = [data_plus, data_minus]


for phi_i in phi:
   charge_index = 0
   for c in charge:
       for alpha_i in alpha:
           for pz in pz1:
              enter_files(drt,pz,alpha_i,phi_i,files[charge_index],c)  
       charge_index +=1
data_plus.close()
data_minus.close()



## GRAFICOS


dataf_p = pd.read_csv("data_plus.dat", sep='\s+', header=None,
             engine='python',
            names=['E1','E2_med','Sigma_E2','x1','y1','z1','x2','y2','z2','Sigma_x2','Sigma_y2','Sigma_z2','x_bar','y_bar','z_bar', 'alpha','phi', 'pz' ,'pzmed','N'])
dataf_m = pd.read_csv("data_minus.dat",  sep='\s+', header=None,
            engine='python',
            names=['E1','E2_med','Sigma_E2','x1','y1','z1','x2','y2','z2','Sigma_x2','Sigma_y2','Sigma_z2','x_bar','y_bar','z_bar', 'alpha','phi', 'pz' ,'pzmed','N'])
#print(dataf_p)


##Em função de phi
##E2> x E1, SigmaE x E1
for i in phi:
   fig, (ax1, ax2) = plt.subplots(2, 1)
   ax1.set_title("mu+")
   for j in alpha:
      ##<E2> x E1, SigmaE x E1
      df_phi_p =  dataf_p[(dataf_p["phi"] == i) & (dataf_p["alpha"] == j)]
      df_phi_m =  dataf_m[(dataf_m["phi"] == i) & (dataf_m["alpha"] == j)]
      sns.scatterplot(x='E1', y='E2_med', data=df_phi_p, ax=ax1,label= r'$\alpha$ = {0}'.format(j),marker="+")
      
      sns.scatterplot(x='E1', y='Sigma_E2', data=df_phi_p, ax=ax2,label= r'$\alpha$ = {0}'.format(j),marker="+")
       
      ax1.legend(loc="best",fontsize=5)
      ax2.legend(loc="best",fontsize=5)
       

   plt.tight_layout()
   plt.savefig("E{0}.pdf".format(i), dpi=1000)
   #plt.show()
### x_bar e y_bar
pz1_red = [2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5]
for i in phi:
   fig, ((ax1, ax2),(ax3,ax4)) = plt.subplots(2, 2)
   ax1.set_title("mu+")
   ax2.set_title("mu-")
   for j in pz1_red:
      df_phi_p =  dataf_p[(dataf_p["phi"] == i) & (dataf_p["pz"] == j)]
      df_phi_m =  dataf_m[(dataf_m["phi"] == i) & (dataf_m["pz"] == j)]
      sns.scatterplot(x='alpha', y='x_bar', data=df_phi_p, ax=ax1, label= r'$pz$ = {0}'.format(j), marker="+")
      sns.scatterplot(x='alpha', y='x_bar', data=df_phi_m, ax=ax2, label= r'$pz$ = {0}'.format(j), marker="+")
      sns.scatterplot(x='alpha', y='y_bar', data=df_phi_p, ax=ax3, label= r'$pz$ = {0}'.format(j), marker="+")
      sns.scatterplot(x='alpha', y='y_bar', data=df_phi_m, ax=ax4, label= r'$pz$ = {0}'.format(j), marker="+")
      ax1.legend(loc="best",fontsize=5)
      ax2.legend(loc="best",fontsize=5)
      ax3.legend(loc="best",fontsize=5)
      ax4.legend(loc="best",fontsize=5)
      
   plt.tight_layout()
   plt.savefig("xy_bar{0}phi.pdf".format(i), dpi=1000)

## x_bar e y_bar
for i in alpha:
   fig, ((ax1, ax2),(ax3,ax4)) = plt.subplots(2, 2)
   ax1.set_title("mu+")
   ax2.set_title("mu-")
   for j in pz1_red: 
      df_phi_p =  dataf_p[(dataf_p["alpha"] == i)& (dataf_p["pz"] == j)]
      df_phi_m =  dataf_m[(dataf_m["alpha"] == i)& (dataf_m["pz"] == j)]
      sns.scatterplot(x='phi', y='x_bar', data=df_phi_p, ax=ax1,label= r'$pz$ = {0}'.format(j), marker="+")
      sns.scatterplot(x='phi', y='x_bar', data=df_phi_m, ax=ax2,label= r'$pz$ = {0}'.format(j), marker="+")
      sns.scatterplot(x='phi', y='y_bar', data=df_phi_p, ax=ax3,label= r'$pz$ = {0}'.format(j), marker="+")
      sns.scatterplot(x='phi', y='y_bar', data=df_phi_m, ax=ax4,label= r'$pz$ = {0}'.format(j), marker="+")
      ax1.legend(loc="best",fontsize=5)
      ax2.legend(loc="best",fontsize=5)
      ax3.legend(loc="best",fontsize=5)
      ax4.legend(loc="best",fontsize=5)
      
 
   plt.tight_layout()
   plt.savefig("xy_bar{0}alpha.pdf".format(i), dpi=1000)


#arrumar cara
fig, ax1 = plt.subplots()
ax1.set_title("mu+")
for i in alpha:
   df_phi_p =  dataf_p[(dataf_p["alpha"] == i)& (dataf_p["phi"] == 45)]
   sns.scatterplot(x='E1', y='E2_med', data=df_phi_p, ax=ax1,label= r'$\alpha$ = {0}'.format(i), marker="+")
   ax1.legend(loc="best",fontsize=5)   
plt.tight_layout()
plt.savefig("ExE_o_alpha.pdf", dpi=1000)




fig, ax1 = plt.subplots()
ax1.set_title("mu+")
for i in pz1_red:
   df_phi_p =  dataf_p[(dataf_p["pz"] == i)& (dataf_p["phi"] == 45)]
   sns.scatterplot(x='alpha', y='E2_med', data=df_phi_p, ax=ax1,label= r'$Pz$ = {0}'.format(i), marker="+")
   ax1.legend(loc="best",fontsize=5)
   
plt.tight_layout()
plt.savefig("Exalpha.pdf", dpi=1000)

fig, (ax1,ax2) = plt.subplots(1,2)
ax1.set_title("mu+")
ax2.set_title("mu+")
for i in alpha:
   df_phi_p =  dataf_p[(dataf_p["alpha"] == i)& (dataf_p["phi"] == 45)]
   df_phi_m =  dataf_m[(dataf_p["alpha"] == i)& (dataf_p["phi"] == 45)]
   sns.scatterplot(x='E1', y='x1', data=df_phi_p, ax=ax1,label= r'$\alpha$ = {0}'.format(i), marker="+")
   sns.scatterplot(x='E1', y='x1', data=df_phi_m, ax=ax2,label= r'$\alpha$ = {0}'.format(i), marker="+")
   ax1.legend(loc="best",fontsize=5)
   ax2.legend(loc="best",fontsize=5)
plt.tight_layout()
plt.savefig("xxx.pdf", dpi=1000)
