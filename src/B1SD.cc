#include "B1SD.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1RunAction.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4MTRunManager.hh"
#include <iostream>
#include <fstream>

//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice Frontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: SensitiveDetector
//--------------------------------------------------


B1SD::B1SD(G4String SDname): G4VSensitiveDetector(SDname),
  hitCollection(nullptr), HCID(-1) {
  //cria a hit collection
  G4cout << "Criando Hit Collection com nome: " << SDname <<G4endl;
  collectionName.insert(SDname);
  track_id = 0;
  sdname = SDname;
}

B1SD::~B1SD() {

}

G4bool B1SD::ProcessHits(G4Step* step, G4TouchableHistory* ROhist) {

  G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
  //get particle name
  const G4String particle_name = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();
  //get particle track
  const G4int track = step->GetTrack()->GetTrackID();
  //get particle energy 
  const G4double energy = step->GetPreStepPoint()->GetTotalEnergy();

  const G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
  const G4double x = position.getX();
  const G4double y = position.getY(); 
  
  //get particle momentum
  const G4ThreeVector momentum = step->GetPreStepPoint()->GetMomentum();
  const G4double px = momentum.getX();
  const G4double py = momentum.getY();
  const G4double pz = momentum.getZ();

  const G4StepPoint* thePreVL = step->GetPreStepPoint();
  const G4String detec_name = step->GetTrack()->GetVolume()->GetLogicalVolume()->GetName();
    

  const B1RunAction* runAction = static_cast<const B1RunAction*>
       (G4MTRunManager::GetRunManager()->GetUserRunAction());


// check if particle is entering in volume and if its primary

if (thePreVL->GetStepStatus() == fGeomBoundary && track == 1) {
   G4String filename = runAction->getFilename();
   std::ofstream data(("results/" + detec_name + "/" + filename),std::ios_base::app);
  // std::ofstream test("testSD" + detec_name + ".txt",std::ios_base::app);  Unity test
  //Write data in file
  // X, Y, px, py, pz
   data << x/cm << " " << y/cm << " " << px/GeV << " " << py/GeV << " " << pz/GeV << " " <<  energy/GeV << "\n";
  //test << x/cm << " " << y/cm << " " << px/GeV << " " << py/GeV << " " << pz/GeV << "\n"; Unity test
       
} else {
 return false;

}

return true;

}

void B1SD::Initialize(G4HCofThisEvent* HCE) {
  hitCollection = new B1HitsCollection(SensitiveDetectorName,collectionName[0]);
  if (HCID < 0) HCID = GetCollectionID(0);
  HCE->AddHitsCollection(HCID, hitCollection);
}

void B1SD::EndOfEvent(G4HCofThisEvent* HCE) {
  track_id = 0;
}
