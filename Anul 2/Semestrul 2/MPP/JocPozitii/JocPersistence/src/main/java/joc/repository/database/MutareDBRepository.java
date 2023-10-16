package joc.repository.database;

import joc.domain.*;
import joc.repository.JocRepository;
import joc.repository.JucatorRepository;
import joc.repository.MutareRepository;
import joc.repository.ConfiguratieRepository;
import org.springframework.stereotype.Component;

import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

@Component
public class MutareDBRepository implements MutareRepository {

    private JdbcUtils dbUtils;
    Properties props = new Properties();

    JocRepository jocRepository;
    JucatorRepository jucatorRepository;
    ConfiguratieRepository configuratieRepository;

    public MutareDBRepository() {
        try {
            props.load(MutareDBRepository.class.getResourceAsStream("/jocserver.properties"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        dbUtils = new JdbcUtils(props);
    }

    public MutareDBRepository(JocRepository jocRepository, JucatorRepository jucatorRepository, ConfiguratieRepository configuratieRepository) {
        try {
            props.load(MutareDBRepository.class.getResourceAsStream("/jocserver.properties"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        dbUtils = new JdbcUtils(props);

        this.jocRepository = jocRepository;
        this.jucatorRepository = jucatorRepository;
        this.configuratieRepository = configuratieRepository;
    }


    @Override
    public void save(Mutare entity) {
        Connection con = dbUtils.getConnection();

        try (PreparedStatement preStmt = con.prepareStatement("insert into Mutari(idJoc, idJucator, stareJoc, cuvant1, cuvant2, cuvant3, rezultat, idConfiguratie, timestamp) values (?,?,?,?,?,?,?,?,?)")) {
            preStmt.setLong(1, entity.getJoc().getId());
            preStmt.setLong(2, entity.getJucator().getId());
            preStmt.setString(3, entity.getStareJoc());
            preStmt.setString(4, entity.getCuvant1());
            preStmt.setString(5, entity.getCuvant2());
            preStmt.setString(6, entity.getCuvant3());
            preStmt.setInt(7, entity.getRezultat());
            preStmt.setLong(8, entity.getConfiguratie().getId());
            preStmt.setString(9, entity.getTimestamp().toString());
            preStmt.executeUpdate();
        } catch (SQLException ex) {
            System.out.println("Error DB " + ex);
        }

    }

    @Override
    public void delete(Long aLong) {

    }

    @Override
    public void update(Long aLong, Mutare entity) {
        Connection con = dbUtils.getConnection();

        try (PreparedStatement preStmt = con.prepareStatement("update Mutari SET stareJoc=?, cuvant1=? , cuvant2=?, cuvant3=?, rezultat=? where id=?")) {
            preStmt.setString(1, entity.getStareJoc());
            preStmt.setString(2, entity.getCuvant1());
            preStmt.setString(3, entity.getCuvant2());
            preStmt.setString(4, entity.getCuvant3());
            preStmt.setInt(5, entity.getRezultat());
            preStmt.setLong(6, aLong);
            preStmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Mutare findOne(Long aLong) {
        return null;
    }


    @Override
    public List<Mutare> findAll() {
        Connection con = dbUtils.getConnection();
        List<Mutare> mutari = new ArrayList<>();
        try (PreparedStatement preStmt = con.prepareStatement("select * from Mutari ")) {

            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    long id = result.getLong("id");
                    long idJoc = result.getLong("idJoc");
                    long idJucator = result.getLong("idJucator");
                    String stareJoc = result.getString("stareJoc");
                    long idConfiguratie = result.getLong("idConfiguratie");


                    String cuvant1 = result.getString("cuvant1");
                    String cuvant2 = result.getString("cuvant2");
                    String cuvant3 = result.getString("cuvant3");
                    Integer rezultat = result.getInt("rezultat");
                    Timestamp timestamp = result.getTimestamp("timestamp");

                    Integer nrGhicite = result.getInt("nrGhicite");
                    String cuvinteGhicite = result.getString("cuvinteGhicite");

                    Joc joc = jocRepository.findOne(idJoc);
                    Jucator jucator = jucatorRepository.findOne(idJoc);
                    Configuratie configuratie = configuratieRepository.findOne(idConfiguratie);

                    Mutare j = new Mutare(id, joc, jucator, stareJoc, configuratie, cuvant1, cuvant2, cuvant3, rezultat,timestamp, nrGhicite, cuvinteGhicite);
                    mutari.add(j);
                }
            }

        } catch (SQLException ex) {
            System.err.println("Error DB" + ex);
        }
        return mutari;

    }

    public List<Mutare> findToateJocuriFinalizate(){
        Connection con = dbUtils.getConnection();
        List<Mutare> mutari = new ArrayList<>();
        try (PreparedStatement preStmt = con.prepareStatement("select * from Mutari where stareJoc=? order by rezultat desc")) {
            preStmt.setString(1, "FINALIZAT");
            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    long id = result.getLong("id");
                    long idJoc = result.getLong("idJoc");
                    long idJucator = result.getLong("idJucator");
                    String stareJoc = result.getString("stareJoc");
                    long idConfiguratie = result.getLong("idConfiguratie");


                    String cuvant1 = result.getString("cuvant1");
                    String cuvant2 = result.getString("cuvant2");
                    String cuvant3 = result.getString("cuvant3");
                    Integer rezultat = result.getInt("rezultat");
                    Timestamp timestamp = result.getTimestamp("timestamp");
                    Integer nrGhicite = result.getInt("nrGhicite");
                    String cuvinteGhicite = result.getString("cuvinteGhicite");

                    Joc joc = jocRepository.findOne(idJoc);
                    Jucator jucator = jucatorRepository.findOne(idJoc);
                    Configuratie configuratie = configuratieRepository.findOne(idConfiguratie);

                    Mutare j = new Mutare(id, joc, jucator, stareJoc, configuratie, cuvant1, cuvant2, cuvant3, rezultat,timestamp, nrGhicite, cuvinteGhicite);
                    mutari.add(j);
                }
            }

        } catch (SQLException ex) {
            System.err.println("Error DB" + ex);
        }
        return mutari;

    }

    public List<MutareDTO> findJocuriFinalizateJucator(Long idJucator){
        Connection con = dbUtils.getConnection();
        List<MutareDTO> mutari = new ArrayList<>();
        try (PreparedStatement preStmt = con.prepareStatement("select * from Mutari where stareJoc=? and idJucator=?")) {
            preStmt.setString(1, "FINALIZAT");
            preStmt.setLong(2, idJucator);
            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    long id = result.getLong("id");
                    Long idJoc = result.getLong("idJoc");
                    Long idJ = result.getLong("idJucator");
                    String stareJoc = result.getString("stareJoc");
                    long idConfiguratie = result.getLong("idConfiguratie");

                    String cuvant1 = result.getString("cuvant1");
                    String cuvant2 = result.getString("cuvant2");
                    String cuvant3 = result.getString("cuvant3");
                    Integer rezultat = result.getInt("rezultat");
                    Timestamp timestamp = result.getTimestamp("timestamp");
                    Integer nrGhicite = result.getInt("nrGhicite");
                    String cuvinteGhicite = result.getString("cuvinteGhicite");

                    //Joc joc = jocRepository.findOne(idJoc);
                    //Jucator jucator = jucatorRepository.findOne(idJ);
                    //Configuratie pozitie = pozitieRepository.findOne(idPozitie);

                    MutareDTO j = new MutareDTO(id, idJoc, idJucator, stareJoc, idConfiguratie, cuvant1, cuvant2, cuvant3, rezultat, timestamp, nrGhicite, cuvinteGhicite);
                    mutari.add(j);
                }
            }

        } catch (SQLException ex) {
            System.err.println("Error DB" + ex);
        }
        return mutari;

    }

    public Mutare findMutareJucator(Long idJucator){
        System.out.println("idJucatorDat:"+idJucator);
        Connection con = dbUtils.getConnection();
        Mutare mutare = null;
        try (PreparedStatement preStmt = con.prepareStatement("select * from Mutari where idJucator=? and stareJoc=?")) {
            preStmt.setLong(1, idJucator);
            preStmt.setString(2, "IN_DESFASURARE");
            try (ResultSet result = preStmt.executeQuery()) {
                if (result.next()) {
                    long id = result.getLong("id");
                    Long idJoc = result.getLong("idJoc");
                    Long idJ = result.getLong("idJucator");
                    String stareJoc = result.getString("stareJoc");
                    long idConfiguratie = result.getLong("idConfiguratie");


                    String cuvant1 = result.getString("cuvant1");
                    String cuvant2 = result.getString("cuvant2");
                    String cuvant3 = result.getString("cuvant3");
                    Integer rezultat = result.getInt("rezultat");
                    Timestamp timestamp = result.getTimestamp("timestamp");
                    Integer nrGhicite = result.getInt("nrGhicite");
                    String cuvinteGhicite = result.getString("cuvinteGhicite");

                    Joc joc = jocRepository.findOne(idJoc);
                    Jucator jucator = jucatorRepository.findOne(idJoc);
                    Configuratie configuratie = configuratieRepository.findOne(idConfiguratie);

                    mutare = new Mutare(id, joc, jucator, stareJoc, configuratie, cuvant1, cuvant2, cuvant3, rezultat,timestamp, nrGhicite, cuvinteGhicite);
                    return mutare;
                }
            }

        } catch (SQLException ex) {
            System.err.println("Error DB" + ex);
        }
        return mutare;

    }



}
