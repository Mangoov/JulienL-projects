////////////////////////////////////////////////////////////////////////////////////
/// @file NoeudCompositeTest.cpp
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-09-25
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "NoeudCompositeTest.h"
#include "Utilitaire.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( NoeudCompositeTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::setUp()
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
void NoeudCompositeTest::setUp()
{
	noeud = new NoeudAraignee(ArbreRenduINF2990::NOM_ARAIGNEE);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::tearDown()
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
void NoeudCompositeTest::tearDown()
{
	delete noeud;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testVider()
///
/// cas de test : vider le noeud
/// 
/// 
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testVider()
{
	noeud->vider();
	CPPUNIT_ASSERT(noeud->obtenirNombreEnfants() == 0);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testChercher()
///
/// cas de test : recherche d'un noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testChercher()
{
	NoeudAbstrait* nouveauNoeud = new NoeudAraignee(ArbreRenduINF2990::NOM_CONECUBE);
	noeud->ajouter(nouveauNoeud);
	CPPUNIT_ASSERT(noeud->chercher("Araignee") != 0);
	CPPUNIT_ASSERT(noeud->chercher("conecube") != 0);
	CPPUNIT_ASSERT(noeud->chercher("patate") == 0);
	CPPUNIT_ASSERT(noeud->chercher(0) != 0);
	CPPUNIT_ASSERT(noeud->chercher(-1) == 0);
	CPPUNIT_ASSERT(noeud->chercher(1) == 0);
	noeud->effacer(nouveauNoeud);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEffacer()
///
/// cas de test : effacement d'un noeud
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacer()
{
	NoeudAbstrait* nouveauNoeud = new NoeudAraignee(ArbreRenduINF2990::NOM_CONECUBE);
	noeud->ajouter(nouveauNoeud);
	noeud->effacer(nouveauNoeud);
	CPPUNIT_ASSERT(noeud->chercher("conecube")== 0);	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testEffacerSelection()
///
/// cas de test : effacement des noeuds selectionnes
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testEffacerSelection()
{
	NoeudAbstrait* nouveauNoeud = new NoeudAraignee(ArbreRenduINF2990::NOM_CONECUBE);
	nouveauNoeud->assignerSelection(true);
	noeud->ajouter(nouveauNoeud);
	noeud->effacerSelection();
	CPPUNIT_ASSERT(noeud->chercher("conecube") == 0);	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudCompositeTest::testSelectionnerTout()
///
/// cas de test : selection de tous les noeuds
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudCompositeTest::testSelectionnerTout()
{
	NoeudAbstrait* nouveauNoeud1 = new NoeudAraignee(ArbreRenduINF2990::NOM_CONECUBE);
	NoeudAbstrait* nouveauNoeud2 = new NoeudAraignee("patate");
	noeud->ajouter(nouveauNoeud1);
	noeud->ajouter(nouveauNoeud2);
	noeud->selectionnerTout();
	CPPUNIT_ASSERT(noeud->estSelectionne());
	CPPUNIT_ASSERT(nouveauNoeud1->estSelectionne());
	CPPUNIT_ASSERT(nouveauNoeud2->estSelectionne());	
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
