// +++++++++++++++++++++++++++++++++++++++++++++++++
//
//	This ROOT macro hopes to find the
//	measure for the half-life of the 57Fe
//	metastable state
//
// +++++++++++++++++++++++++++++++++++++++++++++++++

using namespace RooFit;

int TauSeeker() {

	gStyle->SetOptStat(1111);

	//import data
	TFile* file = new TFile("/home/alessandro/Scrivania/University/QuartoAnno/Lab/tau.root");
	TH1F* histo = (TH1F*)file->Get("tau");

	// variables
	RooRealVar x("x", "x", 0, 5000);
	RooDataHist dh("dh", "dh", x, Import(*histo));

	//gaussian distribution
	RooRealVar mean("mean", "mean of the gaussian distribution", 2100, 2000, 2500);
	RooRealVar sigma("sigma", "sigma of the gaussian distribution", 1, 0.1, 10);
	
	RooGaussian gauss("gauss", "gaussian PDF", x, mean, sigma);

	//exponential distribution
	RooRealVar tau("tau", "decay constant of the exponential distribution", 1, 0.0005, 0.01);
	RooExponential expo("expo", "exponential distribution", x, tau);

	//convolution of the two distributions
	x.setBins(10000, "cache");
	RooFFTConvPdf gxe("gxe", "gauss (X) exponential", x, gauss, expo);

	gxe.fitTo(dh);




}
