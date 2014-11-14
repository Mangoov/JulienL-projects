package ca.polymtl.inf2990;
import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.IOException;

/**
*
* @author Etienne Vallée
*/
public class Volume extends JDialog implements ActionListener, ChangeListener
{
	/** 
     * Initialisation de la fenetre dialog
     */
	public void DialogVolume(JFrame jf, float volumeSonInit, float volumeMusiqueInit)
	{
		container = getContentPane();
		
		int VOLSON_MIN = 0;
		int VOLSON_MAX = 100;
		int VOLSON_INIT = (int) (volumeSonInit*100);
		int VOLMUS_MIN = 0;
		int VOLMUS_MAX = 100;
		int VOLMUS_INIT = (int) (volumeMusiqueInit*100);
		
		setTitle("Volume");
		
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
		
		//Crée le label du son
		sliderSon = new JLabel("Volume Du Son", JLabel.CENTER);
		sliderSon.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		//Crée le slider du son
		volumeSon = new JSlider(JSlider.HORIZONTAL, VOLSON_MIN, VOLSON_MAX, VOLSON_INIT);
		volumeSon.addChangeListener(this);
		
		
		//Crée le label de la musique
		sliderMusique = new JLabel("Volume De La Musique", JLabel.CENTER);
		sliderMusique.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		//Crée le slider de la musique
		volumeMusique = new JSlider(JSlider.HORIZONTAL, VOLMUS_MIN, VOLMUS_MAX, VOLMUS_INIT);
		volumeMusique.addChangeListener(this);
		
		//Mettre des labels aux ticks majeurs
		volumeSon.setMajorTickSpacing(20);
		volumeSon.setMinorTickSpacing(10);
		volumeSon.setPaintTicks(true);
		volumeSon.setPaintLabels(true);
		volumeSon.setBorder(BorderFactory.createEmptyBorder(0, 0, 10, 0));
		
		volumeMusique.setMajorTickSpacing(20);
		volumeMusique.setMinorTickSpacing(10);
		volumeMusique.setPaintTicks(true);
		volumeMusique.setPaintLabels(true);
		volumeMusique.setBorder(BorderFactory.createEmptyBorder(0, 0, 10, 0));
		
		setSize(250, 200);
		setLocationRelativeTo(getFocusOwner());
		container.setLayout(new FlowLayout());
		container.add(sliderSon,CENTER_ALIGNMENT);
		container.add(volumeSon,CENTER_ALIGNMENT);
		container.add(sliderMusique,CENTER_ALIGNMENT);
		container.add(volumeMusique,CENTER_ALIGNMENT);

	}
	
	Container container;
	
    /** 
     * Changer l'état des volume
     */
	public void stateChanged(ChangeEvent e) 
	{
		JSlider source = (JSlider)e.getSource();
		if(!source.getValueIsAdjusting())
		{
			float volume = (float)source.getValue();
			System.out.println(volume);
			float newvolume = volume/100;
			System.out.println(newvolume);
			if(e.getSource() == volumeSon)
			{
				menu_.volumeSon_ = newvolume;
				InterfaceJava.fctC_ajusterVolumeSon(newvolume);
			}
			else if(e.getSource() == volumeMusique)
			{
				menu_.volumeMusique = newvolume;
				InterfaceJava.fctC_ajusterVolumeMusique(newvolume);
			}
		}
		
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {}
	
private JLabel sliderSon;
private JSlider volumeSon;
private JLabel sliderMusique;
private JSlider volumeMusique;
private MenuPrincipal menu_ = MenuPrincipal.getInstance();
}


