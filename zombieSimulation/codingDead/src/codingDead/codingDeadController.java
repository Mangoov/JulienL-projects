package codingDead;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.ResourceBundle;
import java.util.Timer;
import java.util.TimerTask;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.shape.RectangleBuilder;


public class codingDeadController implements Initializable{
	@FXML
	private TextField zombieCount;
	@FXML
	private TextField hunterCount;
	@FXML
	private TextField victimCount;
	@FXML
	private Pane simulationMap;
	@FXML
	private TextField mapSize;

	private double dimension;
	private List<Unit> units;
	private Rectangle [][] field;
	private Parent root; 
	private Boolean gameEnd;

	public void setRoot(Parent root){
		this.root = root;
	}

	@Override
	public void initialize(URL arg0, ResourceBundle arg1) {
		// TODO Auto-generated method stub
		mapSize.setText("20");
		dimension = 20;
		zombieCount.setText("1");
		hunterCount.setText("1");
		victimCount.setText("1");
		units = new ArrayList<Unit>();
		gameEnd = false;
	}

	public void startCodingDead(){
		clearMap();
		units.clear();
		System.out.print("Started coding dead");
		dimension = Integer.parseInt(mapSize.getText());
		field = new Rectangle[(int) dimension][(int) dimension];
		drawMap();
		generateUnits();

		new Timer().schedule(
				new TimerTask() {
					@Override
					public void run() {
						moveUnits();
						checkChangeConditions();
					}
				}, 0, 200);
	}

	private void generateUnits(){
		int i = 0;
		for(i=0;i<Integer.parseInt(zombieCount.getText()); i++)
			addUnitToMap("zombie");
		for(i=0;i<Integer.parseInt(hunterCount.getText()); i++)
			addUnitToMap("hunter");
		for(i=0;i<Integer.parseInt(victimCount.getText()); i++)
			addUnitToMap("victim");
	}

	private Unit addUnitToMap(String unitType){
		Unit newUnit = new Unit(getRandomLocation(), unitType);
		Position newUnitPos = newUnit.getPosition();
		field[newUnitPos.getX()][newUnitPos.getY()].setFill(newUnit.getDisplayColor());
		units.add(newUnit);
		return newUnit;

	}

	private void moveUnits(){
		for(Unit unit:units){
			if(unit.getUnitType().equals("victim")){
				if(isZombieClose(unit.getPosition()))
					moveUnit(unit);
			}
			if(unit.getUnitType().equals("hunter")){
				moveUnit(unit);
			}
			if(unit.getUnitType().equals("zombie")){
				moveUnit(unit);
			}
		}
	}

	private void checkChangeConditions(){
		List<Unit> killedZombies = new ArrayList<Unit>();
		for(Unit unit:units){
			if(unit.getUnitType().equals("victim")){
				if(isZombieClose(unit.getPosition()))
					unit.setUnitType("zombie");
			}
			else if(unit.getUnitType().equals("hunter")){
				List<Unit> zombiesClose = getZombiesCloseToHunter(unit.getPosition());
				if(zombiesClose.size()>=3)
					unit.setUnitType("zombie");
				else
					killedZombies.addAll(zombiesClose);
			}
		}
		if(!killedZombies.isEmpty())
			removeZombies(killedZombies);	
	}
	
	private void removeZombies(List<Unit> killedZombies){
		for(Unit killedZombie:killedZombies){
			field[killedZombie.getPosition().getX()][killedZombie.getPosition().getY()].setFill(Color.GRAY);
		}
		units.removeAll(killedZombies);
	}

	private void changePosColor(Unit unit, Position newPos){
		field[unit.getPosition().getX()][unit.getPosition().getY()].setFill(Color.GRAY);
		field[newPos.getX()][newPos.getY()].setFill(unit.getDisplayColor());
	}

	private void moveUnit(Unit unit){
		Position unitPos = unit.getPosition();
		Integer randomDirection = getRandomDirection(unit.getUnitType());
		Position newPosition;
		if(randomDirection == 0){
			newPosition = new Position(unitPos.getX()+1, unitPos.getY());
			if(isPosFree(newPosition)){
				changePosColor(unit, newPosition);
				unit.setPosition(newPosition);
			}
		}
		else if(randomDirection == 1){
			newPosition = new Position(unitPos.getX(), unitPos.getY()+1);
			if(isPosFree(newPosition)){
				changePosColor(unit, newPosition);
				unit.setPosition(newPosition);
			}
		}
		else if(randomDirection == 2){
			newPosition = new Position(unitPos.getX()-1, unitPos.getY());
			if(isPosFree(newPosition)){
				changePosColor(unit, newPosition);
				unit.setPosition(newPosition);
			}
		}
		else if(randomDirection == 3){
			newPosition = new Position(unitPos.getX(), unitPos.getY()-1);
			if(isPosFree(newPosition)){
				changePosColor(unit, newPosition);
				unit.setPosition(newPosition);
			}
		}
		else if(randomDirection == 4){
			newPosition = new Position(unitPos.getX()+1, unitPos.getY()+1);
			if(isPosFree(newPosition)){
				changePosColor(unit, newPosition);
				unit.setPosition(newPosition);
			}
		}
		else if(randomDirection == 5){
			newPosition =new Position(unitPos.getX()+1, unitPos.getY()-1);
			if(isPosFree(newPosition)){
				changePosColor(unit, newPosition);
				unit.setPosition(newPosition);
			}
		}
		else if(randomDirection == 6){
			newPosition = new Position(unitPos.getX()-1, unitPos.getY()+1);
			if(isPosFree(newPosition)){
				changePosColor(unit, newPosition);
				unit.setPosition(newPosition);
			}
		}
		else if(randomDirection == 7){
			newPosition = new Position(unitPos.getX()-1, unitPos.getY()-1);
			if(isPosFree(newPosition)){
				changePosColor(unit, newPosition);
				unit.setPosition(newPosition);
			}
		}
	}

	private boolean isPosFree(Position pos){
		Boolean isFree = null;
		try{
			isFree = field[pos.getX()][pos.getY()].getFill()==Color.GREY;
		} catch(Exception e){
			isFree = false;
		}
		return isFree;
	}

	private Integer getRandomDirection(String unitType){
		int randomValue;
		if(unitType.equals("zombie"))
			randomValue =  (int)(Math.random() * 4);
		else
			randomValue =  (int)(Math.random() * 8);
		return randomValue;
	}


	private boolean isZombieClose(Position pos){
		for(Unit unit:units){
			if(unit.getUnitType().equals("zombie")){
				Position zombiePosition = unit.getPosition();
				List<Position> adjPos = zombieProximityPositions(pos);
				for(Position adj:adjPos){
					if(zombiePosition.equals(adj)){
						return true;
					}
				}
			}
		}
		return false;
	}
	
	private List<Unit> getZombiesCloseToHunter(Position pos){
		List<Unit> closeZombies = new ArrayList<Unit>();
		for(Unit unit:units){
			if(unit.getUnitType().equals("zombie")){
				Position currentZombiePos = unit.getPosition();
				List<Position> adjPos = zombieProximityPositions(pos);
				for(Position adj:adjPos){
					if(currentZombiePos.equals(adj)){
						closeZombies.add(unit);
					}
				}
			}
		
		}
		return closeZombies;
		
	}

	private List<Position> zombieProximityPositions(Position pos){
		List<Position> adjacentPositions = new ArrayList<Position>();
		adjacentPositions.add(new Position(pos.getX()+1, pos.getY()));
		adjacentPositions.add(new Position(pos.getX()-1, pos.getY()));
		adjacentPositions.add(new Position(pos.getX(), pos.getY()+1));
		adjacentPositions.add(new Position(pos.getX(), pos.getY()-1));
		return adjacentPositions;
	}

	private Position getRandomLocation(){
		Random rand = new Random();
		Integer x = rand.nextInt((int)dimension);
		Integer y = rand.nextInt((int)dimension);
		while(field[x][y].getFill()!=Color.GREY){
			x = rand.nextInt((int)dimension);
			y = rand.nextInt((int)dimension);
		}
		return new Position(x, y);
	}

	private void drawMap(){
		double squareSize = 600/dimension;
		for(int x = 0; x < dimension;x++){
			for(int y = 0; y < dimension;y++){
				Rectangle rect = RectangleBuilder.create()
						.x(x*squareSize)
						.y(y*squareSize)
						.width(squareSize)
						.height(squareSize)
						.build();
				rect.setStrokeWidth(0.5);
				rect.setStroke(Color.BLACK);
				rect.setFill(Color.GREY);
				simulationMap.getChildren().add(rect);
				field[x][y] = rect;
			}
		}
	}

	public void clearMap(){
		units.clear();
		simulationMap.getChildren().clear();
	}
}
