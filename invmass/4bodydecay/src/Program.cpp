#include "../include/Program.h"
using namespace std;

Int_t Program::Code()
{
    /* Note that TFGenPhaseSpace, as per LHCb standard, is in GeV. Hence all the
     * calculations and graphs hereonin are in GeV. */

    if (!gROOT -> GetClass("TGenPhaseSpace"))
        gSystem->Load("libPhysics"); // Get and load TGenPhaseSoace class

    gStyle->SetOptStat(0);

    TH1F *hist1 = new TH1F("hist1", "m(K+ K-[1])^2", 50, 0.95, 1.55);
    TH1F *hist2 = new TH1F("hist2", "m(K+ K-[2])^2", 50, 0.95, 1.55);
    TH1F *hist3 = new TH1F("hist3", "m(K-[1] K-[2])^2", 50, 0.95, 1.55);

    TH1F *hist4 = new TH1F("hist4", "m(K+ Pi+)^2", 50, 0.35, 0.8);
    TH1F *hist5 = new TH1F("hist5", "m(K-[1] Pi+)^2", 50, 0.35, 0.8);
    TH1F *hist6 = new TH1F("hist6", "m(K-[2] Pi+)^2", 50, 0.35, 0.8);

    TH1F *hist7 = new TH1F("hist7", "m(K+ K-[1] K-[2])^2", 50, 2.1, 3);

    TH1F *hist8 = new TH1F("hist8", "m(K+ K-[1]) Pi+)^2", 50, 1.2, 1.9);
    TH1F *hist9 = new TH1F("hist9", "m(K+ K-[2]) Pi+)^2", 50, 1.2, 1.9);
    TH1F *hist10 = new TH1F("hist10", "m(K-[1] K-[2] Pi+)^2", 50, 1.2, 1.9);

    TH1F *hist11 = new TH1F("hist11", "m(KK)^2", 50, 0.98, 1.25);
    TH1F *hist12 = new TH1F("hist12", "m(KPi)^2", 50, 0.62, 0.9);
    TH1F *hist13 = new TH1F("hist13", "m(KKK)^2", 50, 1.48, 1.74);
    TH1F *hist14 = new TH1F("hist14", "m(KKPi)^2", 50, 1.12, 1.38);
    // Initiliase all the histograms used for plotting later on

    TLorentzVector D0(0.0, 0.0, 0.0, 1.86484);
    // 4-vector for parent D0 in rest frame

    Double_t masses[4] = { 0.493677, 0.493677, 0.493677, 0.13957018 };
    // Product particles mass array

    TGenPhaseSpace event; // Declare event of type class TGenPhaseSpace
    event.SetDecay(D0, 4, masses); // Setup decay

    for (Int_t n = 0; n < 100000; n++) // Loop 100,000 times
    {
        Double_t        weight                  = event.Generate();
        // generate weightings for each event

        TLorentzVector  *K_plus                 = event.GetDecay(0);
        TLorentzVector  *K_minus1               = event.GetDecay(1);
        TLorentzVector  *K_minus2               = event.GetDecay(2);
        TLorentzVector  *Pi_plus                = event.GetDecay(3);    
        // Get 4-vectors for products from GetDecay(), in order of mass arrah

        TLorentzVector  K_plusK_minus1          = *K_plus + *K_minus1;
        TLorentzVector  K_plusK_minus2          = *K_plus + *K_minus2;
        TLorentzVector  K_plusPi_plus           = *K_plus + *Pi_plus;
        TLorentzVector  K_minus1K_minus2        = *K_minus1 + *K_minus2;
        TLorentzVector  K_minus1Pi_plus         = *K_minus1 + *Pi_plus;
        TLorentzVector  K_minus2Pi_plus         = *K_minus2 + *Pi_plus;
        // Add the different two-combinations of products

        TLorentzVector  K_plusK_minus1K_minus2  = *K_plus + *K_minus1 + *K_minus2;
        TLorentzVector  K_plusK_minus1Pi_plus   = *K_plus + *K_minus1 + *Pi_plus;
        TLorentzVector  K_plusK_minus2Pi_plus   = *K_plus + *K_minus2 + *Pi_plus;
        TLorentzVector  K_minus1K_minus2Pi_plus = *K_minus1 + *K_minus2 + *Pi_plus;
        // All the different three-combinations of products

        hist1->Fill(K_plusK_minus1.M2(), weight);
        hist2->Fill(K_plusK_minus2.M2(), weight);
        hist3->Fill(K_minus1K_minus2.M2(), weight);
        hist4->Fill(K_plusPi_plus.M2(), weight);
        hist5->Fill(K_minus1Pi_plus.M2(), weight);
        hist6->Fill(K_minus2Pi_plus.M2(), weight);
        hist7->Fill(K_plusK_minus1K_minus2.M2(), weight);
        hist8->Fill(K_plusK_minus1Pi_plus.M2(), weight);
        hist9->Fill(K_plusK_minus2Pi_plus.M2(), weight);
        hist10->Fill(K_minus1K_minus2Pi_plus.M2(), weight);

        hist11->Fill(K_plusK_minus1.M(), weight);
        hist12->Fill(K_plusPi_plus.M(), weight);
        hist13->Fill(K_plusK_minus1K_minus2.M(), weight);
        hist14->Fill(K_plusK_minus1Pi_plus.M(), weight);
        // Fill all the histograms with all the invariant masses squared
    }

    TCanvas* canv1 = new TCanvas("canv1", "Canvas", 1200, 800);
    canv1->Divide(3,1);

    canv1->cd(1);
    hist1->SetTitle("K^{+} K^{-}_{1};m^{2}(K^{+} K^{-}_{1}) [(GeV/c^{2})^{2}]");
    hist1->GetXaxis() -> CenterTitle();
    hist1->GetXaxis() -> SetTitleOffset(1.25);
    hist1->SetLineColor(2);
    hist1->Draw();

    canv1->cd(2);
    hist2->SetTitle("K^{+} K^{-}_{2};m^{2}(K^{+} K^{-}_{2}) [(GeV/c^{2})^{2}]");
    hist2->GetXaxis() -> CenterTitle();
    hist2->GetXaxis() -> SetTitleOffset(1.25);
    hist2->SetLineColor(3);
    hist2->Draw();

    canv1->cd(3);
    hist3->SetTitle("K^{-}_{1} K^{-}_{2};m^{2}(K^{-}_{1} K^{-}_{2}) [(GeV/c^{2})^{2}]");
    hist3->GetXaxis() -> CenterTitle();
    hist3->GetXaxis() -> SetTitleOffset(1.25);
    hist3->SetLineColor(4);
    hist3->Draw();

    TCanvas* canv2 = new TCanvas("canv2", "Canvas", 1200, 800);
    canv2->Divide(3,1);

    canv2->cd(1);
    hist4->SetTitle("K^{+} #pi^{+};m^{2}(K^{+} #pi^{+}) [(GeV/c^{2})^{2}]");
    hist4->GetXaxis() -> CenterTitle();
    hist4->GetXaxis() -> SetTitleOffset(1.25);
    hist4->SetLineColor(2);
    hist4->Draw();

    canv2->cd(2);
    hist5->SetTitle("K^{-}_{1} #pi^{+};m^{2}(K^{-}_{1} #pi^{+}) [(GeV/c^{2})^{2}]");
    hist5->GetXaxis() -> CenterTitle();
    hist5->GetXaxis() -> SetTitleOffset(1.25);
    hist5->SetLineColor(3);
    hist5->Draw();

    canv2->cd(3);
    hist6->SetTitle("K^{-}_{2} #pi^{+};m^{2}(K^{-}_{2} #pi^{+}) [(GeV/c^{2})^{2}]");
    hist6->GetXaxis() -> CenterTitle();
    hist6->GetXaxis() -> SetTitleOffset(1.25);
    hist6->SetLineColor(4);
    hist6->Draw();

    TCanvas* canv3 = new TCanvas("canv3", "Canvas", 1200, 800);

    hist7->SetTitle("K^{+} K^{-}_{1} K^{-}_{2};m^{2}(K^{+} K^{-}_{1} K^{-}_{2}) [(GeV/c^{2})^{2}]");
    hist7->GetXaxis() -> CenterTitle();
    hist7->GetXaxis() -> SetTitleOffset(1.25);
    hist7->SetLineColor(6);
    hist7->Draw();

    TCanvas* canv4 = new TCanvas("canv4", "Canvas", 1200, 800);
    canv4->Divide(3,1);

    canv4->cd(1);
    hist8->SetTitle("K^{+} K^{-}_{1} #pi^{+};m^{2}(K^{+} K^{-}_{1} #pi^{+}) [(GeV/c^{2})^{2}]");
    hist8->GetXaxis() -> CenterTitle();
    hist8->GetXaxis() -> SetTitleOffset(1.25);
    hist8->SetLineColor(2);
    hist8->Draw();

    canv4->cd(2);
    hist9->SetTitle("K^{+} K^{-}_{2} #pi^{+};m^{2}(K^{+} K^{-}_{2} #pi^{+}) [(GeV/c^{2})^{2}]");
    hist9->GetXaxis() -> CenterTitle();
    hist9->GetXaxis() -> SetTitleOffset(1.25);
    hist9->SetLineColor(3);
    hist9->Draw();

    canv4->cd(3);
    hist10->SetTitle("K^{-}_{1} K^{-}_{2} #pi^{+};m^{2}(K^{-}_{1} K^{-}_{2} #pi^{+}) [(GeV/c^{2})^{2}]");
    hist10->GetXaxis() -> CenterTitle();
    hist10->GetXaxis() -> SetTitleOffset(1.25);
    hist10->SetLineColor(4);
    hist10->Draw();

    TCanvas *canv5 = new TCanvas("canv5", "Canvas", 1000, 1000);
    canv5->Divide(2,2);

    canv5->cd(1);
    hist11->SetTitle("K K; m(K K) [GeV/c^{2}]");
    hist11->SetLineColor(1);
    hist11->Draw();

    canv5->cd(2);
    hist12->SetTitle("K #pi; m(K #pi) [GeV/c^{2}]");
    hist12->SetLineColor(2);
    hist12->Draw();

    canv5->cd(3);
    hist13->SetTitle("K K K; m(K K K) [GeV/c^{2}]");
    hist13->SetLineColor(3);
    hist13->Draw();

    canv5->cd(4);
    hist14->SetTitle("K K #pi; m(K K #pi) [GeV/c^{2}]");
    hist14->SetLineColor(4);
    hist14->Draw();

    canv1->Print("../graphs/FourBodyDecay1.eps");
    canv2->Print("../graphs/FourBodyDecay2.eps");
    canv3->Print("../graphs/FourBodyDecay3.eps");
    canv4->Print("../graphs/FourBodyDecay4.eps");

    canv5->Print("../graphs/FourBodyDecay.eps");

    delete canv1;
    delete canv2;
    delete canv3;
    delete canv4;
    delete hist1;
    delete hist2;
    delete hist3;
    delete hist4;
    delete hist5;
    delete hist6;
    delete hist7;
    delete hist8;
    delete hist9;
    delete hist10;
    delete hist11;
    delete hist12;
    delete hist13;

    return 0;
}