# 57Code

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


## .cxx files

- ```Spectrum122.cxx```, ```Spectrum14.cxx``` plot the spectrum for the 122 and 14 keV detectors

- ```TauPlotter.cxx``` plots the time spectrum, from which the half-life of the 57Fe can be measured

- ```SpectrumFit.cxx``` is a ROOT macro that fits the spectrum from the 122 keV detector (122 keV + 136 keV + bkg)

- ```SpectrumFit14.cxx``` same thing as above, but on the 14 keV peak

- ```TauBKGEraser.cxx``` removes all counts due to the random coincidences

- ``` TauSeeker2.cxx``` fits the times spectrum with the convolution of an exponential distribution with a gaussian distribution and computes tau


