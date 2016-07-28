package codingDead;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.stage.Stage;
public class codingDeadView extends Application{
	
	
	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage stage) throws Exception {
		Label lb_text = new Label("The Coding Dead");
		FXMLLoader loader = new FXMLLoader(getClass().getResource("../codingDead.fxml"));
		Parent root = (Parent)loader.load();
		
		Scene scene = new Scene(root);
		stage.setTitle("The Coding Dead");
		stage.setScene(scene);
		stage.show();
		stage.setResizable(false);
		codingDeadController controller = (codingDeadController)loader.getController();
		controller.setRoot(root);
	}
}
