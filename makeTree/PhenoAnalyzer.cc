////////////////////////////////////////////////////////////////
//                                                            //
// Author: Andrés Flórez, Universidad de los Andes, Colombia  //
//                                                            //
////////////////////////////////////////////////////////////////



#include <iostream>
#include "ROOTFunctions.h"
#include "DelphesFunctions.h"
#include "PhenoAnalyzer.h"
#include <time.h>

int main(int argc, char *argv[]) {

  //TApplication app("App",&argc, argv);
  TChain chain("Delphes");
  chain.Add(argv[1]);
  TFile * HistoOutputFile = new TFile(argv[2], "RECREATE");
  int nDir = 11;
  TDirectory *theDirectory[nDir];
  theDirectory[0]  = HistoOutputFile->mkdir("No_cuts");
  theDirectory[1]  = HistoOutputFile->mkdir("Muon_one_pT_eTa_min");
  theDirectory[2]  = HistoOutputFile->mkdir("Muon_two_pT_eTa_min");
  theDirectory[3]  = HistoOutputFile->mkdir("N_muons");
  theDirectory[4]  = HistoOutputFile->mkdir("N_bjets");
  theDirectory[5]  = HistoOutputFile->mkdir("Lead_jet_pT");
  theDirectory[6]  = HistoOutputFile->mkdir("SubLead_jet_pT");
  theDirectory[7]  = HistoOutputFile->mkdir("MET");
  theDirectory[8]  = HistoOutputFile->mkdir("VBF_jets_opposite_hemispheres");
  theDirectory[9]  = HistoOutputFile->mkdir("VBF_jets_delta_eta");
  theDirectory[10]  = HistoOutputFile->mkdir("VBF_diJetMass");
  PhenoAnalysis BSM_analysis(chain, HistoOutputFile, theDirectory, nDir);

}

using namespace std;
PhenoAnalysis::PhenoAnalysis(TChain& chain, TFile* theFile, TDirectory *cdDir[], int nDir)
{
  ifstream inFile;
  inFile.open ("config.in", ios::in);
  
  if (!inFile)
    {
      cerr << "ERROR: Can't open input file: " << endl;
      exit (1);
    }
  
  string inputType = "";
  
  //This set of lines are used to open and read the "config.in" file.
  ///////////////////////////////////////////////////////////////////////
  TEnv *params = new TEnv ("config_file");
  params->ReadFile ("config.in", kEnvChange);
  
  double lead_jet_pt      = params->GetValue ("lead_jet_pt", 30.);
  double jet_eta_max      = params->GetValue ("jet_eta_max", 5.0);
  double b_jet_pt_min     = params->GetValue ("b_jet_pt_min", 20.0);
  double DR_jet_lep_max   = params->GetValue ("DR_jet_lep_max", 0.3);
  double met_max          = params->GetValue ("met_max", 1000.);
  double jet_eta_product  = params->GetValue("jet_eta_product", 0);
  double jet_DEta         = params->GetValue("jet_DEta", 4.0);
  double min_diJetmass    = params->GetValue("min_diJetmass", 500.);
  double muon_pt_min      = params->GetValue("muon_pt_min", 0.);
  crateHistoMasps(nDir);
  
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  
  TClonesArray *branchJet = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");
  MissingET *METpointer;
  
  for(Int_t entry = 0; entry < numberOfEntries; ++entry){
    
    treeReader->ReadEntry(entry);
    int pass_cuts[nDir] = {0};
    TLorentzVector Jet_leading_vec(0., 0., 0., 0.);
    TLorentzVector Jet_sleading_vec(0., 0., 0., 0.);
    TLorentzVector Jet_1(0., 0., 0., 0.);
    TLorentzVector Jet_2(0., 0., 0., 0.);
    TLorentzVector jet_i(0., 0., 0., 0.);
    TLorentzVector elec_i(0., 0., 0., 0.);
    TLorentzVector muon_i(0., 0., 0., 0.);
    TLorentzVector Muon1TLV (0., 0., 0., 0.);
    TLorentzVector Muon2TLV (0., 0., 0., 0.);
    
    bool is_b_jet = false;
    bool fill_muon1 = false;
    bool fill_muon2 = false;
    METpointer = (MissingET*) branchMissingET->At(0);
    double Met = METpointer->MET;
    double HT = 0.;
    double Met_phi = METpointer->Phi;
    int njets_counter = 0;
    int nmuon_counter = 0;
    int index_jet_lead = 0;
    double jet_min_pt = 20.0;
    double DiJetMass_min = 100.;
    int n_b_jets = 0;
    
    // Number of muons not overlaping with jets
    for (int muo = 0; muo < branchMuon->GetEntriesFast(); muo++){
      Muon *muon = (Muon*) branchMuon->At(muo);
      //      print("         Getting %d muo entry\n",muo);
      double muon_energy = calculateE(muon->Eta, muon->PT, 0.1056583715);
      muon_i.SetPtEtaPhiE(muon->PT, muon->Eta, muon->Phi, muon_energy);
      
      if ((muon->PT > 30.) &&  (abs(muon->Eta) < 2.5)){
        for (int j = 0; j < branchJet->GetEntriesFast(); j++){
          Jet *jet = (Jet*) branchJet->At(j);
          double jet_energy = calculateE(jet->Eta, jet->PT, jet->Mass);
          jet_i.SetPtEtaPhiE(jet->PT, jet->Eta, jet->Phi, jet_energy);
          double DR_jet_muon = jet_i.DeltaR(muon_i);
          if ((jet_i.Pt() > 20.0) && (abs(jet_i.Eta()) < 5.0) && (DR_jet_muon > DR_jet_lep_max)){
            if((fill_muon1 == false) && (fill_muon2 == false)){
              Muon1TLV.SetPtEtaPhiE(muon->PT, muon->Eta, muon->Phi, muon_energy);
              fill_muon1 = true;
              break; 
            }
            if((fill_muon1 == true) && (fill_muon2 == false)){
              Muon2TLV.SetPtEtaPhiE(muon->PT, muon->Eta, muon->Phi, muon_energy);
              fill_muon2 = true;
              break;
            }
          }
        }
        nmuon_counter++;
      }
    } //end muon number loop
    //    print("         Getting %d muo entry\n",muo);
    //////////////////Search leading jet and taus///////////
    for (int j = 0; j < branchJet->GetEntriesFast(); j++){
      
      bool is_jet_muon_overlap = false;
      bool is_jet_muon_overlap_2 = false;
      
      Jet *jet = (Jet*) branchJet->At(j);
      double jet_energy = calculateE(jet->Eta, jet->PT, jet->Mass);
      jet_i.SetPtEtaPhiE(jet->PT, jet->Eta, jet->Phi, jet_energy);
      
      // Check if jet overlaps with any muon
      for (int muo = 0; muo < branchMuon->GetEntriesFast(); muo++){
        Muon *muon = (Muon*) branchMuon->At(muo);
        double muon_energy = calculateE(muon->Eta, muon->PT, 0.1056583715);
        muon_i.SetPtEtaPhiE(muon->PT, muon->Eta, muon->Phi, muon_energy);
        double DR_jet_muon = jet_i.DeltaR(muon_i);
	
        if ((muon->PT > 30.) &&  (abs(muon->Eta) < 2.5)){
	  if ((DR_jet_muon < DR_jet_lep_max) ){
	    is_jet_muon_overlap = true;
	    break;
	  }
        }
      } //end muon-jet overlap loop
      
      if((!is_jet_muon_overlap)){
	if ((jet->PT > b_jet_pt_min) && (jet->BTag == 1)){n_b_jets++;}
	if ( (jet->PT > jet_min_pt) && jet->TauTag == 0 && (jet->BTag == 0)){
	  njets_counter++;
	  Jet_1.SetPtEtaPhiE(jet->PT, jet->Eta, jet->Phi, jet_energy);
	  index_jet_lead = j;
	  
	  for (int sj = 0; sj < branchJet->GetEntriesFast(); sj++){
	    
	    if (sj != j){
	      // check if any muon overlaps with the second jet	
	      for (int muo = 0; muo < branchMuon->GetEntriesFast(); muo++){
		Muon *muon = (Muon*) branchMuon->At(muo);
		double muon_energy = calculateE(muon->Eta, muon->PT, 0.1056583715);
		muon_i.SetPtEtaPhiE(muon->PT, muon->Eta, muon->Phi, muon_energy);
		double DR_jet_muon = jet_i.DeltaR(muon_i);
		if ((muon->PT > 30.) &&  (abs(muon->Eta) < 2.5)){
		  if ((DR_jet_muon < DR_jet_lep_max) ){
		    is_jet_muon_overlap_2 = true;
		    break;
		  }
		}
	      }
	      
	      Jet *jet2 = (Jet*) branchJet->At(sj);
	      double jet2_energy = calculateE(jet2->Eta, jet2->PT, jet2->Mass);
	      if((jet2->PT > jet_min_pt) && (is_jet_muon_overlap_2 == false) && (jet2->TauTag == 0) &&
		 (jet2->BTag == 0)){
		Jet_2.SetPtEtaPhiE(jet2->PT, jet2->Eta, jet2->Phi, jet2_energy);
		double DiJetMass = (Jet_1+Jet_2).M();
		if (DiJetMass > DiJetMass_min){
		  DiJetMass_min = DiJetMass;
                  //cout <<"DiJetMass "<<DiJetMass<<endl;
		  Jet_leading_vec = Jet_1;
		  Jet_sleading_vec = Jet_2;
		}
	      }
	    }
	  }
	}
      }
      
    } //end jet loop for searching taus and leading jet

    // Reconstruct mass
    double diMuonMass = 0.0;
    if((Muon1TLV.Pt() > 30.0) && (Muon2TLV.Pt() > 30.0) && (Muon1TLV.DeltaR(Muon2TLV) > 0.3)){
      diMuonMass = (Muon1TLV+Muon2TLV).M(); 
      //cout <<"Muon1TLV.Pt() "<<Muon1TLV.Pt()<<"  Muon2TLV.Pt() "<<Muon2TLV.Pt()<<endl;
      // cout << "diMuonMass " << diMuonMass << endl;
    }  
 
    // Apply cuts
    // Events with no cuts
    pass_cuts[0] = 1;
    // Events with tau with min pt and eta
    if ((Muon1TLV.Pt() > muon_pt_min) && (abs(Muon1TLV.Eta()) < 2.3)){ //poner muon pt desde 10
      pass_cuts[1] = 1;
    }
    // Events with second tau with min pt and eta
    if((Muon2TLV.Pt() > muon_pt_min) && (abs(Muon2TLV.Eta()) < 2.3) && (Muon1TLV.DeltaR(Muon2TLV) > 0.3)){
      pass_cuts[2] = 1;
    }
    // Muon cut
    if ((pass_cuts[1] == 1) && (pass_cuts[2] == 1) && (nmuon_counter > 1)){
      pass_cuts[3] = 1;
    }
    // Bjet cuts
    if ((pass_cuts[3] == 1) && (n_b_jets == 0)){
      pass_cuts[4] = 1;
    }
    // Cut in pT of leading jet
    if((pass_cuts[4] == 1) && (Jet_leading_vec.Pt() > lead_jet_pt) && (abs(Jet_leading_vec.Eta()) < jet_eta_max) ){ //para el Pt
      pass_cuts[5] = 1;
    } 
    // Cut in pt of subleading jet
    if((pass_cuts[5] == 1) && (Jet_sleading_vec.Pt() > 30.0) && (abs(Jet_sleading_vec.Eta()) < jet_eta_max)){
      pass_cuts[6] = 1;
    }
    // MET cut
    if ((pass_cuts[6] == 1) && (Met < 10000.0)){pass_cuts[7] = 1;}
    
    //Cuts specific for VBF
    //Jets in opposites hemispheres (eta product)
    if ((pass_cuts[7] == 1) && (Jet_leading_vec.Eta()*Jet_sleading_vec.Eta() < jet_eta_product)){pass_cuts[8] = 1;}
    // Cut delta eta between jets (eta difference)
    if ((pass_cuts[8] == 1) && (abs(Jet_leading_vec.Eta()-Jet_sleading_vec.Eta()) > jet_DEta) ){pass_cuts[9] = 1;} //3.5 5.0 con pasos 0.1
    //Cut in dijet mass
    if ((pass_cuts[9] == 1) && (DiJetMass_min > 500.0)){pass_cuts[10] = 1;}
    
    for (int i = 0; i < nDir; i++){
      _hmap_Nevents[i]->Fill(0.0);
      _hmap_n_jets[i]->Fill(njets_counter);
      
      if ( pass_cuts[i] == 1){
        _hmap_Nevents[i]->Fill(1.0);
        _hmap_met[i]->Fill(Met);
        _hmap_lead_jet_pT[i]->Fill(Jet_leading_vec.Pt());
        _hmap_lead_jet_eta[i]->Fill(Jet_leading_vec.Eta());
        _hmap_lead_jet_phi[i]->Fill(Jet_leading_vec.Phi());
        _hmap_slead_jet_pT[i]->Fill(Jet_sleading_vec.Pt());
        _hmap_slead_jet_eta[i]->Fill(Jet_sleading_vec.Eta());
        _hmap_slead_jet_phi[i]->Fill(Jet_sleading_vec.Phi());
        _hmap_muon_1_pT[i]->Fill(Muon1TLV.Pt());
        _hmap_muon_1_eta[i]->Fill(Muon1TLV.Eta());
        _hmap_muon_1_phi[i]->Fill(Muon1TLV.Phi());
        _hmap_muon_2_pT[i]->Fill(Muon2TLV.Pt());
        _hmap_muon_2_eta[i]->Fill(Muon2TLV.Eta());
        _hmap_muon_2_phi[i]->Fill(Muon2TLV.Phi());
        _hmap_dimuon_mass[i]->Fill(diMuonMass);

      }
    }
  }// end entry loop //for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  
  theFile->cd();
  for (int d = 0; d < nDir; d++)
    {
      cdDir[d]->cd();
      _hmap_Nevents[d]->Write();
      _hmap_n_jets[d]->Write();
      _hmap_lead_jet_pT[d]->Write();
      _hmap_lead_jet_eta[d]->Write();
      _hmap_lead_jet_phi[d]->Write();
      _hmap_slead_jet_pT[d]->Write();
      _hmap_slead_jet_eta[d]->Write();
      _hmap_slead_jet_phi[d]->Write();
      _hmap_muon_1_pT[d]->Write();
      _hmap_muon_1_eta[d]->Write();
      _hmap_muon_1_phi[d]->Write();
      _hmap_muon_2_pT[d]->Write();
      _hmap_muon_2_eta[d]->Write();
      _hmap_muon_2_phi[d]->Write();
      _hmap_met[d]->Write();
      _hmap_dimuon_mass[d]->Write();
    }
  theFile->Close(); 
}

PhenoAnalysis::~PhenoAnalysis()
{
  // do anything here that needs to be done at desctruction time
}

double PhenoAnalysis::calculateE(double eta, double pt, double mass){
  
  double theta = TMath::ATan(TMath::Exp(-eta));
  double sin_theta = TMath::Sin(2*theta);
  double p= pt/sin_theta;
  double e = sqrt(pow(p, 2) + pow(mass, 2));
  
  return e;
  
}

double PhenoAnalysis::normalizedDphi(double phi){
  const double PI  = 3.141592653589793238463;
  double twoPI = 2.0*PI;
  if ( phi < -PI ){phi += twoPI;}
  if ( phi > PI ){phi = twoPI-phi;}
  else phi = TMath::Abs(phi);
  return phi;
}
void PhenoAnalysis::crateHistoMasps (int directories)
{
  for (int i = 0; i < directories; i++)
    {
      _hmap_Nevents[i]       = new TH1F("Nevents", "Nevents", 3,0.,3);
      _hmap_lead_jet_pT[i]   = new TH1F("jet_lead_pT",    "Pt lead jet", 100, 0., 1000.);
      _hmap_lead_jet_eta[i]  = new TH1F("jet_lead_eta",   "#eta lead jet", 50, -5.0, 5.0);
      _hmap_lead_jet_phi[i]  = new TH1F("jet_lead_phi",   "#phi lead jet", 70, -3.6, 3.6);
      _hmap_slead_jet_pT[i]   = new TH1F("jet_slead_pT",    "Pt sublead jet", 100, 0., 1000.);
      _hmap_slead_jet_eta[i]  = new TH1F("jet_slead_eta",   "#eta sublead jet", 50, -5.0, 5.0);
      _hmap_slead_jet_phi[i]  = new TH1F("jet_slead_phi",   "#phi sublead jet", 70, -3.6, 3.6);
      _hmap_n_jets[i]        = new TH1F("N_jets",         "N(jet)", 4, 0., 4);
      _hmap_met[i]           = new TH1F("met",            "met", 120, 0., 1200.);
      _hmap_muon_1_pT[i]   = new TH1F("muon_1_pT",    "Pt muon 1", 100, 0., 1000.);
      _hmap_muon_1_eta[i]  = new TH1F("muon_1_eta",   "#eta muon 1", 50, -5.0, 5.0);
      _hmap_muon_1_phi[i]  = new TH1F("muon_1_phi",   "#phi muon 1", 70, -3.6, 3.6);
      _hmap_muon_2_pT[i]   = new TH1F("muon_2_pT",    "Pt muon 2", 100, 0., 1000.);
      _hmap_muon_2_eta[i]  = new TH1F("muon_2_eta",   "#eta muon 2", 50, -5.0, 5.0);
      _hmap_muon_2_phi[i]  = new TH1F("muon_2_phi",   "#phi muon 2", 70, -3.6, 3.6);
      _hmap_dimuon_mass[i]  = new TH1F("dimuon_mass", "dimuon mass", 2000, 0., 5000.);
    }
}
