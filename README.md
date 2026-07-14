*Este proyecto ha sido creado como parte del currículo de 42 por acanadil.*
 
# Codexion
 
## Descripción
 
**Codexion** es una simulación de concurrencia inspirada en el problema clásico de los
filósofos comensales. En lugar de filósofos y tenedores, un grupo de **personas que
programan** ("coders") se sienta alrededor de una mesa circular y compite por un número
limitado de **dongles USB** para poder compilar su código.
 
Cada coder alterna entre tres fases: **compilar**, **depurar** y **refactorizar**.
Compilar requiere adquirir simultáneamente los dos dongles adyacentes (izquierdo y
derecho); depurar y refactorizar no requieren ningún dongle. Tras liberar un dongle,
este entra en un periodo de **enfriamiento** (`dongle_cooldown`) durante el cual nadie
puede volver a tomarlo. Si un coder no logra empezar a compilar dentro de
`time_to_burnout` milisegundos desde el inicio de su última compilación (o desde el
arranque de la simulación), se **agota** y la simulación se detiene.
 
El objetivo del proyecto es implementar esta simulación en C usando hilos POSIX
(`pthread`) y mutexes, garantizando:
 
- Que nunca se dupliquen ni se corrompan los dongles (exclusión mutua correcta).
- Que se respete el enfriamiento obligatorio de cada dongle.
- Que el arbitraje entre coders que compiten por el mismo dongle sea justo, según la
  política de scheduling elegida (`fifo` o `edf`).
- Que, si los parámetros son viables, **nadie se agote nunca**.
- Que la detección de agotamiento sea precisa (dentro de un margen de 10 ms) y que el
  log de eventos esté correctamente serializado.
## Instrucciones
 
### Compilación
 
```bash
make        # compila el binario `codexion`
make clean  # elimina los archivos objeto
make fclean # elimina los archivos objeto y el binario
make re     # fclean + all
```
 
El proyecto compila con `cc` y las flags `-Wall -Wextra -Werror -pthread`, sin relink.
 
### Ejecución
 
```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```
 
También se admite pasar todos los argumentos como una única cadena entre comillas:
 
```bash
./codexion "number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler"
```
 
| Argumento | Descripción |
|---|---|
| `number_of_coders` | Número de personas que programan (y de dongles). |
| `time_to_burnout` | ms sin empezar a compilar antes de agotarse. |
| `time_to_compile` | ms que dura una compilación. |
| `time_to_debug` | ms que dura la fase de depuración. |
| `time_to_refactor` | ms que dura la fase de refactorización. |
| `number_of_compiles_required` | Compilaciones que debe completar cada coder para terminar. |
| `dongle_cooldown` | ms de enfriamiento tras liberar un dongle. |
| `scheduler` | `fifo` o `edf`. |
 
Todos los argumentos son obligatorios y deben ser enteros positivos válidos (se
rechazan números negativos, no enteros, valores fuera de rango, o un scheduler distinto
de `fifo`/`edf`).
 
Ejemplo:
 
```bash
./codexion 5 800 300 300 100 6 200 fifo
```
 
## Recursos
 
- [The Little Book of Semaphores – Allen B. Downey](https://greenteapress.com/wp/semaphores/) — referencia clásica sobre sincronización con mutexes, variables de condición y el problema de los filósofos comensales, en el que se inspira este proyecto.
- [POSIX Threads Programming (LLNL)](https://hpc-tutorials.llnl.gov/posix/) — guía de referencia sobre `pthread_create`, `pthread_mutex_t` y `pthread_cond_t`.
- [man 3 pthread_cond_timedwait](https://man7.org/linux/man-pages/man3/pthread_cond_timedwait.3p.html) — documentación de la función usada para las esperas con timeout sin busy-waiting.
- Liu, C. L.; Layland, J. (1973). *Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment* — trabajo original que formaliza el algoritmo EDF (Earliest Deadline First) usado como scheduler alternativo en este proyecto.
### Uso de IA
 
Se ha utilizado un asistente de IA (Claude, de Anthropic) durante el desarrollo de este
proyecto, principalmente como herramienta de depuración guiada y de segunda opinión,
no como generador de código de la solución final. Usos concretos:
 
- **Revisión de la lógica de `ft_sleep` y `verif_usb_and_bornout`**: se discutieron
  varias versiones de las condiciones de espera hasta llegar a una que detectara el
  agotamiento de forma correcta en cualquier fase (compilando, depurando,
  refactorizando o esperando dongle), sin depender de un busy-wait activo.
  Se sustituyó por `pthread_cond_timedwait` construyendo el `timespec` a partir de
  `gettimeofday` (ya que `clock_gettime` no está en la lista de funciones permitidas).

Todo el código generado o sugerido fue revisado, probado con distintos conjuntos de
parámetros (incluyendo casos límite construidos a propósito) y comprendido línea a
línea antes de incorporarse, siguiendo las buenas prácticas indicadas en el enunciado.
 
## Blocking cases handled
 
- **Prevención de interbloqueos (deadlock) y condiciones de Coffman**: cada coder
  siempre adquiere sus dos dongles en el mismo orden relativo (derecho primero,
  izquierdo después, dentro de `takeusb`), evitando la espera circular clásica del
  problema de los filósofos comensales. Además, la adquisición de ambos dongles se
  protege bajo el mutex global de la mesa (`table->mutex`) mientras se comprueba
  disponibilidad y prioridad, de modo que ningún otro coder puede "colarse" a mitad de
  la comprobación y dejar el sistema en un estado inconsistente.
- **Prevención de inanición (starvation)**: el scheduler (`fifo` o `edf`) decide, entre
  los coders que compiten por un dongle compartido, quién tiene prioridad, evitando que
  un coder quede indefinidamente relegado frente a otros. La comprobación de prioridad
  solo se aplica frente a coders con los que realmente se comparte al menos un dongle
  físico (vecinos en la mesa circular), no frente a la tabla completa, para no bloquear
  a coders que no tienen ningún conflicto de recursos real entre sí.
- **Gestión del cooldown**: cada `t_USB` almacena su propio `cooldown_start`,
  actualizado en `dropusb` bajo el mutex de la mesa. `available_usbs` comprueba tanto
  que el dongle esté libre (`fre`) como que haya transcurrido `dongle_cooldown` desde
  su liberación, antes de considerarlo disponible para un nuevo coder.
- **Detección precisa del agotamiento**: un hilo monitor independiente (`rutine_table`)
  recorre periódicamente el estado de todos los coders y compara
  `now - last_compile_start` contra `time_to_burnout`, de forma centralizada — evitando
  que la detección dependa de que cada coder individual esté precisamente en el punto
  del código donde comprueba su propio deadline. Esto garantiza que el agotamiento se
  detecte y registre dentro del margen de 10 ms exigido, sin importar en qué fase
  (compilando, depurando, refactorizando o esperando dongle) se encuentre el coder en
  el momento exacto en que expira su plazo.
- **Serialización del log**: todos los mensajes de estado se imprimen a través de
  `print_coder`, y las escrituras de estado compartido que preceden a la impresión
  (toma/liberación de dongles, cambio de `state`) se realizan bajo mutex, evitando que
  dos mensajes se entrelacen en la misma línea de salida.
## Thread synchronization mechanisms
 
El proyecto usa dos primitivas de sincronización de `pthread`, sin variables globales:
 
- **`pthread_mutex_t table->mutex`**: protege el estado compartido de la mesa (el
  array de coders, el flag `failed`, y sirve como mutex asociado a la variable de
  condición). Se adquiere en `verif_usb_and_bornout` antes de comprobar disponibilidad
  de dongles y prioridad, y en `dropusb`/`rutine_table`/`found_dead` antes de modificar
  el estado global de fallo. Cada camino de adquisición garantiza que el mutex se
  libera en **todos** los puntos de salida de la función (incluidos los `return`
  tempranos), para evitar dejar el mutex bloqueado indefinidamente al terminar un hilo.
- **`pthread_mutex_t usb->mutex`**: protege el campo `fre` de cada dongle individual
  durante `takeusb`, evitando que dos coders lean/escriban el mismo flag de
  disponibilidad de forma concurrente.
- **`pthread_cond_t table->cond`**: usada para que un coder que no puede tomar sus
  dongles (`verif_usb_and_bornout`) espere de forma eficiente en vez de hacer
  busy-waiting reteniendo el mutex. Se usa `pthread_cond_timedwait` con un timeout
  corto (~1 ms), construido manualmente a partir de `gettimeofday` (ya que
  `clock_gettime` no está entre las funciones permitidas). Esto permite que el hilo
  ceda el mutex mientras espera, se despierte inmediatamente cuando otro hilo hace
  `pthread_cond_broadcast` (por ejemplo, al liberar un dongle en `dropusb`, o al
  declararse un fallo global), y como fallback re-evalúe su condición cada milisegundo
  aproximadamente por si el evento de despertar se hubiera perdido.
### Ejemplo de cómo se evitan las condiciones de carrera
 
Antes de tomar un dongle, un coder mantiene el mutex de la mesa bloqueado durante toda
la comprobación de `available_usbs()` + `priority()` y la posterior llamada a
`takeusb()`, de forma atómica:
 
```c
pthread_mutex_lock(&coder->table->mutex);
while ((!available_usbs(coder) || !priority(coder, coder->table))
    && !coder->table->failed)
{
    if (verif_time(deadline))
    { /* declarar burned out */ }
    wait_time(coder); /* pthread_cond_timedwait, libera el mutex mientras espera */
}
if (!coder->table->failed)
    takeusb(&coder); /* toma ambos dongles sin que nadie más pueda interferir */
pthread_mutex_unlock(&coder->table->mutex);
```
 
Esto asegura que ningún otro hilo pueda cambiar la disponibilidad de un dongle entre el
momento en que se comprueba y el momento en que se marca como ocupado.
 
### Comunicación thread-safe entre coders y el monitor
 
Los coders **no se comunican entre sí ni consultan el estado de otros coders**
directamente. La única señal compartida es `table->failed`, un entero protegido por
`table->mutex`, escrito exclusivamente por el hilo monitor (`rutine_table` /
`found_dead`) al detectar un agotamiento o la finalización de todos los coders, y leído
por cada coder para decidir si debe detenerse. Esto respeta la restricción del
enunciado de que "las personas no se comunican entre sí" ni "saben si otra está a
punto de agotarse": ningún coder inspecciona el estado interno de otro coder concreto,
solo consulta la bandera global calculada de forma centralizada por el monitor.