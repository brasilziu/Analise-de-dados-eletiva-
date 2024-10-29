#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TChain.h>

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

void exercicio() {
    // Abrir o arquivo ROOT
    //TFile *file = TFile::Open("tree.root");
   
    

    // Carregar a árvore de eventos
   // TTree *tree = (TTree*)file->Get("Events");
    
    // Variáveis para armazenar os dados
    std::vector<float> *Muon_pt;
    std::vector<float> *Muon_eta;
    std::vector<float> *Muon_phi;

    TBranch        *b_Muon_pt;
    TBranch        *b_Muon_eta;
    TBranch        *b_Muon_phi;

    TChain* tree = new TChain("Events");
    tree->Add("tree.root");
    
    tree->SetBranchAddress("Muon_pt", &Muon_pt, &b_Muon_pt);
    tree->SetBranchAddress("Muon_eta", &Muon_eta, &b_Muon_eta);
    tree->SetBranchAddress("Muon_phi", &Muon_phi, &b_Muon_phi);

    // Criar histograms para pT, eta e phi
    TH1F *h_lep_pt = new TH1F("h_lep_pt", "Distribuição de pT dos léptons; pT (GeV); Eventos", 50, 0, 200);
    TH1F *h_lep_eta = new TH1F("h_lep_eta", "Distribuição de eta dos léptons; #eta; Eventos", 50, -5, 5);
    TH1F *h_lep_phi = new TH1F("h_lep_phi", "Distribuição de phi dos léptons; #phi; Eventos", 50, -3.14, 3.14);

    Muon_pt = 0;
    Muon_eta = 0;
    Muon_phi = 0;
    
    
    TH1F *h_inv_mass = new TH1F("h_inv_mass", "Massa invariante dos dois léptons com maior pT; Massa invariante (GeV); Eventos", 50, 0, 200);
    
    int nentries = tree->GetEntries();
    
    // Loop sobre os eventos
    for (int i = 0; i < nentries; i++) {

        Muon_pt->clear();
        Muon_eta->clear();
        Muon_phi->clear();
        
        tree->GetEntry(i);
        
        // Preencher os histogramas dos léptons
        for (int j = 0; j < Muon_pt->size(); j++) {
            h_lep_pt->Fill(Muon_pt->at(j));
            h_lep_eta->Fill(Muon_eta->at(j));
            h_lep_phi->Fill(Muon_phi->at(j));
        }
        
   
        
        
        // Se houver pelo menos 2 léptons, calcular a massa invariante dos 2 com maior pT
        //if (Muon_pt->size() > 1) {
         // std::vector<std::pair<float, size_t>> pts;
          //  for (size_t j = 0; j < Muon_pt->size(); j++) {
            
            
            // Ordenar léptons por pT
         //   std::sort(pts.begin(), pts.end(), std::greater<std::pair<float, size_t>>());
            
            // Pegar os dois léptons de maior pT
         //   size_t idx1 = pts[0].second;
          //  size_t idx2 = pts[1].second;
            
            // Construir os vetores de Lorentz para os dois léptons
          //  TLorentzVector lep1, lep2;
          //  lep1.SetPtEtaPhiM(0,0,0,0);
          //  lep2.SetPtEtaPhiM(0,0,0,0);
          //  lep1.SetPtEtaPhiM(Muon_pt->at(idx1), Muon_eta->at(idx1), Muon_phi->at(idx1), 0.0); // Assumindo massa desprezível
           // lep2.SetPtEtaPhiM(Muon_pt->at(idx2), Muon_eta->at(idx2), Muon_phi->at(idx2), 0.0); // testar com massa de cada muon depois
            
            // Calcular a massa invariante
          //  double inv_mass = (lep1 + lep2).M();
          //  h_inv_mass->Fill(inv_mass);
  //      }
   // }
    }
    
    // Criar canvas para plotar
    TCanvas *c = new TCanvas("c", "Distribuições", 1200, 800);
    c->Divide(2, 2);
    
    c->cd(1);
    h_lep_pt->Draw();
    
    c->cd(2);
    h_lep_eta->Draw();
    
    c->cd(3);
    h_lep_phi->Draw();
    
   // c->cd(4);
   // h_inv_mass->Draw();
    
    // Salvar os gráficos em um arquivo
    c->SaveAs("distribuicoes.pdf");
    
}


