<h1 style="text-align:center"> Klasyfikacja zasad 1D automaty Wolframa, za pomocą testu losowości generatora liczb pseudolosowych "Wand"</h1>


<h2 style="text-align:center"> Autor: Piotr Drabik</h2>
<!-- <h2 style="text-align:center"> Zadanie 1: </h2> -->




<p style="page-break-after: always;"> </p> 

## Spis treści 
 - Problematyka
   - Definicja jednowymiarowej automaty Wolframa
   - Cztery klasy podziału
   - Problematyka zadania  
 - Wprowadzenie teoretyczne
   - Lista użytych narzędzi
   - Legenda do generowanych obrazów automaty
   - Definicja generatora liczb losowych "Wand"
 - Teza
    - Opis procesu analizy
    - Definicja kryteriów przydziału zasad automaty do klas 
 - Argumentacja dla wybranych zasad
    - Zasada 3
    - Zasada 107
    - Zasada 120
    - Zasada 55
    - Zasada 68
 - Podsumowanie
 - Bibliografia

<p style="page-break-after: always;"> </p> 

## Problematyka

### Definicja jednowymiarowej automaty Wolframa
Automata komórkowa zaproponowana Stephena Wolframa, to jednowymiarowy system wzajemnie połączonych komórek mogących znajdować się w jednym z dwóch stanów, włączonym albo martwym. Tego rodzaju układ możemy przyrównać do dowolnej długości taśmy o szerokości pojedynczej komórki. 

<p style="text-align:center" style = "font-size: x-small;">
<img  src="tape_image.png" alt="rysunek-taśmy" />

[1] Wizualizacja taśmy automaty o szerokości 10 elementów, 
białym kolorem oznaczone są komórki żywe.
</p>

Każda komórka na taśmie posiada dwóch sąsiadów, lewego i prawego, każdy mogący znajdować sie w jednym z dwóch stanów. 

Generacja nowego stanu opiera sie na pomiarze stanów komórek z poprzedniej generacji i poddaniu ich funkcji n zasady automaty oznaczonej r. Wzór określający stan i'tej komórki w generacji t:

<p style="text-align:center" >x<sub>( t, i )</sub> = r ( x<sub>(t - 1 , i - 1)</sub>, x<sub>(t - 1, i)</sub>, x<sub>(t - 1, i + 1)</sub> )</p>

 Należy zauważyć że zarówno stan komórek jak i ich pozycja na taśmie ma znaczenie: 

<p style="text-align:center" >r(x<sub>1</sub>,x<sub>2</sub>,x<sub>3</sub>)  =/=  r(x<sub>3</sub>,x<sub>2</sub>,x<sub>1</sub>)</p>  

Obserwacja ta prowadzi do następującej konkluzji: 

w systemie jednowymiarowej automaty Wolframa przy promieniu sąsiedztwa 1 i dwu stanowej naturze komórek istnieje tylko 255 możliwych reguł r.

Zwyczajowo reguły oznacza się liczbami w zakresie <0,255>.   

Krańce taśmy na potrzeby rozważań w tej pracy będą ze sobą połączone, tworząc walec.

<!-- <p style="page-break-after: always;"> </p>  -->

### Cztery klasy podziału

Stephen Wolfram na łamach swojej słynnej publikacji ***"A new kind of Science"*** i kilku pracach z lat 80' proponuje klasyfikacje automat komórkowych na cztery kategorie, opisujące tendencje zachowania symulacji. 

Cztery klasy to:
   1. ***"Nearly all initial patterns evolve quickly into a stable, homogeneous state. Any randomness in the initial pattern disappears."***
   ~ Symulacja szybko dąży do stanu stabilnego, losowość stanu początkowego zanika. 

   2. ***"Nearly all initial patterns evolve quickly into stable or oscillating structures. Some of the randomness in the initial pattern may filter out, but some remains. Local changes to the initial pattern tend to remain local."***
   ~ Symulacja szybko dąży do stanu stabilnego, losowość stanu początkowego zanika lecz nie w całości. 

   3. ***"Nearly all initial patterns evolve in a pseudo-random or chaotic manner. Any stable structures that appear are quickly destroyed by the surrounding noise. Local changes to the initial pattern tend to spread indefinitely."***
   ~ Symulacja szybko dąży do stanu pseudo losowego. Pośród generowanego szumu pojawiają się stabilne strontowy które szybko podlegają destrukcji. 

   4. ***"Nearly all initial patterns evolve into structures that interact in complex and interesting ways, with the formation of local structures that are able to survive for long periods of time"***
   ~ Symulacja rozwija się w skomplikowane struktury które są w stanie długo opierać się destrukcji.



   W przypadku analizowanej w tym dokumencie automaty klasy rozumie się następująco:

   1. Symulacja dąży do stanu stabilnego, po osiągnięciu tego stanu każda kolejna iteracja jest identyczna do poprzedniej.

   2. Symulacja dąży do stanu stabilnego, po osiągnięciu tego stanu identyczne do siebie iteracje powtarzają się cyklicznie ze stałą częstotliwością.
   
   3. Symulacja dąży do stanu losowego. 

   4. Symulacja tworzy powtarzalne struktury które opierają się wygłuszają.


### Problematyka zadania  

   Celem tego dokumentu jest opracowanie uniwersalnej metodologi klasyfikacji zasad jednowymiarowej automaty komórkowej Wolframa i za pomocą przygotowanych narzędzi, przeprowadzić klasyfikację następujących zasad: 
   3, 16, 19, 42, 55, 68, 81, 107, 120, 133, 146, 159, 172, 185, 198, 211, 224, 237, 250. 

## Wprowadzenie teoretyczne 
   
### Lista użytych narzędzi

Potrzebne narzędzia do generowania obrazów automaty i ich analizy napisane zostały w języku c++. 

Do wizualizacji przebiegu czasowego automaty użyto biblioteki [SFML](https://www.sfml-dev.org).

Wszystkie grafy wygenerowane zostały za pomocą biblioteki [ROOT](https://root.cern.ch).

### Legenda do generowanych obrazów automaty

Na obrazie [2] przedstawiono przykładowy przebieg czasowy automaty wygenerowany dla zasady 30, stan początkowy został wygenerowany losowo z wypełnieniem 30%. Generowana automata ma szerokość 72 komórek, pod sobą wyświetlone są kolejne 72 generacje. Należy zaznaczyć iż ukazane stany nie są pierwszymi następującymi po stanie początkowym. Ukazany wycinek obrazuje stany automaty od 144 iteracji do 216. Pionowa ściana odpowiada osi czasu, a na poziomej nałożone są kolejne stany jakie przyjmuje automata  
 
<p style="text-align:center" style = "font-size: x-small;">
<img  src="example_image.png" alt="Przebieg-czasowy-dla-zasady-30" />

[2] Przebieg czasowy dla zasady 30 i losowo wygenerowanego stanu początkowego.
</p>

### Definicja generatora liczb losowych "Wand"

Generator liczb pseudo losowych "Wand" to opierający się losowości sumy komórek generowanych w kolejnych stanach automaty. Generator przy generowaniu kolejnych stanów symulacji nie bierze pod uwagę chaosu wynikającego z początkowego stanu automaty. Suma obliczana jest poprzez zliczanie stanów komórek w pojedynczej generacji automaty. Następnie wartość ta jest normalizowana. 

<p style="page-break-after: always;"> </p> 

``` c++

/// \param rule rule witch will be used to generate successive values 
/// \param seed the initial state 
/// \return sudo random value in range <0,1> 
double Wand(AutomataInfo rule, const Slice &seed) {
  static std::map<int, Slice> buffer;

  if (buffer.find(rule.rule_dec) == buffer.end()) {

    Slice slice(seed);
    for (int i = 0; i < seed.GetWidth() * 3; i++)
      slice.GenerateSuccessor(rule);

    buffer.insert({rule.rule_dec, slice});
  }

  buffer[rule.rule_dec].GenerateSuccessor(rule);

  double sum = 0;

  for (int i = 0; i < buffer[rule.rule_dec].GetWidth(); i++)
    if (buffer[rule.rule_dec][i])
      sum += 1;

  return sum / (double)buffer[rule.rule_dec].GetWidth();
}

```
Suma dla przykładowego obrazu [1] o szerokości 10 wynosi 4. Wygenerowana liczba losowa przez algorytm Wand wynosiłaby 0.4. 

## Teza

Podstawowa analiza cykliczności zasady automaty wraz z analizą rozkładu wartości generowanych przez generator Wand, oparty na danej zasadzie i losowo wygenerowanej warstwie początkowej. Mogą zostać skutecznie użyte do definitywnej klasyfikacji badanej zasady.

### Opis procesu analizy

Do klasyfikacji wybranej zasady automaty należy:

1. Zbadać okres jej powtarzalności. 
Należy w tym miejscu zaznaczyć iż przy stosowanej w tej pracy zasadzie "zawijania" brzegów taśmy, występować muszą powtórzenia warstw spowodowane przez "zawinięcie" się wzorów dookoła taśmy. Takie przypadki powtórzenia nie będą brane pod uwagę. 

2. Zmierzyć rozkład generowanych wartości przez generator Wand dla danej zasady. Następnie przyrównać otrzymany do rozkładu normalnego.   


### Definicja kryteriów przydziału zasad automaty do klas 

1. Zasada należy do grupy pierwszej jeżeli jej okres jest równy 1.

2. Zasada należy do grupy drugiej jeżeli jej okres jest równy n, gdzie n >1 i n < oo.

3. Zasada należy do grupy trzeciej jeżeli jej okres dla taśmy o nieskończonej długości jest nieskończony i rozkład wartości generowanych przez algorytm Wand, oparty na danej zasadzie jest rozkładem normalnym.  

4. Zasada należy do grupy czwartej jeżeli jej okres dla taśmy o nieskończonej długości jest nieskończony i rozkład wartości generowanych przez algorytm Wand, oparty na danej zasadzie nie jest rozkładem normalnym.  

<p style="page-break-after: always;"> </p> 

## Argumentacja dla wybranych zasad
   
### Zasada 3

<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_3_graph.png" alt="zasada3_rozkład" />

[3] Rozkład wylosowanych wartości.

<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_3_size_72.png" alt="zasada3_przebieg_czasowy" />

[4] Przebieg czasowy dla zasady 3 i losowo wygenerowanego stanu początkowego.
</p>


</p>

| **Okres** | **Rozkład Normalny** | **Werdykt** |
| :-------: | :------------------: | :---------: |
|  **oo**   |       **nie**        | **Grupa 4** |

<p style="page-break-after: always;"> </p> 

### Zasada 107

<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_107_graph.png" alt="zasada107_rozkład" />

[5] Rozkład wylosowanych wartości.
</p>

<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_107_size_72.png" alt="zasada107_przebieg_czasowy" />

[6] Przebieg czasowy dla zasady 107 i losowo wygenerowanego stanu początkowego.
</p>




| **Okres** | **Rozkład Normalny** | **Werdykt** |
| :-------: | :------------------: | :---------: |
|  **oo**   |       **nie**        | **Grupa 4** |


<p style="page-break-after: always;"> </p> 

### Zasada 120


<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_120_graph.png" alt="zasada120_rozkład" />

[7] Rozkład wylosowanych wartości.
</p>

<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_120_size_72.png" alt="zasada120_przebieg_czasowy" />

[8] Przebieg czasowy dla zasady 120 i losowo wygenerowanego stanu początkowego.
</p>


| **Okres** | **Rozkład Normalny** | **Werdykt** |
| :-------: | :------------------: | :---------: |
|  **oo**   |       **tak**        | **Grupa 3** |

<p style="page-break-after: always;"> </p> 

### Zasada 55

<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_55_graph.png" alt="zasada55_rozkład" />

[9] Rozkład wylosowanych wartości.
</p>

<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_55_size_72.png" alt="zasada55_przebieg_czasowy" />

[10] Przebieg czasowy dla zasady 55 i losowo wygenerowanego stanu początkowego.
</p>


| **Okres** | **Rozkład Normalny** | **Werdykt** |
| :-------: | :------------------: | :---------: |
|   **1**   |       **nie**        | **Grupa 2** |

<p style="page-break-after: always;"> </p> 

### Zasada 68

<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_68_graph.png" alt="zasada68_rozkład" />

[11] Rozkład wylosowanych wartości.
</p>

<p style="text-align:center" style = "font-size: x-small;">
<img  src="rule_68_size_72.png" alt="zasada68_przebieg_czasowy" />

[12] Przebieg czasowy dla zasady 68 i losowo wygenerowanego stanu początkowego.
</p>


| **Okres** | **Rozkład Normalny** | **Werdykt** |
| :-------: | :------------------: | :---------: |
|   **2**   |       **nie**        | **Grupa 1** |



## Podsumowanie

Podstawowa analiza cykliczności zasady automaty wraz z analizą rozkładu wartości generowanych przez generator Wand może być stosowana do kategoryzacji zasad jednowymiarowej automaty wolframa.
By tą korelację potwierdzić z większą pewnością należy przeprowadzić kategoryzację reszty reguł. Wyniki należy też porównać i innymi istniejącymi metodami kategoryzacji.  

<p style="page-break-after: always;"> </p> 

## Bibliografia

1. [Wolfram MathWorld](https://mathworld.wolfram.com/ElementaryCellularAutomaton.html)
2. [A New Kind of Science](https://en.wikipedia.org/wiki/A_New_Kind_of_Science)  
3. [Cellular automaton](https://en.wikipedia.org/wiki/Cellular_automaton)