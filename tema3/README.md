**Simulare de trafic**

In acest folder este tema3 care include si tema1 si tema2.

Aplicatia contine mai multe clase care modeleaza masini, pietoni, strazi, intersectii(cu semafoare), calatori.

Mai jos mentionez (dau cateva exemple) cum au fost indeplinite cerintele: 
**La tema 2 am folosit:**
 - smart pointers: shared_ptr in clasele ...
- moșteniri: din ObiectMiscator sunt derivatele: Masina, Masina_prioritara, Pieton
- funcții virtuale (pure)- din clasa ObiectMiscator
- constructori virtuali (clone) - TODO
- funcțiile virtuale vor fi apelate prin pointeri la clasa de bază: in clasa Run - pointerii la clasa de bază vor fi atribute ale altei clase, nu doar niște pointeri/referințe în main
apelarea constructorului din clasa de bază
 - dynamic_cast - TODO
- suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap - TODO
- excepții: in clasa Eroare din Exceptions.h
- atribute statice
- functii statice - TODO

**La tema 3 am folosit:**

- clasă șablon (template): clasa Subject este template din Subject.h
- minim un atribut de tip T sau care depinde de T
-adăugați (minim) o funcție membru care să depindă de T (sau de alt parametru template);
adăugați (minim) o funcție normală/liberă template; poate să fie friend
 - minim 2 design patterns : 
     - Observer - care contine elemente in Observer.h, Subject.h, Clock.h : exista o clasa Clock care masoara timpul si toate elementele dinamice (Obiectele miscatoare, semafoarele) isi schimba starea atunci cand se schimba timpul
     - StrategyPattern - am adaugat o clasa Calator (Calator.h) care poate folosi diferite tipuri de masini pentru a se deplasa. 
- minim o funcție șablon - TODO


Observatie: inca mai am erori de compilare, deoarece am combinat mai multe elemente avansate si nu am avut timp sa rezolv toate situatiile aparute. Voi modifica cat de curand.
