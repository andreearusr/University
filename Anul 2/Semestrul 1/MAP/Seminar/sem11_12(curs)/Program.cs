
using Sem11_12.Model;
using Sem11_12.Model.Validator;
using Sem11_12.Repository;
using Sem11_12.Service;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Security.Cryptography;

namespace Sem11_12
{
    class Program
    {

        static void Main(string[] args)
        {


            List<Angajat> angajati = GetAngajatService().FindAllAngajati();

            List<int> l = new List<int>() { 1,2,3,4,5,6,7,8,9,10};          
            var res=l.Where(x => x % 2 == 0);

            //res.ToList().ForEach(Console.WriteLine);
            Task3();

            // 1. afisati doar angajatii care au nivelul junior - extension methods "Where"

            //2  - cerinta 1 din pdf sem11-12  extension methods 

            //2  - cerinta 1 din pdf sem11-12  sql like 

            //2 cate ore dureaza in medie fiecare tip de sarcina


            //3 primii doi cei mai harnici angajati

        }

        private static void Task1()
        {
            //1.afisati doar angajatii care au nivelul junior -extension methods "Where"
            List<Angajat> angajati = GetAngajatService().FindAllAngajati();
            angajati.Where(x => x.Nivel == KnowledgeLevel.Junior)
                .ToList()
                .ForEach(Console.WriteLine);

        }

        private static void Task11()
        {
            //Sa se afișeze lista de angajați, grupați după nivel. 
            // Mai întâi se vor afișa angajații care sunt juniori, 
            // apoi cei de nivel Medium, iar apoi cei care sunt de nivel Senior, 
            //in cadrul fiecărei grupe angajații se vor afișa ordonați descrescător după venitPeOra

            
            List<Angajat> angajati = GetAngajatService().FindAllAngajati();
            // cu sort
            Console.WriteLine("---------sort------ extension methods like----------");
            angajati.Sort((x, y) =>
            {
                if (x.Nivel == y.Nivel)
                    return -(int)(x.VenitPeOra - y.VenitPeOra);
                return x.Nivel - y.Nivel;
            });
            angajati.ToList()
                .ForEach(Console.WriteLine);

            Console.WriteLine("---------sort------ sql like----------");
            (from angajat in angajati
             orderby angajat.Nivel ascending, angajat.VenitPeOra descending
             select angajat).ToList().ForEach(Console.WriteLine);

            Console.WriteLine("---------group------ extension methods like----------");

        }
        private static void Task2()
        {
            // Sa se det cat castiga in media fiecare nivel de exp
            List<Angajat> angajati = GetAngajatService().FindAllAngajati();
            angajati.GroupBy(a => a.Nivel)
                .Select(a => new { Nivel = a.Key, Media = a.Average(x => x.VenitPeOra) })
                .ToList()
                .ForEach(Console.WriteLine);

        }

        public static void Task3()
        {
            //primii doi cei mai harnici angajati: (nr de ore lucrate X venit pe ora ->maxim)
            List<Pontaj> pontaje = GetPontajService().FindAllPontaje();

            pontaje.GroupBy(x => x.Angajat)
              .Select(g => new { Nume = g.Key.Nume, Salar = g.Sum(x => x.Sarcina.NrOreEstimate * x.Angajat.VenitPeOra) })
              .OrderByDescending(x => x.Salar)
              .ToList()
              .Take(2)
              .ToList()
              .ForEach(Console.WriteLine);
        }


        private static AngajatService GetAngajatService()
        {
            //string fileName2 = ConfigurationManager.AppSettings["angajatiFileName"];
            string fileName = "..\\..\\..\\data\\angajati.txt";
            IValidator<Angajat> vali = new AngajatValidator();

            IRepository<string, Angajat> repo1 = new AngajatInFileRepository(vali, fileName);
            AngajatService service = new AngajatService(repo1);
            return service;
        }

        private static SarcinaService GetSarcinaService()
        {
            //string fileName2 = ConfigurationManager.AppSettings["sarciniFileName"];
            string fileName2 = "..\\..\\..\\data\\sarcini.txt";
            IValidator<Sarcina> vali = new SarcinaValidator();

            IRepository<string, Sarcina> repo1 = new SarcinaInFileRepository(vali, fileName2);
            SarcinaService service = new SarcinaService(repo1);
            return service;
        }

        private static PontajService GetPontajService()
        {
            //string fileName2 = ConfigurationManager.AppSettings["pontajeFileName"];
            string fileName2 = "..\\..\\..\\data\\pontaje.txt";
            IValidator<Pontaj> vali = new PontajValidator();

            IRepository<string, Pontaj> repo1 = new PontajInFileRepository(vali, fileName2);
            PontajService service = new PontajService(repo1);
            return service;
        }

    }
}
