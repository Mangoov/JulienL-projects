package codingDead;

import javafx.scene.paint.Color;


public class Unit {
	private Position currentPosition;
	private String unitType;
	
	public Unit(Position pos, String unitType){
		this.unitType = unitType;
		currentPosition = pos;
	}
	
	public Color getDisplayColor(){
		if(this.unitType.equals("zombie")){
			return Color.RED;
		}
		if(this.unitType.equals("hunter")){
			return Color.GREEN;
		}
		else{
			return Color.WHITE;
		}
	}
	
	public Position getPosition(){
		return currentPosition;
	}

	public String getUnitType() {
		return unitType;
	}

	public void setUnitType(String unitType) {
		this.unitType = unitType;
	}


	public void setPosition(Position currentPosition) {
		this.currentPosition = currentPosition;
	}
	
	
}
