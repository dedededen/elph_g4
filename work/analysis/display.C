/*#include <iostream>
#include <fstream>
#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TGraph.h>
#include <TPad.h>
#include <TTree.h>

using namespace std;

Int_t main ()*/

void display(){

  /***Input File***/
  const Char_t* data_dir="../data/";
  const Int_t Data_N = 15;
  TFile* fin[Data_N];
  TTree* itree[Data_N];
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->Divide(4,4);
  for(int i=0;i<Data_N;i++){
    c1 -> cd(i+1);
    fin[i] = new TFile(Form("%swid_%d.root",data_dir,i+1),"read");
    itree[i] = (TTree*) fin[i] -> Get("ntuple");
    itree[i] -> Draw("pos_x:pos_y","par_id==1","colz");
    
  }
  c1 -> SaveAs("./pic/pos.png");
    
  TCanvas *c2 = new TCanvas("c2","c2");
  c2->Divide(4,4);
  TH1D* hist[Data_N];
  Double_t wid[Data_N];
  Double_t energy[Data_N]={};
  for(int i=0;i<Data_N;i++){
    hist[i] = new TH1D(Form("hist%d",i),Form("hist%d",i),100,0,100);
    c2 -> cd(i+1);
    itree[i] -> Draw(Form("energy>>hist%d",i),"par_id==1");

    wid[i] = i;
    energy[i] = hist[i] -> GetMean();
    energy[i] = log(energy[i]);
    cout << energy[i] << endl;
    
  }
  c2 -> SaveAs("./pic/energy.png");
  
  TCanvas *c3 = new TCanvas("c3","c3");
  TGraph *g1 = new TGraph(Data_N,wid,energy);
  g1 -> Draw("AL");
  g1 -> Fit("pol1");
  
}

