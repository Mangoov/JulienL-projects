package ca.polymtl.inf2990;


import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelListener;

import java.awt.event.MouseWheelEvent;


/**
*
* @author Etienne Vallée
*/
public class EtatJeu implements Etats
{
	/**
	    * Cette fonction ne fait rien pour l'instant.
	    * Elle servira a gérer les événements dans le mode jeu
	    */
	@Override
	public void ajouterGestionnaires(ContexteEtat contexteEtat, final MenuPrincipal menu) 
	{
		//menu = MenuPrincipal.getInstance();
		System.out.println("Jeu");
		
		//menu.getCanvas().addKeyListener(new Gestionnaire(menu));
		
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
					click_ = 1;
					balle = InterfaceJava.fctC_clickBalle(evenement.getX(), evenement.getY());
					
					if(balle == true)
					{
						InterfaceJava.fctC_creerFleche();
					}
	        	 }
	        	 else if(evenement.getButton() == MouseEvent.BUTTON3)
	        	 {
	        		 boutonLibre = true;
	        		 click_ = 3;
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
				
				  if(evenement.getButton() == MouseEvent.BUTTON1)
				  {
					  if(balle == true)
	    		  		{						  
	    		  			InterfaceJava.fctC_effacerFleche();
	    		  			menuPrincipal_.boutonReplay.setEnabled(true);
	    		  			balle = false;
	    		  		}
		     	  }
				  else if(evenement.getButton() == MouseEvent.BUTTON3)
				  {
					  boutonLibre = false;
		     	  }
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
		
		/**
		    * Cette fonction s'occupe des événements générés lorsque l'on bouge la souris
		    * 
		    */
		//Ajout d'un gestionnaire d'évenements de mouvements de souris
		InterfaceJava.canvas_.addMouseMotionListener(new MouseAdapter() {  
	    	  @Override
			public void mouseDragged(MouseEvent evenement){

	    		  	if(click_ == 1)
	    		  	{
	    		  		if(balle == true)
	    		  		{
	    		  			InterfaceJava.fctC_modifierFleche(evenement.getX(), evenement.getY());
	    		  		}
	    		  	}
	    		  	else if(click_ == 3)
	    		  	{
	    		  		
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
		    * Quand la souris est bougée sans de bouton pressé
		    * 
		    */
	
		InterfaceJava.canvas_.addMouseMotionListener(new MouseAdapter() {
			@Override
			public void mouseMoved(MouseEvent evenement){
				
			
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
	}
	//Variables de declaration
	boolean boutonLibre = false;
	int lastTournerX;
    int lastTournerY;
	private int click_;
	private boolean balle = false;
	private MenuPrincipal menuPrincipal_ = MenuPrincipal.getInstance();
}
