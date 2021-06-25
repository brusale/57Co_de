#include <vector>
#include <cmath>

void TauMultipleFit() {

	gStyle->SetOptFit(1111);

	// load spectrum without bkg due to random coincidences
	TFile* file = new TFile("./TauClean.root");
	TH1F* tau = (TH1F*)file->Get("tau_clean");

	//fit only the right part of the spectrum with an exponential distribution
//	TF1* exponential = new TF1("exponential", "[3]+[0]*exp(-(x-[1])/[2])", 2300, 4700);

	float avg;
	int x0, x1, x2, x3, x4;
	//data smoothing
	for (int ibin=1; ibin < 8999; ibin++) {
		x0 = tau->GetBinContent(ibin-2);
		x1 = tau->GetBinContent(ibin-1);
		x2 = tau->GetBinContent(ibin);
		x3 = tau->GetBinContent(ibin+1);
		x4 = tau->GetBinContent(ibin+2);
		avg = (x0+x1+x2+x3+x4)/5;

		tau->SetBinContent(ibin, avg);
	}

/*	exponential->SetParameter(0, 130);
	exponential->SetParameter(1, 2100);
	exponential->SetParameter(2, 404);
	exponential->SetParameter(3, 5);

	tau->Fit(exponential, "R");

	float t = exponential->GetParameter(2);*/

	Double_t upper_level[1847], tau_value[1847], sigma_up[1847], sigma_hl[1847];
	for (int i =4 ; i < 1851; i++) {
		double up = 1000+2*i;
		TF1* exponential = new TF1("exponential", "[3]+[0]*exp(-(x-[1])/[2])", 2300, up);
		TF1* convolution = new TF1("convolution", "[0]+[1]/2*exp(-(x-[2])/[3]+[4]/(2*[3]*[3]))*(1+TMath::Erf((x-[2]-[4]/[3])/(sqrt(2*[4]))))", 1000, up);
		
		exponential->SetParameter(0, 130);
		exponential->SetParameter(1, 2100);
		exponential->SetParameter(2, 404);
		exponential->SetParameter(3, 5);

		tau->Fit(exponential, "R");

		float t = exponential->GetParameter(2);
		convolution->SetParName(0, "A");
		convolution->SetParName(1, "C");
		convolution->SetParName(2, "t_0");
		convolution->SetParName(3, "tau");
		convolution->SetParName(4, "sigma sq");

		convolution->SetParameter(0, 2);
		convolution->SetParameter(1, 150);
		convolution->SetParameter(2, 2100);
		convolution->SetParameter(3, t);
		convolution->SetParameter(4, 25000);

		tau->Fit(convolution, "R");

		float m = 2.465;
		float q = -4.79;
		float sigma_m = 0.03093;
		float sigma_q = 7.504;

		float channel_tau = convolution->GetParameter(3);

		float tauvalue = (channel_tau - q)/m;
		float halflife = log(2)*tauvalue;
		std::cout << "\n57Fe lifetime: " << tauvalue << std::endl;

		float sigma_tau = 1/pow(m, 2)*sqrt(pow((channel_tau - q),2)*sigma_m*sigma_m + sigma_q*sigma_q);
		float sigma_half_life = log(2)*sigma_tau;	

		upper_level[i-4] = up;
		tau_value[i-4] = halflife;
		sigma_up[i-4] = 0;
		sigma_hl[i-4] = sigma_half_life;
	}
	TCanvas* cc_tau = new TCanvas("cc_residuals", "", 800, 600);
	TGraphErrors* gr_tau = new TGraphErrors(1847, upper_level, tau_value, sigma_up, sigma_hl);
	TLine *line = new TLine(2300, 98, 4800, 98);
	
	gr_tau->SetTitle("Half-life vs upper fit limit");
	gr_tau->GetXaxis()->SetTitle("Channel");
	gr_tau->GetYaxis()->SetTitle("Half-life");
	gr_tau->SetMarkerSize(1.);
	gr_tau->SetMarkerStyle(20);
	gr_tau->SetMarkerColor(kBlack);
	gr_tau->SetLineColor(kRed);
	line->SetLineColor(kBlue);
	gr_tau->Draw("AP");
	line->Draw("same");
}
