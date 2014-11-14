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
/// Effectue l'initialisation pr�alable � l'ex�cution de l'ensemble des
/// cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets doivent �tre construits, il est conseill� de le
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
/// Effectue les op�rations de finalisation n�cessaires suite � l'ex�cution
/// de l'ensemble des cas de tests de cette suite de tests (si n�cessaire).
/// 
/// Si certains objets ont �t� allou�s � l'initialisation, ils doivent �tre
/// d�sallou�s, et il est conseill� de le faire ici.
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
	////r�gler l'�tat enregistrable � faux
	//noeudTest->assignerEstEnregistrable(false);
	//visiteurTest->visiterNoeudAbstrait(noeudTest);

	//// V�rifier que noeudTest n'a pas �t� ajout� dans l'arbre XML
	//CPPUNIT_ASSERT(visiteurTest->obtenirArbreXML()->LastChild(noeudTest->obtenirType().c_str()) == 0);

	////vider l'arbre XML
	//visiteurTest->obtenirArbreXML()->Clear();

	////r�gler l'�tat enregistrable � vrai
	//noeudTest->assignerEstEnregistrable(true);
	//visiteurTest->visiterNoeudAbstrait(noeudTest);

	////V�rifier que la valeur du noeud ajout� dans l'arbre XML est la m�me que celle de noeudTest
	//CPPUNIT_ASSERT(visiteurTest->obtenirArbreXML()->FirstChildElement()->Value() == noeudTest->obtenirType());
	//visiteurTest->obtenirArbreXML()->Clear();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void VisiteurXMLTest::testEcrireFichier()
///
/// Cas de test: cas de test �criture du fichier de configuration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////

void VisiteurXMLTest::testEcrireFichier()
{
	////cr�er l'arbre qui contiendra les donn�es � �crire et ajouter noeudTest
	//ArbreRenduINF2990* arbreTest = new ArbreRenduINF2990();	
	//arbreTest->ajouter(noeudTest);
	//
	//visiteurTest->ecrireFichier(arbreTest, "testEcriture.xml");

	////v�rifier si le chargement du fichier est r�ussi
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
	//cr�er l'arbre qui contiendra les donn�es � �crire et ajouter noeudTest
	//ArbreRenduINF2990* arbreTest = new ArbreRenduINF2990();

	//visiteurTest->lireFichierXML(arbreTest,"testEcriture.xml");

	////v�rification des attributs de l'arbre 
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