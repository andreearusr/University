package joc.repository;

import joc.domain.Entity;
import java.util.List;

public interface Repository<ID, E extends Entity<ID>> {

    void save(E entity);

    void delete(ID id);

    void update(ID id, E entity);

    E findOne(ID id);

    List<E> findAll();
}
