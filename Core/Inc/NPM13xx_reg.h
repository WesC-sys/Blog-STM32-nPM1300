#ifndef nPM13xx_reg_H
#define nPM13xx_reg_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * NPM1300 I2C Address
 */
#define NPM13xx_ADDR 0x6b

/**
 * nPM13xx MAIN registers list.
 */
#define nPM13xx_REG_TASKSWRESET                   0x0001
#define nPM13xx_REG_EVENTSADCSET                  0x0002
#define nPM13xx_REG_EVENTSADCCLR                  0x0003
#define nPM13xx_REG_INTENEVENTSADCSET             0x0004
#define nPM13xx_REG_INTENEVENTSADCCLR             0x0005
#define nPM13xx_REG_EVENTSBCHARGER0SET            0x0006
#define nPM13xx_REG_EVENTSBCHARGER0CLR            0x0007
#define nPM13xx_REG_INTENEVENTSBCHARGER0SET       0x0008
#define nPM13xx_REG_INTENEVENTSBCHARGER0CLR       0x0009
#define nPM13xx_REG_EVENTSBCHARGER1SET            0x000A
#define nPM13xx_REG_EVENTSBCHARGER1CLR            0x000B
#define nPM13xx_REG_INTENEVENTSBCHARGER1SET       0x000C
#define nPM13xx_REG_INTENEVENTSBCHARGER1CLR       0x000D
#define nPM13xx_REG_EVENTSBCHARGER2SET            0x000E
#define nPM13xx_REG_EVENTSBCHARGER2CLR            0x000F
#define nPM13xx_REG_INTENEVENTSBCHARGER2SET       0x0010
#define nPM13xx_REG_INTENEVENTSBCHARGER2CLR       0x0011
#define nPM13xx_REG_EVENTSSHPHLDSET               0x0012
#define nPM13xx_REG_EVENTSSHPHLDCLR               0x0013
#define nPM13xx_REG_INTENEVENTSSHPHLDSET          0x0014
#define nPM13xx_REG_INTENEVENTSSHPHLDCLR          0x0015
#define nPM13xx_REG_EVENTSVBUSIN0SET              0x0016
#define nPM13xx_REG_EVENTSVBUSIN0CLR              0x0017
#define nPM13xx_REG_INTENEVENTSVBUSIN0SET         0x0018
#define nPM13xx_REG_INTENEVENTSVBUSIN0CLR         0x0019
#define nPM13xx_REG_EVENTSVBUSIN1SET              0x001A
#define nPM13xx_REG_EVENTSVBUSIN1CLR              0x001B
#define nPM13xx_REG_INTENEVENTSVBUSIN1SET         0x001C
#define nPM13xx_REG_INTENEVENTSVBUSIN1CLR         0x001D
#define nPM13xx_REG_EVENTSGPIOSET                 0x0022
#define nPM13xx_REG_EVENTSGPIOCLR                 0x0023
#define nPM13xx_REG_INTENEVENTSGPIOSET            0x0024
#define nPM13xx_REG_INTENEVENTSGPIOCLR            0x0025

/**
 * nPM13xx VBUSIN registers list.
 */
#define nPM13xx_REG_VBUSIN_TASKUPDATEILIMSW            0x0200
#define nPM13xx_REG_VBUSIN_VBUSINILIM0                 0x0201
#define nPM13xx_REG_VBUSIN_VBUSSUSPEND                 0x0203
#define nPM13xx_REG_VBUSIN_USBCDETECTSTATUS            0x0205
#define nPM13xx_REG_VBUSIN_VBUSINSTATUS                0x0207

/**
 * nPM13xx CHARGER registers list.
 */
#define nPM13xx_REG_BCHARGER_TASKRELEASEERR            0x0300
#define nPM13xx_REG_BCHARGER_TASKCLEARCHGERR           0x0301
#define nPM13xx_REG_BCHARGER_TASKCLEARSAFETYTIMER      0x0302
#define nPM13xx_REG_BCHARGER_BCHGENABLESET             0x0304
#define nPM13xx_REG_BCHARGER_BCHGENABLECLR             0x0305
#define nPM13xx_REG_BCHARGER_BCHGDISABLESET            0x0306
#define nPM13xx_REG_BCHARGER_BCHGDISABLECLR            0x0307
#define nPM13xx_REG_BCHARGER_BCHGISETMSB               0x0308
#define nPM13xx_REG_BCHARGER_BCHGISETLSB               0x0309
#define nPM13xx_REG_BCHARGER_BCHGISETDISCHARGEMSB      0x030A
#define nPM13xx_REG_BCHARGER_BCHGISETDISCHARGELSB      0x030B
#define nPM13xx_REG_BCHARGER_BCHGVTERM                 0x030C
#define nPM13xx_REG_BCHARGER_BCHGVTERMR                0x030D
#define nPM13xx_REG_BCHARGER_BCHGVTRICKLESEL           0x030E
#define nPM13xx_REG_BCHARGER_BCHGITERMSEL              0x030F
#define nPM13xx_REG_BCHARGER_NTCCOLD                   0x0310
#define nPM13xx_REG_BCHARGER_NTCCOLDLSB                0x0311
#define nPM13xx_REG_BCHARGER_NTCCOOL                   0x0312
#define nPM13xx_REG_BCHARGER_NTCCOOLLSB                0x0313
#define nPM13xx_REG_BCHARGER_NTCWARM                   0x0314
#define nPM13xx_REG_BCHARGER_NTCWARMLSB                0x0315
#define nPM13xx_REG_BCHARGER_NTCHOT                    0x0316
#define nPM13xx_REG_BCHARGER_NTCHOTLSB                 0x0317
#define nPM13xx_REG_BCHARGER_DIETEMPSTOP               0x0318
#define nPM13xx_REG_BCHARGER_DIETEMPSTOPLSB            0x0319
#define nPM13xx_REG_BCHARGER_DIETEMPRESUME             0x031A
#define nPM13xx_REG_BCHARGER_DIETEMPRESUMELSB          0x031B
#define nPM13xx_REG_BCHARGER_BCHGILIMSTATUS            0x032D
#define nPM13xx_REG_BCHARGER_NTCSTATUS                 0x0332
#define nPM13xx_REG_BCHARGER_DIETEMPSTATUS             0x0333
#define nPM13xx_REG_BCHARGER_BCHGCHARGESTATUS          0x0334
#define nPM13xx_REG_BCHARGER_BCHGERRREASON             0x0336
#define nPM13xx_REG_BCHARGER_BCHGERRSENSOR             0x0337
#define nPM13xx_REG_BCHARGER_BCHGCONFIG                0x033C

/**
 * nPM13xx BUCK registers list
 */
#define nPM13xx_REG_BUCK_BUCK1ENASET                   0x0400
#define nPM13xx_REG_BUCK_BUCK1ENACLR                   0x0401
#define nPM13xx_REG_BUCK_BUCK2ENASET                   0x0402
#define nPM13xx_REG_BUCK_BUCK2ENACLR                   0x0403
#define nPM13xx_REG_BUCK_BUCK1PWMSET                   0x0404
#define nPM13xx_REG_BUCK_BUCK1PWMCLR                   0x0405
#define nPM13xx_REG_BUCK_BUCK2PWMSET                   0x0406
#define nPM13xx_REG_BUCK_BUCK2PWMCLR                   0x0407
#define nPM13xx_REG_BUCK_BUCK1NORMVOUT                 0x0408
#define nPM13xx_REG_BUCK_BUCK1RETVOUT                  0x0409
#define nPM13xx_REG_BUCK_BUCK2NORMVOUT                 0x040A
#define nPM13xx_REG_BUCK_BUCK2RETVOUT                  0x040B
#define nPM13xx_REG_BUCK_BUCKENCTRL                    0x040C
#define nPM13xx_REG_BUCK_BUCKVRETCTRL                  0x040D
#define nPM13xx_REG_BUCK_BUCKPWMCTRL                   0x040E
#define nPM13xx_REG_BUCK_BUCKSWCTRLSEL                 0x040F
#define nPM13xx_REG_BUCK_BUCK1VOUTSTATUS               0x0410
#define nPM13xx_REG_BUCK_BUCK2VOUTSTATUS               0x0411
#define nPM13xx_REG_BUCK_BUCKCTRL0                     0x0415
#define nPM13xx_REG_BUCK_BUCKSTATUS                    0x0434

/**
 * nPM13xx ADC registers list.
 */
#define nPM13xx_REG_ADC_TASKVBATMEASURE                0x0500
#define nPM13xx_REG_ADC_TASKNTCMEASURE                 0x0501
#define nPM13xx_REG_ADC_TASKTEMPMEASURE                0x0502
#define nPM13xx_REG_ADC_TASKVSYSMEASURE                0x0503
#define nPM13xx_REG_ADC_TASKIBATMEASURE                0x0506
#define nPM13xx_REG_ADC_TASKVBUS7MEASURE               0x0507
#define nPM13xx_REG_ADC_TASKDELAYEDVBATMEASURE         0x0508
#define nPM13xx_REG_ADC_ADCCONFIG                      0x0509
#define nPM13xx_REG_ADC_ADCNTCRSEL                     0x050A
#define nPM13xx_REG_ADC_ADCAUTOTIMCONF                 0x050B
#define nPM13xx_REG_ADC_TASKAUTOTIMUPDATE              0x050C
#define nPM13xx_REG_ADC_ADCDELTIMCONF                  0x050D
#define nPM13xx_REG_ADC_ADCIBATMEASSTATUS              0x0510
#define nPM13xx_REG_ADC_ADCVBATRESULTMSB               0x0511
#define nPM13xx_REG_ADC_ADCNTCRESULTMSB                0x0512
#define nPM13xx_REG_ADC_ADCTEMPRESULTMSB               0x0513
#define nPM13xx_REG_ADC_ADCVSYSRESULTMSB               0x0514
#define nPM13xx_REG_ADC_ADCGP0RESULTLSBS               0x0515
#define nPM13xx_REG_ADC_ADCVBAT0RESULTMSB              0x0516
#define nPM13xx_REG_ADC_ADCVBAT1RESULTMSB              0x0517
#define nPM13xx_REG_ADC_ADCVBAT2RESULTMSB              0x0518
#define nPM13xx_REG_ADC_ADCVBAT3RESULTMSB              0x0519
#define nPM13xx_REG_ADC_ADCGP1RESULTLSBS               0x051A
#define nPM13xx_REG_ADC_ADCIBATMEASEN                  0x0524

/**
 *  nPM13xx GPIOS registers list.
 */
#define nPM13xx_REG_GPIOS_GPIOMODE_0                   0x0600
#define nPM13xx_REG_GPIOS_GPIOMODE_1                   0x0601
#define nPM13xx_REG_GPIOS_GPIOMODE_2                   0x0602
#define nPM13xx_REG_GPIOS_GPIOMODE_3                   0x0603
#define nPM13xx_REG_GPIOS_GPIOMODE_4                   0x0604
#define nPM13xx_REG_GPIOS_GPIODRIVE_0                  0x0605
#define nPM13xx_REG_GPIOS_GPIODRIVE_1                  0x0606
#define nPM13xx_REG_GPIOS_GPIODRIVE_2                  0x0607
#define nPM13xx_REG_GPIOS_GPIODRIVE_3                  0x0608
#define nPM13xx_REG_GPIOS_GPIODRIVE_4                  0x0609
#define nPM13xx_REG_GPIOS_GPIOPUEN_0                   0x060A
#define nPM13xx_REG_GPIOS_GPIOPUEN_1                   0x060B
#define nPM13xx_REG_GPIOS_GPIOPUEN_2                   0x060C
#define nPM13xx_REG_GPIOS_GPIOPUEN_3                   0x060D
#define nPM13xx_REG_GPIOS_GPIOPUEN_4                   0x060E
#define nPM13xx_REG_GPIOS_GPIOPDEN_0                   0x060F
#define nPM13xx_REG_GPIOS_GPIOPDEN_1                   0x0610
#define nPM13xx_REG_GPIOS_GPIOPDEN_2                   0x0611
#define nPM13xx_REG_GPIOS_GPIOPDEN_3                   0x0612
#define nPM13xx_REG_GPIOS_GPIOPDEN_4                   0x0613
#define nPM13xx_REG_GPIOS_GPIOOPENDRAIN_0              0x0614
#define nPM13xx_REG_GPIOS_GPIOOPENDRAIN_1              0x0615
#define nPM13xx_REG_GPIOS_GPIOOPENDRAIN_2              0x0616
#define nPM13xx_REG_GPIOS_GPIOOPENDRAIN_3              0x0617
#define nPM13xx_REG_GPIOS_GPIOOPENDRAIN_4              0x0618
#define nPM13xx_REG_GPIOS_GPIODEBOUNCE_0               0x0619
#define nPM13xx_REG_GPIOS_GPIODEBOUNCE_1               0x061A
#define nPM13xx_REG_GPIOS_GPIODEBOUNCE_2               0x061B
#define nPM13xx_REG_GPIOS_GPIODEBOUNCE_3               0x061C
#define nPM13xx_REG_GPIOS_GPIODEBOUNCE_4               0x061D
#define nPM13xx_REG_GPIOS_GPIOSTATUS                   0x061E

/**
 * nPM13xx TIMER and WATCHDOG registers list.
 */
#define nPM13xx_REG_TIMER_TIMERSET                     0x0700
#define nPM13xx_REG_TIMER_TIMERCLR                     0x0701
#define nPM13xx_REG_TIMER_TIMERTARGETSTROBE            0x0703
#define nPM13xx_REG_TIMER_WATCHDOGKICK                 0x0704
#define nPM13xx_REG_TIMER_TIMERCONFIG                  0x0705
#define nPM13xx_REG_TIMER_TIMERSTATUS                  0x0706
#define nPM13xx_REG_TIMER_TIMERHIBYTE                  0x0708
#define nPM13xx_REG_TIMER_TIMERMIDBYTE                 0x0709
#define nPM13xx_REG_TIMER_TIMERLOBYTE                  0x070A

/**
 * nPM13xx LOAD SWITCH / LDO registers list.
 */
#define nPM13xx_REG_LDSW_TASKLDSW1SET                  0x0800
#define nPM13xx_REG_LDSW_TASKLDSW1CLR                  0x0801
#define nPM13xx_REG_LDSW_TASKLDSW2SET                  0x0802
#define nPM13xx_REG_LDSW_TASKLDSW2CLR                  0x0803
#define nPM13xx_REG_LDSW_LDSWSTATUS                    0x0804
#define nPM13xx_REG_LDSW_LDSW1GPISEL                   0x0805
#define nPM13xx_REG_LDSW_LDSW2GPISEL                   0x0806
#define nPM13xx_REG_LDSW_LDSWCONFIG                    0x0807
#define nPM13xx_REG_LDSW_LDSW1LDOSEL                   0x0808
#define nPM13xx_REG_LDSW_LDSW2LDOSEL                   0x0809
#define nPM13xx_REG_LDSW_LDSW1VOUTSEL                  0x080C
#define nPM13xx_REG_LDSW_LDSW2VOUTSEL                  0x080D

/**
 * nPM13xx POF registers list.
 */
#define nPM13xx_REG_POF_POFCONFIG                      0x0900

/**
 * nPM13xx LED DRIVER registers list.
 */
#define nPM13xx_REG_LEDDRV_LEDDRV0MODESEL              0x0A00
#define nPM13xx_REG_LEDDRV_LEDDRV1MODESEL              0x0A01
#define nPM13xx_REG_LEDDRV_LEDDRV2MODESEL              0x0A02
#define nPM13xx_REG_LEDDRV_LEDDRV0SET                  0x0A03
#define nPM13xx_REG_LEDDRV_LEDDRV0CLR                  0x0A04
#define nPM13xx_REG_LEDDRV_LEDDRV1SET                  0x0A05
#define nPM13xx_REG_LEDDRV_LEDDRV1CLR                  0x0A06
#define nPM13xx_REG_LEDDRV_LEDDRV2SET                  0x0A07
#define nPM13xx_REG_LEDDRV_LEDDRV2CLR                  0x0A08

/**
 * nPM13xx SHIP / HIBERNATE registers list.
*/
#define nPM13xx_REG_SHIP_TASKENTERHIBERNATE            0x0B00
#define nPM13xx_REG_SHIP_TASKSHPHLDCFGSTROBE           0x0B01
#define nPM13xx_REG_SHIP_TASKENTERSHIPMODE             0x0B02
#define nPM13xx_REG_SHIP_TASKRESETCFG                  0x0B03
#define nPM13xx_REG_SHIP_SHPHLDCONFIG                  0x0B04
#define nPM13xx_REG_SHIP_SHPHLDSTATUS                  0x0B05
#define nPM13xx_REG_SHIP_LPRESETCONFIG                 0x0B06

/**
 * nPM13xx ERRLOG instance registers list.
*/
#define nPM13xx_REG_ERRLOG_TASKCLRERRLOG               0x0E00
#define nPM13xx_REG_ERRLOG_SCRATCH0                    0x0E01
#define nPM13xx_REG_ERRLOG_SCRATCH1                    0x0E02
#define nPM13xx_REG_ERRLOG_RSTCAUSE                    0x0E03
#define nPM13xx_REG_ERRLOG_CHARGERERRREASON            0x0E04
#define nPM13xx_REG_ERRLOG_CHARGERERRSENSOR            0x0E05

/**
 * nPM13xx GPIO mode setting.
*/
#define nPM13xx_GPIO_MODE_GPIINPUT                     0x00
#define nPM13xx_GPIO_MODE_GPILOGIC1                    0x01
#define nPM13xx_GPIO_MODE_GPILOGIC0                    0x02
#define nPM13xx_GPIO_MODE_GPIEVENTRISE                 0x03
#define nPM13xx_GPIO_MODE_GPIEVENTFALL                 0x04
#define nPM13xx_GPIO_MODE_GPOIRQ                       0x05
#define nPM13xx_GPIO_MODE_GPORESET                     0x06
#define nPM13xx_GPIO_MODE_GPOPLW                       0x07
#define nPM13xx_GPIO_MODE_GPOLOGIC1                    0x08
#define nPM13xx_GPIO_MODE_GPOLOGIC0                    0x09

/**
 *  nPM13xx BATTERY CHARGE DISABLE register setting.
 */
#define nPM13xx_BCHGDISABLESET_DISABLERCHG             0x01
#define nPM13xx_BCHGDISABLESET_IGNORENTC               0x02

/**
 * nPM13xx BATTERY CHARGE RE-ENABLE register setting.
 */
#define nPM13xx_BCHGDISABLECLR_ENABLERCHG              0x01
#define nPM13xx_BCHGDISABLECLR_USENTC                  0x02

/**
 * nPM13xx BCHGENABLESET register setting.
*/
#define nPM13xx_BCHGENABLESET_ENABLECHG                0x01
#define nPM13xx_BCHGENABLESET_ENABLECOOL               0x02

/**
 * nPM13xx BCHGENABLECLR register setting.
*/
#define nPM13xx_BCHGENABLECLR_DISABLECHG               0x01
#define nPM13xx_BCHGENABLECLR_DISABLECOOL              0x02

/**
 * nPM13xx ADC CONFIG register setting.
*/
#define nPM13xx_ADCCONFIG_AUTOENABLE                   0x01
#define nPM13xx_ADCCONFIG_BURSTMODE                    0x02

/**
 * nPM13xx Battery Charger Termination Voltage Normal setting.
*/
#define nPM13xx_BCHGVTERMNORM_3V50                     0x00
#define nPM13xx_BCHGVTERMNORM_3V55                     0x01
#define nPM13xx_BCHGVTERMNORM_3V60                     0x02
#define nPM13xx_BCHGVTERMNORM_3V65                     0x03
#define nPM13xx_BCHGVTERMNORM_4V00                     0x04
#define nPM13xx_BCHGVTERMNORM_4V05                     0x05
#define nPM13xx_BCHGVTERMNORM_4V10                     0x06
#define nPM13xx_BCHGVTERMNORM_4V15                     0x07
#define nPM13xx_BCHGVTERMNORM_4V20                     0x08
#define nPM13xx_BCHGVTERMNORM_4V25                     0x09
#define nPM13xx_BCHGVTERMNORM_4V30                     0x0A
#define nPM13xx_BCHGVTERMNORM_4V35                     0x0B
#define nPM13xx_BCHGVTERMNORM_4V40                     0x0C
#define nPM13xx_BCHGVTERMNORM_4V45                     0x0D

/**
 * nPM13xx Battery Charging current setting.
*/
#define nPM13xx_CHARGING_CURRENT_MIN                   32
#define nPM13xx_CHARGING_CURRENT_DEFAULT               200
#define nPM13xx_CHARGING_CURRENT_MAX                   800

/**
 * nPM13xx VBAT/VSYS/VBUS measurement setting.
*/
#define nPM13xx_TRIGGER_MEASUREMENT                    0x01
#define nPM13xx_VBAT_FULL_SCALE_MILLIVOLTS             5000.0f
#define nPM13xx_VBAT_DATA_RESOLUTION                   0x03FF
#define nPM13xx_VSYS_FULL_SCALE_MILLIVOLTS             6375.0f
#define nPM13xx_VSYS_DATA_RESOLUTION                   0x03FF
#define nPM13xx_VBUS_FULL_SCALE_MILLIVOLTS             7500.0f
#define nPM13xx_VBUS_DATA_RESOLUTION                   0x03FF

/**
 * nPM13xx battery charging status setting.
*/
#define nPM13xx_CHARGE_STATUS_BATTERYDETECTED          0x01
#define nPM13xx_CHARGE_STATUS_COMPLETED                0x02
#define nPM13xx_CHARGE_STATUS_TRICKLECHARGE            0x04
#define nPM13xx_CHARGE_STATUS_CONSTANTCURRENT          0x08
#define nPM13xx_CHARGE_STATUS_CONSTANTVOLTAGE          0x10
#define nPM13xx_CHARGE_STATUS_RECHARGE                 0x20
#define nPM13xx_CHARGE_STATUS_DIETEMPHIGHCHGPAUSED     0x40
#define nPM13xx_CHARGE_STATUS_SUPPLEMENTACTIVE         0x80

/**
 * nPM13xx event and interrupt setting.
*/
#define nPM13xx_EVENTADCVBATRDY                        0x01
#define nPM13xx_EVENTADCNTCRDY                         0x02
#define nPM13xx_EVENTADCTEMPRDY                        0x04
#define nPM13xx_EVENTADCVSYSRDY                        0x08
#define nPM13xx_EVENTADCVSET1RDY                       0x10
#define nPM13xx_EVENTADCVSET2RDY                       0x20
#define nPM13xx_EVENTADCIBATRDY                        0x40
#define nPM13xx_EVENTADCVBUS7V0RDY                     0x80
#define nPM13xx_EVENTS_ALL_FLAGS_MASK                  0xFF
#define nPM13xx_WAIT_EVENT_TIMEOUT_MS                  2000


#ifdef __cplusplus
}
#endif
#endif // nPM13xx_H

