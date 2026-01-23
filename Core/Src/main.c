/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include	<stdio.h>
#include 	<npmx.h>
#include 	<npmx_core.h>
#include 	<npmx_instance.h>
#include	"fuel_gauge.h"			//Fuel Gauge functions


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define I2C_BUF_SIZE 	256//I2C buffer size
#define MEM_ADDR_SIZE	I2C_MEMADD_SIZE_8BIT
#define TIMEOUT 		HAL_MAX_DELAY
#define NPM13xx_ADDR 	0x6b
#define BATTERY_VOLTAGE_THRESHOLD_1 3290		//Battery voltage 1 threshold setting Threshold 1 should have a higher value than threshold 2.
#define BATTERY_VOLTAGE_THRESHOLD_2 3240		//Battery Voltage 2 Threshold setting

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
static npmx_instance_t npm1300_instance;
static npmx_backend_t npm1300_backend;
static bool pmic_interrupt;



static npmx_error_t my_i2c_write_function(void * p_context, uint32_t register_address, uint8_t * p_data, size_t num_of_bytes);
static npmx_error_t my_i2c_read_function(void * p_context, uint32_t register_address, uint8_t * p_data, size_t num_of_bytes);


static void my_npmx_initialization_function(void)
{
	//Associate the I2C Read and Write to backend data structure used in npmx drivers
    npm1300_backend.p_read = my_i2c_read_function;
    npm1300_backend.p_write = my_i2c_write_function;
    npm1300_backend.p_context = NULL; // Optional context for our use

    npmx_error_t npmx_err = npmx_core_init(&npm1300_instance, &npm1300_backend, NULL, true);
    // TODO: Verify that npmx_err == NPMX_SUCCESS
}

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* Definitions for myTask01 */
osThreadId_t myTask01Handle;
const osThreadAttr_t myTask01_attributes = {
  .name = "myTask01",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* USER CODE BEGIN PV */
/** @brief Possible events from requested PMIC device. */
enum npm1300_charger_event_t {
	/* Event registered when battery connection detected. */
	APP_CHARGER_EVENT_BATTERY_DETECTED,
	/* Event registered when battery connection removed. */
	APP_CHARGER_EVENT_BATTERY_REMOVED,
	/* Event registered when VBUS connection detected. */
	APP_CHARGER_EVENT_VBUS_DETECTED,
	/* Event registered when VBUS connection removed. */
	APP_CHARGER_EVENT_VBUS_REMOVED,
	/* Event registered when trickle charging started. */
	APP_CHARGER_EVENT_CHARGING_TRICKE_STARTED,
	/* Event registered when constant current charging started. */
	APP_CHARGER_EVENT_CHARGING_CC_STARTED,
	/* Event registered when constant voltage charging started. */
	APP_CHARGER_EVENT_CHARGING_CV_STARTED,
	/* Event registered when charging completed. */
	APP_CHARGER_EVENT_CHARGING_COMPLETED,
	/* Event registered when first low battery voltage alert detected. */
	APP_CHARGER_EVENT_BATTERY_LOW_ALERT1,
	/* Event registered when second low battery voltage alert detected. */
	APP_CHARGER_EVENT_BATTERY_LOW_ALERT2,
};

/** @brief Possible nPM device working states. */
enum npm1300_state_t {
	/* State when VBUSIN disconnected and battery disconnected. */
	APP_STATE_BATTERY_DISCONNECTED,
	/* State when VBUSIN disconnected and battery connected. */
	APP_STATE_BATTERY_CONNECTED,
	/* State when VBUSIN connected and battery disconnected. */
	APP_STATE_VBUS_CONNECTED_BATTERY_DISCONNECTED,
	/* State when VBUSIN connected and battery connected. */
	APP_STATE_VBUS_CONNECTED_BATTERY_CONNECTED,
	/* State when VBUSIN connected, battery connected and charger in trickle mode. */
	APP_STATE_VBUS_CONNECTED_CHARGING_TRICKE,
	/* State when VBUSIN connected, battery connected and charger in constant current mode. */
	APP_STATE_VBUS_CONNECTED_CHARGING_CC,
	/* State when VBUSIN connected, battery connected and charger in constant voltage mode. */
	APP_STATE_VBUS_CONNECTED_CHARGING_CV,
	/* State when VBUSIN connected, battery connected and charger completed charging. */
	APP_STATE_VBUS_CONNECTED_CHARGING_COMPLETED,
	/* State when VBUSIN disconnected, battery connected. */
	APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING,
	/* State when VBUSIN disconnected. */
	/* Battery connected and battery voltage is below first alert threshold. */
	APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING_ALERT1,
	/* State when VBUSIN disconnected. */
	/* Battery connected and battery voltage is below second alert threshold. */
	APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING_ALERT2,
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
void StartTask01(void *argument);
void StartTask02(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void clear_events(void);		//Clear all Interrupts in the nPM1300
void my_pmic_config(void);		//Change the default config
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  pmic_interrupt = true;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  my_npmx_initialization_function();		// initialize the nPM1300 core to default values.

  clear_events();							//Clear all Event Registers
  my_pmic_config();							//Change configuration of PMIC

  if (fuel_gauge_init(&npm1300_instance) < 0) {   //initialize the Fuel Gauge
 		printf("Fuel gauge initialization failed.\n");
  		return 0;
  	}

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */

  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of myTask01 */
  myTask01Handle = osThreadNew(StartTask01, NULL, &myTask01_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
npmx_error_t my_i2c_write_function(void * p_context, uint32_t register_address, uint8_t * p_data, size_t num_of_bytes)
{
	   uint8_t tx_buffer[ I2C_BUF_SIZE ] = { 0 };
	   npmx_error_t ret;
	   HAL_StatusTypeDef stm_ret;

	    tx_buffer[ 0 ] = ( uint8_t ) ( ( register_address >> 8 ) & 0xFF );
	    tx_buffer[ 1 ] = ( uint8_t ) ( register_address & 0xFF );

	    for ( uint8_t cnt = 0; cnt < num_of_bytes; cnt++ )
	    {
	        tx_buffer[ cnt + 2 ] = p_data[ cnt ];
	    }
	    stm_ret = HAL_I2C_Master_Transmit(&hi2c1, NPM13xx_ADDR << 1,tx_buffer,num_of_bytes+2, TIMEOUT );

		if (stm_ret != HAL_OK)
				ret=NPMX_ERROR_INVALID_PARAM;
		else
				ret=NPMX_SUCCESS;

	    return ret;

}
npmx_error_t my_i2c_read_function(void * p_context, uint32_t register_address, uint8_t * p_data, size_t num_of_bytes)
{
    uint8_t rx_buffer[ 2 ] = { 0 };
    npmx_error_t ret;
    HAL_StatusTypeDef stm_ret;

    rx_buffer[ 0 ] = ( uint8_t ) ( ( register_address >> 8 ) & 0xFF );
    rx_buffer[ 1 ] = ( uint8_t ) ( register_address & 0xFF );

    stm_ret = HAL_I2C_Master_Transmit(&hi2c1, NPM13xx_ADDR << 1,rx_buffer,2, TIMEOUT);
	if (stm_ret != HAL_OK)
			ret=NPMX_ERROR_INVALID_PARAM;
	else
			ret=NPMX_SUCCESS;

    stm_ret = HAL_I2C_Master_Receive(&hi2c1,NPM13xx_ADDR<< 1, p_data, num_of_bytes, TIMEOUT);
	if (stm_ret != HAL_OK)
			ret=NPMX_ERROR_INVALID_PARAM;
	else
			ret=NPMX_SUCCESS;


    return ret;
}

void clear_events(void)
{
	npmx_error_t npmx_err;
	printf("clearing Interrupts \n");

	// Clear all events before enabling interrupts, just in case other interrupt source was configured before.
	for (uint32_t i = 0; i < NPMX_EVENT_GROUP_COUNT; i++) {
	        npmx_err = npmx_core_event_interrupt_disable(&npm1300_instance, (npmx_event_group_t)i, NPMX_EVENT_GROUP_ALL_EVENTS_MASK);
	    }
}

/**
 * @brief Function for registering the new event received from PMIC device.
 *
 * @param[in] event New event type.
 */
static void register_state_change(enum npm1300_charger_event_t event)
{
	static enum npm1300_state_t state = APP_STATE_BATTERY_DISCONNECTED;

	switch (event) {
	case APP_CHARGER_EVENT_BATTERY_DETECTED:
		if (state == APP_STATE_BATTERY_DISCONNECTED) {
			state = APP_STATE_BATTERY_CONNECTED;
			printf("State: BATTERY_CONNECTED. \n");
		}

		if (state == APP_STATE_VBUS_CONNECTED_BATTERY_DISCONNECTED) {
			state = APP_STATE_VBUS_CONNECTED_BATTERY_CONNECTED;
			printf("State: VBUS_CONNECTED_BATTERY_CONNECTED. \n");
		}

		if (state == APP_STATE_VBUS_CONNECTED_CHARGING_TRICKE ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_CC ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_CV ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_COMPLETED) {
			printf("State: BATTERY_CONNECTED. \n");
		}
		break;
	case APP_CHARGER_EVENT_BATTERY_REMOVED:
		if (state == APP_STATE_BATTERY_CONNECTED) {
			state = APP_STATE_BATTERY_DISCONNECTED;
			printf("State: BATTERY_DISCONNECTED. \n");
		}

		if (state == APP_STATE_VBUS_CONNECTED_BATTERY_CONNECTED ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_TRICKE ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_CC ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_CV ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_COMPLETED) {
			state = APP_STATE_VBUS_CONNECTED_BATTERY_DISCONNECTED;
			printf("State: VBUS_CONNECTED_BATTERY_DISCONNECTED. \n");
		}
		break;
	case APP_CHARGER_EVENT_VBUS_DETECTED:
		if (state == APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING ||
		    state == APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING_ALERT1 ||
		    state == APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING_ALERT2) {
			state = APP_STATE_VBUS_CONNECTED_BATTERY_CONNECTED;
			printf("State: VBUS_CONNECTED_BATTERY_CONNECTED. \n");
		}
		if (state == APP_STATE_BATTERY_DISCONNECTED) {
			state = APP_STATE_VBUS_CONNECTED_BATTERY_DISCONNECTED;
			printf("State: VBUS_CONNECTED_BATTERY_DISCONNECTED. \n");
		}
		break;
	case APP_CHARGER_EVENT_VBUS_REMOVED:
		if (state == APP_STATE_VBUS_CONNECTED_CHARGING_TRICKE ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_CC ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_CV ||
		    state == APP_STATE_VBUS_CONNECTED_CHARGING_COMPLETED ||
		    state == APP_STATE_VBUS_CONNECTED_BATTERY_CONNECTED) {
			state = APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING;
			printf("State: VBUS_NOT_CONNECTED_DISCHARGING. \n");
		}
		break;
	case APP_CHARGER_EVENT_CHARGING_TRICKE_STARTED:
		if (state != APP_STATE_VBUS_CONNECTED_CHARGING_TRICKE &&
		    state != APP_STATE_VBUS_CONNECTED_CHARGING_CC &&
		    state != APP_STATE_VBUS_CONNECTED_CHARGING_CV &&
		    state != APP_STATE_VBUS_CONNECTED_CHARGING_COMPLETED) {
			state = APP_STATE_VBUS_CONNECTED_CHARGING_TRICKE;
			printf("State: VBUS_CONNECTED_CHARGING_TRICKE. \n");
		}
		break;
	case APP_CHARGER_EVENT_CHARGING_CC_STARTED:
		if (state != APP_STATE_VBUS_CONNECTED_CHARGING_CC &&
		    state != APP_STATE_VBUS_CONNECTED_CHARGING_CV) {
			state = APP_STATE_VBUS_CONNECTED_CHARGING_CC;
			printf("State: VBUS_CONNECTED_CHARGING_CC. \n");
		}
		break;
	case APP_CHARGER_EVENT_CHARGING_CV_STARTED:
		if (state != APP_STATE_VBUS_CONNECTED_CHARGING_CV) {
			state = APP_STATE_VBUS_CONNECTED_CHARGING_CV;
			printf("State: VBUS_CONNECTED_CHARGING_CV. \n");
		}
		break;
	case APP_CHARGER_EVENT_CHARGING_COMPLETED:
		if (state != APP_STATE_VBUS_CONNECTED_CHARGING_COMPLETED) {
			state = APP_STATE_VBUS_CONNECTED_CHARGING_COMPLETED;
			printf("State: VBUS_CONNECTED_CHARGING_COMPLETED. \n");
		}
		break;
	case APP_CHARGER_EVENT_BATTERY_LOW_ALERT1:
		if (state == APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING) {
			state = APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING_ALERT1;
			printf("State: VBUS_NOT_CONNECTED_DISCHARGING_ALERT1. \n");
		}
		break;
	case APP_CHARGER_EVENT_BATTERY_LOW_ALERT2:
		if (state == APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING ||
		    state == APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING_ALERT1) {
			state = APP_STATE_VBUS_NOT_CONNECTED_DISCHARGING_ALERT2;
			printf("State: VBUS_NOT_CONNECTED_DISCHARGING_ALERT2. \n");
		}
		break;

	default:
		printf("Unsupported event: %d. \n", event);
		break;
	}
}


static void vbus_callback(npmx_instance_t *p_pm, npmx_callback_type_t type, uint8_t mask)
{
	/* Current limit has to be applied each time when USB is (re)connected. */
	if (mask & (uint8_t)NPMX_EVENT_GROUP_VBUSIN_DETECTED_MASK) {
		register_state_change(APP_CHARGER_EVENT_VBUS_DETECTED);
		npmx_vbusin_task_trigger(npmx_vbusin_get(p_pm, 0), NPMX_VBUSIN_TASK_APPLY_CURRENT_LIMIT);
	}

	if (mask & (uint8_t)NPMX_EVENT_GROUP_VBUSIN_REMOVED_MASK) {
		register_state_change(APP_CHARGER_EVENT_VBUS_REMOVED);
	}
}

/**
 * @brief Function callback for ADC events.
 *
 * @param[in] p_pm Pointer to the instance of PMIC device.
 * @param[in] type Type of callback, should be always NPMX_CALLBACK_TYPE_EVENT_VBUSIN_VOLTAGE.
 * @param[in] mask Received event mask @ref npmx_event_group_vbusin_mask_t .
 */
static void adc_callback(npmx_instance_t *p_pm, npmx_callback_type_t type, uint8_t mask)
{
	if ((mask & (uint8_t)NPMX_EVENT_GROUP_ADC_BAT_READY_MASK)) {
		static int32_t battery_voltage_millivolts_last;
		int32_t battery_voltage_millivolts;

		if (npmx_adc_meas_get(npmx_adc_get(p_pm, 0), NPMX_ADC_MEAS_VBAT,
				      &battery_voltage_millivolts) == NPMX_SUCCESS) {
			if (battery_voltage_millivolts != battery_voltage_millivolts_last) {
				battery_voltage_millivolts_last = battery_voltage_millivolts;
				printf("Battery:\t %ld mV. \n", battery_voltage_millivolts);
			}
			if (battery_voltage_millivolts < BATTERY_VOLTAGE_THRESHOLD_2) {
				register_state_change(APP_CHARGER_EVENT_BATTERY_LOW_ALERT2);
			} else if (battery_voltage_millivolts <
				   BATTERY_VOLTAGE_THRESHOLD_1) {
				register_state_change(APP_CHARGER_EVENT_BATTERY_LOW_ALERT1);
			}
		}
	}
}

/**
 * @brief Function callback for charger status events.
 *
 * @param[in] p_pm Pointer to the instance of PMIC device.
 * @param[in] type Type of callback, should always be NPMX_CALLBACK_TYPE_EVENT_BAT_CHAR_STATUS.
 * @param[in] mask Received event mask @ref npmx_event_group_charger_mask_t .
 */
static void charger_status_callback(npmx_instance_t *p_pm, npmx_callback_type_t type, uint8_t mask)
{
	npmx_charger_t *charger_instance = npmx_charger_get(p_pm, 0);

	if (mask & (uint8_t)NPMX_EVENT_GROUP_CHARGER_ERROR_MASK) {
		/* Check charger errors and run default debug callbacks to log error bits. */
		npmx_charger_errors_check(charger_instance);
	}

	npmx_charger_status_mask_t status;

	/* Delay required for status stabilization. */
	osDelay(5);

	if (npmx_charger_status_get(charger_instance, &status) == NPMX_SUCCESS) {
		if (status & NPMX_CHARGER_STATUS_TRICKLE_CHARGE_MASK) {
			register_state_change(APP_CHARGER_EVENT_CHARGING_TRICKE_STARTED);
		}

		if (status & NPMX_CHARGER_STATUS_CONSTANT_CURRENT_MASK) {
			register_state_change(APP_CHARGER_EVENT_CHARGING_CC_STARTED);
		}

		if (status & NPMX_CHARGER_STATUS_CONSTANT_VOLTAGE_MASK) {
			register_state_change(APP_CHARGER_EVENT_CHARGING_CV_STARTED);
		}

		if (status & NPMX_CHARGER_STATUS_COMPLETED_MASK) {
			register_state_change(APP_CHARGER_EVENT_CHARGING_COMPLETED);
		}
	}
}

/**
 * @brief Function callback for battery events.
 *
 * @param[in] p_pm Pointer to the instance of PMIC device.
 * @param[in] type Type of callback, should always be NPMX_CALLBACK_TYPE_EVENT_BAT_CHAR_BAT.
 * @param[in] mask Received event mask @ref npmx_event_group_battery_mask_t .
 */
static void charger_battery_callback(npmx_instance_t *p_pm, npmx_callback_type_t type, uint8_t mask)
{
	if (mask & (uint8_t)NPMX_EVENT_GROUP_BATTERY_DETECTED_MASK) {
		register_state_change(APP_CHARGER_EVENT_BATTERY_DETECTED);
	}

	if (mask & (uint8_t)NPMX_EVENT_GROUP_BATTERY_REMOVED_MASK) {
		register_state_change(APP_CHARGER_EVENT_BATTERY_REMOVED);
	}
}

void my_pmic_config(void)
{
	npmx_error_t ret;
	uint8_t mask;

   	// Enable VBAT auto measure every 1 second in single measurement mode
    npmx_adc_config_t adc_conf;
    adc_conf.vbat_burst =0;									//Set ADCCONFIG VBAT BURST to SINGLEMODE
    adc_conf.vbat_auto = 1;									//set ADCONFIG VBAT AUTO to Trigger measurement every 1 Second
    npmx_adc_t * adc = npmx_adc_get(&npm1300_instance, 0);	//Get ADC instance
    ret =  npmx_adc_config_set(adc, &adc_conf);


	// Check if VBUS is connected.
	npmx_vbusin_t * vbus = npmx_vbusin_get(&npm1300_instance, 0);  //Get the Vbus instance
	ret = npmx_vbusin_vbus_status_get(vbus, &mask);
		if (mask & NPMX_VBUSIN_STATUS_CONNECTED_MASK) {
			register_state_change(APP_CHARGER_EVENT_VBUS_DETECTED);
		}
	/* register callbacks for all events of the nPM*/
	/* Register callback for VBUS events. */
	npmx_core_register_cb(&npm1300_instance, vbus_callback, NPMX_CALLBACK_TYPE_EVENT_VBUSIN_VOLTAGE);
	/* Register callback for ADC events. */
	npmx_core_register_cb(&npm1300_instance, adc_callback, NPMX_CALLBACK_TYPE_EVENT_ADC);
	/* Register callback for battery events. */
	npmx_core_register_cb(&npm1300_instance, charger_battery_callback, NPMX_CALLBACK_TYPE_EVENT_BAT_CHAR_BAT);
	/* Register callback for charger status events. */
	npmx_core_register_cb(&npm1300_instance, charger_status_callback,  NPMX_CALLBACK_TYPE_EVENT_BAT_CHAR_STATUS);

	// Set GPIO 3 as GPIO Interrupt.
	ret = npmx_gpio_mode_set(npmx_gpio_get(&npm1300_instance, 3), NPMX_GPIO_MODE_OUTPUT_IRQ);

	// Disable charger before changing charge current.
    npmx_charger_t * charger = npmx_charger_get(&npm1300_instance, 0);
    ret = npmx_charger_module_disable_set(charger,NPMX_CHARGER_MODULE_CHARGER_MASK );

    // Set charging current.
    charger->charging_current_ua = NPM_BCHARGER_CHARGING_CURRENT_DEFAULT;
    ret = npmx_charger_charging_current_set(charger, charger->charging_current_ua);

	/* Set maximum discharging current. */
    charger->discharging_current_ma = NPM_BCHARGER_DISCHARGING_CURRENT_DEFAULT;
	ret = npmx_charger_discharging_current_set(charger, charger->discharging_current_ma);


	// Set battery termination voltage in Normal and Warm temperature.
    ret =npmx_charger_termination_normal_voltage_set(charger, npmx_charger_voltage_convert(4200));  //4.2V
    /* Set battery termination voltage in warm temperature. */
    ret =npmx_charger_termination_warm_voltage_set(charger, npmx_charger_voltage_convert(4000));  //4.0V

	// Enable charger for events handling.
    ret = npmx_charger_module_enable_set(charger,NPMX_CHARGER_MODULE_CHARGER_MASK | NPMX_CHARGER_MODULE_RECHARGE_MASK );

    //Change Buck 1 output Voltage
    npmx_buck_t * buck =  npmx_buck_get(&npm1300_instance, 0);
    ret = npmx_buck_converter_mode_set(buck, NPMX_BUCK_MODE_PWM);   //Set to PWM Mode
    ret = npmx_buck_normal_voltage_set(buck, NPMX_BUCK_VOLTAGE_2V5); //Set Buck 1 VOUT to 2.5V

    /* Set the current limit for the USB port to 500mA
     * Current limit needs to be applied after each USB (re)connection.
  	 */
    ret = npmx_vbusin_current_limit_set(vbus, npmx_vbusin_current_convert(500));

    /* Apply current limit. */
    ret = npmx_vbusin_task_trigger(vbus, NPMX_VBUSIN_TASK_APPLY_CURRENT_LIMIT);

    /* Set thermistor type and NTC beta value for ADC measurements.*/
    npmx_adc_ntc_config_t ntc_config = { .type = NPMX_ADC_NTC_TYPE_10_K, .beta = 3380 };
   	ret =npmx_adc_ntc_config_set(adc, &ntc_config);


   	/* Enable auto measurement of the battery current after the battery voltage measurement. */
   	ret =npmx_adc_ibat_meas_enable_set(adc, true);
   	/* Trigger required ADC measurements. WRC Not sure this is correct*/
 	ret =npmx_adc_task_trigger(adc, NPMX_ADC_TASK_SINGLE_SHOT_VBAT);
 	ret =npmx_adc_task_trigger(adc, NPMX_ADC_TASK_SINGLE_SHOT_NTC);


	//  Enable USB connections interrupts and events handling.
	npmx_core_event_interrupt_enable(&npm1300_instance, NPMX_EVENT_GROUP_VBUSIN_VOLTAGE, NPMX_EVENT_GROUP_VBUSIN_DETECTED_MASK |
				NPMX_EVENT_GROUP_VBUSIN_REMOVED_MASK);

	/* Enable all charging status interrupts and events. */
	npmx_core_event_interrupt_enable(
		&npm1300_instance, NPMX_EVENT_GROUP_BAT_CHAR_STATUS,
		NPMX_EVENT_GROUP_CHARGER_SUPPLEMENT_MASK | NPMX_EVENT_GROUP_CHARGER_TRICKLE_MASK |
			NPMX_EVENT_GROUP_CHARGER_CC_MASK | NPMX_EVENT_GROUP_CHARGER_CV_MASK |
			NPMX_EVENT_GROUP_CHARGER_COMPLETED_MASK |
			NPMX_EVENT_GROUP_CHARGER_ERROR_MASK);

	/* Enable battery interrupts and events. */
	npmx_core_event_interrupt_enable(&npm1300_instance, NPMX_EVENT_GROUP_BAT_CHAR_BAT,
					 NPMX_EVENT_GROUP_BATTERY_DETECTED_MASK | NPMX_EVENT_GROUP_BATTERY_REMOVED_MASK);

	/* Enable ADC measurements ready interrupts. */
	npmx_core_event_interrupt_enable(&npm1300_instance, NPMX_EVENT_GROUP_ADC, NPMX_EVENT_GROUP_ADC_BAT_READY_MASK);

}


//GPIO Callback for external Interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if (GPIO_Pin == GPIO_PIN_3)  //Check to see if Pin 3 triggered the INT
	{
		pmic_interrupt = true;
		npmx_core_interrupt(&npm1300_instance); 		//This sets a flag in npmx
		HAL_NVIC_DisableIRQ(EXTI3_IRQn);				//Disable GPIO Interrupt
	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartTask01 */
/**
  * @brief  Function implementing the myTask01 thread.
  * @param  argument: Not used
  * @retval None
  */


/* USER CODE END Header_StartTask01 */
void StartTask01(void *argument)
{
  /* USER CODE BEGIN 5 */
	npmx_error_t err;
	int ret;
  /* Infinite loop */
  for(;;)
  {
	printf("\n myTask01 \n"); //WRC print Task
	if (pmic_interrupt) {
		  //the nPM13xx interrupt GPIO signal will be active until the interrupt event registers are cleared by calling the npmx_core_proc function.
		  err=npmx_core_proc(&npm1300_instance);  //Process the interrupt
		  pmic_interrupt = false;
		  HAL_NVIC_EnableIRQ(EXTI3_IRQn);		//Re-enable GPIO IRQ
		  printf("\n myTask01 PMIC_INTERRUPT\n"); //WRC print Task


	 	  }
	ret = fuel_gauge_update(&npm1300_instance);
	vTaskDelay(1000);

  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */

  /* Infinite loop */
  for(;;)
  {
	printf(" myTask02 \n"); //WRC print Task

	vTaskDelay(1000);		//Delay task for 1 Second.  Allow other higher priority tasks to run
  }
  /* USER CODE END StartTask02 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
