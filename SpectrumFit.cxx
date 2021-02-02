// ++++++++++++++++++++++++++++++++++++++++++++++++++
//
//  This ROOT macro fits the spectrum peaks and
//  plots the fitted funtion.
//
// ++++++++++++++++++++++++++++++++++++++++++++++++++


int SpectrumFit() {

	gStyle->SetOptFit(1111);


	TCanvas* cc_spectrum = new TCanvas("cc_spectrum", "", 800, 600);
	TFile *f = new TFile("spectrum.root");
	TH1F *spectrum = (TH1F*)f->Get("spectrum"); // we use the spectrum in which the background has already been subtracted
	spectrum->SetFillColor(kYellow);
	spectrum->Draw();

	TF1 *double_gaus = new TF1("double_gaus", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2])) + [3]*exp(-(x-[4])*(x-[4])/(2*[5]*[5])) + [6]*x*x+[7]*x+[8]", 3500, 4700); 

	// the parameters are set after having fitted a first time through the ROOT fit panel
	double_gaus->SetParameter(0, 35000);
	double_gaus->SetParameter(1, 3800);
	double_gaus->SetParameter(2, 200);
	double_gaus->SetParameter(3, 6000);
	double_gaus->SetParameter(4, 4200);
	double_gaus->SetParameter(5, 200);

	// set parameters names
	double_gaus->SetParName(0, "constant 122");
	double_gaus->SetParName(1, "mean 122");
	double_gaus->SetParName(2, "sigma 122");

	double_gaus->SetParName(3, "constant 136");
	double_gaus->SetParName(4, "mean 136");
	double_gaus->SetParName(5, "sigma 136");

	double_gaus->SetParName(6, "bkg order2");
	double_gaus->SetParName(7, "bkg order1");
	double_gaus->SetParName(8, "bkg order0");

	spectrum->Fit("double_gaus", "R"); // R restricts the fit to the range specified in double_gaus	

	// plot the peak related to the 122 keV peak
	TF1* peak122 = new TF1("122_peak", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))", 3000, 5000);
	peak122->SetParameter(0, double_gaus->GetParameter(0));
	peak122->SetParameter(1, double_gaus->GetParameter(1));
	peak122->SetParameter(2, double_gaus->GetParameter(2));

	peak122->SetLineColor(kBlue);
	peak122->SetFillStyle(1001);
	peak122->SetFillColor(38);
	peak122->Draw("CF same");

	// plot the peak related to the 136 peak
	TF1* peak136 = new TF1("136_peak", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))", 3500, 5000);
	peak136->SetParameter(0, double_gaus->GetParameter(3));
	peak136->SetParameter(1, double_gaus->GetParameter(4));
	peak136->SetParameter(2, double_gaus->GetParameter(5));

	peak136->SetLineColor(kGreen);
	peak136->Draw("same");

	TF1* background = new TF1("backgrounf", "[0]*x*x+[1]*x+[2]", 3300, 5000);
	background->SetParameter(0, double_gaus->GetParameter(6));
	background->SetParameter(1, double_gaus->GetParameter(7));
	background->SetParameter(2, double_gaus->GetParameter(8));

	background->SetLineColor(kBlack);
	background->Draw("same");	

/*	// plot the two remaining peaks (iodium escpae peak)
	TF1* iodium_escape = new TF1("iodium_escape", "[0]*exp(-(x-[1])*(x-[1])/[2])", 2000, 3000);
	iodium_escape->SetParameter(0, double_gaus->GetParameter(6));
	iodium_escape->SetParameter(1, double_gaus->GetParameter(7));
	iodium_escape->SetParameter(2, double_gaus->GetParameter(8));

	iodium_escape->SetLineColor(kCyan);
	iodium_escape->Draw("same");

	// due to the lead shield
	TF1* iodium_escape2 = new TF1("iodium_escape2", "[0]*exp(-(x-[1])*(x-[1])/[2])", 2000, 3000);
	iodium_escape2->SetParameter(0, double_gaus->GetParameter(9));
	iodium_escape2->SetParameter(1, double_gaus->GetParameter(10));
	iodium_escape2->SetParameter(2, double_gaus->GetParameter(11));

	iodium_escape2->SetLineColor(kBlack);
	iodium_escape2->Draw("same");*/


	
}
