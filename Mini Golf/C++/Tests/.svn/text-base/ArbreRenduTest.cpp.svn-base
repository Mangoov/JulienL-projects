////////////////////////////////////////////////////////////////////////////////////
/// @file ArbreRenduTest.cpp
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-23
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudComposite.h"
#include "ArbreRenduTest.h"
#include "Usines/UsineNoeudAraignee.h"
//#include "Utilitaire.h"
//#include "FacadeModele.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( ArbreRenduTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduTest::setUp()
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
void ArbreRenduTest::setUp()
{	
	arbreTest = new ArbreRendu();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduTest::tearDown()
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
void ArbreRenduTest::tearDown()
{
	delete arbreTest;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduTest::testCreerNoeud()
///
/// Cas de test: création réussite du noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduTest::testCreerNoeud()
{
	arbreTest->ajouterUsine("noeudTest", new UsineNoeudAraignee("noeudTest"));
	NoeudAbstrait* noeudTest = arbreTest->creerNoeud("noeudTest");
	arbreTest->ajouter(noeudTest);
	CPPUNIT_ASSERT(arbreTest->chercher("noeudTest") != 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduTest::testAjoutNouveauNoeud()
///
/// Cas de test: ajout d'un nouveau noeud dans l'arbre
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduTest::testAjoutNouveauNoeud()
{
	arbreTest->ajouterUsine("noeudTest", new UsineNoeudAraignee("noeudTest"));
	arbreTest->ajouterUsine("enfant", new UsineNoeudAraignee("enfant"));
	NoeudAbstrait* noeudTest = arbreTest->creerNoeud("noeudTest");
	arbreTest->ajouter(noeudTest);
	CPPUNIT_ASSERT(arbreTest->ajouterNouveauNoeud("noeudTest","enfant") != 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ArbreRenduTest::testCalculProfondeurMax()
///
/// Cas de test: calcul de la profonde
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ArbreRenduTest::testCalculProfondeurMax()
{	
	GLint glMaxNameStackDept_;
	glGetIntegerv(GL_MAX_NAME_STACK_DEPTH , &glMaxNameStackDept_);
	CPPUNIT_ASSERT(arbreTest->calculerProfondeurMaximale() == glMaxNameStackDept_ );	
}

///////////////////////////////////////////////////////////////////////////////
/// @}
//////////////////////////////////////////////////////////////////////////////