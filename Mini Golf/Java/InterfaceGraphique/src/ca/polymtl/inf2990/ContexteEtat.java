package ca.polymtl.inf2990;
/**
*
* @author Etienne Vallée
*/
public class ContexteEtat {

	/**
    * Cette fonction ne sert pas pour l'instant.
    * Elle permettrait de mettre un état par défaut.
    */
	public ContexteEtat()
	{
		//choixEtat(new Menu()); Permet de mettre un Etat par défaut ...
	}
	
	/**
	    * Cette fonction permettre de changer l'état dans lequel l'on se trouve
	    * 
	    * @param   nouvelEtat	L'état dans lequel on veut aller
	    */	
	public void choixEtat(Etats nouvelEtat)
	{
		this.monEtat_ = nouvelEtat;
	}
	
	/**
	    * Cette fonction ajoute un gestionnaire à l'état
	    * 
	    * @param	menu	l'instance du menu
	    * 
	    */
	public void ajouterGestionnaires(MenuPrincipal menu)
	{
		this.monEtat_.ajouterGestionnaires(this, menu);
	}
	
	//Variables de declaration
	private Etats monEtat_;
}
