//code for pt of resonances
//Author-Jinu Raj,PHYS2801-SRFP 2022,CHEP-IISc Banglore


#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "Math/Vector4Dfwd.h"
#include "Math/Vector4D.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TStyle.h"


using namespace ROOT::VecOps;

// Compute the invariant mass of two muon four-vectors
float computeInvariantMass(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) {
    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);
    return (m1 + m2).mass();
}


void pt() {
    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT(1);

    // Create dataframe from NanoAOD files
    ROOT::RDataFrame df("Events", "Run2012BC_DoubleMuParked_Muons.root");


    // Select events with exactly two muons
    auto df_2mu = df.Filter("nMuon == 2", "Events with exactly two muons");
 
    // Select events with two muons of opposite charge
    auto df_os = df_2mu.Filter("Muon_charge[0] != Muon_charge[1]", "Muons with opposite charge");

  
  //muon pt
     auto df_p=df_os.Define("mUon_pt", {"Muon_pt"});
  
  
    // Book histogram for muon_pt
    const auto bins =3000; // Number of bins in the histogram
    const auto low = 0.0; // Lower edge of the histogram
   const auto up = 120.0; // Upper edge of the histogram
    auto hist=df_p.Histo1D({"","",bins,low,up},"mUon_pt");
    
      
    
    // Request cut-flow report
    auto report = df_p.Report();

    // Create canvas for plotting muonpt
    gStyle->SetOptStat(0);
    gStyle->SetTextFont(42);
    auto c = new TCanvas("c", "", 800, 700);
 // c->SetLogx();
 // c->SetLogy();
    




    // Draw histogram
    hist->GetXaxis()->SetTitle("MUON PT");
    hist->GetXaxis()->SetTitleSize(0.04);
    hist->GetYaxis()->SetTitle("N_{Events}");
    hist->GetYaxis()->SetTitleSize(0.04);
    hist->DrawClone();
    
      
      
    ///auto hist=df_p.Histo1D({"","",bins,low,up},"mUon_pt");
    
    
      // Save plot
    c->SaveAs("mupt.pdf");
     report->Print();
}


int main() {
   pt();
}
  
