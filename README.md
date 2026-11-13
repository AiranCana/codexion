*Este proyecto ha sido creado como parte del currículo de 42 por acanadil.*
 
# Codexion
 
## Descripción
 
**Codexion** es una simulación de concurrencia inspirada en el problema clásico de los
filósofos comensales. En lugar de filósofos y tenedores, un grupo de **personas que
programan** ("coders") se sienta alrededor de una mesa circular y compite por un número
limitado de **dongles USB** para poder compilar su código.
 
Cada coder repite un ciclo de tres fases: **compilar**, **depurar** y **refactorizar**.
Compilar requiere tener a la vez los dos dongles adyacentes (izquierdo y derecho);
depurar y refactorizar no necesitan ninguno. Tras liberar un dongle, este entra en un
periodo de **enfriamiento** (`dongle_cooldown`) durante el cual nadie puede cogerlo.
Si un coder no consigue empezar a compilar antes de `time_to_burnout` milisegundos
desde el inicio de su última compilación (o desde el arranque), se **agota**
(*burned out*) y la simulación se detiene. La simulación también termina cuando todos
los coders han completado `number_of_compiles_required` compilaciones.
 
El proyecto está escrito en C con hilos POSIX (`pthread`), mutexes y variables de
condición, y garantiza:
 
- Exclusión mutua correcta sobre los dongles.
- Respeto del enfriamiento de cada dongle.
- Arbitraje entre coders vecinos según la política elegida (`fifo` o `edf`).
- Un log de eventos serializado y ordenado por marca de tiempo.
- Una parada ordenada de todos los hilos y la liberación de toda la memoria.
## Instrucciones
 
### Compilación
 
```bash
make        # compila el binario `codexion`
make clean  # elimina los archivos objeto
make fclean # elimina los archivos objeto y el binario
make re     # fclean + all
```
 
Se compila con `cc` y las flags `-Wall -Wextra -Werror -pthread`, sin relink.
 
### Ejecución
 
```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```
 
También se admite pasar todos los argumentos como una única cadena entre comillas,
separados por espacios:
 
```bash
./codexion "number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler"
```
 
| Argumento | Descripción |
|---|---|
| `number_of_coders` | Número de coders (y de dongles). |
| `time_to_burnout` | ms sin empezar a compilar antes de agotarse. |
| `time_to_compile` | ms que dura una compilación. |
| `time_to_debug` | ms que dura la depuración. |
| `time_to_refactor` | ms que dura la refactorización. |
| `number_of_compiles_required` | Compilaciones que debe completar cada coder para terminar. |
| `dongle_cooldown` | ms de enfriamiento tras liberar un dongle. |
| `scheduler` | `fifo` o `edf`. |
 
Los ocho argumentos son obligatorios. Los siete primeros deben ser enteros positivos
(se rechazan negativos, no numéricos y valores fuera de rango) y el último debe ser
`fifo` o `edf`.
 
Ejemplo:
 
```bash
./codexion 5 800 300 300 100 6 200 fifo
```
 
### Formato de salida
 
Cada línea tiene la forma `<ms> <id_coder> <mensaje>`, donde `<ms>` son los
milisegundos desde el inicio del coder. Los mensajes posibles son:
 
```
has taken a dongle
is compiling
is debugging
is refactoring
has burned out
```
 
### Estructura del código
 
| Fichero | Contenido |
|---|---|
| `main.c` | Punto de entrada, gestión de argumentos y errores, orquestación. |
| `parser.c` | Validación de argumentos y creación de los coders. |
| `gen_structurs.c` | Creación y destrucción de coders y de los datos de configuración. |
| `gen_table.c` | Creación y destrucción de la mesa (mutex, condición, cola de log). |
| `gen_usb.c` | Creación y destrucción de los dongles. |
| `utilsUsb.c` | Asignación de dongles, toma/liberación, disponibilidad y prioridad. |
| `priority.c` | Políticas `fifo`/`edf`, comprobación de vecinos y arranque de hilos. |
| `operate_pthread.c` | Rutina de cada coder y rutina del hilo monitor. |
| `utils_printer.c` | Cola de mensajes del log y su impresión ordenada. |
| `timer.c` | Tiempo, sleeps interrumpibles y espera con `pthread_cond_timedwait`. |
| `utils_rutin.c` | Utilidades de estado (fin de todos los coders, impresión protegida). |
 
## Recursos
 
- [The Little Book of Semaphores – Allen B. Downey](https://greenteapress.com/wp/semaphores/) — referencia clásica sobre sincronización y el problema de los filósofos comensales.
- [POSIX Threads Programming (LLNL)](https://hpc-tutorials.llnl.gov/posix/) — guía sobre `pthread_create`, `pthread_mutex_t` y `pthread_cond_t`.
- [man 3 pthread_cond_timedwait](https://man7.org/linux/man-pages/man3/pthread_cond_timedwait.3p.html) — documentación de la espera con límite de tiempo.
- Liu, C. L.; Layland, J. (1973). *Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment* — trabajo original que formaliza EDF (*Earliest Deadline First*).
### Uso de IA
 
Se ha utilizado un asistente de IA (Claude, de Anthropic) como herramienta de revisión
y segunda opinión, no como generador de la solución final. Usos concretos:
 
- **Lógica de espera y detección de agotamiento** (`ft_sleep`, `verif_usb_and_bornout`):
  discusión de varias versiones hasta sustituir la espera activa por
  `pthread_cond_timedwait`, con el `timespec` construido a partir de `gettimeofday`
  (`clock_gettime` no está entre las funciones permitidas).
- **Análisis de la salida de Helgrind**: interpretación de los avisos de
  `pthread_cond_timedwait` y revisión de accesos compartidos sin proteger.
Todo el código sugerido fue revisado, probado con distintos parámetros (incluidos casos
límite) y comprendido antes de incorporarse.
 
## Casos de bloqueo tratados
 
- **Interbloqueo (deadlock)**: un coder nunca coge un dongle y espera por el otro. Bajo
  `table->mutex` comprueba que **ambos** dongles están disponibles (libres y fuera de
  enfriamiento) y que tiene prioridad, y solo entonces los toma a la vez en `takeusb`.
  Así no se da la condición de *hold and wait* ni la espera circular. Con un solo coder
  ambos dongles son el mismo, por lo que nunca puede compilar y acaba agotándose.
- **Inanición (starvation)**: `priority` compara al coder solo con sus dos vecinos en la
  mesa (los únicos con los que comparte dongle) y solo cuando están en estado `IDLE`
  esperando. Con `fifo` tiene prioridad el que lleva más tiempo sin compilar
  (menor `last_compile_start`); con `edf` el que tiene el plazo de agotamiento más
  cercano (`last_compile_start + time_to_burnout`).
- **Enfriamiento**: cada dongle guarda su `cooldown_start`, que se actualiza en
  `dropusb` bajo el mutex de la mesa. `available_usbs` exige que el dongle esté libre y
  que haya pasado `dongle_cooldown` desde su liberación.
- **Detección del agotamiento**: mientras un coder espera sus dongles comprueba en cada
  vuelta su plazo (`inicio de la última compilación + time_to_burnout`). Si vence, marca
  su estado como `BURNED_OUT`, avisa con `pthread_cond_broadcast` y registra el mensaje.
  El hilo monitor lo imprime y activa la bandera global `failed`.
- **Parada ordenada**: al activarse `failed`, los coders que esperan dongles salen del
  bucle de espera (como mucho tras 1 ms, por el timeout de la espera), los que duermen
  en `ft_sleep` lo detectan en su siguiente comprobación (cada 0,5 ms) y `ruotine`
  retorna. Después `start_routin` hace `pthread_join` de todos los hilos y se libera la
  memoria.
- **Serialización del log**: los coders no escriben en la salida. Cada evento se añade
  a una cola bajo `table->mutex` y solo el hilo monitor imprime. En cada iteración
  extrae el mensaje con menor marca de tiempo y, si hay empate, el más antiguo de ese
  grupo, de modo que la salida sale ordenada aunque los hilos encolen en otro orden.
  La impresión se detiene tras `has burned out` o cuando todos los coders han
  terminado.
## Mecanismos de sincronización
 
El proyecto no usa variables globales y se apoya en tres primitivas de `pthread`:
 
- **`pthread_mutex_t table->mutex`**: protege el estado compartido de la mesa (estado de
  los coders, dongles, bandera `failed` y cola de mensajes) y es el mutex asociado a la
  variable de condición. Se toma en `verif_usb_and_bornout`, `dropusb`, `asign_state`,
  `printer_coder` y en el bucle del monitor, y se libera en todos los caminos de salida.
- **`pthread_mutex_t usb->mutex`**: uno por dongle, tomado en `takeusb` al marcar cada
  dongle como ocupado.
- **`pthread_cond_t table->cond`**: permite que un coder sin dongles espere sin consumir
  CPU y liberando el mutex. Se usa `pthread_cond_timedwait` con un timeout de ~1 ms,
  construido con `gettimeofday`. Se despierta antes si otro hilo hace `broadcast`
  (al liberar dongles en `dropusb` o al declararse un agotamiento), y el timeout sirve
  de red de seguridad para reevaluar la condición, ya que el enfriamiento de un dongle
  expira con el tiempo y no genera ninguna señal.
### Ejemplo de cómo se evitan las condiciones de carrera
 
Un coder mantiene el mutex de la mesa durante toda la comprobación de disponibilidad y
prioridad y la posterior toma de dongles, de forma atómica:
 
```c
pthread_mutex_lock(&coder->table->mutex);
while ((!available_usbs(coder) || !priority(coder, coder->table))
    && !coder->table->failed)
{
    if (verif_time(deadline))
    { /* marcar BURNED_OUT, broadcast, unlock y salir */ }
    wait_time(coder); /* pthread_cond_timedwait: libera el mutex mientras espera */
}
if (!coder->table->failed)
    takeusb(&coder); /* toma ambos dongles sin interferencias */
pthread_mutex_unlock(&coder->table->mutex);
```
 
Ningún otro hilo puede cambiar la disponibilidad de un dongle entre la comprobación y
el momento en que se marca como ocupado.
 
### Comunicación entre coders y monitor
 
Los coders no se comunican directamente. La única señal global es `table->failed`, que
escribe el hilo monitor al imprimir un agotamiento (o `start_routin` si falla la
creación de un hilo) y que cada coder lee para saber si debe detenerse. El monitor
también finaliza cuando todos los coders han alcanzado el estado `FINISH`.