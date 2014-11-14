////////////////////////////////////////////////////////////////////////////////////
/// @file VisiteurXMLTest.cpp
/// @author Jean-Luc Dubeau & Aiman Badr Jaouhar 
/// @date 2011-10-02
/// @version 1.2
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////


#include "VisiteurXMLTest.h"
#include "ArbreRenduINF2990.h"

// Enregistrement de la suite de tests au sein du registre
CPPUNIT_TEST_SUITE_REGISTRATION( VisiteurXMLTest );

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXMLTest::setUp()
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
void VisiteurXMLTest::setUp()
{	
	visiteurTest = VisiteurXML::obtenirInstance();
	/*noeudTest = new NoeudConeCube("conecube");*/
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXMLTest::tearDown()
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
void VisiteurXMLTest::tearDown()
{	
	visiteurTest->obtenirInstance()->libererInstance();
	/*delete noeudTest;*/
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXMLTest::testVisiterNoeudAbstrait()
///
/// Cas de test: cas de test visite d'un noeud abstrait
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void VisiteurXMLTest::testVisiterNoeudAbstrait()
{
	////régler l'état enregistrable à faux
	//noeudTest->assignerEstEnregistrable(false);
	//visiteurTest->visiterNoeudAbstrait(noeudTest);

	//// Vérifier que noeudTest n'a pas été ajouté dans l'arbre XML
	//CPPUNIT_ASSERT(visiteurTest->obtenirArbreXML()->LastChild(noeudTest->obtenirType().c_str()) == 0);

	////vider l'arbre XML
	//visiteurTest->obtenirArbreXML()->Clear();

	////régler l'état enregistrable à vrai
	//noeudTest->assignerEstEnregistrable(true);
	//visiteurTest->visiterNoeudAbstrait(noeudTest);

	////Vérifier que la valeur du noeud ajouté dans l'arbre XML est la même que celle de noeudTest
	//CPPUNIT_ASSERT(visiteurTest->obtenirArbreXML()->FirstChildElement()->Value() == noeudTest->obtenirType());
	//visiteurTest->obtenirArbreXML()->Clear();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXMLTest::testEcrireFichier()
///
/// Cas de test: cas de test écriture du fichier de configuration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void VisiteurXMLTest::testEcrireFichier()
{
	////créer l'arbre qui contiendra les données à écrire et ajouter noeudTest
	//ArbreRenduINF2990* arbreTest = new ArbreRenduINF2990();	
	//arbreTest->ajouter(noeudTest);
	//
	//visiteurTest->ecrireFichier(arbreTest, "testEcriture.xml");

	////vérifier si le chargement du fichier est réussi
	//CPPUNIT_ASSERT(visiteurTest->obtenirArbreXML()->LoadFile("testEcriture.xml"));	

	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXMLTest::testLireFichier()
///
/// Cas de test: cas de test lecture du fichier de configuration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void VisiteurXMLTest::testLireFichier()
{
	//créer l'arbre qui contiendra les données à écrire et ajouter noeudTest
	//ArbreRenduINF2990* arbreTest = new ArbreRenduINF2990();

	//visiteurTest->lireFichierXML(arbreTest,"testEcriture.xml");

	////vérification des attributs de l'arbre 
	//CPPUNIT_ASSERT(arbreTest->chercher("conecube")->obtenirNombreEnfants() == 0);
	//CPPUNIT_ASSERT(arbreTest->chercher("conecube")->obtenirFacteurAgrandissment() == 1);
	//CPPUNIT_ASSERT(arbreTest->chercher("conecube")->obtenirType() == "conecube");
	//CPPUNIT_ASSERT(!arbreTest->chercher("conecube")->estSelectionnable());
	//CPPUNIT_ASSERT(!arbreTest->chercher("conecube")->estSelectionne());
	//CPPUNIT_ASSERT(arbreTest->chercher("conecube")->estAffiche());
	//
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////