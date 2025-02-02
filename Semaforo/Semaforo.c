#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LEDG 11  // Definição do LED Verde
#define LEDB 12  // Definição do LED azul/amarelo
#define LEDR 13  // Definição do LED vermelho

int led_index = 1;  // Variável para alternar entre os LEDs

// Callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) 
{
    // Apaga todos os LEDs antes de acender o próximo


    // Alterna entre os LEDs a cada ciclo
    if (led_index == 0) 
    {
        gpio_put(LEDR, 1);
        gpio_put(LEDB, 0);
        gpio_put(LEDG, 0);
        printf("LED %d aceso\n", led_index + 1);
        led_index++;
    } else if (led_index == 1) 
    {
        gpio_put(LEDB, 1);
        gpio_put(LEDR, 0);
        gpio_put(LEDG, 0);
        printf("LED %d aceso\n", led_index + 1);
        led_index++;
    }else if (led_index == 2) 
    {
        gpio_put(LEDG, 1);
        gpio_put(LEDB, 0);
        gpio_put(LEDR, 0);
        printf("LED %d aceso\n", led_index + 1);
        led_index = 0;
    }


    return true; // Mantém o temporizador ativo
}

int main() 
{
    stdio_init_all();

    // Inicializa os pinos dos LEDs como saída
    gpio_init(LEDG);
    gpio_set_dir(LEDG, GPIO_OUT);

    gpio_init(LEDB);
    gpio_set_dir(LEDB, GPIO_OUT);

    gpio_init(LEDR);
    gpio_set_dir(LEDR, GPIO_OUT);
    gpio_put(LEDR, 1);

    struct repeating_timer timer;

    // Configura o temporizador para chamar o callback a cada 3 segundos
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        sleep_ms(1000);
        printf("1 segundo passou\n");
    }

    return 0;
}
