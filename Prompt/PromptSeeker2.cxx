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

void PromptSeeker2() {

	gStyle->SetOptFit(1111);

	// load spectrum without bkg due to random coincidences
	TFile* file = new TFile("./Prompt2Clean.root");
	TH1F* tau = (TH1F*)file->Get("tau_clean_low");

	//fit only the right part of the spectrum with an exponential distribution
	TF1* gaus = new TF1("gaus", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]))", 1400, 2400);


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

	gaus->SetParameter(0, 1800);
	gaus->SetParameter(1, 1850);

	tau->Fit(gaus, "RL");
}
