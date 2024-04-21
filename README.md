<h1>
  Documentation
</h1>
<h2>
  SRB
</h2>
<h2>
  Main.c
</h2>
<p>
  U main funkciji se nalazi glavni loop igre i sadrzi se iz dve funkcije, <b>menuLoop()</b> i <str>gameLoop()</str>, tu je i <b>ghostCheck()</b>, ali on je samo deo <b>gameLoop()</b> funkcije. 
  U <b>menuLoop()</b> funkcij se nalaze sve stvari vezane za renderovanje i navigaciju glavnog menija, koristi funkcije iz <i>MainMenu.c</i>.
</p>
<h2>
  MainMenu.c
</h2>
<p>
  U <i>MainMenu.c</i> fajlu se nalaze sve funkcije i promenljive vezane za renderovanje i navigaciju po meniju. Od promenljivih imamo niz "stringova" u kome je sacuvan logo i promenljivu selectedOption koja nam belezi koje dugme u meniju je selektovano trenutno.
  Postoje tri funkcije u ovom fajlu. Prva, <b>renderLogo()</b>, sluzi za printovanje logoa. Druga, <b>navigateMenu()</b>, nam je funkcija koja menja promenljivu selectedOption i gleda da li smo odabrali opciju (da li smo pritisnuli [SPACE]).
  I treca i poslednja, <b>renderButtons()</b>, stampa "dugmice" menija, i stampa ih razlicito u zavisnosti da li su selectovani.
</p>
<h2>
  Map.c
</h2>
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
<h2>
  Player.c
</h2>
<p>
  U ovom fajlu se javlja nas prvi "custom tip podataka", enum Direction. Direction cuva stranu na koju ide igrac. Osim toga <i>Player.c</i> je fajl za sve sto je vezano za igraca. Sadrzi neke proste funkcije: <b>getPlayerPos(), setPlayerPos(int x, int y),
  getPlayerDirection(), getNextDirection() i isPlayerHere()</b> i ove funkcije rade tacno sto njihovo ime kaze. 
</p>
<p>
  Tu je i funkcija <b>setupPlayer(int x, int y)</b> koja namesta igraca na pocetku igre. Ostaju nam funkcije <b>handleInput(char input)</b> 
  uzima input sa tastaturei pokusava da zarotira igraca na osnovu toga koristeci funkciju <b>changeDirection(Direction dir)</b>, ova funkcija radi tako sto prvo proveri da li ima zid na unetoj poziciji, ako nema zarotira igraca da ide na tu stranu, a ako ima, 
  sacuva stranu na koju smo zeleli da se zarotiramo i zarotira igraca kada na toj strani ne bude zid. Kad kazem zarotira, jednostavno mislim na menjanje promenljive currentDirection koja se koristi u funkciji <b>movePlayer()</b>. Ona pomeraigraca ako moze 
  odredjenom direkcijom i ako predje preko pelleta, sakuplja ga. Igraceva pozicija se cuva koriscenjem vektora.
</p>
<h2>
  Vectors.c
</h2>
<p>
    Ovaj fajl nam sluzi za kreiranje strukture Vector2 koju koristimo da prikazemo pozicju na gridu na kome se odigrava igra. Njene funkcije su <b>distance(Vector2 a, Vector2 b)</b> koja racuna razdaljinu izmedju dve tacke i <b>getOffset(Vector2 a, Vector2 b)</b>
    koja racuna koliko se razlikuje x i koliko y koordinata dva vektora. Vector2 struktura se koristi za poziciju igraca i duhova.
</p>
<h2>
    Queue.c
</h2>
<p>
    Ovo mi je bilo potrebno da bih implementirao pathfinding algoritam za duhove. Promenljive ovog fajla su queue[500], niz koji se ponasa kao queue pozicia i queueLength. Funkcije su <b>enqueue(Vector2 item)</b> koja ubacuje poziciju na kraj niza odnosno na 
    poziciju queueLength, <b>dequeue()</b> koja izbacuje poziciju sa pocetka i pomera sve ostale pozicije za jedan indeks u desno. Ostale dve funkcije su <b>clearQueue()</b> koja prazni queue i <b>getQueueLength()</b>.
</p>
<h2>
    Ghosts.c
</h2>
<p>
    <i>Ghosts.c</i> je najveci fajl koji sam verovatno mogo da razdvojim u fajl poseban za sve duhove ali eto sve vezano za duhove je ovde. Deli se na 5 sekcije i ima puno promenljivih. Promenljive su ghostSpawns[4], niz pozicija koji cuva pocetnu poziciju svakog 
    duha i ozncava se sa 'G' u map fajlu. posle toga imamo 4 promenljive za svakog od duhova one sluze za cuvanje njihove trenutne pozicije, njihovog puta, njihovog movement indexa i njihovog moda koji je "novi tip podataka" odnosno enum. I ostaju nam 2 promenljive
    vezane za pathfindih, exploredTiles novog tipa ExploredTile koji koritiomo da nadjemo put tokom pathfindinga, exploredTilesIndex da znamo koliko tajlova smo istrazili i ghost movement koji sluzi da menja brzinu duhova.
</p>
<h3>
    GHOST MOVEMENT SECTION
</h3>
<p>
    U ovom delu koda su sve funkcije za pomeranje duhova. Svaki duh drugacije radi ali imaju krajnju poziciju i svi racunaju novi put kada im je movementIndex = -1. Ako je duh uplasen, pomera se svaki drugi frame.
</p>
<h3>
    GHOST MANAGEMN SECTION
</h3>
<p>
    Sekcija za rad sa duhovima, prva funkcija je <b>setupGhost(int ghostId, int x, int y)</b> sluzi za namestanje duha i njegovog spawna. Onda imamo funkciju <b>frightenGhosts()</b> koja se poziva kada igrac pojede veliki pellet i ona plasi sve duhove, slicnu
    njoj imamo funkciju <b>isGhostFrightened(int ghostId)</b> koja proverava da li je duh uplasen. I konacno imamo funkcije <b>isGhostHere(int x, int y)</b> koja proverava da li je duh tu i <b>eatGhost(int ghostId)</b> koja jede duha i vraca ga na pocetnu poziciju
</p>
<h3>
    EXPLORED TILE MANAGEMENT SECTION
</h3>
<p>
    Ovaj deo koda sadrzi 3 funkcije. Prva od njih je <b>isTileExplored(Vector2 tile)</b> i ona proverava da li je dat tile istrazen. Druga je <b>getTileAdress(Vector2 pos)</b>, ova funkcija vraca indeks iz niza explored tiles za odredjenu poziciju.
    I poslednja <b>findClosestValidTile(Vector2 tile)</b> pronalazi najblizi istrazen tile odabranom tileu.
</p>
<h3>
    PATHFINDING SECTION
</h3>
<p>
    U ovom delu koda se nalaze funkcije za nalazenje najkraceg puta izmedju dve tacke na mapi. Funkcije su: <b>pathfind(Vector2 startPos, Vector2 endPos, Vector2* ghostPath)</b> koja ide kroz queue tajlova i istrazuje okruzne neistrazene tajlove koristeci <b>
    explore(Vector2 newPos, Vector2 endPos, ExploredTile* origin)</b> funkciju koja proverava da li je trenutantile validan i <b>offsetPosition(Vector2* pos, int xOffset, int yOffset)</b> koja sluzi za dobijanje pozicije do koje idu neki od duhova.
    Vise o pathfindig algoritmu koriscenom <a href = "https://en.wikipedia.org/wiki/Breadth-first_search">ovde</a>.
</p>
<h2>
    Render.c
</h2>
<p>
    Ovaj fajl sadrzi sve vezano za renderovanje igre. Za renderovanje boje koristi ANSI escape karaktere, vise o njima <a href = "https://en.wikipedia.org/wiki/ANSI_escape_code#Colors">ovde</a>. Promenljive ovog fajla su mapDimensions koja cuva dimenzije mape
    za renderovanje i ghost flash koja belezi da li duh treba da bude plav ili siv kada je uplasen. Prva funkcija samo namesta mapDimensions promenljivu a ostatak renderovanja se sastoji iz glavne <b>renderGame()</b> funkcije i dve pomocne funkcije 
    <b>renderPlayer() i renderGhost()</b>. Renderovanje je odradjeno karakter po karakter i ekran se cisti svakih 200ms.
</p>
<h2>
    Scoreboard.c
</h2>
<p>
    Fajl za pisanje i citanje iz scoreboard.txt fajla. Sastoji se iz dve funkcije <b>displayScoreboard() i addScore(int score, char name[3])</b>. Prva prikazujescoreboard, odnosno sva vremena i imena ljudi koji su presli mapu i poziva se sa main menija. 
    Druga se poziva kada igrac sakupi sve pelete i upisuje novi score u fajl.
</p>
