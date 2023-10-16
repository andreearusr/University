package joc.network.rpcprotocol;

import joc.domain.Mutare;
import joc.domain.Jucator;
import joc.services.IJocObserver;
import joc.services.IJocService;
import joc.services.LogException;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.util.List;


public class JocClientRpcReflectionWorker implements Runnable, IJocObserver {
    private IJocService server;
    private Socket connection;

    private ObjectInputStream input;
    private ObjectOutputStream output;
    private volatile boolean connected;

    public JocClientRpcReflectionWorker(IJocService server, Socket connection) {
        this.server = server;
        this.connection = connection;
        try {
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            connected = true;
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        while (connected) {
            try {
                Object request = input.readObject();
                Response response = handleRequest((Request) request);
                if (response != null) {
                    sendResponse(response);
                }
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        try {
            input.close();
            output.close();
            connection.close();
        } catch (IOException e) {
            System.out.println("Error " + e);
        }
    }


    private static Response okResponse = new Response.Builder().type(ResponseType.OK).build();

    //  private static Response errorResponse=new Response.Builder().type(ResponseType.ERROR).build();
    private Response handleRequest(Request request) {
        Response response = null;
        String handlerName = "handle" + (request).type();
        System.out.println("HandlerName " + handlerName);
        try {
            Method method = this.getClass().getDeclaredMethod(handlerName, Request.class);
            response = (Response) method.invoke(this, request);
            System.out.println("Method " + handlerName + " invoked");
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }

        return response;
    }

    private void sendResponse(Response response) throws IOException {
        System.out.println("sending response " + response);
        output.writeObject(response);
        output.flush();
    }

    private Response handleLOGIN(Request request) {
        System.out.println("Login request ..." + request.type());
        Jucator jucator = (Jucator) request.data();
        try {
            server.logIn(jucator, this);
            return okResponse;
        } catch (LogException e) {
            connected = false;
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleLOGOUT(Request request) {
        System.out.println("Logout request...");
        Jucator jucator = (Jucator) request.data();
        try {
            server.logOut(jucator, this);
            connected = false;
            return okResponse;
        } catch (LogException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }

    }


    private Response handleFIND_JUCATOR_BY_USERNAME(Request request) {
        System.out.println("FindJucatorByUsername Request ...");
        String username = (String) request.data();
        try {
            Jucator jucator = server.findJucatorByUsername(username);
            return new Response.Builder().type(ResponseType.FIND_JUCATOR_BY_USERNAME).data(jucator).build();
        } catch (LogException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleFIND_MUTARE_JUCATOR(Request request) {
        System.out.println("Mutare Jucator Request ...");
        Long idJucator = (Long) request.data();
        try {
            Mutare mutare = server.getMutareJucator(idJucator);
            return new Response.Builder().type(ResponseType.MUTARE_JUCATOR).data(mutare).build();
        } catch (LogException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleSTART(Request request) {
        System.out.println("Start Request ...");
        Jucator jucator = (Jucator) request.data();
        try {
            Mutare mutare = server.startJoc(jucator, this);
            return new Response.Builder().type(ResponseType.START).data(mutare).build();
        } catch (LogException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleCLASAMENT(Request request) {
        System.out.println("Clasament request...");
        try {
            List<Mutare> clasament = server.getClasament();
            return new Response.Builder().type(ResponseType.CLASAMENT).data(clasament).build();
        } catch (LogException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }

    }

    @Override
    public void clasamentUpdated(List<Mutare> clasament) throws LogException {
        Response resp = new Response.Builder().type(ResponseType.CLASAMENT_UPDATED).data(clasament).build();
        System.out.println("Clasament updated reflexion ");
        try {
            sendResponse(resp);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private Response handleUPDATE_CLASAMENT(Request request) {
        System.out.println("UpdateClasament Request ...");
        List<Mutare> clasament = (List<Mutare>) request.data();
        try {
            server.updateClasament(clasament);
            return okResponse;
        } catch (LogException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }

    private Response handleUPDATE_MUTARE(Request request) {
        System.out.println("UpdateMutare Request ...");
        List<Object> list = (List<Object>) request.data();
        Long mutareId = (Long) list.get(0);
        Mutare mutare = (Mutare) list.get(1);
        try {
            server.updateMutare(mutareId, mutare);
            return okResponse;
        } catch (LogException e) {
            return new Response.Builder().type(ResponseType.ERROR).data(e.getMessage()).build();
        }
    }


}
