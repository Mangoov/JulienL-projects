////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrthoTest.cpp
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-16
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "ProjectionOrthoTest.h"
#include "Utilitaire.h"
#include "FacadeModele.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( ProjectionOrthoTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::setUp()
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
void ProjectionOrthoTest::setUp()
{
	
	testProjection = new vue::ProjectionOrtho(0,500,0,500,0,0,1/1000,1000,20,-100,100,-100,100);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::tearDown()
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
void ProjectionOrthoTest::tearDown()
{
	delete testProjection;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testRedimension()
///
/// Cas de test: coins de la nouvelle clôture correspondant aux
/// coordonnées de clôtures
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testRedimension()
{
	//dimensions de la clotures
	int xMinClotureTest = 0;
	int yMinClotureTest = 0;
	int xMaxClotureTest = 0;
	int yMaxClotureTest = 0;
	//coins pour redimensionner
	Vecteur2i cointest1(100,100);
	Vecteur2i cointest2(700,700);
	testProjection->redimensionnerFenetre(cointest1,cointest2);

	//obtenir les coordonnées de la cloture après la redimension et comparer avec les coins simulés
	testProjection->obtenirCoordonneesCloture(xMinClotureTest,xMaxClotureTest,yMinClotureTest,yMaxClotureTest);
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(cointest1[0] - xMinClotureTest));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(cointest1[1] - yMinClotureTest));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(cointest2[0] - xMaxClotureTest));
	CPPUNIT_ASSERT(utilitaire::EGAL_ZERO(cointest2[1] - yMaxClotureTest));	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testObtentionVirtuel()
///
/// Cas de test: exactitude des coordonnées virtuelles
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testObtentionVirtuel()
{
	double xMinFenetreTest = 0;
	double yMinFenetreTest = 0;
	double xMaxFenetreTest = 0;
	double yMaxFenetreTest = 0;
	testProjection->obtenirCoordonneesFenetreVirtuelle(xMinFenetreTest,xMaxFenetreTest,yMinFenetreTest,yMaxFenetreTest);
	CPPUNIT_ASSERT(xMinFenetreTest == -100);
	CPPUNIT_ASSERT(xMaxFenetreTest ==  100);
	CPPUNIT_ASSERT(yMinFenetreTest == -100);
	CPPUNIT_ASSERT(yMaxFenetreTest ==  100);		
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ProjectionOrthoTest::testObtentionCloture()
///
/// Cas de test: exactitude des coordonnées de clotures
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ProjectionOrthoTest::testObtentionCloture()
{
	int xMinClotureTest = 0;
	int yMinClotureTest = 0;
	int xMaxClotureTest = 0;
	int yMaxClotureTest = 0;
	testProjection->obtenirCoordonneesCloture(xMinClotureTest,xMaxClotureTest,yMinClotureTest,yMaxClotureTest);
	CPPUNIT_ASSERT(xMinClotureTest == 0);
	CPPUNIT_ASSERT(xMaxClotureTest == 500);
	CPPUNIT_ASSERT(yMinClotureTest == 0);
	CPPUNIT_ASSERT(yMaxClotureTest == 500);		
}
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////