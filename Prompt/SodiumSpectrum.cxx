/* 
 This ROOT macro plots the Na22 spectrum
 as seen by the 14keV detector.
 It also computes the amount of counts
 due to the Pb X-rays, in order to estimate
 the percentage of counts to neglect consider in
 the time spectrum.
*/

void SodiumSpectrum() {

	gStyle->SetOptFit(1111);

	// Load bkg and spectrum data
	int x;
	std::ifstream in_file, in_file2;
	in_file.open("14_x10_1000V.dat");
    	if (!in_file) {
        	std::cout << "error" << std::endl;
        	exit(1);
    	}

	//TCanvas and TH1F for spectrum
	TCanvas* cc_spectrum = new TCanvas("cc_spectrum", "", 800, 600);
    	TH1F *spectrum = new TH1F("spectrum", "", 9000, 0, 8999);

	int ibin = 0;
	while (in_file >> x) {
		spectrum->SetBinContent(ibin, x);
		ibin++;
	}

	spectrum->SetLineWidth(1.);
	spectrum->SetLineColor(kBlack);
	spectrum->Draw();

	//define fit function for the Pb peak at approximately 80 keV
	TF1 *pb_peak = new TF1("pb_peak", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]))", 500, 900);

	// set parameters
	pb_peak->SetParameter(0, 120); 
	pb_peak->SetParameter(1, 700);
	pb_peak->SetParameter(2, 44000);

	// fit
	spectrum->Fit(pb_peak, "RL");

	

//	spectrum->SaveAs("spectrum14.root");
}
