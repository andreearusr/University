import joc.network.utils.AbstractServer;
import joc.network.utils.JocRpcConcurrentServer;
import joc.network.utils.ServerException;
import joc.repository.MutareRepository;
import joc.repository.JocRepository;
import joc.repository.JucatorRepository;
import joc.repository.ConfiguratieRepository;
import joc.repository.database.ConfiguratieDBRepository;
import joc.repository.database.MutareDBRepository;
import joc.repository.database.JucatorDBRepository;
import joc.repository.orm.JocORMRepository;
import joc.server.JocImpl;
import joc.services.IJocService;

import java.io.IOException;
import java.util.Properties;

public class StartRpcServer {
    private static int defaultPort = 55555;

    public static void main(String[] args) {

        Properties serverProps = new Properties();
        try {
            serverProps.load(StartRpcServer.class.getResourceAsStream("/jocserver.properties"));
            System.out.println("Server properties set. ");
            serverProps.list(System.out);
        } catch (IOException e) {
            System.err.println("Cannot find server.properties " + e);
            return;
        }

       /* ArtistRepository artistRepository = new ArtistDBRepository();
       //ArtistRepository artistRepository = new ArtistORMRepository();
        OfficeEmployeeRepository officeEmployeeRepository = new OfficeEmployeeDBRepository(serverProps);
        ShowRepository showRepository = new ShowDBRepository(serverProps, artistRepository);
        TicketRepository ticketRepository = new TicketDBRepository(serverProps,showRepository, officeEmployeeRepository);
*/

        ConfiguratieRepository configuratieRepository = new ConfiguratieDBRepository();
        JocRepository jocRepository = new JocORMRepository();
        JucatorRepository jucatorRepository = new JucatorDBRepository(serverProps);
        MutareRepository mutareRepository = new MutareDBRepository(jocRepository, jucatorRepository, configuratieRepository);


        IJocService jocServiceImpl = new JocImpl(jocRepository, jucatorRepository, mutareRepository, configuratieRepository);

        int jocServerPort = defaultPort;
        try {
            jocServerPort = Integer.parseInt(serverProps.getProperty("joc.server.port"));
        } catch (NumberFormatException nef) {
            System.err.println("Wrong  Port Number" + nef.getMessage());
            System.err.println("Using default port " + defaultPort);
        }
        System.out.println("Starting server on port: " + jocServerPort);
        AbstractServer server = new JocRpcConcurrentServer(jocServerPort, jocServiceImpl);
        try {
            server.start();
        } catch (ServerException e) {
            System.err.println("Error starting the server" + e.getMessage());
        } finally {
            try {
                server.stop();
            } catch (ServerException e) {
                System.err.println("Error stopping server " + e.getMessage());
            }
        }
    }
}
