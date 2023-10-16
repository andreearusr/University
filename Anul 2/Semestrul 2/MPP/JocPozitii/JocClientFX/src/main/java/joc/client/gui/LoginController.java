package joc.client.gui;


import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import joc.domain.Jucator;
import joc.services.IJocService;
import joc.services.LogException;

public class LoginController {

    private IJocService server;
    private JocController jocController;
    Parent mainJucatorParent;

    @FXML
    private TextField inputUsername;

    @FXML
    private PasswordField inputPassword;


    public void setParent(Parent p) {
        mainJucatorParent = p;
    }

    public void setServer(IJocService s) {
        this.server = s;
    }


    public void setJucatorController(JocController jocController) {
        this.jocController = jocController;
    }


    @FXML
    public void jucatorLogin(ActionEvent actionEvent) {
        tryLogin(actionEvent, inputUsername.getText(), inputPassword.getText());
    }


    private void tryLogin(ActionEvent actionEvent, String username, String password) {
        try {
            Jucator jucator = server.findJucatorByUsername(username);
            if (jucator.getPassword().equals(password)) {
                server.logIn(jucator, this.jocController);

                Stage stage = new Stage();
                stage.setTitle("Chat Window for " + jucator.getUsername());
                stage.setScene(new Scene(mainJucatorParent));

                stage.show();
                jocController.setJucator(jucator);
                ((Node) (actionEvent.getSource())).getScene().getWindow().hide();
            } else
                throw new LogException("Login failed");
        } catch (LogException e) {
            MessageAlert.showErrorMessage(null, e.getMessage());
        }
    }

}
