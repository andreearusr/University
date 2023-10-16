package joc.services.rest;

import joc.domain.Configuratie;
import joc.repository.ConfiguratieRepository;
import joc.repository.RepositoryException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

@RestController
@CrossOrigin
@RequestMapping("/joc/Configuratie")
public class ConfiguratieController {

    @Autowired
    private ConfiguratieRepository configuratieRepository;

    @RequestMapping(method = RequestMethod.POST)
    public void create(@RequestBody Configuratie configuratie){
        configuratieRepository.save(configuratie);
    }

    @ExceptionHandler(RepositoryException.class)
    @ResponseStatus(HttpStatus.BAD_REQUEST)
    public String jocError(RepositoryException e) {
        return e.getMessage();
    }

}


