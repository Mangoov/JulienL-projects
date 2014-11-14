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
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
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
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
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
/// Cas de test : transformation d'un point 3D en coordonn�es homog�nes
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void UtilitaireTest::testAppliquerMatrice()
{
	//matrice identit�
	const double matriceTest[] =  {1, 0, 0, 0,
								   0, 1, 0, 0,
								   0, 0, 1, 0,
								   0, 0, 0, 1};
	//point � transformer
	Vecteur3 point(1,2,3);
	//v�rifier si le resultat retourn� est bien le m�me point
	CPPUNIT_ASSERT(utilitaire::appliquerMatrice(point, matriceTest) == point);
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void UtilitaireTest::testRadToDeg()
///
/// Cas de test : conversion d'un angle de radian en degr�s
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