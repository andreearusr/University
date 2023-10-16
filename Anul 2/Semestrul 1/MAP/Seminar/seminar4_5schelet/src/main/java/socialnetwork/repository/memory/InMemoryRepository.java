package socialnetwork.repository.memory;

import socialnetwork.domain.Entity;
import socialnetwork.domain.validators.Validator;
import socialnetwork.repository.Repository;



import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {

    private Validator<E> validator;
    Map<ID,E> entities;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        entities=new HashMap<ID,E>();
    }


    @Override
    public Optional<E> findOne(ID id) {
        return null;
    }

    @Override
    public Iterable<E> findAll() {
        return null;

    }

    @Override
    public Optional<E> save(E entity)  {
        return null;
    }

    @Override
    public Optional<E> delete(ID id) {
        return null;
    }

    @Override
    public Optional<E> update(E entity) {
        return null;
    }

}
