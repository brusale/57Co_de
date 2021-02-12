// ************************************************
//                                               
//  This ROOT macro plots spectrum for related to
//  the 122 keV detector                             
//                                               
//*************************************************

void Spectrum122() {

	// TCanvas and TH1F for bkg
	TCanvas* cc_bkg = new TCanvas ("cc_bkg", "", 800, 600);

	// Load bkg and spectrum data
	int x;
	std::ifstream in_file, in_file2;
	in_file.open("11_dic_122kev.dat");
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
	spectrum->SaveAs("spectrum122.root");


}
