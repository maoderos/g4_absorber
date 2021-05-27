
/// \file B1RunAction.cc
/// \brief Implementation of the B1RunAction class

#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1Run.hh"
#include <stdio.h>      /* printf */
#include <math.h>
#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Timer.hh"
#include "G4VSteppingVerbose.hh"

#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::B1RunAction()
: G4UserRunAction(),
  n_of_mu_plus(0.),
  n_of_mu_minus(0.),
  nEvent(0)
{


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::~B1RunAction()
{}


G4Run* B1RunAction::GenerateRun()
{ return new B1Run; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::BeginOfRunAction(const G4Run*)
{
 G4cout << "BEGIN RUN" << G4endl;

  n_of_mu_plus = 0.;
  n_of_mu_minus = 0.;

  const B1DetectorConstruction* detectorConstruction
   = static_cast<const B1DetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());



   for (G4int i=0; i<detectorConstruction->getNumDetec();i++) {

       num_event_detec.push_back(0);
}

const B1PrimaryGeneratorAction* generatorAction
 = static_cast<const B1PrimaryGeneratorAction*>
   (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
G4String runCondition;

G4double angle_a;
if (generatorAction)
{
  const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
  runCondition += particleGun->GetParticleDefinition()->GetParticleName();
  runCondition += " of ";
  G4double particleEnergy = particleGun->GetParticleEnergy();
  G4double x = particleGun->GetParticleMomentumDirection().x();
  G4double y = particleGun->GetParticleMomentumDirection().y();
  G4double z = particleGun->GetParticleMomentumDirection().z();

  runCondition += G4BestUnit(particleEnergy,"Energy");

 #define PI 3.14159265
  G4double angle_a = acos((z/sqrt(x*x+y*y+z*z)))*180/PI;
  G4double angle = acos((z/sqrt(x*x+y*y+z*z)));
  G4double P = particleGun->GetParticleMomentum()/GeV;
  G4double Pz = P*cos(angle);


 std::stringstream energy_k;
 std::stringstream angle_b;
 angle_b << std::setprecision(4) << angle_a;
 energy_k << std::setprecision(4) << Pz;

 alpha = angle_b.str();
 gunEnergy = energy_k.str();

}


  timer = new G4Timer();
  timer->Start();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run* run)
{

  timer->Stop();


  G4int nofEvents = run->GetNumberOfEvent();

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Compute dose = total energy deposit in a run and its variance

  const B1DetectorConstruction* detectorConstruction
   = static_cast<const B1DetectorConstruction*>
     (G4RunManager::GetRunManager()->GetUserDetectorConstruction());



  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const B1PrimaryGeneratorAction* generatorAction
   = static_cast<const B1PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;

  G4double angle_a;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();

    runCondition += G4BestUnit(particleEnergy,"Energy");

  }



  num_event_detec.clear();

  // Print
  //
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }

  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition
     << G4endl
     << "Time of Run: " << timer->GetRealElapsed()
     << G4endl
     << "Angle: " << angle_a << " graus"
     << G4endl;


// PRIMITIVE SCORES
const B1Run* theRun = (const B1Run*) run;


G4int N = detectorConstruction->getNV();
std::vector<G4String> names = detectorConstruction->GetNames();
std::vector<G4String> Regions_p = detectorConstruction->GetPhyNames();
 G4String detName[N];
  for(G4int i=0;i<N;i++) {
      G4String CIname = names[i];
      detName[i] = CIname;
  }

  G4double nEvt = (G4double)(theRun->GetNumberOfEvent());
    for(size_t i=0;i<N;i++)
    {


      G4Region* region = G4RegionStore::GetInstance()->GetRegion(Regions_p[i]);

      G4ProductionCuts* cuts = region->GetProductionCuts();

      G4cout << "Region : " << region->GetName() << G4endl;

      G4cout << " Population in an event :" << G4endl << "   "
      << " Poputation in CI " << i << ": " << (theRun->GetPopulation(i))/nEvt
      << G4endl;
      G4cout << " Passage cells Current  :" << G4endl << "   "
      << " Passage Cells in Current " << i << ": " << (theRun->GetPassageCell(i))/nEvt
      << G4endl;
      G4cout << " N of Step:  " << i << ": " << (theRun->GetNofStep(i))/nEvt
      << G4endl;
      G4cout << " N of Collisions " << i << ": " << (theRun->GetNofCollision(i))/nEvt
      << G4endl;
      G4cout << " n of Secondary " << i << ": " << (theRun->GetNofSecondary(i))/nEvt
      << G4endl;
      G4cout << " Trackcounter " << i << ": " << (theRun->GetPassageTrackLength(i))/nEvt
      << G4endl;
      G4cout << " Cell flux " << i << ": " << (theRun->GetCellFlux(i))/nEvt
      << G4endl;
      G4cout << " Passage Cell flux " << i << ": " << (theRun->GetPassageCellFlux(i))/nEvt
      << G4endl;
      G4cout << " CylinderSurfaceCurrent " << i << ": " << (theRun->GetCylinderSurfaceCurrent(i))/nEvt
      << G4endl;
      G4cout << " G4PSTermination " << i << ": " << (theRun->GetTermination(i))/nEvt
      << G4endl;
      G4cout << "----------------------------------------------------------------------------------------" << G4endl;

      //info <<  region->GetName() << " " << theRun->GetNumberOfEvent() << " " << G4BestUnit((theRun->GetPopulation(i)),"Energy") << " " << (theRun->GetPassageCell(i)) << " " << G4endl;

}



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::add_number_of_event(G4int detec_id)
{
  num_event_detec[detec_id] += 1;
 // G4cout << num_event_detec[detec_id]  << G4endl;

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
