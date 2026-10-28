  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 8;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (Lab3_IMU_Encoder_comp_P)
    ;%
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_P.Joystick_gain_x
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_P.Joystick_gain_y
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_P.HILWriteAnalog_channels
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 48;
      section.data(48)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_OOTerminate
	  section.data(1).logicalSrcIdx = 3;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_OOExit
	  section.data(2).logicalSrcIdx = 4;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_OOStart
	  section.data(3).logicalSrcIdx = 5;
	  section.data(3).dtTransOffset = 2;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_OOEnter
	  section.data(4).logicalSrcIdx = 6;
	  section.data(4).dtTransOffset = 3;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOFinal
	  section.data(5).logicalSrcIdx = 7;
	  section.data(5).dtTransOffset = 4;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POFinal
	  section.data(6).logicalSrcIdx = 8;
	  section.data(6).dtTransOffset = 5;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AIHigh
	  section.data(7).logicalSrcIdx = 9;
	  section.data(7).dtTransOffset = 6;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AILow
	  section.data(8).logicalSrcIdx = 10;
	  section.data(8).dtTransOffset = 7;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOHigh
	  section.data(9).logicalSrcIdx = 11;
	  section.data(9).dtTransOffset = 8;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOLow
	  section.data(10).logicalSrcIdx = 12;
	  section.data(10).dtTransOffset = 9;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOInitial
	  section.data(11).logicalSrcIdx = 13;
	  section.data(11).dtTransOffset = 10;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOWatchdog
	  section.data(12).logicalSrcIdx = 14;
	  section.data(12).dtTransOffset = 11;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POFrequency
	  section.data(13).logicalSrcIdx = 15;
	  section.data(13).dtTransOffset = 12;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POLeading
	  section.data(14).logicalSrcIdx = 16;
	  section.data(14).dtTransOffset = 13;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POTrailing
	  section.data(15).logicalSrcIdx = 17;
	  section.data(15).dtTransOffset = 14;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POInitial
	  section.data(16).logicalSrcIdx = 18;
	  section.data(16).dtTransOffset = 15;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POWatchdog
	  section.data(17).logicalSrcIdx = 19;
	  section.data(17).dtTransOffset = 16;
	
	  ;% Lab3_IMU_Encoder_comp_P.TravelCounttorad_Gain
	  section.data(18).logicalSrcIdx = 20;
	  section.data(18).dtTransOffset = 17;
	
	  ;% Lab3_IMU_Encoder_comp_P.TravelTransferFcn_A
	  section.data(19).logicalSrcIdx = 21;
	  section.data(19).dtTransOffset = 18;
	
	  ;% Lab3_IMU_Encoder_comp_P.TravelTransferFcn_C
	  section.data(20).logicalSrcIdx = 22;
	  section.data(20).dtTransOffset = 19;
	
	  ;% Lab3_IMU_Encoder_comp_P.TravelTransferFcn_D
	  section.data(21).logicalSrcIdx = 23;
	  section.data(21).dtTransOffset = 20;
	
	  ;% Lab3_IMU_Encoder_comp_P.PitchCounttorad_Gain
	  section.data(22).logicalSrcIdx = 24;
	  section.data(22).dtTransOffset = 21;
	
	  ;% Lab3_IMU_Encoder_comp_P.PitchTransferFcn_A
	  section.data(23).logicalSrcIdx = 25;
	  section.data(23).dtTransOffset = 22;
	
	  ;% Lab3_IMU_Encoder_comp_P.PitchTransferFcn_C
	  section.data(24).logicalSrcIdx = 26;
	  section.data(24).dtTransOffset = 23;
	
	  ;% Lab3_IMU_Encoder_comp_P.PitchTransferFcn_D
	  section.data(25).logicalSrcIdx = 27;
	  section.data(25).dtTransOffset = 24;
	
	  ;% Lab3_IMU_Encoder_comp_P.ElevationCounttorad_Gain
	  section.data(26).logicalSrcIdx = 28;
	  section.data(26).dtTransOffset = 25;
	
	  ;% Lab3_IMU_Encoder_comp_P.ElevationTransferFcn_A
	  section.data(27).logicalSrcIdx = 29;
	  section.data(27).dtTransOffset = 26;
	
	  ;% Lab3_IMU_Encoder_comp_P.ElevationTransferFcn_C
	  section.data(28).logicalSrcIdx = 30;
	  section.data(28).dtTransOffset = 27;
	
	  ;% Lab3_IMU_Encoder_comp_P.ElevationTransferFcn_D
	  section.data(29).logicalSrcIdx = 31;
	  section.data(29).dtTransOffset = 28;
	
	  ;% Lab3_IMU_Encoder_comp_P.Constant_Value
	  section.data(30).logicalSrcIdx = 32;
	  section.data(30).dtTransOffset = 29;
	
	  ;% Lab3_IMU_Encoder_comp_P.Constant1_Value
	  section.data(31).logicalSrcIdx = 33;
	  section.data(31).dtTransOffset = 30;
	
	  ;% Lab3_IMU_Encoder_comp_P.Memory_InitialCondition
	  section.data(32).logicalSrcIdx = 34;
	  section.data(32).dtTransOffset = 31;
	
	  ;% Lab3_IMU_Encoder_comp_P.Gain1_Gain
	  section.data(33).logicalSrcIdx = 35;
	  section.data(33).dtTransOffset = 41;
	
	  ;% Lab3_IMU_Encoder_comp_P.Gain2_Gain
	  section.data(34).logicalSrcIdx = 36;
	  section.data(34).dtTransOffset = 50;
	
	  ;% Lab3_IMU_Encoder_comp_P.Backgain_Gain
	  section.data(35).logicalSrcIdx = 37;
	  section.data(35).dtTransOffset = 59;
	
	  ;% Lab3_IMU_Encoder_comp_P.Frontgain_Gain
	  section.data(36).logicalSrcIdx = 38;
	  section.data(36).dtTransOffset = 60;
	
	  ;% Lab3_IMU_Encoder_comp_P.FrontmotorSaturation_UpperSat
	  section.data(37).logicalSrcIdx = 39;
	  section.data(37).dtTransOffset = 61;
	
	  ;% Lab3_IMU_Encoder_comp_P.FrontmotorSaturation_LowerSat
	  section.data(38).logicalSrcIdx = 40;
	  section.data(38).dtTransOffset = 62;
	
	  ;% Lab3_IMU_Encoder_comp_P.BackmotorSaturation_UpperSat
	  section.data(39).logicalSrcIdx = 41;
	  section.data(39).dtTransOffset = 63;
	
	  ;% Lab3_IMU_Encoder_comp_P.BackmotorSaturation_LowerSat
	  section.data(40).logicalSrcIdx = 42;
	  section.data(40).dtTransOffset = 64;
	
	  ;% Lab3_IMU_Encoder_comp_P.RateTransitionx_InitialConditio
	  section.data(41).logicalSrcIdx = 43;
	  section.data(41).dtTransOffset = 65;
	
	  ;% Lab3_IMU_Encoder_comp_P.DeadZonex_Start
	  section.data(42).logicalSrcIdx = 44;
	  section.data(42).dtTransOffset = 66;
	
	  ;% Lab3_IMU_Encoder_comp_P.DeadZonex_End
	  section.data(43).logicalSrcIdx = 45;
	  section.data(43).dtTransOffset = 67;
	
	  ;% Lab3_IMU_Encoder_comp_P.Gainx_Gain
	  section.data(44).logicalSrcIdx = 46;
	  section.data(44).dtTransOffset = 68;
	
	  ;% Lab3_IMU_Encoder_comp_P.RateTransitiony_InitialConditio
	  section.data(45).logicalSrcIdx = 47;
	  section.data(45).dtTransOffset = 69;
	
	  ;% Lab3_IMU_Encoder_comp_P.DeadZoney_Start
	  section.data(46).logicalSrcIdx = 48;
	  section.data(46).dtTransOffset = 70;
	
	  ;% Lab3_IMU_Encoder_comp_P.DeadZoney_End
	  section.data(47).logicalSrcIdx = 49;
	  section.data(47).dtTransOffset = 71;
	
	  ;% Lab3_IMU_Encoder_comp_P.Gainy_Gain
	  section.data(48).logicalSrcIdx = 50;
	  section.data(48).dtTransOffset = 72;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 51;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOWatchdog
	  section.data(2).logicalSrcIdx = 52;
	  section.data(2).dtTransOffset = 3;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_EIInitial
	  section.data(3).logicalSrcIdx = 53;
	  section.data(3).dtTransOffset = 4;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POModes
	  section.data(4).logicalSrcIdx = 54;
	  section.data(4).dtTransOffset = 5;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POConfiguration
	  section.data(5).logicalSrcIdx = 55;
	  section.data(5).dtTransOffset = 6;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POAlignment
	  section.data(6).logicalSrcIdx = 56;
	  section.data(6).dtTransOffset = 7;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POPolarity
	  section.data(7).logicalSrcIdx = 57;
	  section.data(7).dtTransOffset = 8;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILReadEncoderTimebase_Clock
	  section.data(8).logicalSrcIdx = 58;
	  section.data(8).dtTransOffset = 9;
	
	  ;% Lab3_IMU_Encoder_comp_P.StreamCall1_SendBufferSize
	  section.data(9).logicalSrcIdx = 59;
	  section.data(9).dtTransOffset = 10;
	
	  ;% Lab3_IMU_Encoder_comp_P.StreamCall1_ReceiveBufferSize
	  section.data(10).logicalSrcIdx = 60;
	  section.data(10).dtTransOffset = 11;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 61;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 62;
	  section.data(2).dtTransOffset = 8;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_EIChannels
	  section.data(3).logicalSrcIdx = 63;
	  section.data(3).dtTransOffset = 16;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_EIQuadrature
	  section.data(4).logicalSrcIdx = 64;
	  section.data(4).dtTransOffset = 24;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POChannels
	  section.data(5).logicalSrcIdx = 65;
	  section.data(5).dtTransOffset = 25;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILReadEncoderTimebase_Channels
	  section.data(6).logicalSrcIdx = 66;
	  section.data(6).dtTransOffset = 33;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILReadEncoderTimebase_SamplesI
	  section.data(7).logicalSrcIdx = 67;
	  section.data(7).dtTransOffset = 36;
	
	  ;% Lab3_IMU_Encoder_comp_P.StreamFormattedWrite_MaxUnits
	  section.data(8).logicalSrcIdx = 68;
	  section.data(8).dtTransOffset = 37;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_P.GameController_BufferSize
	  section.data(1).logicalSrcIdx = 69;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 41;
      section.data(41)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_Active
	  section.data(1).logicalSrcIdx = 70;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOTerminate
	  section.data(2).logicalSrcIdx = 71;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOExit
	  section.data(3).logicalSrcIdx = 72;
	  section.data(3).dtTransOffset = 2;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOTerminate
	  section.data(4).logicalSrcIdx = 73;
	  section.data(4).dtTransOffset = 3;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOExit
	  section.data(5).logicalSrcIdx = 74;
	  section.data(5).dtTransOffset = 4;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POTerminate
	  section.data(6).logicalSrcIdx = 75;
	  section.data(6).dtTransOffset = 5;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POExit
	  section.data(7).logicalSrcIdx = 76;
	  section.data(7).dtTransOffset = 6;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_CKPStart
	  section.data(8).logicalSrcIdx = 77;
	  section.data(8).dtTransOffset = 7;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_CKPEnter
	  section.data(9).logicalSrcIdx = 78;
	  section.data(9).dtTransOffset = 8;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_CKStart
	  section.data(10).logicalSrcIdx = 79;
	  section.data(10).dtTransOffset = 9;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_CKEnter
	  section.data(11).logicalSrcIdx = 80;
	  section.data(11).dtTransOffset = 10;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AIPStart
	  section.data(12).logicalSrcIdx = 81;
	  section.data(12).dtTransOffset = 11;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AIPEnter
	  section.data(13).logicalSrcIdx = 82;
	  section.data(13).dtTransOffset = 12;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOPStart
	  section.data(14).logicalSrcIdx = 83;
	  section.data(14).dtTransOffset = 13;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOPEnter
	  section.data(15).logicalSrcIdx = 84;
	  section.data(15).dtTransOffset = 14;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOStart
	  section.data(16).logicalSrcIdx = 85;
	  section.data(16).dtTransOffset = 15;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOEnter
	  section.data(17).logicalSrcIdx = 86;
	  section.data(17).dtTransOffset = 16;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_AOReset
	  section.data(18).logicalSrcIdx = 87;
	  section.data(18).dtTransOffset = 17;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOPStart
	  section.data(19).logicalSrcIdx = 88;
	  section.data(19).dtTransOffset = 18;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOPEnter
	  section.data(20).logicalSrcIdx = 89;
	  section.data(20).dtTransOffset = 19;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOStart
	  section.data(21).logicalSrcIdx = 90;
	  section.data(21).dtTransOffset = 20;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOEnter
	  section.data(22).logicalSrcIdx = 91;
	  section.data(22).dtTransOffset = 21;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOReset
	  section.data(23).logicalSrcIdx = 92;
	  section.data(23).dtTransOffset = 22;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_EIPStart
	  section.data(24).logicalSrcIdx = 93;
	  section.data(24).dtTransOffset = 23;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_EIPEnter
	  section.data(25).logicalSrcIdx = 94;
	  section.data(25).dtTransOffset = 24;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_EIStart
	  section.data(26).logicalSrcIdx = 95;
	  section.data(26).dtTransOffset = 25;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_EIEnter
	  section.data(27).logicalSrcIdx = 96;
	  section.data(27).dtTransOffset = 26;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POPStart
	  section.data(28).logicalSrcIdx = 97;
	  section.data(28).dtTransOffset = 27;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POPEnter
	  section.data(29).logicalSrcIdx = 98;
	  section.data(29).dtTransOffset = 28;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POStart
	  section.data(30).logicalSrcIdx = 99;
	  section.data(30).dtTransOffset = 29;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POEnter
	  section.data(31).logicalSrcIdx = 100;
	  section.data(31).dtTransOffset = 30;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_POReset
	  section.data(32).logicalSrcIdx = 101;
	  section.data(32).dtTransOffset = 31;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_OOReset
	  section.data(33).logicalSrcIdx = 102;
	  section.data(33).dtTransOffset = 32;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOFinal
	  section.data(34).logicalSrcIdx = 103;
	  section.data(34).dtTransOffset = 33;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILInitialize_DOInitial
	  section.data(35).logicalSrcIdx = 104;
	  section.data(35).dtTransOffset = 34;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILReadEncoderTimebase_Active
	  section.data(36).logicalSrcIdx = 105;
	  section.data(36).dtTransOffset = 35;
	
	  ;% Lab3_IMU_Encoder_comp_P.StreamCall1_NonBlocking
	  section.data(37).logicalSrcIdx = 106;
	  section.data(37).dtTransOffset = 36;
	
	  ;% Lab3_IMU_Encoder_comp_P.StreamCall1_Active
	  section.data(38).logicalSrcIdx = 107;
	  section.data(38).dtTransOffset = 37;
	
	  ;% Lab3_IMU_Encoder_comp_P.HILWriteAnalog_Active
	  section.data(39).logicalSrcIdx = 108;
	  section.data(39).dtTransOffset = 38;
	
	  ;% Lab3_IMU_Encoder_comp_P.GameController_AutoCenter
	  section.data(40).logicalSrcIdx = 109;
	  section.data(40).dtTransOffset = 39;
	
	  ;% Lab3_IMU_Encoder_comp_P.GameController_Enabled
	  section.data(41).logicalSrcIdx = 110;
	  section.data(41).dtTransOffset = 40;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_P.HILReadEncoderTimebase_Overflow
	  section.data(1).logicalSrcIdx = 111;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_P.StringConstant_Value
	  section.data(2).logicalSrcIdx = 112;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_Encoder_comp_P.StreamCall1_URI
	  section.data(3).logicalSrcIdx = 113;
	  section.data(3).dtTransOffset = 256;
	
	  ;% Lab3_IMU_Encoder_comp_P.StreamCall1_Endian
	  section.data(4).logicalSrcIdx = 114;
	  section.data(4).dtTransOffset = 257;
	
	  ;% Lab3_IMU_Encoder_comp_P.GameController_ControllerNumber
	  section.data(5).logicalSrcIdx = 115;
	  section.data(5).dtTransOffset = 258;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(8) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (Lab3_IMU_Encoder_comp_B)
    ;%
      section.nData     = 16;
      section.data(16)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_B.TravelCounttorad
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_B.TravelTransferFcn
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_Encoder_comp_B.PitchCounttorad
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% Lab3_IMU_Encoder_comp_B.PitchTransferFcn
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% Lab3_IMU_Encoder_comp_B.ElevationCounttorad
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% Lab3_IMU_Encoder_comp_B.ElevationTransferFcn
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% Lab3_IMU_Encoder_comp_B.Switch
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% Lab3_IMU_Encoder_comp_B.Gain1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 16;
	
	  ;% Lab3_IMU_Encoder_comp_B.Gain2
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 19;
	
	  ;% Lab3_IMU_Encoder_comp_B.DataTypeConversion
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 22;
	
	  ;% Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 23;
	
	  ;% Lab3_IMU_Encoder_comp_B.RateTransitionx
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 44;
	
	  ;% Lab3_IMU_Encoder_comp_B.Joystick_gain_x
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 45;
	
	  ;% Lab3_IMU_Encoder_comp_B.RateTransitiony
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 46;
	
	  ;% Lab3_IMU_Encoder_comp_B.Joystick_gain_y
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 47;
	
	  ;% Lab3_IMU_Encoder_comp_B.euler_rates
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 48;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_B.StreamCall1_o2
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 10;
    sectIdxOffset = 2;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (Lab3_IMU_Encoder_comp_DW)
    ;%
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_AIMinimums
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_AIMaximums
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 8;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_AOMinimums
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 16;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_AOMaximums
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 24;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_AOVoltages
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 32;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_FilterFrequency
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 40;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedFreqs
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 48;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 56;
	
	  ;% Lab3_IMU_Encoder_comp_DW.Memory_PreviousInput
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 64;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILWriteAnalog_Buffer
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 74;
	
	  ;% Lab3_IMU_Encoder_comp_DW.RateTransitionx_Buffer0
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 76;
	
	  ;% Lab3_IMU_Encoder_comp_DW.RateTransitiony_Buffer0
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 77;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.GameController_Controller
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.HILReadEncoderTimebase_Task
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 17;
      section.data(17)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.Scope_PWORK.LoggedData
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_DW.ToFile_PWORK.FilePtr
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_Encoder_comp_DW.e_imuve_PWORK.LoggedData
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 2;
	
	  ;% Lab3_IMU_Encoder_comp_DW.edot_imuvedot_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 19;
	  section.data(4).dtTransOffset = 4;
	
	  ;% Lab3_IMU_Encoder_comp_DW.lambdadot_imuvlambdadot_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 20;
	  section.data(5).dtTransOffset = 6;
	
	  ;% Lab3_IMU_Encoder_comp_DW.p_imuvp_PWORK.LoggedData
	  section.data(6).logicalSrcIdx = 21;
	  section.data(6).dtTransOffset = 8;
	
	  ;% Lab3_IMU_Encoder_comp_DW.pdot_imuvpdot_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 22;
	  section.data(7).dtTransOffset = 10;
	
	  ;% Lab3_IMU_Encoder_comp_DW.ElevationScoperads_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 23;
	  section.data(8).dtTransOffset = 12;
	
	  ;% Lab3_IMU_Encoder_comp_DW.ElevationScoperad_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 24;
	  section.data(9).dtTransOffset = 13;
	
	  ;% Lab3_IMU_Encoder_comp_DW.PitchScoperad_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 25;
	  section.data(10).dtTransOffset = 14;
	
	  ;% Lab3_IMU_Encoder_comp_DW.PtichrateScoperads_PWORK.LoggedData
	  section.data(11).logicalSrcIdx = 26;
	  section.data(11).dtTransOffset = 15;
	
	  ;% Lab3_IMU_Encoder_comp_DW.TravelrateScoperads_PWORK.LoggedData
	  section.data(12).logicalSrcIdx = 27;
	  section.data(12).dtTransOffset = 16;
	
	  ;% Lab3_IMU_Encoder_comp_DW.TravelScoperad_PWORK.LoggedData
	  section.data(13).logicalSrcIdx = 28;
	  section.data(13).dtTransOffset = 17;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILWriteAnalog_PWORK
	  section.data(14).logicalSrcIdx = 29;
	  section.data(14).dtTransOffset = 18;
	
	  ;% Lab3_IMU_Encoder_comp_DW.Connected_PWORK.LoggedData
	  section.data(15).logicalSrcIdx = 30;
	  section.data(15).dtTransOffset = 19;
	
	  ;% Lab3_IMU_Encoder_comp_DW.XScope_PWORK.LoggedData
	  section.data(16).logicalSrcIdx = 31;
	  section.data(16).dtTransOffset = 20;
	
	  ;% Lab3_IMU_Encoder_comp_DW.YScope_PWORK.LoggedData
	  section.data(17).logicalSrcIdx = 32;
	  section.data(17).dtTransOffset = 21;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_ClockModes
	  section.data(1).logicalSrcIdx = 33;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_QuadratureModes
	  section.data(2).logicalSrcIdx = 34;
	  section.data(2).dtTransOffset = 3;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_InitialEICounts
	  section.data(3).logicalSrcIdx = 35;
	  section.data(3).dtTransOffset = 11;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_POModeValues
	  section.data(4).logicalSrcIdx = 36;
	  section.data(4).dtTransOffset = 19;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_POAlignValues
	  section.data(5).logicalSrcIdx = 37;
	  section.data(5).dtTransOffset = 27;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_POPolarityVals
	  section.data(6).logicalSrcIdx = 38;
	  section.data(6).dtTransOffset = 35;
	
	  ;% Lab3_IMU_Encoder_comp_DW.HILReadEncoderTimebase_Buffer
	  section.data(7).logicalSrcIdx = 39;
	  section.data(7).dtTransOffset = 43;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedChans
	  section.data(1).logicalSrcIdx = 40;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.ToFile_IWORK.Count
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_Encoder_comp_DW.StreamCall1_State
	  section.data(1).logicalSrcIdx = 42;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(10) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 241584936;
  targMap.checksum1 = 2377646479;
  targMap.checksum2 = 1291162109;
  targMap.checksum3 = 2421960728;

