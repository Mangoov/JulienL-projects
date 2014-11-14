package ca.polymtl.inf2990;
import javax.swing.filechooser.FileFilter;
import java.io.File;

/**
*
* @author Etienne Vallée
*/
public class FiltreXml extends FileFilter{

	/**
	    * Cette fonction prend les caractères après le point et vérifie que ce sont des fichiers XML
	    * 
	    * @param   fichier   Le fichier qu'il faut vérifier
	    * 
	    */
	@Override
	public boolean accept(File fichier) {
		
		if(fichier.isDirectory())
		{
			return true;
		}
		String nomFichier = fichier.getName();
		int i = nomFichier.lastIndexOf('.');
		
		if(i>0 && i<nomFichier.length() - 1)
		{
			if (nomFichier.substring(i+1).toLowerCase().equals("xml"))
			{
				return true;
			}
		}
		
		return false;
	}

	/**
	 * 
	 * Obtenir description
	 * 
	 */
	@Override
	public String getDescription() {

		return "/*.xml";
	}

}
