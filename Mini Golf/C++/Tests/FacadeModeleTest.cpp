////////////////////////////////////////////////////////////////////////////////////
/// @file FacadeModeleTest.cpp
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////


#include "FacadeModeleTest.h"
#include "tinyxml.h"
#include "Utilitaire.h"

//const std::string FacadeModele::FICHIER_CONFIGURATION = "configuration.xml";

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( FacadeModeleTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::setUp()
///
/// Effectue l'initialisation préalable à l'exécution de l'ensemble des
/// cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets doivent être construits, il est conseillé de le
/// faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::setUp()
{	
	modeleTest->obtenirInstance();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::tearDown()
///
/// Effectue les opérations de finalisation nécessaires suite à l'exécution
/// de l'ensemble des cas de tests de cette suite de tests (si nécessaire).
/// 
/// Si certains objets ont été alloués à l'initialisation, ils doivent être
/// désalloués, et il est conseillé de le faire ici.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::tearDown()
{	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::testChargerConfiguration()
///
/// Cas de test: chargement de la configuration du fichier xml
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::testChargerConfiguration()
{
	modeleTest->chargerConfiguration();
	TiXmlDocument document;
	CPPUNIT_ASSERT(document.LoadFile("configuration.xml"));
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModeleTest::testEnregistrerConfiguration()
///
/// Cas de test: génération d'un fichier xml
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModeleTest::testEnregistrerConfiguration()
{
	modeleTest->enregistrerConfiguration();
	TiXmlDocument document;	
	CPPUNIT_ASSERT(document.LoadFile("configuration.xml"));
	
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////