
//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice Frontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: RunAction
//--------------------------------------------------


#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1Run.hh"
#include <stdio.h>      /* printf */
#include <math.h>
#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4MTRunManager.hh"
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

#define PI 3.14159265

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1RunAction::B1RunAction()
: G4UserRunAction()

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


const B1PrimaryGeneratorAction* generatorAction
 = static_cast<const B1PrimaryGeneratorAction*>
   (G4MTRunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
G4String runCondition;


if (generatorAction)
{
  const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
  runCondition += particleGun->GetParticleDefinition()->GetParticleName();
  runCondition += " of ";
  G4double particleEnergy = particleGun->GetParticleEnergy();
  G4double x = particleGun->GetParticleMomentumDirection().x();
  G4double y = particleGun->GetParticleMomentumDirection().y();
  G4double z = particleGun->GetParticleMomentumDirection().z();
  G4double p = particleGun->GetParticleMomentum();

  runCondition += G4BestUnit(particleEnergy,"Energy");


  G4double angle_a = acos((z/sqrt(x*x+y*y+z*z)));
 

 // Pass values to variable to be acessed in Stepping action

 alpha = angle_a*180/PI;
 Pz = p*cos(angle_a);
 
 
 G4String particleName = particleGun->GetParticleDefinition()->GetParticleName();
 // Create a file and store its name 
 std::stringstream file;
 file << "data_" << particleName << "_" << std::setprecision(2) <<  Pz/GeV << "_GeV_" << std::setprecision(2) << alpha << "_deg.dat";
 
 filename = file.str();
 
 
 

 //Creating header for file

 std::stringstream file_physics;
 file_physics << "data_volumes/data_" << std::setprecision(2) << alpha << "_deg.dat";
 file_Pphysics = file_physics.str();

 std::ofstream data_physics(file_Pphysics);

 //Adding header to this file
 
 data_physics << "Process N_process/ev Pz_o\n";

 data_physics.close(); 


}


  timer = new G4Timer();
  timer->Start();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1RunAction::EndOfRunAction(const G4Run* run)
{
  G4cout << "End Of Run" << G4endl;

  timer->Stop();


  G4int nofEvents = run->GetNumberOfEvent();

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  

  const B1DetectorConstruction* detectorConstruction
   = static_cast<const B1DetectorConstruction*>
     (G4MTRunManager::GetRunManager()->GetUserDetectorConstruction());

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const B1PrimaryGeneratorAction* generatorAction
   = static_cast<const B1PrimaryGeneratorAction*>
     (G4MTRunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;

  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();

    runCondition += G4BestUnit(particleEnergy,"Energy");

  }



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
     << "--------------------End of Local Run------------------------" << G4endl;
    return;

  }

  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition
     << G4endl
     << "Time of Run: " << timer->GetRealElapsed()
     << G4endl
     << "Angle: " << alpha << " graus"
     << G4endl;


// PRIMITIVE SCORES
const B1Run* theRun = (const B1Run*) run;


int N = detectorConstruction->getNV();
std::vector<G4String> names = detectorConstruction->GetNames();
std::vector<G4String> Regions_p = detectorConstruction->GetPhyNames();
std::vector<G4String> detName;

	//detName.reserve(N);

  for(int i=0;i<N;i++) {
      
      G4String CIname = names[i];

      detName.push_back(CIname);

  }
 
 auto print = false;
 G4double nEvt = (G4double)(theRun->GetNumberOfEvent());
 
if (print) { 
    for(int i=0;i<N;i++)
    {


      G4Region* region = G4RegionStore::GetInstance()->GetRegion(Regions_p[i]);

      //G4ProductionCuts* cuts = region->GetProductionCuts();

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
}

}

std::ofstream file_physics(file_Pphysics, std::ios_base::app);
std::map<G4String, int> processMap = theRun->GetProcessMap();

std::map<G4String, int>::iterator it;

for(it = processMap.begin(); it != processMap.end(); it++) {
	file_physics << it->first << " " << (1.0*(it->second)/nEvt) << " " 
		     << std::setprecision(2) << Pz/GeV << "\n";
		

	G4cout << it->first << " " << (1.0*(it->second)/nEvt) << " " 

		     << std::setprecision(2) << Pz/GeV << "\n" << G4endl;
		
}

file_physics.close();


}


