////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.h
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-25
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_NOEUDCOMPOSITETEST_H
#define _TESTS_NOEUDCOMPOSITETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "NoeudAraignee.h"
#include "ArbreRenduINF2990.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudCompositeTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe NoeudAbstrait
///
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-25
///////////////////////////////////////////////////////////////////////////
class NoeudCompositeTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE( NoeudCompositeTest );
	CPPUNIT_TEST( testVider );
	CPPUNIT_TEST( testChercher );
	CPPUNIT_TEST( testEffacer );
	CPPUNIT_TEST( testEffacerSelection );
	CPPUNIT_TEST( testSelectionnerTout );
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();

	///test vider
	void testVider();

	///test recherche d'un noeud
	void testChercher();

	///test effacement d'un noeud
	void testEffacer();

	///test effacement de noeuds selectionne
	void testEffacerSelection();

	///test selection de tous les noeuds
	void testSelectionnerTout();

private:
	/// Instance d'un noeud composite
	NoeudAraignee* noeud;
};

#endif // _TESTS_NOEUDCOMPOSITETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
