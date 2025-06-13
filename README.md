# Projekt PSIO: Space Dungeon Roguelike

### Autorzy: Kamil Stankiewicz • Oliwia Strzyzewska

---

## 🛠 Wersja SFML

`SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit`

---

## 🎮 Sterowanie

* `WASD` – poruszanie sie
* `R` – regeneracja zdrowia
* `PPM` / `Spacja` – atak
* `ESC` – zmiana trybu wyswietlania okna
* `P` – pauza

---

## 🕹️ Rozgrywka

- **Generator**  
  Poziomy generowane sa przez proceduralny generator, ktory bazuje na ustawieniach podanych w pliku `parameters_init.txt` oraz na aktualnym poziomie gracza. Wraz ze zdobywaniem kolejnych poziomow doswiadczenia beda pojawiac sie nowe typy przeciwnikow i zwiekszy sie ilosc monet w skrzyniach.  
  
- **Punkty doswiadczenia**  
  Punkty doswiadczenia zdobywa sie za pokonywanie wrogow. Przyrost PD jest kwadratowy (za kazda kolejna eliminacje otrzymuje sie coraz wiecej PD). Za wyeliminowanie wszystkich przeciwnikow i ukonczenie poziomu zdobyte PD sa dodatkowo mnozone. Ilosc otrzymanego PD za przeciwnika i mnoznik za ukonczenie poziomu mozna zmieniac poprzez plik `parameters_init.txt`.  
  
- **Rozwoj postaci**  
  Zdobywajac kolejne poziomy doswiadczenia, zwieksza sie maksymalna liczba punktow zdrowia oraz zadawane obrazenia. Bazowa liczbe PZ mozna zmienic w pliku `parameters_init.txt`. Obrazenia zadawane przeciwnikom to suma obrazen aktualnie wyposazonej broni oraz wartosci wynikajacej z poziomu postaci.  

- **Tempo rozgrywki**  
  Ilosc pojawiajacych sie przeciwnikow, predkosc poruszania sie postaci, predkosc pociskow, zasieg widoku kamery, ilosc zdobywanych PD i wiele wiecej parametrow mozna zmieniac poprzez plik `parameters_init.txt`.  
    
- **Sklep**  
  Za zdobyte monety mozna kupic lepsza bron.  

---

## 📅 Kamienie milowe

- **29.05.2025 18:56** - `add component system`  
  Pelna implementacja systemu scen, obiektow i komponentow (pozniej wprowadzano drobne poprawki). Pierwszym krokiem w tworzeniu gry na tym silniku jest utworzenie klasy dziedziczacej po `Engine`, np klasy `Game`. Nastepnie tworzymy sceny. Kazda scena musi dziedziczyc publicznie po `Scene` i implementowac metode abstrakcyjna `loadObjects`. Kiedy mamy juz gotowa klase sceny, np `MainScene` mozemy utworzyc ja w silniku. Robimy to poprzez metode `createScene<T>` wywolywana w konstruktorze `Game`. W konstruktorze mozemy tez uruchamic scene glowna metoda `changeScene`. Kolejnym krokiem jest utworzenie obiektow i umieszczenie ich na wybranej scenie. Obiektem moze byc kazda klasa bedaca rodzajem klasy `Object`. Obiekty na scenie tworzymy metoda `createObject<T>`, ktora moze zostac wywolana z dowolnego miejsca. Do tworzenia obiektow glownych takich jak `Camera` lub `LevelManager` przeznaczona jest metoda `loadObjects`, ale mozliwe jest takze tworzenie obiektow z poziomu innych obiektow lub componentow. Componenty umieszczane sa w obiektach analogicznie jak w przypadku tworzenia obiektow na scenie. Robimy to metoda `createComponent<T>`. Componentem moze zostac kazda klasa bedaca rodzajem klasy `Component`.

- **01.06.2025 02:36** - `add matrix generation`  
  Wyswietlanie sprite'ow wzgledem kamery (uwzgledniona pozycja, zasieg widzenia i rotacja). Sprite `VSprite`, który jest rodzajem `VRenderable` jest jednym z domyslnie dostepnych w silniku componentow. Umozliwia on nadanie obiektowi tekstury i renderowanie go z uwzglenieniem perspektywy kamery istniejacej na scenie. `VSprite` renderuje sie automatycznie, gdy na obiekcie, do ktorego jest przypisany istnieje component `Transform`. W trakcie renderowania uwzgledniona zostaje nie tylko pozycja i zasieg widzenia kamery `view_size`, ale tez jej obrot, dzieki czemu mozna bylo stworzyc efekt zachwiania kamery w momencie przyjmowania obrazen przez gracza.

- **03.06.2025 20:47** - `add player animations`  
  Pierwsze dzialajace animacje gracza. Animacje opieraja sie na systemie kilku klas: `AnimationStep`, `AnimationCycle`, `Animation` oraz `AnimationController` bedacej componentem. Kazda z tych klas posiada metode `update`, ktora aktualizuje ich stan. `AnimationStep` reprezentuje pojedynczy krok animacji. Jest to klasa abstrakcyjna. Na potrzeby gry zdefiniowane zostaly dwa rodzaje `AnimationStep`, czyli `AnimationTransformStep`, ktory reprezentuje plynna, liniowa zmiane pozycji, rotacji lub skali w podanym czasie i `AnimationTextureStep`, ktory zmienia teksture wyswietlana przez `VSprite` z podanym opoznieniem. Metoda `update` w kroku animacji zwraca `true`, gdy krok sie zakonczy. `AnimationCycle` reprezentuje sekwencje `AnimationStep`. Kroki animacji sa uruchamiane po kolei. Gdy skonczy sie ostatni krok metoda `update` tej klasy zwraca `true`. `Animation` odtwarza rozne `AnimationCycle` rownolegle. Metoda `update` w tej klasie zwraca `true` kiedy zakoncza sie wszystkie cykle. `AnimationController` przechowuje w sobie animacje `Animation`, uruchamia je i zarzadza nimi. Jest on componentem, wiec mozna go utworzyc na obiekcie, aby zarzadzal jego animacjami.  

- **06.06.2025 14:37** - `add entity with basic AI`  
  Przeciwnicy atakuja gracza, gdy go widza. Przeciwnik moze przyjac jeden z trzech stanow: `Sleep`, `Attack`, `Seek`. W stanie `Sleep` nie robi nic, czeka az zostanie pobudzony przez gracza. Gdy zauwazy gracza rozpoczyna `Attack`, czyli podbiega na odleglosc jaka jest wymagana, aby zadac obrazenia z aktualnie uzywanej broni. Kazdy przeciwnik jest rodzajem klasy `Entity`. Sposoby ataku roznych typow przeciwnikow moga sie roznic w zaleznosci od implementacji abstrakcyjnej metody `attack`. Przedstawiony opis ataku dotyczy jedynego zdefiniowanego w grze rodzaju przeciwnika `BasicEntity`. Kazdemu `Entity` moze zostac przypisana dowolna bron istniejaca w grze, a byt `Entity` bedzie w stanie jej uzywac. Mozna dzieki temu tworzyc dowolne kombinacje bytow i broni lub zautomatyzowac to poprzez generator. Gdy przeciwnik straci gracza z pola widzenia przechodzi w stan `Seek`. Zaczyna poruszac sie losowo do momentu az znow zobaczy gracza.

- **09.06.2025 01:21** - `add entities and chests generation`  
  Generator poziomow rozmieszcza przeciwnikow i skrzynie. Kazdy poziom generowany jest losowo przez proceduralny generator. Generator tworzy startowy pokoj, a potem losuje kierunek i dlugosc korytarza. Na koncu korytarza tworzony jest kolejny pokoj. Czynnosc sie powtarza az do osiagniecia zamierzonej ilosci pokoi, ktora jest losowana z zakresu podanego w pliku `parameters_init.txt`. W pliku mozna ustawic tez wiele innych parametrow generatora, takich jak dlugosc i szerokosc korytarzy, albo rozmiar pokoi lub ilosc pojawiajacych sie w nich przeciwnikow i skrzyn. Pokoje sa wypelniane losowymi przeciwnikami. Zakres losowania ustalany jest na podstawie poziomu doswiadczenia gracza. Z czasem jak gracz bedzie zdobywal coraz wyzsze poziomy doswiadczenia, w generowanych poziomach beda pojawiac sie nowi przeciwnicy. Aby utworzyc nowego przeciwnika i uwzglednic go w generatorze - trzeba utworzyc jego `EntityData` i dodac go do kolekcji w klasie `EntitySO`. Byt automatycznie po dodaniu zostanie uwzgledniony w generatorze. `EntityData` jest opisem przeciwnika na podstawie, ktorego generator jest w stanie utworzyc odpowiedni obiekt na scenie.

- **10.06.2025 12:21** - `add player health system`  
  Dodano paski zdrowia i system walki. Kazdy przeciwnik posiada swoj pasek zdrowia, ktory informuje ile obrazen moze jeszcze przyjac dana jednostka zanim zostanie wyeliminowana. Gracz dodatkowo poza swoim paskiem zdrowia wyswietlanym w interfejsie - posiada tez pasek punktow leczenia. Zuzywajac te punkty mozna szybciej regenerowac zdrowie. Regeneracje przeprowadza sie przytrzymujac przycisk `R`. Podczas regeneracji gracz nie moze sie poruszac, namierzac wrogow ani strzelac. Dodatkowo kamera przybliza sie zmniejszajac zakres widocznosci, przez co gracz staje sie odsloniety na niespodziewane ataki. Zdrowie odzyskuje sie takze dzieki naturalnej regeneracji, ktorej tempo mozna dostosowac w pliku `parameters_init.txt`.

- **11.06.2025 22:58** - `milestone 7`  
  Finalna wersja gry (prawie). Dodano rozne efekty specjalne, np efekt czasteczkowy podczas regeneracji zdrowia. Dodano efekty dzwiekowe i soundtrack.

- **13.06.2025** - `milestone 7.1`  
  Finalna wersja gry. Dodano nowych przeciwnikow. Poprawiono balans rozgrywki i kilka bledow. Zuzyte punkty leczenia mozna odzyskiwac eliminujac przeciwnikow.

---

## 📁 Pliki

Wszystkie sciezki do zasobow znajduja sie w pliku:  
`include/game/core/Asset.h`

Assety:
- [TEXTURES](https://0x72.itch.io/16x16-dungeon-tileset)
- [SOUNDTRACK](https://davidkbd.itch.io/purgatory-extreme-metal-music-pack)
- [SFX](https://f8studios.itch.io/snakes-authentic-gun-sounds)

---

## 🎥 Nagranie

[GAMEPLAY](https://youtu.be/KVrBpx0nRoo)

---
