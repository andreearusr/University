package joc.network.rpcprotocol;


import joc.domain.Mutare;
import joc.domain.Jucator;
import joc.services.IJocObserver;
import joc.services.IJocService;
import joc.services.LogException;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;


public class JocServicesRpcProxy implements IJocService {
    private String host;
    private int port;

    private IJocObserver client;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private Socket connection;

    private BlockingQueue<Response> qresponses;
    private volatile boolean finished;

    public JocServicesRpcProxy(String host, int port) {
        this.host = host;
        this.port = port;
        qresponses = new LinkedBlockingQueue<Response>();
    }

    private void closeConnection() {
        finished = true;
        try {
            input.close();
            output.close();
            connection.close();
            client = null;
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void sendRequest(Request request) throws LogException {
        try {
            output.writeObject(request);
            output.flush();
        } catch (IOException e) {
            throw new LogException("Error sending object " + e);
        }

    }

    private Response readResponse() throws LogException {
        Response response = null;
        try {
            response = qresponses.take();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return response;
    }

    private void initializeConnection() throws LogException {
        try {
            connection = new Socket(host, port);
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            finished = false;
            startReader();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void startReader() {
        Thread tw = new Thread(new ReaderThread());
        tw.start();
    }


    private void handleUpdate(Response response) {
        if (response.type() == ResponseType.CLASAMENT_UPDATED) {
            List<Mutare> clasament = (List<Mutare>) response.data();
            System.out.println("Clasament updated");
            try {
                client.clasamentUpdated(clasament);
            } catch (LogException e) {
                e.printStackTrace();
            }
        }
    }

    private boolean isUpdate(Response response) {
        return response.type() == ResponseType.CLASAMENT_UPDATED;
    }

    @Override
    public void updateClasament(List<Mutare> clasament) throws LogException {
        Request req = new Request.Builder().type(RequestType.UPDATE_CLASAMENT).data(clasament).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            throw new LogException(err);
        }

    }


    private class ReaderThread implements Runnable {
        public void run() {
            while (!finished) {
                try {
                    Object response = input.readObject();
                    System.out.println("response received " + response);
                    if (isUpdate((Response) response)) {
                        handleUpdate((Response) response);
                    } else {

                        try {
                            qresponses.put((Response) response);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                } catch (IOException e) {
                    System.out.println("Reading error " + e);
                } catch (ClassNotFoundException e) {
                    System.out.println("Reading error " + e);
                }
            }
        }
    }


    @Override
    public void logIn(Jucator jucator, IJocObserver client) throws LogException {
        initializeConnection();
        Request req = new Request.Builder().type(RequestType.LOGIN).data(jucator).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.OK) {
            this.client = client;
            return;
        }
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            closeConnection();
            throw new LogException(err);
        }
    }


    @Override
    public void logOut(Jucator jucator, IJocObserver client) throws LogException {

        Request req = new Request.Builder().type(RequestType.LOGOUT).data(jucator).build();
        sendRequest(req);
        Response response = readResponse();
        closeConnection();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            throw new LogException(err);
        }
    }

    @Override
    public Jucator findJucatorByUsername(String username) throws LogException {
        initializeConnection();
        Request req = new Request.Builder().type(RequestType.FIND_JUCATOR_BY_USERNAME).data(username).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            throw new LogException(err);
        }

        Jucator jucator = (Jucator) response.data();
        return jucator;
    }


    @Override
    public Mutare getMutareJucator(Long idJucator) throws LogException {
        Request req = new Request.Builder().type(RequestType.FIND_MUTARE_JUCATOR).data(idJucator).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            throw new LogException(err);
        }

        Mutare mutare = (Mutare) response.data();
        return mutare;
    }

    @Override
    public void updateMutare(Long idMutare, Mutare mutare) throws LogException {
        List<Object> list = new ArrayList<>();
        list.add(idMutare);
        list.add(mutare);
        Request req = new Request.Builder().type(RequestType.UPDATE_MUTARE).data(list).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            throw new LogException(err);
        }
    }

    @Override
    public Mutare startJoc(Jucator jucator, IJocObserver client) throws LogException {
        Request req = new Request.Builder().type(RequestType.START).data(jucator).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            throw new LogException(err);
        }

        Mutare mutare = (Mutare) response.data();
        return mutare;
    }

    @Override
    public List<Mutare> getClasament() throws LogException {
        Request req = new Request.Builder().type(RequestType.CLASAMENT).data(null).build();
        sendRequest(req);
        Response response = readResponse();
        if (response.type() == ResponseType.ERROR) {
            String err = response.data().toString();
            throw new LogException(err);
        }

        List<Mutare> clasament = (List<Mutare>) response.data();
        return clasament;
    }



}
