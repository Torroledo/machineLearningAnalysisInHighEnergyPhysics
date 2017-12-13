#include <iostream>
#include <time.h>
#include <vector>
extern const string inFolder = "randomSample/";
void histogramsByType(std::string filename);
void randomSampleHistograms(){

  std::string signal2 = "signal_0p5TeV.root";
  std::string signal3 = "signal_1p0TeV.root";
  std::string signal4 = "signal_1p25TeV.root";
  std::string signal5 = "signal_2p0TeV.root";

  histogramsByType(signal2);
  histogramsByType(signal3);
  histogramsByType(signal4);
  histogramsByType(signal5);
}
void histogramsByType(std::string filename){

  gROOT->Reset();
  gStyle->SetOptStat(0);

  // Loading input data
  std::string pre= "joined_";
  TFile * inputFile = new TFile((inFolder+pre+filename).c_str(), "READ");
  TTree * totalSimulation = (TTree*) inputFile->Get("totalSimulation");

  // Create output Data
  std::string prefix="histograms_";
  std::string sufix1="ByType_1.pdf";
  std::string sufix2="ByType_2.pdf";
  std::string sufix3="ByType_3.pdf";
  TFile * outputFile = new TFile((inFolder+prefix+filename).c_str(), "RECREATE");

  // --------------- INPUT VARIABLES && OUTPUT VARIABLES -----------------------
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

  totalSimulation->SetBranchAddress("type", &type);
  totalSimulation->SetBranchAddress("type_2", &type_2);
  totalSimulation->SetBranchAddress("Tau_PT_sum",  &Tau_PT_sum);
  totalSimulation->SetBranchAddress("Tau_PT_dif",  &Tau_PT_dif);
  totalSimulation->SetBranchAddress("Tau_PT_1",  &Tau_PT_1);
  totalSimulation->SetBranchAddress("Tau_PT_2",  &Tau_PT_2);
  totalSimulation->SetBranchAddress("Tau_Eta_dif",  &Tau_Eta_dif);
  totalSimulation->SetBranchAddress("Tau_Eta_1",  &Tau_Eta_1);
  totalSimulation->SetBranchAddress("Tau_Eta_2",  &Tau_Eta_2);
  totalSimulation->SetBranchAddress("Tau_Phi_dif",  &Tau_Phi_dif);
  // 10
  totalSimulation->SetBranchAddress("Tau_Phi_1",  &Tau_Phi_1);
  totalSimulation->SetBranchAddress("Tau_Phi_2",  &Tau_Phi_2);
  totalSimulation->SetBranchAddress("Tau_DeltaEta",  &Tau_DeltaEta);
  totalSimulation->SetBranchAddress("Tau_DeltaPhi",  &Tau_DeltaPhi);
  totalSimulation->SetBranchAddress("Tau_Charge_1",  &Tau_Charge_1);
  totalSimulation->SetBranchAddress("Tau_Charge_2",  &Tau_Charge_2);
  totalSimulation->SetBranchAddress("Tau_Mass_sum",  &Tau_Mass_sum);
  totalSimulation->SetBranchAddress("Tau_Mass_dif",  &Tau_Mass_dif);
  totalSimulation->SetBranchAddress("Tau_Mass_1",  &Tau_Mass_1);
  totalSimulation->SetBranchAddress("Tau_Mass_2",  &Tau_Mass_2);
  totalSimulation->SetBranchAddress("TauTag",  &TauTag);
  totalSimulation->SetBranchAddress("Tau_Ener_sum",  &Tau_Ener_sum);
  totalSimulation->SetBranchAddress("Tau_Ener_1",  &Tau_Ener_1);
  totalSimulation->SetBranchAddress("Tau_Ener_2",  &Tau_Ener_2);
  // 24
  totalSimulation->SetBranchAddress("Miss_MET",  &Miss_MET);
  totalSimulation->SetBranchAddress("Miss_Eta",  &Miss_Eta);
  totalSimulation->SetBranchAddress("Miss_Phi",  &Miss_Phi);
  totalSimulation->SetBranchAddress("Jet_PT_sum",   &Jet_PT_sum);
  totalSimulation->SetBranchAddress("Jet_PT_dif",   &Jet_PT_dif);
  totalSimulation->SetBranchAddress("Jet_PT_1",   &Jet_PT_1);
  // 30
  totalSimulation->SetBranchAddress("Jet_PT_2",   &Jet_PT_2);
  totalSimulation->SetBranchAddress("Jet_Mass_sum", &Jet_Mass_sum);
  totalSimulation->SetBranchAddress("Jet_Mass_dif", &Jet_Mass_dif);
  totalSimulation->SetBranchAddress("Jet_Mass_1", &Jet_Mass_1);
  totalSimulation->SetBranchAddress("Jet_Mass_2",&Jet_Mass_2);
  totalSimulation->SetBranchAddress("Jet_Eta_dif",  &Jet_Eta_dif);
  totalSimulation->SetBranchAddress("Jet_Eta_1",  &Jet_Eta_1);
  totalSimulation->SetBranchAddress("Jet_Eta_2",  &Jet_Eta_2);
  totalSimulation->SetBranchAddress("Jet_Phi_dif",  &Jet_Phi_dif);
  totalSimulation->SetBranchAddress("Jet_Phi_1",  &Jet_Phi_1);
  // 40
  totalSimulation->SetBranchAddress("Jet_Phi_2",  &Jet_Phi_2);
  totalSimulation->SetBranchAddress("Jet_DeltaEta",    &Jet_DeltaEta);
  totalSimulation->SetBranchAddress("Jet_DeltaPhi",    &Jet_DeltaPhi);
  totalSimulation->SetBranchAddress("Jet_T_1",    &Jet_T_1);
  totalSimulation->SetBranchAddress("Jet_T_2",    &Jet_T_2);
  totalSimulation->SetBranchAddress("Jet_Charge_1",  &Jet_Charge_1);
  totalSimulation->SetBranchAddress("Jet_Charge_2",  &Jet_Charge_2);
  totalSimulation->SetBranchAddress("Jet_EhadOverEem_1", &Jet_EhadOverEem_1);
  totalSimulation->SetBranchAddress("Jet_EhadOverEem_2", &Jet_EhadOverEem_2);
  totalSimulation->SetBranchAddress("Jet_Ener_sum", &Jet_Ener_sum);
  totalSimulation->SetBranchAddress("Jet_Ener_1", &Jet_Ener_1);
  totalSimulation->SetBranchAddress("Jet_Ener_2",&Jet_Ener_2);
  totalSimulation->SetBranchAddress("BTag", &BTag);
  // 43

  // Create a TCanvas.
  TCanvas* c1 = new TCanvas("c1","Data Exploration",200,10,600,400);
  TCanvas* c2 = new TCanvas("c2","Data Exploration",200,10,600,400);
  TCanvas* c3 = new TCanvas("c3","Data Exploration",200,10,600,400);
  c1->Divide(3,4);
  c2->Divide(3,4);
  c3->Divide(3,4);
  // Create a 1D histogram, set its fill colour, and draw it on the current TPad
  TH1F * h1  = new TH1F("h1","type",100,0.,-5.0);
  TH1F * h2  = new TH1F("h2","Tau_PT_sum",100,0.,-5.0);
  TH1F * h3  = new TH1F("h3","Tau_PT_dif",100,0.,-5.0);
  TH1F * h4  = new TH1F("h4","Tau_PT_1",100,0.,-5.0);
  TH1F * h5  = new TH1F("h5","Tau_PT_2",100,0.,-5.0);
  TH1F * h6  = new TH1F("h6","Tau_Eta_dif",100,0.,-5.0);
  TH1F * h7  = new TH1F("h7","Tau_Eta_1",100,0.,-5.0);
  TH1F * h8  = new TH1F("h8","Tau_Eta_2",100,0.,-5.0);
  TH1F * h9  = new TH1F("h9","Tau_Phi_dif",100,0.,-5.0);
  TH1F * h10  = new TH1F("h10","Tau_Phi_1",100,0.,-5.0);
  TH1F * h11  = new TH1F("h11","Tau_Phi_2",100,0.,-5.0);
  TH1F * h12  = new TH1F("h12","Tau_DeltaEta",100,0.,-5.0);
  TH1F * h13  = new TH1F("h13","Tau_DeltaPhi",100,0.,-5.0);
  TH1F * h14  = new TH1F("h14","Tau_Charge_1",100,0.,-5.0);
  TH1F * h15  = new TH1F("h15","Tau_Charge_2",100,0.,-5.0);
  TH1F * h16  = new TH1F("h16","Tau_Mass_sum",100,0.,-5.0);
  TH1F * h17  = new TH1F("h17","Tau_Mass_dif",100,0.,-5.0);
  TH1F * h18  = new TH1F("h18","Tau_Mass_1",100,0.,-5.0);
  TH1F * h19  = new TH1F("h19","Tau_Mass_2",100,0.,-5.0);
  TH1F * h20  = new TH1F("h20","TauTag",100,0.,-5.0);
  TH1F * h21  = new TH1F("h21","Tau_Ener_sum",100,0.,-5.0);
  TH1F * h22  = new TH1F("h22","Tau_Ener_1",100,0.,-5.0);
  TH1F * h23  = new TH1F("h23","Tau_Ener_2",100,0.,-5.0);

  TH1F * h30  = new TH1F("h30","Miss_MET",100,0.,-5.0);
  TH1F * h31  = new TH1F("h31","Miss_Eta",100,0.,-5.0);
  TH1F * h32  = new TH1F("h32","Miss_Phi",100,0.,-5.0);
  TH1F * h33  = new TH1F("h33","Jet_PT_sum",100,0.,-5.0);
  TH1F * h34  = new TH1F("h34","Jet_PT_dif",100,0.,-5.0);
  TH1F * h35  = new TH1F("h35","Jet_PT_1",100,0.,-5.0);
  TH1F * h36  = new TH1F("h36","Jet_PT_2",100,0.,-5.0);
  TH1F * h37  = new TH1F("h37","Jet_Mass_sum",100,0.,-5.0);
  TH1F * h38  = new TH1F("h38","Jet_Mass_dif",100,0.,-5.0);
  TH1F * h39  = new TH1F("h39","Jet_Mass_1",100,0.,-5.0);
  TH1F * h40  = new TH1F("h40","Jet_Mass_2",100,0.,-5.0);
  TH1F * h41  = new TH1F("h41","Jet_Eta_dif",100,0.,-5.0);
  TH1F * h42  = new TH1F("h42","Jet_Eta_1",100,0.,-5.0);
  TH1F * h43  = new TH1F("h43","Jet_Eta_2",100,0.,-5.0);
  TH1F * h44  = new TH1F("h44","Jet_Phi_dif",100,0.,-5.0);
  TH1F * h45  = new TH1F("h45","Jet_Phi_1",100,0.,-5.0);
  TH1F * h46  = new TH1F("h46","Jet_Phi_2",100,0.,-5.0);
  TH1F * h47  = new TH1F("h47","Jet_DeltaEta",100,0.,-5.0);
  TH1F * h48  = new TH1F("h48","Jet_DeltaPhi",100,0.,-5.0);
  TH1F * h49  = new TH1F("h49","Jet_T_1",100,0.,-5.0);
  TH1F * h50  = new TH1F("h50","Jet_T_2",100,0.,-5.0);
  TH1F * h51  = new TH1F("h51","Jet_Charge_1",100,0.,-5.0);
  TH1F * h52  = new TH1F("h52","Jet_Charge_2",100,0.,-5.0);
  TH1F * h53  = new TH1F("h53","Jet_EhadOverEem_1",100,0.,-5.0);
  TH1F * h54  = new TH1F("h54","Jet_EhadOverEem_2",100,0.,-5.0);
  TH1F * h55  = new TH1F("h55","Jet_Ener_sum",100,0.,-5.0);
  TH1F * h56  = new TH1F("h56","Jet_Ener_1",100,0.,-5.0);
  TH1F * h57  = new TH1F("h57","Jet_Ener_2",100,0.,-5.0);
  TH1F * h58  = new TH1F("h58","BTag",100,0.,-5.0);

  TH1F * h101  = new TH1F("h101","type",100,0.,-5.0);
  TH1F * h102  = new TH1F("h102","Tau_PT_sum",100,0.,-5.0);
  TH1F * h103  = new TH1F("h103","Tau_PT_dif",100,0.,-5.0);
  TH1F * h104  = new TH1F("h104","Tau_PT_1",100,0.,-5.0);
  TH1F * h105  = new TH1F("h105","Tau_PT_2",100,0.,-5.0);
  TH1F * h106  = new TH1F("h106","Tau_Eta_dif",100,0.,-5.0);
  TH1F * h107  = new TH1F("h107","Tau_Eta_1",100,0.,-5.0);
  TH1F * h108  = new TH1F("h108","Tau_Eta_2",100,0.,-5.0);
  TH1F * h109  = new TH1F("h109","Tau_Phi_dif",100,0.,-5.0);
  TH1F * h1010  = new TH1F("h1010","Tau_Phi_1",100,0.,-5.0);
  TH1F * h1011  = new TH1F("h1011","Tau_Phi_2",100,0.,-5.0);
  TH1F * h1012  = new TH1F("h1012","Tau_DeltaEta",100,0.,-5.0);
  TH1F * h1013  = new TH1F("h1013","Tau_DeltaPhi",100,0.,-5.0);
  TH1F * h1014  = new TH1F("h1014","Tau_Charge_1",100,0.,-5.0);
  TH1F * h1015  = new TH1F("h1015","Tau_Charge_2",100,0.,-5.0);
  TH1F * h1016  = new TH1F("h1016","Tau_Mass_sum",100,0.,-5.0);
  TH1F * h1017  = new TH1F("h1017","Tau_Mass_dif",100,0.,-5.0);
  TH1F * h1018  = new TH1F("h1018","Tau_Mass_1",100,0.,-5.0);
  TH1F * h1019  = new TH1F("h1019","Tau_Mass_2",100,0.,-5.0);
  TH1F * h1020  = new TH1F("h1020","TauTag",100,0.,-5.0);
  TH1F * h1021  = new TH1F("h1021","Tau_Ener_sum",100,0.,-5.0);
  TH1F * h1022  = new TH1F("h1022","Tau_Ener_1",100,0.,-5.0);
  TH1F * h1023  = new TH1F("h1023","Tau_Ener_2",100,0.,-5.0);

  TH1F * h1030  = new TH1F("h1030","Miss_MET",100,0.,-5.0);
  TH1F * h1031  = new TH1F("h1031","Miss_Eta",100,0.,-5.0);
  TH1F * h1032  = new TH1F("h1032","Miss_Phi",100,0.,-5.0);
  TH1F * h1033  = new TH1F("h1033","Jet_PT_sum",100,0.,-5.0);
  TH1F * h1034  = new TH1F("h1034","Jet_PT_dif",100,0.,-5.0);
  TH1F * h1035  = new TH1F("h1035","Jet_PT_1",100,0.,-5.0);
  TH1F * h1036  = new TH1F("h1036","Jet_PT_2",100,0.,-5.0);
  TH1F * h1037  = new TH1F("h1037","Jet_Mass_sum",100,0.,-5.0);
  TH1F * h1038  = new TH1F("h1038","Jet_Mass_dif",100,0.,-5.0);
  TH1F * h1039  = new TH1F("h1039","Jet_Mass_1",100,0.,-5.0);
  TH1F * h1040  = new TH1F("h1040","Jet_Mass_2",100,0.,-5.0);
  TH1F * h1041  = new TH1F("h1041","Jet_Eta_dif",100,0.,-5.0);
  TH1F * h1042  = new TH1F("h1042","Jet_Eta_1",100,0.,-5.0);
  TH1F * h1043  = new TH1F("h1043","Jet_Eta_2",100,0.,-5.0);
  TH1F * h1044  = new TH1F("h1044","Jet_Phi_dif",100,0.,-5.0);
  TH1F * h1045  = new TH1F("h1045","Jet_Phi_1",100,0.,-5.0);
  TH1F * h1046  = new TH1F("h1046","Jet_Phi_2",100,0.,-5.0);
  TH1F * h1047  = new TH1F("h1047","Jet_DeltaEta",100,0.,-5.0);
  TH1F * h1048  = new TH1F("h1048","Jet_DeltaPhi",100,0.,-5.0);
  TH1F * h1049  = new TH1F("h1049","Jet_T_1",100,0.,-5.0);
  TH1F * h1050  = new TH1F("h1050","Jet_T_2",100,0.,-5.0);
  TH1F * h1051  = new TH1F("h1051","Jet_Charge_1",100,0.,-5.0);
  TH1F * h1052  = new TH1F("h1052","Jet_Charge_2",100,0.,-5.0);
  TH1F * h1053  = new TH1F("h1053","Jet_EhadOverEem_1",100,0.,-5.0);
  TH1F * h1054  = new TH1F("h1054","Jet_EhadOverEem_2",100,0.,-5.0);
  TH1F * h1055  = new TH1F("h1055","Jet_Ener_sum",100,0.,-5.0);
  TH1F * h1056  = new TH1F("h1056","Jet_Ener_1",100,0.,-5.0);
  TH1F * h1057  = new TH1F("h1057","Jet_Ener_2",100,0.,-5.0);
  TH1F * h1058  = new TH1F("h1058","BTag",100,0.,-5.0);

  int numberOfEntries = totalSimulation->GetEntries();
  cout << "Tree  has : " << numberOfEntries << " entries" << endl;

  for (int entry = 0; entry < numberOfEntries; ++entry){
    totalSimulation->GetEntry(entry);
    if (type==1){
      h1->Fill(type);
      h2->Fill(Tau_PT_sum);
      h3->Fill(Tau_PT_dif);
      h4->Fill(Tau_PT_1);
      h5->Fill(Tau_PT_2);
      h6->Fill(Tau_Eta_dif);
      h7->Fill(Tau_Eta_1);
      h8->Fill(Tau_Eta_2);
      h9->Fill(Tau_Phi_dif);
      h10->Fill(Tau_Phi_1);
      h11->Fill(Tau_Phi_2);
      h12->Fill(Tau_DeltaEta);
      h13->Fill(Tau_DeltaPhi);
      h14->Fill(Tau_Charge_1);
      h15->Fill(Tau_Charge_2);
      h16->Fill(Tau_Mass_sum);
      h17->Fill(Tau_Mass_dif);
      h18->Fill(Tau_Mass_1);
      h19->Fill(Tau_Mass_2);
      h20->Fill(TauTag);
      h21->Fill(Tau_Ener_sum);
      h22->Fill(Tau_Ener_1);
      h23->Fill(Tau_Ener_2);

      h30->Fill(Miss_MET);
      h31->Fill(Miss_Eta);
      h32->Fill(Miss_Phi);
      h33->Fill(Jet_PT_sum);
      h34->Fill(Jet_PT_dif);
      h35->Fill(Jet_PT_1);
      h36->Fill(Jet_PT_2);
      h37->Fill(Jet_Mass_sum);
      h38->Fill(Jet_Mass_dif);
      h39->Fill(Jet_Mass_1);
      h40->Fill(Jet_Mass_2);
      h41->Fill(Jet_Eta_dif);
      h42->Fill(Jet_Eta_1);
      h43->Fill(Jet_Eta_2);
      h44->Fill(Jet_Phi_dif);
      h45->Fill(Jet_Phi_1);
      h46->Fill(Jet_Phi_2);
      h47->Fill(Jet_DeltaEta);
      h48->Fill(Jet_DeltaPhi);
      h49->Fill(Jet_T_1);
      h50->Fill(Jet_T_2);
      h51->Fill(Jet_Charge_1);
      h52->Fill(Jet_Charge_2);
      h53->Fill(Jet_EhadOverEem_1);
      h54->Fill(Jet_EhadOverEem_2);
      h55->Fill(Jet_Ener_sum);
      h56->Fill(Jet_Ener_1);
      h57->Fill(Jet_Ener_2);
      h58->Fill(BTag);
    }
    else{
      h101->Fill(type);
      h102->Fill(Tau_PT_sum);
      h103->Fill(Tau_PT_dif);
      h104->Fill(Tau_PT_1);
      h105->Fill(Tau_PT_2);
      h106->Fill(Tau_Eta_dif);
      h107->Fill(Tau_Eta_1);
      h108->Fill(Tau_Eta_2);
      h109->Fill(Tau_Phi_dif);
      h1010->Fill(Tau_Phi_1);
      h1011->Fill(Tau_Phi_2);
      h1012->Fill(Tau_DeltaEta);
      h1013->Fill(Tau_DeltaPhi);
      h1014->Fill(Tau_Charge_1);
      h1015->Fill(Tau_Charge_2);
      h1016->Fill(Tau_Mass_sum);
      h1017->Fill(Tau_Mass_dif);
      h1018->Fill(Tau_Mass_1);
      h1019->Fill(Tau_Mass_2);
      h1020->Fill(TauTag);
      h1021->Fill(Tau_Ener_sum);
      h1022->Fill(Tau_Ener_1);
      h1023->Fill(Tau_Ener_2);

      h1030->Fill(Miss_MET);
      h1031->Fill(Miss_Eta);
      h1032->Fill(Miss_Phi);
      h1033->Fill(Jet_PT_sum);
      h1034->Fill(Jet_PT_dif);
      h1035->Fill(Jet_PT_1);
      h1036->Fill(Jet_PT_2);
      h1037->Fill(Jet_Mass_sum);
      h1038->Fill(Jet_Mass_dif);
      h1039->Fill(Jet_Mass_1);
      h1040->Fill(Jet_Mass_2);
      h1041->Fill(Jet_Eta_dif);
      h1042->Fill(Jet_Eta_1);
      h1043->Fill(Jet_Eta_2);
      h1044->Fill(Jet_Phi_dif);
      h1045->Fill(Jet_Phi_1);
      h1046->Fill(Jet_Phi_2);
      h1047->Fill(Jet_DeltaEta);
      h1048->Fill(Jet_DeltaPhi);
      h1049->Fill(Jet_T_1);
      h1050->Fill(Jet_T_2);
      h1051->Fill(Jet_Charge_1);
      h1052->Fill(Jet_Charge_2);
      h1053->Fill(Jet_EhadOverEem_1);
      h1054->Fill(Jet_EhadOverEem_2);
      h1055->Fill(Jet_Ener_sum);
      h1056->Fill(Jet_Ener_1);
      h1057->Fill(Jet_Ener_2);
      h1058->Fill(BTag);
    }
    if(!(entry%1000)){
      cout << "Entry : "<< entry << endl;
    }
  }

  h1->Scale(1./h1->Integral()); h101->Scale(1./h101->Integral());
  h2->Scale(1./h2->Integral()); h102->Scale(1./h102->Integral());
  h3->Scale(1./h3->Integral()); h103->Scale(1./h103->Integral());
  h4->Scale(1./h4->Integral()); h104->Scale(1./h104->Integral());
  h5->Scale(1./h5->Integral()); h105->Scale(1./h105->Integral());
  h6->Scale(1./h6->Integral()); h106->Scale(1./h106->Integral());
  h7->Scale(1./h7->Integral()); h107->Scale(1./h107->Integral());
  h8->Scale(1./h8->Integral()); h108->Scale(1./h108->Integral());
  h9->Scale(1./h9->Integral()); h109->Scale(1./h109->Integral());
  h10->Scale(1./h10->Integral()); h1010->Scale(1./h1010->Integral());
  h11->Scale(1./h11->Integral()); h1011->Scale(1./h1011->Integral());
  h12->Scale(1./h12->Integral()); h1012->Scale(1./h1012->Integral());
  h13->Scale(1./h13->Integral()); h1013->Scale(1./h1013->Integral());
  h14->Scale(1./h14->Integral()); h1014->Scale(1./h1014->Integral());
  h15->Scale(1./h15->Integral()); h1015->Scale(1./h1015->Integral());
  h16->Scale(1./h16->Integral()); h1016->Scale(1./h1016->Integral());
  h17->Scale(1./h17->Integral()); h1017->Scale(1./h1017->Integral());
  h18->Scale(1./h18->Integral()); h1018->Scale(1./h1018->Integral());
  h19->Scale(1./h19->Integral()); h1019->Scale(1./h1019->Integral());
  h20->Scale(1./h20->Integral()); h1020->Scale(1./h1020->Integral());
  h21->Scale(1./h21->Integral()); h1021->Scale(1./h1021->Integral());
  h22->Scale(1./h22->Integral()); h1022->Scale(1./h1022->Integral());
  h23->Scale(1./h23->Integral()); h1023->Scale(1./h1023->Integral());

  //c1->cd(1); h1->Draw("hist"); h101->SetLineColor(kRed); h101->Draw("hist same");
  c1->cd(1); h2->Draw("hist"); h102->SetLineColor(kRed); h102->Draw("hist same");
  c1->cd(2); h3->Draw("hist"); h103->SetLineColor(kRed); h103->Draw("hist same");
  c1->cd(3); h4->Draw("hist"); h104->SetLineColor(kRed); h104->Draw("hist same");
  c1->cd(4); h5->Draw("hist"); h105->SetLineColor(kRed); h105->Draw("hist same");
  c1->cd(5); h6->Draw("hist"); h106->SetLineColor(kRed); h106->Draw("hist same");
  c1->cd(6); h7->Draw("hist"); h107->SetLineColor(kRed); h107->Draw("hist same");
  c1->cd(7); h8->Draw("hist"); h108->SetLineColor(kRed); h108->Draw("hist same");
  c1->cd(8); h9->Draw("hist"); h109->SetLineColor(kRed); h109->Draw("hist same");
  c1->cd(9); h10->Draw("hist"); h1010->SetLineColor(kRed); h1010->Draw("hist same");
  c1->cd(10); h11->Draw("hist"); h1011->SetLineColor(kRed); h1011->Draw("hist same");
  /*c1->cd(12); h12->Draw("hist"); h1012->SetLineColor(kRed); h1012->Draw("hist same");
  c1->cd(13); h13->Draw("hist"); h1013->SetLineColor(kRed); h1013->Draw("hist same");
  c1->cd(14); h14->Draw("hist"); h1014->SetLineColor(kRed); h1014->Draw("hist same");
  c1->cd(15); h15->Draw("hist"); h1015->SetLineColor(kRed); h1015->Draw("hist same");*/
  c1->cd(11); h16->Draw("hist"); h1016->SetLineColor(kRed); h1016->Draw("hist same");
  c1->cd(12); h17->Draw("hist"); h1017->SetLineColor(kRed); h1017->Draw("hist same");
  c1->cd(0);
  c1->Print((inFolder+prefix+filename+sufix1).c_str());

  c2->cd(1); h18->Draw("hist"); h1018->SetLineColor(kRed); h1018->Draw("hist same");
  c2->cd(2); h19->Draw("hist"); h1019->SetLineColor(kRed); h1019->Draw("hist same");
  //c2->cd(3); h20->Draw("hist"); h1020->SetLineColor(kRed); h1020->Draw("hist same");
  c2->cd(3); h21->Draw("hist"); h1021->SetLineColor(kRed); h1021->Draw("hist same");
  c2->cd(4); h22->Draw("hist"); h1022->SetLineColor(kRed); h1022->Draw("hist same");
  c2->cd(5); h23->Draw("hist"); h1023->SetLineColor(kRed); h1023->Draw("hist same");
  /*
  h30->Scale(1./h30->Integral()); h1030->Scale(1./h1030->Integral());
  h31->Scale(1./h31->Integral()); h1031->Scale(1./h1031->Integral());
  h32->Scale(1./h32->Integral()); h1032->Scale(1./h1032->Integral());
  h33->Scale(1./h33->Integral()); h1033->Scale(1./h1033->Integral());
  h34->Scale(1./h34->Integral()); h1034->Scale(1./h1034->Integral());
  h35->Scale(1./h35->Integral()); h1035->Scale(1./h1035->Integral());
  h36->Scale(1./h36->Integral()); h1036->Scale(1./h1036->Integral());
  h37->Scale(1./h37->Integral()); h1037->Scale(1./h1037->Integral());
  h38->Scale(1./h38->Integral()); h1038->Scale(1./h1038->Integral());
  h39->Scale(1./h39->Integral()); h1039->Scale(1./h1039->Integral());
  h40->Scale(1./h40->Integral()); h1040->Scale(1./h1040->Integral());
  h41->Scale(1./h41->Integral()); h1041->Scale(1./h1041->Integral());
  h42->Scale(1./h42->Integral()); h1042->Scale(1./h1042->Integral());
  h43->Scale(1./h43->Integral()); h1043->Scale(1./h1043->Integral());
  h44->Scale(1./h44->Integral()); h1044->Scale(1./h1044->Integral());
  h45->Scale(1./h45->Integral()); h1045->Scale(1./h1045->Integral());
  h46->Scale(1./h46->Integral()); h1046->Scale(1./h1046->Integral());
  h47->Scale(1./h47->Integral()); h1047->Scale(1./h1047->Integral());
  h48->Scale(1./h48->Integral()); h1048->Scale(1./h1048->Integral());
  h49->Scale(1./h49->Integral()); h1049->Scale(1./h1049->Integral());
  h50->Scale(1./h50->Integral()); h1050->Scale(1./h1050->Integral());
  h51->Scale(1./h51->Integral()); h1051->Scale(1./h1051->Integral());
  h52->Scale(1./h52->Integral()); h1052->Scale(1./h1052->Integral());
  h53->Scale(1./h53->Integral()); h1053->Scale(1./h1053->Integral());
  h54->Scale(1./h54->Integral()); h1054->Scale(1./h1054->Integral());
  h55->Scale(1./h55->Integral()); h1055->Scale(1./h1055->Integral());
  h56->Scale(1./h56->Integral()); h1056->Scale(1./h1056->Integral());
  h57->Scale(1./h57->Integral()); h1057->Scale(1./h1057->Integral());
  h58->Scale(1./h58->Integral()); h1058->Scale(1./h1058->Integral());
  */
  c2->cd(6); h30->Draw("hist"); h1030->SetLineColor(kRed); h1030->Draw("hist same");
  c2->cd(7); h31->Draw("hist"); h1031->SetLineColor(kRed); h1031->Draw("hist same");
  c2->cd(8); h32->Draw("hist"); h1032->SetLineColor(kRed); h1032->Draw("hist same");
  c2->cd(9); h33->Draw("hist"); h1033->SetLineColor(kRed); h1033->Draw("hist same");
  c2->cd(10); h34->Draw("hist"); h1034->SetLineColor(kRed); h1034->Draw("hist same");
  c2->cd(11); h35->Draw("hist"); h1035->SetLineColor(kRed); h1035->Draw("hist same");
  c2->cd(12); h36->Draw("hist"); h1036->SetLineColor(kRed); h1036->Draw("hist same");
  c2->cd(0);
  c2->Print((inFolder+prefix+filename+sufix2).c_str());

  c3->cd(1); h37->Draw("hist"); h1037->SetLineColor(kRed); h1037->Draw("hist same");
  c3->cd(2); h38->Draw("hist"); h1038->SetLineColor(kRed); h1038->Draw("hist same");
  c3->cd(3); h39->Draw("hist"); h1039->SetLineColor(kRed); h1039->Draw("hist same");
  c3->cd(4); h40->Draw("hist"); h1040->SetLineColor(kRed); h1040->Draw("hist same");
  c3->cd(5); h41->Draw("hist"); h1041->SetLineColor(kRed); h1041->Draw("hist same");
  c3->cd(6); h42->Draw("hist"); h1042->SetLineColor(kRed); h1042->Draw("hist same");
  c3->cd(7); h43->Draw("hist"); h1043->SetLineColor(kRed); h1043->Draw("hist same");
  c3->cd(8); h44->Draw("hist"); h1044->SetLineColor(kRed); h1044->Draw("hist same");
  c3->cd(9); h45->Draw("hist"); h1045->SetLineColor(kRed); h1045->Draw("hist same");
  c3->cd(10); h46->Draw("hist"); h1046->SetLineColor(kRed); h1046->Draw("hist same");
  /*c2->cd(18); h47->Draw("hist"); h1047->SetLineColor(kRed); h1047->Draw("hist same");
  c2->cd(19); h48->Draw("hist"); h1048->SetLineColor(kRed); h1048->Draw("hist same");
  c2->cd(20); h49->Draw("hist"); h1049->SetLineColor(kRed); h1049->Draw("hist same");
  c2->cd(21); h50->Draw("hist"); h1050->SetLineColor(kRed); h1050->Draw("hist same");
  c2->cd(22); h51->Draw("hist"); h1051->SetLineColor(kRed); h1051->Draw("hist same");
  c2->cd(23); h52->Draw("hist"); h1052->SetLineColor(kRed); h1052->Draw("hist same");
  c2->cd(24); h53->Draw("hist"); h1053->SetLineColor(kRed); h1053->Draw("hist same");
  c2->cd(25); h54->Draw("hist"); h1054->SetLineColor(kRed); h1054->Draw("hist same");*/
  c3->cd(11); h55->Draw("hist"); h1055->SetLineColor(kRed); h1055->Draw("hist same");
  c3->cd(12); h56->Draw("hist"); h1056->SetLineColor(kRed); h1056->Draw("hist same");
  c3->cd(13); h57->Draw("hist"); h1057->SetLineColor(kRed); h1057->Draw("hist same");
  //  c2->cd(29); h58->Draw("hist"); h1058->SetLineColor(kRed); h1058->Draw("hist same");
  c3->cd(0);
  c3->Print((inFolder+prefix+filename+sufix3).c_str());
  // outputFile->Write();
  // outputFile->Close();
}
