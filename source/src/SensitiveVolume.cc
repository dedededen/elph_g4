//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SensitiveVolume.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "SensitiveVolume.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4HCofThisEvent.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"
#include "G4SystemOfUnits.hh"

//------------------------------------------------------------------------------
SensitiveVolume::SensitiveVolume(G4String name)
  : G4VSensitiveDetector(name)
    //------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
SensitiveVolume::~SensitiveVolume()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
void SensitiveVolume::Initialize(G4HCofThisEvent*)
//------------------------------------------------------------------------------
{}
//------------------------------------------------------------------------------
void SensitiveVolume::EndOfEvent(G4HCofThisEvent*)
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
G4bool SensitiveVolume::ProcessHits(G4Step* aStep, G4TouchableHistory*)
//------------------------------------------------------------------------------
{
  G4StepPoint* point = aStep->GetPreStepPoint();
  if(point->GetStepStatus() == fGeomBoundary){

    G4int particle_id;
    G4int trackid = aStep -> GetTrack() ->GetTrackID();
    const G4String particle_name = aStep->GetTrack()->GetDefinition()->GetParticleName();;
    if(particle_name=="e+"){
      if(trackid==1)
        particle_id = 1;
      else
        particle_id = 2;
    }
    else if(particle_name=="e-")
      particle_id = 3;
    else if(particle_name=="gamma")
      particle_id = 4;
    else
      particle_id = 0;

    G4ThreeVector worldPos = point ->GetPosition();
    G4double x,y,z,Ene;
    x = worldPos.getX();
    y = worldPos.getY();
    z = worldPos.getZ();
    Ene = point -> GetTotalEnergy();
      
    /*    G4cout << x << G4endl
           << y << G4endl
           << z << G4endl
           << Ene << G4endl
           << particle_name << G4endl
           << particle_id << G4endl;*/
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, x);
    analysisManager->FillNtupleDColumn(1, y);
    analysisManager->FillNtupleDColumn(2, z);
    analysisManager->FillNtupleDColumn(3, Ene);
    analysisManager->FillNtupleSColumn(4, particle_name);
    analysisManager->FillNtupleIColumn(5, particle_id);
    analysisManager->AddNtupleRow();
  }
  return true;
}






