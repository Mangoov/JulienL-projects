//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurXMLTest.h
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-10-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

//VisiteurXML.h utilise tinyxml.h qui est une entête précompilée
#include "VisiteurXML.h"

#ifndef _TESTS_VISITEURXMLTEST_H
#define _TESTS_VISITEURXMLTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "NoeudConeCube.h"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurXMLTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe VisiteurXML
///
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-10-02
///////////////////////////////////////////////////////////////////////////
class VisiteurXMLTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE( VisiteurXMLTest );
	CPPUNIT_TEST( testVisiterNoeudAbstrait );
	CPPUNIT_TEST(testEcrireFichier);
	CPPUNIT_TEST(testLireFichier);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();
	
	///cas de test visite d'un noeud abstrait
	void testVisiterNoeudAbstrait();

	///cas de test écriture du fichier de configuration
	void testEcrireFichier();

	///cas de test lecture du fichier de configuration
	void testLireFichier();

private:
	 VisiteurXML* visiteurTest;
	 NoeudConeCube* noeudTest;
};

#endif // _TESTS_VISITEURXMLTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
