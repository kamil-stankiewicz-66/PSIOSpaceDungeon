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
  Pelna implementacja systemu scen, obiektow i komponentow (pozniej wprowadzano drobne poprawki).

- **01.06.2025 02:36** - `add matrix generation`  
  Wyswietlanie sprite'ow wzgledem kamery (uwzgledniona pozycja, zasieg widzenia i rotacja).

- **03.06.2025 20:47** - `add player animations`  
  Pierwsze dzialajace animacje gracza.

- **06.06.2025 14:37** - `add entity with basic AI`  
  Przeciwnicy atakuja gracza, gdy go widza.

- **09.06.2025 01:21** - `add entities and chests generation`  
  Generator poziomow rozmieszcza przeciwnikow i skrzynie.

- **10.06.2025 12:21** - `add player health system`  
  Dodano paski zdrowia i system walki.

- **11.06.2025 22:58** - `milestone 7`  
  Finalna wersja gry (prawie).

- **12.06.2025 - `milestone 7.1`  
  Finalna wersja gry.

---

## 📁 Pliki

Wszystkie sciezki do zasobow znajduja sie w pliku:  
`include/game/core/Asset.h`

Assety:
- [TEXTURY](https://0x72.itch.io/16x16-dungeon-tileset)
- [MUZYKA](https://davidkbd.itch.io/purgatory-extreme-metal-music-pack)
- [EFEKTY DZWIEKOWE](https://f8studios.itch.io/snakes-authentic-gun-sounds)

---

## 🎥 Nagranie

[GAMEPLAY](https://youtu.be/KVrBpx0nRoo)

---
