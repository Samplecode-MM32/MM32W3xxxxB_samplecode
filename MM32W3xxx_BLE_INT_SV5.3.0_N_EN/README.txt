//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
1、Procedure description:
     The BLE library runs as a system interrupt service program, which is suitable for application scenarios that require a long CPU time but can be interrupted to implement a user function. Need to use two interrupt service routines,
     One is the GPIO interrupt corresponding to the IRQ interrupt pin, and the other is the interrupt corresponding to the SysTick. 
The interrupt service program corresponding to IRQ is used to run the Bluetooth protocol, which requires a high interrupt priority 
(for other users to interrupt).

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////i
2、Cooperating with the Bluetooth protocol stack, the system application implements interfaces such as SPI communication and timers.
The main functions include:

1. unsigned char SPI_WriteBuf(unsigned char reg, unsigned char const *pBuf, unsigned char len);

2. unsigned char SPI_ReadBuf(unsigned char reg, unsigned char *pBuf, unsigned char len);
The above two functions are implemented in the spi.c file, which is related to the BLE communication. To ensure BLE operation, 
the spi clock should be greater than 6MHz and less than 10MHz.
  
3. Char IsIrqEnabled(void) ;
Determine whether the IRQ signal generates an interrupt (low level is valid for interrupt) 。

4. void IRQ_RF(void);
The above two functions are implemented in the irq_rf.c file, which is related to BLE communication。

5. unsigned int GetSysTickCount(void); 
Get the accumulated value of the millisecond timer for timing and other functions。

6. void SysTick_Handler(void)
The above two functions are implemented in the bsp.c file, which is related to BLE communication. Please do not modify it.
The accuracy of the system tick timer can be changed, for example from 1ms to 10ms, does not affect the normal operation of BLE。

7. Low-power function implementation example：
void IrqMcuGotoSleepAndWakeup(void)
{
   if(ble_run_interrupt_McuCanSleep())
   {
     //to do MCU sleep/stop/standby
   }
}

This function is called cyclically in the user program of the main () function。

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
3、MCU and RF control pins：

   MCU      RF
   PB5      MOSI 
   PB4      MISO(Requires external hardware connection)
   PB3      SCK
   PD2      CSN
   PC12     IRQ(Requires external hardware connection)
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
4、Interface function：
1) void radio_initBle(unsigned char txpwr, unsigned char**addr/*Output*/);
2) void radio_standby(void);
3) void ble_run_interrupt_start(unsigned short adv_interval);
4) void SetBleIntRunningMode(void);
5) void ble_set_adv_type(unsigned char type);
6) void ble_set_adv_data(unsigned char* adv, unsigned char len);
7) void ble_set_adv_rsp_data(unsigned char* rsp, unsigned char len);
8) void ble_set_name(unsigned char* name,unsigned char len);
9) void ble_set_interval(unsigned short interval);
10) void ble_set_adv_enableFlag(char sEnableFlag);
11) unsigned char ble_set_role(unsigned char role_new, unsigned short scan_window);
12) void ble_disconnect(void);
13) unsigned char *get_ble_version(void);
14) unsigned char *GetFirmwareInfo(void);
15) void ser_write_rsp_pkt(unsigned char pdu_type);
16) void att_notFd(unsigned char pdu_type, unsigned char attOpcode, unsigned short attHd );
17) void att_ErrorFd_ecode(unsigned char pdu_type, unsigned char attOpcode, unsigned short attHd, unsigned char errCode );
18) void att_server_rdByGrTypeRspDeviceInfo(unsigned char pdu_type);
19) void att_server_rdByGrTypeRspPrimaryService(unsigned char pdu_type,
                                                unsigned short start_hd,
                                                unsigned short end_hd,
                                                unsigned char*uuid,
                                                unsigned char uuidlen);
20) void att_server_rd(unsigned char pdu_type,
                        unsigned char attOpcode,
                        unsigned short att_hd,
                        unsigned char* attValue,
                        unsigned char datalen );
21) unsigned char sconn_notifydata(unsigned char* data, unsigned char len);
22) unsigned char sconn_indicationdata(unsigned char* data, unsigned char len);
23) void SetFixAdvChannel(unsigned char isFixCh37Flag);
24) void test_carrier(unsigned char freq, unsigned char txpwr);
25) void radio_setBleAddr(u8 addr[6]);
26) void SIG_ConnParaUpdateReq(unsigned short IntervalMin, unsigned short IntervalMax, unsigned short SlaveLatency,unsigned short TimeoutMultiplier);
27) unsigned short sconn_GetConnInterval(void);
28) Unsigned char GetRssiData(void);
29)unsigned char radio_initBle_TO(unsigned char txpwr, unsigned char** addr, unsigned short ms_timeout);
30)void radio_initBle_recover(unsigned char txpwr, unsigned char** addr);
31)void radio_setCal_nonBlocking(unsigned nonblocking);
32)void radio_resume(void);
33)void radio_fixSPI(unsigned char cs,unsigned char sck,unsigned char mosi);
34)void radio_setXtal(unsigned char xoib, unsigned char xocc);
35)unsigned char radio_setRxGain(unsigned char lna_gain, unsigned char preamble_th);
36)void ble_run(unsigned short interv_adv);
37)unsigned char ble_set_wakeupdly(unsigned short counter);
38)unsigned char ble_run_interrupt_McuCanSleep(void);
39)void ser_write_rsp_pkt(unsigned char pdu_type);
40)unsigned char* GetMasterDeviceMac(unsigned char* MacType);
41)void SetLePinCode(unsigned char *PinCode/*6 0~9 digitals*/);
42)unsigned char* GetLTKInfo(unsigned char* newFlag);
43)void s_llSmSecurityReq(void);
44)void Led_getInfo(unsigned char* data);
45)void SetLEDLum(int r, int g, int b, int L); //rgb[0~255], L[0~100,101] 101 means not used 
46)void UpdateLEDValueFading(unsigned char flag_fade); //1-fading, 0-now
47)unsigned char OTA_Proc(unsigned char *data, unsigned short len);
48)void SetBleIntRunningMode(void);
49)void ble_run_interrupt_start(unsigned short interv_adv);
50)void ble_nMsRoutine(void);
51)GetOtaAddr;
52)void WriteFlashE2PROM(u8* data, u16 len, u32 pos, u8 flag);
53)void OtaSystemReboot(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
5、Power-up information：

This version is a comprehensive version of transparent transmission and interruption, and the mode is switched by the macro of USE_AT_CMD
Baud rate: 9600

