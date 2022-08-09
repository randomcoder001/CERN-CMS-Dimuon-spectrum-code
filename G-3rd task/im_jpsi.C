//code for invariant mass distribution of J/psi meson
//Author-Jinu Raj,PHYS2801-SRFP 2022,CHEP-IISc Banglore



#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "Math/Vector4Dfwd.h"
#include "Math/Vector4D.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLatex.h"
#include "TStyle.h"


using namespace ROOT::VecOps;

// Compute the invariant mass of two muon four-vectors
float computeInvariantMass(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) {
    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);
    return (m1 + m2).mass();
}


void im_jpsi() {
    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT(1);

    // Create dataframe from NanoAOD files
    ROOT::RDataFrame df("Events", "Run2012BC_DoubleMuParked_Muons.root");

    // Select events with exactly two muons
    auto df_2mu = df.Filter("nMuon == 2", "Events with exactly two muons");

    // Select events with two muons of opposite charge
    auto df_os = df_2mu.Filter("Muon_charge[0] != Muon_charge[1]", "Muons with opposite charge");

    // Compute invariant mass of the dimuon system
    auto df_mass = df_os.Define("Dimuon_mass", computeInvariantMass,
                                {"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
    
    
     //hist j/psi
   const auto bins4=200;
   const auto low4=3.066;
   const auto up4=3.122;
   auto hist4=df_mass.Histo1D({"j/psi","",bins4,low4,up4},"Dimuon_mass");
   
   
   
    // Request cut-flow report
    auto report = df_mass.Report();

    // Create canvas for plotting
    gStyle->SetOptStat(0);
    gStyle->SetTextFont(42);
    auto c4 = new TCanvas("c4", "", 800, 700);
    
        // hist4->SetTitle("j/psi");
    hist4->GetXaxis()->SetTitle("m_{#mu#mu} (GeV)");
    hist4->GetXaxis()->SetTitleSize(0.04);
    hist4->GetYaxis()->SetTitle("N_{Events}");
    hist4->GetYaxis()->SetTitleSize(0.04);
    hist4->Fit("gaus");
    hist4->DrawClone();
    TLatex label4;
    label4.DrawLatex(3.05, 1000, "#bf{j/psi}");
    
    
    
    
    
      // Save plot
    
   c4->SaveAs("im_jpsi.pdf");

    // Print cut-flow report
    report->Print();
}

    
 int main() {
    im_jpsi();
}
