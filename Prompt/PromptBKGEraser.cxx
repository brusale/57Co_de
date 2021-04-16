
void PromptBKGEraser () {

	//load file and histo
	TFile* file = new TFile("prompt.root");
	TList *list = new TList();
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
	float sigma_bkg = 0.5*delta_sig*sqrt(background1/pow(delta_bkg1, 2) + background2/pow(delta_bkg2, 2));


	int content, content_low, content_high, content_clean;
	TH1F* tau_clean_low = new TH1F("tau_clean_low", "",  9000, 0, 8999);
	TH1F* tau_clean_high = new TH1F("tau_clean_high", "", 9000, 0, 8999);
	TH1F* tau_clean = new TH1F("tau_clean", "", 9000, 0, 8999);

	// fill clean histogram
	for (int ibin = 1; ibin < 8193; ibin++){
		content = tau->GetBinContent(ibin);
		content_clean = content - background;

		tau_clean->SetBinContent(ibin, content_clean);
		if (content_clean < 0) tau_clean->SetBinContent(ibin, 0);
		else tau_clean->SetBinContent(ibin, content_clean);

		content_low = content - background - sigma_bkg;
		if (content_low < 0) tau_clean_low->SetBinContent(ibin, 0);
		else tau_clean_low->SetBinContent(ibin, content_low);

		content_high = content - background + sigma_bkg;
		if (content_high < 0) tau_clean_high->SetBinContent(ibin, 0);
		else tau_clean_high->SetBinContent(ibin, content_high);
	}


	tau_clean->GetXaxis()->SetTitle("Channel");
	tau_clean->GetYaxis()->SetTitle("Counts");

	tau_clean_low->GetXaxis()->SetTitle("Channel");
	tau_clean_low->GetYaxis()->SetTitle("Counts");

	tau_clean_high->GetXaxis()->SetTitle("Channel");
	tau_clean_high->GetYaxis()->SetTitle("Counts");
	
	TCanvas* cc_tau_clean = new TCanvas("cc_tau_clean", "", 800, 600);
	tau_clean->Draw();
	TCanvas* cc_tau_clean_low = new TCanvas("cc_tau_clean_low", "", 800, 600);
	tau_clean_low->Draw();
	TCanvas* cc_tau_clean_high = new TCanvas("cc_tau_clean_high", "", 800, 600);
	tau_clean_high->Draw();

	list->Add(tau_clean);
	list->Add(tau_clean_low);
	list->Add(tau_clean_high);
	list->SaveAs("PromptClean.root");

}
