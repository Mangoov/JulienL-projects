package ca.polymtl.inf2990;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.Timer;
import java.util.TimerTask;

import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.EventQueue;
import java.awt.Image;
import java.awt.Toolkit;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.WindowConstants;
import java.awt.Graphics2D;
import java.awt.SplashScreen;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.event.WindowStateListener;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;


// pour afficher le splash screen dans run configuration, arguments, VM arguments
// copier -splash:${workspace_loc:InterfaceGraphique}\src\ca\polymtl\inf2990\icones\angryball.png
//bon exemple : http://www.twoplayergames.org/play/39-Office_Golf.html

/**
 *
 * @author Etienne Vallée et Jean-Luc Dubeau
 */
public class InterfaceJava implements Runnable, WindowListener
{
	/////////////////////////
	//                     //
	//  FONCTIONS NATIVES  //
	//                     //
	/////////////////////////


	/**
	 * Initialisation statique de la classe qui charge la librairie C++ contenant
	 * l'implantation des fonctions natives.
	 */
	static {
		System.loadLibrary("DLL/INF2990");
	}


	/**
	 * Fonction qui initialise un contexte OpenGL dans la fenêtre identifiée par
	 * le canvas AWT passé en paramètre.  Cette fonction doit être la première à
	 * être appelée, car la création de l'objet du modèle C++ s'attend à avoir un
	 * contexte OpenGL valide.
	 *
	 * @param   canvas   Le canvas dans lequel créer le contexte OpenGL.
	 */
	public static native void fctC_initialiserOpenGL( Canvas canvas );

	/**
	 * Fonction qui libère le contexte OpenGL dans la fenêtre identifiée par le
	 * canvas AWT passé en paramètre.  Cette fonction doit être la dernière à
	 * être appelée, car elle libère également l'objet du modèle C++.
	 *
	 * @param   canvas   Le canvas dans lequel créer le contexte OpenGL.
	 */
	public static native void fctC_libererOpenGL( Canvas canvas );

	/**
	 * Fonction qui affiche la scène dans la fenêtre identifiée par le canvas AWT
	 * passé en paramètre.
	 *
	 * @param   canvas   Le canvas dans lequel créer le contexte OpenGL.
	 */
	public static native void fctC_dessinerOpenGL( Canvas canvas );

	/**
	 * Fonction qui doit être appelée lorsque la fenêtre est redimensionnée afin
	 * d'ajuster les paramètres de la machine à états d'OpenGL pour correspondre
	 * aux nouvelles dimensions de la fenêtre.
	 *
	 * @param   largeur   La nouvelle largeur de la fenêtre.
	 * @param   hauteur   La nouvelle hauteur de la fenêtre.
	 */
	public static native void fctC_redimensionnerFenetre(
			int largeur, int hauteur
			);

	/**
	 * Fonction qui anime le jeu d'un certain intervalle de temps.
	 * 
	 * Elle vise à être appelée de nombreuses fois par seconde.  Elle effectue
	 * les différents calculs de physique et effectue un affichage.
	 *
	 * @param   temps   L'intervalle de temps à utiliser pour les différents
	 *                  calculs.  On vise à faire correspondre cet invervalle de
	 *                  temps au temps entre deux appels à la fonction.
	 */
	public static native void fctC_animer(float temps);

	/**
	 * Fonction qui applique un zoom avant sur le présent volume de vision.
	 */
	public static native void fctC_zoomIn(int pourcentage);

	/**
	 * Fonction qui applique un zoom arrière sur le présent volume de vision.
	 */
	public static native void fctC_zoomOut(int pourcentage);

	/**
	 * Fonction qui retourne le nombre moyen d'affichage par secondes.
	 */
	public static native int obtenirAffichagesParSeconde();

	/**
	 * Fonction qui exécute les jeux de tests unitaires C++.
	 */
	public static native int fctC_executerTests();

	/**
	 * Fonction qui permet de déplacer la fenêtre virtuelle.
	 */
	public static native void fctC_deplacerXY(double deplacementX,double deplacementY);

	/**
	 * Fonction qui permet de zoomer selon un rectangle élastique
	 */
	public static native void fctC_zoomerInElastique(int coin1x, int coin1y , int coin2x, int coin2y);

	/**
	 * Fonction qui permet d'effectuer un zoom arriere selon un rectangle élastique
	 */
	public static native void fctC_zoomerOutElastique(int coin1x, int coin1y , int coin2x, int coin2y);
	
	/**
	 * Fonction qui permet d'initialiser le traçage du rectangle élastique
	 */
	public static native void fctC_initialiserRectangleElastique(int ancrageX, int ancrageY);

	/**
	 * Fonction qui permet de mettre a jour le traçage du rectangle élastique
	 */
	public static native void fctC_mettreAJourRectangleElastique(int ancrageX, int ancrageY, int coin1x, int coin1y , int coin2x, int coin2y);

	/**
	 * Fonction qui permet de terminer le traçage du rectangle élastique
	 */
	public static native void fctC_terminerRectangleElastique(int ancrageX, int ancrageY, int coin2x, int coin2y);

	/**
	 * Fonction qui permet de selectionner un objet basé sur les paremetres x et y
	 */
	public static native void  fctC_selectionClick(  int sourisX, int sourisY, int modeSelection);

	/**
	 * Selectionne un objet base sur les paremetres x et y du debut et de fin
	 */
	public static native void  fctC_selectionRectangle( int startX, int startY, int endX, int endY);

	/**
	 * Effectue une rotation sur tous les objets selectionnés
	 * @param angle 
	 */
	public static native void  fctC_rotationSelection(float angle);

	/**
	 * Permet de Créer les objets et les ajouter a l'arbre lorsqu'on est dans le mode d'édition
	 * 
	 */
	public static native boolean  fctC_creationObject(int i, double SourisX, double SourisY, double Souris2X, double Souris2Y);

	/**
	 * Delete les objets selectionnes
	 * 
	 */
	public static native void  fctC_deleteSelection();

	/**
	 * Deplace les objets selectionnes en se servant de la position actuelle de la souris
	 * 
	 */
	public static native void  fctC_deplacementSelection(int lastX, int lastY, int sourisX, int sourisY );

	/**
	 * Duplique les objets selectionnés
	 * 
	 */
	public static native void  fctC_duplicationSelection();

	/**
	 * Désélectionne les objets selectionnés
	 * 
	 */
	public static native void fctC_viderSelection();

	/**
	 * Détruit tous les objets
	 * 
	 */
	public static native void fctC_viderArbre();

	/**
	 * Converti les coordonées de cloture à virtuelle
	 * 
	 */
	public static native int[] fctC_convertirCoordonneesSouris(int sourisX, int sourisY);

	/**
	 * Enregistre dans le XML
	 * 
	 */
	public static native boolean fctC_enregistrerXml(String nomDoc, int par);

	/**
	 * Charge le XML
	 * 
	 */
	public static native void fctC_chargerXml(String nomDoc);

	/**
	 * Change le facteur d'agrandissement des objets sélectionnés
	 * 
	 */
	public static native void fctC_facteurSelection(float facteur);

	/**
	 * Prend du C++ les données de l'objet sélectionné
	 * 
	 */
	public static native int[] fctC_recevoirInformation();

	/**
	 * Change le facteur d'agrandissement des objets sélectionnés
	 * 
	 */
	public static native void fctC_manipulerObjet(int X, int Y, int Z, int rotation, int facteur);

	/**
	 * Vérifie si une balle est cliquée
	 * @return boolean (vrai si c'est une balle)
	 * 
	 */
	public static native boolean fctC_clickBalle(int X, int Y);

	/**
	 * Crée la flèche qui indique la force et la direction du cou
	 * 
	 */
	public static native void fctC_creerFleche();

	/**
	 * Efface la flèche qui indique la force et la direction du coup
	 * 
	 */
	public static native void fctC_effacerFleche();

	/**
	 * Modifie la flèche qui indique la force et la direction du coup
	 * 
	 */
	public static native void fctC_modifierFleche(int x, int y);

	/**
	 * Modifie le mode  (jeu ou édition)
	 * 
	 */
	public static native void fctC_changerMode(boolean mode);

	/**
	 * Obtenir la friction du sol
	 * 
	 */
	public static native int fctC_obtenirFrictionSol();

	/**
	 * Mdifier la friction du sol
	 * 
	 */
	public static native void fctC_modifierFrictionSol(int frictionSol);

	/**
	 * Obtenir la friction du sable
	 * 
	 */
	public static native int fctC_obtenirFrictionSable();

	/**
	 * Modifier la friction du sable
	 * 
	 */
	public static native void fctC_modifierFrictionSable(int frictionSable);

	/**
	 * Obtenir le rebond du mur
	 * 
	 */
	public static native int fctC_obtenirRebondMur();

	/**
	 * Modifier le rebond du mur
	 * 
	 */
	public static native void fctC_modifierRebondMur(int rebondMur);

	/**
	 * Obtenir l'acceration du bonus
	 * 
	 */
	public static native int fctC_obtenirAccelerationBonus();

	/**
	 * Modifier l'acceration du bonus
	 * 
	 */
	public static native void fctC_modifierAccelerationBonus(int accelerationBonus);

	/**
	 * Obtenir la hauteur de la zone edition
	 * 
	 */
	public static native int fctC_obtenirTailleEditionHauteur();

	/**
	 * Modifier la hauteur de la zone edition
	 * 
	 */
	public static native void fctC_modifierTailleEditionHauteur(int tailleHauteur);

	/**
	 * Obtenir la largeur de la zone edition
	 * 
	 */
	public static native int fctC_obtenirTailleEditionLargeur();

	/**
	 * Modifier la largeur de la zone edition
	 * 
	 */
	public static native void fctC_modifierTailleEditionLargeur(int tailleLargeur);

	/**
	 * Forcer la sauvegarde du fichier configuration.xml
	 * 
	 */
	public static native void fctC_forcerSauvergardeConfig();

	/**
	 * Modifier la touche de la fleche
	 * 
	 */
	public static native void fctC_modifierFlecheTouche(int x);

	/**
	 * Vérifie si la balle est dans le trou
	 * 
	 */
	public static native boolean fctC_verifierVictoire();

	/**
	 * Permet d'effacer un fichier XML
	 * 
	 */
	public static native void fctC_effacerFichierXml(String nomDoc);

	/**
	 * Permet de charger un fichier joueur
	 * 
	 */
	public static native void fctC_chargerFichierJoueur();

	/**
	 * Permet de charger un fichier de tournoi
	 * 
	 */
	public static native void fctC_chargerFichierTournoi();

	/**
	 * Permet d'enregistrer un fichier joueur
	 * 
	 */
	public static native void fctC_enregistrerFichierJoueur();

	/**
	 * Permet d'enregistrer un fichier tournoi
	 * 
	 */
	public static native void fctC_enregistrerFichierTournoi();

	/**
	 * Permet d'ajouter un joueur
	 * 
	 */
	public static native void fctC_ajouterJoueur(String nomDoc);

	/**
	 * Permet d'ajouter un tournoi
	 * 
	 */
	public static native void fctC_ajouterTournoi(String nomDoc);

	/**
	 * Permet d'obtenir les touches du clavier.
	 * 
	 */
	public static native int[] fctC_obtenirToucheClavier();

	/**
	 * Permet de modifier les touches du clavier.
	 * 
	 */
	public static native void fctC_modifierToucheClavier(int gauche, int droit, int haut, int bas, int espace);
	
	/**
	 * Permet d'obtenir les touches d'options du clavier.
	 * 
	 */
	public static native String[] fctC_obtenirOptionClavier();

	/**
	 * Permet de modifier les touches d'options du clavier.
	 * 
	 */
	public static native void fctC_modifierOptionClavier(String gauche, String droit, String haut, String bas, String espace);

	/**
	 * Obtenir nom parcours.
	 * 
	 */
	public static native String[] fctC_obtenirNomsParcours(String nomTournoi);
	
	/**
	 * Obtenir les noms de tournoi present dans le fichier de tournoi par defaut.
	 * 
	 */
	public static native String[] fctC_obtenirNomsTournois();
	
	/**
	 * Obtenir le nombre de tournois present dans le fichier de tournoi par defaut.
	 * 
	 */
	public static native int fctC_obtenirNombreTournois();

	/**
	 * Permet de modifier une fiche de tournoi se trouvant dans le fichier xml de tournoi par defaut.
	 * 
	 */ 
	public static native void fctC_modifierFicheTournoi(String nomTournoi, String Parcours,
			String nomJoueur,int Score); 
	
	/**
	 * Permet de changer la vue
	 * 
	 */
	public static native void fctC_changerVue(int vue);
	
	/**
	 * Permet d'ajouter un parcours appartenant au tournoi passe en parametre.
	 * 
	 */
	public static native void fctC_ajouterParcoursATournoi(String nomTournoi ,String Parcours );

	/**
	 * Permet d'initialiser le son
	 * 
	 */
	public static native void fctC_initialiserSon();

	/**
	 * Retourne un entier representant la type de vue utilisee
	 * 
	 */
	public static native int fctC_getTypeVue(); 

	/**
	 *  Deplace la camera
	 * 
	 */
	public static native void fctC_deplacerLibre(int Horizontale, int Verticale); 

	/**
	 *  Joue la musique
	 * 
	 */
	public static native void fctC_play();

	/**
	 *  Arrete la musique
	 * 
	 */
	public static native void fctC_stop(); 

	/**
	 *  Ajuste le volume des sons
	 * 
	 */
	public static native void fctC_ajusterVolumeSon(float volume); 

	/**
	 *  Ajuste le volume de la musique
	 * 
	 */
	public static native void fctC_ajusterVolumeMusique(float volume); 

	/**
	 *  Passe à la prochaine musique
	 * 
	 */
	public static native void fctC_musiqueSuivante(); 

	/**
	 *  Retourne à la piste précédente
	 * 
	 */
	public static native void fctC_musiquePrecedente(); 

	/**
	 *  Change l'état de la musique du menu
	 * 
	 */
	public static native void fctC_musiqueMenu(int etat);

	/**
	 *  Tourne la camera
	 * 
	 */
	public static native void fctC_tournerCamera(double rotationX, double rotationY); 

	/**
	 *  Orbite la camera
	 * 
	 */
	public static native void fctC_orbiterCamera(double rotationX, double rotationY);

	/**
	 *  Retourne le nombre de coups
	 * 
	 */
	public static native int fctC_obtenirFrappes();

	/**
	 *  Retourne le nom du joueur
	 * 
	 */
	public static native void fctC_obtenirNomJoueur(String nomJoueur);
	
	/**
	 * Converti les coordonées de cloture à virtuelle, version 2
	 * 
	 */
	public static native double[] fctC_convertirCoordonneesSouris2(int sourisX, int sourisY);
	
	/**
	 *  Permet de sauvegarder les informations specifiques au joueur pour pouvoir les recharger lors du mode multijoueur.
	 * 
	 */
	public static native void fctC_sauvegarderMultijoueur(String NomMap);
	
	/**
	 *  Permet de charger les informations specifiques au joueur lors du mode multijoueur.
	 * 
	 */	   
	public static native void fctC_chargerMultijoueur(String NomJoueur);
	
	/**
	 *  Cette fonction arrête ou repart le volume
	 * 
	 */	
	public static native void fctC_mute();

	/**
	 *  Retourne le nom de la map
	 * 
	 */
	public static native void fctC_obtenirNomMap(String nomMap);
	
	/**
	 *  Retourne le int de Par de la map
	 * 
	 */
	public static native int fctC_obtenirPardeMap(String nomMap);
	
	/**
	 *  Retourne le nombre de joueurs dans le fichier de joueurXML.
	 * 
	 */
	public static native int fctC_obtenirNombreJoueursTableauMeilleurScore();
	
	/**
	 *  Retourne le nombre de parcours sous le nom de joueur dans le fichier de joueurXML.
	 * 
	 */
	public static native int fctC_obtenirNombreParcoursTableauMeilleurScore(String nomJoueur);
	
	/**
	 *  Retourne les noms de parcours presents sous le nom de joueur dans le fichier JoueurXML.
	 * 
	 */
	public static native String[] fctC_obtenirNomsParcoursTableauMeilleurScore(String nomJoueur);
	
	/**
	 *  Initialise les listes d'affichages
	 * 
	 */
	public static native void fctC_initialiserListesAffichage();
	
	/**
	 *  Cette methode permet d'effacer le fichier contenant le tableau des meilleurs scores.
	 * 
	 */
	public static native void fctC_effacerFichierJoueur();

	/////////////////////////
	//                     //
	//       FIN DES       //
	//  FONCTIONS NATIVES  //
	//                     //
	/////////////////////////


	/**
	 * Main du programme, lance les tests et crée l'instance du contrôleur
	 * 
	 */
	public static void main(String[] args)
	{
		// initialisation des parametre d'affichage du splash screen
		// splashInit();           
		//appInit();

		// verifier l'existence du splash screen
		//if (mySplash != null)   
		//     mySplash.close();

		// Vérifier si nous exécuterons les tests unitaires... 
		if (args.length >= 1 && args[0].equals("testsC++")) 
		{
			// Exécution des tests C++
			int resultat = fctC_executerTests();
			System.exit(resultat);
		}
		// Pas d'exécution des tests unitaires, crééons la fenêtre et affichons-là
		else 
		{
			//Change le "LookAndFeel" pour celui de la platforme qui roule le programme
			try {
				UIManager.setLookAndFeel(
						UIManager.getSystemLookAndFeelClassName());
			} catch (Exception e) { }

			// Création de l'unique instance du contrôleur
			final InterfaceJava instance = new InterfaceJava();
			EventQueue.invokeLater(instance);

		}
	}


	/**
	 * Initialise le Canvas à la taille et la couleur voulue
	 * 
	 */
	public void initialiserCanvas (Canvas canvas)
	{
		canvas_.setBackground(Color.BLACK);
		canvas_.setPreferredSize(new Dimension(800,600));
	}

	/**
	 * Cette fonction construit la fenêtre Java
	 * 
	 */
	public void construireFenetre()
	{
		//Pour Indiquer dans quelle fonction/méthode nous sommes dans la console
		System.out.println("construireFenetre");

		//Défini le titre de l'application
		fenetreGeneral_.setTitle("Angry Balls");
		fenetreGeneral_.getContentPane().setLayout(new BorderLayout());		
		//Défini l'opération de fermeture de la fenêtre
		fenetreGeneral_.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		fenetreGeneral_.add(canvas_,BorderLayout.CENTER);
		fenetreGeneral_.addWindowListener(this);

		// change l'icone de la fenetre
		BufferedImage image = null;
		try 
		{
			image = ImageIO.read(fenetreGeneral_.getClass().getResource("/ca/polymtl/inf2990/icones/Golf_Icone.png"));
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
		fenetreGeneral_.setIconImage(image);

		//Appel l'initialisation du canvas
		initialiserCanvas(canvas_);
		mode_ = "Editeur";

		fenetreGeneral_.pack();
		//Initialise l'OpenGl
		fctC_initialiserOpenGL(canvas_);
		canvas_.requestFocus();		
	}

	/**
	 * Cette fonction instancie la fenêtre, le canvas et les menus
	 * 
	 */
	public InterfaceJava()
	{
		//Pour Indiquer dans quelle fonction/méthode nous sommes
		System.out.println("InterfaceJava");

		fenetreGeneral_ = new JFrame();
		canvas_ = new Canvas();
		etat_ = new ContexteEtat();
		menuPrincipal_ = MenuPrincipal.getInstance();
		dialogue_ = new Dialog();
		menuDeBase_ = MenuDeBase.getInstance();
	}

	/**
	 * Cette fonction appel la construction de la fenetre, des menus et du gestionnaire
	 * Elle active aussi la minuterie
	 */
	public void run() {

		//Pour Indiquer dans quelle fonction/méthode nous sommes
		System.out.println("run");

		splashInit();           
		appInit();

		// verifier l'existence du splash screen
		if (mySplash != null)   
			mySplash.close();



		// Activation de la minuterie appelée plusieurs fois par seconde pour
		// réafficher la fenêtre.
		activerMinuterie();

		menuDeBase_.setVisible(true);
		fctC_musiqueMenu(1);
	}

	/**
	 * Cette fonction active la minuterie qui appelle périodiquement une fonction
	 * afin de rafraîchir constamment la fenêtre.
	 */
	private void activerMinuterie() {

		//Pour Indiquer dans quelle fonction/méthode nous sommes
		System.out.println("activerMinuterie");

		Timer minuterie = new Timer();
		minuterie.scheduleAtFixedRate(new TimerTask() {
			@Override
			public void run() {
				try {
					SwingUtilities.invokeAndWait(new Runnable() {
						@Override
						public void run() {
							float temps = TEMPS_INTER_AFFICHAGE / 1000.0f;
							//Si l'on veut arrêter l'affichage
							if(arretMinuterie_ == false)
							{
								fctC_animer(temps);
								fctC_dessinerOpenGL(canvas_);
								if(fctC_verifierVictoire() == true)
								{
									if(menuPrincipal_.jouerEdition == false)
										menuPrincipal_.Pointage();
										
									if((menuDeBase_.mapTournoi==null || map == menuDeBase_.mapTournoi.length)&&joueurCourant_ == menuDeBase_.nbJoueur)
									{
										if(menuPrincipal_.jouerEdition==false)
										{
											InterfaceJava.fctC_stop();
											InterfaceJava.fctC_musiqueMenu(1);											
											menuDeBase_.setVisible(true);
											fenetreGeneral_.setVisible(false);
										}
										else
										{
											menuDeBase_.edition("CurrentMap.xml");
											menuPrincipal_.jouerEdition=false;
										}
									}
									else
									{
										if(joueurCourant_ == menuDeBase_.nbJoueur)
										{
											if(joueurCourant_ == 2)
											{
												joueurCourant_ = 1;
											}
											fctC_viderArbre();
											fctC_chargerXml(menuDeBase_.mapTournoi[map]);
											fctC_obtenirNomJoueur(menuDeBase_.nomJoueur);
											fctC_obtenirNomMap(menuDeBase_.mapTournoi[map]);
											map++;
										}
										else
										{
											joueurCourant_ = 2;
											fctC_viderArbre();
											fctC_chargerXml(menuDeBase_.mapTournoi[map-1]);
											fctC_obtenirNomJoueur(menuDeBase_.nomJoueur2);
										}
									}
								}
							}
						}
					});
				}
				catch (InvocationTargetException ex) {
					ex.printStackTrace();
				}
				catch (InterruptedException ex) {
					ex.printStackTrace();
				}
			}
		}, 0, TEMPS_INTER_AFFICHAGE);
	}

	/**
	 * Fonction qui s'occupe de calculer la progression de la barre de progres
	 * et les taches effectue avant l'ouverture du programme
	 */
	private void appInit()
	{
		splashProgress(20);
		fctC_initialiserSon();
		splashProgress(60);
		
		// Construction de la fenêtre.
		construireFenetre();
		fctC_initialiserListesAffichage();
		splashProgress(80);
		fenetreGeneral_.setVisible(false);
		fenetreGeneral_.setLocationRelativeTo(null);

		//Création des différentes parties du menu
		menuPrincipal_.creerMenu();
		menuPrincipal_.creerBarreOutilGeneral();
		menuPrincipal_.creerBarreOutilEdition();
		menuPrincipal_.creeBarreStatus();
		etat_.choixEtat(EtatEditeur.getInstance());
		etat_.ajouterGestionnaires(menuPrincipal_);
		splashProgress(99);
		splashProgress(100);

	}

	/**
	 * Preparation du splash screen
	 */
	private static void splashInit()
	{
		mySplash = SplashScreen.getSplashScreen();

		if (mySplash != null)
		{
			// obtenir la grandeur de l'image
			Dimension ssDim = mySplash.getSize();
			int hauteurImage = ssDim.height;
			int largeurImage = ssDim.width;

			// disposer la barre de progression sur l'image
			splashProgressArea = new Rectangle2D.Double(largeurImage * .30, hauteurImage*.92, largeurImage*.4, 12 );

			// creation de l'environnement graphique pour dessiner
			splashGraphics = mySplash.createGraphics();
		}
	}

	/**
	 * Creation de la barre de progres
	 * @param tacheEffectue combien de pourcent de la barre de progression a afficher (de 0 a 100)
	 */
	public static void splashProgress(int tacheEffectue)
	{
		if (mySplash != null && mySplash.isVisible())
		{
			// interieur de la barrede progression vide
			splashGraphics.setPaint(Color.BLACK);
			splashGraphics.fill(splashProgressArea);

			// contour de la barre de progression
			splashGraphics.setPaint(Color.RED);
			splashGraphics.draw(splashProgressArea);

			// calculer les pourcentage de la barre de progression
			int x = (int) splashProgressArea.getMinX();
			int y = (int) splashProgressArea.getMinY();
			int largeurBarre = (int) splashProgressArea.getWidth();
			int hauteurBarre = (int) splashProgressArea.getHeight();

			int largeurEffectue = Math.round(tacheEffectue*largeurBarre/100.f);
			largeurEffectue = Math.max(0, Math.min(largeurEffectue, largeurBarre-1));

			// remplir la partir realise de la barre de progression
			splashGraphics.setPaint(Color.ORANGE);
			splashGraphics.fillRect(x, y+1, largeurEffectue, hauteurBarre-1);

			// s'assurer de l'affichage
			mySplash.update();
		}
	}

	//Variables de declaration
	static private final int TEMPS_INTER_AFFICHAGE = 20; // Le temps souhaité entre 2 affichages, en millisecondes.
	public static Canvas canvas_;
	static JFrame fenetreGeneral_;
	private JPanel fenetreMenuGeneral_;
	private ContexteEtat etat_;
	private MenuPrincipal menuPrincipal_;
	private MenuDeBase menuDeBase_;
	public static String mode_;
	public static boolean arretMinuterie_ = false;
	public Dialog dialogue_;
	public static SplashScreen mySplash;                   // pour obtenir les graphic
	public static Graphics2D splashGraphics;               // contexte graphic pour afficher l'image du splash screen
	public static Rectangle2D.Double splashProgressArea;   // region ou on dessine la barre de progression
	public static int map = 1;
	public static int joueurCourant_ = 1;
	private Pointage pointage_ = Pointage.getInstance();
	

	@Override
	public void windowActivated(WindowEvent e) {
	}

	@Override
	public void windowClosed(WindowEvent e) {
	}

	@Override
	public void windowClosing(WindowEvent e) {
		int choix = menuPrincipal_.boiteDialogueChoix("Êtes-vous certain de vouloir quitter?" + '\n' + "Tous les changements non sauvegardés seronts perdus.", "Quitter?");
		if(choix != 1)
		{
			System.exit(0);
		}

	}

	@Override
	public void windowDeactivated(WindowEvent e) {
	}

	@Override
	public void windowDeiconified(WindowEvent e) {
	}

	@Override
	public void windowIconified(WindowEvent e) {
	}

	@Override
	public void windowOpened(WindowEvent e) {
	}
	
	public static int getJoueurCourant(){
		return joueurCourant_;
	}
}
