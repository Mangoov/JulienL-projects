//////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduTest.h
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_ARBRERENDUTEST_H
#define _TESTS_ARBRERENDUTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ArbreRendu.h"

///////////////////////////////////////////////////////////////////////////
/// @class ArbreRenduTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe ArbreRendu
///
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-23
///////////////////////////////////////////////////////////////////////////
class ArbreRenduTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE( ArbreRenduTest );
	CPPUNIT_TEST( testCreerNoeud );
	CPPUNIT_TEST( testAjoutNouveauNoeud );
	CPPUNIT_TEST( testCalculProfondeurMax );
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();
	
	/// Test création de noeud
	void testCreerNoeud();

	/// Test ajout nouveau noeud
	void testAjoutNouveauNoeud();

	///Test calcul de profondeur maximale de l'arbre
	void testCalculProfondeurMax();

private:
	 ArbreRendu* arbreTest;
};

#endif // _TESTS_ARBRERENDUTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
