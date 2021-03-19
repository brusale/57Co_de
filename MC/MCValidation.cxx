//
// ROOT Macro for MC validation
//

void MCValidation() {

	// Fitting using the same code as in SpectrumFit.cxx
	gStyle->SetOptFit(1111);


	TCanvas* cc_spectrum = new TCanvas("cc_spectrum", "", 800, 600);
	TFile *f = new TFile("../Plotters/spectrum122.root");
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
	
	//copmute functions integral
	TF1* peak122 = new TF1("122_peak", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))", 3000, 5000);
	peak122->SetParameter(0, double_gaus->GetParameter(0));
	peak122->SetParameter(1, double_gaus->GetParameter(1));
	peak122->SetParameter(2, double_gaus->GetParameter(2));

	float integral122 = peak122->Integral(3500, 4700);

	TF1* peak136 = new TF1("136_peak", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))", 3500, 5000);
	peak136->SetParameter(0, double_gaus->GetParameter(3));
	peak136->SetParameter(1, double_gaus->GetParameter(4));
	peak136->SetParameter(2, double_gaus->GetParameter(5));

	float integral136 = peak136->Integral(3500, 4700);

	std::cout << integral136/integral122 << std::endl;

	
}
