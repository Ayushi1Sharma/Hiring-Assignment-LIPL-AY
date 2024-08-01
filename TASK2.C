#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include <stdio.h>


QueueHandle_t xQueue;


void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

int main(void)
{
    xQueue = xQueueCreate(10, sizeof(int32_t));

    if (xQueue != NULL)
    {

        xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);
        xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);

        vTaskStartScheduler();
    }


    for (;;);
}

void vTask1(void *pvParameters)
{
    int32_t lValueToSend = 0;
    for (;;)
    {
        lValueToSend++;
        printf("Task 1 sending value: %ld\n", lValueToSend);
        xQueueSend(xQueue, &lValueToSend, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
    }
}

void vTask2(void *pvParameters)
{
    int32_t lReceivedValue;
    for (;;)
    {
        if (xQueueReceive(xQueue, &lReceivedValue, portMAX_DELAY))
        {
            printf("Task 2 received value: %ld\n", lReceivedValue);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
