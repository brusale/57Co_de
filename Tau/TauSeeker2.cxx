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

	//define fit function
	TF1* convolution = new TF1("convolution", "[0]+[1]/2*exp(-(x-[2])/[3]+[4]/(2*[3]*[3]))*(1+TMath::Erf((x-[2]-[4]/[3])/(sqrt(2*[4]))))", 0, 5000);

	convolution->SetParameter(0, 20);
	convolution->SetParameter(1, 300);
	convolution->SetParameter(2, 2100);
	convolution->FixParameter(3, 500);
	convolution->SetParameter(4, 1000);

	tau->Fit(convolution, "R");

	float a = convolution->GetParameter(0);
	float b = convolution->GetParameter(1);
	float c = convolution->GetParameter(2);
	float d = 500;
	float e = convolution->GetParameter(4);

	convolution->SetParameter(0, a);
	convolution->SetParameter(1, b);
	convolution->SetParameter(2, c);
	convolution->SetParameter(3, d);
	convolution->SetParameter(4, e);

	tau->Fit(convolution, "R");




}
