#include <iostream>
#include "ROOTFunctions.h"
#include "DelphesFunctions.h"
#include "PhenoAnalyzer.h"
#include <time.h>

//--------------------------------------------------------------------------------------
// makeTree creates a TTree with branches that have data from Muon,
// MissingET and Jet branches of any .root source file (TTree Delphes)
//--------------------------------------------------------------------------------------

int main(int argc, char *argv[]){

  // Loading data from a TChain file
  TChain chain("Delphes");
  chain.Add(argv[1]);
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);

  // Retrieving the seleted Branches
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchEvent = treeReader->UseBranch("Event");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");
  TClonesArray *branchJet = treeReader->UseBranch("Jet");

  Long64_t numberOfEntries = treeReader->GetEntries();

  // Creating the output file
  TFile * rawOutputFile = new TFile(argv[2], "RECREATE");

  // Creating a TTree for the output data
  TTree *simu = new TTree("simu","Raw Data from Delphes");

  // Declaring Muon variables
  Float_t PT, Eta, Phi, T;
  Int_t Charge;
  // Declaring MissingET (M_)
  Float_t M_MET, M_Eta, M_Phi;
  // Declaring Jet (J_) variables
  Float_t J_PT,J_Eta, J_Phi, J_T, J_Mass, J_DeltaEta, J_DeltaPhi, J_EhadOverEem, J_Beta, J_BetaStar, J_MeanSqDeltaR, J_PTD, J_FracPt, J_Tau1, J_Tau2, J_Tau3, J_Tau4, J_Tau5;
  Int_t J_Charge, J_NCharged, J_NNeutrals;
  // Declaring a target variable
  Int_t type;

  // Creating one Branch for each variable
  simu->Branch("PT",     &PT,     "PT/F");
  simu->Branch("Eta",    &Eta,    "Eta/F");
  simu->Branch("Phi",    &Phi,    "Phi/F");
  simu->Branch("Charge", &Charge, "Charge/I");
  simu->Branch("M_MET",  &M_MET,  "M_MET/F");
  simu->Branch("M_Eta",  &M_Eta,  "M_Eta/F");
  simu->Branch("M_Phi",  &M_Phi,  "M_Phi/F");
  simu->Branch("J_PT",  &J_PT,  "J_PT/F");
  simu->Branch("J_Eta",  &J_Eta,  "J_Eta/F");
  simu->Branch("J_Phi",  &J_Phi,  "J_Phi/F");
  simu->Branch("J_T",  &J_T,  "J_T/F");
  simu->Branch("J_Mass",  &J_Mass,  "J_Mass/F");
  simu->Branch("J_DeltaEta",  &J_DeltaEta,  "J_DeltaEta/F");
  simu->Branch("J_DeltaPhi",  &J_DeltaPhi,  "J_DeltaPhi/F");
  simu->Branch("J_EhadOverEem",  &J_EhadOverEem,  "J_EhadOverEem/F");
  simu->Branch("J_Beta",  &J_Beta,  "J_Beta/F");
  simu->Branch("J_BetaStar",  &J_BetaStar,  "J_BetaStar/F");
  simu->Branch("J_MeanSqDeltaR",  &J_MeanSqDeltaR,  "J_MeanSqDeltaR/F");
  simu->Branch("J_PTD",  &J_PTD,  "J_PTD/F");
  simu->Branch("J_FracPt",  &J_FracPt,  "J_FracPt/F");
  simu->Branch("J_Tau1",  &J_Tau1,  "J_Tau1/F");
  simu->Branch("J_Tau2",  &J_Tau2,  "J_Tau2/F");
  simu->Branch("J_Tau3",  &J_Tau3,  "J_Tau3/F");
  simu->Branch("J_Tau4",  &J_Tau4,  "J_Tau4/F");
  simu->Branch("J_Tau5",  &J_Tau5,  "J_Tau5/F");
  simu->Branch("J_Charge",  &J_Charge,  "J_Charge/I");
  simu->Branch("J_NCharged",  &J_NCharged,  "J_NCharged/I");
  simu->Branch("J_NNeutrals",  &J_NNeutrals,  "J_NNeutrals/I");
  simu->Branch("type", &type, "type/I");

  cout << "\n\nNumber of entries in the Tree: " << numberOfEntries <<endl;
  cout << "\nEmpty Tree:\n" << endl;
  simu->Print();

  for(Int_t entry = 0; entry < numberOfEntries; ++entry){
    treeReader->ReadEntry(entry);

    for (int muo = 0; muo < branchMuon->GetEntriesFast(); muo++){
      Muon *muon = (Muon*) branchMuon->At(muo);
      PT = muon->PT;
      Eta = muon->Eta;
      Phi = muon->Phi;
      Charge = muon->Charge;
    }

    for (int mis = 0; mis < branchMissingET->GetEntriesFast(); mis++){
      MissingET *missinget = (MissingET*) branchMissingET->At(mis);
      M_MET = missinget->MET;
      M_Eta = missinget->Eta;
      M_Phi = missinget->Phi;
    }

    for (int je = 0; je < branchJet->GetEntriesFast(); je++){
      Jet *jet= (Jet*) branchJet->At(je);
      J_PT = jet->PT;
      J_Eta = jet->Eta;
      J_Phi = jet->Phi;
      J_T = jet->T;
      J_Mass = jet->Mass;
      J_DeltaEta = jet->DeltaEta;
      J_DeltaPhi = jet->DeltaPhi;
      J_EhadOverEem = jet->EhadOverEem;
      J_Beta = jet->Beta;
      J_BetaStar = jet->BetaStar;
      J_MeanSqDeltaR = jet->MeanSqDeltaR;
      J_PTD = jet->PTD;
      J_FracPt = jet->FracPt[5];
      J_Tau1 = jet->Tau1;
      J_Tau2 = jet->Tau2;
      J_Tau3 = jet->Tau3;
      J_Tau4 = jet->Tau4;
      J_Tau5 = jet->Tau5;
      J_Charge = jet->Charge;
      J_NCharged = jet->NCharged;
      J_NNeutrals = jet->NNeutrals;
      }
      simu->Fill();
    }
  simu->Print();
  rawOutputFile->Write();
  rawOutputFile->Close();
}
