package ca.polymtl.inf2990;

import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.WindowConstants;


/**
 *
 * @author Jean-Luc Dubeau
 */
public class Pointage extends javax.swing.JFrame {

	/**
	 * Créer une instance de Pointage
	 */
	public static Pointage getInstance() {
		if (null == instance_) // Si c'est la première fois
		{ 
			instance_ = new Pointage();			
		}
		return instance_;
	}
	
    /** 
     * Initialisation du tableau de pointage
     */
    public void initiationTableauPointage() {
    	
    	setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
    	setSize(575,223);
        setLocationRelativeTo(null);
        setTitle("Pointage");
        
        
        // change l'icone de la fenetre
/*     	BufferedImage image = null;
     	try 
     	{
     		image = ImageIO.read(getClass().getResource("/ca/polymtl/inf2990/icones/Golf_icone.png"));
     	} 
     	catch (IOException e) 
     	{
     		e.printStackTrace();
     	}
     	setIconImage(image);*/
        
        joueur1 = new javax.swing.JLabel();
        joueur2 = new javax.swing.JLabel();
        j1Score1 = new javax.swing.JLabel();
        j1Score2 = new javax.swing.JLabel();
        j1Score3 = new javax.swing.JLabel();
        j1Score4 = new javax.swing.JLabel();
        j1Score5 = new javax.swing.JLabel();
        j1Score6 = new javax.swing.JLabel();
        j1Score7 = new javax.swing.JLabel();
        j1Score8 = new javax.swing.JLabel();
        j1Score9 = new javax.swing.JLabel();
        j1Total = new javax.swing.JLabel();
        j2Score1 = new javax.swing.JLabel();
        j2Score2 = new javax.swing.JLabel();
        j2Score3 = new javax.swing.JLabel();
        j2Score4 = new javax.swing.JLabel();
        j2Score5 = new javax.swing.JLabel();
        j2Score6 = new javax.swing.JLabel();
        j2Score7 = new javax.swing.JLabel();
        j2Score8 = new javax.swing.JLabel();
        j2Score9 = new javax.swing.JLabel();
        j2Total = new javax.swing.JLabel();
        par1 = new javax.swing.JLabel();
        par2 = new javax.swing.JLabel();
        par3 = new javax.swing.JLabel();
        par4 = new javax.swing.JLabel();
        par5 = new javax.swing.JLabel();
        par6 = new javax.swing.JLabel();
        par7 = new javax.swing.JLabel();
        par8 = new javax.swing.JLabel();
        par9 = new javax.swing.JLabel();
        parTotal = new javax.swing.JLabel();
        tableauScore = new javax.swing.JLabel();

        getContentPane().setLayout(null);

        joueur1.setFont(new java.awt.Font("Comic Sans MS", 1, 18)); 
        
        joueur1.setText(menuDeBase_.nomJoueur);
        getContentPane().add(joueur1);
        joueur1.setBounds(8, 60, 91, 20);

        joueur2.setFont(new java.awt.Font("Comic Sans MS", 1, 18));
        joueur2.setText(menuDeBase_.nomJoueur2);
        getContentPane().add(joueur2);
        joueur2.setBounds(8, 105, 91, 20);
        
        ///////////////////////////////
        // Pointage pour le joueur 1 //
        ///////////////////////////////
        
        j1Score1.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 1 && InterfaceJava.joueurCourant_ == 1)
        {
        	joueur1Score1 = InterfaceJava.fctC_obtenirFrappes();
        }
        j1Score1.setText("" + joueur1Score1);
        getContentPane().add(j1Score1);
        j1Score1.setBounds(125, 60, 20, 20);
        
        j1Score2.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 2 && InterfaceJava.joueurCourant_ == 1)
        	joueur1Score2 = InterfaceJava.fctC_obtenirFrappes();
        j1Score2.setText("" + joueur1Score2);
        getContentPane().add(j1Score2);
        j1Score2.setBounds(168, 60, 20, 20);

        j1Score3.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 3 && InterfaceJava.joueurCourant_ == 1)
        	joueur1Score3 = InterfaceJava.fctC_obtenirFrappes();
        j1Score3.setText(""+ joueur1Score3);
        getContentPane().add(j1Score3);
        j1Score3.setBounds(208, 60, 20, 20);

        j1Score4.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 4 && InterfaceJava.joueurCourant_ == 1)
        	joueur1Score4 = InterfaceJava.fctC_obtenirFrappes();
        j1Score4.setText(""+ joueur1Score4);
        getContentPane().add(j1Score4);
        j1Score4.setBounds(246, 60, 20, 20);

        j1Score5.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 5 && InterfaceJava.joueurCourant_ == 1)
        	joueur1Score5 = InterfaceJava.fctC_obtenirFrappes();
        j1Score5.setText("" + joueur1Score5);
        getContentPane().add(j1Score5);
        j1Score5.setBounds(285, 60, 20, 20);

        j1Score6.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 6 && InterfaceJava.joueurCourant_ == 1)
        	joueur1Score6 = InterfaceJava.fctC_obtenirFrappes();
        j1Score6.setText("" + joueur1Score6);
        getContentPane().add(j1Score6);
        j1Score6.setBounds(328, 60, 20, 20);

        j1Score7.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 7 && InterfaceJava.joueurCourant_ == 1)
        	joueur1Score7 = InterfaceJava.fctC_obtenirFrappes();
        j1Score7.setText("" + joueur1Score7);
        getContentPane().add(j1Score7);
        j1Score7.setBounds(368, 60, 20, 20);

        j1Score8.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 8 && InterfaceJava.joueurCourant_ == 1)
        	joueur1Score8 = InterfaceJava.fctC_obtenirFrappes();
        j1Score8.setText("" + joueur1Score8);
        getContentPane().add(j1Score8);
        j1Score8.setBounds(408, 60, 20, 20);

        j1Score9.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 9 && InterfaceJava.joueurCourant_ == 1)
        	joueur1Score9 = InterfaceJava.fctC_obtenirFrappes();
        j1Score9.setText("" + joueur1Score9);
        getContentPane().add(j1Score9);
        j1Score9.setBounds(448, 60, 20, 20);

        j1Total.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        joueur1Total = joueur1Score1 + joueur1Score2 + joueur1Score3 + joueur1Score4 + joueur1Score5 + joueur1Score6 + joueur1Score7 + joueur1Score8 + joueur1Score9;
        j1Total.setText("" + joueur1Total);
        getContentPane().add(j1Total);
        j1Total.setBounds(500, 60, 40, 20);

        ///////////////////////////////
        // Pointage pour le joueur 2 //
        ///////////////////////////////
        
        j2Score1.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 1 && InterfaceJava.joueurCourant_ == 2)
        	joueur2Score1 = InterfaceJava.fctC_obtenirFrappes();
        j2Score1.setText("" + joueur2Score1);
        getContentPane().add(j2Score1);
        j2Score1.setBounds(125, 105, 20, 20);

        j2Score2.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 2 && InterfaceJava.joueurCourant_ == 2)
        	joueur2Score2 = InterfaceJava.fctC_obtenirFrappes();
        j2Score2.setText("" + joueur2Score2);
        getContentPane().add(j2Score2);
        j2Score2.setBounds(168, 105, 20, 20);

        j2Score3.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 3 && InterfaceJava.joueurCourant_ == 2)
        	joueur2Score3 = InterfaceJava.fctC_obtenirFrappes();
        j2Score3.setText("" + joueur2Score3);
        getContentPane().add(j2Score3);
        j2Score3.setBounds(208, 105, 20, 20);

        j2Score4.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 4 && InterfaceJava.joueurCourant_ == 2)
        	joueur2Score4 = InterfaceJava.fctC_obtenirFrappes();
        j2Score4.setText("" + joueur2Score4);
        getContentPane().add(j2Score4);
        j2Score4.setBounds(246, 105, 20, 20);

        j2Score5.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 5 && InterfaceJava.joueurCourant_ == 2)
        	joueur2Score5 = InterfaceJava.fctC_obtenirFrappes();
        j2Score5.setText("" + joueur2Score5);
        getContentPane().add(j2Score5);
        j2Score5.setBounds(285, 105, 20, 20);

        j2Score6.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 6 && InterfaceJava.joueurCourant_ == 2)
        	joueur2Score6 = InterfaceJava.fctC_obtenirFrappes();
        j2Score6.setText("" + joueur2Score6);
        getContentPane().add(j2Score6);
        j2Score6.setBounds(328, 105, 20, 20);

        j2Score7.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 7 && InterfaceJava.joueurCourant_ == 2)
        	joueur2Score7 = InterfaceJava.fctC_obtenirFrappes();
        j2Score7.setText("" + joueur2Score7);
        getContentPane().add(j2Score7);
        j2Score7.setBounds(368, 105, 20, 20);

        j2Score8.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 8 && InterfaceJava.joueurCourant_ == 2)
        	joueur2Score8 = InterfaceJava.fctC_obtenirFrappes();
        j2Score8.setText("" + joueur2Score8);
        getContentPane().add(j2Score8);
        j2Score8.setBounds(408, 105, 20, 20);

        j2Score9.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        if(InterfaceJava.map == 9 && InterfaceJava.joueurCourant_ == 2)
        	joueur2Score9 = InterfaceJava.fctC_obtenirFrappes();
        j2Score9.setText("" + joueur2Score9);
        getContentPane().add(j2Score9);
        j2Score9.setBounds(448, 105, 20, 20);

        j2Total.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        joueur2Total = joueur2Score1 + joueur2Score2 + joueur2Score3 + joueur2Score4 + joueur2Score5 + joueur2Score6 + joueur2Score7 + joueur2Score8 + joueur2Score9;
        j2Total.setText("" + joueur2Total);
        getContentPane().add(j2Total);
        j2Total.setBounds(500, 105, 40, 20);
        
        ///////////////////////////////
        // Par pour les parcours     //
        ///////////////////////////////
        if(menuDeBase_.tournoiActif_== false)
        {
        par1_ = InterfaceJava.fctC_obtenirPardeMap(menuPrincipal_.nomFichierXml_);
        par2_ = 0;
        par3_ = 0;
        par4_ = 0;
        par5_ = 0;
        par6_ = 0;
        par7_ = 0;
        par8_ = 0;
        par9_ = 0;
        par1.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        par1.setText("" + par1_ );
        getContentPane().add(par1);
        par1.setBounds(125, 150, 20, 20);
        }
        else
        {
	        par1.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
	        if(InterfaceJava.map == 1)
	        	par1_ = InterfaceJava.fctC_obtenirPardeMap(menuDeBase_.mapTournoi[0]);
	        par1.setText("" + par1_ );
	        getContentPane().add(par1);
	        par1.setBounds(125, 150, 20, 20);
	
	        par2.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
	        if(InterfaceJava.map == 2)
	        	par2_ = InterfaceJava.fctC_obtenirPardeMap(menuDeBase_.mapTournoi[1]);
	        par2.setText("" + par2_ );
	        getContentPane().add(par2);
	        par2.setBounds(168, 150, 20, 20);
	
	        par3.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
	        if(InterfaceJava.map == 3)
	        	par3_ = InterfaceJava.fctC_obtenirPardeMap(menuDeBase_.mapTournoi[2]);
	        par3.setText("" + par3_);
	        getContentPane().add(par3);
	        par3.setBounds(208, 150, 20, 20);
	
	        par4.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
	        if(InterfaceJava.map == 4)
	        	par4_ = InterfaceJava.fctC_obtenirPardeMap(menuDeBase_.mapTournoi[3]);
	        par4.setText("" + par4_);
	        getContentPane().add(par4);
	        par4.setBounds(246, 150, 20, 20);
	
	        par5.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
	        if(InterfaceJava.map == 5)
	        	par5_ = InterfaceJava.fctC_obtenirPardeMap(menuDeBase_.mapTournoi[4]);
	        par5.setText("" + par5_);
	        getContentPane().add(par5);
	        par5.setBounds(285, 150, 20, 20);
	
	        par6.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
	        if(InterfaceJava.map == 6)
	        	par6_ = InterfaceJava.fctC_obtenirPardeMap(menuDeBase_.mapTournoi[5]);
	        par6.setText("" + par6_);
	        getContentPane().add(par6);
	        par6.setBounds(328, 150, 20, 20);
	
	        par7.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
	        if(InterfaceJava.map == 7)
	        	par7_ = InterfaceJava.fctC_obtenirPardeMap(menuDeBase_.mapTournoi[6]);
	        par7.setText("" + par7_);
	        getContentPane().add(par7);
	        par7.setBounds(368, 150, 20, 20);
	
	        par8.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
	        if(InterfaceJava.map == 8)
	        	par8_ = InterfaceJava.fctC_obtenirPardeMap(menuDeBase_.mapTournoi[7]);
	        par8.setText("" + par8_);
	        getContentPane().add(par8);
	        par8.setBounds(408, 150, 20, 20);
	
	        par9.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
	        if(InterfaceJava.map == 9)
	        	par9_ = InterfaceJava.fctC_obtenirPardeMap(menuDeBase_.mapTournoi[8]);
	        par9.setText("" + par9_);
	        getContentPane().add(par9);
	        par9.setBounds(448, 150, 20, 20);
        }

        parTotal.setFont(new java.awt.Font("Comic Sans MS", 1, 16));
        parTotal_ = par1_ + par2_ + par3_ + par4_ + par5_ + par6_ + par7_ + par8_ + par9_;
        parTotal.setText("" + parTotal_);
        getContentPane().add(parTotal);
        parTotal.setBounds(500, 150, 40, 20);

        tableauScore.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/tableauScore.png")));
        getContentPane().add(tableauScore);
        tableauScore.setBounds(0, -30, 600, 250);
    }
    
    /** 
     * Effacer les scores
     */
    public static void effacerScore()
    {
    	joueur1Score1 =0;
    	joueur1Score2 =0;
    	joueur1Score3 =0;
    	joueur1Score4 =0;
    	joueur1Score5 =0;
    	joueur1Score6 =0;
    	joueur1Score7 =0;
    	joueur1Score8 =0;
    	joueur1Score9 =0;
    	joueur1Total =0;
    	joueur2Score1 =0;
    	joueur2Score2 =0;
    	joueur2Score3 =0;
    	joueur2Score4 =0;
    	joueur2Score5 =0;
    	joueur2Score6 =0;
    	joueur2Score7 =0;
    	joueur2Score8 =0;
    	joueur2Score9 =0;
    	joueur2Total =0;
    	par1_ = 0;
        par2_ = 0;
        par3_ = 0;
        par4_ = 0;
        par5_ = 0;
        par6_ = 0;
        par7_ = 0;
        par8_ = 0;
        par9_ = 0;
    }
   
    // Variables de declaration
    private javax.swing.JLabel j1Score1, j1Score2, j1Score3, j1Score4, j1Score5, j1Score6, j1Score7, j1Score8, j1Score9, j1Total;
    private javax.swing.JLabel j2Score1, j2Score2, j2Score3, j2Score4, j2Score5, j2Score6, j2Score7, j2Score8, j2Score9, j2Total;
    private javax.swing.JLabel joueur1, joueur2;
    private javax.swing.JLabel par1, par2, par3, par4, par5, par6, par7, par8, par9, parTotal;
    private javax.swing.JLabel tableauScore;
    private static int joueur1Score1, joueur1Score2, joueur1Score3, joueur1Score4, joueur1Score5, joueur1Score6, joueur1Score7, joueur1Score8, joueur1Score9, joueur1Total;
    private static int joueur2Score1, joueur2Score2, joueur2Score3, joueur2Score4, joueur2Score5, joueur2Score6, joueur2Score7, joueur2Score8, joueur2Score9, joueur2Total;
    private static int par1_, par2_, par3_, par4_, par5_, par6_, par7_, par8_, par9_, parTotal_;
    private MenuDeBase menuDeBase_ = MenuDeBase.getInstance();
    private static Pointage instance_;
    private static MenuPrincipal menuPrincipal_ = MenuPrincipal.getInstance();
}
