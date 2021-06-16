

#include "SteppingAction.hh"
//#include "EventAction.hh"
//#include "HistoManager.hh"
#include "TrackInformation.hh"
#include "Run.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include "G4ProcessManager.hh"
#include "RunData.hh"
#include "G4UnitsTable.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"
//int fPhotonCounter1=0;
//int fPhotonCounter2=0;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SteppingAction::SteppingAction()
: G4UserSteppingAction(),
fVerbose(0),checktrack(-1),checkprimary(-1)
{}

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  SteppingAction::~SteppingAction()
  {}

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    void SteppingAction::UserSteppingAction(const G4Step* step)
    {
      G4Track* track = step->GetTrack();
      G4StepPoint* endPoint   = step->GetPostStepPoint();
      G4StepPoint* startPoint = step->GetPreStepPoint();

      G4String particleName = track->GetDynamicParticle()->
      GetParticleDefinition()->GetParticleName();

      G4String volume = step->GetTrack()->GetVolume()->GetName();
      G4ThreeVector pos =step->GetTrack()->GetPosition();

      RunData *runData = static_cast<RunData*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());

////
      if( startPoint->GetPhysicalVolume()->GetName() == "bucoPV")//&&particleName !="opticalphoton")
       {
          runData->SetTotenergy(startPoint->GetKineticEnergy()/keV);

      //       G4cout<<particleName<<G4endl;
     if(particleName =="e-"||particleName =="e+")
      {
        runData->SetElectronenergy(startPoint->GetKineticEnergy()/keV);
      }
     else if(particleName =="gamma")
      {
      
        runData->SetGammaenergy(startPoint->GetKineticEnergy()/keV);
      }
           else if(particleName =="alpha")
      {
         
        runData->SetAlphaenergy(startPoint->GetKineticEnergy()/keV);
      }
        else if(particleName =="neutron")
      {
         
        runData->SetNeutronenergy(startPoint->GetKineticEnergy()/keV);
      }
        else if(particleName =="proton")
      {
         
        runData->SetProtonenergy(startPoint->GetKineticEnergy()/keV);
      }
  }

// G4cout<<"first  "<<startPoint->GetPhysicalVolume()->GetName()<<" end   "<<endPoint->GetPhysicalVolume()->GetName()<<
// "   "<<particleName<< G4endl;

	    if( 
        (startPoint->GetPhysicalVolume()->GetName()== "Mylar"||startPoint->GetPhysicalVolume()->GetName()== "World")
      &&endPoint->GetPhysicalVolume()->GetName() == "Scintillator"&&particleName !="opticalphoton")
      {
        checkprimary=track->GetTrackID();
      // G4cout<< pos.y()<<G4endl;

       // G4cout<<startPoint->GetKineticEnergy()/keV<<G4endl;
      runData->SetEntPoint(pos.x() /cm, pos.y() /cm,pos.z() /cm);
      runData->SetEntAngle(track->GetMomentumDirection().theta(),track->GetMomentumDirection().phi());
     /////
     runData->SetEntTotenergy(startPoint->GetKineticEnergy()/keV);

       if(particleName =="e-"||particleName =="e+")
      {
        runData->SetEntElectronenergy(startPoint->GetKineticEnergy()/keV);
      }
     else if(particleName =="gamma")
      {
      
        runData->SetEntGammaenergy(startPoint->GetKineticEnergy()/keV);
      }
           else if(particleName =="alpha")
      {
         
        runData->SetEntAlphaenergy(startPoint->GetKineticEnergy()/keV);
      }
        else if(particleName =="neutron")
      {
         
        runData->SetEntNeutronenergy(startPoint->GetKineticEnergy()/keV);
      }
        else if(particleName =="proton")
      {
         
        runData->SetEntProtonenergy(startPoint->GetKineticEnergy()/keV);
      }
     
     
     
      }
      else if 
      ( startPoint->GetPhysicalVolume()->GetName()== "Scintillator"
      &&((endPoint->GetPhysicalVolume()->GetName() == "Mylar")||(endPoint->GetPhysicalVolume()->GetName() == "World"))
      &&particleName !="opticalphoton"&&(checkprimary==track->GetTrackID()))
      {
      
      runData->SetExitPoint(pos.x() /cm, pos.y() /cm,pos.z() /cm);
      runData->SetExitAngle(track->GetMomentumDirection().theta(),track->GetMomentumDirection().phi());
     runData->SetExitTotenergy(startPoint->GetKineticEnergy()/keV);

       if(particleName =="e-"||particleName =="e+")
      {
        runData->SetExitElectronenergy(startPoint->GetKineticEnergy()/keV);
      }
     else if(particleName =="gamma")
      {
      
        runData->SetExitGammaenergy(startPoint->GetKineticEnergy()/keV);
      }
           else if(particleName =="alpha")
      {
         
        runData->SetExitAlphaenergy(startPoint->GetKineticEnergy()/keV);
      }
        else if(particleName =="neutron")
      {
         
        runData->SetExitNeutronenergy(startPoint->GetKineticEnergy()/keV);
      }
        else if(particleName =="proton")
      {
         
        runData->SetExitProtonenergy(startPoint->GetKineticEnergy()/keV);
      }
     
     
      }


  if ( volume == "Scintillator")
  {

   const std::vector<const G4Track*>* secondary  = step->GetSecondaryInCurrentStep();
  for (size_t lp=0; lp<(*secondary).size(); lp++) {
  G4ParticleDefinition*  particle = (*secondary)[lp]->GetDefinition();
  G4String name   = particle->GetParticleName();
 if (name="opticalphoton"){
    
       runData->SetNumPhoton();
     
 }
  }

    
       if( particleName!="opticalphoton") 
 
   ///( particleName !="opticalphoton") 
     { 

      G4double fdose=(step->GetTotalEnergyDeposit()/joule)/
      (startPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetMass()/kg);
       runData->SetDepEnergy(step->GetTotalEnergyDeposit()/keV);

       runData->SetDose(fdose);//Gy
G4double feq_dose=0;
 if(particleName=="proton") {feq_dose=fdose*5.0;}
else if(particleName=="alpha") {feq_dose=fdose*20.0;}
else if(particleName=="neutron") {
  if (startPoint->GetKineticEnergy()/keV<10){feq_dose=fdose*5.0;}
  else if (startPoint->GetKineticEnergy()/keV>=10&&startPoint->GetKineticEnergy()/keV<100){feq_dose=fdose*10.0;}
  else if (startPoint->GetKineticEnergy()/keV>=100&&startPoint->GetKineticEnergy()/MeV<2){feq_dose=fdose*20.0;}
  else if (startPoint->GetKineticEnergy()/MeV>=2&&startPoint->GetKineticEnergy()/MeV<20){feq_dose=fdose*10.0;}
  else if (startPoint->GetKineticEnergy()/MeV>=20){feq_dose=fdose*5.0;}
}
else {feq_dose=fdose;}
runData->SetEqDose(feq_dose);
// tot_dose+=fdose;
// tot_eq_dose+=feq_dose;      

       }
       
////////////////////////////////////////////////////////////////

  if(checktrack!=G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID())
 {
   const std::vector<const G4Track*>* secondary2  = step->GetSecondaryInCurrentStep();
  for (size_t lp=0; lp<(*secondary2).size(); lp++) {
  G4ParticleDefinition*  particle = (*secondary2)[lp]->GetDefinition();
  G4String name   = particle->GetParticleName();
 if (name="opticalphoton"){
       runData->SetSciPoint(pos.x() /cm, pos.y() /cm,pos.z() /cm);
checktrack=G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
  break;
 }
  }
 }
  }

//G4cout<<"2- particle "<<particleName<<
//" event "<<G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID()<<
//" checktrack "<<checktrack<<G4endl;

   //cout<<step->GetTrack()->GetSecondaryID()<<G4endl;
   // G4cout<<volume<<" E start = "<<startPoint->GetKineticEnergy()/eV<<" E start = "<<endPoint->GetKineticEnergy()/eV<<G4endl;
//G4cout<<step->GetTrack()->GetParentID()<<G4endl;
  //   //  G4cout<<"posx=  "<<pos.x() /cm<<"  posy=  "<<pos.y() /cm<<"  posz=  "<<pos.z() /cm<<G4endl;
//G4cout<<"name after"<<endPoint->GetPhysicalVolume()->GetName()<<G4endl;
  if (particleName == "opticalphoton") {

  //   if (endPoint->GetStepStatus() == fGeomBoundary) {
  //     for (int i_sipm = 1; i_sipm < 3; i_sipm++) {

	// buffer = "SiPM" + to_string(i_sipm );
	// sipm_name = buffer;
	// buffer = "Grease" + to_string(i_sipm );
	// grease_name = buffer;

	if (endPoint->GetPhysicalVolume()->GetName() == "SiPM1"
	    && startPoint->GetPhysicalVolume()->GetName()
	    == "Grease1") {
	  fEkin = startPoint->GetKineticEnergy()/eV;
	  runData->sipm(fEkin,0);
// tot_sipmcount1++;
// tot_sipmenergy1+=fEkin;

	}
else if (endPoint->GetPhysicalVolume()->GetName() == "SiPM2"
	    && startPoint->GetPhysicalVolume()->GetName()
	    == "Grease2") {
	  fEkin = startPoint->GetKineticEnergy()/eV;
	  runData->sipm(fEkin,1);
//     tot_sipmcount2++;
// tot_sipmenergy2+=fEkin;
 
    }
 }

//  runData->SetTotDoseinfo (tot_dose, tot_eq_dose, tot_photon) ;
//  runData->SetTotParticleinfo (accelecnum,accgammanum,accprotonnum,accneutronnum,accalphanum);
//  runData->SetTotSipminfo (tot_sipmenergy1,tot_sipmenergy2,tot_sipmcount1, tot_sipmcount2) ;


    return;














    //   if ( volume == "Mylar"&&
    //   // step->GetTrack()->GetParentID() == 0 &&
    //   step->GetTrack()->GetDynamicParticle()->GetMomentumDirection().z() < 0
    // ){}
    // if(step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary){
    //   //  G4cout<<"posx=  "<<pos.x() /cm<<"  posy=  "<<pos.y() /cm<<"  posz=  "<<pos.z() /cm<<G4endl;
    //   //runData->detectorData1(pos.x() /cm, pos.y() /cm);}
    //   //runData->detectorData2(pos.z() /cm);
    // }
    // if (particleName == "opticalphoton") {

    //   if (endPoint->GetStepStatus() == fGeomBoundary) {
    //     for (int i_sipm = 0; i_sipm < 64; i_sipm++) {

    //       buffer = "sipmPV" + to_string(i_sipm + 1);
    //       sipm_name = buffer;
    //       buffer = "greasePV" + to_string(i_sipm + 1);
    //       grease_name = buffer;

    //       if (endPoint->GetPhysicalVolume()->GetName() == sipm_name
    //       && startPoint->GetPhysicalVolume()->GetName()
    //       == grease_name) {
    //         fEkin = startPoint->GetKineticEnergy();
    //         runData->sipm(fEkin,i_sipm);

    //       }

    //     }
    //   }
    // }

  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
