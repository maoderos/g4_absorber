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


#ifndef Run_h
#define Run_h 1

#include "globals.hh"
#include "G4Run.hh"

#include "G4THitsMap.hh"


class G4Event;

class B1Run : public G4Run
{
public:
  B1Run();
  virtual ~B1Run();

  virtual void RecordEvent(const G4Event*);
  virtual void Merge(const G4Run*);

  G4double GetPopulation(G4int i) const    { return GetTotal(fMapSum[i][0]); }
  G4double GetPassageCell(G4int i) const    { return GetTotal(fMapSum[i][1]); }
  G4double GetNofStep(G4int i) const {return GetTotal(fMapSum[i][2]);}
  G4double GetNofCollision(G4int i) const {return GetTotal(fMapSum[i][3]);}
  G4double GetNofSecondary(G4int i) const {return GetTotal(fMapSum[i][4]);}
  G4double GetPassageTrackLength(G4int i) const {return GetTotal(fMapSum[i][5]);}
  G4double GetCellFlux(G4int i) const {return GetTotal(fMapSum[i][6]);}
  G4double GetPassageCellFlux(G4int i) const {return GetTotal(fMapSum[i][7]);}
  G4double GetCylinderSurfaceCurrent(G4int i) const {return GetTotal(fMapSum[i][8]);}
  G4double GetTermination(G4int i) const {return GetTotal(fMapSum[i][9]);}
  private:
  G4double GetTotal(const G4THitsMap<G4double> &map) const;
  //G4double FindMinimum(const G4THitsMap<G4double> &map) const;



  G4THitsMap<G4double> fMapSum[43][9];
  G4int fColIDSum[43][9];
  G4int HID1;
  G4int HID2;
};

#endif
