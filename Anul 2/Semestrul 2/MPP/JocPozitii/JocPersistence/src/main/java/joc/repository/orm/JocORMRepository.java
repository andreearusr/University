package joc.repository.orm;

import joc.repository.JocRepository;
import joc.domain.Joc;
import joc.repository.database.JdbcUtils;
import joc.repository.database.MutareDBRepository;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.boot.MetadataSources;
import org.hibernate.boot.registry.StandardServiceRegistry;
import org.hibernate.boot.registry.StandardServiceRegistryBuilder;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;


public class JocORMRepository implements JocRepository {

    private static SessionFactory sessionFactory;
    Properties props = new Properties();
    private JdbcUtils dbUtils;

    public JocORMRepository() {

        try {
            props.load(MutareDBRepository.class.getResourceAsStream("/jocserver.properties"));
        } catch (IOException e) {
            e.printStackTrace();
        }

        dbUtils = new JdbcUtils(props);

    }


    static void initialize() {
        // A SessionFactory is set up once for an application!
        final StandardServiceRegistry registry = new StandardServiceRegistryBuilder()
                .configure() // configures settings from hibernate.cfg.xml
                .build();
        try {
            sessionFactory = new MetadataSources(registry).buildMetadata().buildSessionFactory();
        } catch (Exception e) {
            System.err.println("Exceptie " + e);
            StandardServiceRegistryBuilder.destroy(registry);
        }
    }

    static void close() {
        if (sessionFactory != null) {
            sessionFactory.close();
        }
    }

    @Override
    public void save(Joc entity) {
        initialize();
        /*try {
            findOne(entity.getId());
            throw new LoginException("artist already exists");
        } catch (LoginException e) {
            e.printStackTrace();
        }*/
        try (Session session = sessionFactory.openSession()) {
            Transaction transaction = null;
            try {
                transaction = session.beginTransaction();
                session.save(entity);
                //session.save(new Artist("Anuel","AA",30,"Cuba"));
                transaction.commit();

            } catch (RuntimeException exception) {
                if (transaction != null)
                    transaction.rollback();
            }
        }finally {
            close();
        }
    }

    @Override
    public void delete(Long aLong) {
        initialize();
        Joc joc = findOne(aLong);
        try (Session session = sessionFactory.openSession()) {
            Transaction transaction = null;
            try {
                transaction = session.beginTransaction();
                session.delete(joc);
                transaction.commit();
            } catch (RuntimeException exception) {
                if (transaction != null)
                    transaction.rollback();
            }
        }
        finally {
            close();
        }
    }

    public Long getIdLastAdded(){
        initialize();
        Integer id = null;
        try (Session session = sessionFactory.openSession()) {
            Transaction transaction = null;
            try {
                transaction = session.beginTransaction();

                Joc joc = session.createQuery("from joc order by id desc" , Joc.class)
                        .setMaxResults(1)
                        .getSingleResult();

                transaction.commit();

                return joc.getId();
            } catch (RuntimeException exception) {
                if (transaction != null)
                    transaction.rollback();
            }
        }
        finally {
            close();
        }
        return null;
    }

    @Override
    public void update(Long aLong, Joc entity) {
        initialize();
        try (Session session = sessionFactory.openSession()) {
            Transaction transaction = null;
            try {
                transaction = session.beginTransaction();
                session.update(entity);
                transaction.commit();
            } catch (RuntimeException exception) {
                if (transaction != null)
                    transaction.rollback();
            }
        }
        finally {
            close();
        }
    }

    @Override
    public Joc findOne(Long aLong) {
        initialize();
        Joc joc = null;
        try (Session session = sessionFactory.openSession()) {
            Transaction transaction = null;
            try {
                transaction = session.beginTransaction();

                joc = session.createQuery("from joc where id=:idx" , Joc.class)
                        .setParameter("idx", aLong)
                        .getSingleResult();

                transaction.commit();

                return joc;
            } catch (RuntimeException exception) {
                if (transaction != null)
                    transaction.rollback();
            }
        }
        finally {
            close();
        }
        return null;
    }

    @Override
    public List<Joc> findAll() {
        initialize();
        List<Joc> jocuri = new ArrayList<>();
        try (Session session = sessionFactory.openSession()) {
            Transaction transaction = null;
            try {
                transaction = session.beginTransaction();
                jocuri = session.createQuery("select a from joc a", Joc.class).getResultList();

                transaction.commit();

            } catch (RuntimeException exception) {
                if (transaction != null)
                    transaction.rollback();
            }
        }
        finally {
            close();
        }
        return jocuri;
    }
}
