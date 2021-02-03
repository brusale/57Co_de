#!/usr/bin/env python
# coding: utf-8

# In[ ]:

# MC simulation that gives an estimate of the contribution of 122 keV, 136 keV and background
# This script assumes to have a pol2 bkg

import numpy as np
import matplotlib.pyplot as plt
import config
import argparse

# In[ ]:

parser = argparse.ArgumentParser()
parser.add_argument("--sigma", help="set window width in terms of 122 peak sigma", type=float)
args = parser.parse_args()

# function for the two peaks
def gaussian(x, constant, mean, sigma):
    return constant*np.exp(-(x-mean)**2/(2*sigma**2))

# function for the background
def bkg(x, pol0, pol1, pol2):
    return pol0+pol1*x+pol2*x*x


# In[ ]:

# function for the MC integration
def AreaMC(N, threshold1, threshold2, par122, par136, parbkg):
    Area122 = 0
    Area136 = 0
    BKG = 0
    AreaTot = 0

    for i in range(0, N):
        x1 = threshold1 + (threshold2 - threshold1)*(np.random.random_sample())
        
        Area122 += (threshold2-threshold1)*gaussian(x1, *par122)/N
            
        Area136 += (threshold2-threshold1)*gaussian(x1, *par136)/N
            
        BKG += (threshold2-threshold1)*bkg(x1, *parbkg)/N
            
    AreaTot = Area136+Area122+BKG
            
    return Area122, Area136, AreaTot, BKG


# In[ ]:


x = np.linspace(3000, 5000, 10000)

# all the parameters obtained from the fit
par122 = [config.peak122['constant'], config.peak122['mean'], config.peak122['sigma']]
par136 = [config.peak136['constant'], config.peak136['mean'], config.peak136['sigma']]
parbkg = [config.bkg['pol0'], config.bkg['pol1'], config.bkg['pol2']]

#set window
threshold1 = par122[1]-par122[2]*(args.sigma)
threshold2 = par122[1]+par122[2]*(args.sigma)
# In[ ]:

# pretty plot
plt.plot(x, gaussian(x, *par122), label="122 peak")
plt.plot(x, gaussian(x, *par136), label="136 peak")
plt.plot(x, bkg(x, *parbkg), label="background")
plt.plot(x, gaussian(x, *par122)+gaussian(x, *par136)+bkg(x, *parbkg), label="total")
plt.axvline(x=threshold1, ymin=0, ymax=0.75, color="r", linestyle="--")
plt.axvline(x=threshold2, ymin=0, ymax=0.75, color="r", linestyle="--")
plt.grid(True)
plt.legend()
plt.xlabel("Channel")
plt.ylabel("Counts")

# integration
area122, area136, areaTot, bkg = AreaMC(10000,threshold1, threshold2, par122, par136, parbkg)

print("122 peak: "+ str(area122/areaTot))
print("136 peak: "+str(area136/areaTot))
print("bkg: "+str(bkg/areaTot))

# In[ ]:

plt.show()
# In[ ]:




