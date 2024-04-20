<h1>
  Documentation
</h1>
<h2>
  SRB
</h2>
<h3>
  Main.c
</h3>
<p>
  U main funkciji se nalazi glavni loop igre i sadrzi se iz dve funkcije, <b>menuLoop()</b> i <str>gameLoop()</str>, tu je i <b>ghostCheck()</b>, ali on je samo deo <b>gameLoop()</b> funkcije. 
  U <b>menuLoop()</b> funkcij se nalaze sve stvari vezane za renderovanje i navigaciju glavnog menija, koristi funkcije iz <i>MainMenu.c</i>.
</p>
<h3>
  MainMenu.c
</h3>
<p>
  U <i>MainMenu.c</i> fajlu se nalaze sve funkcije i promenljive vezane za renderovanje i navigaciju po meniju. Od promenljivih imamo niz "stringova" u kome je sacuvan logo i promenljivu selectedOption koja nam belezi koje dugme u meniju je selektovano trenutno.
  Postoje tri funkcije u ovom fajlu. Prva, <b>renderLogo()</b>, sluzi za printovanje logoa. Druga, <b>navigateMenu()</b>, nam je funkcija koja menja promenljivu selectedOption i gleda da li smo odabrali opciju (da li smo pritisnuli [SPACE]).
  I treca i poslednja, <b>renderButtons()</b>, stampa "dugmice" menija, i stampa ih razlicito u zavisnosti da li su selectovani.
</p>
<h3>
  Map.c
</h3>
<p>
  Ovaj fajl nam sluzi za sve vezano sa mapom dok igramo igricu. U promenljivama cuvamo "string" mape (map), sirinu i visinu mape (width, heighr) i koliko peleta je ostalo do pobede (pelletCount).
  Prva funkcija je <b>loadMap(char* name)</b> i ona ucitava mapu po imenu fajla unetog. Ako fajl nije nadjen, odmah izlazimo iz funkcije i stampamo odgovarajucu poruku na main meniju. Ako je ipak nadjen map fajl,
  krecemo da ga citamo. Svaki map fajl se sadrzi iz 3 dela: duzine (prvi red), sirine (drugi red) i mape (sve ostalo). Kada nadjemo duzinu i sirinu mape, alociramo memoriju za mapu i onda citamo karakter po karakter i ubacujemo u string mape.
  Ako nadjemo G, namestamo duha, P namestamo igraca, i ., povecavamo pelletCount.
</p>
<p>
  Nakon sto smo namestili mapu imamo 5 malih funkcija koje nam sluze za dobijanje i namestanje raznih delica mape. Funkcija <b>setCell(int x, int y)</b> nam sluzi da pretvorimo polje x, y na prazno polje, ovo se koristi kada igrac pojede pellet.
  Slede 3 funkcije, <b>getWidth()</b>, <b>getHeight</b> i <b>getPelletCount</b> koje samo vracaju promenljive sa istim imenom. Poslednja funkcija ovog fajla je <b>collectPellet()</b> i ona samo umanjuje pelletCount.
</p>
