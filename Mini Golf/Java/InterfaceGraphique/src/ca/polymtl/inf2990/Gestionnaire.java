package ca.polymtl.inf2990;

import java.awt.event.*;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
*
* @author Etienne Vallée
*/
public class Gestionnaire extends KeyAdapter implements ActionListener {
	   
	/**
     * Constructeur qui ne fait qu'assigner le gestionnaire des actions reçues
     * par cet écouteur.
     *
     * @param   gestionnaire   Le gestionnaire des actions reçues par cet
     *                         écouteur.
     */
	float angle = 0;
	   public Gestionnaire(Object gestionnaire) 
	   {
	         gestionnaire_ = gestionnaire;
	   }
	   
	   /**
	    * Implantation de l'interface ActionEvent qui gère les
	    * événements d'actions.
	    *
	    * @param   evenement   L'événement correspondant à l'action.
	    */   
	   public void actionPerformed(ActionEvent evenement) {
	         
	         String nom = evenement.getActionCommand();
	         
	         // On obtient la méthode par réflexion Java.
	         try {
	            Class[] typeParametres = {};
	            Object[] parametres = {};
	            
	            Method methode = gestionnaire_.getClass().getMethod(
	                  nom, typeParametres
	                  );
	            methode.invoke(gestionnaire_, parametres);
	         }
	         catch (NoSuchMethodException ex) {
	            ex.printStackTrace();
	         }
	         catch (IllegalAccessException ex) {
	        	 ex.printStackTrace();
	         }
	         catch (InvocationTargetException ex) {
	        	 ex.printStackTrace();
	         }
	         catch (SecurityException ex) {
	        	 ex.printStackTrace();
	         }
	         
	      }
	   
    /**
    * Implantation de l'interface <code>KeyListener</code> qui gère les
    * événements de tapage d'une touche.
    *
    * @param   evenement   L'événement correspondant à l'action.
    */   
	@Override
	public void keyTyped(KeyEvent evenement) {
        
        String nom = "appuyer_" + evenement.getKeyChar();
       
        // On obtient la méthode par réflexion Java.
        try {
           Class[] typeParametres = {};
         Object[] parametres = {};
           
           Method methode = gestionnaire_.getClass().getMethod(
                 nom, typeParametres
                 );
          
          methode.invoke(gestionnaire_, parametres);
        
        }
        catch (NoSuchMethodException ex) {
           // ...
       }
       catch (IllegalAccessException ex) {
           // ...
        }
        catch (InvocationTargetException ex) {
           // ...
        }
        catch (SecurityException ex) {
           // ...
        }
        
     }
	
	/**
	    * Gère les événement retournés par le clavier lorsque les touches sont appuyées
	    *
	    * @param   evenement   L'événement correspondant à la touche appuyée.
	    */   
	@Override
	public void keyPressed(KeyEvent evenement) 
	{
        if( InterfaceJava.fctC_getTypeVue() == 1 )
        {
            switch(evenement.getKeyCode())
            {
                 case KeyEvent.VK_UP: 
                	 InterfaceJava.fctC_deplacerLibre(0, 10);
                	 break;
                case KeyEvent.VK_DOWN: 
                	InterfaceJava.fctC_deplacerLibre(0, -10);
                	break;
                case KeyEvent.VK_LEFT:
                	InterfaceJava.fctC_deplacerLibre(10, 0);
                	break;
                case KeyEvent.VK_RIGHT: 
                	InterfaceJava.fctC_deplacerLibre(-10, 0);
                	break;
            }
        }
        else if( InterfaceJava.fctC_getTypeVue() == 2 && InterfaceJava.mode_ == "Jeu")
        {
        	switch(evenement.getKeyCode())
            {
                 case KeyEvent.VK_UP: 
                	 InterfaceJava.fctC_deplacerLibre(0, 10);         
                	 break;
                case KeyEvent.VK_DOWN: 
                	InterfaceJava.fctC_deplacerLibre(0, -10);
                	break;
                case KeyEvent.VK_LEFT:
                	InterfaceJava.fctC_orbiterCamera(-2, 0);
                	break;
                case KeyEvent.VK_RIGHT: 
                	InterfaceJava.fctC_orbiterCamera(2, 0);
                	break;
            }
        }
		
		
  	  if(InterfaceJava.mode_ == "Editeur")
  	  {
	  	  switch(evenement.getKeyCode())
	  	  {
	 	   /*
	    	  case KeyEvent.VK_UP :   		   
	    		  	InterfaceJava.fctC_deplacerXY( 0,InterfaceJava.canvas_.getHeight()*1/20);
	        	  	System.out.println("vers le bas");
	        	  	break;
	    	  case KeyEvent.VK_DOWN :   		   
	    		  	InterfaceJava.fctC_deplacerXY( 0,-InterfaceJava.canvas_.getHeight()*1/20);
	    		  	System.out.println("vers le haut");
	      	  		break;
	    	  case KeyEvent.VK_RIGHT :   		   
	    		  	InterfaceJava.fctC_deplacerXY( InterfaceJava.canvas_.getWidth()*1/20,0);
		      	  	System.out.println("vers la droite");
		      	  	break;
	    	  case KeyEvent.VK_LEFT :   		   
	    		  	InterfaceJava.fctC_deplacerXY( -InterfaceJava.canvas_.getWidth()*1/20,0);
		      	  	System.out.println("vers la gauche");
		      	  	break;
		      	  	*/
	    	  case KeyEvent.VK_ADD :  // touche +		   
	    		  	InterfaceJava.fctC_zoomIn(0);
	    		  	System.out.println("Zoom in");
		      	  	break;
	    	  case KeyEvent.VK_SUBTRACT :  // touche -		   
	    		  	InterfaceJava.fctC_zoomOut(0);
	    		  	System.out.println("Zoom out");
		      	  	break;
		  }
  	  }
  	  else
  	  {
    	 info = InterfaceJava.fctC_obtenirToucheClavier();
  		// info[0] : gauche, info[1] : droite, info[2] : haut, info[3] : bas, info[4] espace
  		 if(info[2] == (evenement.getKeyCode()))
		 {
  			InterfaceJava.fctC_modifierFlecheTouche(3);
		 }
  		 else if (info[3] == (evenement.getKeyCode()))
  		 {
  			InterfaceJava.fctC_modifierFlecheTouche(4);
  		 }
  		 else if (info[1] == (evenement.getKeyCode()))
 		 {
  			InterfaceJava.fctC_modifierFlecheTouche(1);
 		 }
  		 else if (info[0] == (evenement.getKeyCode()))
 		 {
  			InterfaceJava.fctC_modifierFlecheTouche(2);
 		 }
  		 else if (info[4] == (evenement.getKeyCode()))
 		 {
  			InterfaceJava.fctC_modifierFlecheTouche(0);
 		 }

  	  }
    }
	
	/**
	    * Gère les événement retournés par le clavier lorsque les touches sont relachées
	    *
	    * @param   evenement   L'événement correspondant à la touche relachée.
	    */   
	@Override
	public void keyReleased(KeyEvent e)
	{
		
	}
	
	//Variables de declaration
	 private Object gestionnaire_;
	 private MenuPrincipal menu_ = MenuPrincipal.getInstance();
	 private Option option_ = new Option();
	 private int info[] = new int[5];
}   
