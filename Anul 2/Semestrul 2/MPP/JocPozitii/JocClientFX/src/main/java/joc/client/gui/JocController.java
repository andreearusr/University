package joc.client.gui;

import javafx.application.Platform;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import joc.domain.Configuratie;
import joc.domain.Mutare;
import joc.domain.Jucator;
import joc.services.IJocObserver;
import joc.services.IJocService;
import joc.services.LogException;

import java.io.IOException;
import java.net.URL;
import java.sql.Timestamp;
import java.util.List;
import java.util.Objects;
import java.util.Random;
import java.util.ResourceBundle;

public class JocController implements Initializable, IJocObserver {

    private IJocService server;
    private Jucator jucator;
    private Integer numarRunda;
    private Mutare mutareJucator;
    private Integer nrGhicite;

    private final ObservableList<Configuratie> model1 = FXCollections.observableArrayList();
    private final ObservableList<Mutare> model2 = FXCollections.observableArrayList();
    private final ObservableList<Configuratie> model3 = FXCollections.observableArrayList();

    public void setServer(IJocService s) {
        this.server = s;
    }

    public void setJucator(Jucator jucator) throws LogException {
        this.jucator = jucator;
        this.numarRunda = 0;
        this.mutareJucator = null;
        this.nrGhicite = 0;
    }

    @FXML
    private TableColumn<Configuratie, Long> l1;

    @FXML
    private TableColumn<Configuratie, Long> l2;

    @FXML
    private TableColumn<Configuratie, Long> l3;

    @FXML
    private TableColumn<Configuratie, Long> cuv1;

    @FXML
    private TableColumn<Configuratie, Long> cuv2;

    @FXML
    private TableColumn<Configuratie, Long> cuv3;

    @FXML
    private TableView<Configuratie> tableViewCuvintePosibile;

    @FXML
    private TableView<Configuratie> tableViewPozitii;

    @FXML
    private TableView<Mutare> tableViewClasament;

    @FXML
    private TableColumn<Mutare, Long> aliasColumn;

    @FXML
    private TableColumn<Mutare, Timestamp> dataSiOraColumn;

    @FXML
    private TableColumn<Mutare, Integer> rezColumn;

    @FXML
    private TextField textGhicit;

    @FXML
    private TextField textCuvant;


    @FXML
    private TextField textAlias;

    @FXML
    private TextField textRezultate;

    @FXML
    private Button butonTrimitere;


    @Override
    public void initialize(URL location, ResourceBundle resources) {
        tableViewPozitii.setVisible(false);
        l1.setCellValueFactory(new PropertyValueFactory<Configuratie, Long>("l1"));
        l2.setCellValueFactory(new PropertyValueFactory<Configuratie, Long>("l2"));
        l3.setCellValueFactory(new PropertyValueFactory<Configuratie, Long>("l3"));

        tableViewPozitii.setItems(model1);

        tableViewClasament.setVisible(false);
        aliasColumn.setCellValueFactory(new PropertyValueFactory<Mutare, Long>("idJucator"));
        //aliasColumn.setCellValueFactory(param -> new ReadOnlyObjectWrapper<>(param.getValue().getJucator().getAlias()));
        dataSiOraColumn.setCellValueFactory(new PropertyValueFactory<Mutare, Timestamp>("timestamp"));
        rezColumn.setCellValueFactory(new PropertyValueFactory<Mutare, Integer>("rezultat"));

        tableViewClasament.setItems(model2);

        tableViewCuvintePosibile.setVisible(false);
        cuv1.setCellValueFactory(new PropertyValueFactory<Configuratie, Long>("cuv1"));
        cuv2.setCellValueFactory(new PropertyValueFactory<Configuratie, Long>("cuv2"));
        cuv3.setCellValueFactory(new PropertyValueFactory<Configuratie, Long>("cuv3"));

        tableViewCuvintePosibile.setItems(model3);
    }

    @FXML
    private void handleLogout(javafx.event.ActionEvent actionEvent) throws IOException {
        try {
            server.logOut(jucator, this);
        } catch (LogException e) {
            System.out.println("Logout error " + e);
        }
        ((Node) (actionEvent.getSource())).getScene().getWindow().hide();
    }

    @FXML
    private void handleIncepeJoc() throws LogException {
        String alias = textAlias.getText();
        if (alias.equals(jucator.getAlias())) {
            startJoc();
        } else {
            MessageAlert.showErrorMessage(null, "Alias incorect pentru jucatorul inregistrat: " + jucator.getUsername());
        }
    }

    private void startJoc() throws LogException {
        Mutare mutare = server.startJoc(jucator, this);
        mutareJucator = mutare;

        tableViewPozitii.getItems().clear();
        Configuratie configuratie = mutare.getConfiguratie();

        tableViewPozitii.getItems().add(configuratie);
        tableViewPozitii.setVisible(true);

    }


    @FXML
    private void handleTrimitere() throws LogException {
        numarRunda = numarRunda + 1;

        String cuvantIntrodus = textCuvant.getText();
        Mutare mutare = server.getMutareJucator(jucator.getId());

        mutare.setCuvant(numarRunda, cuvantIntrodus);

        System.out.println(cuvantIntrodus);
        System.out.println(mutareJucator.getConfiguratie().getCuv1());
        System.out.println(mutareJucator.getConfiguratie().getCuv2());
        System.out.println(mutareJucator.getConfiguratie().getCuv3());

        if (Objects.equals(mutareJucator.getConfiguratie().getCuv1(), cuvantIntrodus) ||
                Objects.equals(mutareJucator.getConfiguratie().getCuv2(), cuvantIntrodus) ||
                Objects.equals(mutareJucator.getConfiguratie().getCuv3(), cuvantIntrodus)) {

            mutare.setRezultat(mutare.getRezultat() + cuvantIntrodus.length());
            nrGhicite = nrGhicite + 1;
            mutare.setNrGhicite(nrGhicite);
            mutare.setCuvant(numarRunda, cuvantIntrodus);

            /*String cuvG = "";
            cuvG = cuvG.concat(cuvantIntrodus);
            cuvG = cuvG.concat(",");
            mutare.setCuvinteGhicite(cuvG);*/
            textGhicit.setText("Cuvant ghicit");
        } else {
            textGhicit.setText("Cuvant gresit");
        }

        if (numarRunda == 3) {
            mutare.setStareJoc("FINALIZAT");
        }

        textRezultate.setText(mutare.getRezultat().toString());
        server.updateMutare(mutareJucator.getId(), mutare);

        if (numarRunda == 3) {
            butonTrimitere.setDisable(true);

            tableViewCuvintePosibile.getItems().clear();
            Configuratie configuratie = mutareJucator.getConfiguratie();

            tableViewCuvintePosibile.getItems().add(configuratie);
            tableViewCuvintePosibile.setVisible(true);

            //textRezultate.setText(mutare.getRezultat().toString());

            List<Mutare> mutari = server.getClasament();
            server.updateClasament(mutari);

        }


    }

    @Override
    public void clasamentUpdated(List<Mutare> clasament) throws LogException {
        System.out.println("Clasament updated");

        Platform.runLater(() -> {
            tableViewClasament.getItems().clear();

            for (Mutare m : clasament) {
                tableViewClasament.getItems().add(m);
            }
            tableViewClasament.setVisible(true);


        });
    }


}
