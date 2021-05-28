#include <cmath>
//
//	***********************************************
//
//	This ROOT macro really hopes to find the tau
//	using the analytical form of the convolution
//	of a gaussian distribution with an 
//	exponential distribution
//
// 	***********************************************
//
//

void TauSeeker2() {

	gStyle->SetOptFit(1111);

	// load spectrum without bkg due to random coincidences
	TFile* file = new TFile("./TauClean.root");
	TH1F* tau = (TH1F*)file->Get("tau_clean");

	//fit only the right part of the spectrum with an exponential distribution
	TF1* exponential = new TF1("exponential", "[3]+[0]*exp(-(x-[1])/[2])", 2300, 4700);


	float avg;
	int x0, x1, x2, x3, x4;
	//data smoothing
	for (int ibin=2; ibin < 8999; ibin++) {
		x0 = tau->GetBinContent(ibin-2);
		x1 = tau->GetBinContent(ibin-1);
		x2 = tau->GetBinContent(ibin);
		x3 = tau->GetBinContent(ibin+1);
		x4 = tau->GetBinContent(ibin+2);
		avg = (x0+x1+x2+x3+x4)/5;

		tau->SetBinContent(ibin, avg);
	}

	exponential->SetParameter(0, 130);
	exponential->SetParameter(1, 2100);
	exponential->SetParameter(2, 300);
	exponential->SetParameter(3, 5);

	tau->Fit(exponential, "R");


	float t = exponential->GetParameter(2);
	float t_0 = exponential->GetParameter(1);

	//define fit function
	TF1* convolution = new TF1("convolution", "[0]+[1]/2*exp(-(x-[2])/[3]+[4]/(2*[3]*[3]))*(1+TMath::Erf((x-[2]-[4]/[3])/(sqrt(2*[4]))))", 1500, 4700);

	convolution->SetParName(0, "A");
	convolution->SetParName(1, "C");
	convolution->SetParName(2, "t_0");
	convolution->SetParName(3, "tau");
	convolution->SetParName(4, "sigma sq");

	convolution->SetParameter(0, 2);
	convolution->SetParameter(1, 150);
	convolution->SetParameter(2, t_0);
	convolution->SetParameter(3, t);
	convolution->SetParameter(4, 80*80);

	tau->SaveAs("TauSeeker.root");
	tau->Fit(convolution, "R");

	//find tau from TAC linearity
	float m = 2.465;
	float q = -4.79;
	float sigma_m = 0.03093;
	float sigma_q = 7.504;

	float channel_tau = convolution->GetParameter(3);

	float tauvalue = (channel_tau - q)/m;

	std::cout << "------ TAU ------" << std::endl;
	std::cout << "\n57Fe lifetime: " << tauvalue << std::endl;

	float sigma_tau = 1/pow(m, 2)*sqrt(pow((channel_tau - q),2)*sigma_m*sigma_m + sigma_q*sigma_q);
	std::cout << "error: " << sigma_tau << std::endl;

	std::cout << "\n------ HALF-LIFE ------" << std::endl;
	float half_life = log(2)*tauvalue;
	float sigma_half_life = log(2)*sigma_tau;

	std::cout << "\n57Fe half-life: " << half_life << std::endl;
	std::cout << "error: " << sigma_half_life << std::endl;
	//residuals
	Double_t channel[3000], residuals[3000];
	for (int i = 1500; i < 4500; i++) {
		channel[i-1500] = tau->GetBinCenter(i);
		residuals[i] = ((tau->GetBinContent(i))- (convolution->Eval(channel[i-1500])))/(tau->GetBinContent(i));
	}
	
/*	TCanvas* cc_residuals = new TCanvas("cc_residuals", "", 800, 600);
	TGraph* gr_residuals = new TGraph(3000, channel, residuals);
	gr_residuals->SetTitle("Residuals");
	gr_residuals->GetXaxis()->SetTitle("Channel");
	gr_residuals->GetYaxis()->SetTitle("Residual");
	gr_residuals->SetMarkerSize(1.);
	gr_residuals->SetMarkerStyle(20);
	gr_residuals->SetMarkerColor(kRed);
	gr_residuals->Draw("AL");*/


}
