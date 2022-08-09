
//code for phi of positive muon
//Author-Jinu Raj,PHYS2801-SRFP 2022,CHEP-IISc Banglore



#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "Math/Vector4Dfwd.h"
#include "Math/Vector4D.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TStyle.h"



using namespace ROOT::VecOps;
float computephi(RVec<float>& pt, RVec<float>& eta, RVec<float>& phi, RVec<float>& mass) {
    ROOT::Math::PtEtaPhiMVector m1(pt[0], eta[0], phi[0], mass[0]);
    ROOT::Math::PtEtaPhiMVector m2(pt[1], eta[1], phi[1], mass[1]);
    return (m1 + m2).mass();
    


}
using namespace ROOT::VecOps;
float checking(RVec<int>& chargee,RVec<float>& phii)
{
 


if(chargee[0]== 1)
      return phii[0];
  //else
      //return etaa[1];

if (chargee[1]==1)
    return phii[1];
    //else 
        //return etaa[0];

}
 void phipos() {
 
 
 
 
 
 
 
 
 
 
 
    // Enable multi-threading
    // The default here is set to a single thread. You can choose the number of threads based on your system.
    ROOT::EnableImplicitMT(1);

    // Create dataframe from NanoAOD files
    ROOT::RDataFrame df("Events", "Run2012BC_DoubleMuParked_Muons.root");


    // Select events with exactly two muons
    auto df_2mu = df.Filter("nMuon == 2", "Events with exactly two muons");
    
    auto df_os=df_2mu.Filter("Muon_charge[0] != Muon_charge[1]","two muons with opposite charge" );
    
     
   //auto df_osn=df_os.Filter("Muon_charge[0] == -1  || Muon_charge[1] == -1","only negative muons");
  
  
  auto df_he=df_os.Define("mUon_phi",checking,{"Muon_charge","Muon_phi"});
  
  
    
  
  
  
  
     

     
   //Book histogram for muon_pt
     const auto bins = 700; // Number of bins in the histogram
     const auto low = -5; // Lower edge of the histogram
     const auto up = 5; // Upper edge of the histogram
     auto hist=df_he.Histo1D({"","",bins,low,up},"mUon_phi");
    
      
    
    // Request cut-flow report
    auto report = df_he.Report();

    // Create canvas for plotting muonpt
    gStyle->SetOptStat(1111111);
    gStyle->SetTextFont(42);
    auto c = new TCanvas("c", "", 800, 700);

  
    // Draw histogram
    hist->GetXaxis()->SetTitle("phi of #mu^{+}");
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
    c->SaveAs("phi pos1.pdf");
     report->Print();
          
      }    
          

int main() {
   phipos();
}
