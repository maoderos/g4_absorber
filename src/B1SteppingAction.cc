

/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume1(0),
  fScoringVolume2(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{

  if (Log_volumes.empty()) { 
    const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    Log_volumes = detectorConstruction->GetVolumes(); 
      
  }
  
  // get volume of the current step 
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
  //get currente particle    
  
  G4String particle_name = step->GetTrack()->GetParticleDefinition()->GetParticleName();
  const G4String particle_process = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName(); 
   
  auto track = step->GetTrack();

   G4cout<<particle_process << "\n";
   if (track->GetTrackID() != 1) {
     track->SetTrackStatus(fKillTrackAndSecondaries);
     //const G4String process_name = track->GetCreatorProcess()->GetProcessName();
     //G4cout<<process_name << "\n";
    }
   // } else {
    //  G4cout << particle_process << "\n";
   //}

     
     
  
   
   
  
    
  
 


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

