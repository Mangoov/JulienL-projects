package ca.polymtl.inf2990;

import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
/**
 *
 * @author Jean-Luc Dubeau et Etienne Vallée
 */

public class MenuDeBase extends javax.swing.JFrame {

	/** 
	 * Creation du menu
	 */
	public MenuDeBase() {
		initComponents();
		setLocationRelativeTo(null);  
	}

	/** 
	 * Initialisation du menu de base du jeu
	 */
	private void initComponents() {

		boutonJouer = new javax.swing.JButton();
		boutonEdition = new javax.swing.JButton();
		boutonOptions = new javax.swing.JButton();
		boutonTournoi = new javax.swing.JButton();
		imageMenuBase = new javax.swing.JLabel();

		getContentPane().setLayout(null);

		setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
		setTitle("Menu Angryball");
		setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));

		// change l'icone de la fenetre
		BufferedImage image = null;
		try 
		{
			image = ImageIO.read(getClass().getResource("/ca/polymtl/inf2990/icones/Golf_Icone.png"));
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
		setIconImage(image);

		boutonJouer.setBackground(new java.awt.Color(255, 186, 126));
		boutonJouer.setFont(new java.awt.Font("Comic Sans MS", 1, 20));
		boutonJouer.setForeground(new java.awt.Color(102, 51, 0));
		boutonJouer.setText("Partie Rapide");
		boutonJouer.addActionListener(new java.awt.event.ActionListener() {
			@Override
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				boutonJouerActionPerformed(evt);
			}
		});

		boutonEdition.setBackground(new java.awt.Color(255, 186, 126));
		boutonEdition.setFont(new java.awt.Font("Comic Sans MS", 1, 20));
		boutonEdition.setForeground(new java.awt.Color(102, 51, 0));
		boutonEdition.setText("Mode Édition");
		boutonEdition.addActionListener(new java.awt.event.ActionListener() {
			@Override
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				boutonModeEditionActionPerformed(evt);
			}
		});

		boutonOptions.setBackground(new java.awt.Color(255, 186, 126));
		boutonOptions.setFont(new java.awt.Font("Comic Sans MS", 1, 20));
		boutonOptions.setForeground(new java.awt.Color(102, 51, 0));
		boutonOptions.setText("Option");
		boutonOptions.addActionListener(new java.awt.event.ActionListener() {
			@Override
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				boutonOptionsActionPerformed(evt);
			}
		});

		boutonTournoi.setBackground(new java.awt.Color(255, 186, 126));
		boutonTournoi.setFont(new java.awt.Font("Comic Sans MS", 1, 20));
		boutonTournoi.setForeground(new java.awt.Color(102, 51, 0));
		boutonTournoi.setText("Tournoi");
		boutonTournoi.addActionListener(new java.awt.event.ActionListener() {
			@Override
			public void actionPerformed(java.awt.event.ActionEvent evt) {
				boutonTournoiActionPerformed(evt);
			}
		});

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(
				layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
				.addGroup(layout.createSequentialGroup()
						.addGap(108, 108, 108)
						.addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER)
								.addComponent(boutonJouer, javax.swing.GroupLayout.PREFERRED_SIZE, 191, javax.swing.GroupLayout.PREFERRED_SIZE)
								.addComponent(boutonOptions, javax.swing.GroupLayout.PREFERRED_SIZE, 191, javax.swing.GroupLayout.PREFERRED_SIZE)
								.addComponent(boutonEdition, javax.swing.GroupLayout.PREFERRED_SIZE, 191, javax.swing.GroupLayout.PREFERRED_SIZE)
								.addComponent(boutonTournoi, javax.swing.GroupLayout.PREFERRED_SIZE, 191, javax.swing.GroupLayout.PREFERRED_SIZE))
								.addContainerGap(118, Short.MAX_VALUE))
				);
		layout.setVerticalGroup(
				layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
				.addGroup(layout.createSequentialGroup()
						.addGap(53, 53, 53)
						.addComponent(boutonJouer, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
						.addGap(55, 55, 55)
						.addComponent(boutonTournoi, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
						.addGap(49, 49, 49)
						.addComponent(boutonEdition, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
						.addGap(52, 52, 52)
						.addComponent(boutonOptions, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
						.addContainerGap(54, Short.MAX_VALUE))
				);


		imageMenuBase.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/imageMenuBase.png")));
		getContentPane().add(imageMenuBase);
		imageMenuBase.setBounds(0, 0, 420, 540);


		pack();
	}

	/**
	 * Fonction qui s'occupe du bouton Jouer (partie rapide)
	 */  
	private void boutonJouerActionPerformed(java.awt.event.ActionEvent evt)
	{
		tournoiActif_ = false;
		jeu("BaseMap.xml");
	}

	/**
	 * Fonction qui s'occupe du bouton Tournoi
	 */  
	private void boutonTournoiActionPerformed(java.awt.event.ActionEvent evt) {

		Object[] options = {"Tournoi existant",
		"Nouveau tournoi"};
		int reponse = JOptionPane.showOptionDialog(InterfaceJava.fenetreGeneral_,
				"Voulez vous ouvrir un tournoi existant"+ '\n' + "  ou créer un nouveau tournoi?","Tournoi",
				JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[0]);

		if(reponse == 1)//nouveau tournois
		{
			String nomTournoi = MenuPrincipal.getInstance().boiteDialogueTexte("Comment voulez-vous nommer le tournoi?", "Tournoi");
			
			if(nomTournoi != null)
			{			
				if (nomTournoi.matches(".*[0-9].*") )
				{
					System.out.println("Contains numbers");
					JOptionPane.showMessageDialog(InterfaceJava.fenetreGeneral_,
							"Vous ne pouvez pas entrer de chiffre dans le nom du tournoi.",
							"Attention!",
							JOptionPane.WARNING_MESSAGE);
				}
				else
				{
					if(nomTournoi.matches(".*[ ].*"))
					{
						nomTournoi= nomTournoi.replaceAll("\\s+", "_");
						System.out.println("");
					}
					
					String nbTrou = MenuPrincipal.getInstance().boiteDialogueTexte("Combien de trous voulez-vous mettre?" + '\n' + "Maximum de 9 trous.", "Tournoi");
					if(nbTrou != null)
					{
						int nbTrous = Integer.parseInt(nbTrou);
						
						while(nbTrous <1 || nbTrous >9)
						{
							nbTrou = MenuPrincipal.getInstance().boiteDialogueTexte("Combien de trous voulez-vous mettre?" + '\n' + "Maximum de 9 trous.", "Tournoi");
							nbTrous =Integer.parseInt(nbTrou);
						}
						
						mapTournoi = new String[nbTrous];
						
						for(int i=0; i<nbTrous; i++)
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
		
								mapTournoi[i]= nomFichier;
							
								InterfaceJava.fctC_chargerFichierTournoi(); 
								InterfaceJava.fctC_ajouterParcoursATournoi(nomTournoi, nomFichier);
		
							}
							else if(valeurRetour == JFileChooser.CANCEL_OPTION)
							{
								cancel_ = true;
								break;
							}
						}
						if(cancel_ == false)
						{
							InterfaceJava.fctC_enregistrerFichierTournoi();
							tournoiActif_ = true;
							jeu(mapTournoi[0]);
						}
					}
				}
			}
		}
		else //Tournoi existant
		{
			InterfaceJava.fctC_chargerFichierTournoi();

			String[] choices = InterfaceJava.fctC_obtenirNomsTournois();
			selectedName = TournoisDialogue.showDialog(InterfaceJava.fenetreGeneral_, null,
					"A description of the list:", "Dialog Title", choices, choices[0], "--------size of the strings--------");

			mapTournoi = InterfaceJava.fctC_obtenirNomsParcours(selectedName);

			InterfaceJava.fctC_musiqueMenu(0);
			InterfaceJava.fctC_play();
			tournoiActif_ = true;
			jeu(mapTournoi[0]);		
		}
	}

	/**
	 * Fonction qui s'occupe du bouton mode edition
	 */  
	private void boutonModeEditionActionPerformed(java.awt.event.ActionEvent evt) {
		InterfaceJava.fenetreGeneral_.setVisible(true);
		menuDeBase_.setVisible(false);
		edition("BaseMapEdition.xml");
		//dispose();
	}

	/**
	 * Fonction qui s'occupe du bouton option
	 */  
	private void boutonOptionsActionPerformed(java.awt.event.ActionEvent evt) {

		new Option().setVisible(true);
	}

	/**
	 * Fonction pour mode edition
	 */  
	public void edition(String nom)
	{
		instance_ = MenuPrincipal.getInstance();
		InterfaceJava.mode_ = "Editeur";
		instance_.boutonModeJeu.setSelected(false);
		instance_.boutonModeEdition.setSelected(true);
		nbJoueur = 1;
		InterfaceJava.fctC_changerMode(false); // le mode est édition
		if(nom!="")
		{
			InterfaceJava.fctC_viderArbre();
			InterfaceJava.fctC_chargerXml(nom);
		}
		else
		{
			InterfaceJava.fctC_viderArbre();
		}
		if(instance_.vue_ == true)
		{
			//InterfaceJava.fctC_changerVue();
			instance_.vue_ = false;
		}
		instance_.nomFichierXml_ = "CurrentMap.xml";
		instance_.boutonSelection.setVisible(true);
		instance_.barreEdition.setVisible(true);
		instance_.menuEdition.setVisible(true);
		instance_.boutonDupliquer.setVisible(true);
		instance_.boutonEffacer.setVisible(true);
		instance_.boutonRedimentionner.setVisible(true);
		instance_.boutonTourner.setVisible(true);
		instance_.barreStatus.setVisible(true);
		instance_.boutonDeplacer.setVisible(true);
		instance_.boutonOuvrirTournois.setVisible(false);
		instance_.boutonOuvrir.setVisible(true);
		instance_.boutonSauvegarderTournois.setVisible(false);
		instance_.boutonSauvegarder.setVisible(true);
		instance_.boutonRecommencer.setVisible(false);
		instance_.boutonReplay.setVisible(false);
		instance_.boutonJouerMusique.setVisible(false);
		instance_.boutonStopMusique.setVisible(false);
		instance_.boutonJouerPrecedent.setVisible(false);
		instance_.boutonJouerSuivant.setVisible(false);
		instance_.boutonZoomElastique.setVisible(true);
		instance_.boutonZoomSouris.setVisible(true);
		instance_.elementNouveau.setVisible(true);
		instance_.boutonVue.setVisible(false);
		instance_.elementOrbite.setEnabled(false);
		instance_.elementCiel.setEnabled(false);
		instance_.elementOrthogonale.setEnabled(true);
		instance_.boutonPointage.setVisible(false);
		instance_.boutonModeEdition.setEnabled(true);

		etat_ = new ContexteEtat();
		etat_.choixEtat(EtatEditeur.getInstance());
		etat_.ajouterGestionnaires(instance_);
		InterfaceJava.fctC_musiqueMenu(0);
		InterfaceJava.fctC_play();
	}

	/**
	 * Fonction pour mode jeu
	 */  
	private void jeu(String nom)
	{
		instance_ = MenuPrincipal.getInstance();
		if(tournoiActif_ == true)
		{
			nombreJoueur = instance_.boiteDialogueTexte("Êtes-vous 1 ou 2 joueurs?", "Nombre de joueur?");
			try{
				nbJoueur = Integer.parseInt(nombreJoueur);

				while(nbJoueur < 1 || nbJoueur > 2){
					nombreJoueur = instance_.boiteDialogueTexte("Êtes-vous 1 ou 2 joueurs?", "Nombre de joueur?");
					nbJoueur = Integer.parseInt(nombreJoueur);
				}

			}
			catch (NumberFormatException nfe){
				//System.out.println("Erreur format de nombre de joueur.");
				if(nombreJoueur != null)
					JOptionPane.showMessageDialog(null,"Le format de nombre de joueur doit être un nombre.", "Erreur", JOptionPane.WARNING_MESSAGE);
				return;
			}
		}
		else
		{
			nbJoueur = 1;
		}

		nomJoueur = "";
		nomJoueur2 = "";
		
		nomJoueur = instance_.boiteDialogueTexte("Quel est votre nom?", "Nom du premier joueur");
		while (nomJoueur.matches(".*[0-9].*") )
		{
			System.out.println("Contains numbers");
			JOptionPane.showMessageDialog(InterfaceJava.fenetreGeneral_,
					"Vous ne pouvez pas entrer de chiffre dans le nom du joueur.",
					"Attention!",
					JOptionPane.WARNING_MESSAGE);
			nomJoueur = instance_.boiteDialogueTexte("Quel est votre nom?", "Nom du premier joueur");
		}
		
		if(nbJoueur == 2){
			nomJoueur2 = instance_.boiteDialogueTexte("Quel est votre nom?", "Nom du deuxième joueur");
			
			while (nomJoueur2.matches(".*[0-9].*") )
			{
				System.out.println("Contains numbers");
				JOptionPane.showMessageDialog(InterfaceJava.fenetreGeneral_,
						"Vous ne pouvez pas entrer de chiffre dans le nom du joueur.",
						"Attention!",
						JOptionPane.WARNING_MESSAGE);
				nomJoueur2 = instance_.boiteDialogueTexte("Quel est votre nom?", "Nom du deuxième joueur");
			}
		}
		
		if(nomJoueur != null)
		{
			
			if(nomJoueur.matches(".*[ ].*"))
			{
				nomJoueur= nomJoueur.replaceAll("\\s+", "_");
			}
			if(nbJoueur == 2){
				if(nomJoueur2.matches(".*[ ].*"))
				{
					nomJoueur2= nomJoueur2.replaceAll("\\s+", "_");
				}
			}
			
			menuDeBase_.setVisible(false);
			
			Pointage.effacerScore();
			InterfaceJava.joueurCourant_=1;
			InterfaceJava.map=1;
			
			if(nomJoueur.equals(""))
			{
				JOptionPane.showMessageDialog(null, "Comme le joueur 1 n'a pas inscrit de nom, il s'appellera Joueur1!"); 
				nomJoueur = "Joueur1";
			}

			if(nbJoueur == 2 && nomJoueur2.equals(""))
			{
				JOptionPane.showMessageDialog(null, "Comme le joueur 2 n'a pas inscrit de nom, il s'appellera Joueur2!"); 
				nomJoueur2 = "Joueur2";
			}

			System.out.println(nomJoueur);
			InterfaceJava.fctC_obtenirNomJoueur(nomJoueur);
			if(instance_.vue_ == false)
			{
				//InterfaceJava.fctC_changerVue();
				instance_.vue_ = true;
			}
			if(nbJoueur == 2)
			{
				instance_.boutonRecommencer.setEnabled(false);
			}
			InterfaceJava.mode_ = "Jeu";
			instance_.boutonModeJeu.setSelected(true);
			instance_.boutonModeEdition.setSelected(false);
			InterfaceJava.fctC_viderArbre();
			InterfaceJava.fctC_chargerXml(nom);
			InterfaceJava.fctC_obtenirNomMap(nom);
			InterfaceJava.fctC_changerMode(true);
			instance_.nomFichierXml_ = nom;
			instance_.boutonSelection.setVisible(false);
			instance_.barreEdition.setVisible(false);
			instance_.menuEdition.setVisible(false);
			instance_.boutonDupliquer.setVisible(false);
			instance_.boutonEffacer.setVisible(false);
			instance_.boutonRedimentionner.setVisible(false);
			instance_.boutonTourner.setVisible(false);
			instance_.barreStatus.setVisible(false);
			instance_.boutonOuvrirTournois.setVisible(false);
			instance_.boutonOuvrir.setVisible(true);
			instance_.boutonDeplacer.setVisible(false);
			instance_.boutonSauvegarderTournois.setVisible(true);
			instance_.boutonSauvegarder.setVisible(false);
			instance_.boutonRecommencer.setVisible(true);
			instance_.boutonReplay.setVisible(true);
			instance_.boutonJouerMusique.setVisible(true);
			instance_.boutonStopMusique.setVisible(true);
			instance_.boutonJouerPrecedent.setVisible(true);
			instance_.boutonJouerSuivant.setVisible(true);
			instance_.boutonZoomElastique.setVisible(false);
			instance_.boutonZoomSouris.setVisible(false);
			instance_.elementNouveau.setVisible(false);
			instance_.boutonVue.setVisible(false);
			instance_.elementOrbite.setEnabled(true);
			instance_.elementCiel.setEnabled(true);
			instance_.elementOrthogonale.setEnabled(false);
			instance_.boutonPointage.setVisible(true);
			instance_.boutonModeEdition.setEnabled(false);
			instance_.menuMode.setEnabled(false);

			InterfaceJava.fctC_changerVue(3);
			InterfaceJava.fctC_redimensionnerFenetre(InterfaceJava.canvas_.getWidth(), InterfaceJava.canvas_.getHeight());
			
			etat_ = new ContexteEtat();
			etat_.choixEtat(new EtatJeu());
			etat_.ajouterGestionnaires(instance_);
			// dispose();
			InterfaceJava.fenetreGeneral_.setVisible(true);
			InterfaceJava.fctC_musiqueMenu(0);
			InterfaceJava.fctC_play();

			if(nbJoueur == 2){
				JOptionPane.showMessageDialog(null, "Bonne partie " + nomJoueur + " et " + nomJoueur2 + "!", ":)", JOptionPane.INFORMATION_MESSAGE);
			}
			else
				JOptionPane.showMessageDialog(null, "Bonne partie " + nomJoueur + "!", ":)", JOptionPane.INFORMATION_MESSAGE);
		}

		else
			return;
	}

	/**
	 * Créer une instance de MenuDeBase
	 */
	public static MenuDeBase getInstance() {
		if (null == menuDeBase_) // Si c'est la première fois
		{ 
			menuDeBase_ = new MenuDeBase();
		}
		return menuDeBase_;
	}

	// Variables de declaration
	private javax.swing.JButton boutonJouer;
	private javax.swing.JButton boutonEdition;
	private javax.swing.JButton boutonOptions;
	private javax.swing.JButton boutonTournoi;
	private javax.swing.JLabel imageMenuBase;
	private ContexteEtat etat_;
	private static MenuPrincipal instance_;
	private boolean cancel_ = false;
	private static MenuDeBase menuDeBase_;
	public String nomJoueur, nomJoueur2, nombreJoueur;
	public int nbJoueur;
	public String mapTournoi [];
	public boolean tournoiActif_ = false;
	public String selectedName;
}

