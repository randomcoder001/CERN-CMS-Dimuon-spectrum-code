//code for invariant mass distribution of phi meson
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


void PHI() {
    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT(1);

    // Create dataframe from NanoAOD files
    ROOT::RDataFrame df("Events", "Run2012BC_DoubleMuParked_Muons.root");


    // Select events with exactly two muons
    auto df_2mu = df.Filter("nMuon == 2", "Events with exactly two muons");
 
    // Select events with two muons of opposite charge
    auto df_os = df_2mu.Filter("Muon_charge[0] != Muon_charge[1]", "Muons with opposite charge");

 
  //muon phi                      
 auto df_ph=df_os.Define("mUon_phi", {"Muon_phi"});
 
 
 //book histogram for muon_phi
     
 const auto bins2= 3000; // Number of bins in the histogram
    const auto low2= -3.24; // Lower edge of the histogram
    const auto up2= 3.14; // Upper edge of the histogram
  auto hist2=df_ph.Histo1D({"","",bins2,low2,up2},"mUon_phi");
  
  
     //Request cut-flow report for muonphi
    auto report2 = df_ph.Report();
     // Create canvas for plotting muonphi
    gStyle->SetOptStat(0);
    gStyle->SetTextFont(42);
    auto c2=new TCanvas("C2","",800,700);
    
    hist2->GetXaxis()->SetTitle("MUON PHI");
    hist2->GetXaxis()->SetTitleSize(0.04);
    hist2->GetYaxis()->SetTitle("N_{Events}");
    hist2->GetYaxis()->SetTitleSize(0.04);
    hist2->DrawClone();
     
     

    c2->SaveAs("phimu.pdf");


    // Print cut-flow report
    //report->Print();
}


int main() {
   PHI();
}
