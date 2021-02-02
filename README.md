# Half-Life Measurement of the 57Fe First Excited Metastable State
The aim of this work is to find a measure of the half-life of the first excited metastable state of 57Fe

## notebook

- ```MCALinearity.ipynb```
: in this notebook we plot the data for the MCA calibration; the data is fitted to a linear model

- ```TACLinearity.ipynb```
: in this notebook we plot the data for the TAC calibration; the data is fitted to a linear model; this notebook has a ROOT section for fancy ROOT plots

- ```Resolution.ipynb``` 
: this notebook plots the matrices we used when looking at the 122 keV and 14 keV peaks resolution

- ```WindowMC```
: MC simulation in order to see how the choice of the TiSCA window affects the counts due to the 122 keV and 136 keV photons and background


## python script

- ```WindowMC.py```
: MC simulation that estimates the contribution of counts due to 122 keV, 136 keV and background, given a window expressed in terms of 122 peak sigma; window width needs to be given from terminal

		python WindowMC.py --sigma <width>

- ```config.py```
: contains all the peak and background parameters needed in ```WindowMC.py```


## dati

- ```Dati_line``` contains data needed in the ```MCALiinearity``` notebook

- ```Risol_tempi``` contains data needed in the ```Resolution``` notebook

- ```TAC``` is the ods file that contains TAC linearity data; 

## .cxx files

- ```SpectrumFit.cxx``` is a ROOT macro that fits the spectrum from the 122 keV detector (122 keV + 136 keV + bkg)

- ```SpectrumFit14.cxx``` same thing as above, but on the 14 keV peak

- ```TauSeeker.cxx``` is a ROOT macro that hopes to find the half-life of the first excited metastable state of 57Fe

