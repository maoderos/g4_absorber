import numpy as np
import pandas as pd
import os



def analyze_file(filename,angle_i,columns):
    # arrays from detector 1 (SD1)
    x1,y1,px1,py1,pz1,kinEn1 = np.loadtxt("results/SD1/" + filename, unpack=True,dtype=np.float128)
    x2,y2,px2,py2,pz2,kinEn2 = np.loadtxt("results/SD2/" + filename, unpack=True,dtype=np.float128)
    
    ## MEAN

    x1_mean = np.mean(x1); y1_mean = np.mean(y1); px1_mean = np.mean(px1); py1_mean = np.mean(py1)
    pz1_mean = np.mean(pz1); kinEn1_mean = np.mean(kinEn1)
    
    x2_mean = np.mean(x2); y2_mean = np.mean(y2); px2_mean = np.mean(px2); py2_mean = np.mean(py2)
    pz2_mean = np.mean(pz2); kinEn2_mean = np.mean(kinEn2)
    
    ## STD
    
    x1_std = np.std(x1); y1_std = np.std(y1); px1_std = np.std(px1); py1_std = np.std(py1)
    pz1_std = np.std(pz1); kinEn1_std = np.std(kinEn1)
    
    x2_std = np.std(x2); y2_std = np.std(y2); px2_std = np.std(px2); py2_std = np.std(py2)
    pz2_std = np.std(pz2); kinEn2_std = np.std(kinEn2)
    

    new_row = {'x1_mean':x1_mean, 'x1_std':x1_std, 'x2_mean':x2_mean, 'x2_std':x2_std, 
              'y1_mean':y1_mean, 'y1_std':y1_std, 'y2_mean':y2_mean, 'y2_std':y2_std,
              'px1_mean':px1_mean, 'px1_std':px1_std, 'px2_mean':px2_mean, 'px2_std':px2_std,
              'py1_mean':py1_mean, 'py1_std':py1_std, 'py2_mean':py2_mean, 'py2_std':py2_std,
               'pz1_mean':pz1_mean, 'pz1_std':pz1_std, 'pz2_mean':pz2_mean, 'pz2_std':pz2_std,
              'kinEn1_mean':kinEn1_mean, 'kinEn1_std':kinEn1_std, 'kinEn2_mean':kinEn2_mean,
              'kinEn2_std':kinEn2_std, 'angle':angle_i}
    '''
    line = "{0} {1} {2} {3} {4} {5} {6} {7} {8} {9} {10} {11} {12} {13} {14} {15} {16} {17} {18} {19} {20}\n".format(x1_mean,x1_std,x2_mean,x2_std,
                                                                                                                     y1_mean,y1_std,y2_mean,y2_std,
                                                                                                                     px1_mean,px1_std,px2_mean,px2_std,
                                                                                                                    py1_mean,py1_std,py2_mean,py2_std,
                                                                                                                    kinEn1_mean,kinEn1_std,kinEn2_mean,
                                                                                                                    kinEn2_std, angle)
                                                                                                                   
    file.write(line)
    
    pd.Series([x1_mean,x1_std,x2_mean,x2_std,y1_mean,y1_std,
                     y2_mean,y2_std,px1_mean,px1_std,px2_mean,px2_std,
                     py1_mean,py1_std,py2_mean,py2_std,kinEn1_mean,kinEn1_std,
                     kinEn2_mean,kinEn2_std], index=columns)
    '''
    return new_row


particle = ['mu+']
pz = [1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,7.5,8,8.5,9,9.5]
#angle = [2.5,3,4,7]
angle=[7]
detectors = ["SD1", "SD2"]

# creating a blank dataframe 
column = {"x1_mean","x1_std","x2_mean","x2_std","y1_mean","y1_std",
                     "y2_mean","y2_std","px1_mean","px1_std","px2_mean","px2_std",
                     "py1_mean","py1_std","py2_mean","py2_std","pz1_mean","pz1_std","pz2_mean","pz2_std",
                     "kinEn1_mean","kinEn1_std","kinEn2_mean","kinEn2_std","angle"}
dataFrame = pd.DataFrame()

# list of files in SD2
#file_test = open("test.csv", "a")

#file_test.write("x1_mean x1_std x2_mean x2_std y1_mean y1_std y2_mean y2_std px1_mean px1_std px2_mean px2_std py1_mean py1_std py2_mean py2_std kinEn1_mean kinEn1_std kinEn2_mean kinEn2_std\n")

list_files = os.listdir(path='results/SD2')
for part in particle:
    for pz_i in pz:
        for angle_i in angle:
            filename = "data_{0}_{1}_GeV_{2}_deg.dat".format(part,pz_i,angle_i)
            # first check if we have the same file directory SD2
            if filename in list_files:
                row = analyze_file(filename,angle_i,column)
                #print(row)
                dataFrame = dataFrame.append(row,ignore_index=True)
            

print(dataFrame)

## Save Dataframe in file

dataFrame.to_csv('sim_dataframe.csv')



