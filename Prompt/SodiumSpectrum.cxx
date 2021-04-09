\\ 
\\ This ROOT macro plots the Na22 spectrum
\\ as seen by the 14keV detector.
\\ It also computes the amount of counts
\\ due to the Pb X-rays, in order to estimate
\\ the percentage of counts we won't consider in
\\ the time spectrum.
\\

void SodiumSpectrum() {

	// TCanvas and TH1F for bkg
	TCanvas* cc_bkg = new TCanvas ("cc_bkg", "", 800, 600);

	// Load bkg and spectrum data
	int x;
	std::ifstream in_file, in_file2;
	in_file.open("14_x10.dat");
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
	TF1 *pb_peak = new TF1("pb_peak", "[0]*exp(-(x-[1])*(x-[1])/(2*[2]))");

	// set parameters

	// fit

	

//	spectrum->SaveAs("spectrum14.root");
}
