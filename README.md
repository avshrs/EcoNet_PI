# EcoNet na Raspberry PI 
(Po zmianie linkowania do libek w cmake również na x86_64)

Integracja urządzeń firmy Plum z Home Assistant napisana w C++

Obsługiwane urządznia:
Ecomax 920p i Ecoster Touch
 
 
**Pobieranie informacji ze sterownika:**
* Sterownik
   * Ramka z danymi live
       * Aktualny status sterownika (praca, postój...)
       * Aktualna temperatura CWU
       * Aktualna temperatura CO mieszacza
       * Aktualna temperatura kotła
       * Aktualna temperatura kotła - powrót
       * Aktualna temperatura spalin
       * Aktualna temperatura podajnika / palnika
       * Aktualna wartość czujnika płomienia
       * Aktualna temperatura zasobnika górna
       * Aktualna temperatura zasobnika dolna
       * Zadana temperatura CWU
       * Zadana temperatura mieszacza
       * Zadana temperatura kotła
       * Aktualny poziom paliwa
       * Aktualna moc nawiewu
       * Aktualna moc wywiewu
       * Aktualna moc kotła w kW
       * Aktualna dawka paliwa
       * dodatkowe dane: czas pracy, ilość rozpaleń...
 
   * Ramka z ustawieniami
       * Maksymalna moc kotła
       * Średnia moc kotła
       * Minimalna moc kotła
       * Maksymalna moc wiatraka
       * Średnia moc wiatraka
       * Minimalna moc wiatraka
       * Wydajność podajnika
       * Zadana temperatura kotła
       * Zadana temperatura CWU
       * Zadana temperatura mieszacza 
       * Priorytet CWU
       * Histereza CWU
       * Sterylizacja CWU
       * tryb lato zima auto
 
* Termostat
   * Ramka z danymi live
       * Aktualna temperatura zadana
       * Aktualna temperatura pomieszczenia
   * Ramka z ustawieniami
       * Tryb termostatu
       * Temperatura trybu impreza
       * Temperatura trybu wakacje
       * Czas trybu poza domem
       * Czas trybu wietrzenie
       * Czas trybu impreza
       * Czas trybu wakacje
       * histereza termostatu
       * termostat temperatura dzień
       * termostat temperatura noc
 
**Ustawianie parametrów:**       
* Termostat
   * temperatura nocna
   * temperatura dzienna
   * tryb działania
   * histereza
   
* Sterownik
   * Temperatura CWU
   * Tryb CWU
   * Histereza CWU
   * Sterylizacja CWU
   * Tryb lato, zima, auto
   * Temperatura kotła
   * Kocioł on/off
   * Temperatura mieszacza
   * Maxymalna moc kotła
   * Średnia moc kotła
   * Minimalna moc kotła
   * Maxymalna moc wiatraka
   * Średnia moc wiatraka
   * Minimalna moc wiatraka
 
 
**Komunikacja**
* Do komunikacji używam zwykłego konwertera rs485 na usb CH340 (za ok 8zł ze znanego portalu aukcyjnego).
**Info**
* Niestety nie miałem czasu analizować i wyłapać ramki z zapytaniem o konfigurację, dlatego odczyt ramek z ustawieniami odbywa się na razie tylko po zmianie ustawień. w trakcie działania to nie przeszkadza bo dane są buforowane i uaktualniane w przypadku zmiany.
Pierwsze uruchomienie wymaga set'ow aby master rozgłosił ramki z ustawieniami.
 
**Home Assistant** 
* plik HA_config zawiera moje ustawienia - przykład użycia.
 
**Todo**
* Złapać ramkę/sekwencję ramek podczas startu econet albo ecoster, która prosi mastera o rozgłoszenie ramek z ustawieniami aby użyć jej do odczytu ustawień przy starcie aplikacji i ewentualnemu wymuszaniu uaktualnienia ustawień.
 
 
 
 

