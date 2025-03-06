
/* ========================================================================= */
/* The information contained herein is the exclusive property of             */
/* Sunplus Technology Co. And shall not be distributed, reproduced,          */
/* or disclosed in whole in part without prior written permission.           */
/*             (C) COPYRIGHT 2004 SUNPLUS TECHNOLOGY CO.                     */
/*                    ALL RIGHTS RESERVED                                    */
/* The entire notice above must be reproduced on all authorized copies.      */
/* ========================================================================= */
/* 																			 */
/* ========================================================================= */
/* Project Name  : SPMC75F2413A_Digital_PID	            					 */
/* File Name     : DigitalPID.c												 */
/* Description   : Digital PID Speed Controller for Motor Drive Applications */
/*                 Using SPMC75F2413A                              		     */
/* Processor     : SPMC75F2413A											     */
/* Tools	     : u'nSP IDE tools v1.18.1A or later version				 */
/* ========================================================================= */
/* Revision																	 */
/* ========================================================================= */
/* Version       :  1.00   													 */
/* Date			 :	2005.9.1												 */
/* Modified by   :	更换正规的文件头和最新的头文件							 */
/* Description	 :												    		 */
/* ========================================================================= */

typedef struct PID
{
	float  SetPoint; 			//  设定目标 Desired Value
	long SumError;			//	误差累计 
		
	float  Proportion;     //  比例常数 Proportional Const
	float  Integral;       //  积分常数 Integral Const
	float  Derivative;     //  微分常数 Derivative Const

	float LastError;         	//  Error[-1]
	float PrevError;          //  Error[-2]

} PID_structure;

static PID_structure	 sPID;
static PID_structure	 *sptr = &sPID;
//============================================================= 
// ----Function: IncPIDInit() 
// ------Syntax: void IncPIDInit(void);
// -Description: Initialization PID parameter.
// -------Notes: 
// --parameters: none
// -----returns: none
//=============================================================
void PIDInit(PID_structure *My_PID)
{	
    My_PID->LastError  = 0;			//Error[-1]
    My_PID->PrevError  = 0;			//Error[-2]
	  My_PID->Proportion = 0;			//比例常数 Proportional Const
    My_PID->Integral   = 0;			//积分常数 Integral Const
    My_PID->Derivative = 0;			//微分常数 Derivative Const
    My_PID->SetPoint   = 0;
	  My_PID->SumError   = 0;
}

//============================================================= 
// ----Function: IncPIDSetPoint() 
// ------Syntax: void IncPIDSetPoint(unsigned int setpoint);
// -Description: Set PID Desired Value
// -------Notes: 
// --parameters: Desired Value
// -----returns: none
//=============================================================
void PIDSetPoint(float setpoint)
{	sptr->SetPoint = setpoint;	}

int PIDGetSetpoint(void)
{	return(sptr->SetPoint);	}
//============================================================= 
// ----Function: IncPIDKp() 
// ------Syntax: void IncPIDKp(double dKp);
// -Description: Set PID Proportion coefficient
// -------Notes: 
// --parameters: Proportion Const
// -----returns: none
//=============================================================
void PIDSetKp(float dKpp)
{	sptr->Proportion = dKpp;	}
//===================================//
// Get Proportion
//===================================//
double PIDGetKp(void)
{	return(sptr->Proportion);	}
//============================================================= 
// ----Function: IncPIDKi() 
// ------Syntax: void IncPIDKi(double dKi);
// -Description: Set PID Integral coefficient
// -------Notes: 
// --parameters: Integral Const
// -----returns: none
//=============================================================
void PIDSetKi(float dKii)
{	sptr->Integral = dKii;	}
//===================================//
// Get Integral
//===================================//
double PIDGetKi(void)
{	return(sptr->Integral);	}
//============================================================= 
// ----Function: IncPIDKd() 
// ------Syntax: void IncPIDKd(double dKd);
// -Description: Set PID Derivative coefficient
// -------Notes: 
// --parameters: Derivative Const
// -----returns: none
//=============================================================
void PIDSetKd(float dKdd)
{	sptr->Derivative = dKdd;	}
//===================================//
// Get Derivative
//===================================//
double PIDGetKd(void)
{	return(sptr->Derivative);	}
//============================================================= 
// ----Function: IncPIDCalc() 
// ------Syntax: int IncPIDCalc(unsigned int NextPoint);
// -Description: Increment Digital PID calculate
// -------Notes: Basic Increment Digital PID
// --parameters: Next Point
// -----returns: increase controls parameter
//=============================================================
float IncPIDCalc(PID_structure *Process_PID_Structure,float NextPoint)
{
	register int iError, iIncpid;

	iError = Process_PID_Structure->SetPoint - NextPoint;

	iIncpid = Process_PID_Structure->Proportion * iError				//E[0]
            - Process_PID_Structure->Integral   * Process_PID_Structure->LastError	//E[-1]
            + Process_PID_Structure->Derivative * Process_PID_Structure->PrevError;	//E[-2]

	Process_PID_Structure->PrevError = Process_PID_Structure->LastError;
	Process_PID_Structure->LastError = iError;

	return(iIncpid);
}

//============================================================= 
// ----Function: LocPIDCalc() 
// ------Syntax: unsigned int locPIDCalc(unsigned int NextPoint);
// -Description: Location Digital PID calculate
// -------Notes: Basic Location Digital PID
// --parameters: Next Point
// -----returns: Location controls parameter
//=============================================================
float LocPIDCalc(PID_structure *Process_PID_Structure,float NextPoint)
{
    register float  iError,dError;
	
	iError = Process_PID_Structure->SetPoint - NextPoint;      	// 偏差
	
	Process_PID_Structure->SumError += iError;					// 积分
	
	dError = iError - Process_PID_Structure->LastError; 			// 当前微分
	
	Process_PID_Structure->LastError = iError;

	return(Process_PID_Structure->Proportion * iError           	// 比例项
           + Process_PID_Structure->Integral * Process_PID_Structure->SumError 	// 积分项
           + Process_PID_Structure->Derivative * dError);
}

//=============================================//
//	*END*
//=============================================//

