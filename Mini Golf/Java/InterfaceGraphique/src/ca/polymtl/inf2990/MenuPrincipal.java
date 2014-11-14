package ca.polymtl.inf2990;

import java.awt.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import javax.swing.*;

/**
 *
 * @author Etienne Vallée
 */
public class MenuPrincipal implements PropertyChangeListener
{

	/**
	 * Créer une instance de MenuPrincipal
	 */
	public static MenuPrincipal getInstance() {
		if (null == instance_) // Si c'est la première fois
		{ 
			instance_ = new MenuPrincipal();
		}
		return instance_;
	}

	/////////////////////////////////////////
	//                                     //
	//  FONCTIONS DE GESTION D'ÉVÉNEMENTS  //
	//                                     //
	/////////////////////////////////////////	

	//Pour les menus

	/**
	 * Fonction appelée lorsque l'élément Nouveau du menu est actionné.
	 */
	public void Nouveau() 
	{
		System.out.println("L'élément Nouveau a été activé.");
		InterfaceJava.fctC_viderArbre();
		InterfaceJava.fctC_chargerXml("BaseMapEdition.xml");
		sauvegarde_ = false;
		etatEditeur_.setPlacer(false);
		etatSouris = EtatSouris.ES_aucun;
	}	

	/**
	 * Fonction appelée lorsque l'élément Ouvrir du menu est actionné.
	 */
	public void Ouvrir() 
	{
		JFileChooser fc = new JFileChooser(".");
		//Ajoute un filtre pour n'afficher que les fichiers XML
		FiltreXml filtre = new FiltreXml();	
		fc.setFileFilter(filtre);
		int valeurRetour = fc.showOpenDialog(null);
		//Si l'utilisateur choisi un fichier
		if(valeurRetour == JFileChooser.APPROVE_OPTION)
		{
			//Prend le nom du fichier et le met dans une String
			String nomFichier = fc.getSelectedFile().getName();
			//Pour voir si tout fonctionne bien de la console
			System.out.println(nomFichier);
			//Appel la fonction C++ qui se charge de charger le fichier XML
			InterfaceJava.fctC_viderArbre();
			InterfaceJava.fctC_chargerXml(nomFichier);
			InterfaceJava.fctC_effacerFichierXml("CurrentMap.xml");
			InterfaceJava.fctC_enregistrerXml("CurrentMap.xml",2);
			InterfaceJava.fctC_obtenirNomMap(nomFichier);
			sauvegarde_ = true;
			nomFichierXml_ = nomFichier;
		}
		else if(valeurRetour == JFileChooser.CANCEL_OPTION)
		{
			//Pour voir ce qui se passe de la console
			System.out.println(JFileChooser.CANCEL_OPTION);
		}
		
	}	    

	/**
	 * Fonction appelée lorsque l'élément Enregistrer du menu est actionné.
	 */
	public void Enregistrer() 
	{
		if(sauvegarde_ == false)
		{
			System.out.println("L'élément Enregistrer a été activé.");

			par = instance_.boiteDialogueTexte("Votre trou est un par combien (de 1 à 9)", "Par du trou?");
			try{
				nbPar = Integer.parseInt(par);

				while(nbPar < 1 || nbPar > 10){
					par = instance_.boiteDialogueTexte("Votre trou est un par combien (de 1 à 9)", "Par du trou?");
					nbPar = Integer.parseInt(par);
				}
			}
			catch (NumberFormatException nfe){
				//System.out.println("Erreur format du par.");
				if(par != null)
					JOptionPane.showMessageDialog(null,"Le format dpar doit être un nombre.", "Erreur", JOptionPane.WARNING_MESSAGE);
				return;
			}

			JFileChooser fc = new JFileChooser(".");
			FiltreXml filtre = new FiltreXml();
			fc.setFileFilter(filtre);
			int valeurRetour = fc.showSaveDialog(null);
			if(valeurRetour == JFileChooser.APPROVE_OPTION)
			{
				String nomFichier = fc.getSelectedFile().getName();

				int i = nomFichier.lastIndexOf('.');

				if(i>0 && i<nomFichier.length() - 1)
				{
					if (!nomFichier.substring(i+1).toLowerCase().equals("xml"))
					{
						nomFichier = nomFichier + ".xml";
					}
				}
				else if(i == -1)
				{
					nomFichier = nomFichier + ".xml";
				}
				
				if(nomFichier.matches(".*[ ].*"))
				{
					nomFichier= nomFichier.replaceAll("\\s+", "_");
				}
				
				System.out.println(nomFichier);
				//Met une variable à vrai pour dire que le fichier a déjà été sauvegarder et que l'on n'a pas
				//à redemander où enregistrer
				sauvegarde_ = true;
				nomFichierXml_ = nomFichier;
				InterfaceJava.fctC_effacerFichierXml(nomFichier);
				if (InterfaceJava.fctC_enregistrerXml(nomFichier,nbPar) == false)
				{
					JOptionPane.showMessageDialog(InterfaceJava.fenetreGeneral_, "Le terrain doit avoir une balle, un trou et une bordure!", "Attention!", JOptionPane.WARNING_MESSAGE);
				}
			}
			else if(valeurRetour == JFileChooser.CANCEL_OPTION)
			{
				System.out.println(JFileChooser.CANCEL_OPTION);
			}
		}
		//SI le fichier a déjà été sauvegardé
		else
		{
			InterfaceJava.fctC_enregistrerXml(nomFichierXml_,nbPar);
		}
	}	    

	/**
	 * Fonction appelée lorsque l'élément Enregistrer Sous du menu est actionné dans le mode jeu.
	 */
	public void EnregistrerSousTournois() 
	{
		//TODO
	}	    

	/**
	 * Fonction appelée lorsque l'élément Enregistrer du menu est actionné dans le mode jeu.
	 */
	public void EnregistrerTournois() 
	{
	
		InterfaceJava.fctC_sauvegarderMultijoueur(nomFichierXml_);
	}	  

	/**
	 * Fonction appelée lorsque l'élément Ouvrir du menu est actionné dans le mode jeu.
	 */
	public void OuvrirTournois() 
	{
		JFileChooser fc = new JFileChooser(".");
		//Ajoute un filtre pour n'afficher que les fichiers XML
		FiltreXml filtre = new FiltreXml();	
		fc.setFileFilter(filtre);
		int valeurRetour = fc.showOpenDialog(null);
		//Si l'utilisateur choisi un fichier
		if(valeurRetour == JFileChooser.APPROVE_OPTION)
		{
			//Prend le nom du fichier et le met dans une String
			String nomTournoi_ = fc.getSelectedFile().getName();

			InterfaceJava.fctC_obtenirNomsParcours(nomTournoi_);
			for(int i=0; i<9; i++)
			{
				// tournoi_.maps[i] = mapTournoi[i];
			}
		}

	}	    

	/**
	 * Fonction appelée lorsque l'élément Enregistrer Sous du menu est actionné.
	 */
	public void EnregistrerSous() 
	{
		System.out.println("L'élément Enregistrer Sous a été activé.");


		par = instance_.boiteDialogueTexte("Votre trou est un par de combien de coups (de 1 à 9)", "Par du trou?");
		try{
			nbPar = Integer.parseInt(par);

			while(nbPar < 1 || nbPar > 10){
				par = instance_.boiteDialogueTexte("Votre trou est un par de combien de coups (de 1 à 9)", "Par du trou?");
				nbPar = Integer.parseInt(par);
			}
		}
		catch (NumberFormatException nfe){
			//System.out.println("Erreur format du par.");
			if(par != null)
				JOptionPane.showMessageDialog(null,"Le format dpar doit être un nombre.", "Erreur", JOptionPane.WARNING_MESSAGE);
			return;
		}

		JFileChooser fc = new JFileChooser(".");
		FiltreXml filtre = new FiltreXml();
		fc.setFileFilter(filtre);
		int valeurRetour = fc.showSaveDialog(null);
		if(valeurRetour == JFileChooser.APPROVE_OPTION)
		{
			String nomFichier = fc.getSelectedFile().getName();

			int i = nomFichier.lastIndexOf('.');

			if(i>0 && i<nomFichier.length() - 1)
			{
				if (!nomFichier.substring(i+1).toLowerCase().equals("xml"))
				{
					nomFichier = nomFichier + ".xml";
				}
			}
			else if(i == -1)
			{
				nomFichier = nomFichier + ".xml";
			}
			
			if(nomFichier.matches(".*[ ].*"))
			{
				nomFichier= nomFichier.replaceAll("\\s+", "_");
			}
			System.out.println(nomFichier);
			sauvegarde_ = true;
			nomFichierXml_ = nomFichier;


			InterfaceJava.fctC_effacerFichierXml(nomFichier);
			InterfaceJava.fctC_enregistrerXml(nomFichier,nbPar);
		}
		else if(valeurRetour == JFileChooser.CANCEL_OPTION)
		{
			System.out.println(JFileChooser.CANCEL_OPTION);
		}
	}	     

	/**
	 * Fonction appelée lorsque l'élément Quitter du menu est actionné.
	 */
	public void Quitter() 
	{
		System.out.println("L'élément Quitter a été activé.");
		int choix = boiteDialogueChoix("Êtes-vous certain de vouloir quitter?" + '\n' + "Tous les changements non sauvegardés seronts perdus.", "Quitter?");
		if(choix != 1)
		{
			System.exit(0);
		}
	}

	/**
	 * Fonction appelée lorsque l'élément Ajouter du menu est actionné.
	 */
	public void Ajouter() 
	{
		System.out.println("L'élément Ajouter a été activé.");
	}	 

	/**
	 * Fonction appelée lorsque l'élément Selection/Edition du menu est actionné.
	 */
	public void SelectionEdition() 
	{
		System.out.println("L'élément Selection/Edition a été activé.");
		//DÉsactive les autres boutons d'options concernants les options de la souris
		boutonZoomElastique.setSelected(false);
		boutonZoomSouris.setSelected(false);

		if (active == false) //si selection ou selection rectangle n'est pas activé
		{
			etatSouris = EtatSouris.ES_selectionner;
			boutonSelection.setSelected(true);
			active = true;
		}
		else
		{
			etatSouris = EtatSouris.ES_aucun;
			InterfaceJava.fctC_viderSelection();
			active = false;
		}
	}    

	/**
	 * Fonction appelée lorsque l'élément Configurations du menu est actionné.
	 */
	public void Config() 
	{
		System.out.println("L'élément Configuraiton a été activé.");
		new Option().setVisible(true);
	}    

	/**
	 * Fonction appelée lorsque l'élément Dupliquer du menu est actionné.
	 */
	public void Dupliquer() 
	{
		System.out.println("L'élément Dupliquer a été activé.");
		InterfaceJava.fctC_duplicationSelection();
	}    

	/**
	 * Fonction appelée lorsque l'élément Effacer du menu est actionné.
	 */
	public void Effacer() 
	{
		System.out.println("L'élément Effacer a été activé.");
		InterfaceJava.fctC_deleteSelection();
	}   

	/**
	 * Fonction appelée lorsque l'élément Deplacer du menu est actionné.
	 */
	public void Deplacer() 
	{
		System.out.println("L'élément Deplacer a été activé.");
		etatSouris = EtatSouris.Es_deplacerSelect;
	}    

	/**
	 * Fonction appelée lorsque l'élément Tourner du menu est actionné.
	 */
	public void Tourner() 
	{
		System.out.println("L'élément Tourner a été activé.");
		String chaine = boiteDialogueTexte("De combien de degrés voulez vous tourner la sélection?" , "Rotation");
		if(chaine != null)
		{	
			float angle = Integer.parseInt(chaine);
			InterfaceJava.fctC_rotationSelection(angle);   
		}
		else
			return;
	}   

	/**
	 * Fonction appelée lorsque l'élément Taille du menu est actionné.
	 */
	public void Taille() 
	{
		System.out.println("L'élément Taille a été activé.");
		String chaine = boiteDialogueTexte("Quel facteur d'agrandissement voulez vous appliquer à la sélection?" + '\n' + "Doit être entre 1 et 10 pour aggrandir la sélection" + '\n' + "ou entre -1 et -10 pour rapetisser la sélection" , "Facteur d'agrandissement");
		if(chaine != null)
		{
			float taille = Integer.parseInt(chaine);
			if(taille >= 1 || taille <= 10) // si taille entre 1 et 10
			{
				InterfaceJava.fctC_facteurSelection(taille);
			}
			else if(taille <= (-1) || taille >= (-10)) // si taille entre -1 et -10
			{
			}
			else
			{
				Taille();

			}
		}
		else
			return;	   
	}    
	
	/**
	 * Fonction appelée lorsque l'élément EffacerListeJoueurs du menu est actionné
	 * Efface la liste de joueur
	 */
	public void EffacerListeJoueurs()
	{
		System.out.println("L'élément EffacerListeJoueurs a été activé.");
		InterfaceJava.fctC_effacerFichierJoueur();
	}

	/**
	 * Fonction appelée lorsque l'élément Edition du menu est actionné.
	 */
	public void Edition() 
	{
		System.out.println("L'élément Edition a été activé.");

		if(InterfaceJava.mode_ != "Editeur")
		{
			int choix = boiteDialogueChoix("Êtes-vous certain de vouloir quitter le mode jeu?" + '\n' + "Tous les changements non sauvegardés seronts perdus.", "Quitter mode jeu?");

			if(choix == 0)
			{

				InterfaceJava.mode_ = "Editeur";
				boutonModeJeu.setSelected(false);
				boutonModeEdition.setSelected(true);
				InterfaceJava.fctC_changerMode(false); // le mode est édition
				if(vue_ == true)
				{
					//InterfaceJava.fctC_changerVue();
					vue_ = false;
				}
				InterfaceJava.fctC_viderArbre();
				//InterfaceJava.fctC_chargerXml("CurrentMap.xml"); // si current map existe pas a cause de p. rapide
				InterfaceJava.fctC_chargerXml(instance_.nomFichierXml_);
				nomFichierXml_ = "CurrentMap.xml";
				InterfaceJava.fctC_obtenirNomMap(nomFichierXml_);
				boutonSelection.setVisible(true);
				barreEdition.setVisible(true);
				menuEdition.setVisible(true);
				boutonDupliquer.setVisible(true);
				boutonEffacer.setVisible(true);
				boutonRedimentionner.setVisible(true);
				boutonTourner.setVisible(true);
				barreStatus.setVisible(true);
				boutonDeplacer.setVisible(true);
				boutonOuvrirTournois.setVisible(false);
				boutonOuvrir.setVisible(true);
				boutonSauvegarderTournois.setVisible(false);
				boutonSauvegarder.setVisible(true);
				boutonRecommencer.setVisible(false);
				boutonReplay.setVisible(false);
				boutonJouerMusique.setVisible(false);
				boutonStopMusique.setVisible(false);
				boutonJouerPrecedent.setVisible(false);
				boutonJouerSuivant.setVisible(false);
				boutonZoomElastique.setVisible(true);
				boutonZoomSouris.setVisible(true);
				elementNouveau.setVisible(true);
				boutonVue.setVisible(false);
				elementOrbite.setEnabled(false);
				elementCiel.setEnabled(false);
				elementOrthogonale.setEnabled(true);
				boutonPointage.setVisible(false);

				if(InterfaceJava.fctC_getTypeVue() == 2 || InterfaceJava.fctC_getTypeVue() == 3 )
					Libre();

				etat_ = new ContexteEtat();
				etat_.choixEtat(new EtatEditeur());
				etat_.ajouterGestionnaires(instance_);

			}
			else
			{
				boutonModeEdition.setSelected(false);
			}

		}

	}   

	/**
	 * Fonction appelée lorsque l'élément Jeu du menu est actionné.
	 */
	public void Jeu() 
	{

		System.out.println("L'élément Jeu a été activé.");

		if(InterfaceJava.mode_ != "Jeu")
		{
			int choix = boiteDialogueChoix("Êtes-vous certain de vouloir quitter le mode édition?" + '\n' + "Tous les changements non sauvegardés seronts perdus.", "Quitter mode édition?");

			if(choix == 0)
			{
				InterfaceJava.fctC_effacerFichierXml("CurrentMap.xml");
				if (InterfaceJava.fctC_enregistrerXml("CurrentMap.xml",0) == false)
				{
					JOptionPane.showMessageDialog(InterfaceJava.fenetreGeneral_, "Le terrain doit avoir une balle, un trou et une bordure!", "Attention!", JOptionPane.WARNING_MESSAGE);
				}
				else
				{	
					jouerEdition = true;
					InterfaceJava.mode_ = "Jeu";
					boutonModeJeu.setSelected(true);
					boutonModeEdition.setSelected(false);
					InterfaceJava.fctC_changerMode(true); // le mode est jeu
					if(vue_ == false)
					{
						//if(InterfaceJava.fctC_getTypeVue() == 4)
						//   InterfaceJava.fctC_changerVue(4);
						vue_ = true;
					}
					InterfaceJava.fctC_viderArbre();
					InterfaceJava.fctC_chargerXml("CurrentMap.xml");
					nomFichierXml_ = "CurrentMap.xml";
					InterfaceJava.fctC_obtenirNomMap(nomFichierXml_);
					InterfaceJava.fctC_obtenirNomJoueur("test");
					boutonSelection.setVisible(false);
					barreEdition.setVisible(false);
					menuEdition.setVisible(false);
					boutonDupliquer.setVisible(false);
					boutonEffacer.setVisible(false);
					boutonRedimentionner.setVisible(false);
					boutonTourner.setVisible(false);
					boutonDeplacer.setVisible(false);
					boutonOuvrirTournois.setVisible(false);
					boutonOuvrir.setVisible(true);
					boutonSauvegarderTournois.setVisible(true);
					boutonSauvegarder.setVisible(false);
					barreStatus.setVisible(false);
					boutonRecommencer.setVisible(true);
					boutonReplay.setVisible(true);
					boutonJouerMusique.setVisible(true);
					boutonStopMusique.setVisible(true);
					boutonJouerPrecedent.setVisible(true);
					boutonJouerSuivant.setVisible(true);
					boutonZoomElastique.setVisible(false);
					boutonZoomSouris.setVisible(false);
					elementNouveau.setVisible(false);
					boutonVue.setVisible(false);
					elementOrbite.setEnabled(true);
					elementCiel.setEnabled(true);
					elementOrthogonale.setEnabled(false);
					//boutonPointage.setVisible(true);

					if(InterfaceJava.fctC_getTypeVue() == 4 || InterfaceJava.fctC_getTypeVue() == 1)
						Ciel();

					etat_ = new ContexteEtat();
					etat_.choixEtat(new EtatJeu());
					etat_.ajouterGestionnaires(instance_);
				}
			}
			else
			{
				boutonModeJeu.setSelected(false);
			}

		}

	} 

	/**
	 * Fonction appelée lorsque l'élément Auteurs du menu est actionné.
	 */
	public void Auteurs() 
	{
		System.out.println("L'élément Auteurs a été activé.");
		String auteurs = 
				"Aiman Badr Jaouhar -  Matricule 1488723" + '\n' +
				"Ashley Manraj             -  Matricule 1417566" + '\n' +
				"Etienne Vallée             -  Matricule 1433586" + '\n' +
				"Jean-Luc Dubeau      -  Matricule 1486091" + '\n' +
				"Julien Lapointe           -   Matricule 1478834" + '\n' +
				"Mohammed Benbachir - Matricule 1484785";
		JOptionPane.showMessageDialog(null, auteurs, "Auteurs", JOptionPane.INFORMATION_MESSAGE);
	}  

	/**
	 * Fonction appelée lorsque l'élément Propos du menu est actionné.
	 */
	public void Propos() 
	{
		System.out.println("L'élément Propos a été activé.");
		String propos = "Angry Balls" + '\n' + "Automne 2011" + '\n' + "Réalisé dans le cadre du cours INF2990" + '\n' +
				"École Polytechnique de Montréal";
		JOptionPane.showMessageDialog(null, propos, "À Propos", JOptionPane.INFORMATION_MESSAGE);
	}  

	/**
	 * Fonction appelée lorsque l'élément Vue du menu est actionné.
	 */
	public void Vue() 
	{
		System.out.println("L'élément Vue a été activé.");
		if(vue_ == true)
		{
			vue_ = false;
		}
		else
		{
			vue_ = true;
		}
		//InterfaceJava.fctC_changerVue();
		InterfaceJava.fctC_redimensionnerFenetre(InterfaceJava.canvas_.getWidth(), InterfaceJava.canvas_.getHeight());
	}  

	/**
	 * Fonction appelée lorsque l'élément Vue Libre du menu est actionné.
	 */
	public void Libre()
	{
		System.out.println("L'élément Libre a été activé.");
		InterfaceJava.fctC_changerVue(1);
		InterfaceJava.fctC_redimensionnerFenetre(InterfaceJava.canvas_.getWidth(), InterfaceJava.canvas_.getHeight());
		elementLibre.setSelected(true);
		elementOrbite.setSelected(false);
		elementCiel.setSelected(false);
		elementOrthogonale.setSelected(false);
	}

	/**
	 * Fonction appelée lorsque l'élément Vue Orbite du menu est actionné.
	 */
	public void Orbite()
	{
		System.out.println("L'élément Orbite a été activé.");
		InterfaceJava.fctC_changerVue(2);
		elementOrbite.setSelected(true);
		elementLibre.setSelected(false);
		elementCiel.setSelected(false);
		elementOrthogonale.setSelected(false);

		InterfaceJava.fctC_redimensionnerFenetre(InterfaceJava.canvas_.getWidth(), InterfaceJava.canvas_.getHeight());
	}

	/**
	 * Fonction appelée lorsque l'élément Vue Ciel du menu est actionné.
	 */
	public void Ciel()
	{
		System.out.println("L'élément Ciel a été activé.");
		InterfaceJava.fctC_changerVue(3);
		elementCiel.setSelected(true);
		elementOrbite.setSelected(false);
		elementLibre.setSelected(false);
		elementOrthogonale.setSelected(false);

		InterfaceJava.fctC_redimensionnerFenetre(InterfaceJava.canvas_.getWidth(), InterfaceJava.canvas_.getHeight());
	}

	/**
	 * Fonction appelée lorsque l'élément Vue Orthogonale du menu est actionné.
	 */
	public void Orthogonale()
	{
		System.out.println("L'élément Orthogonale a été activé.");
		InterfaceJava.fctC_changerVue(4);
		InterfaceJava.fctC_redimensionnerFenetre(InterfaceJava.canvas_.getWidth(), InterfaceJava.canvas_.getHeight());
		elementOrthogonale.setSelected(true);
		elementOrbite.setSelected(false);
		elementLibre.setSelected(false);
		elementCiel.setSelected(false);
	}

	/**
	 * Fonction appelée lorsque l'élément Aide de la barre d'outils est actionné.
	 */
	public void AideBarre() 
	{
		System.out.println("Le bouton Aide a été activé.");
		String aide = "Pour ajouter un objet avec la barre d'outil," + '\n'  +
				"il suffit de cliquer sur l'image et de cliquer de " + '\n'  +
				"nouveau sur le terrain à l'endroit désiré.";
		JOptionPane.showMessageDialog(null, aide, "À Propos", JOptionPane.INFORMATION_MESSAGE);
	}  

	/**
	 * Fonction appelée lorsque l'élément Recommencer du menu est actionné.
	 */
	public void Recommencer() 
	{
		System.out.println("Le bouton Recommencer a été activé.");
		InterfaceJava.fctC_viderArbre();
		InterfaceJava.fctC_chargerXml(nomFichierXml_);
	} 
	
	/**
	 * Fonction appelée lorsque l'élément Replay du menu est actionné.
	 */
	public void Replay() 
	{
		System.out.println("Le bouton Replay a été activé.");
		//InterfaceJava.fctC_viderArbre();
		if(InterfaceJava.getJoueurCourant() == 1){
			if(MenuDeBase.getInstance().nomJoueur != null)
				InterfaceJava.fctC_chargerMultijoueur(MenuDeBase.getInstance().nomJoueur);
			else
				InterfaceJava.fctC_chargerMultijoueur("test");
		}
		else{
			if(MenuDeBase.getInstance().nomJoueur2 != null)
				InterfaceJava.fctC_chargerMultijoueur(MenuDeBase.getInstance().nomJoueur2);
			else
				InterfaceJava.fctC_chargerMultijoueur("test");
		}
	} 

	/**
	 * Fonction appelée lorsque l'élément JouerMusique du menu est actionné.
	 */
	public void JouerMusique() 
	{
		System.out.println("Le bouton JouerMusique a été activé.");
		InterfaceJava.fctC_play();
	} 

	/**
	 * Fonction appelée lorsque l'élément StopMusique du menu est actionné.
	 */
	public void StopMusique() 
	{
		System.out.println("Le bouton StopMusique a été activé.");
		InterfaceJava.fctC_stop();
	} 

	/**
	 * Fonction appelée lorsque l'élément JouerPrecedent du menu est actionné.
	 */
	public void JouerPrecedent() 
	{
		System.out.println("Le bouton JouerPrecedent a été activé.");
		InterfaceJava.fctC_musiquePrecedente();
	} 

	/**
	 * Fonction appelée lorsque l'élément JouerSuivant du menu est actionné.
	 */
	public void JouerSuivant() 
	{
		System.out.println("Le bouton JouerSuivant a été activé.");
		InterfaceJava.fctC_musiqueSuivante();
	} 

	/**
	 * Fonction appelée lorsque l'élément BaisserMusique du menu est actionné.
	 */
	public void BaisserMusique() 
	{
		System.out.println("Le bouton BaisserMusique a été activé.");
		InterfaceJava.fctC_ajusterVolumeMusique((float)2.0);
	} 

	/**
	 * Fonction appelée lorsque l'élément MonterMusique du menu est actionné.
	 */
	public void MonterMusique() 
	{
		System.out.println("Le bouton MonterMusique a été activé.");
		InterfaceJava.fctC_ajusterVolumeMusique((float)3.0);
	} 

	/**
	 * Fonction appelée lorsque l'élément BaisserSon du menu est actionné.
	 */
	public void BaisserSon() 
	{
		System.out.println("Le bouton BaisserSon a été activé.");
		InterfaceJava.fctC_ajusterVolumeSon((float)2.0);
	} 

	/**
	 * Fonction appelée lorsque l'élément MonterSon du menu est actionné.
	 */
	public void MonterSon() 
	{
		System.out.println("Le bouton MonterSon a été activé.");
		InterfaceJava.fctC_ajusterVolumeSon((float)3.0);
	} 

	/**
	 * Fonction appelée lorsque l'élément ChangerVolumes du menu est actionné.
	 */
	public void ChangerVolumes() 
	{
		System.out.println("Le bouton ChangerVolumes a été activé.");
		volume_ = new Volume();
		volume_.setVisible(true);
		volume_.DialogVolume(InterfaceJava.fenetreGeneral_, volumeSon_, volumeMusique);   
	} 

	/**
	 * Fonction appelée lorsque l'élément Mute du menu est actionné.
	 */
	public void Mute()
	{
		System.out.println("Le bouton Mute a été activé.");
		InterfaceJava.fctC_mute();
	}

	/**
	 * Fonction appelée lorsque l'élément Bonus du menu est actionné.
	 */
	public void Bonus() 
	{
		System.out.println("Le menu Bonus a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_bonus;
		InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_bonus.ordinal(), InterfaceJava.canvas_.getWidth()/2 , InterfaceJava.canvas_.getHeight()/2, 0, 0);
	}  

	/**
	 * Fonction appelée lorsque l'élément Bonus de la barre d'outils est actionné.
	 */
	public void BonusBarre() 
	{
		System.out.println("Le bouton Bonus a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_bonus;
		etatSouris = EtatSouris.ES_placer;
	}  

	/**
	 * Fonction appelée lorsque l'élément Sable du menu est actionné.
	 */
	public void Sable() 
	{
		System.out.println("Le bouton Sable a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_sable;
		InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_sable.ordinal(), InterfaceJava.canvas_.getWidth()/2 , InterfaceJava.canvas_.getHeight()/2, 0, 0);  
	}  

	/**
	 * Fonction appelée lorsque l'élément Sable de la barre d'outils est actionné.
	 */
	public void SableBarre() 
	{
		System.out.println("Le bouton Sable a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_sable;
		etatSouris = EtatSouris.ES_placer;
	}  

	/**
	 * Fonction appelée lorsque l'élément Eau du menu est actionné.
	 */
	public void Eau() 
	{
		System.out.println("Le bouton Eau a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_eau;
		InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_eau.ordinal(), InterfaceJava.canvas_.getWidth()/2 , InterfaceJava.canvas_.getHeight()/2, 0, 0);  
	}  

	/**
	 * Fonction appelée lorsque l'élément Eau de la barre d'outils est actionné.
	 */
	public void EauBarre() 
	{
		System.out.println("Le bouton Eau a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_eau;
		etatSouris = EtatSouris.ES_placer;
	}  

	/**
	 * Fonction appelée lorsque l'élément Mur du menu est actionné.
	 */
	public void Mur() 
	{
		System.out.println("Le bouton Mur a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_mur;
		InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_mur.ordinal(), 273 , 262, 300,300);   
	} 

	/**
	 * Fonction appelée lorsque l'élément Contour du menu est actionné.
	 */
	public void Contour() 
	{
		System.out.println("Le bouton Contour a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_contour;
		InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_contour.ordinal(), 273 , 262, 300,300);   
	} 

	/**
	 * Fonction appelée lorsque l'élément ContourBarre de la barre d'outils est actionné.
	 */
	public void ContourBarre() 
	{
		System.out.println("Le bouton ContourBarre a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_contour;
		etatSouris = EtatSouris.ES_placer;
	}  

	/**
	 * Fonction appelée lorsque l'élément Mur de la barre d'outils est actionné.
	 */
	public void MurBarre() 
	{
		System.out.println("Le bouton Mur a été activé.");
		etatEditeur_.setPlacer(false);
		etatSourisObjets = EtatSourisObjets.ESO_mur;
		etatSouris = EtatSouris.ES_placer;
	}  

	/**
	 * Fonction appelée lorsque l'élément Trou du menu est actionné.
	 */
	public void Trou() 
	{
		System.out.println("Le bouton Trou a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_trou;
		InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_trou.ordinal(), InterfaceJava.canvas_.getWidth()/2 , InterfaceJava.canvas_.getHeight()/2, 0, 0);    
	}  

	/**
	 * Fonction appelée lorsque l'élément TrouBarre de la barre d'outils est actionné.
	 */
	public void TrouBarre() 
	{
		System.out.println("Le bouton TrouBarre a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_trou;
		etatSouris = EtatSouris.ES_placer;
	}  

	/**
	 * Fonction appelée lorsque l'élément Balle du menu est actionné.
	 */
	public void Balle() 
	{
		System.out.println("Le bouton Balle a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_balle;
		InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_balle.ordinal(), InterfaceJava.canvas_.getWidth()/2 , InterfaceJava.canvas_.getHeight()/2, 0, 0);
	}  

	/**
	 * Fonction appelée lorsque l'élément Balle de la barre d'outils est actionné.
	 */
	public void BalleBarre() 
	{
		System.out.println("Le bouton Balle a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_balle;
		etatSouris = EtatSouris.ES_placer;
	}  

	/**
	 * Fonction appelée lorsque l'élément Portail du menu est actionné.
	 */
	public void Portail() 
	{
		System.out.println("Le bouton Portail a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_portal;
		etatSouris = EtatSouris.ES_placer;   
	}  

	/**
	 * Fonction appelée lorsque l'élément PortailBarre de la barre d'outils est actionné.
	 */
	public void PortailBarre() 
	{
		System.out.println("Le bouton PortailBarre a été activé.");
		etatSourisObjets = EtatSourisObjets.ESO_portal;
		InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_portal.ordinal(), InterfaceJava.canvas_.getWidth()/2 , InterfaceJava.canvas_.getHeight()/2, 0, 0);
	}  

	/**
	 * Fonction appelée lorsque l'élément ZoomIn de la barre d'outils est actionné.
	 */
	public void ZoomIn() 
	{
		System.out.println("Le bouton ZoomIn a été activé.");
		InterfaceJava.fctC_zoomIn(0);
	}  

	/**
	 * Fonction appelée lorsque l'élément ZoomOut de la barre d'outils est actionné.
	 */
	public void ZoomOut() 
	{
		System.out.println("Le bouton ZoomOut a été activé.");
		InterfaceJava.fctC_zoomOut(0);
	}  

	/**
	 * Fonction appelée lorsque l'élément ZoomElastique de la barre d'outils est actionné.
	 */
	public void ZoomElastique() 
	{
		System.out.println("Le bouton ZoomElastique a été activé.");
		if (etatSouris.ordinal() != 1) //si le zommElastique n'est pas activé
		{
			etatSouris = EtatSouris.ES_zoomElastique;
			boutonZoomElastique.setSelected(true);
			boutonSelection.setSelected(false);
			boutonZoomSouris.setSelected(false);
		}
		else
		{
			etatSouris = EtatSouris.ES_aucun;
			boutonZoomElastique.setSelected(false);
		}
	}  

	/**
	 * Fonction appelée lorsque l'élément Zoom Souris de la barre d'outils est actionné.
	 */
	public void ZoomSouris() 
	{
		boutonSelection.setSelected(false);
		boutonZoomElastique.setSelected(false);

		System.out.println("Le bouton ZoomSouris a été activé.");
		if (etatSouris.ordinal() != 1) //si le ZoomSouris n'est pas activé
		{
			etatSouris = EtatSouris.ES_zoomSouris;
			boutonZoomSouris.setSelected(true);
		}
		else
		{
			etatSouris = EtatSouris.ES_aucun;
			boutonZoomSouris.setSelected(false);
		}
	}

	/**
	 * Fonction appelée lorsque l'élément ModeEdition de la barre d'outils est actionné.
	 */
	public void ModeEdition() 
	{
		System.out.println("Le bouton ModeEdition a été activé.");
		InterfaceJava.mode_ = "Editeur";
		boutonModeJeu.setSelected(false);
	}  

	/**
	 * Fonction appelée lorsque l'élément ModeJeu de la barre d'outils est actionné.
	 */
	public void ModeJeu() 
	{
		System.out.println("Le bouton ModeJeu a été activé.");
		InterfaceJava.mode_ = "Jeu";
		boutonModeEdition.setSelected(false);
	}  

	/**
	 * Fonction appelée lorsque l'élément Menu du menu Fichier est actionné.
	 */
	public void Menu() 
	{
		System.out.println("Le menu RetourMenu a été activé.");
		int choix = boiteDialogueChoix("Êtes-vous certain de vouloir quitter?" + '\n' + "Tous les changements non sauvegardés seronts perdus.", "Retour au menu principal?");
		if(choix != 1)
		{
			menuDeBase_.setVisible(true);
			InterfaceJava.fctC_stop();
			InterfaceJava.fctC_musiqueMenu(1);
			InterfaceJava.fenetreGeneral_.setVisible(false);
			InterfaceJava.fctC_viderArbre();
			InterfaceJava.fctC_changerMode(false);
			InterfaceJava.fctC_musiqueMenu(1);
		}
	}  

	/**
	 * Fonction appelée lorsque l'élément Pointage de la barre d'outils est actionné.
	 */
	public void Pointage() 
	{
		System.out.println("Le bouton Pointage a été activé.");
		pointage_ = new Pointage();
		pointage_.setVisible(true);
		pointage_.initiationTableauPointage();
	}  

	//Fin des fonctions de gestion d'évènements

	/**
	 * Fonction qui construit la barre de menus
	 */
	public void creerMenu()
	{
		// Création de la barre de menus.
		JMenuBar barre = new JMenuBar();

		//Menu Fichier
		menuFichier = new JMenu("Fichier");
		// On s'assure que les menus apparaîtront par-dessus l'OpenGL
		menuFichier.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mnémonique.
		menuFichier.setMnemonic('F');
		// Gestionnaire des menus.
		Gestionnaire gestionnaire = new Gestionnaire(this);

		//Menu Edition
		menuEdition = new JMenu("Edition");
		// On s'assure que les menus apparaîtront par-dessus l'OpenGL
		menuEdition.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mnémonique.
		menuEdition.setMnemonic('E');
		Gestionnaire gestionnaireEdition = new Gestionnaire(this);

		//Menu Mode
		menuMode = new JMenu("Mode");
		// On s'assure que les menus apparaîtront par-dessus l'OpenGL
		menuMode.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mnémonique.
		menuMode.setMnemonic('M');		
		Gestionnaire gestionnaireMode = new Gestionnaire(this);

		//Menu Aide
		JMenu menuAide = new JMenu("Aide");
		// On s'assure que les menus apparaîtront par-dessus l'OpenGL
		menuAide.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mnémonique.
		menuAide.setMnemonic('A');		
		Gestionnaire gestionnaireAide = new Gestionnaire(this);

		//Menu Vue
		JMenu menuVue = new JMenu(" Vue ");
		// On s'assure que les menus apparaîtront par-dessus l'OpenGL
		menuVue.getPopupMenu().setLightWeightPopupEnabled(false);
		// On assigne un mnémonique.
		menuAide.setMnemonic('V');		
		Gestionnaire gestionnaireVue = new Gestionnaire(this);

		//Menu Musique
		JMenu menuMusique = new JMenu(" Musique ");
		// On s'assure que les menus apparaîtront par-dessus l'OpenGL
		menuVue.getPopupMenu().setLightWeightPopupEnabled(false);
		menuAide.setMnemonic('u');	
		Gestionnaire gestionnaireMusique = new Gestionnaire(this);


		/////////////////////////////////////////
		//Création des éléments du menu Fichier//
		/////////////////////////////////////////

		//Nouveau
		elementNouveau = new JMenuItem("Nouveau");
		elementNouveau.setMnemonic('N');
		elementNouveau.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/file.png")));
		elementNouveau.setAccelerator(KeyStroke.getKeyStroke("ctrl N"));
		elementNouveau.setActionCommand("Nouveau");
		elementNouveau.addActionListener(gestionnaire);

		//Ouvrir
		JMenuItem elementOuvrir = new JMenuItem("Ouvrir");
		elementOuvrir.setMnemonic('O');
		elementOuvrir.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/folder-horizontal-open.png")));
		elementOuvrir.setAccelerator(KeyStroke.getKeyStroke("ctrl O"));
		elementOuvrir.setActionCommand("Ouvrir");
		elementOuvrir.addActionListener(gestionnaire);

		//Enregistrer
		JMenuItem elementEnregistrer = new JMenuItem("Enregistrer");
		elementEnregistrer.setMnemonic('S');
		elementEnregistrer.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/disk-black.png")));
		elementEnregistrer.setAccelerator(KeyStroke.getKeyStroke("ctrl S"));
		elementEnregistrer.setActionCommand("Enregistrer");
		elementEnregistrer.addActionListener(gestionnaire);

		//Enregistrer Sous
		JMenuItem elementEnregistrerSous = new JMenuItem("Enregistrer Sous");
		elementEnregistrerSous.setMnemonic('E');
		elementEnregistrerSous.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/disks-black.png")));
		//elementEnregistrerSous.setAccelerator(KeyStroke.getKeyStroke("ctrl O"));
		elementEnregistrerSous.setActionCommand("EnregistrerSous");
		elementEnregistrerSous.addActionListener(gestionnaire);

		//Quitter
		JMenuItem elementQuitter = new JMenuItem("Quitter");
		elementQuitter.setMnemonic('Q');
		elementQuitter.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/cross-button.png")));
		elementQuitter.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
		elementQuitter.setActionCommand("Quitter");
		elementQuitter.addActionListener(gestionnaire);

		//Retour au menu
		JMenuItem elementMenu = new JMenuItem("Retour au menu");
		elementMenu.setMnemonic('H');
		elementMenu.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/home-arrow-icon-icon.png")));
		elementMenu.setActionCommand("Menu");
		elementMenu.addActionListener(gestionnaire);

		//Configuration
		JMenuItem elementConfiguration = new JMenuItem("Configurations");
		elementConfiguration.setMnemonic('C');
		elementConfiguration.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/configuration.png")));
		elementConfiguration.setActionCommand("Config");
		elementConfiguration.addActionListener(gestionnaire);

		/////////////////////////////////////////
		//Création des éléments du menu Edition//
		/////////////////////////////////////////

		//Ajouter
		JMenuItem elementAjouter = new JMenu("Ajouter");
		elementAjouter.setMnemonic('A');
		elementAjouter.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/action_add.png")));
		//elementAjouter.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));

		//Sous-Menu d'ajouter

		//Balle
		JMenuItem elementBalle = new JMenuItem("Balle");
		elementBalle.setMnemonic('B');
		// elementBalle.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/nouveau.png")));
		//elementBalle.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
		elementBalle.setActionCommand("Balle");
		elementBalle.addActionListener(gestionnaireEdition);
		elementAjouter.add(elementBalle);

		//Trou
		JMenuItem elementTrou = new JMenuItem("Trou");
		elementTrou.setMnemonic('T');
		// elementTrou.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/nouveau.png")));
		//elementTrou.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
		elementTrou.setActionCommand("Trou");
		elementTrou.addActionListener(gestionnaireEdition);
		elementAjouter.add(elementTrou);

		//Mur
		JMenuItem elementMur = new JMenuItem("Mur");
		elementMur.setMnemonic('M');
		// elementMur.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/nouveau.png")));
		//elementMur.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
		elementMur.setActionCommand("Mur");
		elementMur.addActionListener(gestionnaireEdition);
		elementAjouter.add(elementMur);

		//Eau
		JMenuItem elementEau = new JMenuItem("Eau");
		elementEau.setMnemonic('E');
		// elementEau.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/nouveau.png")));
		//elementEau.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
		elementEau.setActionCommand("Eau");
		elementEau.addActionListener(gestionnaireEdition);
		elementAjouter.add(elementEau);

		//Sable
		JMenuItem elementSable = new JMenuItem("Sable");
		elementSable.setMnemonic('S');
		// elementSable.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/nouveau.png")));
		//elementSable.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
		elementSable.setActionCommand("Sable");
		elementSable.addActionListener(gestionnaireEdition);
		elementAjouter.add(elementSable);

		//Bonus
		JMenuItem elementBonus = new JMenuItem("Bonus");
		elementBonus.setMnemonic('O');
		// elementBonus.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/nouveau.png")));
		//elementBonus.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
		elementBonus.setActionCommand("Bonus");
		elementBonus.addActionListener(gestionnaireEdition);
		elementAjouter.add(elementBonus);

		//Fin du sous-menu

		//Selection/Edition
		JMenuItem elementSelectionEdition = new JMenuItem("Sélection/Édition");
		elementSelectionEdition.setMnemonic('S');
		elementSelectionEdition.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/cursor.png")));
		elementSelectionEdition.setAccelerator(KeyStroke.getKeyStroke(toucheSelection));
		elementSelectionEdition.setActionCommand("SelectionEdition");
		elementSelectionEdition.addActionListener(gestionnaireEdition);

		//Dupliquer
		JMenuItem elementDupliquer = new JMenuItem("Dupliquer");
		elementDupliquer.setMnemonic('U');
		elementDupliquer.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/document-copy.png")));
		elementDupliquer.setAccelerator(KeyStroke.getKeyStroke("D"));
		elementDupliquer.setActionCommand("Dupliquer");
		elementDupliquer.addActionListener(gestionnaireEdition);

		//Effacer
		JMenuItem elementEffacer = new JMenuItem("Effacer");
		elementEffacer.setMnemonic('E');
		elementEffacer.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/action_remove.png")));
		elementEffacer.setAccelerator(KeyStroke.getKeyStroke("DELETE"));
		elementEffacer.setActionCommand("Effacer");
		elementEffacer.addActionListener(gestionnaireEdition);

		//Deplacer
		JMenuItem elementDeplacer = new JMenuItem("Déplacer");
		elementDeplacer.setMnemonic('P');
		elementDeplacer.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/arrow-move.png")));
		elementDeplacer.setAccelerator(KeyStroke.getKeyStroke("W"));
		elementDeplacer.setActionCommand("Deplacer");
		elementDeplacer.addActionListener(gestionnaireEdition);

		//Tourner
		JMenuItem elementTourner = new JMenuItem("Tourner");
		elementTourner.setMnemonic('T');
		elementTourner.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/arrow-circle-315-left.png")));
		elementTourner.setAccelerator(KeyStroke.getKeyStroke("T"));
		elementTourner.setActionCommand("Tourner");
		elementTourner.addActionListener(gestionnaireEdition);

		//Taille
		JMenuItem elementTaille = new JMenuItem("Redimensionner");
		elementTaille.setMnemonic('T');
		elementTaille.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/layer-resize.png")));
		elementTaille.setAccelerator(KeyStroke.getKeyStroke("R"));
		elementTaille.setActionCommand("Taille");
		elementTaille.addActionListener(gestionnaireEdition);
		
		//EffacerListeJoueurs
		JMenuItem elementEffacerListeJoueurs = new JMenuItem("EffacerListeJoueurs");
		elementEffacerListeJoueurs.setActionCommand("EffacerListeJoueurs");
		elementEffacerListeJoueurs.addActionListener(gestionnaireEdition);

		/////////////////////////////////////////
		//  Création des éléments du menu Mode //
		/////////////////////////////////////////

		//Edition
		JMenuItem elementEdition = new JMenuItem("Édition");
		elementEdition.setMnemonic('É');
		elementEdition.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/hammer.png")));
		elementEdition.setAccelerator(KeyStroke.getKeyStroke("E"));
		elementEdition.setActionCommand("Edition");
		elementEdition.addActionListener(gestionnaireMode);

		//Jeu
		JMenuItem elementJeu = new JMenuItem("Jeu");
		elementJeu.setMnemonic('J');
		elementJeu.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/game.png")));
		elementJeu.setAccelerator(KeyStroke.getKeyStroke("J"));
		elementJeu.setActionCommand("Jeu");
		elementJeu.addActionListener(gestionnaireMode);

		/////////////////////////////////////////
		//  Création des éléments du menu Aide //
		/////////////////////////////////////////

		//Auteurs
		JMenuItem elementAuteurs = new JMenuItem("Auteurs");
		elementAuteurs.setMnemonic('A');
		//elementAuteurs.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/nouveau.png")));
		//elementAuteurs.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
		elementAuteurs.setActionCommand("Auteurs");
		elementAuteurs.addActionListener(gestionnaireAide);

		//Propos
		JMenuItem elementPropos = new JMenuItem("À propos de ce logiciel.");
		elementPropos.setMnemonic('p');
		// elementPropos.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/nouveau.png")));
		//elementPropos.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
		elementPropos.setActionCommand("Propos");
		elementPropos.addActionListener(gestionnaireAide);


		/////////////////////////////////////////
		//  Création des éléments du menu Vue  //
		/////////////////////////////////////////

		//Libre
		elementLibre = new JMenuItem("Libre");
		elementLibre.setAccelerator(KeyStroke.getKeyStroke("1"));
		elementLibre.setActionCommand("Libre");
		elementLibre.addActionListener(gestionnaireVue);

		//Orbite
		elementOrbite = new JMenuItem("Orbite");
		elementOrbite.setEnabled(false);
		elementOrbite.setAccelerator(KeyStroke.getKeyStroke("2"));
		elementOrbite.setActionCommand("Orbite");
		elementOrbite.addActionListener(gestionnaireVue);

		//Ciel
		elementCiel = new JMenuItem("Ciel");
		elementCiel.setEnabled(false);
		elementCiel.setAccelerator(KeyStroke.getKeyStroke("3"));
		elementCiel.setActionCommand("Ciel");
		elementCiel.addActionListener(gestionnaireVue);

		//Orthogonale
		elementOrthogonale = new JMenuItem("Orthogonale");
		elementOrthogonale.setAccelerator(KeyStroke.getKeyStroke("4"));
		elementOrthogonale.setActionCommand("Orthogonale");
		elementOrthogonale.addActionListener(gestionnaireVue);

		///////////////////////////////////////////
		//  Création des éléments du menu Musique//
		///////////////////////////////////////////

		//ChangerVolumes
		JMenuItem elementChangerVolumes = new JMenuItem("Configuration des Volumes");
		elementChangerVolumes.setActionCommand("ChangerVolumes");
		elementChangerVolumes.addActionListener(gestionnaireMusique);

		//MonterMusique
		JMenuItem elementAugmenterMusique = new JMenuItem("+ Volume Musique");
		elementAugmenterMusique.setActionCommand("MonterMusique");
		elementAugmenterMusique.addActionListener(gestionnaireMusique);

		//BaisserMusique
		JMenuItem elementDiminuerMusique = new JMenuItem("- Volume Musique");
		elementDiminuerMusique.setActionCommand("BaisserMusique");
		elementDiminuerMusique.addActionListener(gestionnaireMusique);

		//MonterSon
		JMenuItem elementAugmenterSons = new JMenuItem("+ Volume Sons");
		elementAugmenterSons.setActionCommand("MonterSon");
		elementAugmenterSons.addActionListener(gestionnaireMusique);

		//BaisserSon
		JMenuItem elementDiminuerSons = new JMenuItem("- Volume Sons");
		elementDiminuerSons.setActionCommand("BaisserSon");
		elementDiminuerSons.addActionListener(gestionnaireMusique);

		//Play
		JMenuItem elementPlay = new JMenuItem("Play");
		elementPlay.setActionCommand("JouerMusique");
		elementPlay.addActionListener(gestionnaireMusique);

		//Stop
		JMenuItem elementStop = new JMenuItem("Stop");
		elementStop.setActionCommand("StopMusique");
		elementStop.addActionListener(gestionnaireMusique);

		//Suivant
		JMenuItem elementSuivant = new JMenuItem("Musique suivante");
		elementSuivant.setActionCommand("JouerSuivant");
		elementSuivant.addActionListener(gestionnaireMusique);

		//Precedent
		JMenuItem elementPrecedent = new JMenuItem("Musique précédente");
		elementPrecedent.setActionCommand("JouerPrecedent");
		elementPrecedent.addActionListener(gestionnaireMusique);

		//Menu Fichier
		menuFichier.add(elementMenu);
		menuFichier.add(elementConfiguration);
		menuFichier.add(elementNouveau);
		menuFichier.add(new JSeparator());
		menuFichier.add(elementOuvrir);
		menuFichier.add(elementEnregistrer);
		menuFichier.add(elementEnregistrerSous);
		menuFichier.add(new JSeparator());
		menuFichier.add(elementQuitter);

		//Menu Edition
		menuEdition.add(elementAjouter);
		menuEdition.add(elementSelectionEdition);
		menuEdition.add(elementDupliquer);
		menuEdition.add(elementEffacer);
		menuEdition.add(elementDeplacer);
		menuEdition.add(elementTourner);
		menuEdition.add(elementTaille);
		menuEdition.add(elementEffacerListeJoueurs);
		
		//Menu Mode
		menuMode.add(elementEdition);
		menuMode.add(elementJeu);

		//Menu Aide
		menuAide.add(elementAuteurs);
		menuAide.add(elementPropos);

		//Menu Vue
		menuVue.add(elementLibre);
		menuVue.add(elementOrbite);
		menuVue.add(elementCiel);
		menuVue.add(elementOrthogonale);

		//Menu Musique
		menuMusique.add(elementChangerVolumes);
		menuMusique.addSeparator();
		menuMusique.add(elementAugmenterMusique);
		menuMusique.add(elementDiminuerMusique);
		menuMusique.addSeparator();
		menuMusique.add(elementAugmenterSons);
		menuMusique.add(elementDiminuerSons);
		menuMusique.addSeparator();
		menuMusique.add(elementPlay);
		menuMusique.add(elementStop);
		menuMusique.add(elementSuivant);
		menuMusique.add(elementPrecedent);

		barre.add(menuFichier);
		if(InterfaceJava.mode_ == "Editeur")
		{
			barre.add(menuEdition);
		}
		barre.add(menuMode);
		barre.add(menuVue);
		barre.add(menuMusique);
		barre.add(menuAide);

		InterfaceJava.fenetreGeneral_.setJMenuBar(barre);
	}

	/**
	 * Fonction qui construit la barre d'outil utilisé dans les 2 états
	 */
	public void creerBarreOutilGeneral()
	{

		barreGeneral = new JToolBar("General", SwingConstants.HORIZONTAL);
		barreGeneral.setFloatable(false);

		Gestionnaire gestionnaireBarreGeneral = new Gestionnaire(this);

		//ZoomIn
		JButton boutonZoomIn = new JButton();
		boutonZoomIn.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/Zoom-In.png")));
		boutonZoomIn.setActionCommand("ZoomIn");
		boutonZoomIn.addActionListener(gestionnaireBarreGeneral);
		boutonZoomIn.setToolTipText("Augmente le zoom.");

		//ZoomOut
		JButton boutonZoomOut = new JButton();
		boutonZoomOut.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/Zoom-Out.png")));
		//boutonZoomOut.setActionCommand("ZoomOut");MonterSonSlider
		boutonZoomOut.setActionCommand("ZoomOut");
		boutonZoomOut.addActionListener(gestionnaireBarreGeneral);
		boutonZoomOut.setToolTipText("Réduit le zoom.");

		//ZoomElastique
		boutonZoomElastique = new JToggleButton();
		boutonZoomElastique.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/zoom-selection-icon.png")));
		boutonZoomElastique.setActionCommand("ZoomElastique");
		boutonZoomElastique.addActionListener(gestionnaireBarreGeneral);
		boutonZoomElastique.setToolTipText("Fait un zoom à l'aide d'un rectangle élastique.");

		//ZoomSouris
		boutonZoomSouris = new JToggleButton();
		boutonZoomSouris.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/mouse-add-icon.png")));
		boutonZoomSouris.setActionCommand("ZoomSouris");
		boutonZoomSouris.addActionListener(gestionnaireBarreGeneral);
		boutonZoomSouris.setToolTipText("Modifie le zoom en bougeant la souris vers le haut ou le bas.");

		//Mode Selection
		boutonSelection = new JToggleButton();
		boutonSelection.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/select-icon.png")));
		boutonSelection.setActionCommand("SelectionEdition");
		boutonSelection.addActionListener(gestionnaireBarreGeneral);
		boutonSelection.setToolTipText("Permet la sélection d'un ou de plusieurs objets.");


		//ModeEdition
		boutonModeEdition = new JToggleButton();
		boutonModeEdition.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/hammer-icon.png")));
		boutonModeEdition.setSelected(true);
		boutonModeEdition.setActionCommand("Edition");
		boutonModeEdition.addActionListener(gestionnaireBarreGeneral);
		boutonModeEdition.setToolTipText("Passe au mode édition.");

		//ModeJeu
		boutonModeJeu = new JToggleButton();
		boutonModeJeu.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/controller-icon.png")));
		boutonModeJeu.setActionCommand("Jeu");
		boutonModeJeu.addActionListener(gestionnaireBarreGeneral);	
		boutonModeJeu.setToolTipText("Passe au mode jeu.");

		//Dupliquer
		boutonDupliquer = new JButton();
		boutonDupliquer.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/Actions-edit-copy-icon.png")));
		boutonDupliquer.setActionCommand("Dupliquer");
		boutonDupliquer.addActionListener(gestionnaireBarreGeneral);
		boutonDupliquer.setToolTipText("Fait une copie des objets sélectionnés.");

		//Effacer
		boutonEffacer = new JButton();
		boutonEffacer.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/cross-icon.png")));
		boutonEffacer.setActionCommand("Effacer");
		boutonEffacer.addActionListener(gestionnaireBarreGeneral);
		boutonEffacer.setToolTipText("Détruit les objets sélectionnés.");

		//Tourner
		boutonTourner = new JButton();
		boutonTourner.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/arrow-rotate-anticlockwise-icon.png")));
		boutonTourner.setActionCommand("Tourner");
		boutonTourner.addActionListener(gestionnaireBarreGeneral);
		boutonTourner.setToolTipText("Change l'angle des objets sélectionnés.");

		//Redimentionner
		boutonRedimentionner = new JButton();
		boutonRedimentionner.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/resize-picture-icon.png")));
		boutonRedimentionner.setActionCommand("Taille");
		boutonRedimentionner.addActionListener(gestionnaireBarreGeneral);
		boutonRedimentionner.setToolTipText("Redimentionne les objets sélectionnés.");

		//Deplacer
		boutonDeplacer = new JButton();
		boutonDeplacer.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/canvas-size-icon.png")));
		boutonDeplacer.setActionCommand("Deplacer");
		boutonDeplacer.addActionListener(gestionnaireBarreGeneral);
		boutonDeplacer.setToolTipText("Déplace les objets sélectionnés.");

		//Enregistrer
		boutonSauvegarder = new JButton();
		boutonSauvegarder.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/disk-icon.png")));
		boutonSauvegarder.setActionCommand("Enregistrer");
		boutonSauvegarder.addActionListener(gestionnaireBarreGeneral);
		boutonSauvegarder.setToolTipText("Enregistre le parcours.");

		//EnregistrerTournoi
		boutonSauvegarderTournois = new JButton();
		boutonSauvegarderTournois.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/disk-icon.png")));
		boutonSauvegarderTournois.setActionCommand("EnregistrerTournois");
		boutonSauvegarderTournois.addActionListener(gestionnaireBarreGeneral);
		boutonSauvegarderTournois.setToolTipText("Enregistre le tournoi.");
		boutonSauvegarderTournois.setVisible(false);

		//Ouvrir
		boutonOuvrir = new JButton();
		boutonOuvrir.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/open-folder-icon.png")));
		boutonOuvrir.setActionCommand("Ouvrir");
		boutonOuvrir.addActionListener(gestionnaireBarreGeneral);
		boutonOuvrir.setToolTipText("Ouvre un parcours existant.");

		//OuvrirTournoi
		boutonOuvrirTournois = new JButton();
		boutonOuvrirTournois.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/open-folder-icon.png")));
		boutonOuvrirTournois.setActionCommand("OuvrirTournois");
		boutonOuvrirTournois.addActionListener(gestionnaireBarreGeneral);
		boutonOuvrirTournois.setToolTipText("Ouvre un tournoi existant.");
		boutonOuvrirTournois.setVisible(false);

		//Recommencer trou
		boutonRecommencer = new JButton();
		boutonRecommencer.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/Letter-R-icon.png")));
		boutonRecommencer.setActionCommand("Recommencer");
		boutonRecommencer.addActionListener(gestionnaireBarreGeneral);
		boutonRecommencer.setToolTipText("Recommencer le trou en cours.");
		boutonRecommencer.setVisible(false);

		//Replay coup
		boutonReplay = new JButton();
		boutonReplay.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/Replay.png")));
		boutonReplay.setActionCommand("Replay");
		boutonReplay.addActionListener(gestionnaireBarreGeneral);
		boutonReplay.setToolTipText("Voir le dernier coup joué.");
		boutonReplay.setVisible(false);
		boutonReplay.setEnabled(false);
		
		// boutonJouerMusique
		boutonJouerMusique = new JButton();
		boutonJouerMusique.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/jouerMusique.png")));
		boutonJouerMusique.setActionCommand("JouerMusique");
		boutonJouerMusique.addActionListener(gestionnaireBarreGeneral);
		boutonJouerMusique.setToolTipText("Jouer la musique.");
		boutonJouerMusique.setVisible(false);

		// boutonStopMusique
		boutonStopMusique = new JButton();
		boutonStopMusique.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/Button-Stop-icon.png")));
		boutonStopMusique.setActionCommand("StopMusique");
		boutonStopMusique.addActionListener(gestionnaireBarreGeneral);
		boutonStopMusique.setToolTipText("Arrêter la musique.");
		boutonStopMusique.setVisible(false);

		// boutonJouerPrecedent
		boutonJouerPrecedent = new JButton();
		boutonJouerPrecedent.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/jouerPrecedent.png")));
		boutonJouerPrecedent.setActionCommand("JouerPrecedent");
		boutonJouerPrecedent.addActionListener(gestionnaireBarreGeneral);
		boutonJouerPrecedent.setToolTipText("Jouer la musique précédente.");
		boutonJouerPrecedent.setVisible(false);

		// boutonJouerSuivant
		boutonJouerSuivant = new JButton();
		boutonJouerSuivant.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/jouerSuivant.png")));
		boutonJouerSuivant.setActionCommand("JouerSuivant");
		boutonJouerSuivant.addActionListener(gestionnaireBarreGeneral);
		boutonJouerSuivant.setToolTipText("Jouer la musique suivante.");
		boutonJouerSuivant.setVisible(false);

		//Vue
		boutonVue = new JToggleButton();
		boutonVue.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/eye-icon.png")));
		boutonVue.setActionCommand("Vue");
		boutonVue.addActionListener(gestionnaireBarreGeneral);
		boutonVue.setToolTipText("Changer la vue.");
		boutonVue.setVisible(false);

		//Volume
		boutonVolume = new JButton();
		boutonVolume.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/sound-icon.png")));
		boutonVolume.setActionCommand("ChangerVolumes");
		boutonVolume.addActionListener(gestionnaireBarreGeneral);
		boutonVolume.setToolTipText("Changer le volume de la musique ou des sons.");
		boutonVolume.setVisible(true);
		
		//Mute
		boutonMute = new JButton();
		boutonMute.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/mute.png")));
		boutonMute.setActionCommand("Mute");
		boutonMute.addActionListener(gestionnaireBarreGeneral);
		boutonMute.setToolTipText("Enlever ou remettre le volume de la musique ou des sons.");
		boutonMute.setVisible(true);

		//Pointage
		boutonPointage = new JButton();
		boutonPointage.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/Trophy.png")));
		boutonPointage.setActionCommand("Pointage");
		boutonPointage.addActionListener(gestionnaireBarreGeneral);
		boutonPointage.setToolTipText("Affiche le pointage de la partie.");
		boutonPointage.setVisible(true);

		// Ajout dans la barre
		barreGeneral.add(boutonModeEdition);
		barreGeneral.add(boutonModeJeu);
		barreGeneral.addSeparator();
		barreGeneral.add(boutonSauvegarder);
		barreGeneral.add(boutonSauvegarderTournois);
		barreGeneral.add(boutonOuvrir);
		barreGeneral.add(boutonOuvrirTournois);
		barreGeneral.addSeparator();
		barreGeneral.add(boutonZoomIn);
		barreGeneral.add(boutonZoomOut);
		barreGeneral.add(boutonZoomElastique);
		barreGeneral.add(boutonZoomSouris);
		barreGeneral.add(boutonVue);
		barreGeneral.addSeparator();
		barreGeneral.add(boutonSelection);
		barreGeneral.add(boutonRecommencer);
		barreGeneral.add(boutonReplay);
		barreGeneral.addSeparator();
		barreGeneral.add(boutonVolume);
		barreGeneral.add(boutonMute);
		barreGeneral.add(boutonJouerPrecedent);
		barreGeneral.add(boutonStopMusique);
		barreGeneral.add(boutonJouerMusique);
		barreGeneral.add(boutonJouerSuivant);
		barreGeneral.addSeparator();
		barreGeneral.add(boutonDupliquer);
		barreGeneral.add(boutonEffacer);
		barreGeneral.add(boutonTourner);
		barreGeneral.add(boutonRedimentionner);
		barreGeneral.add(boutonDeplacer);
		barreGeneral.add(boutonPointage);


		barreGeneral.setPreferredSize(new Dimension(500,50));
		InterfaceJava.fenetreGeneral_.add(barreGeneral, BorderLayout.NORTH);	
	}

	/**
	 * Fonction qui construit la barre d'outil de l'état édition
	 */
	public void creerBarreOutilEdition()
	{

		barreEdition = new JToolBar("Edition", SwingConstants.VERTICAL);
		// Gestionnaire des boutons.
		// GestionnaireAction gestionnaire = new GestionnaireAction(this);
		barreEdition.setFloatable(false);

		Gestionnaire gestionnaireBarreEdition = new Gestionnaire(this);

		//Aide
		JButton boutonAide = new JButton();
		boutonAide.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/aide32x32.png")));
		boutonAide.setActionCommand("AideBarre");
		boutonAide.addActionListener(gestionnaireBarreEdition);
		boutonAide.setToolTipText("Aide pour ajouter un objet.");

		//Balle
		JButton boutonBalle = new JButton();
		boutonBalle.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/balle.png")));
		boutonBalle.setActionCommand("BalleBarre");
		boutonBalle.addActionListener(gestionnaireBarreEdition);
		boutonBalle.setToolTipText("Ajoute une balle.");

		//Trou
		JButton boutonTrou = new JButton();
		boutonTrou.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/trou.png")));
		boutonTrou.setActionCommand("TrouBarre");
		boutonTrou.addActionListener(gestionnaireBarreEdition);
		boutonTrou.setToolTipText("Ajoute un trou.");

		//Mur
		JButton boutonMur = new JButton();
		boutonMur.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/mur.png")));
		boutonMur.setActionCommand("MurBarre");
		boutonMur.addActionListener(gestionnaireBarreEdition);	   
		boutonMur.setToolTipText("Ajoute un mur.");

		//Eau
		JButton boutonEau = new JButton();
		boutonEau.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/eau.png")));
		boutonEau.setActionCommand("EauBarre");
		boutonEau.addActionListener(gestionnaireBarreEdition);	
		boutonEau.setToolTipText("Ajoute un trou d'eau.");

		//Sable
		JButton boutonSable = new JButton();
		boutonSable.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/sable.png")));
		boutonSable.setActionCommand("SableBarre");
		boutonSable.addActionListener(gestionnaireBarreEdition);	
		boutonSable.setToolTipText("Ajoute une trappe de sable.");

		//Bonus
		JButton boutonBonus = new JButton();
		boutonBonus.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/bonus.png")));
		boutonBonus.setActionCommand("BonusBarre");
		boutonBonus.addActionListener(gestionnaireBarreEdition);	
		boutonBonus.setToolTipText("Ajoute un bonus.");

		//Contour
		JButton boutonContour = new JButton();
		boutonContour.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/contour.png")));
		boutonContour.setActionCommand("ContourBarre");
		boutonContour.addActionListener(gestionnaireBarreEdition);	   
		boutonContour.setToolTipText("Ajoute le contour.");

		//Portail
		JButton boutonPortail = new JButton();
		boutonPortail.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/portal.png")));
		boutonPortail.setActionCommand("Portail");
		boutonPortail.addActionListener(gestionnaireBarreEdition);	   
		boutonPortail.setToolTipText("Ajoute un Portail");

		// Ajout dans la barre
		barreEdition.add(boutonAide);
		barreEdition.add(boutonBalle);
		barreEdition.add(boutonTrou);
		barreEdition.add(boutonMur);
		barreEdition.add(boutonEau);
		barreEdition.add(boutonSable);
		barreEdition.add(boutonBonus);
		barreEdition.add(boutonContour);
		barreEdition.add(boutonPortail);

		barreEdition.setPreferredSize(new Dimension(50,500));
		InterfaceJava.fenetreGeneral_.add(barreEdition, BorderLayout.EAST);

	}

	/**
	 * Fonction qui construit la barre de status qui affiche la position de la souris
	 */
	public void creeBarreStatus()
	{
		barreStatus = new JPanel();
		position = new JLabel();
		position.setText("Position de la souris : (X,Y)");
		barreStatus.add(position); //Position de la souris : (X,Y)" + "( 102 , " + "253 )
		InterfaceJava.fenetreGeneral_.add(barreStatus, BorderLayout.SOUTH);
	}

	@Override
	public void propertyChange(PropertyChangeEvent evt) 
	{
		//  Auto-generated method stub

	}

	/**
	 * Fonction qui retourne le canvas
	 */
	public Canvas getCanvas() 
	{
		return canvas_;
	}

	/**
	 * Fonction qui retourne le X du dernier clic de souris
	 */
	public int getLastX() {
		return lastX_;
	}

	/**
	 * Fonction qui retourne le Y du dernier clic de souris
	 */
	public int getLastY() {
		return lastY_;
	}

	/**
	 * Fonction qui retourne le X virtuel du dernier clic de souris
	 */
	public double getLastXd() {
		return lastXd_;
	}

	/**
	 * Fonction qui retourne le Y virtuel du dernier clic de souris
	 */
	public double getLastYd() {
		return lastYd_;
	}

	/**
	 * Fonction qui retourne le bouton de la souris qui est utilisé
	 */
	public int getQuelClick() {
		return quelClick_;
	}

	/**
	 * Fonction qui retourne le X du premier coin du rectangle
	 */
	public int getCoin1X() {
		return coin1X_;
	}

	/**
	 * Fonction qui retourne le Y du premier coin du rectangle
	 */
	public int getCoin1Y() {
		return coin1Y_;
	}

	/**
	 * Fonction qui retourne le X du deuxième coin du rectangle
	 */
	public int getCoin2X() {
		return coin2X_;
	}

	/**
	 * Fonction qui retourne le Y du deuxième coin du rectangle
	 */
	public int getCoin2Y() {
		return coin2Y_;
	}

	/**
	 * Fonction qui définie le X du dernier clic de souris 
	 */
	public void setLastX(int x) {
		lastX_ = x;
	}

	/**
	 * Fonction qui définie le Y du dernier clic de souris 
	 */
	public void setLastY(int y) {
		lastY_ = y;
	}

	/**
	 * Fonction qui définie le X virtuel du dernier clic de souris 
	 */
	public void setLastXd(double x) {
		lastXd_ = x;
	}

	/**
	 * Fonction qui définie le Y virtuel du dernier clic de souris 
	 */
	public void setLastYd(double y) {
		lastYd_ = y;
	}

	/**
	 * Fonction qui définie le bouton de la souris qui est utilisé 
	 */
	public void setClick(int click)
	{
		quelClick_ = click;
	}

	/**
	 * Fonction qui définie le X du premier coin du rectangle
	 */
	public void setCoin1X(int x) {
		coin1X_ = x;
	}

	/**
	 * Fonction qui définie le Y du premier coin du rectangle
	 */
	public void setCoin1Y(int y) {
		coin1Y_ = y;
	}

	/**
	 * Fonction qui définie le X du deuxième coin du rectangle
	 */
	public void setCoin2X(int x) {
		coin2X_ = x;
	}

	/**
	 * Fonction qui définie le Y du deuxième coin du rectangle
	 */
	public void setCoin2Y(int y) {
		coin2Y_ = y;
	}

	/**
	 * Fonction qui définie l'ancrage en X
	 */
	public void setAncrageX(int x) {
		ancrageX_ = x;
	}

	/**
	 * Fonction qui définie l'ancrage en Y
	 */
	public void setAncrageY(int y) {
		ancrageY_ = y;
	}

	/**
	 * Fonction qui définie l'ancrage virtuel en X
	 */
	public void setAncrageXd(double x) {
		ancrageXd_ = x;
	}

	/**
	 * Fonction qui définie l'ancrage virtuel en Y
	 */
	public void setAncrageYd(double y) {
		ancrageYd_ = y;
	}

	/**
	 * Fonction qui retourne l'ancrage en X
	 */
	public int getAncrageX() {
		return ancrageX_;
	}

	/**
	 * Fonction qui retourne l'ancrage en Y
	 */
	public int getAncrageY() {
		return ancrageY_;
	}

	/**
	 * Fonction qui retourne l'ancrage virtuel en X
	 */
	public double getAncrageXd() {
		return ancrageXd_;
	}

	/**
	 * Fonction qui retourne l'ancrage virtuel en Y
	 */
	public double getAncrageYd() {
		return ancrageYd_;
	}

	/**
	 * Fonction qui définie l'état de la souris
	 * 
	 * @param	nouvelEtat	le nouvel état de la souris
	 */
	public void setEtatSouris(EtatSouris nouvelEtat)
	{
		etatSouris = nouvelEtat;
	}

	/**
	 * Fonction qui construit une boite de dialogue
	 * 
	 * @param 	message		la question a poser dans la boite de dialogue
	 * @param	titre		le titre de la boite de dialogue
	 * 
	 * @return	retour		retourne la String entrée par l'utilisateur
	 */
	public String boiteDialogueTexte(String message, String titre)
	{
		int messageType = 3; // affiche un point d'intérogation
		String retour = JOptionPane.showInputDialog(InterfaceJava.fenetreGeneral_, message, titre, messageType);

		return retour;
	}

	/**
	 * Fonction qui construit une boite de dialogue de choix
	 * 
	 * @param 	message		la question a poser dans la boite de dialogue
	 * @param	titre		le titre de la boite de dialogue
	 * 
	 * @return	retour		retourne la String entrée par l'utilisateur
	 */    
	public int boiteDialogueChoix(String message, String titre)
	{
		Object[] options = {"Oui", "Non"};

		int retour = JOptionPane.showOptionDialog(InterfaceJava.fenetreGeneral_, message, titre, JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[1]);

		return retour;
	}

	//Enum contenant tous les états possible de la souris
	public enum EtatSouris 
	{
		ES_aucun,
		ES_zoomElastique,
		ES_placer,
		ES_selectionner,
		ES_selectionnerRectangle,
		Es_deplacerSelect,
		ES_zoomSouris
	}

	//Enum contenant tous les objets possible
	public enum EtatSourisObjets
	{
		ESO_balle,
		ESO_trou,
		ESO_eau,
		ESO_sable,
		ESO_bonus,
		ESO_mur,
		ESO_contour,
		ESO_portal
	}

	//Variables de declaration
	private int lastX_ = 0, lastY_ = 0,coin1X_ = 0, coin1Y_ = 0, quelClick_ = 0;
	private int coin2X_ = 0, coin2Y_ = 0, ancrageX_ = 0, ancrageY_ = 0;
	private double lastXd_ = 0.0, lastYd_ = 0.0, ancrageXd_ = 0.0,ancrageYd_ = 0.0;
	private static MenuPrincipal instance_;
	private Canvas canvas_;
	protected JToggleButton boutonModeEdition, boutonModeJeu, boutonZoomSouris, boutonZoomElastique, boutonSelection, boutonVue;
	protected JButton boutonDupliquer, boutonEffacer, boutonTourner, boutonRedimentionner, boutonDeplacer, boutonSauvegarder, boutonOuvrir, boutonSauvegarderTournois, 
	boutonOuvrirTournois, boutonRecommencer, boutonReplay, boutonJouerMusique, boutonStopMusique, boutonJouerPrecedent, boutonJouerSuivant, boutonVolume, boutonPointage, boutonMute;
	protected JMenu menuEdition, menuMode;
	private boolean active = false;
	public EtatSourisObjets etatSourisObjets;
	public EtatSouris etatSouris = EtatSouris.ES_aucun;
	public JLabel position;
	private boolean sauvegarde_ = false;
	protected String nomFichierXml_ ="configuration.xml";
	protected JToolBar barreEdition, barreGeneral;
	private ContexteEtat etat_;
	protected JMenu menuFichier;
	public JMenuItem elementNouveau;
	public JMenuItem elementOrbite;
	public JMenuItem elementCiel;
	public JMenuItem elementLibre;
	public JMenuItem elementOrthogonale;
	protected JPanel barreStatus;
	protected String toucheSelection = "F";
	private MenuDeBase menuDeBase_ = MenuDeBase.getInstance();
	public boolean jouerEdition = false;
	public boolean vue_ = false;
	private Volume volume_;
	private Pointage pointage_ = Pointage.getInstance();
	public float volumeSon_ = (float) 0.5;
	public float volumeMusique = (float) 0.3;
	private EtatEditeur etatEditeur_ = EtatEditeur.getInstance();
	public String par;
	private int nbPar;
}