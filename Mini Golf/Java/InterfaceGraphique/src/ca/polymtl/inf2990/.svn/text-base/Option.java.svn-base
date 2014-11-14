package ca.polymtl.inf2990;

import java.awt.Color;
import java.awt.color.ColorSpace;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.WindowConstants;


//import javax.swing.ImageIcon;

/**
 *
 * @author Jean-Luc Dubeau et Etienne Vallée
 */
public class Option extends javax.swing.JFrame implements KeyListener, ActionListener {

    /** 
     *  Creation du menu option
     */
    public Option() {
        initComponents();
        setLocationRelativeTo(null);  
        instance_ = MenuPrincipal.getInstance();
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        info = InterfaceJava.fctC_obtenirToucheClavier();
        // info1[0] : gauche, info1[1] : droite, info1[2] : haut, info1[3] : bas, info1[4] espace
        info1 = InterfaceJava.fctC_obtenirOptionClavier(); 
        toucheGauche1 = info1[0];
        toucheDroite1 = info1[1];
        toucheHaut1 = info1[2];
        toucheBas1 = info1[3];
        toucheEspace1 = info1[4]; 
        controleHaut.setText(toucheHaut1);
        controleBas.setText(toucheBas1);
        controleGauche.setText(toucheGauche1);
		controleDroite.setText(toucheDroite1);
		controleEspace.setText(toucheEspace1);
    }

    /** 
     * Initialisation du menu d'option du jeu
     */
    private void initComponents() {
    	
    	String temp = "0";

    	// change l'icone de la fenetre
 /*    	BufferedImage image = null;
     	try 
     	{
     		image = ImageIO.read(getClass().getResource("/ca/polymtl/inf2990/icones/Golf_icone.png"));
     	} 
     	catch (IOException e) 
     	{
     		e.printStackTrace();
     	}
     	setIconImage(image);*/
    	
        jPanel2 = new javax.swing.JPanel();
        jTabbedPane1 = new javax.swing.JTabbedPane();
        parametreJeu = new javax.swing.JPanel();
        CoefficientFrictionSol = new javax.swing.JLabel();
        
        temp = Integer.toString(InterfaceJava.fctC_obtenirFrictionSol());
        controleCoefficientFrictionSol = new javax.swing.JTextField(temp);
        
        coefficientFrictionSable = new javax.swing.JLabel();
        
        temp = Integer.toString(InterfaceJava.fctC_obtenirFrictionSable());
        controleCoefficientFrictionSable = new javax.swing.JTextField(temp);
        
        jSeparator1 = new javax.swing.JSeparator();
        coefficientRebondMurs = new javax.swing.JLabel();
        
        temp = Integer.toString(InterfaceJava.fctC_obtenirRebondMur());
        controleCoefficientRebondMurs = new javax.swing.JTextField(temp);
        
        jSeparator2 = new javax.swing.JSeparator();
        accelerationBonus = new javax.swing.JLabel();
          
        temp = Integer.toString(InterfaceJava.fctC_obtenirAccelerationBonus());
        controleAccelerationBonus = new javax.swing.JTextField(temp);
        	
        jSeparator3 = new javax.swing.JSeparator();
        
        tailleZoneEditionHauteur = new javax.swing.JLabel();
                
        temp = Integer.toString(InterfaceJava.fctC_obtenirTailleEditionHauteur());
        controleTailleZoneEditionHauteur = new javax.swing.JTextField(temp);
        
        tailleZoneEditionLargeur = new javax.swing.JLabel();
        
        temp = Integer.toString(InterfaceJava.fctC_obtenirTailleEditionLargeur());
        controleTailleZoneEditionLargeur = new javax.swing.JTextField(temp);
        
        controleBaton = new javax.swing.JPanel();
        
        haut = new javax.swing.JLabel();
        controleHaut = new javax.swing.JTextField(toucheHaut1);
        controleHaut.addKeyListener(this);
		controleHaut.setEditable(false);
		controleHaut.setBackground(new JTextField().getBackground());
		controleHaut.addFocusListener(new FocusAdapter() {
			public void focusGained(FocusEvent e){
				controleHaut.setBackground(Color.RED);
				controleBas.setBackground(new JTextField().getBackground());
				controleGauche.setBackground(new JTextField().getBackground());
				controleDroite.setBackground(new JTextField().getBackground());
				controleEspace.setBackground(new JTextField().getBackground());
			}
		});
        
        bas = new javax.swing.JLabel();
        controleBas = new javax.swing.JTextField(toucheBas1);
        controleBas.addKeyListener(this);
        controleBas.setEditable(false);
        controleBas.setBackground(new JTextField().getBackground());
        controleBas.addFocusListener(new FocusAdapter() {
			public void focusGained(FocusEvent e){
				controleHaut.setBackground(new JTextField().getBackground());
				controleBas.setBackground(Color.RED);
				controleGauche.setBackground(new JTextField().getBackground());
				controleDroite.setBackground(new JTextField().getBackground());
				controleEspace.setBackground(new JTextField().getBackground());
			}
		});
        
        gauche = new javax.swing.JLabel();
        controleGauche = new javax.swing.JTextField(toucheGauche1);
        controleGauche.addKeyListener(this);
        controleGauche.setEditable(false);
        controleGauche.setBackground(new JTextField().getBackground());
        controleGauche.addFocusListener(new FocusAdapter() {
			public void focusGained(FocusEvent e){
				controleHaut.setBackground(new JTextField().getBackground());
				controleBas.setBackground(new JTextField().getBackground());
				controleGauche.setBackground(Color.RED);
				controleDroite.setBackground(new JTextField().getBackground());
				controleEspace.setBackground(new JTextField().getBackground());
			}
		});
        
        droite = new javax.swing.JLabel();
        controleDroite = new javax.swing.JTextField(toucheDroite1);
        controleDroite.addKeyListener(this);
        controleDroite.setEditable(false);
        controleDroite.setBackground(new JTextField().getBackground());
        controleDroite.addFocusListener(new FocusAdapter() {
			public void focusGained(FocusEvent e){
				controleHaut.setBackground(new JTextField().getBackground());
				controleBas.setBackground(new JTextField().getBackground());
				controleGauche.setBackground(new JTextField().getBackground());
				controleDroite.setBackground(Color.RED);
				controleEspace.setBackground(new JTextField().getBackground());
			}
		});
        
        joypad = new javax.swing.JLabel();
        
        frapper = new javax.swing.JLabel();
        controleEspace = new javax.swing.JTextField(toucheEspace1);
        controleEspace.addKeyListener(this);
        controleEspace.setEditable(false);
        controleEspace.setBackground(new JTextField().getBackground());
        controleEspace.addFocusListener(new FocusAdapter() {
			public void focusGained(FocusEvent e){
				controleHaut.setBackground(new JTextField().getBackground());
				controleBas.setBackground(new JTextField().getBackground());
				controleGauche.setBackground(new JTextField().getBackground());
				controleDroite.setBackground(new JTextField().getBackground());
				controleEspace.setBackground(Color.RED);
			}
		});
        
        ok = new javax.swing.JButton();
        annuler = new javax.swing.JButton();

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 100, Short.MAX_VALUE)
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 100, Short.MAX_VALUE)
        );

        setTitle("Option");

        CoefficientFrictionSol.setText("Coefficients de friction du sol :");

        coefficientFrictionSable.setText("Coefficients de friction du sable :");

        coefficientRebondMurs.setText("Coefficients de rebond des murs :");

        accelerationBonus.setText("Accélération du bonus :");

        tailleZoneEditionHauteur.setText("Taille de la hauteur de la zone d'édition :");

        tailleZoneEditionLargeur.setText("Taille de la largeur de la zone d'édition :");

        javax.swing.GroupLayout parametreJeuLayout = new javax.swing.GroupLayout(parametreJeu);
        parametreJeu.setLayout(parametreJeuLayout);
        parametreJeuLayout.setHorizontalGroup(
            parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(parametreJeuLayout.createSequentialGroup()
                .addGap(21, 21, 21)
                .addGroup(parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(CoefficientFrictionSol, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(coefficientFrictionSable, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(coefficientRebondMurs, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(accelerationBonus, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(tailleZoneEditionHauteur, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(tailleZoneEditionLargeur, javax.swing.GroupLayout.Alignment.TRAILING))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.CENTER)
                    .addComponent(controleCoefficientRebondMurs, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(controleAccelerationBonus, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(controleTailleZoneEditionHauteur, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(controleCoefficientFrictionSable, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(controleCoefficientFrictionSol, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(controleTailleZoneEditionLargeur, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(135, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, parametreJeuLayout.createSequentialGroup()
                .addContainerGap(83, Short.MAX_VALUE)
                .addGroup(parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jSeparator3, javax.swing.GroupLayout.PREFERRED_SIZE, 305, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jSeparator2, javax.swing.GroupLayout.PREFERRED_SIZE, 305, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(jSeparator1, javax.swing.GroupLayout.PREFERRED_SIZE, 305, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(71, 71, 71))
        );
        parametreJeuLayout.setVerticalGroup(
            parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(parametreJeuLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(CoefficientFrictionSol)
                    .addComponent(controleCoefficientFrictionSol, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(coefficientFrictionSable)
                    .addComponent(controleCoefficientFrictionSable, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSeparator1, javax.swing.GroupLayout.PREFERRED_SIZE, 6, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(controleCoefficientRebondMurs, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(coefficientRebondMurs))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jSeparator2, javax.swing.GroupLayout.PREFERRED_SIZE, 11, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(accelerationBonus)
                    .addComponent(controleAccelerationBonus, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jSeparator3, javax.swing.GroupLayout.PREFERRED_SIZE, 11, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(tailleZoneEditionHauteur)
                    .addComponent(controleTailleZoneEditionHauteur, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addGroup(parametreJeuLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(tailleZoneEditionLargeur)
                    .addComponent(controleTailleZoneEditionLargeur, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(14, Short.MAX_VALUE))
        );

        jTabbedPane1.addTab("Paramètres du jeu", parametreJeu);

        haut.setText("Haut :");

        controleHaut.setToolTipText("Augmente l'angle de frappe.");

        bas.setText("Bas :");

        controleBas.setToolTipText("Diminue l'angle de frappe.");

        gauche.setText("Gauche :");

        controleGauche.setToolTipText("Tourne le bâton en sens anti-horaire.");

        droite.setText("Droite :");

        controleDroite.setToolTipText("Tourne le bâton en sens horaire.");

        joypad.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/joypad.png")));

        frapper.setText("Frapper :");

        controleEspace.setToolTipText("Frappe la balle.");

        javax.swing.GroupLayout controleBatonLayout = new javax.swing.GroupLayout(controleBaton);
        controleBaton.setLayout(controleBatonLayout);
        controleBatonLayout.setHorizontalGroup(
            controleBatonLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(controleBatonLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(frapper)
                .addGap(10, 10, 10)
                .addComponent(controleEspace, javax.swing.GroupLayout.PREFERRED_SIZE, 85, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(309, Short.MAX_VALUE))
            .addGroup(controleBatonLayout.createSequentialGroup()
                .addContainerGap(10, Short.MAX_VALUE)
                .addComponent(gauche)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 10, Short.MAX_VALUE)
                .addComponent(controleGauche, javax.swing.GroupLayout.PREFERRED_SIZE, 84, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(14, 14, 14)
                .addComponent(joypad, javax.swing.GroupLayout.PREFERRED_SIZE, 117, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(droite)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(controleDroite, javax.swing.GroupLayout.PREFERRED_SIZE, 84, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(51, 51, 51))
            .addGroup(controleBatonLayout.createSequentialGroup()
                .addGap(140, 140, 140)
                .addComponent(haut)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(controleHaut, javax.swing.GroupLayout.PREFERRED_SIZE, 84, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(195, Short.MAX_VALUE))
            .addGroup(controleBatonLayout.createSequentialGroup()
                .addGap(145, 145, 145)
                .addComponent(bas)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(controleBas, javax.swing.GroupLayout.PREFERRED_SIZE, 84, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(196, Short.MAX_VALUE))
        );
        controleBatonLayout.setVerticalGroup(
            controleBatonLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(controleBatonLayout.createSequentialGroup()
                .addGroup(controleBatonLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(controleBatonLayout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(controleBatonLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(haut)
                            .addComponent(controleHaut, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(controleBatonLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(joypad)
                            .addGroup(controleBatonLayout.createSequentialGroup()
                                .addGap(52, 52, 52)
                                .addGroup(controleBatonLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                    .addComponent(controleGauche, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addComponent(gauche)))))
                    .addGroup(controleBatonLayout.createSequentialGroup()
                        .addGap(82, 82, 82)
                        .addGroup(controleBatonLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(controleDroite, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(droite))))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(controleBatonLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(bas)
                    .addComponent(controleBas, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 30, Short.MAX_VALUE)
                .addGroup(controleBatonLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(controleEspace, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(frapper))
                .addContainerGap())
        );

        jTabbedPane1.addTab("Contrôle du bâton", controleBaton);

        ok.setText("OK");
        ok.addActionListener(new java.awt.event.ActionListener() {
            @Override
			public void actionPerformed(java.awt.event.ActionEvent evt) {
                okActionPerformed(evt);
            }
        });

        annuler.setText("Annuler");
        annuler.addActionListener(new java.awt.event.ActionListener() {
            @Override
			public void actionPerformed(java.awt.event.ActionEvent evt) {
                annulerActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(ok, javax.swing.GroupLayout.PREFERRED_SIZE, 104, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(annuler, javax.swing.GroupLayout.DEFAULT_SIZE, 120, Short.MAX_VALUE))
                    .addComponent(jTabbedPane1, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.PREFERRED_SIZE, 464, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap())
        );

        layout.linkSize(javax.swing.SwingConstants.HORIZONTAL, new java.awt.Component[] {annuler, ok});

        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addComponent(jTabbedPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 271, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(ok)
                    .addComponent(annuler))
                .addContainerGap())
        );

        pack();
    }

    /** 
     * Gestion du bouton OK
     */
    private void okActionPerformed(java.awt.event.ActionEvent evt) {                                   
    // TODO add your handling code here:
    	System.out.println("OK");
		InterfaceJava.fctC_modifierFrictionSol(Integer.parseInt(controleCoefficientFrictionSol.getText()));
		InterfaceJava.fctC_modifierFrictionSable(Integer.parseInt(controleCoefficientFrictionSable.getText()));
		
		rebondMur = Integer.parseInt(controleCoefficientRebondMurs.getText());
		if(rebondMur>= 0 && rebondMur <= 100)
			InterfaceJava.fctC_modifierRebondMur(Integer.parseInt(controleCoefficientRebondMurs.getText()));
		else
			JOptionPane.showMessageDialog(null,"Les rebonds des murs doivent être entre 0 et 100 vaut changement du rebond ne seront pas pris en compte.", "Erreur", JOptionPane.WARNING_MESSAGE);
		
		acBonus = Integer.parseInt(controleAccelerationBonus.getText());
		if(acBonus>= 150 && acBonus <= 300)
			InterfaceJava.fctC_modifierAccelerationBonus(Integer.parseInt(controleAccelerationBonus.getText()));
		else
			JOptionPane.showMessageDialog(null,"L'accélération du bonus doit être entre 150 et 300 vaut changement de bonus ne seront pas pris en compte.", "Erreur", JOptionPane.WARNING_MESSAGE);
		
		InterfaceJava.fctC_modifierTailleEditionHauteur(Integer.parseInt(controleTailleZoneEditionHauteur.getText()));
		InterfaceJava.fctC_modifierTailleEditionLargeur(Integer.parseInt(controleTailleZoneEditionLargeur.getText()));
		InterfaceJava.fctC_modifierToucheClavier(info[0], info[1], info[2], info[3], info[4]);
		InterfaceJava.fctC_modifierOptionClavier(toucheGauche1, toucheDroite1, toucheHaut1, toucheBas1, toucheEspace1); 
		InterfaceJava.fctC_forcerSauvergardeConfig();
		dispose();
    }                                  

    /** 
     * Gestion du bouton Annuler
     */
    private void annulerActionPerformed(java.awt.event.ActionEvent evt) {                                        
    	dispose();
    }   

//Variables de declaration
private javax.swing.JLabel CoefficientFrictionSol;
private javax.swing.JLabel accelerationBonus;
private javax.swing.JButton annuler;
private javax.swing.JLabel bas;
private javax.swing.JLabel coefficientFrictionSable;
private javax.swing.JLabel coefficientRebondMurs;
private javax.swing.JTextField controleAccelerationBonus;
private javax.swing.JTextField controleBas;
private javax.swing.JPanel controleBaton;
private javax.swing.JTextField controleCoefficientFrictionSable;
private javax.swing.JTextField controleCoefficientFrictionSol;
private javax.swing.JTextField controleCoefficientRebondMurs;
private javax.swing.JTextField controleDroite;
private javax.swing.JTextField controleEspace;
private javax.swing.JTextField controleGauche;
private javax.swing.JTextField controleHaut;
private javax.swing.JTextField controleTailleZoneEditionHauteur;
private javax.swing.JTextField controleTailleZoneEditionLargeur;
private javax.swing.JLabel droite;
private javax.swing.JLabel frapper;
private javax.swing.JLabel gauche;
private javax.swing.JLabel haut;
private javax.swing.JPanel jPanel2;
private javax.swing.JSeparator jSeparator1;
private javax.swing.JSeparator jSeparator2;
private javax.swing.JSeparator jSeparator3;
private javax.swing.JTabbedPane jTabbedPane1;
private javax.swing.JLabel joypad;
private javax.swing.JButton ok;
private javax.swing.JPanel parametreJeu;
private javax.swing.JLabel tailleZoneEditionHauteur;
private javax.swing.JLabel tailleZoneEditionLargeur;
private String toucheGauche1, toucheDroite1, toucheHaut1, toucheBas1, toucheEspace1;
public int toucheGauche, toucheDroite, toucheHaut, toucheBas, toucheEspace;
private static MenuPrincipal instance_;
protected int info[] = new int[5];
private String info1[] = new String[5];
private static int rebondMur, acBonus;

@Override
public void keyTyped(KeyEvent e) {
	
}

/** 
 * Changer les touche dans les parametres du baton
 */
@Override
public void keyPressed(KeyEvent e) {
	// TODO Auto-generated method stub
	// info[0] : gauche, info[1] : droite, info[2] : haut, info[3] : bas, info[4] espace
	
	if(e.getKeyCode()!= 69 && e.getKeyCode() != 74)
	{
		if(e.getComponent() == controleHaut)
		{
			info[2] = e.getKeyCode();
			System.out.println(info[2]);
			toucheHaut = info[2];
			toucheHaut1 = KeyEvent.getKeyText(info[2]);
			controleHaut.setText(toucheHaut1);
		}
		else if(e.getComponent() == controleBas)
		{
			info[3] = e.getKeyCode();
			toucheBas = info[3];
			toucheBas1 = KeyEvent.getKeyText(info[3]);
			controleBas.setText(toucheBas1);
		}
		else if(e.getComponent() == controleGauche)
		{
			info[0] = e.getKeyCode();
			toucheGauche = info[0];
			toucheGauche1 = KeyEvent.getKeyText(info[0]);
			controleGauche.setText(toucheGauche1);
		}
		else if(e.getComponent() == controleDroite)
		{
			info[1] = e.getKeyCode();
			toucheDroite = info[1];
			toucheDroite1 = KeyEvent.getKeyText(info[1]);
			controleDroite.setText(toucheDroite1);
		}
		else if(e.getComponent() == controleEspace)
		{
			info[4] = e.getKeyCode();
			toucheEspace = info[4];
			toucheEspace1 = KeyEvent.getKeyText(info[4]);
			controleEspace.setText(toucheEspace1);
		}
	}
	else
		JOptionPane.showMessageDialog(null, "Les touches J et E son déjà utilisées pour d'autres raccourcis." + "\n" + "                 Veuiller choisir une autre touche.");
}

@Override
public void keyReleased(KeyEvent e) {
	// TODO Auto-generated method stub

}

@Override
public void actionPerformed(ActionEvent e) {
	// TODO Auto-generated method stub
	
}
}
