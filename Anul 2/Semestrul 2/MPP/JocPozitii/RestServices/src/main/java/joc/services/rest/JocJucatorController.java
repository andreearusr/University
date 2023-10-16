package joc.services.rest;


import joc.domain.MutareDTO;
import joc.repository.MutareRepository;
import joc.repository.RepositoryException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

import java.util.List;


@RestController
@CrossOrigin
@RequestMapping("/joc/Mutare")
public class JocJucatorController {

    private static final String template = "Hello, %s!";

    @Autowired
    private MutareRepository mutareRepository;


    /*@RequestMapping("/greeting")
    public  String greeting(@RequestParam(value="name", defaultValue="World") String name) {
        return String.format(template, name);
    }*/

    @RequestMapping(value = "/jucator/{idJucator}/jocFinalizat", method = RequestMethod.GET)
    public List<MutareDTO> getJocuriFinalizate(@PathVariable Long idJucator) {
        System.out.println("Get by id " + idJucator);
        List<MutareDTO> jocuriFinalizate = mutareRepository.findJocuriFinalizateJucator(idJucator);

        return jocuriFinalizate;
    }





/*
    @RequestMapping( method=RequestMethod.GET)
    public List<Artist> getAll(){
        System.out.println("Get all users ...");
        return artistRepository.findAll();
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<?> getArtistById(@PathVariable Long id){
        System.out.println("Get by id "+id);
        Artist artist=artistRepository.findOne(id);
        if (artist==null)
            return new ResponseEntity<String>("Artist not found",HttpStatus.NOT_FOUND);
        else
            return new ResponseEntity<Artist>(artist, HttpStatus.OK);
    }

    @RequestMapping(method = RequestMethod.POST)
    public void create(@RequestBody Artist artist){
        artistRepository.save(artist);
    }
;
    @RequestMapping(value = "/{id}", method = RequestMethod.PUT)
    public void update(@RequestBody Artist artist) {
        System.out.println("Updating user ...");
        artistRepository.update(artist.getId(),artist);
    }

    // @CrossOrigin(origins = "http://localhost:3000")
    @RequestMapping(value="/{id}", method= RequestMethod.DELETE)
    public ResponseEntity<?> delete(@PathVariable Long id){
        System.out.println("Deleting user ... "+id);
        try {
            artistRepository.delete(id);
            return new ResponseEntity<Artist>(HttpStatus.OK);
        }catch (RepositoryException ex){
            System.out.println("Ctrl Delete artist exception");
            return new ResponseEntity<String>(ex.getMessage(),HttpStatus.BAD_REQUEST);
        }
    }
*/


    @ExceptionHandler(RepositoryException.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public String jocError(RepositoryException e) {
        return e.getMessage();
    }

}
