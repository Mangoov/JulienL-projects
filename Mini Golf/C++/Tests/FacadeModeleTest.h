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
///        m�thodes de la classe FacadeModeleTest
///
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-23
///////////////////////////////////////////////////////////////////////////
class FacadeModeleTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE( FacadeModeleTest );
	CPPUNIT_TEST( testChargerConfiguration );
	CPPUNIT_TEST( testEnregistrerConfiguration );
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();
	
	/// Test le chargement de la configuration du fichier xml
	void testChargerConfiguration();

	/// Test la g�n�ration d'un fichier xml
	void testEnregistrerConfiguration();
	
private:
	FacadeModele *modeleTest;
};

#endif // _TESTS_FACADEMODELETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
