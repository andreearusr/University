package tasks.controller;

import org.junit.jupiter.api.*;
import tasks.model.Task;
import tasks.services.DateService;
import tasks.services.TasksService;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.time.LocalDate;
import java.util.Date;

import static org.junit.jupiter.api.Assertions.*;

@DisplayNameGeneration(DisplayNameGenerator.ReplaceUnderscores.class)
public class NewEditControllerTest {
    public DateService dateService=new DateService();
    public  Date startDateWithNoTime= new Date();
    public  NewEditController ctrl= new NewEditController();
    public Date di,di2,di3= new Date();
    public Date dou,dou2,dou3= new Date();
    public String titleNotEmptyError;
    public String moreTitleCharactersError;
    public String startTimeError;

    @BeforeEach
    public void setUp() {
        ctrl.setService(new TasksService(null));
        startDateWithNoTime = dateService.getDateValueFromLocalDate(LocalDate.now());
        di =dateService.getDateMergedWithTime("8:00", startDateWithNoTime);
        dou =dateService.getDateMergedWithTime("10:00", startDateWithNoTime);
        di2 =dateService.getDateMergedWithTime("13:00", startDateWithNoTime);
        dou2 =dateService.getDateMergedWithTime("15:00", startDateWithNoTime);
        di3 =dateService.getDateMergedWithTime("0:00", startDateWithNoTime);
        dou3 =dateService.getDateMergedWithTime("3:00", startDateWithNoTime);

        titleNotEmptyError = "Title should not be empty";
        moreTitleCharactersError = "Title should not contain more than 20 characters";
        startTimeError = "Start time should be between 0 and 23";
    }

    @Disabled
    @AfterEach
    public void tearDown() {
    }

    @Test
    @Order(1)
    @DisplayName("Test pt ECP valid")
    public void makeTaskECPvalid() {

        Task ecpv = new Task("Mancare",di, dou,1800);

        Task t = ctrl.makeTask("Mancare", LocalDate.now(),"8:00",LocalDate.now(),"10:00","0:30",true);

        assertEquals(t.getTitle(),ecpv.getTitle());
        assertEquals(t.getRepeatInterval(),ecpv.getRepeatInterval());

    }

    @Test
    @Order(2)
    public void makeTaskECPinvalid1() {
          Task ecpi= new Task("Iesiredupamasaaceastaa",di2, dou2,1800);
          Task t= null;

        try {
            t = ctrl.makeTask("Iesiredupamasaaceastaa", LocalDate.now(),"13:00",LocalDate.now(),"15:00","0:30",true);
            assertNotEquals(t.getTitle(),ecpi.getTitle());
        }
        catch (Exception e){
            assertEquals(t,null);
            assertEquals(e.getMessage(), moreTitleCharactersError);
        }
    }

    @Test
    @Order(3)
    public void makeTaskECPinvalid2() {
        Task ecpi = new Task("",di2, dou2,1800);
        Task t= null;

        try {
            t = ctrl.makeTask("", LocalDate.now(),"-5:00",LocalDate.now(),"15:00","0:30",true);
            assertNotEquals(t.getTitle(),ecpi.getTitle());
        }
        catch (Exception e){
            assertEquals(t,null);
            assertEquals(e.getMessage(), titleNotEmptyError);
        }
    }

    @Test
    @Order(4)
    public void makeTaskECPinvalid3() {
        Task ecpi = new Task("Da",di2, dou2,1800);
        Task t= null;

        try {
            t = ctrl.makeTask("Da", LocalDate.now(),"34:00",LocalDate.now(),"23:00","0:30",true);
            assertNotEquals(t.getTitle(),ecpi.getTitle());
        }
        catch (Exception e){
            assertEquals(t,null);
            assertEquals(e.getMessage(), startTimeError);
        }
    }


    @Test
    @Order(5)
    public void makeTaskBVAvalid1() {

        Task bvav = new Task("A",di3, dou3,1800);

        Task t = ctrl.makeTask("A", LocalDate.now(),"0:00",LocalDate.now(),"10:00","0:30",true);

        assertEquals(t.getTitle(),bvav.getTitle());
        assertEquals(t.getRepeatInterval(), bvav.getRepeatInterval());
    }

    @Test
    @Order(6)
    public void makeTaskBVAvalid2() {

        Task bvav = new Task("Mainemergemacasasasa",di3, dou3,1800);

        Task t = ctrl.makeTask("Mainemergemacasasasa", LocalDate.now(),"23:00",LocalDate.now(),"23:10","0:30",true);

        assertEquals(t.getTitle(),bvav.getTitle());
        assertEquals(t.getRepeatInterval(), bvav.getRepeatInterval());
    }

    @Test
    @RepeatedTest(3)
    @Order(7)
    public void makeTaskBVAinvalid1() {
        Task bvai = new Task("",di3, dou3,1800);
        Task t= null;

        try {
            t = ctrl.makeTask("", LocalDate.now(),"-1:00",LocalDate.now(),"23:00","0:30",true);
            assertNotEquals(t.getTitle(),bvai.getTitle());
        }
        catch (Exception e){
            assertEquals(t,null);
            assertEquals(e.getMessage(),titleNotEmptyError);
        }
    }

    @Test
    @Order(8)
    public void makeTaskBVAinvalid2() {
        Task bvai = new Task("Mainemergemacasasasas",di3, dou3,1800);
        Task t= null;

        try {
            t = ctrl.makeTask("Mainemergemacasasasas", LocalDate.now(),"24:00",LocalDate.now(),"20:00","0:30",true);
            assertNotEquals(t.getTitle(),bvai.getTitle());
        }
        catch (Exception e){
            assertEquals(t,null);
            assertEquals(e.getMessage(),moreTitleCharactersError);
        }
    }
    }