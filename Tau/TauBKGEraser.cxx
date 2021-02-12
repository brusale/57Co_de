
void TauBKGEraser () {

	//load file and histo
	TFile* file = new TFile("./Plotters/tau.root");
	TH1F* tau = (TH1F*)file->Get("tau");

	//sidebands
	float bkg1Min = 200;
	float bkg1Max = 1700;
	float delta_bkg1 = bkg1Max-bkg1Min;

	float bkg2Min = 3200;
	float bkg2Max = 5000;
	float delta_bkg2 = bkg2Max-bkg2Min;

	//signal channels
	float delta_sig = 1500;

	// define constant functions to be fitted to the sidebands
	TF1* bkg1 = new TF1("bkg1", "[0]", bkg1Min, bkg1Max);
	TF1* bkg2 = new TF1("bkg2", "[0]", bkg2Min, bkg2Max);


	tau->Fit(bkg1, "RO");
	tau->Fit(bkg2, "RO");

	float background1 = bkg1->GetParameter(0);
	float background2 = bkg2->GetParameter(0);

	// estimate of background
	float background = 0.5*(background1*(delta_bkg1/delta_sig)+background2*(delta_bkg2/delta_sig));

	int content;
	TH1F* tau_clean = new TH1F("tau_clean", "",  9000, 0, 8999);

	// fill clean histogram
	for (int ibin = 1; ibin < 8193; ibin++){
		content = tau->GetBinContent(ibin);
		content = content - background;
		if (content < 0) tau_clean->SetBinContent(ibin, 0);
		else tau_clean->SetBinContent(ibin, content);
	}

	TCanvas* cc_tau_clean = new TCanvas("cc_tau_clean", "", 800, 600);

	tau_clean->GetXaxis()->SetTitle("Channel");
	tau_clean->GetYaxis()->SetTitle("Counts");
	
	tau_clean->Draw();
	tau_clean->SaveAs("TauClean.root");

}
