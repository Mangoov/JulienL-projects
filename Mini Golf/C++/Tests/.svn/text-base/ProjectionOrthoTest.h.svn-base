//////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.h
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef _TESTS_PROJECTIONORTHOTEST_H
#define _TESTS_PROJECTIONORTHOTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "ProjectionOrtho.h"

///////////////////////////////////////////////////////////////////////////
/// @class ProjectionOrthoTest
/// @brief Classe de test cppunit pour tester le bon fonctionnement des
///        méthodes de la classe ProjectionOrtho
///
/// @author Jean-Luc Dubeau
/// @date 2011-09-16
///////////////////////////////////////////////////////////////////////////
class ProjectionOrthoTest : public CppUnit::TestFixture
{

	// =================================================================
	// Déclaration de la suite de tests et des méthodes de tests
	//
	// Important, vous devez définir chacun de vos cas de tests à l'aide
	// de la macro CPPUNIT_TEST sinon ce dernier ne sera pas exécuté !
	// =================================================================
	CPPUNIT_TEST_SUITE( ProjectionOrthoTest );
	CPPUNIT_TEST( testRedimension );
	CPPUNIT_TEST( testObtentionVirtuel );
	CPPUNIT_TEST( testObtentionCloture );
	CPPUNIT_TEST_SUITE_END();

public:

	// =================================================================
	// Méthodes pour initialiser et 'finaliser' la suite de tests
	// =================================================================

	/// Traitement à effectuer pour initialiser cette suite de tests
	void setUp();

	/// Traitement à effectuer pour 'finaliser' cette suite de tests
	void tearDown();

	/// test si les coins de la nouvelle clôture correspondent aux coordonnées de clôtures
	void testRedimension();

	/// test si les coordonnées virtuelles sont bien obtenues
	void testObtentionVirtuel();

	/// test si les coordonnées clotures sont bien obtenues
	void testObtentionCloture();

private:
	vue::ProjectionOrtho* testProjection;	
};

#endif // _TESTS_PROJECTIONORTHOTEST_H


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
