Board use PT2272-M4

**********************************************************************************************
When click A the value clickAState++;  using with TB6560 , MicroStep , DM542 , DM860 , A4988
Using pin : PUL- 8;
Using pin :	DIR- 9;

	if(clickAState == 0 ){
		StepMotor clockwise;
	}else if(clickAState == 1){
		StepMotor counter-clockwise;
	}
	
**********************************************************************************************	
When click B the value clickBState++; using with ULN2003
Using pin 2: IN1;
Using pin 3: IN2;
Using pin 4: IN3;
Using pin 5: IN4;

	if(clickBState==0){
		StepMotor clockwise;
	}else if(clickBState==1){
		StepMotor counter-clockwise;
	}

**********************************************************************************************
	
When click C ; Using with BTS7960 43A

- > RF_D2 = 5V+ => RPWM = 5V+ => Moter clockwise;

When click C ; Using with BTS7960 43A

- > RF_D3 = 5V+ => LPWM = 5V+ => Moter counter-clockwise;

**********************************************************************************************

Status StepMotor

If(StepMotor == clockwise){
	LedStatus1 blink with 100ms !
	LedStatus2 turn off !
}else if (StepMotor == counter-clockwise){
	LedStatus1 turn off!
	LedStatus2 blink with 100ms !
}





	

		

	