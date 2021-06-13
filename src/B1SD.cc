#include "B1SD.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include <iostream>
#include <fstream>

/// \file B1SD.cc
/// \brief Implementation of the B1SD class.


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
  //pega o nome da partícula
  const G4String particle_name = step->GetTrack()->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();
  //pega o Track relacionado à ela
  G4int track = step->GetTrack()->GetTrackID();
//pega energia da particula
 const G4double energy = step->GetPreStepPoint()->GetTotalEnergy();

  const G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
  //pega momentum da particula
  const G4ThreeVector momentum = step->GetPreStepPoint()->GetMomentum();

  const G4StepPoint* thePreVL = step->GetPreStepPoint();
  const G4String detec_name = step->GetTrack()->GetVolume()->GetLogicalVolume()->GetName();

// get initial data
  const B1PrimaryGeneratorAction* generatorAction
     = static_cast<const B1PrimaryGeneratorAction*>
       (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());

  const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
  G4double x = particleGun->GetParticleMomentumDirection().x();
  G4double y = particleGun->GetParticleMomentumDirection().y();
  G4double z = particleGun->GetParticleMomentumDirection().z();

  const G4double alpha = acos((z/sqrt(x*x+y*y+z*z)));
  const G4double alpha_degree  = alpha*(180/(3.14159265));
  const G4double P = particleGun->GetParticleMomentum();
  const G4double Pz = P*cos(alpha);
//	G4cout << "ppp" << G4endl;
//Checa se a partícula é repetida
if (thePreVL->GetStepStatus() == fGeomBoundary && track == 1) {
       // X,Y,Z,Px,Py,PZ,Pz0,alpha
       std::ofstream data("data_" + detec_name + ".dat",std::ios_base::app);
       data << position.x()/(m) << "  " << position.y()/(m) << "  " << position.z()/(m) << " "
                                << energy/GeV << " " << momentum.x()/GeV << " " << momentum.y()/(GeV)<< " "
                                <<  momentum.z()/(GeV) << " " << Pz/(GeV) << " " << alpha_degree <<"\n";
       data.close();
}

}

void B1SD::Initialize(G4HCofThisEvent* HCE) {
  hitCollection = new B1HitsCollection(SensitiveDetectorName,collectionName[0]);
  if (HCID < 0) HCID = GetCollectionID(0);
  HCE->AddHitsCollection(HCID, hitCollection);
}

void B1SD::EndOfEvent(G4HCofThisEvent* HCE) {
  track_id = 0;
}
