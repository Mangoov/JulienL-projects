//////////////////////////////////////////////////////////////////////////////
/// @file VisiteurXMLTest.h
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-10-02
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

//VisiteurXML.h utilise tinyxml.h qui est une ent�te pr�compil�e
#include "VisiteurXML.h"

#ifndef _TESTS_VISITEURXMLTEST_H
#define _TESTS_VISITEURXMLTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "NoeudConeCube.h"


///////////////////////////////////////////////////////////////////////////
/// @class VisiteurXMLTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        m�thodes de la classe VisiteurXML
///
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-10-02
///////////////////////////////////////////////////////////////////////////
class VisiteurXMLTest : public CppUnit::TestFixture
{

	// =================================================================
	// D�claration de la suite de tests et des m�thodes de tests
	//
	// Important, vous devez d�finir chacun de vos cas de tests � l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas ex�cut� !
	// =================================================================
	CPPUNIT_TEST_SUITE( VisiteurXMLTest );
	CPPUNIT_TEST( testVisiterNoeudAbstrait );
	CPPUNIT_TEST(testEcrireFichier);
	CPPUNIT_TEST(testLireFichier);
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// M�thodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement � effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement � effectuer pour 'finaliser' cette suite de tests
	void tearDown();
	
	///cas de test visite d'un noeud abstrait
	void testVisiterNoeudAbstrait();

	///cas de test �criture du fichier de configuration
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
