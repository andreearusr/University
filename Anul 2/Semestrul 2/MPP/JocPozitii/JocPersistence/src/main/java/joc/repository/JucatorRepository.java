package joc.repository;

import joc.domain.Jucator;

public interface JucatorRepository extends Repository<Long, Jucator> {
    Long getId(String username);
    //Jucator findOneAlias(String aliass);
}
