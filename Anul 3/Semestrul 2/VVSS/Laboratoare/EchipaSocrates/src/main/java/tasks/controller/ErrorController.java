package tasks.controller;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import org.apache.log4j.Logger;

public class ErrorController {

    private static final Logger log = Logger.getLogger(ErrorController.class.getName());

    @FXML
    private Label labelValidator;

    @FXML
    public void initialize(){
        log.info("new/edit window initializing");
//        switch (clickedButton.getId()){
//            case  "btnNew" : initNewWindow("New Task");
//                break;
//            case "btnEdit" : initEditWindow("Edit Task");
//                break;
//        }
        labelValidator.setText("");
    }

    public void setLabelValidator(String text){
        labelValidator.setText(text);
    }


}
