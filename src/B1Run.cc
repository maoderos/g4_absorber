//-------------------------------------------------------------------------------------------------------
//Application developed for studying the dispersion of muon in the Alice Frontal Absorber
//History of the code
//----------------------------
//Year; Author; Paper	
// 2021; M.A.O Derós, L.G Pareira ,G. Hoff; marcosderos78@gmail.com, lgp@ufrgs.br, ghoff.gesic@gmail.com
//----------------------------
//-------------------------------------------------------------------------------------------------------
//$ID: Run
//--------------------------------------------------


#include "B1Run.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "B1DetectorConstruction.hh"
#include <vector>
#include "G4MTRunManager.hh"
#include "B1SteppingAction.hh"

using namespace std;

B1Run::B1Run()
 : G4Run()
{

  const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4MTRunManager::GetRunManager()->GetUserDetectorConstruction());


  auto N = detectorConstruction->getNV();
  std::vector<G4String> names = detectorConstruction->GetNames();

  std::vector<G4String> detName;
  detName.reserve(N);
  for(int i=0;i<N;i++) {
  G4String CIname = names[i];
  detName[i] = CIname;

  }

  G4String primNameSum[10]
    = {"pop","passCell","nOfStep","nOfCollision","nOfSecondary","Trackcounter", "cellFlux",
        "passageCellFlux","cylinder","termination"};

  G4SDManager* SDMan = G4SDManager::GetSDMpointer();
  
  G4String fullName;
  int i,j;
  for(i=0;i<N;i++)
  {
    for(j=0;j<9;j++)
    {
      fullName = detName[i]+"/"+primNameSum[j];
      fColIDSum[i][j] = SDMan->GetCollectionID(fullName);

    }
  }
}

B1Run::~B1Run()
{;}

G4double B1Run::GetTotal(const G4THitsMap<G4double> &map) const
{
  G4double tot = 0.;
  if(map.GetSize()==0) return tot;
  std::map<G4int,G4double*>::iterator itr = map.GetMap()->begin();
  for(; itr != map.GetMap()->end(); itr++)
  { tot += *(itr->second); }
  return tot;

}

void B1Run::RecordEvent(const G4Event* evt)
{

  const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4MTRunManager::GetRunManager()->GetUserDetectorConstruction());

  const B1SteppingAction* steppingAction 
      = static_cast<const B1SteppingAction*>
        (G4MTRunManager::GetRunManager()->GetUserSteppingAction());

  G4int N = detectorConstruction->getNV();


  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  if(!HCE) return;

  //Get Hits collections
 
  numberOfEvent++;
  int i,j;
  for(i=0;i<N;i++)
  {
    for(j=0;j<9;j++)
    {
      G4THitsMap<G4double>* evtMap
        = (G4THitsMap<G4double>*)(HCE->GetHC(fColIDSum[i][j]));
      fMapSum[i][j] += *evtMap;
    }
  }

processMap = steppingAction->getProcessCount();

}

void B1Run::Merge(const G4Run * aRun) {
 
  const B1DetectorConstruction* detectorConstruction
      = static_cast<const B1DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    

  G4int N = detectorConstruction->getNV();
  //AAAA
  const B1Run * localRun = static_cast<const B1Run *>(aRun);
  int i,j;
  for(i = 0; i <N; i++) {
    for(j = 0; j <9; j++) {
      fMapSum[i][j] += localRun->fMapSum[i][j];
    }
  }
  
  std::map<G4String,int> processMap_localRun = localRun->GetProcessMap();
  
  // loop through this map
  std::map<G4String, int>::iterator it;

  for (it = processMap_localRun.begin(); it != processMap_localRun.end(); it++) {
  	processMap[it->first] += it->second;
  
  }

  G4Run::Merge(aRun);
}
