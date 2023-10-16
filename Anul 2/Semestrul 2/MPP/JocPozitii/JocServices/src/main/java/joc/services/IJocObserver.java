package joc.services;


import joc.domain.Joc;
import joc.domain.Mutare;

import java.util.List;

public interface IJocObserver {
    //void inceputJoc(Long idJoc) throws  LogException;

    void clasamentUpdated(List<Mutare> clasament) throws LogException;

}
