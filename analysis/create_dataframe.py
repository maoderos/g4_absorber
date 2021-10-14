import numpy as np
import pandas as pd
import glob, os


def analyze_file(rad,part,pz_i,angle_i,df):
    # arrays from detector 1 (SD1)
    filename = "{0}_{1}_{2}_GeV_{3}_deg.dat".format(rad,part,pz_i,angle_i)
    x1,y1,px1,py1,pz1,kinEn1 = np.loadtxt("SD1/" + filename, unpack=True)
    x2,y2,px2,py2,pz2,kinEn2 = np.loadtxt("SD2/" + filename, unpack=True)
    
    ## MEAN

    x1_mean = np.mean(x1); y1_mean = np.mean(y1); px1_mean = np.mean(px1); py1_mean = np.mean(py1)
    pz1_mean = np.mean(pz1); kinEn1_mean = np.mean(kinEn1)
    
    x2_mean = np.mean(x2); y2_mean = np.mean(y2); px2_mean = np.mean(px2); py2_mean = np.mean(py2)
    pz2_mean = np.mean(pz2); kinEn2_mean = np.mean(kinEn2)
    
    x2_x1_mean = np.mean(x2 - x1); px2_px1_mean = np.mean(px2 - px1); kinEn2_kinEn1_mean = np.mean(kinEn2 - kinEn1)
    
    ## STD
    
    x1_std = np.std(x1); y1_std = np.std(y1); px1_std = np.std(px1); py1_std = np.std(py1)
    pz1_std = np.std(pz1); kinEn1_std = np.std(kinEn1)
    
    x2_std = np.std(x2); y2_std = np.std(y2); px2_std = np.std(px2); py2_std = np.std(py2)
    pz2_std = np.std(pz2); kinEn2_std = np.std(kinEn2)
    
    x2_x1_std = np.std(x2 - x1); px2_px1_std = np.std(px2 - px1); kinEn2_kinEn1_std = np.std(kinEn2 - kinEn1)
    
    
    
    line = pd.Series([x1_mean,x1_std,x2_mean,x2_std,y1_mean,y1_std,
                     y2_mean,y2_std,px1_mean,px1_std,px2_mean,px2_std,
                     py1_mean,py1_std,py2_mean,py2_std,kinEn1_mean,kinEn1_std,
                     kinEn2_mean,kinEn2_std,x2_x1_mean,x2_x1_std,px2_px1_mean,
                     px2_px1_std,kinEn2_kinEn1_mean,kinEn2_kinEn1_std], columns=df.columns)
    
    return line

rad='data'
particle = ['mu+']
pz = [1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,7.5,8,8.5,9,9.5]
angle = [2.5,3,4,7]
detectors = ["SD1", "SD2"]

# creating a blank dataframe 

'''
dataFrame = pd.DataFrame(columns={"<x1>","sigma_<x1>","<y1>","sigma_<y1>","<x2>","sigma_<x2>","<y2>",
                                 "<px1>","<px2>", "<EnKin1>", "<EnKin2>", "<x2 - x1>", "sigma_<x2 - x1>",
                                  "<y2 - y1>", "sigma_<y2 - y1>",
                                  "<px2 - px1>", "sigma_<px2 - px1>",
                                  "<py2 - py1>", "sigma_<py2 - py1>" })
'''

for part in particle:
    for pz_i in pz:
        for angle_i in angle:
            a = 1
            # first check if we have the same file in both directories SD1 and SD2
            #line = analyze_file(rad,part,pz_i,angle_i,dataFrame)
            #dataFrame = dataFrame.append(line,ignore_index=True)
            


