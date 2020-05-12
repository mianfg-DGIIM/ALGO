# Capítulo 1. La Eficiencia de los Algoritmos

## Tema 1. Planteamiento general

### Ciencia de la computación

#### ¿Qué es la Ciencia de la Computación?

* La **Ciencia de la Computación** es el estudio de los computadores, _en el sentido de que:_
  * un telescopio tiene relación con la Astronomía.
  * La Ciencia no trata de las herramientas, sino sobre cómo se usan y lo que descubrimos al usarlas.
* La Ciencia de la Computación es el estudio de cómo hacer programas de ordenador.
  * Programación como herramienta para implementar ideas y soluciones: programa como medio, no como objetivo.
* La Ciencia de la Computación estudia los usos y las aplicaciones de computadores y software.
  * El estudio de cómo usar un computador/software es una parte de ella, no el todo.

#### Definición

> Estudio de los **algoritmos**, incluyendo sus propiedades, su hardware, sus aspectos lingüísticos (sintácticos y semánticos) y sus aplicaciones.

### Concepto de algoritmo

#### ¿Qué es un algoritmo?

* **Definición formal:**

  > Secuencia finita y ordenada de pasos, exentos de ambigüedad, tal que al llevarse a cabo con fidelidad _(el algoritmo va haciendo los pasos para los que ha sido diseñado)_, dará como resultado que se realice la tarea para la que se ha diseñado (se obtenga la solución del problema planteado) con recursos limitados y en tiempo finito _(esto nos lleva a que la secuencia sea finita)_.

  Definición imprecisa:

  * ¿Cuándo un algoritmo está completamente exento de ambigüedad?
    * 
  * ¿Cómo se define fidelidad?
    * 
  * ¿Un gran número de años es un tiempo finito?
    * _Entendemos por "finito" algo razonable._

* **Definición de Bazaraa, Sheraly y Shetty (2006):**

  > Un método de solución para resolver un problema (algoritmo) es un proceso iterativo que genera una sucesión de puntos, conforme a un conjunto dado de instrucciones, y un criterio de parada.

* **Definición de Knuth (1997):**

  > Un método computacional o método de cálculo es una cuaterna
  > $$
  > (Q, I, \Omega, f)
  > $$
  > en la cual:
  >
  > * I es el conjunto de **estados de entrada**;
  > * omega es el conjunto de **estados de salida**;
  > * Q es el conjunto de **estados de cálculo**, que contiene a I y a omega; y
  > * f es una función:
  >
  > $$
  > f:Q\rightarrow Q,\hspace{1cm}\text{con}\hspace{1cm}f(q)=q\hspace{0.5cm}\forall q\in Q
  > $$
  >
  > Una secuencia de cálculo es una serie de estados:
  > $$
  > x_0, x_1, x_2, ..., x_n, ...
  > $$
  > donde
  > $$
  > x_0 \in I\hspace{1cm}\text{y}\hspace{1cm}f(x_k) = x_{k+1}\hspace{0.5cm}\forall k \geq 0
  > $$
  > Se dice que la secuencia de cálculo acaba en _n_ pasos si _n_ es el menor entero con
  > $$
  > x_n\in \Omega
  > $$
  >

* **Informalmente:**

  > Método por etapas para realizar alguna tarea.

* > Un **programa** es una serie de instrucciones ordenadas, codificadas en un lenguaje de prgramación que expresa un algoritmo y que puede ser ejecutado en un computador.

#### Características principales

Un algoritmo tiene cinco características principales:

* **Finitud:** ha de terminar después de un tiempo acotado superiormente.
* **Especificidad:** cada etapa debe estar precisamente definida; las acciones que hay que llevar a cabo deben estar rigurosamente especificadas para cada caso.
* **Input:** cero o más.
* **Output:** uno o más.
* **Efectividad:** las operaciones que se realicen deben ser operaciones básicas y fáciles de implementar.

#### //NO TODAVÍA Ciencia de la Computación

Aborda

* Propiedades formales y matemáticas
  * Cómo diseñar algoritmos para resolver una gran variedad de problemas.
  * Cómo determinar si los problemas son (eficientemente) computables, es decir, si se pueden especificar por un algoritmo.
* Hardware

### Elección de un algoritmo

### Problemas y casos

### Distintos tipos de casos



## Tema 2. Tiempo de ejecución. Notaciones para la eficiencia de los algoritmos

### La eficiencia de los algoritmos

* ¿Por qué estudiar la eficiencia de los algoritmos?
  * Existe un método para resolver un problema: ¿es viable?
  * Existen varios: ¿cuál de ellos es mejor?, ¿en qué situaciones?
* ¿Cómo medimos la eficiencia de un algoritmo?
  * En **tiempo**: tiempo que tarda un algoritmo en resolver un problema.
  * En **espacio**: recursos (memoria, espacio en disco, etc.) necesarios para resolver el problema.
* Aclaraciones sobre notación:
  * **Problema:** el problema general que queremos resolver.
  * **Instancia del problema:** problema concreto a resolver.
  * **Caso:** instancia o conjunto de instancias de un problema con dificultad idéntica o muy similar. Tres tipos: caso peor, caso mejor, caso promedio.
  * **Tamaño del caso:** tamaño de la instancia o instancias del problema a resolver.
* ¿En qué unidad habrá que expresar la eficiencia de un algoritmo?
  * El orden del algoritmo no depende del caso particular. 
* Independientemente de la medida que nos la evalúe, hay tres métodos:
  * **Enfoque empírico, _a posteriori_:** depende del agente tecnológico usado. Se implementa el algoritmo y se mide el tiempo de ejecución.
  * **Enfoque teórico, _a priori_**: no depende del agente tecnológico, sino de cálculos matemáticos. Se calcula una función matemática que indique cómo evolucionará el tiempo de ejecución del algoritmo según varíe el tamaño _n_ del caso.
  * **Enfoque híbrido:** mezcla de ambos.
* La selección de la unidad para calcular la eficiencia la encontraremos a partir del **principio de invariancia**: dos implementaciones de un mismo algoritmo no difieren en eficiencia más que, a lo sumo, una constante multiplicativa.
  * Si dos implementaciones consumen _t1(n)_ y _t2(n)_ unidades de tiempo, respectivamente, en resolver un caso de tamaño _n_, entonces siempre existe una constante positiva _c_ tal que _t1(n) <= ct2(n)_, siempre que _n_ sea suficientemente grande.
  * Este principio es independiente del agente tecnológico usado.
  * Si queremos que la cota sea mucho más elevada, debemos de cambiar de algoritmo.
* El **tiempo de ejecución** de un programa depende de:
  * La entrada.
  * La calidad del código que genera el compilador.
  * La naturaleza y velocidad de las instrucciones máquina.
  * La **complejidad en tiempo** o **eficiencia** (calculada a nivel teórico) del programa.
  * Notas:
    * No depende directamente del input, sino de su tamaño.
    * Notaremos _T(n)_ como el tiempo de ejecución de un programa de tamaño _n_.
    * No habrá unidad para expresarlo. Usamos una constante para acumular en ella todos los factores relativos a los aspectos tecnológicos.
      * Diremos que un algoritmo consume un tiempo _t(n)_ si existe una constante positiva _c_ y una implementación del algoritmo capaz de resolver cualquier caso del problema en un tiempo acotado superiormente por _ct(n)_ segundos.
      * El uso de segundos es arbitrario, sólo necesitamos cambiar la constante para cambiar dicha magnitud.
    * Hay que tener cuidado con cómo defino el tiempo. _Ej: n² días y n³ segundos, aparentemente mejor n² días, pero será mejor en casos que requieran más de 20M de años._

### Métodos para evaluar la eficiencia. Notaciones _O_, _Ω_ y _Θ_

* Estas notaciones se usan para comparar algoritmos empleando los tiempos de ejecución, y las constantes ocultas. Se emplea la denominada **notación asintótica**.

#### Notación formal para _O_

Intuitivamente, _f(n)_ está asintóticamente dominada por _g(n)_ si cuando multiplicamos _g(n)_ por alguna constante lo que se obtiene es realmente mayor que _f(n)_ para valores grandes de _n_.

**Formalmente:**

Sean _f_, _g_, funciones definidas como:
$$
f,g:\mathbb{N}\rightarrow \mathbb{R}^+_0
$$
Se dice que _f_ es de orden _g_, que se nota _O(g(n))_, si existen dos constantes positivas _C_ y _k_ tales que:
$$
\forall n \geq k, f(n) \leq C \cdot g(n)
$$
es decir, pasado _k_, _f_ es menor o igual que un múltiplo de _g_.

La notación _O_ nos permite conocer cómo se comportará el algoritmo en términos de eficiencia en instancias del **caso peor** del problema: _"como mucho, sabemos que el algoritmo no tarda más de Cg(n) en ejecutarse, en el peor de los casos"_.

##### Confusiones

* Tomo como función el mínimo de todas las que hay encima:

  * Es cierto que:
    $$
    3x^3+5x^2-9=O(x^3)\\
    3x^3+5x^2-9=O(x^4)\\
    x^3=O(3x^3+5x^2-9)\\
    sen(x)=O(x^4)
    $$


---

Los límites puede ayudar a demostrar relacines en notación O

[SEGUIR -- copiar lema]
$$
O(f(n)) = O(g(n)) \iff \lim_{n\rightarrow\infty}\frac{f(n)}{g(n)}=C
$$

$$
O(f(n)) > O(g(n)) \iff \lim_{n\rightarrow\infty}\frac{f(n)}{g(n)}=\infty
$$

$$
O(f(n)) < O(g(n)) \iff \lim_{n\rightarrow\infty}\frac{f(n)}{g(n)}=0
$$

#### Notación formal para _Ω_

Es exactamente lo contrario para _O_.
$$
f(n) = \Omega(g)n))\iff g(n)=O(f(n))
$$
**Definición:** sean _f_ y _g_ funciones:
$$
f,g:\mathbb{N}\rightarrow\mathbb{R}^+_0
$$
Se dice que _f_ es _Ω(g(n))_ si existen dos constantes positivas _C_ y _k_ tales que:
$$
\forall n \geq k, f(n) \leq C \cdot g(n)
$$

#### Notación formal para _Θ_

Es el orden equivalente.
$$
f(n) = \Theta(g)n))\iff f(n)=O(g(n)) \and g(n)=O(f(n))
$$

#### La dictadura de la Tasa de Crecimiento




### La notación asintótica de Brassard y Bratley

### Análisis teórico del tiempo de ejecución de un algoritmo

### Análisis práctico del tiempo de ejecución de un algoritmo

### Análisis de programas con llamadas a procedimientos

### Análisis de procedimientos recursivos

### Algunos ejemplos prácticos



