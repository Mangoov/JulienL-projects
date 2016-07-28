package codingDead;

public class Position {
	Integer x;
	public Integer getX() {
		return x;
	}

	public void setX(Integer x) {
		this.x = x;
	}

	public Integer getY() {
		return y;
	}

	public void setY(Integer y) {
		this.y = y;
	}

	Integer y;
	
	public Position(Integer x, Integer y){
		this.x = x;
		this.y = y;
	}
	
	public boolean equals(Position pos){
		if(pos.getX() == this.x && pos.getY() == this.y)
			return true;
		else
			return false;
	}


}
