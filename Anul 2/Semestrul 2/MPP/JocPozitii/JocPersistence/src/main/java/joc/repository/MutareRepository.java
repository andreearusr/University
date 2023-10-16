package joc.repository;

import joc.domain.Mutare;
import joc.domain.MutareDTO;

import java.util.List;


public interface MutareRepository extends Repository<Long, Mutare> {
   // List<Mutare> findJocJucatori(long idJoc, long idJucator);
    /*List<Mutare> findClasament(long idJoc);
    List<Mutare> findJoc(Long idJoc);*/

    List<Mutare> findToateJocuriFinalizate();
    List<MutareDTO> findJocuriFinalizateJucator(Long idJucator);
    Mutare findMutareJucator(Long idJucator);
}
