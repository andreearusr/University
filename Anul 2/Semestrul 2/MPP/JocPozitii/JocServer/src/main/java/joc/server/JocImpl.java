package joc.server;

import joc.domain.Configuratie;
import joc.domain.Joc;
import joc.domain.Mutare;
import joc.domain.Jucator;
import joc.repository.MutareRepository;
import joc.repository.JocRepository;
import joc.repository.JucatorRepository;
import joc.repository.ConfiguratieRepository;
import joc.services.IJocObserver;
import joc.services.IJocService;
import joc.services.LogException;

import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class JocImpl implements IJocService {

    private JucatorRepository jucatorRepository;
    private JocRepository jocRepository;
    private MutareRepository mutareRepository;
    private ConfiguratieRepository configuratieRepository;

    private Map<Long, IJocObserver> loggedJucatori;
    private Map<Long, IJocObserver> playingJucatori;


    public JocImpl(JocRepository jocRepository, JucatorRepository jucatorRepository, MutareRepository mutareRepository, ConfiguratieRepository configuratieRepository) {
        this.jocRepository = jocRepository;
        this.jucatorRepository = jucatorRepository;
        this.mutareRepository = mutareRepository;
        this.configuratieRepository = configuratieRepository;

        loggedJucatori = new ConcurrentHashMap<>();
        playingJucatori = new ConcurrentHashMap<>();
    }


    public synchronized Jucator findJucatorByUsername(String username) {
        Long id = jucatorRepository.getId(username);
        System.out.println("id:" + id);
        return jucatorRepository.findOne(id);
    }


    public synchronized List<Mutare> getClasament(){
        return mutareRepository.findToateJocuriFinalizate();
    }

    public synchronized Mutare getMutareJucator(Long idJucator){
        return mutareRepository.findMutareJucator(idJucator);
    }

    public synchronized void updateMutare(Long idMutare, Mutare mutare){
        mutareRepository.update(idMutare, mutare);
    }


    @Override
    public synchronized Mutare startJoc(Jucator jucator, IJocObserver client) {
        playingJucatori.put(jucator.getId(), client);

        List<Configuratie> pozitii = configuratieRepository.findAll();
        System.out.println("pozitii:"+pozitii);
        Random random = new Random();

        int a = random.nextInt(pozitii.size());
        Configuratie randomPoz = pozitii.get(a);


        Joc jocNou = new Joc("IN_DESFASURARE");
        jocRepository.save(jocNou);

        Timestamp timestamp = Timestamp.valueOf(LocalDateTime.now());
        Mutare mutare = new Mutare(jocNou, jucator, "IN_DESFASURARE", randomPoz, "", "", "", 0, timestamp, 0, "");
        mutareRepository.save(mutare);

        return mutare;

    }

    private final int defaultThreadsNo = 5;
    public synchronized void updateClasament(List<Mutare> clasament) {
        ExecutorService executor = Executors.newFixedThreadPool(defaultThreadsNo);
        for (Map.Entry<Long, IJocObserver> entry : playingJucatori.entrySet()) {
            //IFestivalObserver festivalClient = entry.getValue();
            //if (festivalClient != null)
            executor.execute(() ->
            {
                try {
                    entry.getValue().clasamentUpdated(clasament);
                } catch (LogException e) {
                    e.printStackTrace();
                }
            });

        }
        executor.shutdown();
    }


    @Override
    public synchronized void logIn(Jucator jucator, IJocObserver client) throws LogException {
        Long jucatorId = jucatorRepository.getId(jucator.getUsername());
        if (jucatorId != null) {
            if (loggedJucatori.get(jucatorId) != null)
                throw new LogException("Jucator already logged in.");
            loggedJucatori.put(jucatorId, client);
            //setPoz(jucator);
        } else
            throw new LogException("Authentication failed.");
    }

    @Override
    public synchronized void logOut(Jucator jucator, IJocObserver client) throws LogException {
        IJocObserver localClient = loggedJucatori.remove(jucator.getId());
        if (localClient == null)
            throw new LogException("Jucator " + jucator.getId() + "is not logged in.");
    }

}

