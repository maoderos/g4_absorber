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

  private:
  G4double GetTotal(const G4THitsMap<G4double> &map) const;
  //G4double FindMinimum(const G4THitsMap<G4double> &map) const;



  G4THitsMap<G4double> fMapSum[43][2];
  G4int fColIDSum[43][2];

};

#endif
