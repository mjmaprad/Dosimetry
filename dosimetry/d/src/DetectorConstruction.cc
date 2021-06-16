//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file optical/OpNovice2/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
//#include "DetectorMessenger.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{
 fExpHall_x = fExpHall_y = fExpHall_z = 30*cm;
  fScintillator_x    = 10.0*mm; 
  fScintillator_y    = 9.0*mm;
  fScintillator_z    = 5.0*mm;

  fScintillator = nullptr;

  fScintillatorMPT    = new G4MaterialPropertiesTable();
  fWorldMPT   = new G4MaterialPropertiesTable();
  fSurfaceMPT = new G4MaterialPropertiesTable();

//G4NistManager* man = G4NistManager::Instance();


 //Teflon-scint
G4double sigma_alpha = 0.1;
fSurface = new G4OpticalSurface("Surface");
fSurface->SetType(dielectric_dielectric);
fSurface->SetModel(unified);
fSurface->SetFinish(groundbackpainted);
fSurface -> SetSigmaAlpha(sigma_alpha);
G4double Energy_teflon[2]={2.755*eV,2.755*eV};
G4double refin_teflon[2]={1.35,1.35};
//G4double transmit_teflon[2]={0.06,0.06};
G4double reflect_teflon[2]={0.95,0.95};
 fSurfaceMPT->AddProperty("RINDEX",Energy_teflon,refin_teflon,2);
 fSurfaceMPT->AddProperty("REFLECTIVITY",Energy_teflon,reflect_teflon,2);
fSurface->SetMaterialPropertiesTable(fSurfaceMPT);
////////////////////////////////////////////////////////////
//////

// G4double eff_teflon[2]={1,1};
//  G4double specularlobe[2] = {0.3, 0.3};
//  G4double specularspike[2] = {0.2, 0.2};
//  G4double backscatter[2] = {0.1, 0.1};



// // // Add entries into properties table

// fSurfaceMPT->AddProperty("TRANSMITTANCE",Energy_teflon,transmit_teflon,2);
 //fSurfaceMPT -> AddProperty("EFFICIENCY",Energy_teflon,eff_teflon,2);
  //fSurfaceMPT -> AddProperty("SPECULARLOBECONSTANT",Energy_teflon,specularlobe,2);
 // fSurfaceMPT -> AddProperty("SPECULARSPIKECONSTANT",Energy_teflon,specularspike,2);
// fSurfaceMPT -> AddProperty("BACKSCATTERCONSTANT",Energy_teflon,backscatter,2);
// //   //fsurfs->SetMaterialPropertiesTable(fSurfaceMPT);


//  G4double sigma_alpha = 0.1;
//  fSurface -> SetType(dielectric_dielectric);
//  fSurface -> SetModel(unified);
//  fSurface -> SetFinish(groundbackpainted);
//  fSurface -> SetSigmaAlpha(sigma_alpha);
// const G4int NUM = 2;
// G4double pp[NUM] = {2.038*eV, 4.144*eV};
// G4double specularlobe[NUM] = {0.3, 0.3};
// G4double specularspike[NUM] = {0.2, 0.2};
// G4double backscatter[NUM] = {0.1, 0.1};
// G4double rindex[NUM] = {1.35, 1.40};
// G4double reflectivity[NUM] = {0.3, 0.5};
// G4double efficiency[NUM] = {0.8, 0.1};
//  fSurfaceMPT -> AddProperty("RINDEX",pp,rindex,NUM);
//  fSurfaceMPT -> AddProperty("SPECULARLOBECONSTANT",pp,specularlobe,NUM);
//  fSurfaceMPT -> AddProperty("SPECULARSPIKECONSTANT",pp,specularspike,NUM);
//  fSurfaceMPT -> AddProperty("BACKSCATTERCONSTANT",pp,backscatter,NUM);
//  fSurfaceMPT -> AddProperty("REFLECTIVITY",pp,reflectivity,NUM);
//  fSurfaceMPT -> AddProperty("EFFICIENCY",pp,efficiency,NUM);



//   fSurface = new G4OpticalSurface("Surface");
//   fSurface->SetType(dielectric_LUTDAVIS);
//   fSurface->SetFinish(Rough_LUT);
//  //fSurface->SetFinish(groundteflonair);
//    fSurface->SetModel(DAVIS);
  //fSurface->SetModel(unified);

//   fSurface = new G4OpticalSurface("Surface");
//   fSurface->SetType(dielectric_dielectric);
//   fSurface->SetFinish(ground);
//  //fSurface->SetFinish(groundteflonair);
//    //fSurface->SetModel(glisur);
//   fSurface->SetModel(unified);

  fScintillator_LV  = nullptr;
  fWorld_LV = nullptr;

  fScintillatorMaterial  = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
 // fWorldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
  fWorldMaterial = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

  //fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
  ////delete fDetectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  fScintillatorMaterial->SetMaterialPropertiesTable(fScintillatorMPT);
  fScintillatorMaterial->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

  fWorldMaterial->SetMaterialPropertiesTable(fWorldMPT);

//-------Materials------
  std::vector<G4int> natoms;
  std::vector<G4double> fractionMass;
  std::vector<G4String> elements;
G4double density;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //--------------------------------------------------
  // Silicone (Template for Optical Grease)
  //--------------------------------------------------
/*
  elements.push_back("C");     natoms.push_back(2);
  elements.push_back("H");     natoms.push_back(6);
  
  density = 1.060*g/cm3;

  fSilicone = fNistMan->
          ConstructNewMaterial("Silicone", elements, natoms, density);

  elements.clear();
  natoms.clear();*/
  G4Element* H = new G4Element("H", "H", 1., 1.01*g/mole);
  G4Element* C = new G4Element("C", "C", 6., 12.01*g/mole);
G4Material*    fGreaseMaterial= new G4Material("Silicone", density= 1.032*g/cm3, 2);
    fGreaseMaterial->AddElement(C,9);
    fGreaseMaterial->AddElement(H,10);


  //
  // ------------ Generate & Add Material Properties Table ------------
  //

  G4double photonEnergy[] =
  {2.00*eV,2.03*eV,2.06*eV,2.09*eV,2.12*eV,
   2.15*eV,2.18*eV,2.21*eV,2.24*eV,2.27*eV,
   2.30*eV,2.33*eV,2.36*eV,2.39*eV,2.42*eV,
   2.45*eV,2.48*eV,2.51*eV,2.54*eV,2.57*eV,
   2.60*eV,2.63*eV,2.66*eV,2.69*eV,2.72*eV,
   2.75*eV,2.78*eV,2.81*eV,2.84*eV,2.87*eV,
   2.90*eV,2.93*eV,2.96*eV,2.99*eV,3.02*eV,
   3.05*eV,3.08*eV,3.11*eV,3.14*eV,3.17*eV,
   3.20*eV,3.23*eV,3.26*eV,3.29*eV,3.32*eV,
   3.35*eV,3.38*eV,3.41*eV,3.44*eV,3.47*eV};

  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

  //--------------------------------------------------
  // Air
  //--------------------------------------------------

  G4double refractiveIndex[] =
  { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
    1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};

  assert(sizeof(refractiveIndex) == sizeof(photonEnergy));

  G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
  mpt->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries);




  G4double absClad[] =
  {20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,
   20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,
   20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,
   20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,
   20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m,20.0*m};

  assert(sizeof(absClad) == sizeof(photonEnergy));

  //--------------------------------------------------
  // Silicone
  //--------------------------------------------------

   G4double refractiveIndexSilicone[] =
   { 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
     1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
     1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
     1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46,
     1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46, 1.46};

   assert(sizeof(refractiveIndexSilicone) == sizeof(photonEnergy));
fSurface_scint_grease = new G4OpticalSurface("Surface_scint_grease");
fSurface_scint_grease ->SetType(dielectric_dielectric);
fSurface_scint_grease ->SetModel(unified);
fSurface_scint_grease -> SetSigmaAlpha(0.1);
fSurface_scint_grease ->SetFinish(ground);
  // Add entries into properties table
  G4MaterialPropertiesTable* mptSilicone = new G4MaterialPropertiesTable();
  mptSilicone->
           AddProperty("RINDEX",photonEnergy,refractiveIndexSilicone,nEntries);
  mptSilicone->AddProperty("ABSLENGTH",photonEnergy,absClad,nEntries);
fSurface_scint_grease->SetMaterialPropertiesTable(mptSilicone);
  fGreaseMaterial->SetMaterialPropertiesTable(mptSilicone);





/////////////////////////////////////////////////////////////////////////////////////////////////////7/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //--------------------------------------------------
  //  BC408
  //--------------------------------------------------

  density = 1.032*g/cm3;
    fBC408= new G4Material("BC408", density= 1.032*g/cm3, 2);
    fBC408->AddElement(C,9);
    fBC408->AddElement(H,10);

G4double EnergyBC408[] = 
{3.299*eV, 3.201*eV, 3.130*eV, 3.089*eV, 3.069*eV, 3.056*eV, 3.036*eV, 3.023*eV, 3.016*eV, 3.004*eV, 2.991*eV, 2.972*eV, 2.947*eV, 2.923*eV, 2.905*eV, 2.887*eV, 2.863*eV, 2.852*eV, 2.829*eV, 2.818*eV, 2.818*eV, 2.795*eV, 2.768*eV, 2.736*eV, 2.699*eV, 2.658*eV, 2.638*eV, 2.599*eV, 2.562*eV, 2.511*eV, 2.455*eV, 2.421*eV, 2.384*eV};
const G4int nEntriesBC408 = sizeof(EnergyBC408)/sizeof(G4double);


G4double refractiveIndexBC408[] =
{ 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58, 1.58};
assert(sizeof(refractiveIndexBC408) == sizeof(EnergyBC408));


G4double absBC408[] =
{210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm,210*cm};
assert(sizeof(absBC408) == sizeof(EnergyBC408));


G4double scintillationFastBC408[] =
{0.057, 0.097, 0.163, 0.260, 0.326, 0.396, 0.449, 0.520, 0.564, 0.648, 0.714, 0.793, 0.877, 0.943, 0.978, 0.996, 0.965, 0.930, 0.833, 0.753, 0.705, 0.599, 0.537, 0.476, 0.388, 0.282, 0.242, 0.181, 0.141, 0.088, 0.048, 0.035, 0.022}; 
assert(sizeof(scintillationFastBC408) == sizeof(EnergyBC408));

// Add entries into properties table
G4MaterialPropertiesTable* BC408 = new G4MaterialPropertiesTable();
BC408->AddProperty("RINDEX",EnergyBC408,refractiveIndexBC408,nEntriesBC408);
BC408->AddProperty("ABSLENGTH",EnergyBC408,absBC408,nEntriesBC408);
BC408->AddProperty("FASTCOMPONENT",EnergyBC408, scintillationFastBC408,nEntriesBC408);
//BC408->AddProperty("SLOWCOMPONENT",EnergyBC408, scintillationSlowBC408,nEntriesBC408);
BC408->AddConstProperty("FASTTIMECONSTANT", 0.9*ns);
BC408->AddConstProperty("SLOWTIMECONSTANT", 2.1*ns);
BC408->AddConstProperty("SCINTILLATIONYIELD",10240./MeV);
BC408->AddConstProperty("YIELDRATIO",1.0);
BC408->AddConstProperty("RESOLUTIONSCALE",1.0);

fSurface_grease_sipm = new G4OpticalSurface("Surface__grease_sipm");
fSurface_grease_sipm ->SetType(dielectric_metal);
fSurface_grease_sipm ->SetModel(unified);
fSurface_grease_sipm ->SetFinish(ground);
fSurface_grease_sipm -> SetSigmaAlpha(0.0);

fSurface_grease_sipm->SetMaterialPropertiesTable(BC408);
fBC408->SetMaterialPropertiesTable(BC408);
// Set the Birks Constant for the BC408 scintillator
fBC408->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
G4NistManager* man = G4NistManager::Instance();

G4Material *fSiPMMaterial = man->FindOrBuildMaterial("G4_Si");
G4Material *fPb = man->FindOrBuildMaterial("G4_Pb");

//G4Material *fMylar = man->FindOrBuildMaterial("G4_MYLAR");
G4Material *fMylar = man->FindOrBuildMaterial("G4_TEFLON");
fMylar->SetMaterialPropertiesTable(fSurfaceMPT);






  // ---------------------- Volumes ------------------------
  // The experimental Hall
  G4Box* world_box = new G4Box("Worlds", fExpHall_x, fExpHall_y, fExpHall_z);

  fWorld_LV
    = new G4LogicalVolume(world_box, fWorldMaterial, "Worldl", 0, 0, 0);

  G4VPhysicalVolume* world_PV
    = new G4PVPlacement(0, G4ThreeVector(), fWorld_LV, "Worldp", 0, false, 0,true);
//-----------------------------------------------------------

G4double mylarX = 10.1 * mm;
G4double mylarY = fScintillator_y+0.05 * mm;
G4double	mylarThickness = 5.1 * mm;

	G4Box* solidMylar = new G4Box("Mylar",
			mylarX / 2, mylarY / 2,
			mylarThickness / 2);

	G4LogicalVolume* logicMylar=	 new G4LogicalVolume(solidMylar, //its solid
						             fMylar,    //its material
							     "Mylar");           //its name

	G4VPhysicalVolume *fFoil = new G4PVPlacement(0,                             //no rotation
				G4ThreeVector(0,0.05,0 * mm),                  //at (0,0,0)
				logicMylar,                      //its logical volume
				"Mylar",                           //its name
				fWorld_LV,                                //its mother  volume
				false,                            //no boolean operation
				0,true);                               //copy number

//----------------------------------------------------
//////////////////////////////////////////////////////////////////////////
//Shield
G4double collim_r1=1*mm;
G4double collim_c1=6.5*mm;
G4double collim_c2=8.5*mm;
G4double collim_h=5*mm;
G4Tubs* SolidShield_2 = new G4Tubs("shields_2",collim_r1,
			collim_c2, collim_h / 2,0,
			360);
      G4Tubs* SolidShield_1 = new G4Tubs("shields_1",collim_c1,
			collim_c2, collim_h / 2,0,
			360);
G4UnionSolid* shield = new G4UnionSolid("shield",
SolidShield_1, SolidShield_2, 0,
			G4ThreeVector(
					0, 0, collim_h));


	G4LogicalVolume* logicshield=	 new G4LogicalVolume(shield, //its solid
						             fPb,    //its material
							     "shieldLV");           //its name
  	G4RotationMatrix rotshield = G4RotationMatrix();
	rotshield.rotateX(90 * deg);

  G4ThreeVector positionshield = G4ThreeVector(0,collim_h+collim_h/2+mylarY/2+0.1*mm,0);
  G4cout<<"position of source"<<2*collim_h+mylarY/2+0.1*mm<<G4endl;
	G4Transform3D transformshieled = G4Transform3D(rotshield, positionshield);

	 new G4PVPlacement(transformshieled,   //rotated
			logicshield,               //its logical volume
			"shiledPV",                  //its name
			fWorld_LV,             //its mother
			false,                   //no boulean operat
			0,true);                      //copy number




      ///////////////Buco
      G4Tubs* bucos = new G4Tubs("bucos",0,
			collim_r1, 0.1*mm,0,
			360);
      G4LogicalVolume* logicbuco=	 new G4LogicalVolume(bucos, //its solid
						             fWorldMaterial,    //its material
							     "bucoLV");           //its name
       G4ThreeVector positionbuco = G4ThreeVector(0,mylarY/2+0.3*mm,0);
	G4Transform3D transformbuco = G4Transform3D(rotshield, positionbuco);
      new G4PVPlacement(transformbuco,   //rotated
			logicbuco,               //its logical volume
			"bucoPV",                  //its name
			fWorld_LV,             //its mother
			false,                   //no boulean operat
			0,true);      
//----------------------Mylar---------------------------



	///////////////////////
	//// Holes ///////////
	/////////////////////

	////////////////HOLE SIZE////////////////////////
	G4double holeSizeX = 3 * mm;
	G4double holeSizeY = 5 * mm;
	G4double holeSizeZ = 3 * mm;
	G4double gapBetweenHoles = 1.75 * mm;
	G4double gapOfBeginning = 1 * mm;
	/////////////////////////////////////////////////
//----------------- Scintillator --------------------------
G4Box* solidHole = new G4Box("hole",                            //its name
			holeSizeX / 2, holeSizeY / 2, holeSizeZ / 2);     //its size
	G4Box* solidScintillator = new G4Box("Scintillator",
			fScintillator_x / 2, fScintillator_y / 2,
			fScintillator_z / 2);

	G4SubtractionSolid* subtract1 = new G4SubtractionSolid("subt1",
			solidScintillator, solidHole, 0,
			G4ThreeVector(
					-fScintillator_x / 2 + holeSizeX / 2 + gapOfBeginning,
					-fScintillator_y / 2 + holeSizeY / 2, 0));

	G4SubtractionSolid* subtract2 = new G4SubtractionSolid("subt2", subtract1,
			solidHole, 0,
			G4ThreeVector(
					-fScintillator_x / 2 + holeSizeX / 2 + gapOfBeginning
							+ gapBetweenHoles + holeSizeX,
					-fScintillator_y / 2 + holeSizeY / 2, 0));
 



	fScintillator_LV = new G4LogicalVolume(subtract2, fBC408,
			"Scintillator");

	fScintillator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.),
			fScintillator_LV, "Scintillator", logicMylar, false, 0,true);

//--------------end Holes and Scint------------------------------------

	//
	// Optical Grease

	G4double innerRadiusOfTheTube = 0. * mm;
	G4double outerRadiusOfTheTube = 0.6 * mm;
	G4double hightOfTheTube = 0.5 * mm;
	G4double hightOfTheTube2 = 5 * um;
	G4double startAngleOfTheTube = 0. * deg;
	G4double spanningAngleOfTheTube = 360. * deg;

	///////////////////// Grease Geometry//////////////////////////////
	G4Tubs* SolidGrease = new G4Tubs("Grease", innerRadiusOfTheTube,
			outerRadiusOfTheTube, hightOfTheTube2 / 2, startAngleOfTheTube,
			spanningAngleOfTheTube);

	fLogicGrease = new G4LogicalVolume(SolidGrease, fGreaseMaterial, "Grease");
	///////////////////// end - Grease Geometry//////////////////////////////

	///////////////////// SiPM Geometry//////////////////////////////
	G4Tubs* SolidSiPM = new G4Tubs("SiPM", innerRadiusOfTheTube, outerRadiusOfTheTube,
				hightOfTheTube / 2, startAngleOfTheTube, spanningAngleOfTheTube);

		fLogicSiPM = new G4LogicalVolume(SolidSiPM, fSiPMMaterial, "SiPM");
	///////////////////// end - SiPM Geometry//////////////////////////////

		////////////// 18 volume placement in Scintilator /////////////
	G4int nOfSolids = 2;
	for (G4int k = 1; k <= nOfSolids; k++) {

		G4String volNameGrease;
		G4String volNameSiPM;
		switch (k) {
		case 1:
			volNameGrease = "Grease1";
			volNameSiPM = "SiPM1";
			break;
		case 2:
			volNameGrease = "Grease2";
			volNameSiPM = "SiPM2";
			break;
			}
	////////////////////// Grease Placement///////////////////////
		G4RotationMatrix rotm2 = G4RotationMatrix();
				rotm2.rotateX(90 * deg);
				G4Transform3D transform2 = G4Transform3D(rotm2,
						G4ThreeVector(
								-fScintillator_x / 2 + holeSizeX / 2
										+ gapOfBeginning + (k - 1) * gapBetweenHoles
										+ (k - 1) * holeSizeX,
								-fScintillator_y / 2 + holeSizeY
										- hightOfTheTube2 / 2, 0));

		fgreasePV = new G4PVPlacement(transform2, fLogicGrease, volNameGrease, logicMylar, false,
				0,true);
		////////////////////// SiPM Placement///////////////////////
	G4ThreeVector position = G4ThreeVector(
			-fScintillator_x / 2 + holeSizeX / 2
											+ gapOfBeginning + (k - 1) * gapBetweenHoles
											+ (k - 1) * holeSizeX,
			-fScintillator_y / 2 + holeSizeY - hightOfTheTube2
					- hightOfTheTube / 2, 0);

G4cout<<"position of sipm "<<k<<" is x y z "<< (-fScintillator_x / 2 + holeSizeX / 2
											+ gapOfBeginning + (k - 1) * gapBetweenHoles
											+ (k - 1) * holeSizeX)/mm
                      <<" "<<(-fScintillator_y / 2 + holeSizeY - hightOfTheTube2
					- hightOfTheTube / 2)/mm+0.25/mm<<" 0 " <<G4endl;
	G4RotationMatrix rotm = G4RotationMatrix();
	rotm.rotateX(90 * deg);
	G4Transform3D transform = G4Transform3D(rotm, position);
fsipmPV=
	 new G4PVPlacement(transform,   //rotated
			fLogicSiPM,               //its logical volume
			volNameSiPM,                  //its name
			logicMylar,             //its mother
			false,                   //no boulean operat
			0,true);                      //copy number
}


  // ------------- Surface --------------

  G4LogicalBorderSurface* surface =
          new G4LogicalBorderSurface("Surface",
                                 fScintillator, fFoil, fSurface);
  G4LogicalBorderSurface* surface1 =
          new G4LogicalBorderSurface("Surface",
                                 fScintillator, fgreasePV, fSurface_scint_grease);
    G4LogicalBorderSurface* surface2 =
          new G4LogicalBorderSurface("Surface",
                                 fgreasePV, fsipmPV, fSurface_grease_sipm);                               
                                 
  G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
        (surface->GetSurface(fScintillator,fFoil)->GetSurfaceProperty());
  G4cout << "******  opticalSurface for teflon-scintillator->DumpInfo:" << G4endl;
  if (opticalSurface) { opticalSurface->DumpInfo(); }
  G4cout << "******  end of opticalSurface->DumpInfo" << G4endl;
                               
  G4OpticalSurface* opticalSurface1 = dynamic_cast <G4OpticalSurface*>
        (surface1->GetSurface(fScintillator, fgreasePV)->GetSurfaceProperty());
  G4cout << "******  opticalSurface for scint-grease->DumpInfo:" << G4endl;
  if (opticalSurface1) { opticalSurface->DumpInfo(); }
  G4cout << "******  end of opticalSurface->DumpInfo" << G4endl;
                                 
  G4OpticalSurface* opticalSurface2 = dynamic_cast <G4OpticalSurface*>
        (surface2->GetSurface(fgreasePV, fsipmPV)->GetSurfaceProperty());
  G4cout << "******  opticalSurface for grease-sipm->DumpInfo:" << G4endl;
  if (opticalSurface2) { opticalSurface->DumpInfo(); }
  G4cout << "******  end of opticalSurface->DumpInfo" << G4endl;
  return world_PV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetSurfaceSigmaAlpha(G4double v) {
  fSurface->SetSigmaAlpha(v);
  fSurface_scint_grease->SetSigmaAlpha(0);
  fSurface_grease_sipm->SetSigmaAlpha(0);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();

  G4cout << "Surface sigma alpha set to: " << fSurface->GetSigmaAlpha()
         << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetSurfacePolish(G4double v) {
  fSurface->SetPolish(v);
  G4RunManager::GetRunManager()->GeometryHasBeenModified();

  G4cout << "Surface polish set to: " << fSurface->GetPolish()
         << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddScintillatorMPV(const char* c,
                                     G4MaterialPropertyVector* mpv) {
  fScintillatorMPT->AddProperty(c, mpv);
  G4cout << "The MPT for the box is now: " << G4endl;
  fScintillatorMPT->DumpTable();
  G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddWorldMPV(const char* c,
                                       G4MaterialPropertyVector* mpv) {
  fWorldMPT->AddProperty(c, mpv);
  G4cout << "The MPT for the world is now: " << G4endl;
  fWorldMPT->DumpTable();
  G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPV(const char* c,
                                         G4MaterialPropertyVector* mpv) {
  fSurfaceMPT->AddProperty(c, mpv);
  G4cout << "The MPT for the surface is now: " << G4endl;
  fSurfaceMPT->DumpTable();
  G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddScintillatorMPC(const char* c, G4double v) {
  fScintillatorMPT->AddConstProperty(c, v);
  G4cout << "The MPT for the box is now: " << G4endl;
  fScintillatorMPT->DumpTable();
  G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddWorldMPC(const char* c, G4double v) {
  fWorldMPT->AddConstProperty(c, v);
  G4cout << "The MPT for the world is now: " << G4endl;
  fWorldMPT->DumpTable();
  G4cout << "............." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::AddSurfaceMPC(const char* c, G4double v) {
  fSurfaceMPT->AddConstProperty(c, v);
  G4cout << "The MPT for the surface is now: " << G4endl;
  fSurfaceMPT->DumpTable();
  G4cout << "............." << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetWorldMaterial(const G4String& mat) {
  G4Material* pmat = G4NistManager::Instance()->FindOrBuildMaterial(mat);
  if (pmat && fWorldMaterial != pmat) {
    fWorldMaterial = pmat;
    if (fWorld_LV) {
      fWorld_LV->SetMaterial(fWorldMaterial);
      fWorldMaterial->SetMaterialPropertiesTable(fWorldMPT);
    }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    G4cout << "World material set to " << fWorldMaterial->GetName()
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::SetScintillatorMaterial(const G4String& mat) {
  G4Material* pmat = G4NistManager::Instance()->FindOrBuildMaterial(mat);
  if (pmat && fScintillatorMaterial != pmat) {
    fScintillatorMaterial = pmat;
    if (fScintillator_LV) {
      fScintillator_LV->SetMaterial(fScintillatorMaterial);
      fScintillatorMaterial->SetMaterialPropertiesTable(fScintillatorMPT);
      fScintillatorMaterial->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
    }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
    G4cout << "Scintillator material set to " << fScintillatorMaterial->GetName()
           << G4endl;
  }
}
