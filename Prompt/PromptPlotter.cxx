// #############################################
//
//	This ROOT macro plots the time spectrum
//	and saves it in a .root file
//
// #############################################

void PromptPlotter() {

	// TCanvas and TH1F for bkg
	TCanvas* cc_tau = new TCanvas ("cc_tau", "", 800, 600);
    	TH1F *tau = new TH1F("tau", "", 9000, 0, 8999);

	// Load bkg and spectrum data
	int x;
	std::ifstream in_file, in_file2;
    	in_file.open("23_04_prompt_no_piombo_finestre_strette.dat");
    	if (!in_file) {
        	std::cout << "error" << std::endl;
        	exit(1);
    	}

	int ibin = 0;
    	while (in_file >> x) {
		tau->SetBinContent(ibin, x);
		ibin++;
    	}

	// we remove all the counts due to the 136 peak
	// from the MC simulation we made based on the window width 
	// the estimate for these counts is about 0.038% that of the 
	// 122 counts
	int clean_content;
	for (int i = 0; i < ibin; i++) {
		clean_content = tau->GetBinContent(i);
		clean_content = clean_content - 0.0570421*clean_content;
		tau->SetBinContent(i,clean_content);
	}

 	tau->SetLineWidth(1.);
	tau->SetLineColor(kBlack);
	tau->Draw();
	tau->SaveAs("prompt2.root");


}
