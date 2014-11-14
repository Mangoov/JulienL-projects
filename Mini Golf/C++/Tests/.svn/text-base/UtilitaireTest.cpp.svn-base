//////////////////////////////////////////////////////////////////////////////
/// @file UtilitaireTest.cpp
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar
/// @date 2011-09-25
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "UtilitaireTest.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( UtilitaireTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::setUp()
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
void UtilitaireTest::setUp()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::tearDown()
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
void UtilitaireTest::tearDown()
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testAppliquerMatrice()
///
/// Cas de test : transformation d'un point 3D en coordonnées homogènes
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testAppliquerMatrice()
{
	//matrice identité
	const double matriceTest[] =  {1, 0, 0, 0,
								   0, 1, 0, 0,
								   0, 0, 1, 0,
								   0, 0, 0, 1};
	//point à transformer
	Vecteur3 point(1,2,3);
	//vérifier si le resultat retourné est bien le même point
	CPPUNIT_ASSERT(utilitaire::appliquerMatrice(point, matriceTest) == point);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testRadToDeg()
///
/// Cas de test : conversion d'un angle de radian en degrés
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testRadToDeg()
{
	CPPUNIT_ASSERT(utilitaire::RAD_TO_DEG((utilitaire::PI)/4) == 45);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testSigne()
///
/// Cas de test : signe d'un nombre
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testSigne()
{
	CPPUNIT_ASSERT(utilitaire::SIGN(-7.2f) == -1.0f);
	CPPUNIT_ASSERT(utilitaire::SIGN( 7.2f) ==  1.0f);
	CPPUNIT_ASSERT(utilitaire::SIGN( 0.0f) ==  0.0f);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testdansLimitesXY()
///
/// Cas de test : test dansLimitesXY
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testdansLimitesXY()
{
	CPPUNIT_ASSERT(utilitaire::DANS_LIMITESXY(100,40,130,50,30,100));
	CPPUNIT_ASSERT(!utilitaire::DANS_LIMITESXY(-50,110,140,-3,20,40));
}
///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////