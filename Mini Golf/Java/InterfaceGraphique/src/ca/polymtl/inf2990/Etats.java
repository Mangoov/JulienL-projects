package ca.polymtl.inf2990;


// D�claration du patron State qui permet de passer du menu � l'un des deux autres �tats (�diteur et jeu)
/**
*
* @author Etienne Vall�e
*/
public interface Etats 
{
	public void ajouterGestionnaires(ContexteEtat contexteEtat, MenuPrincipal menu);
}
