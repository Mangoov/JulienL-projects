//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModeleTest.h
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_FACADEMODELETEST_H
#define _TESTS_FACADEMODELETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "FacadeModele.h"



///////////////////////////////////////////////////////////////////////////
/// @class FacadeModeleTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe FacadeModeleTest
///
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-23
///////////////////////////////////////////////////////////////////////////
class FacadeModeleTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE( FacadeModeleTest );
	CPPUNIT_TEST( testChargerConfiguration );
	CPPUNIT_TEST( testEnregistrerConfiguration );
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();
	
	/// Test le chargement de la configuration du fichier xml
	void testChargerConfiguration();

	/// Test la génération d'un fichier xml
	void testEnregistrerConfiguration();
	
private:
	FacadeModele *modeleTest;
};

#endif // _TESTS_FACADEMODELETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
