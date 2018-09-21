#include "Geometry.hh"
#include "UserActionInitialization.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"

int main( int argc, char** argv )
{
  // material width
  G4int width;
  width = atoi(argv[1]);
  
  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // Set up mandatory user initialization: Geometry
  runManager->SetUserInitialization( new Geometry( width ) );

  // Set up mandatory user initialization: Physics-List
  runManager->SetUserInitialization( new FTFP_BERT );

  // Set up user initialization: User Actions
  runManager->SetUserInitialization( new UserActionInitialization );

  // Initialize G4 kernel
  runManager->Initialize();

  // Create visualization environment
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Start interactive session
  G4UIExecutive* uiExec    = new G4UIExecutive(argc, argv);
  G4UImanager*   uiManager = G4UImanager::GetUIpointer();
  uiManager->ApplyCommand("/control/execute GlobalSetup.mac");
  uiExec->SessionStart();

  // Job termination
  delete uiExec;
  delete visManager;
  delete runManager;

  return 0;
}
