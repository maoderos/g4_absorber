

/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1RunAction.hh"
#include "B1DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
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

void B1SteppingAction::UserSteppingAction(const G4Step* aStep)
{


  // get volume of the current step
  /*
  auto pre_volume
    = aStep->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume()->GetName();
  G4cout << pre_volume << G4endl;
  G4cout << "tttttt" << G4endl;
  auto post_volume
    = aStep->GetPostStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume()->GetName();
  G4cout << "bbbbbbbb" << G4endl;
  G4cout << post_volume << G4endl;
  //get currente particle
  */

  B1RunAction* runAction = (B1RunAction*) G4RunManager::GetRunManager()->GetUserRunAction();
  G4String alpha = runAction->get_alpha();
  G4String GunEnergy = runAction->get_energy();

  G4String particle_name = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
  const G4String particle_process = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  G4String ParticleName = aStep->GetTrack()->GetParticleDefinition() -> GetParticleName();
  auto trackID = aStep->GetTrack()->GetTrackID();

  //G4String physical_name = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();

  G4String log_volume = aStep->GetTrack()->GetVolume()->GetName();
  //G4String next_volume = aStep->GetTrack()->GetNextVolume()->GetName();

  //G4cout << "Physic: " << physical_name << G4endl;
  //G4cout << "Logical: " << log_volume << G4endl;
   //G4cout<<particle_process << "\n";
   /*
   if (track->GetTrackID() != 1) {
     //track->SetTrackStatus(fKillTrackAndSecondaries);
     //const G4String process_name = track->GetCreatorProcess()->GetProcessName();
     //G4cout<<process_name << "\n";
    }
   // } else {
    //  G4cout << particle_process << "\n";
   //}
  */

//PRONTO
if (log_volume == "av_1_impr_1_shFaSteelEnvelopeC1_pv_0" || log_volume == "av_1_impr_1_shFaSteelEnvelopeC2_pv_1"
|| log_volume == "av_1_impr_1_shFaSteelEnvelopeC3_pv_2"
|| log_volume == "av_1_impr_1_shFaSteelEnvelopeC4_pv_3" || log_volume == "av_2_impr_1_flange_pv_1"
|| log_volume == "av_2_impr_1_shFaFlange1_pv_0" || log_volume == "av_3_impr_1_shFaWPlateA1_pv_0"
|| log_volume == "av_3_impr_1_shFaWPlateA2_pv_1" || log_volume == "av_3_impr_1_shFaWPlateA3_pv_2"
|| log_volume == "av_3_impr_1_shFaWPlateA4_pv_3" || log_volume == "av_4_impr_1_shFaPbCone1_pv_0"
|| log_volume == "av_4_impr_1_shFaPbCone2_pv_1"  || log_volume == "av_5_impr_1_shFaCompRing1_pv_0"
|| log_volume == "av_5_impr_1_shFaCompRing2_pv_1" || log_volume == "av_6_impr_1_shFaMgRing1_pv_0"
|| log_volume == "av_6_impr_1_shFaMgRing2_pv_1" || log_volume == "av_6_impr_1_shFaMgRing3_pv_2"
|| log_volume == "av_6_impr_1_shFaMgRing4_pv_3" || log_volume == "av_7_impr_1_shFaGraphiteCone1_pv_0"
|| log_volume == "av_7_impr_1_shFaGraphiteCone2_pv_1" || log_volume == "av_7_impr_1_voFaConcreteCone_pv_2"
|| log_volume == "av_7_impr_1_voFaSteelCone25_pv_3" || log_volume == "av_7_impr_1_voFaSteelCone31_pv_4"
|| log_volume == "av_7_impr_1_voFaSteelCone25_pv_3" || log_volume == "av_8_impr_1_shFaWTube1_1_pv_0"
|| log_volume == "av_8_impr_1_shFaWTube1_2_pv_1" || log_volume == "av_8_impr_1_shFaWTube2_1_pv_2"
|| log_volume == "av_8_impr_1_shFaWTube2_2_pv_3" || log_volume == "av_8_impr_1_voFaWTube3_pv_4"
|| log_volume == "av_8_impr_1_voFaWTube4_pv_5" || log_volume == "shFaGraphiteCone1"
|| log_volume == "voFaEndPlate" || log_volume == "voFaWTube5") {
  if (trackID == 1) {
     G4Track* track = aStep -> GetTrack();

     G4StepPoint* point1 = aStep->GetPreStepPoint();
     G4StepPoint* point2 = aStep->GetPostStepPoint();

//Preparing the variables to be printed
     G4String ProcessName1 = point2 -> GetProcessDefinedStep() -> GetProcessName();
    //G4String ProcessName2 = point2 -> GetProcessDefinedStep() -> GetProcessName();
     G4String ParticleName =  track -> GetParticleDefinition() -> GetParticleName();
     G4double Position1X = point1 -> GetPosition().getX()/cm;
     G4double Position1Y = point1 -> GetPosition().getY()/cm;
     G4double Position1Z = point1 -> GetPosition().getZ()/cm;
     G4int EventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
     G4int ParentID = aStep -> GetTrack() -> GetParentID();
     G4int StepNumber =  aStep -> GetTrack() -> GetCurrentStepNumber();
     G4int TrackID = aStep -> GetTrack() -> GetTrackID();


 G4double Position2X = point2 -> GetPosition().getX()/cm;
 G4double Position2Y = point2 -> GetPosition().getY()/cm;
 G4double Position2Z = point2 -> GetPosition().getZ()/cm;

 G4double MomentumDirectionX = track -> GetMomentumDirection().getX();
 G4double MomentumDirectionY = track -> GetMomentumDirection().getY();
 G4double MomentumDirectionZ = track -> GetMomentumDirection().getZ();
 if(aStep->GetPostStepPoint()->GetStepStatus() != fGeomBoundary){
   std::ofstream data("data_volumes/data_" + GunEnergy + "_" + alpha + ".txt",std::ios_base::app);
   data << EventID << " " << ParentID << " " << TrackID << " " << StepNumber << " "  << ProcessName1  << " " << ParticleName
           << " " << Position1X << " " << Position1Y << " " << Position1Z << " "
           << Position2X << " " << Position2Y << " " << Position2Z
           << " " << MomentumDirectionX << " " << MomentumDirectionY << " " << MomentumDirectionZ << " " << (aStep->GetTrack()->GetVolume()->GetName())<< "\n";

 }
}
}

//PRONTO
if (log_volume == "av_1_impr_1_shFaSteelEnvelopeC1_pv_0" || log_volume == "av_1_impr_1_shFaSteelEnvelopeC2_pv_1"
|| log_volume == "av_1_impr_1_shFaSteelEnvelopeC3_pv_2"
|| log_volume == "av_1_impr_1_shFaSteelEnvelopeC4_pv_3" || log_volume == "av_2_impr_1_flange_pv_1"
|| log_volume == "av_2_impr_1_shFaFlange1_pv_0" || log_volume == "av_3_impr_1_shFaWPlateA1_pv_0"
|| log_volume == "av_3_impr_1_shFaWPlateA2_pv_1" || log_volume == "av_3_impr_1_shFaWPlateA3_pv_2"
|| log_volume == "av_3_impr_1_shFaWPlateA4_pv_3" || log_volume == "av_4_impr_1_shFaPbCone1_pv_0"
|| log_volume == "av_4_impr_1_shFaPbCone2_pv_1"  || log_volume == "av_5_impr_1_shFaCompRing1_pv_0"
|| log_volume == "av_5_impr_1_shFaCompRing2_pv_1" || log_volume == "av_6_impr_1_shFaMgRing1_pv_0"
|| log_volume == "av_6_impr_1_shFaMgRing2_pv_1" || log_volume == "av_6_impr_1_shFaMgRing3_pv_2"
|| log_volume == "av_6_impr_1_shFaMgRing4_pv_3" || log_volume == "av_7_impr_1_shFaGraphiteCone1_pv_0"
|| log_volume == "av_7_impr_1_shFaGraphiteCone2_pv_1" || log_volume == "av_7_impr_1_voFaConcreteCone_pv_2"
|| log_volume == "av_7_impr_1_voFaSteelCone25_pv_3" || log_volume == "av_7_impr_1_voFaSteelCone31_pv_4"
|| log_volume == "av_7_impr_1_voFaSteelCone25_pv_3" || log_volume == "av_8_impr_1_shFaWTube1_1_pv_0"
|| log_volume == "av_8_impr_1_shFaWTube1_2_pv_1" || log_volume == "av_8_impr_1_shFaWTube2_1_pv_2"
|| log_volume == "av_8_impr_1_shFaWTube2_2_pv_3" || log_volume == "av_8_impr_1_voFaWTube3_pv_4"
|| log_volume == "av_8_impr_1_voFaWTube4_pv_5" || log_volume == "shFaGraphiteCone1"
|| log_volume == "voFaEndPlate" || log_volume == "voFaWTube5" && trackID == 1) {
      if(aStep->GetPreStepPoint()->GetStepStatus() == fGeomBoundary && trackID==1){

        G4Track* track = aStep -> GetTrack();

        G4StepPoint* point1 = aStep->GetPreStepPoint();
        G4StepPoint* point2 = aStep->GetPostStepPoint();

   //Preparing the variables to be printed
        G4String ProcessName = point1 -> GetProcessDefinedStep() -> GetProcessName();
        G4String ParticleName =  track -> GetParticleDefinition() -> GetParticleName();
        G4double Position1X = point1 -> GetPosition().getX()/cm;
        G4double Position1Y = point1 -> GetPosition().getY()/cm;
        G4double Position1Z = point1 -> GetPosition().getZ()/cm;
        G4int EventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
        G4int ParentID = aStep -> GetTrack() -> GetParentID();
        G4int StepNumber =  aStep -> GetTrack() -> GetCurrentStepNumber();
        G4int TrackID = aStep -> GetTrack() -> GetTrackID();


    G4double Position2X = point2 -> GetPosition().getX()/cm;
    G4double Position2Y = point2 -> GetPosition().getY()/cm;
    G4double Position2Z = point2 -> GetPosition().getZ()/cm;

    G4double MomentumDirectionX = track -> GetMomentumDirection().getX();
    G4double MomentumDirectionY = track -> GetMomentumDirection().getY();
    G4double MomentumDirectionZ = track -> GetMomentumDirection().getZ();

    std::ofstream data("data_volumes/entrada_" + log_volume + "_" + GunEnergy + "_" + alpha + ".txt",std::ios_base::app);
    data << EventID << " " << ParentID << " " << TrackID << " " << StepNumber << " " << ParticleName
            << " " << Position1X << " " << Position1Y << " " << Position1Z << " "
            << Position2X << " " << Position2Y << " " << Position2Z
            << " " << MomentumDirectionX << " " << MomentumDirectionY << " " << MomentumDirectionZ << " " << (aStep->GetTrack()->GetVolume()->GetName()) << "\n";



  }
}

if (log_volume == "av_1_impr_1_shFaSteelEnvelopeC1_pv_0" || log_volume == "av_1_impr_1_shFaSteelEnvelopeC2_pv_1"
|| log_volume == "av_1_impr_1_shFaSteelEnvelopeC3_pv_2"
|| log_volume == "av_1_impr_1_shFaSteelEnvelopeC4_pv_3" || log_volume == "av_2_impr_1_flange_pv_1"
|| log_volume == "av_2_impr_1_shFaFlange1_pv_0" || log_volume == "av_3_impr_1_shFaWPlateA1_pv_0"
|| log_volume == "av_3_impr_1_shFaWPlateA2_pv_1" || log_volume == "av_3_impr_1_shFaWPlateA3_pv_2"
|| log_volume == "av_3_impr_1_shFaWPlateA4_pv_3" || log_volume == "av_4_impr_1_shFaPbCone1_pv_0"
|| log_volume == "av_4_impr_1_shFaPbCone2_pv_1"  || log_volume == "av_5_impr_1_shFaCompRing1_pv_0"
|| log_volume == "av_5_impr_1_shFaCompRing2_pv_1" || log_volume == "av_6_impr_1_shFaMgRing1_pv_0"
|| log_volume == "av_6_impr_1_shFaMgRing2_pv_1" || log_volume == "av_6_impr_1_shFaMgRing3_pv_2"
|| log_volume == "av_6_impr_1_shFaMgRing4_pv_3" || log_volume == "av_7_impr_1_shFaGraphiteCone1_pv_0"
|| log_volume == "av_7_impr_1_shFaGraphiteCone2_pv_1" || log_volume == "av_7_impr_1_voFaConcreteCone_pv_2"
|| log_volume == "av_7_impr_1_voFaSteelCone25_pv_3" || log_volume == "av_7_impr_1_voFaSteelCone31_pv_4"
|| log_volume == "av_7_impr_1_voFaSteelCone25_pv_3" || log_volume == "av_8_impr_1_shFaWTube1_1_pv_0"
|| log_volume == "av_8_impr_1_shFaWTube1_2_pv_1" || log_volume == "av_8_impr_1_shFaWTube2_1_pv_2"
|| log_volume == "av_8_impr_1_shFaWTube2_2_pv_3" || log_volume == "av_8_impr_1_voFaWTube3_pv_4"
|| log_volume == "av_8_impr_1_voFaWTube4_pv_5" || log_volume == "shFaGraphiteCone1"
|| log_volume == "voFaEndPlate" || log_volume == "voFaWTube5" && trackID == 1) {

   if (aStep->GetPostStepPoint()->GetStepStatus() == fGeomBoundary && trackID==1) {
       // G4cout << "saindo" << G4endl;

        G4Track* track = aStep -> GetTrack();

        G4StepPoint* point1 = aStep->GetPreStepPoint();
        G4StepPoint* point2 = aStep->GetPostStepPoint();

   //Preparing the variables to be printed
        G4String ProcessName = point2 -> GetProcessDefinedStep() -> GetProcessName();
        G4String ParticleName =  track -> GetParticleDefinition() -> GetParticleName();
        G4double Position1X = point2 -> GetPosition().getX()/cm;
        G4double Position1Y = point2 -> GetPosition().getY()/cm;
        G4double Position1Z = point2 -> GetPosition().getZ()/cm;
        G4int EventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
        G4int ParentID = aStep -> GetTrack() -> GetParentID();
        G4int StepNumber =  aStep -> GetTrack() -> GetCurrentStepNumber();
        G4int TrackID = aStep -> GetTrack() -> GetTrackID();


    G4double Position2X = point2 -> GetPosition().getX()/cm;
    G4double Position2Y = point2 -> GetPosition().getY()/cm;
    G4double Position2Z = point2 -> GetPosition().getZ()/cm;

    G4double MomentumDirectionX = track -> GetMomentumDirection().getX();
    G4double MomentumDirectionY = track -> GetMomentumDirection().getY();
    G4double MomentumDirectionZ = track -> GetMomentumDirection().getZ();

    std::ofstream data("data_volumes/saida_" + log_volume + "_" + GunEnergy + "_" + alpha + ".txt",std::ios_base::app);
    data << EventID << " " << ParentID << " " << TrackID << " " << StepNumber << " " << ParticleName
            << " " << Position1X << " " << Position1Y << " " << Position1Z << " "
            << Position2X << " " << Position2Y << " " << Position2Z
            << " " << MomentumDirectionX << " " << MomentumDirectionY << " " << MomentumDirectionZ << " " << (aStep->GetTrack()->GetVolume()->GetName())<< "\n";


  }

}


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
