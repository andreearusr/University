package joc.repository.database;

import joc.repository.JucatorRepository;
import joc.domain.Jucator;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class JucatorDBRepository implements JucatorRepository {

    private JdbcUtils dbUtils;

    public JucatorDBRepository(Properties props) {
        dbUtils = new JdbcUtils(props);
    }


    @Override
    public Long getId(String username) {
        Connection con = dbUtils.getConnection();

        try (PreparedStatement preStmt = con.prepareStatement("select * from Jucatori where username=?")) {
            preStmt.setString(1, username);
            try (ResultSet result = preStmt.executeQuery()) {
                if (result.next()) {
                    long id = result.getLong("id");

                    return id;
                }
            }
        } catch (SQLException ex) {
            System.out.println("Error DB " + ex);
        }
        return null;
    }

    @Override
    public void save(Jucator entity) {

    }

    @Override
    public void delete(Long aLong) {

    }

    @Override
    public void update(Long aLong, Jucator entity) {
        /*Connection con = dbUtils.getConnection();

        try (PreparedStatement preStmt = con.prepareStatement("update jucator SET poz=?, castig=?, pozitie=?, poate_muta=? where id=?")) {

            String str = "";
            for (Integer s : entity.getPozitii()) {
                str = str.concat(s.toString());
                str = str.concat(",");
            }

            preStmt.setString(1, str.substring(0, str.length() - 1));
            preStmt.setInt(2, entity.getBaniCastigati());
            preStmt.setInt(3, entity.getPozitieCurenta());
            preStmt.setBoolean(4, entity.isPoateMuta());
            preStmt.setLong(5, aLong);
            preStmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }*/
    }

    @Override
    public Jucator findOne(Long aLong) {
        //System.out.println("along:"+aLong);

        Connection con = dbUtils.getConnection();

        try (PreparedStatement preStmt = con.prepareStatement("select * from Jucatori where id=?")) {
            preStmt.setLong(1, aLong);
            try (ResultSet result = preStmt.executeQuery()) {
                if (result.next()) {
                    //System.out.println(result);

                    long id = result.getLong("id");
                    String username = result.getString("username");
                    String password = result.getString("password");
                    String alias = result.getString("alias");

                    Jucator jucator = new Jucator(id, username, password, alias);
                    return jucator;
                }
            }
        } catch (SQLException ex) {
            System.out.println("Error DB " + ex);
        }
        return null;
    }


    @Override
    public List<Jucator> findAll() {
        Connection con = dbUtils.getConnection();
        List<Jucator> jucatori = new ArrayList<>();
        try (PreparedStatement preStmt = con.prepareStatement("select * from Jucatori")) {
            try (ResultSet result = preStmt.executeQuery()) {
                while (result.next()) {
                    System.out.println(result);
                    long id = result.getLong("id");
                    String username = result.getString("username");
                    String password = result.getString("password");
                    String alias = result.getString("alias");

                    Jucator jucator = new Jucator(id, username, password, alias);
                    jucatori.add(jucator);
                }
            }

        } catch (SQLException ex) {
            System.err.println("Error DB" + ex);
        }
        return jucatori;
    }


  /*  @Override
    public Jucator findOneAlias(String aliass) {
        System.out.println("along:"+aliass);

        Connection con = dbUtils.getConnection();

        try (PreparedStatement preStmt = con.prepareStatement("select * from jucator where alias_ok=?")) {
            preStmt.setString(1, aliass);
            try (ResultSet result = preStmt.executeQuery()) {
                if (result.next()) {
                    long id = result.getLong("id");
                    String username = result.getString("username");
                    String password = result.getString("password");
                    //String aliasss = result.getString("alias_ok");

                    Jucator jucator = new Jucator(id, username, password);
                    return jucator;
                }
            }
        } catch (SQLException ex) {
            System.out.println("Error DB " + ex);
        }
        return null;
    }
*/

}
