//////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.h
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar
/// @date 2011-09-25
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_UTILITAIRETEST_H
#define _TESTS_UTILITAIRETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "Utilitaire.h"

///////////////////////////////////////////////////////////////////////////
/// @class UtilitaireTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe Utilitaire
///
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar
/// @date 2011-09-25
///////////////////////////////////////////////////////////////////////////
class UtilitaireTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE( UtilitaireTest );
	CPPUNIT_TEST( testAppliquerMatrice );
	CPPUNIT_TEST( testRadToDeg );
	CPPUNIT_TEST( testSigne );
	CPPUNIT_TEST( testdansLimitesXY );
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();

	///test application de matrice
	void testAppliquerMatrice();

	///test conversion radian en degr�
	void testRadToDeg();

	///test signe d'un nombre
	void testSigne();

	///test dansLimitesXY
	void testdansLimitesXY();

private:
	
};

#endif // _TESTS_UTILITAIRETEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
