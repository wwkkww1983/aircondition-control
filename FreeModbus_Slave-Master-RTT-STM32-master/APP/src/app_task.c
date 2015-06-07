#include "app_task.h"

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#elif __ICCARM__
#pragma section="HEAP"
#else
extern int __bss_end;
#endif

uint8_t CpuUsageMajor, CpuUsageMinor; //CPU使用率
float voltage_out_1,voltage_out_2;
USHORT  usModbusUserData[MB_PDU_SIZE_MAX];
UCHAR   ucModbusUserData[MB_PDU_SIZE_MAX];
//====================操作系统各线程优先级==================================
#define thread_AIAODIDO_Prio		    	12
#define thread_SysMonitor_Prio		    	11
#define thread_ModbusSlavePoll_Prio      	10
#define thread_ModbusMasterPoll_Prio      	 9
ALIGN(RT_ALIGN_SIZE)
//====================操作系统各线程堆栈====================================
static rt_uint8_t thread_SysMonitor_stack[256];
static rt_uint8_t thread_ModbusSlavePoll_stack[512];
static rt_uint8_t thread_ModbusMasterPoll_stack[512];
static rt_uint8_t thread_AIAODIDOPoll_stack[512];

struct rt_thread thread_SysMonitor;
struct rt_thread thread_ModbusSlavePoll;
struct rt_thread thread_ModbusMasterPoll;
struct rt_thread thread_AIAODIDO ;

//***************************系统监控线程***************************
//函数定义: void thread_entry_SysRunLed(void* parameter)
//入口参数：无
//出口参数：无
//备    注：Editor：Armink   2013-08-02   Company: BXXJS
//******************************************************************
void thread_entry_SysMonitor(void* parameter)
{
	eMBMasterReqErrCode    errorCode = MB_MRE_NO_ERR;
	uint16_t errorCount = 0;
	while (1)
	{
		//cpu_usage_get(&CpuUsageMajor, &CpuUsageMinor);
		//usSRegHoldBuf[S_HD_CPU_USAGE_MAJOR] = CpuUsageMajor;
		//usSRegHoldBuf[S_HD_CPU_USAGE_MINOR] = CpuUsageMinor;
		rt_thread_delay(DELAY_SYS_RUN_LED);
		rt_thread_delay(DELAY_SYS_RUN_LED);
		IWDG_Feed(); //feed the dog
		//Test Modbus Master
		usModbusUserData[0] = (USHORT)(rt_tick_get()/10);
		usModbusUserData[1] = (USHORT)(rt_tick_get()%10);
		ucModbusUserData[0] = 0x1F;
//		errorCode = eMBMasterReqReadDiscreteInputs(1,3,8,RT_WAITING_FOREVER);
//		errorCode = eMBMasterReqWriteMultipleCoils(1,3,5,ucModbusUserData,RT_WAITING_FOREVER);
		errorCode = eMBMasterReqWriteCoil(1,8,0xFF00,RT_WAITING_FOREVER);
//		errorCode = eMBMasterReqReadCoils(1,3,8,RT_WAITING_FOREVER);
//		errorCode = eMBMasterReqReadInputRegister(1,3,2,RT_WAITING_FOREVER);
//		errorCode = eMBMasterReqWriteHoldingRegister(1,3,usModbusUserData[0],RT_WAITING_FOREVER);
//		errorCode = eMBMasterReqWriteMultipleHoldingRegister(1,3,2,usModbusUserData,RT_WAITING_FOREVER);
//		errorCode = eMBMasterReqReadHoldingRegister(1,3,2,RT_WAITING_FOREVER);
//		errorCode = eMBMasterReqReadWriteMultipleHoldingRegister(1,3,2,usModbusUserData,5,2,RT_WAITING_FOREVER);
		//记录出错次数
		if (errorCode != MB_MRE_NO_ERR) {
			errorCount++;
		}
	}
}



//************************AIAODIDO轮训**************************
//函数定义: void thread_entry_AIAODIDO(void* parameter)
//入口参数：无
//出口参数：无
//备    注：Editor：Fan  2015-04-17    Company: TCU
//******************************************************************
void thread_entry_AIAODIDO(void* parameter)
{
   uint16_t GPIO_DI_Pin=((uint16_t)0x0001);
   unsigned  int short DI_Input=0x80;
	   
		 DAC_INIT();
	  // voltage_out_1=1;
	  //voltage_out_2=2;
	   ADC_Configuration();
	   GPIO_INIT();


   
	while (1)
	{

		
		ADC_Show();
    //模拟量输入值 传入寄存器
		usSRegInBuf[0]=p_ch[0];
		usSRegInBuf[1]=(USHORT)(p_ch[0]*10)%10;
		usSRegInBuf[2]=p_ch[1];
		usSRegInBuf[3]=(USHORT)(p_ch[1]*10)%10;
		usSRegInBuf[4]=p_ch[2];
		usSRegInBuf[5]=(USHORT)(p_ch[2]*10)%10;
		usSRegInBuf[6]=p_ch[3];
		usSRegInBuf[7]=(USHORT)(p_ch[3]*10)%10;
		usSRegInBuf[8]=p_ch[4];
		usSRegInBuf[9]=(USHORT)(p_ch[4]*10)%10;
		usSRegInBuf[10]=p_ch[5];
		usSRegInBuf[11]=(USHORT)(p_ch[5]*10)%10;
		usSRegInBuf[12]=p_ch[6];
		usSRegInBuf[13]=(USHORT)(p_ch[6]*10)%10;
	// analog input

    GPIO_DI_Pin=((uint16_t)0x0001);
		DI_Input=0x01;
		

		while((GPIO_DI_Pin & 0xffff) != 0)       //数字量输入值 传入寄存器
		{
			

			
	
			

			if(  GPIO_ReadInputDataBit(GPIOD,GPIO_DI_Pin))
			{
				ucSDiscInBuf[0]=	ucSDiscInBuf[0] | DI_Input ;
			}
			else
			{
				ucSDiscInBuf[0]=	ucSDiscInBuf[0] & (~DI_Input) ;
			}
			
			
	   	
			
			
			
		  DI_Input=	DI_Input <<1;
			GPIO_DI_Pin=GPIO_DI_Pin<<1;
		}
		
		
		
		    GPIO_DI_Pin=((uint16_t)0x0001);
		    DI_Input=0x01;

		while((GPIO_DI_Pin & 0x00ff) != 0)
		{

			if(  GPIO_ReadInputDataBit(GPIOE,GPIO_DI_Pin))
			{
				ucSDiscInBuf[1]=	ucSDiscInBuf[1] | DI_Input ;
			}
			else
			{
				ucSDiscInBuf[1]=	ucSDiscInBuf[1] & (~DI_Input) ;
			}
			
				
		  DI_Input=	DI_Input <<1;
			GPIO_DI_Pin=GPIO_DI_Pin<<1;
		}
		
	//DI输入值传入寄存器	
	
			
  
		
		
		
		
		if((ucSCoilBuf[0]&0x1000)==0x1000)   // 启动自动模式
		{
		
			//调节算法 确定输出量大小
			
			if((usSRegInBuf[2]-usSRegHoldBuf[4]>2))//夏季制冷模式
			{
				
				ucSCoilBuf[0]=0x01ff;//空调全起
				usSRegHoldBuf[0]=3;
				usSRegHoldBuf[1]=3;
				if((ucSDiscInBuf[0]&0xe000)   | (ucSDiscInBuf[1]&0x00ff))
					{
							ucSCoilBuf[0]=ucSCoilBuf[0] | 0x0800;
					}
			
			}
						
			if((usSRegInBuf[2]-usSRegHoldBuf[4]<=2))//夏季制冷模式
			{
				
				ucSCoilBuf[0]=0x00c7;//空调开启一半
				usSRegHoldBuf[0]=3;
				usSRegHoldBuf[1]=3;
				if((ucSDiscInBuf[0]&0xe000)   | (ucSDiscInBuf[1]&0x00ff))
					{
							ucSCoilBuf[0]=ucSCoilBuf[0] | 0x0800;
					}
			
			}
			
  		if((usSRegInBuf[2]-usSRegHoldBuf[4]<=1))//夏季制冷模式
			{
				
				ucSCoilBuf[0]=0x0041;//空调、水泵 各开一台（变频控制）
				usSRegHoldBuf[0]=usSRegInBuf[2];
				usSRegHoldBuf[1]=usSRegInBuf[2];
				
				if((usSRegInBuf[3]-usSRegHoldBuf[5]<=1))
				{
						ucSCoilBuf[0]=0x0000;//空调、水泵 各开一台（变频控制）
					usSRegHoldBuf[0]=0;
					usSRegHoldBuf[2]=0;
					if((ucSDiscInBuf[0]&0xe000)   | (ucSDiscInBuf[1]&0x00ff))
					{
							ucSCoilBuf[0]=ucSCoilBuf[0] | 0x0800;
					}
				}
			
			}
	
			//调节算法 确定输出量大小
			
			if((usSRegHoldBuf[4]-usSRegInBuf[2]>2))//冬季加热模式
			{
						ucSCoilBuf[0]=0x01ff;//空调全起
						usSRegHoldBuf[0]=3;
						usSRegHoldBuf[1]=3;
						usSRegHoldBuf[2]=3;
						usSRegHoldBuf[3]=3;
				if((ucSDiscInBuf[0]&0xe000)   | (ucSDiscInBuf[1]&0x00ff))
					{
							ucSCoilBuf[0]=ucSCoilBuf[0] | 0x0800;
					}
			
			}
						
			if((usSRegHoldBuf[4]-usSRegInBuf[2]<=2))//冬季加热模式
			{
				ucSCoilBuf[0]=0x00c7;//空调开启一半
				usSRegHoldBuf[0]=3;
				usSRegHoldBuf[1]=3;
				usSRegHoldBuf[2]=3;
				usSRegHoldBuf[3]=3;
	 if((ucSDiscInBuf[0]&0xe000)   | (ucSDiscInBuf[1]&0x00ff))
					{
							ucSCoilBuf[0]=ucSCoilBuf[0] | 0x0800;
					}
			
			}
			
  		if((usSRegHoldBuf[4]-usSRegInBuf[2]<=1))//冬季加热模式
			{
				
				ucSCoilBuf[0]=0x0041;//空调、水泵 各开一台（变频控制）
				usSRegHoldBuf[0]=1;
				usSRegHoldBuf[1]=1;
				usSRegHoldBuf[2]=1;
				usSRegHoldBuf[3]=1;		


					if((ucSDiscInBuf[0]&0xe000)   | (ucSDiscInBuf[1]&0x00ff))
					{
							ucSCoilBuf[0]=ucSCoilBuf[0] | 0x0800;
					}
			}
			

			
			//调节算法 确定输出量大小结束
			
			
			
			
			
			
		voltage_out_1=(float)((float)usSRegHoldBuf[0]+(float)(usSRegHoldBuf[1]/10));
		voltage_out_2=(float)((float)usSRegHoldBuf[2]+((float)usSRegHoldBuf[3]/10));
	
			
		DAC_OUTPUT(voltage_out_1,voltage_out_2 );//模拟输出
			
		// Analog done


     DO_OUT();		//数字输出
			
			
		}//自动模式结束
		
		
		
		else //启动手动模式
		{
			unsigned int voltage_out_int_1,voltage_out_int_2;
			
		voltage_out_int_1=(float)((float)usSRegHoldBuf[0]+(float)(usSRegHoldBuf[1]/10));
		voltage_out_int_2=(float)((float)usSRegHoldBuf[2]+((float)usSRegHoldBuf[3]/10));
	
			
		DAC_OUTPUT(voltage_out_int_1,voltage_out_int_2 );//模拟输出
			
		 DO_OUT();//数字输出
			
		//手动模式结束	
		}
		
	}
}




//************************ Modbus从机轮训线程***************************
//函数定义: void thread_entry_ModbusSlavePoll(void* parameter)
//入口参数：无
//出口参数：无
//备    注：Editor：Armink   2013-08-02    Company: BXXJS
//******************************************************************
void thread_entry_ModbusSlavePoll(void* parameter)
{
	eMBInit(MB_RTU, 0x01, 1, 115200,  MB_PAR_EVEN);
	eMBEnable();
	while (1)
	{
		eMBPoll();
	}
}

//************************ Modbus主机轮训线程***************************
//函数定义: void thread_entry_ModbusMasterPoll(void* parameter)
//入口参数：无
//出口参数：无
//备    注：Editor：Armink   2013-08-28    Company: BXXJS
//******************************************************************
void thread_entry_ModbusMasterPoll(void* parameter)
{
	eMBMasterInit(MB_RTU, 2, 115200,  MB_PAR_EVEN);
	eMBMasterEnable();
	while (1)
	{
		eMBMasterPoll();
	}
}

//**********************系统初始化函数********************************
//函数定义: int rt_application_init(void)
//入口参数：无
//出口参数：无
//备    注：Editor：Liuqiuhu   2013-1-31   Company: BXXJS
//********************************************************************
int rt_application_init(void)
{
	rt_thread_init(&thread_SysMonitor, "SysMonitor", thread_entry_SysMonitor,
			RT_NULL, thread_SysMonitor_stack, sizeof(thread_SysMonitor_stack),
			thread_SysMonitor_Prio, 5);
	rt_thread_startup(&thread_SysMonitor);

	rt_thread_init(&thread_ModbusSlavePoll, "MBSlavePoll",
			thread_entry_ModbusSlavePoll, RT_NULL, thread_ModbusSlavePoll_stack,
			sizeof(thread_ModbusSlavePoll_stack), thread_ModbusSlavePoll_Prio,
			5);
	rt_thread_startup(&thread_ModbusSlavePoll);

	rt_thread_init(&thread_ModbusMasterPoll, "MBMasterPoll",
			thread_entry_ModbusMasterPoll, RT_NULL, thread_ModbusMasterPoll_stack,
			sizeof(thread_ModbusMasterPoll_stack), thread_ModbusMasterPoll_Prio,
			5);
	rt_thread_startup(&thread_ModbusMasterPoll);
	
	rt_thread_init(&thread_AIAODIDO, "AIAODIDO",
			thread_entry_AIAODIDO, RT_NULL, thread_AIAODIDOPoll_stack,
			sizeof(thread_AIAODIDOPoll_stack), thread_AIAODIDO_Prio,
			5);
	rt_thread_startup(&thread_AIAODIDO);

	return 0;
}

//**************************初始化RT-Thread函数*************************************
//函数定义: void rtthread_startup(void)
//入口参数：无
//出口参数：无
//备    注：Editor：Armink 2011-04-04    Company: BXXJS
//**********************************************************************************
void rtthread_startup(void)
{
	/* init board */
	rt_hw_board_init();

	/* show version */
	rt_show_version();

	/* init tick */
	rt_system_tick_init();

	/* init kernel object */
	rt_system_object_init();

	/* init timer system */
	rt_system_timer_init();

#ifdef RT_USING_HEAP
#ifdef __CC_ARM
	rt_system_heap_init((void*)&Image$$RW_IRAM1$$ZI$$Limit, (void*)STM32_SRAM_END);
#elif __ICCARM__
	rt_system_heap_init(__segment_end("HEAP"), (void*)STM32_SRAM_END);
#else
	/* init memory system */
	rt_system_heap_init((void*)&__bss_end, (void*)STM32_SRAM_END);
#endif
#endif

	/* init scheduler system */
	rt_system_scheduler_init();

	/* init all device */
	rt_device_init_all();

	/* init application */
	rt_application_init();

#ifdef RT_USING_FINSH
	/* init finsh */
	finsh_system_init();
	finsh_set_device("uart1");
#endif

	/* init timer thread */
	rt_system_timer_thread_init();

	/* init idle thread */
	rt_thread_idle_init();

	/* Add CPU usage to system */
	cpu_usage_init();

	/* start scheduler */
	rt_system_scheduler_start();

	/* never reach here */
	return;
}

