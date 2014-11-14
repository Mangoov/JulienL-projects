package ca.polymtl.inf2990;
import javax.swing.filechooser.FileFilter;
import java.io.File;

/**
*
* @author Etienne Vall�e
*/
public class FiltreXml extends FileFilter{

	/**
	    * Cette fonction prend les caract�res apr�s le point et v�rifie que ce sont des fichiers XML
	    * 
	    * @param   fichier   Le fichier qu'il faut v�rifier
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
