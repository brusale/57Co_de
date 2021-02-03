// ++++++++++++++++++++++++++++++++++++++++++++++++++
//
//  This ROOT macro fits the spectrum peaks and
//  plots the fitted funtion.
//
// ++++++++++++++++++++++++++++++++++++++++++++++++++


int SpectrumFit14() {

	gStyle->SetOptFit(1111);

	TCanvas* cc_spectrum = new TCanvas("cc_spectrum", "", 800, 600);
	TFile *f = new TFile("spectrum14.root");
	TH1F *spectrum = (TH1F*)f->Get("spectrum"); // we use the spectrum in which the background has already been subtracted
	spectrum->SetFillStyle(1001);
	spectrum->SetFillColor(kYellow);	
	spectrum->Draw();

	TF1 *single_gaus = new TF1("single_gaus", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))+[3]*x+[4]", 550, 850); 

	// the parameters are set after having fitted a first time through the ROOT fit panel
	single_gaus->SetParameter(0, 65000);
	single_gaus->SetParameter(1, 700);
	single_gaus->SetParameter(2, 100);


	spectrum->Fit("single_gaus", "R"); // R restricts the fit to the range specified in double_gaus	

	// plot the peak related to the 14 keV peak
	TF1* peak14 = new TF1("14_peak", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))", 400, 950);
	peak14->SetParameter(0, single_gaus->GetParameter(0));
	peak14->SetParameter(1, single_gaus->GetParameter(1));
	peak14->SetParameter(2, single_gaus->GetParameter(2));

	peak14->SetLineColor(kBlue);
	peak14->SetFillStyle(1001);
	peak14->SetFillColor(38);
	peak14->Draw("same");

	// plot the peak related to the 136 peak
/*	TF1* peak136 = new TF1("136_peak", "[0]*exp(-(x-[1])*(x-[1])/[2])", 3500, 5000);
	peak136->SetParameter(0, double_gaus->GetParameter(3));
	peak136->SetParameter(1, double_gaus->GetParameter(4));
	peak136->SetParameter(2, double_gaus->GetParameter(5));

	peak136->SetLineColor(kGreen);
	peak136->Draw("same");

	// plot the two remaining peaks (iodium escpae peak)
	TF1* iodium_escape = new TF1("iodium_escape", "[0]*exp(-(x-[1])*(x-[1])/[2])", 2000, 3000);
	iodium_escape->SetParameter(0, double_gaus->GetParameter(6));
	iodium_escape->SetParameter(1, double_gaus->GetParameter(7));
	iodium_escape->SetParameter(2, double_gaus->GetParameter(8));

	iodium_escape->SetLineColor(kCyan);
	iodium_escape->Draw("same");*/
	
}
