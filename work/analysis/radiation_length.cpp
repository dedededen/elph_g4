#include <iostream>
#include <fstream>
#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TPad.h>

using namespace std;

Int_t main (){

  /***Input File***/
  const Char_t* data_dir="~/Work/180901/data/";
  TFile *fin[2];
  fin[0] = new TFile(Form("%sgain_1.root",data_dir),"read");
  fin[1] = new TFile(Form("%sgain_2.root",data_dir),"read");
  TTree *itree[2];
  itree[0]= (TTree*) fin[0] -> Get("gain");
  itree[1]= (TTree*) fin[1] -> Get("gain");
    
  Double_t gain_read,gain_e_read,ramda_read,ramda_e_read;
  Int_t hv_read;
  itree[0] -> SetBranchAddress("gain",&gain_read);
  itree[0] -> SetBranchAddress("gain_e",&gain_e_read);
  itree[0] -> SetBranchAddress("ramda",&ramda_read);
  itree[0] -> SetBranchAddress("ramda_e",&ramda_e_read);
  itree[0] -> SetBranchAddress("HV",&hv_read);
  itree[1] -> SetBranchAddress("gain",&gain_read);
  itree[1] -> SetBranchAddress("gain_e",&gain_e_read);
  itree[1] -> SetBranchAddress("ramda",&ramda_read);
  itree[1] -> SetBranchAddress("ramda_e",&ramda_e_read);
  itree[1] -> SetBranchAddress("HV",&hv_read);
  
  const Int_t N1 = itree[0] -> GetEntries();
  const Int_t N2 = itree[1] -> GetEntries();
  Double_t HV1[2][N1], HV2[2][N2];
  Double_t G1[2][N1],G2[2][N2],GE1[2][N1],GE2[2][N2];
  Double_t R1[N1],R2[N2],RE1[N1],RE2[N2];
  
  for(Int_t i = 0; i < N1 ; i++){
    itree[0] -> GetEntry(i);
    HV1[0][i] =log( hv_read/1000.);
    G1[0][i] = log(gain_read);
    GE1[0][i] = gain_e_read/gain_read;

    HV1[1][i] = hv_read/1000.0;
    G1[1][i] = gain_read;
    GE1[1][i] = gain_e_read;
    R1[i] = ramda_read;
    RE1[i] = ramda_e_read;
  }
  fin[0] -> Close();
  fin[0] -> Delete();  
  for(Int_t i = 0; i < N2 ; i++){
    itree[1] -> GetEntry(i);    
    HV2[0][i] =log( hv_read/1000.);
    G2[0][i] = log(gain_read);
    GE2[0][i] = gain_e_read/gain_read;
    
    HV2[1][i] = hv_read/1000.;
    G2[1][i] = gain_read;
    GE2[1][i] = gain_e_read;
    R2[i] = ramda_read;
    RE2[i] = ramda_e_read;
  }
  fin[1] -> Close();
  fin[1] -> Delete();

  /***Fit**/
  TCanvas *c0 = new TCanvas("c0","c0");
  Double_t fit_par1[2];
  Double_t fit_par_e1[2];
  Double_t fit_par2[2];
  Double_t fit_par_e2[2];
  TF1 *f0 = new TF1("f0","[0]+x*[1]");
  TGraphErrors *g0_1 = new TGraphErrors( N1 , HV1[0], G1[0], 0, GE1[0]);
  TGraphErrors *g0_2 = new TGraphErrors( N2 , HV2[0], G2[0], 0, GE2[0]);
  g0_1 -> Fit("f0");
  fit_par1[0] = f0 -> GetParameter(0);  
  fit_par1[0] = exp(fit_par1[0]);
  fit_par_e1[0] = f0 -> GetParError(0);
  fit_par_e1[0] = fit_par1[0] * fit_par_e1[0];
  fit_par1[1] = f0 -> GetParameter(1);
  fit_par_e1[1] = f0 -> GetParError(1);

  g0_2 -> Fit("f0","+");
  fit_par2[0] = f0 -> GetParameter(0);
  fit_par2[0] = exp(fit_par2[0]);
  fit_par_e2[0] = f0 -> GetParError(0);
  fit_par_e2[0] = fit_par2[0] * fit_par_e2[0];
  fit_par2[1] = f0 -> GetParameter(1);
  fit_par_e2[1] = f0 -> GetParError(1);

  g0_2 -> Draw("AP");
  g0_1 -> Draw("P");
  c0 -> SaveAs("./pic/fitting_line.pdf");
  

  /***plot***/
  TGraphErrors *g1 = new TGraphErrors( N1 , HV1[1], G1[1], 0, GE1[1]);
  TGraphErrors *r1 = new TGraphErrors( N1 , HV1[1], R1, 0, RE1);
  TGraphErrors *g2 = new TGraphErrors( N2 , HV2[1], G2[1], 0, GE2[1]);
  TGraphErrors *r2 = new TGraphErrors( N2 , HV2[1], R2, 0, RE2);
  
  TF1 *f1 = new TF1("f1","[0]*pow(x,[1])");
  f1 -> SetParameters(fit_par1[0],fit_par1[1]);
  TGraph *gf1 = new TGraph(f1);
  TF1 *f2 = new TF1("f2","[0]*pow(x,[1])");
  f2 -> SetParameters(fit_par2[0],fit_par2[1]);
  TGraph *gf2 = new TGraph(f2);
  
  TCanvas *c1 = new TCanvas("c1","c1");
  c1 -> Divide(2,1);
  
  c1 -> cd(1);
  g1->SetLineColor(2);
  g1->SetMarkerColor(2);
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  g2->GetYaxis()->SetMoreLogLabels();
  g2->GetXaxis()->SetMoreLogLabels();
  g2->SetMaximum(4*1e+6);
  g2->SetMinimum(7*1e+4);
  g2->SetTitle("Gain vs HV");
  gf2 ->SetLineColor(1);
  gf1 ->SetLineColor(2);
  g2 -> Draw("AP");
  g1 -> Draw("P");
  gf1 -> Draw("L");
  gf2 -> Draw("L");
  
  c1 -> cd(2);
  r1->SetLineColor(2);
  r1->SetMarkerColor(2);
  r2->SetMaximum(10);
  r2->SetMinimum(2);
  r2->SetTitle("Ramda vs HV");
  r2 -> Draw("AP");
  r1 -> Draw("P");

  c1 -> SaveAs("./pic/gain_cureve.pdf");
  
  /*** cal ***/  
  cout << "Red!!" << endl;
  cout << "a is " << fit_par1[0] 
       << " +/- " << fit_par_e1[0] << endl;
  cout << "b is " << fit_par1[1] 
       << " +/- " << fit_par_e1[1] << endl;
  cout << "gain_500 V is " << fit_par1[0]*pow(0.5,fit_par1[1]) << " +/- "
       << fit_par1[0]*pow(0.5,fit_par1[1]) * sqrt( pow(fit_par_e1[0]/fit_par1[0],2.)+pow(log(0.5)*fit_par_e1[1],2.) )
       << endl; 
  cout << "gain_1000 V is " << fit_par1[0]*pow(1.,fit_par1[1]) << " +/- "
       << fit_par1[0]*pow(1.,fit_par1[1]) * sqrt( pow(fit_par_e1[0]/fit_par1[0],2.)+pow(log(1.)*fit_par_e1[1],2.) )
       << endl; 
    
  cout << "Black!!" << endl;
  cout << "a is " << fit_par2[0] 
       << " +/- " << fit_par_e2[0] << endl;
  cout << "b is " << fit_par2[1] 
       << " +/- " << fit_par_e2[1] << endl;
  cout << "gain_500 V is " << fit_par2[0]*pow(0.5,fit_par2[1]) << " +/- "
       << fit_par2[0]*pow(0.5,fit_par2[1]) * sqrt( pow(fit_par_e2[0]/fit_par2[0],2.)+pow(log(0.5)*fit_par_e2[1],2.) )
       << endl; 
  cout << "gain_1000 V is " << fit_par2[0]*pow(1.,fit_par2[1]) << " +/- "
       << fit_par2[0]*pow(1.,fit_par2[1]) * sqrt( pow(fit_par_e2[0]/fit_par2[0],2.)+pow(log(1.)*fit_par_e2[1],2.) )
       << endl;  

  return 1;
}

