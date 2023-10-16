package joc.client;


import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import joc.client.gui.JocController;
import joc.client.gui.LoginController;
import joc.network.rpcprotocol.JocServicesRpcProxy;
import joc.services.IJocService;

import java.io.IOException;
import java.util.Properties;

public class StartRpcClientFX extends Application {

    private Stage primaryStage;

    private static int defaultChatPort = 55555;
    private static String defaultServer = "localhost";


    public void start(Stage primaryStage) throws Exception {
        System.out.println("In start");
        Properties clientProps = new Properties();
        try {
            clientProps.load(StartRpcClientFX.class.getResourceAsStream("/jocclient.properties"));
            System.out.println("Client properties set. ");
            clientProps.list(System.out);
        } catch (IOException e) {
            System.err.println("Cannot find jocclient.properties " + e);
            return;
        }
        String serverIP = clientProps.getProperty("joc.server.host", defaultServer);
        int serverPort = defaultChatPort;

        try {
            serverPort = Integer.parseInt(clientProps.getProperty("joc.server.port"));
        } catch (NumberFormatException ex) {
            System.err.println("Wrong port number " + ex.getMessage());
            System.out.println("Using default port: " + defaultChatPort);
        }
        System.out.println("Using server IP " + serverIP);
        System.out.println("Using server port " + serverPort);

        IJocService server = new JocServicesRpcProxy(serverIP, serverPort);

        FXMLLoader loader = new FXMLLoader(
                getClass().getClassLoader().getResource("Login.fxml"));
        Parent root = loader.load();

        LoginController loginController = loader.<LoginController>getController();
        loginController.setServer(server);


        FXMLLoader cloader = new FXMLLoader(
                getClass().getClassLoader().getResource("Jucator.fxml"));
        Parent croot = cloader.load();


        JocController jocController = cloader.<JocController>getController();
        jocController.setServer(server);

        loginController.setJucatorController(jocController);
        loginController.setParent(croot);

        primaryStage.setTitle("Joc");
        primaryStage.setScene(new Scene(root));
        primaryStage.show();

    }
}
