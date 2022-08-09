//code for phi of resonances
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

// Compute the phi of two muon four-vectors
float computephi(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) {
    ROOT::Math::PtEtaPhiMVector phi1(pt[0], eta[0], phi[0], mass[0]);
    ROOT::Math::PtEtaPhiMVector phi2(pt[1], eta[1], phi[1], mass[1]);
    
    
    
    

    
    return (phi1+phi2).phi();
}


void phist() {
    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT(1);

    // Create dataframe from NanoAOD files
    ROOT::RDataFrame df("Events", "Run2012BC_DoubleMuParked_Muons.root");

    // Select events with exactly two muons
    auto df_2mu = df.Filter("nMuon == 2", "Events with exactly two muons");

    // Select events with two muons of opposite charge
    auto df_os = df_2mu.Filter("Muon_charge[0] != Muon_charge[1]", "Muons with opposite charge");

    // Compute phi of the dimuon system
   
    
      auto df_phi = df_os.Define("Dimuon_phi", computephi,
                                {"Muon_pt", "Muon_eta", "Muon_phi", "Muon_mass"});
      
      
         
         
         
         
                                
  
    // Book histogram of dimuon mass spectrum
    const auto bins = 600; // Number of bins in the histogram
    const auto low = -3.5; // Lower edge of the histogram
    const auto up = 3.5; // Upper edge of the histogram
    auto hist = df_phi.Histo1D({"", "", bins, low, up}, "Dimuon_phi");
    
    
    

    // Request cut-flow report
    auto report = df_phi.Report();

    // Create canvas for plotting
    gStyle->SetOptStat(1111111);
    gStyle->SetTextFont(42);
    auto c = new TCanvas("c", "", 800, 700);
    
   
    //c->SetLogx();
    //c->SetLogy();

    // Draw histogram
    hist->GetXaxis()->SetTitle("phi");
    hist->GetXaxis()->SetTitleSize(0.04);
    hist->GetYaxis()->SetTitle("N_{Events}");
    hist->GetYaxis()->SetTitleSize(0.04);
    hist->DrawClone();
    

    // Draw labels
    TLatex label;
    label.SetTextAlign(22);
   // label.DrawLatex(0.55, 3.0e4, "#eta");
   // label.DrawLatex(0.77, 7.0e4, "#rho,#omega");
   // label.DrawLatex(1.20, 4.0e4, "#phi");
   // label.DrawLatex(4.40, 1.0e5, "J/#psi");
   // label.DrawLatex(4.60, 1.0e4, "#psi'");
    //label.DrawLatex(12.0, 2.0e4, "Y(1,2,3S)");
    //label.DrawLatex(91.0, 1.5e4, "Z");
   label.SetNDC(true);
    label.SetTextAlign(11);
    label.SetTextSize(0.04);
    label.DrawLatex(0.10, 0.92, "#bf{CMS Open Data}");
    label.SetTextAlign(31);
    label.DrawLatex(0.90, 0.92, "#sqrt{s} = 8 TeV, L_{int} = 11.6 fb^{-1}");

    // Save plot
    c->SaveAs("phistc.pdf");
   

    // Print cut-flow report
    report->Print();
}


int main() {
    phist();
}
