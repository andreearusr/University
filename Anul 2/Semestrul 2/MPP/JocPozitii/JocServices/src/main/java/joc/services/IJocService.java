package joc.services;

import joc.domain.Mutare;
import joc.domain.Jucator;

import java.util.List;

public interface IJocService {

   // List<Jucator> getJucatori() throws LogException;

    void logIn(Jucator jucator, IJocObserver client) throws LogException;

    void logOut(Jucator jucator, IJocObserver client) throws LogException;

    Jucator findJucatorByUsername(String username) throws LogException;

    Mutare startJoc(Jucator jucator, IJocObserver client) throws LogException;

    List<Mutare> getClasament() throws LogException;

    void updateClasament(List<Mutare> clasament) throws LogException;

    Mutare getMutareJucator(Long idJucator) throws LogException;

    void updateMutare(Long idMutare, Mutare mutare) throws LogException;

    /*Long startJoc(Jucator jucator, IJocObserver client) throws LogException;

    void incepeJoc(Long idJoc) throws LogException;

    List<Mutare> getJocJucatori(Long idJoc) throws LogException;*/

   /* List<Show> getShows() throws LogException;

    List<Show> getArtistsByDate(Timestamp date) throws LogException;

    void buyTicket(Ticket ticket) throws LogException;

    void updateShow(Long showId, Show newShow) throws LogException;

    Show findShowById(Long showId) throws LogException;

    OfficeEmployee findEmployeeByUsername(String username) throws LogException;



*/
}
