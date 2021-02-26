// #############################################
//
//	This ROOT macro plots the time spectrum
//	and saves it in a .root file
//
// #############################################

void TauPlotter() {

	// TCanvas and TH1F for bkg
	TCanvas* cc_tau = new TCanvas ("cc_tau", "", 800, 600);
    	TH1F *tau = new TH1F("tau", "", 9000, 0, 8999);

	// Load bkg and spectrum data
	int x;
	std::ifstream in_file, in_file2;
    	in_file.open("17_feb_2mus_G01_14gg.dat");
    	if (!in_file) {
        	std::cout << "error" << std::endl;
        	exit(1);
    	}

	int ibin = 0;
    	while (in_file >> x) {
		tau->SetBinContent(ibin, x);
		ibin++;
    	}

 	tau->SetLineWidth(1.);
	tau->SetLineColor(kBlack);
	tau->Draw();
	tau->SaveAs("tau.root");


}
