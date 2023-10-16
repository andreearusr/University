package joc.network.utils;

import joc.network.rpcprotocol.JocClientRpcReflectionWorker;
import joc.services.IJocService;

import java.net.Socket;


public class JocRpcConcurrentServer extends AbsConcurrentServer {
    private IJocService jocServer;

    public JocRpcConcurrentServer(int port, IJocService jocServer) {
        super(port);
        this.jocServer = jocServer;
        System.out.println("Joc- JocRpcConcurrentServer");
    }

    @Override
    protected Thread createWorker(Socket client) {
        // ChatClientRpcWorker worker=new ChatClientRpcWorker(chatServer, client);
        JocClientRpcReflectionWorker worker = new JocClientRpcReflectionWorker(jocServer, client);

        Thread tw = new Thread(worker);
        return tw;
    }

    @Override
    public void stop() {
        System.out.println("Stopping services ...");
    }
}
