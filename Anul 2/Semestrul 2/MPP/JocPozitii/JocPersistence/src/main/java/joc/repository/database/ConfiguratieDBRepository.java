package joc.repository.database;

import joc.domain.Configuratie;
import joc.repository.ConfiguratieRepository;
import org.springframework.stereotype.Component;

import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

@Component
public class ConfiguratieDBRepository implements ConfiguratieRepository {

    private JdbcUtils dbUtils;
    Properties props = new Properties();

    public ConfiguratieDBRepository() {
        try {
            props.load(MutareDBRepository.class.getResourceAsStream("/jocserver.properties"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        dbUtils = new JdbcUtils(props);
    }


    @Override
    public void save(Configuratie entity) {
        Connection con = dbUtils.getConnection();

        try (PreparedStatement preStmt = con.prepareStatement("insert into Configuratie(l1, l2, l3, cuv1, cuv2,cuv3) values (?,?,?,?,?,?)")) {
            preStmt.setString(1, entity.getL1());
            preStmt.setString(2, entity.getL2());
            preStmt.setString(3, entity.getL3());
            preStmt.setString(4, entity.getCuv1());
            preStmt.setString(5, entity.getCuv2());
            preStmt.setString(6, entity.getCuv3());

            preStmt.executeUpdate();
        } catch (SQLException ex) {
            System.out.println("Error DB " + ex);
        }
    }

    @Override
    public void delete(Long aLong) {

    }

    @Override
    public void update(Long aLong, Configuratie entity) {

    }

    @Override
    public Configuratie findOne(Long aLong) {
        return null;
    }

    @Override
    public List<Configuratie> findAll() {
        Connection con = dbUtils.getConnection();
        List<Configuratie> pozitii = new ArrayList<>();
        try (PreparedStatement preStmt = con.prepareStatement("select * from Configuratie ")) {

            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    long id = result.getLong("id");

                    String l1 = result.getString("l1");
                    String l2 = result.getString("l2");
                    String l3 = result.getString("l3");
                    String cuv1 = result.getString("cuv1");
                    String cuv2 = result.getString("cuv2");
                    String cuv3 = result.getString("cuv3");

                    Configuratie pozitie = new Configuratie(id, l1, l2, l3, cuv1, cuv2, cuv3);
                    pozitii.add(pozitie);

                }
            }

        } catch (SQLException ex) {
            System.err.println("Error DB" + ex);
        }
        return pozitii;
    }
}
