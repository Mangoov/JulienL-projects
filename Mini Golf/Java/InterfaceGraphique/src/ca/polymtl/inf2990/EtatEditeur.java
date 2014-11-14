package ca.polymtl.inf2990;

import java.awt.Container;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JOptionPane;

import ca.polymtl.inf2990.MenuPrincipal.EtatSouris;
import ca.polymtl.inf2990.MenuPrincipal.EtatSourisObjets;

/**
 *
 * @author Etienne Vallée
 */
public class EtatEditeur implements Etats
{	

	/**
	 * Créer une instance de EtatEditeur
	 */
	public static EtatEditeur getInstance() {
		if (null == instance_) // Si c'est la première fois
		{ 
			instance_ = new EtatEditeur();
		}
		return instance_;
	}

	public EtatEditeur()
	{

	}

	/**
	 * Cette fonction dicte l'agissement des gestionnaires
	 * 
	 */
	@Override
	public void ajouterGestionnaires(ContexteEtat contexteEtat,  final MenuPrincipal menu) 
	{
		System.out.println("EtatEditeur");

		MouseListener[] array = InterfaceJava.canvas_.getMouseListeners();
		for (int i = 0; i< array.length; i++)
		{
			InterfaceJava.canvas_.removeMouseListener(array[i]);
		}

		MouseWheelListener[] array2 = InterfaceJava.canvas_.getMouseWheelListeners();
		for (int i = 0; i < array2.length; i++) 
		{
			InterfaceJava.canvas_.removeMouseWheelListener(array2[i]);
		}

		MouseMotionListener[] array3 = InterfaceJava.canvas_.getMouseMotionListeners();
		for (int i = 0; i < array3.length; i++) 
		{
			InterfaceJava.canvas_.removeMouseMotionListener(array3[i]);
		}

		// Ajout d'un gestionnaire d'événements de la souris.
		InterfaceJava.canvas_.addMouseListener(new MouseAdapter() {

			/**
			 * Cette fonction s'occupe des événements générés lorsque l'on presse un bouton de la souris
			 * 
			 *@param   evenement   L'événement correspondant à l'action.
			 * 
			 */
			@Override
			public void mousePressed(MouseEvent evenement) 
			{
				if(evenement.getButton() == MouseEvent.BUTTON1)
				{
					menu.setClick(evenement.getButton()); 
					pointAvantSourisX_ = evenement.getX();
					pointAvantSourisY_ = evenement.getY();
					switch(menu.etatSouris.ordinal())
					{
					case 0 : // aucun
						System.out.println(
								"La souris a été appuyée à la position (" +
										evenement.getX() + " , " + evenement.getY() + ")"
								);
						//garder les coordonnées lorsqu'on appuie
						menu.setLastX(evenement.getX());
						menu.setLastY(evenement.getY());
						menu.setClick(evenement.getButton());
						break;

					case 1 : //ZoomElastique
						menu.setAncrageX(evenement.getX());
						menu.setAncrageY(evenement.getY());
						menu.setLastX(evenement.getX());
						menu.setLastY(evenement.getY());
						System.out.println("Zoom Elastique (Gauche)");

						// Arrête la minuterie pour que le rectange puisse s'afficher
						InterfaceJava.arretMinuterie_ = true;
						//fctC pour initialiser rect elastique
						InterfaceJava.fctC_initialiserRectangleElastique(menu.getAncrageX(), menu.getAncrageY());
						break;

					case 2 : //Placer

						switch (menu.etatSourisObjets.ordinal())
						{
						case 0:
							InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_balle.ordinal(), evenement.getX(), evenement.getY(), 0, 0);
							menu.etatSouris = EtatSouris.ES_aucun;
							break;
						case 1:
							InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_trou.ordinal(), evenement.getX(), evenement.getY(), 0, 0);
							menu.etatSouris = EtatSouris.ES_aucun;
							break;
						case 2:
							InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_eau.ordinal(), evenement.getX(), evenement.getY(), 0, 0);
							menu.etatSouris = EtatSouris.ES_aucun;
							break;
						case 3:
							InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_sable.ordinal(), evenement.getX(), evenement.getY(), 0, 0);
							menu.etatSouris = EtatSouris.ES_aucun;
							break;
						case 4:
							InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_bonus.ordinal(), evenement.getX(), evenement.getY(), 0, 0);
							menu.etatSouris = EtatSouris.ES_aucun;
							break;
						case 5: //mur
						if(placer_ == false)
						{
							/*menu.setLastX(evenement.getX());
				        	 		menu.setLastY(evenement.getY());*/
				        	 		double lastPos[] = InterfaceJava.fctC_convertirCoordonneesSouris2(evenement.getX(), evenement.getY());
				        	 		menu.setLastXd(lastPos[0]);
				        	 		menu.setLastYd(lastPos[1]);
				        	 		placer_ = true;
						}
						else
						{
							double pos[] = InterfaceJava.fctC_convertirCoordonneesSouris2(evenement.getX(), evenement.getY());
							if(InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_mur.ordinal(), menu.getLastXd(), menu.getLastYd(),pos[0], pos[1]) == true)
							{
								menu.setLastXd(pos[0]);
								menu.setLastYd(pos[1]);
							}
							/*menu.setLastX(evenement.getX());
				        	 		menu.setLastY(evenement.getY());*/		       
						}
						break;
						case 6: //contour
							if(placer_ == false)
							{
								/*menu.setAncrageX(evenement.getX());
		        	 				menu.setAncrageY(evenement.getY());
				        	 		menu.setLastX(evenement.getX());
				        	 		menu.setLastY(evenement.getY());*/
								double ancr[] = InterfaceJava.fctC_convertirCoordonneesSouris2(evenement.getX(), evenement.getY());
								menu.setAncrageXd(ancr[0]);
								menu.setAncrageYd(ancr[1]);
								menu.setLastXd(ancr[0]);
								menu.setLastYd(ancr[1]);
								placer_ = true;
							}
							else
							{
								double p2[] = InterfaceJava.fctC_convertirCoordonneesSouris2(evenement.getX(), evenement.getY());
								if(InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_contour.ordinal(), menu.getLastXd(), menu.getLastYd(),p2[0], p2[1]) == true)
								{		        	 				
									menu.setLastXd(p2[0]);
									menu.setLastYd(p2[1]);
								}
								/*menu.setLastX(evenement.getX());
				        	 		menu.setLastY(evenement.getY());*/

							}
							break;
						case 7:
							if (portal_ == false)
							{
								InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_portal.ordinal(), evenement.getX(), evenement.getY(), 0, 0);
							}
							else
							{
								InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_portal.ordinal(), evenement.getX(), evenement.getY(), 0, 0);
								menu.etatSouris = EtatSouris.ES_aucun;
							}
							break;
						}
						break;

					case 3 : //Selectionner
						menu.setAncrageX(evenement.getX());
						menu.setAncrageY(evenement.getY());
						menu.setLastX(evenement.getX());
						menu.setLastY(evenement.getY());
						InterfaceJava.arretMinuterie_ = true;
						break;

					}
				}
				else if(evenement.getButton() == MouseEvent.BUTTON3)
				{
					boutonLibre = true;
					lastTournerX = evenement.getX();
					lastTournerY = evenement.getY();
					menu.setClick(evenement.getButton());
					switch(menu.etatSouris.ordinal())
					{
					case 0 : // aucun
						InterfaceJava.fctC_selectionClick( evenement.getX(), evenement.getY(),0);
						break;

					case 1 : //ZoomElastique
						menu.setAncrageX(evenement.getX());
						menu.setAncrageY(evenement.getY());
						menu.setLastX(evenement.getX());
						menu.setLastY(evenement.getY());
						System.out.println("Zoom Elastique Arrière (Droit)");

						// Arrête la minuterie pour que le rectange puisse s'afficher
						InterfaceJava.arretMinuterie_ = true;
						//fctC pour initialiser rect elastique
						InterfaceJava.fctC_initialiserRectangleElastique(menu.getAncrageX(), menu.getAncrageY());
						break;

					case 2 : //Placer
						switch (menu.etatSourisObjets.ordinal())
						{
						case 6:
							InterfaceJava.fctC_creationObject(EtatSourisObjets.ESO_contour.ordinal(), menu.getAncrageXd(), menu.getAncrageYd(), menu.getLastXd(), menu.getLastYd());

							break;
						}
						menu.etatSouris = EtatSouris.ES_aucun;
						break;

					case 3 : //Selectionner
						break;
					}
				}
				lastTournerX = evenement.getX();
				lastTournerY = evenement.getY();
			}

			@Override
			public void mouseClicked(MouseEvent e) {
				//  Auto-generated method stub

			}

			/**
			 * Cette fonction s'occupe des événements générés lorsque l'on relache un bouton de la souris
			 * 
			 * @param   evenement   L'événement correspondant à l'action.
			 * 
			 */
			@Override
			public void mouseReleased(MouseEvent evenement) {
				int modeSelection = 0;
				if(evenement.isControlDown() && evenement.getButton() == MouseEvent.BUTTON1)
				{
					System.out.println("ctrl + click");
					modeSelection = 1;
				}

				if(menu.getQuelClick() == 1)
				{
					switch(menu.etatSouris.ordinal())
					{
					case 0 : // aucun
						break;

					case 1 : //ZoomElastique
						menu.setCoin2X(evenement.getX());
						menu.setCoin2Y(evenement.getY());

						//fctC pour terminer le rectangle elastique
						InterfaceJava.fctC_terminerRectangleElastique(menu.getAncrageX(), menu.getAncrageY(), menu.getCoin2X(), menu.getCoin2Y());
						// Repart la minuterie pour continuer l'affichage
						InterfaceJava.arretMinuterie_ = false;
						//fctC pour faire le zomm Élastique
						InterfaceJava.fctC_zoomerInElastique(menu.getAncrageX(), menu.getAncrageY(), menu.getCoin2X(), menu.getCoin2Y());
						break;

					case 2 : //Placer
						//placer_ = true;
						break;

					case 3 : //Selectionner Click
						InterfaceJava.fctC_selectionClick( evenement.getX(), evenement.getY(),modeSelection);
						InterfaceJava.arretMinuterie_=false;
						break;
					case 4 : //Selectionner Rectangle
						menu.setCoin2X(evenement.getX());
						menu.setCoin2Y(evenement.getY());
						InterfaceJava.fctC_terminerRectangleElastique(menu.getAncrageX(), menu.getAncrageY(), menu.getCoin2X(), menu.getCoin2Y());
						InterfaceJava.arretMinuterie_ = false;
						InterfaceJava.fctC_selectionRectangle(menu.getAncrageX(), menu.getAncrageY(), menu.getCoin2X(), menu.getCoin2Y());
						menu.etatSouris = EtatSouris.ES_selectionner;
						break;
					}
				}
				else if(menu.getQuelClick() == 3)
				{
					switch(menu.etatSouris.ordinal())
					{
					case 0 : // aucun
					if(placer_ == false)
					{
						int info[] = new int[5];
						info = InterfaceJava.fctC_recevoirInformation();
						if(info[2] == -1)
						{

						}
						else
						{
							boiteDialogueInformations(info[0], info[1], info[2], info[3], info[4]);	
						}
					}
					else
					{
						placer_ = false;
					}
					break;

					case 1 : //ZoomElastique
						menu.setCoin2X(evenement.getX());
						menu.setCoin2Y(evenement.getY());

						//fctC pour terminer le rectangle elastique
						InterfaceJava.fctC_terminerRectangleElastique(menu.getAncrageX(), menu.getAncrageY(), menu.getCoin2X(), menu.getCoin2Y());
						// Repart la minuterie pour continuer l'affichage
						InterfaceJava.arretMinuterie_ = false;
						//fctC pour faire le zomm Élastique
						InterfaceJava.fctC_zoomerOutElastique(menu.getAncrageX(), menu.getAncrageY(), menu.getCoin2X(), menu.getCoin2Y());
						break;

					case 2 : //Placer

						break;

					case 3 : //Selectionner
						int info2[] = new int[5];
						info2 = InterfaceJava.fctC_recevoirInformation();
						if(info2[2] == -1)
						{

						}
						else
						{
							boiteDialogueInformations(info2[0], info2[1], info2[2], info2[3], info2[4]);	
						}
						break;
					}
				}
				if(evenement.getButton() == MouseEvent.BUTTON3)
					boutonLibre = false;
				
				lastTournerX = evenement.getX();
				lastTournerY = evenement.getY();
			}

			@Override
			public void mouseEntered(MouseEvent e) {
				//  Auto-generated method stub

			}
			@Override
			public void mouseExited(MouseEvent e) {
				//  Auto-generated method stub

			}

		});

		//Ajoute un écouteur de mouvement dans le canvas qui retourne un événement lorsque la souris est bougé sur le canvas
		InterfaceJava.canvas_.addMouseMotionListener(new MouseAdapter() {
			@Override
			public void mouseMoved(MouseEvent evenement){

				int pos[] = InterfaceJava.fctC_convertirCoordonneesSouris(evenement.getX(), evenement.getY());
				menu.position.setText("Coordonnées virtuelles de la souris : (X,Y) (" + pos[0] + "," + pos[1] + ")   " + "Coordonnées de cloture de la souris : (X,Y) (" + evenement.getX() + "," + evenement.getY() + ")");
							
				lastTournerX = evenement.getX();
				lastTournerY = evenement.getY();
			}
		});

		/**
		 * Cette fonction s'occupe des événements générés lorsque l'on bouge la souris
		 * 
		 */
		//Ajout d'un gestionnaire d'évenements de mouvements de souris
		InterfaceJava.canvas_.addMouseMotionListener(new MouseAdapter() {  
			@Override
			public void mouseDragged(MouseEvent evenement){

	    		  	if(menu.getQuelClick() == 1)
	    		  	{
		        		switch(menu.etatSouris.ordinal())
			        	{
			        		case 0 : // aucun
			    		  		//calculer le déplacement nécessaire
				         	    int newX = (evenement.getX() - menu.getLastX());  
				         	    int newY =  (evenement.getY() - menu.getLastY());
				         	  
				         	    InterfaceJava.fctC_deplacerXY(-newX,newY);   
				         	     
				         	    menu.setLastX(evenement.getX());
				         	    menu.setLastY(evenement.getY());
			        			break;
			        	 	
			        	 	case 1 : //ZoomElastique
			        	 		menu.setCoin2X(evenement.getX());
			    		  		menu.setCoin2Y(evenement.getY());
			    		  		// Appel la mise à jour du rectangle poitillé qui montre la zone du zoom
			    		  		InterfaceJava.fctC_mettreAJourRectangleElastique(menu.getAncrageX(), menu.getAncrageY(), menu.getLastX(), menu.getLastY() , menu.getCoin2X(), menu.getCoin2Y());
			    		  		menu.setLastX(evenement.getX());
			    		  		menu.setLastY(evenement.getY());
			        	 		break;
			        	 		
			        	 	case 2 : //Placer
			        	 		break;
			        	 		
			        	 	case 3 : //Selectionner
			        	 		InterfaceJava.fctC_initialiserRectangleElastique(evenement.getX(), evenement.getY());
			        	 	case 4:
			        	 		menu.etatSouris = EtatSouris.ES_selectionnerRectangle;
			        	 		menu.setCoin2X(evenement.getX());
			    		  		menu.setCoin2Y(evenement.getY());
			    		  		// Appel la mise à jour du rectangle poitillé qui montre la zone du zoom
			    		  		InterfaceJava.fctC_mettreAJourRectangleElastique(menu.getAncrageX(), menu.getAncrageY(), menu.getLastX(), menu.getLastY() , menu.getCoin2X(), menu.getCoin2Y());
			    		  		menu.setLastX(evenement.getX());
			    		  		menu.setLastY(evenement.getY());
			        	 		break;
			        	 	case 5:
			        	 		menu.setCoin2X(evenement.getX());
			    		  		menu.setCoin2Y(evenement.getY());
			        	 		InterfaceJava.fctC_deplacementSelection(menu.getLastX(), menu.getLastY(), evenement.getX(), evenement.getY());
			        	 		menu.setLastX(evenement.getX());
			    		  		menu.setLastY(evenement.getY());
			        	 		break;
			        	 	case 6:
			        	 		if(evenement.getY() > pointAvantSourisY_) {
			                        
			                         //zoom out
			                    	InterfaceJava.fctC_zoomOut((evenement.getY() - pointAvantSourisY_) * ZOOM_SOURIS_POURCENTAGE);
			                           
			                        //assigner la nouvelle valeur verticale de la souris
			                        pointAvantSourisY_ = evenement.getY();
			                      }
			                       //si la souris est déplacé verticalement vers le haut en appuyant sur le bouton droit de la souris
			                      else if(evenement.getY() < pointAvantSourisY_) {
			                          
			                          //zoom in
			                    	  InterfaceJava.fctC_zoomIn((pointAvantSourisY_ - evenement.getY()) * ZOOM_SOURIS_POURCENTAGE);
			                          
			                          //assigner la nouvelle valeur verticale de la souris
			                          pointAvantSourisY_ = evenement.getY();
			                      }
			        	 		break;
			        	 		
			        	}
	    		  	}
	    		  	else if(menu.getQuelClick() == 3)
	    		  	{
		        		 switch(menu.etatSouris.ordinal())
			        	 {
			        	 	case 0 : // aucun
			        	 		break;
			        	 	
			        	 	case 1 : //ZoomElastique
			        	 		menu.setCoin2X(evenement.getX());
			    		  		menu.setCoin2Y(evenement.getY());
			    		  		// Appel la mise à jour du rectangle poitillé qui montre la zone du zoom
			    		  		InterfaceJava.fctC_mettreAJourRectangleElastique(menu.getAncrageX(), menu.getAncrageY(), menu.getLastX(), menu.getLastY() , menu.getCoin2X(), menu.getCoin2Y());
			    		  		menu.setLastX(evenement.getX());
			    		  		menu.setLastY(evenement.getY());
			        	 		break;
			        	 		
			        	 	case 2 : //Placer
			        	 		break;
			        	 		
			        	 	case 3 : //Selectionner
			        	 		break;
			        	 }
	    		  	}
	    		  	if(boutonLibre == true)
	    		  	{
	    				if(InterfaceJava.fctC_getTypeVue() == 1)
	    				{
	    					int X = evenement.getX();
	    					int Y = evenement.getY();
	    										
	    					InterfaceJava.fctC_tournerCamera((X-lastTournerX), (Y-lastTournerY));
	    				}
	    			}
	    		  	lastTournerX = evenement.getX();
		    	    lastTournerY = evenement.getY();
	    	  }
	      });
	      
		/**
		 * Cette fonction s'occupe des événements générés lorsque l'on utilise la roulette de la souris
		 * 
		 */
		InterfaceJava.canvas_.addMouseWheelListener(new MouseAdapter() {
			@Override
			public void mouseWheelMoved(MouseWheelEvent evenement)
			{
				int rotation = evenement.getWheelRotation(); //Contient le nombre de fois que le wheel a été tourné
				//System.out.println("Roulette");
				if(rotation < 0) //Si le wheel a été tourné vers le haut
				{
					rotation = -1 * rotation; //On mets la rotation en valeur absolue pour avoir le nombre de rotations non signé
					for(int i = 0; i < rotation; i++)
					{
						InterfaceJava.fctC_zoomIn(0);
					}

				}
				else if(rotation > 0) //Si le wheel a été tourné vers le bas
				{
					for(int i = 0; i < rotation; i++)
					{      
						InterfaceJava.fctC_zoomOut(0);
					}
				}
			}
		});

		/**
		 * Cette fonction s'occupe de prendre en compte les changements à la taille du canvas
		 * 
		 */
		InterfaceJava.canvas_.addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent evenement) {
				int widht = InterfaceJava.canvas_.getWidth();
				int height = InterfaceJava.canvas_.getHeight();
				InterfaceJava.fctC_redimensionnerFenetre(widht, height);
			}
		});

		//Ajout d'un gestionnaire d'événements du clavier
		InterfaceJava.canvas_.addKeyListener(new Gestionnaire(menu));

	}

	/**
	 * Envois les informations a la boite de dialogue
	 * 
	 */
	public void boiteDialogueInformations(int X, int Y, int Z, int rotation, int facteur)
	{
		dialogue_ = new Dialog();
		dialogue_.setVisible(true);
		dialogue_.DialogCustom(InterfaceJava.fenetreGeneral_, X, Y, Z, rotation, facteur);
	}

	/**
	 * modifier placer_
	 * 
	 */
	public void setPlacer(boolean placer)
	{
		placer_ = placer;
	}
	//Variables de declaration
	int lastTournerX ;
	int lastTournerY ;
	int pointAvantSourisY_ = 0;
	int pointAvantSourisX_ = 0;
	boolean boutonLibre = false;
	public static final int ZOOM_SOURIS_POURCENTAGE = 3; // pourcentage de Zoom par souris
	private boolean placer_ = false, portal_ = false;
	private Dialog dialogue_;
	private static EtatEditeur instance_;
}