package ca.polymtl.inf2990;
import javax.swing.*;

import java.awt.*;
import java.awt.event.WindowListener;

/**
*
* @author Etienne Vallée
*/
public class Dialog extends JDialog
{
	/** 
     * Initialisation de la fenetre dialog
     */
	public void DialogCustom(JFrame jf, int X, int Y, int Z, int rotation, int facteur)
	{
		Gestionnaire gestionnaireDialogue = new Gestionnaire(this);
		
		container = getContentPane();
		
		labelXText = "Position en X :";
		labelX = new JLabel(labelXText, JLabel.LEFT);
		
		labelYText = "Position en Y :";
		labelY = new JLabel(labelYText, JLabel.LEFT);

		labelRotationText = "Rotation :";
		labelRotation = new JLabel(labelRotationText, JLabel.LEFT);
		
		labelAgrandissementText = "Agrandissement :";
		labelAgrandissement = new JLabel(labelAgrandissementText, JLabel.LEFT);
		
		String temp = "0";
		
		temp = Integer.toString(X);
		textX = new JTextField(temp, 10);
				
		temp = Integer.toString(Y);
		textY = new JTextField(temp, 10);
		
		temp = Integer.toString(rotation);
		textRotation = new JTextField(temp, 10);
		
		temp = Integer.toString(facteur);
		textAgrandissement = new JTextField(temp, 10);
		
		boutonAccepter = new JButton("Accepter");
		//boutonAccepter.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/disk-icon.png")));
		boutonAccepter.setActionCommand("Accepter");
		boutonAccepter.addActionListener(gestionnaireDialogue);
		
		boutonAnnuler = new JButton("Annuler");
		//boutonAnnuler.setIcon(new ImageIcon(getClass().getResource("/ca/polymtl/inf2990/icones/disk-icon.png")));
		boutonAnnuler.setActionCommand("Annuler");
		boutonAnnuler.addActionListener(gestionnaireDialogue);
		
		setSize(200, 175);
		setLocationRelativeTo(getFocusOwner());
		container.setLayout(new FlowLayout());
		container.add(labelX,LEFT_ALIGNMENT);
		container.add(textX,RIGHT_ALIGNMENT);
		container.add(labelY,LEFT_ALIGNMENT);
		container.add(textY,RIGHT_ALIGNMENT);
		container.add(labelRotation,LEFT_ALIGNMENT);
		container.add(textRotation,RIGHT_ALIGNMENT);
		container.add(labelAgrandissement,LEFT_ALIGNMENT);
		container.add(textAgrandissement,RIGHT_ALIGNMENT);
		container.add(boutonAccepter);
		container.add(boutonAnnuler);

	}
	
	/** 
     * Gestion du bouton Accepter
     */
	public void Accepter()
	{
		System.out.println("Accepter");
		int X, Y, Z, rotation, facteur;
		
    	X = Integer.parseInt(getobjectX());
    	Y = Integer.parseInt(getobjectY());
    	Z = 0;
    	rotation = Integer.parseInt(getobjectRotation());
    	facteur = Integer.parseInt(getobjectAgrandissement());
    	
    	this.dispose();
    	InterfaceJava.fctC_manipulerObjet(X, Y, Z, rotation, facteur);
	}
	
	/** 
     * Gestion du bouton Annuler
     */
	public void Annuler()
	{
		this.dispose();
	}
	
	/** 
     * Gestion du textField textX
     */
	public String getobjectX()
	{
		return textX.getText();
	}
	
	/** 
     * Gestion du textField textY
     */
	public String getobjectY()
	{
		return textY.getText();
	}
	
	/** 
     * Gestion du textField textRotation
     */
	public String getobjectRotation()
	{
		return textRotation.getText();
	}
	
	/** 
     * Gestion du textField textAgrandissement
     */
	public String getobjectAgrandissement()
	{
		return textAgrandissement.getText();
	}
	
	//Variables de declaration
	JLabel labelX, labelY, labelRotation, labelAgrandissement;
	String labelXText, labelYText, labelRotationText, labelAgrandissementText;
	JTextField textX, textY, textRotation, textAgrandissement;
	JButton boutonAccepter, boutonAnnuler;
	Container container;
}
