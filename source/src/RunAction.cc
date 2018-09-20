#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
 : G4UserRunAction()
{
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  analysisManager->SetActivation(true);
  
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("./data/test.root");
  analysisManager->SetFirstHistoId(1);

  // Creating ntuple
  analysisManager->CreateNtuple("ntuple", "ntuple");
  analysisManager->CreateNtupleDColumn("pos_x");
  analysisManager->CreateNtupleDColumn("pos_y");
  analysisManager->CreateNtupleDColumn("pos_z");
  analysisManager->CreateNtupleDColumn("energy");
  analysisManager->CreateNtupleSColumn("particle_name");
  analysisManager->FinishNtuple();

 }



RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}



void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
    
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // Open an output file
  //
  // G4String fileName = "data";
  analysisManager->OpenFile();
    //G4cout << "File " << fileName << " Open" <<G4endl;
    
}



void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();


}
