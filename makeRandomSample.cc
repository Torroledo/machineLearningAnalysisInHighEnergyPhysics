#include <iostream>
#include <algorithm>
#include <time.h>
#include <random>

extern const string back1 = "W+jets.root";
extern const string back2 = "DY+jets.root";

void selectRandom(std::string inFolder, std::string outFolder, std::string signal);
void randomSampleNoCuts(){

  // 1. Load each Tree individually
  std::string inFolder = "fullSample/";
  std::string outFolder = "randomSample/";

  std::string signal2 = "signal_0p5TeV.root";
  std::string signal3 = "signal_1p0TeV.root";
  std::string signal4 = "signal_1p25TeV.root";
  std::string signal5 = "signal_2p0TeV.root";

  if(true){
    selectRandom(inFolder, outFolder, signal2);
    selectRandom(inFolder, outFolder, signal3);
    selectRandom(inFolder, outFolder, signal4);
    selectRandom(inFolder, outFolder, signal5);
  }
}

void selectRandom(std::string inFolder, std::string outFolder, std::string filename){

  // Loading signal data from .root file
  TFile* signalFile1 = new TFile((inFolder + filename).c_str());
  TTree* treeSignal = (TTree *) signalFile1->Get("totalSimulation");
  TFile* backFile1 = new TFile((inFolder + back1).c_str());
  TTree* treeBack1 = (TTree *) backFile1->Get("totalSimulation");
  TFile* backFile2 = new TFile((inFolder + back2).c_str());
  TTree* treeBack2 = (TTree *) backFile2->Get("totalSimulation");
  std::string prefix = "joined_";

  // Creating a final marged TTree
  TFile* finalData = new TFile((outFolder + prefix + filename).c_str(),"RECREATE");
  TTree* totalSimulation = new TTree("totalSimulation","Joined Normalized Data");

  // INPUT VARIABLES && OUTPUT VARIABLES
  // Declaring TAUS variables
  Int_t Tau_Charge, Tau_Charge_1, Tau_Charge_2;
  Float_t Tau_PT_sum, Tau_PT_dif, Tau_PT_1, Tau_PT_2;
  Float_t Tau_Mass_sum, Tau_Mass_dif, Tau_Mass_1, Tau_Mass_2;
  Float_t Tau_Ener_sum, Tau_Ener_1, Tau_Ener_2;
  Float_t Tau_Eta_dif, Tau_Eta_1, Tau_Eta_2;
  Float_t Tau_Phi_dif, Tau_Phi_1, Tau_Phi_2;
  Float_t Tau_DeltaEta, Tau_DeltaPhi;
  Float_t Tau_EhadOverEem;

  // Declaring TAGGING variables
  Int_t BTag,TauTag,type,type_2;

  // Declaring MISS ET variables
  Float_t Miss_MET, Miss_Eta, Miss_Phi;

  // Declaring output variables JETS
  Int_t Jet_Charge, Jet_Charge_1, Jet_Charge_2;
  Float_t Jet_PT_sum, Jet_PT_dif, Jet_PT_1, Jet_PT_2;
  Float_t Jet_Mass_sum, Jet_Mass_dif, Jet_Mass_1, Jet_Mass_2;
  Float_t Jet_Ener_sum, Jet_Ener_1, Jet_Ener_2;
  Float_t Jet_Eta_dif, Jet_Eta_1, Jet_Eta_2;
  Float_t Jet_Phi_dif, Jet_Phi_1, Jet_Phi_2;
  Float_t Jet_DeltaEta, Jet_DeltaPhi;
  Float_t Jet_T_1, Jet_T_2, Jet_BetaStar_1, Jet_BetaStar_2;
  Float_t Jet_EhadOverEem_1, Jet_EhadOverEem_2;
  Float_t Jet_MeanSqDeltaR_1, Jet_MeanSqDeltaR_2;
  Float_t Jet_PTD_1, Jet_PTD_2, Jet_Beta_1,Jet_Beta_2;

  treeSignal->SetBranchAddress("type", &type);
  treeSignal->SetBranchAddress("type_2", &type_2);
  treeSignal->SetBranchAddress("Tau_PT_sum",  &Tau_PT_sum);
  treeSignal->SetBranchAddress("Tau_PT_dif",  &Tau_PT_dif);
  treeSignal->SetBranchAddress("Tau_PT_1",  &Tau_PT_1);
  treeSignal->SetBranchAddress("Tau_PT_2",  &Tau_PT_2);
  treeSignal->SetBranchAddress("Tau_Eta_dif",  &Tau_Eta_dif);
  treeSignal->SetBranchAddress("Tau_Eta_1",  &Tau_Eta_1);
  treeSignal->SetBranchAddress("Tau_Eta_2",  &Tau_Eta_2);
  treeSignal->SetBranchAddress("Tau_Phi_dif",  &Tau_Phi_dif);
  treeSignal->SetBranchAddress("Tau_Phi_1",  &Tau_Phi_1);
  treeSignal->SetBranchAddress("Tau_Phi_2",  &Tau_Phi_2);
  treeSignal->SetBranchAddress("Tau_DeltaEta",  &Tau_DeltaEta);
  treeSignal->SetBranchAddress("Tau_DeltaPhi",  &Tau_DeltaPhi);
  treeSignal->SetBranchAddress("Tau_Charge_1",  &Tau_Charge_1);
  treeSignal->SetBranchAddress("Tau_Charge_2",  &Tau_Charge_2);
  treeSignal->SetBranchAddress("Tau_Mass_sum",  &Tau_Mass_sum);
  treeSignal->SetBranchAddress("Tau_Mass_dif",  &Tau_Mass_dif);
  treeSignal->SetBranchAddress("Tau_Mass_1",  &Tau_Mass_1);
  treeSignal->SetBranchAddress("Tau_Mass_2",  &Tau_Mass_2);
  treeSignal->SetBranchAddress("TauTag",  &TauTag);
  treeSignal->SetBranchAddress("Tau_Ener_sum",  &Tau_Ener_sum);
  treeSignal->SetBranchAddress("Tau_Ener_1",  &Tau_Ener_1);
  treeSignal->SetBranchAddress("Tau_Ener_2",  &Tau_Ener_2);
  treeSignal->SetBranchAddress("Miss_MET",  &Miss_MET);
  treeSignal->SetBranchAddress("Miss_Eta",  &Miss_Eta);
  treeSignal->SetBranchAddress("Miss_Phi",  &Miss_Phi);
  treeSignal->SetBranchAddress("Jet_PT_sum",   &Jet_PT_sum);
  treeSignal->SetBranchAddress("Jet_PT_dif",   &Jet_PT_dif);
  treeSignal->SetBranchAddress("Jet_PT_1",   &Jet_PT_1);
  treeSignal->SetBranchAddress("Jet_PT_2",   &Jet_PT_2);
  treeSignal->SetBranchAddress("Jet_Mass_sum", &Jet_Mass_sum);
  treeSignal->SetBranchAddress("Jet_Mass_dif", &Jet_Mass_dif);
  treeSignal->SetBranchAddress("Jet_Mass_1", &Jet_Mass_1);
  treeSignal->SetBranchAddress("Jet_Mass_2",&Jet_Mass_2);
  treeSignal->SetBranchAddress("Jet_Eta_dif",  &Jet_Eta_dif);
  treeSignal->SetBranchAddress("Jet_Eta_1",  &Jet_Eta_1);
  treeSignal->SetBranchAddress("Jet_Eta_2",  &Jet_Eta_2);
  treeSignal->SetBranchAddress("Jet_Phi_dif",  &Jet_Phi_dif);
  treeSignal->SetBranchAddress("Jet_Phi_1",  &Jet_Phi_1);
  treeSignal->SetBranchAddress("Jet_Phi_2",  &Jet_Phi_2);
  treeSignal->SetBranchAddress("Jet_DeltaEta",    &Jet_DeltaEta);
  treeSignal->SetBranchAddress("Jet_DeltaPhi",    &Jet_DeltaPhi);
  treeSignal->SetBranchAddress("Jet_T_1",    &Jet_T_1);
  treeSignal->SetBranchAddress("Jet_T_2",    &Jet_T_2);
  treeSignal->SetBranchAddress("Jet_Charge_1",  &Jet_Charge_1);
  treeSignal->SetBranchAddress("Jet_Charge_2",  &Jet_Charge_2);
  treeSignal->SetBranchAddress("Jet_EhadOverEem_1", &Jet_EhadOverEem_1);
  treeSignal->SetBranchAddress("Jet_EhadOverEem_2", &Jet_EhadOverEem_2);
  treeSignal->SetBranchAddress("Jet_Ener_sum", &Jet_Ener_sum);
  treeSignal->SetBranchAddress("Jet_Ener_1", &Jet_Ener_1);
  treeSignal->SetBranchAddress("Jet_Ener_2",&Jet_Ener_2);
  treeSignal->SetBranchAddress("BTag", &BTag);

  treeBack1->SetBranchAddress("type", &type);
  treeBack1->SetBranchAddress("type_2", &type_2);
  treeBack1->SetBranchAddress("Tau_PT_sum",  &Tau_PT_sum);
  treeBack1->SetBranchAddress("Tau_PT_dif",  &Tau_PT_dif);
  treeBack1->SetBranchAddress("Tau_PT_1",  &Tau_PT_1);
  treeBack1->SetBranchAddress("Tau_PT_2",  &Tau_PT_2);
  treeBack1->SetBranchAddress("Tau_Eta_dif",  &Tau_Eta_dif);
  treeBack1->SetBranchAddress("Tau_Eta_1",  &Tau_Eta_1);
  treeBack1->SetBranchAddress("Tau_Eta_2",  &Tau_Eta_2);
  treeBack1->SetBranchAddress("Tau_Phi_dif",  &Tau_Phi_dif);
  treeBack1->SetBranchAddress("Tau_Phi_1",  &Tau_Phi_1);
  treeBack1->SetBranchAddress("Tau_Phi_2",  &Tau_Phi_2);
  treeBack1->SetBranchAddress("Tau_DeltaEta",  &Tau_DeltaEta);
  treeBack1->SetBranchAddress("Tau_DeltaPhi",  &Tau_DeltaPhi);
  treeBack1->SetBranchAddress("Tau_Charge_1",  &Tau_Charge_1);
  treeBack1->SetBranchAddress("Tau_Charge_2",  &Tau_Charge_2);
  treeBack1->SetBranchAddress("Tau_Mass_sum",  &Tau_Mass_sum);
  treeBack1->SetBranchAddress("Tau_Mass_dif",  &Tau_Mass_dif);
  treeBack1->SetBranchAddress("Tau_Mass_1",  &Tau_Mass_1);
  treeBack1->SetBranchAddress("Tau_Mass_2",  &Tau_Mass_2);
  treeBack1->SetBranchAddress("TauTag",  &TauTag);
  treeBack1->SetBranchAddress("Tau_Ener_sum",  &Tau_Ener_sum);
  treeBack1->SetBranchAddress("Tau_Ener_1",  &Tau_Ener_1);
  treeBack1->SetBranchAddress("Tau_Ener_2",  &Tau_Ener_2);
  treeBack1->SetBranchAddress("Miss_MET",  &Miss_MET);
  treeBack1->SetBranchAddress("Miss_Eta",  &Miss_Eta);
  treeBack1->SetBranchAddress("Miss_Phi",  &Miss_Phi);
  treeBack1->SetBranchAddress("Jet_PT_sum",   &Jet_PT_sum);
  treeBack1->SetBranchAddress("Jet_PT_dif",   &Jet_PT_dif);
  treeBack1->SetBranchAddress("Jet_PT_1",   &Jet_PT_1);
  treeBack1->SetBranchAddress("Jet_PT_2",   &Jet_PT_2);
  treeBack1->SetBranchAddress("Jet_Mass_sum", &Jet_Mass_sum);
  treeBack1->SetBranchAddress("Jet_Mass_dif", &Jet_Mass_dif);
  treeBack1->SetBranchAddress("Jet_Mass_1", &Jet_Mass_1);
  treeBack1->SetBranchAddress("Jet_Mass_2",&Jet_Mass_2);
  treeBack1->SetBranchAddress("Jet_Eta_dif",  &Jet_Eta_dif);
  treeBack1->SetBranchAddress("Jet_Eta_1",  &Jet_Eta_1);
  treeBack1->SetBranchAddress("Jet_Eta_2",  &Jet_Eta_2);
  treeBack1->SetBranchAddress("Jet_Phi_dif",  &Jet_Phi_dif);
  treeBack1->SetBranchAddress("Jet_Phi_1",  &Jet_Phi_1);
  treeBack1->SetBranchAddress("Jet_Phi_2",  &Jet_Phi_2);
  treeBack1->SetBranchAddress("Jet_DeltaEta",    &Jet_DeltaEta);
  treeBack1->SetBranchAddress("Jet_DeltaPhi",    &Jet_DeltaPhi);
  treeBack1->SetBranchAddress("Jet_T_1",    &Jet_T_1);
  treeBack1->SetBranchAddress("Jet_T_2",    &Jet_T_2);
  treeBack1->SetBranchAddress("Jet_Charge_1",  &Jet_Charge_1);
  treeBack1->SetBranchAddress("Jet_Charge_2",  &Jet_Charge_2);
  treeBack1->SetBranchAddress("Jet_EhadOverEem_1", &Jet_EhadOverEem_1);
  treeBack1->SetBranchAddress("Jet_EhadOverEem_2", &Jet_EhadOverEem_2);
  treeBack1->SetBranchAddress("Jet_Ener_sum", &Jet_Ener_sum);
  treeBack1->SetBranchAddress("Jet_Ener_1", &Jet_Ener_1);
  treeBack1->SetBranchAddress("Jet_Ener_2",&Jet_Ener_2);
  treeBack1->SetBranchAddress("BTag", &BTag);

  treeBack2->SetBranchAddress("type", &type);
  treeBack2->SetBranchAddress("type_2", &type_2);
  treeBack2->SetBranchAddress("Tau_PT_sum",  &Tau_PT_sum);
  treeBack2->SetBranchAddress("Tau_PT_dif",  &Tau_PT_dif);
  treeBack2->SetBranchAddress("Tau_PT_1",  &Tau_PT_1);
  treeBack2->SetBranchAddress("Tau_PT_2",  &Tau_PT_2);
  treeBack2->SetBranchAddress("Tau_Eta_dif",  &Tau_Eta_dif);
  treeBack2->SetBranchAddress("Tau_Eta_1",  &Tau_Eta_1);
  treeBack2->SetBranchAddress("Tau_Eta_2",  &Tau_Eta_2);
  treeBack2->SetBranchAddress("Tau_Phi_dif",  &Tau_Phi_dif);
  treeBack2->SetBranchAddress("Tau_Phi_1",  &Tau_Phi_1);
  treeBack2->SetBranchAddress("Tau_Phi_2",  &Tau_Phi_2);
  treeBack2->SetBranchAddress("Tau_DeltaEta",  &Tau_DeltaEta);
  treeBack2->SetBranchAddress("Tau_DeltaPhi",  &Tau_DeltaPhi);
  treeBack2->SetBranchAddress("Tau_Charge_1",  &Tau_Charge_1);
  treeBack2->SetBranchAddress("Tau_Charge_2",  &Tau_Charge_2);
  treeBack2->SetBranchAddress("Tau_Mass_sum",  &Tau_Mass_sum);
  treeBack2->SetBranchAddress("Tau_Mass_dif",  &Tau_Mass_dif);
  treeBack2->SetBranchAddress("Tau_Mass_1",  &Tau_Mass_1);
  treeBack2->SetBranchAddress("Tau_Mass_2",  &Tau_Mass_2);
  treeBack2->SetBranchAddress("TauTag",  &TauTag);
  treeBack2->SetBranchAddress("Tau_Ener_sum",  &Tau_Ener_sum);
  treeBack2->SetBranchAddress("Tau_Ener_1",  &Tau_Ener_1);
  treeBack2->SetBranchAddress("Tau_Ener_2",  &Tau_Ener_2);
  treeBack2->SetBranchAddress("Miss_MET",  &Miss_MET);
  treeBack2->SetBranchAddress("Miss_Eta",  &Miss_Eta);
  treeBack2->SetBranchAddress("Miss_Phi",  &Miss_Phi);
  treeBack2->SetBranchAddress("Jet_PT_sum",   &Jet_PT_sum);
  treeBack2->SetBranchAddress("Jet_PT_dif",   &Jet_PT_dif);
  treeBack2->SetBranchAddress("Jet_PT_1",   &Jet_PT_1);
  treeBack2->SetBranchAddress("Jet_PT_2",   &Jet_PT_2);
  treeBack2->SetBranchAddress("Jet_Mass_sum", &Jet_Mass_sum);
  treeBack2->SetBranchAddress("Jet_Mass_dif", &Jet_Mass_dif);
  treeBack2->SetBranchAddress("Jet_Mass_1", &Jet_Mass_1);
  treeBack2->SetBranchAddress("Jet_Mass_2",&Jet_Mass_2);
  treeBack2->SetBranchAddress("Jet_Eta_dif",  &Jet_Eta_dif);
  treeBack2->SetBranchAddress("Jet_Eta_1",  &Jet_Eta_1);
  treeBack2->SetBranchAddress("Jet_Eta_2",  &Jet_Eta_2);
  treeBack2->SetBranchAddress("Jet_Phi_dif",  &Jet_Phi_dif);
  treeBack2->SetBranchAddress("Jet_Phi_1",  &Jet_Phi_1);
  treeBack2->SetBranchAddress("Jet_Phi_2",  &Jet_Phi_2);
  treeBack2->SetBranchAddress("Jet_DeltaEta",    &Jet_DeltaEta);
  treeBack2->SetBranchAddress("Jet_DeltaPhi",    &Jet_DeltaPhi);
  treeBack2->SetBranchAddress("Jet_T_1",    &Jet_T_1);
  treeBack2->SetBranchAddress("Jet_T_2",    &Jet_T_2);
  treeBack2->SetBranchAddress("Jet_Charge_1",  &Jet_Charge_1);
  treeBack2->SetBranchAddress("Jet_Charge_2",  &Jet_Charge_2);
  treeBack2->SetBranchAddress("Jet_EhadOverEem_1", &Jet_EhadOverEem_1);
  treeBack2->SetBranchAddress("Jet_EhadOverEem_2", &Jet_EhadOverEem_2);
  treeBack2->SetBranchAddress("Jet_Ener_sum", &Jet_Ener_sum);
  treeBack2->SetBranchAddress("Jet_Ener_1", &Jet_Ener_1);
  treeBack2->SetBranchAddress("Jet_Ener_2",&Jet_Ener_2);
  treeBack2->SetBranchAddress("BTag", &BTag);

  totalSimulation->Branch("type", &type);
  totalSimulation->Branch("type_2", &type_2);
  totalSimulation->Branch("Tau_PT_sum",  &Tau_PT_sum);
  totalSimulation->Branch("Tau_PT_dif",  &Tau_PT_dif);
  totalSimulation->Branch("Tau_PT_1",  &Tau_PT_1);
  totalSimulation->Branch("Tau_PT_2",  &Tau_PT_2);
  totalSimulation->Branch("Tau_Eta_dif",  &Tau_Eta_dif);
  totalSimulation->Branch("Tau_Eta_1",  &Tau_Eta_1);
  totalSimulation->Branch("Tau_Eta_2",  &Tau_Eta_2);
  totalSimulation->Branch("Tau_Phi_dif",  &Tau_Phi_dif);
  totalSimulation->Branch("Tau_Phi_1",  &Tau_Phi_1);
  totalSimulation->Branch("Tau_Phi_2",  &Tau_Phi_2);
  totalSimulation->Branch("Tau_DeltaEta",  &Tau_DeltaEta);
  totalSimulation->Branch("Tau_DeltaPhi",  &Tau_DeltaPhi);
  totalSimulation->Branch("Tau_Charge_1",  &Tau_Charge_1);
  totalSimulation->Branch("Tau_Charge_2",  &Tau_Charge_2);
  totalSimulation->Branch("Tau_Mass_sum",  &Tau_Mass_sum);
  totalSimulation->Branch("Tau_Mass_dif",  &Tau_Mass_dif);
  totalSimulation->Branch("Tau_Mass_1",  &Tau_Mass_1);
  totalSimulation->Branch("Tau_Mass_2",  &Tau_Mass_2);
  totalSimulation->Branch("TauTag",  &TauTag);
  totalSimulation->Branch("Tau_Ener_sum",  &Tau_Ener_sum);
  totalSimulation->Branch("Tau_Ener_1",  &Tau_Ener_1);
  totalSimulation->Branch("Tau_Ener_2",  &Tau_Ener_2);
  totalSimulation->Branch("Miss_MET",  &Miss_MET);
  totalSimulation->Branch("Miss_Eta",  &Miss_Eta);
  totalSimulation->Branch("Miss_Phi",  &Miss_Phi);
  totalSimulation->Branch("Jet_PT_sum",   &Jet_PT_sum);
  totalSimulation->Branch("Jet_PT_dif",   &Jet_PT_dif);
  totalSimulation->Branch("Jet_PT_1",   &Jet_PT_1);
  totalSimulation->Branch("Jet_PT_2",   &Jet_PT_2);
  totalSimulation->Branch("Jet_Mass_sum", &Jet_Mass_sum);
  totalSimulation->Branch("Jet_Mass_dif", &Jet_Mass_dif);
  totalSimulation->Branch("Jet_Mass_1", &Jet_Mass_1);
  totalSimulation->Branch("Jet_Mass_2",&Jet_Mass_2);
  totalSimulation->Branch("Jet_Eta_dif",  &Jet_Eta_dif);
  totalSimulation->Branch("Jet_Eta_1",  &Jet_Eta_1);
  totalSimulation->Branch("Jet_Eta_2",  &Jet_Eta_2);
  totalSimulation->Branch("Jet_Phi_dif",  &Jet_Phi_dif);
  totalSimulation->Branch("Jet_Phi_1",  &Jet_Phi_1);
  totalSimulation->Branch("Jet_Phi_2",  &Jet_Phi_2);
  totalSimulation->Branch("Jet_DeltaEta",    &Jet_DeltaEta);
  totalSimulation->Branch("Jet_DeltaPhi",    &Jet_DeltaPhi);
  totalSimulation->Branch("Jet_T_1",    &Jet_T_1);
  totalSimulation->Branch("Jet_T_2",    &Jet_T_2);
  totalSimulation->Branch("Jet_Charge_1",  &Jet_Charge_1);
  totalSimulation->Branch("Jet_Charge_2",  &Jet_Charge_2);
  totalSimulation->Branch("Jet_EhadOverEem_1", &Jet_EhadOverEem_1);
  totalSimulation->Branch("Jet_EhadOverEem_2", &Jet_EhadOverEem_2);
  totalSimulation->Branch("Jet_Ener_sum", &Jet_Ener_sum);
  totalSimulation->Branch("Jet_Ener_1", &Jet_Ener_1);
  totalSimulation->Branch("Jet_Ener_2",&Jet_Ener_2);
  totalSimulation->Branch("BTag", &BTag);

  // Number of entries
  int signalEntries = treeSignal->GetEntries();
  int back1Entries = treeBack1->GetEntries();
  int back2Entries = treeBack2->GetEntries();
  int sample_size = (int)signalEntries/2;

  cout << "\nTree " << filename << " has : " << signalEntries << " entries" << endl;
  cout << "Tree " << back1 << " has : " << back1Entries << " entries" << endl;
  cout << "Tree " << back2 << " has : " << back2Entries << " entries\n" << endl;

  // ------------------- set the random entries to select ------------------
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution1(0,back1Entries);
  std::uniform_int_distribution<int> distribution2(0,back2Entries);
  // ------------------- set the random entries to select ------------------

  TCanvas* c1 = new TCanvas("c1","random number sample 1",200,10,600,400);
  TCanvas* c2 = new TCanvas("c2","random number sample 2",200,10,600,400);

  TH1I * h1  = new TH1I("h1","sample 1",100,0.,-5.0);
  TH1I * h2  = new TH1I("h2","sample 2",100,0.,-5.0);

  int entry;
  int entries1[sample_size], entries2[sample_size];

  // signal
  cout << "Selecting from signal: " << filename << endl;
  for (int sample_i = 0; sample_i < signalEntries; ++sample_i){
    treeSignal->GetEntry(sample_i);
    totalSimulation->Fill();
    if(!(sample_i%100)){
      cout << "Entryi : "<< sample_i << endl;
    }
  }

  // back1
  cout << "Selecting from Background 1"<< endl;
  for (int sample_i = 0; sample_i < sample_size; ++sample_i){
    entry = distribution1(generator);
    entries1[sample_i] = entry;

     h1->Fill(entry);
     treeBack1->GetEntry(entry);
     totalSimulation->Fill();

    if(!(sample_i%100)){
      cout << "Sample_i : "<< sample_i << " Entry : " << entry << endl;
    }
    // cout << "Tau_PT_sum : " << Tau_PT_sum << endl;
  }
  // back2
  cout << "Selecting from Background 2" << endl;
  for (int sample_i = 0; sample_i < sample_size; ++sample_i){
    entry = distribution2(generator);
    entries2[sample_i] = entry;

    h2->Fill(entry);
    treeBack2->GetEntry(entry);
    totalSimulation->Fill();

    if(!(sample_i%100)){
      cout << "Sample_i : "<< sample_i << " Entry : " << entry << endl;
    }
    // cout << "Tau_PT_sum : " << Tau_PT_sum << endl;
  }
  c1->cd(); h1->Draw();
  c2->cd(); h2->Draw();
  std::string writeTo1 = "sample_1.pdf";
  std::string writeTo2 = "sample_2.pdf";

  c1->Print((outFolder + filename + writeTo1).c_str());
  c2->Print((outFolder + filename + writeTo2).c_str());
  cout << totalSimulation->GetEntries() << " gotten entries " << endl;
  finalData->Write();
  finalData->Close();
}
