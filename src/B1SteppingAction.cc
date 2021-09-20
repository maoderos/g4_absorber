

//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice Frontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: SteppingAction
//--------------------------------------------------


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

  B1RunAction* runAction = (B1RunAction*) G4RunManager::GetRunManager()->GetUserRunAction();

  G4double alpha = runAction->get_alpha();
  G4double pz_o = runAction->get_pz();

  auto trackID = aStep->GetTrack()->GetTrackID();


  G4String log_volume = aStep->GetTrack()->GetVolume()->GetName();
  
  
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


 G4double Position2X = point2 -> GetPosition().getX()/cm;
 G4double Position2Y = point2 -> GetPosition().getY()/cm;
 G4double Position2Z = point2 -> GetPosition().getZ()/cm;

 G4double MomentumDirectionX = track -> GetMomentumDirection().getX();
 G4double MomentumDirectionY = track -> GetMomentumDirection().getY();
 G4double MomentumDirectionZ = track -> GetMomentumDirection().getZ();

 if(aStep->GetPostStepPoint()->GetStepStatus() != fGeomBoundary){
   //In function of Alpha and Energy 
   std::ostringstream filename;
   filename << "data_volumes/data_physics_" << std::setprecision(2) << pz_o/GeV << "_" << std::setprecision(2) << alpha
                                                                                                   << ".txt";
                                                                                                                                                 
   std::ofstream data(filename.str(),std::ios_base::app);
   data << EventID << " " << ParentID << " " << trackID << " " << StepNumber << " "  << ProcessName1  << " " << ParticleName
           << " " << Position1X << " " << Position1Y << " " << Position1Z << " "
           << Position2X << " " << Position2Y << " " << Position2Z
           << " " << MomentumDirectionX << " " << MomentumDirectionY << " " << MomentumDirectionZ << " "
           << alpha << " " << pz_o/GeV << " " << (aStep->GetTrack()->GetVolume()->GetName())<< "\n";
  }
}
}

/* Code for Unity test 

if (log_volume == "SD1" || log_volume == "SD2") {
 if (trackID == 1) {
 std::stringstream name;
 name << "test_step" << log_volume;
 std::ofstream filetest(name.str(), std::ios_base::app);
 
 G4StepPoint* point1 = aStep->GetPreStepPoint();
 G4double x = point1->GetPosition().getX();
 G4double y = point1->GetPosition().getY();
 G4double px = point1->GetMomentumDirection().getX();

 G4double py = point1->GetMomentumDirection().getY();
 G4double pz = point1->GetMomentumDirection().getZ();

 filetest << x/cm << " " << y/cm << " " << px/GeV << " " << py/GeV << " " << pz/GeV << "\n";
 }

}

*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
