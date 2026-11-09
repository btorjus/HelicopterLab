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
    ;% Auto data (Lab3_IMU_LQRI_P)
    ;%
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_P.A_obs
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_P.B_obs
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 25;
	
	  ;% Lab3_IMU_LQRI_P.F
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 35;
	
	  ;% Lab3_IMU_LQRI_P.Joystick_gain_x
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 39;
	
	  ;% Lab3_IMU_LQRI_P.Joystick_gain_y
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 40;
	
	  ;% Lab3_IMU_LQRI_P.K
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 41;
	
	  ;% Lab3_IMU_LQRI_P.L_obs
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 51;
	
	  ;% Lab3_IMU_LQRI_P.Vs0
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 76;
	
	  ;% Lab3_IMU_LQRI_P.e_offset
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 77;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_P.HILWriteAnalog_channels
	  section.data(1).logicalSrcIdx = 9;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 53;
      section.data(53)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_P.Constant_Value
	  section.data(1).logicalSrcIdx = 10;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_P.Constant1_Value
	  section.data(2).logicalSrcIdx = 11;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_OOTerminate
	  section.data(3).logicalSrcIdx = 12;
	  section.data(3).dtTransOffset = 2;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_OOExit
	  section.data(4).logicalSrcIdx = 13;
	  section.data(4).dtTransOffset = 3;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_OOStart
	  section.data(5).logicalSrcIdx = 14;
	  section.data(5).dtTransOffset = 4;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_OOEnter
	  section.data(6).logicalSrcIdx = 15;
	  section.data(6).dtTransOffset = 5;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOFinal
	  section.data(7).logicalSrcIdx = 16;
	  section.data(7).dtTransOffset = 6;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POFinal
	  section.data(8).logicalSrcIdx = 17;
	  section.data(8).dtTransOffset = 7;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AIHigh
	  section.data(9).logicalSrcIdx = 18;
	  section.data(9).dtTransOffset = 8;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AILow
	  section.data(10).logicalSrcIdx = 19;
	  section.data(10).dtTransOffset = 9;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOHigh
	  section.data(11).logicalSrcIdx = 20;
	  section.data(11).dtTransOffset = 10;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOLow
	  section.data(12).logicalSrcIdx = 21;
	  section.data(12).dtTransOffset = 11;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOInitial
	  section.data(13).logicalSrcIdx = 22;
	  section.data(13).dtTransOffset = 12;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOWatchdog
	  section.data(14).logicalSrcIdx = 23;
	  section.data(14).dtTransOffset = 13;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POFrequency
	  section.data(15).logicalSrcIdx = 24;
	  section.data(15).dtTransOffset = 14;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POLeading
	  section.data(16).logicalSrcIdx = 25;
	  section.data(16).dtTransOffset = 15;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POTrailing
	  section.data(17).logicalSrcIdx = 26;
	  section.data(17).dtTransOffset = 16;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POInitial
	  section.data(18).logicalSrcIdx = 27;
	  section.data(18).dtTransOffset = 17;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POWatchdog
	  section.data(19).logicalSrcIdx = 28;
	  section.data(19).dtTransOffset = 18;
	
	  ;% Lab3_IMU_LQRI_P.TravelCounttorad_Gain
	  section.data(20).logicalSrcIdx = 29;
	  section.data(20).dtTransOffset = 19;
	
	  ;% Lab3_IMU_LQRI_P.TravelTransferFcn_A
	  section.data(21).logicalSrcIdx = 30;
	  section.data(21).dtTransOffset = 20;
	
	  ;% Lab3_IMU_LQRI_P.TravelTransferFcn_C
	  section.data(22).logicalSrcIdx = 31;
	  section.data(22).dtTransOffset = 21;
	
	  ;% Lab3_IMU_LQRI_P.TravelTransferFcn_D
	  section.data(23).logicalSrcIdx = 32;
	  section.data(23).dtTransOffset = 22;
	
	  ;% Lab3_IMU_LQRI_P.PitchCounttorad_Gain
	  section.data(24).logicalSrcIdx = 33;
	  section.data(24).dtTransOffset = 23;
	
	  ;% Lab3_IMU_LQRI_P.PitchTransferFcn_A
	  section.data(25).logicalSrcIdx = 34;
	  section.data(25).dtTransOffset = 24;
	
	  ;% Lab3_IMU_LQRI_P.PitchTransferFcn_C
	  section.data(26).logicalSrcIdx = 35;
	  section.data(26).dtTransOffset = 25;
	
	  ;% Lab3_IMU_LQRI_P.PitchTransferFcn_D
	  section.data(27).logicalSrcIdx = 36;
	  section.data(27).dtTransOffset = 26;
	
	  ;% Lab3_IMU_LQRI_P.ElevationCounttorad_Gain
	  section.data(28).logicalSrcIdx = 37;
	  section.data(28).dtTransOffset = 27;
	
	  ;% Lab3_IMU_LQRI_P.ElevationTransferFcn_A
	  section.data(29).logicalSrcIdx = 38;
	  section.data(29).dtTransOffset = 28;
	
	  ;% Lab3_IMU_LQRI_P.ElevationTransferFcn_C
	  section.data(30).logicalSrcIdx = 39;
	  section.data(30).dtTransOffset = 29;
	
	  ;% Lab3_IMU_LQRI_P.ElevationTransferFcn_D
	  section.data(31).logicalSrcIdx = 40;
	  section.data(31).dtTransOffset = 30;
	
	  ;% Lab3_IMU_LQRI_P.Constant_Value_p
	  section.data(32).logicalSrcIdx = 41;
	  section.data(32).dtTransOffset = 31;
	
	  ;% Lab3_IMU_LQRI_P.Constant1_Value_i
	  section.data(33).logicalSrcIdx = 42;
	  section.data(33).dtTransOffset = 32;
	
	  ;% Lab3_IMU_LQRI_P.Memory_InitialCondition
	  section.data(34).logicalSrcIdx = 43;
	  section.data(34).dtTransOffset = 33;
	
	  ;% Lab3_IMU_LQRI_P.Gain1_Gain
	  section.data(35).logicalSrcIdx = 44;
	  section.data(35).dtTransOffset = 43;
	
	  ;% Lab3_IMU_LQRI_P.Gain2_Gain
	  section.data(36).logicalSrcIdx = 45;
	  section.data(36).dtTransOffset = 52;
	
	  ;% Lab3_IMU_LQRI_P.Integrator_IC
	  section.data(37).logicalSrcIdx = 46;
	  section.data(37).dtTransOffset = 61;
	
	  ;% Lab3_IMU_LQRI_P.RateTransitionx_InitialConditio
	  section.data(38).logicalSrcIdx = 47;
	  section.data(38).dtTransOffset = 62;
	
	  ;% Lab3_IMU_LQRI_P.DeadZonex_Start
	  section.data(39).logicalSrcIdx = 48;
	  section.data(39).dtTransOffset = 63;
	
	  ;% Lab3_IMU_LQRI_P.DeadZonex_End
	  section.data(40).logicalSrcIdx = 49;
	  section.data(40).dtTransOffset = 64;
	
	  ;% Lab3_IMU_LQRI_P.Gainx_Gain
	  section.data(41).logicalSrcIdx = 50;
	  section.data(41).dtTransOffset = 65;
	
	  ;% Lab3_IMU_LQRI_P.RateTransitiony_InitialConditio
	  section.data(42).logicalSrcIdx = 51;
	  section.data(42).dtTransOffset = 66;
	
	  ;% Lab3_IMU_LQRI_P.DeadZoney_Start
	  section.data(43).logicalSrcIdx = 52;
	  section.data(43).dtTransOffset = 67;
	
	  ;% Lab3_IMU_LQRI_P.DeadZoney_End
	  section.data(44).logicalSrcIdx = 53;
	  section.data(44).dtTransOffset = 68;
	
	  ;% Lab3_IMU_LQRI_P.Gainy_Gain
	  section.data(45).logicalSrcIdx = 54;
	  section.data(45).dtTransOffset = 69;
	
	  ;% Lab3_IMU_LQRI_P.Integrator_IC_c
	  section.data(46).logicalSrcIdx = 55;
	  section.data(46).dtTransOffset = 70;
	
	  ;% Lab3_IMU_LQRI_P.Backgain_Gain
	  section.data(47).logicalSrcIdx = 56;
	  section.data(47).dtTransOffset = 71;
	
	  ;% Lab3_IMU_LQRI_P.Frontgain_Gain
	  section.data(48).logicalSrcIdx = 57;
	  section.data(48).dtTransOffset = 72;
	
	  ;% Lab3_IMU_LQRI_P.FrontmotorSaturation_UpperSat
	  section.data(49).logicalSrcIdx = 58;
	  section.data(49).dtTransOffset = 73;
	
	  ;% Lab3_IMU_LQRI_P.FrontmotorSaturation_LowerSat
	  section.data(50).logicalSrcIdx = 59;
	  section.data(50).dtTransOffset = 74;
	
	  ;% Lab3_IMU_LQRI_P.BackmotorSaturation_UpperSat
	  section.data(51).logicalSrcIdx = 60;
	  section.data(51).dtTransOffset = 75;
	
	  ;% Lab3_IMU_LQRI_P.BackmotorSaturation_LowerSat
	  section.data(52).logicalSrcIdx = 61;
	  section.data(52).dtTransOffset = 76;
	
	  ;% Lab3_IMU_LQRI_P.C_obs_Gain
	  section.data(53).logicalSrcIdx = 62;
	  section.data(53).dtTransOffset = 77;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOWatchdog
	  section.data(2).logicalSrcIdx = 64;
	  section.data(2).dtTransOffset = 3;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_EIInitial
	  section.data(3).logicalSrcIdx = 65;
	  section.data(3).dtTransOffset = 4;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POModes
	  section.data(4).logicalSrcIdx = 66;
	  section.data(4).dtTransOffset = 5;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POConfiguration
	  section.data(5).logicalSrcIdx = 67;
	  section.data(5).dtTransOffset = 6;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POAlignment
	  section.data(6).logicalSrcIdx = 68;
	  section.data(6).dtTransOffset = 7;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POPolarity
	  section.data(7).logicalSrcIdx = 69;
	  section.data(7).dtTransOffset = 8;
	
	  ;% Lab3_IMU_LQRI_P.HILReadEncoderTimebase_Clock
	  section.data(8).logicalSrcIdx = 70;
	  section.data(8).dtTransOffset = 9;
	
	  ;% Lab3_IMU_LQRI_P.StreamCall1_SendBufferSize
	  section.data(9).logicalSrcIdx = 71;
	  section.data(9).dtTransOffset = 10;
	
	  ;% Lab3_IMU_LQRI_P.StreamCall1_ReceiveBufferSize
	  section.data(10).logicalSrcIdx = 72;
	  section.data(10).dtTransOffset = 11;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 74;
	  section.data(2).dtTransOffset = 8;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_EIChannels
	  section.data(3).logicalSrcIdx = 75;
	  section.data(3).dtTransOffset = 16;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_EIQuadrature
	  section.data(4).logicalSrcIdx = 76;
	  section.data(4).dtTransOffset = 24;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POChannels
	  section.data(5).logicalSrcIdx = 77;
	  section.data(5).dtTransOffset = 25;
	
	  ;% Lab3_IMU_LQRI_P.HILReadEncoderTimebase_Channels
	  section.data(6).logicalSrcIdx = 78;
	  section.data(6).dtTransOffset = 33;
	
	  ;% Lab3_IMU_LQRI_P.HILReadEncoderTimebase_SamplesI
	  section.data(7).logicalSrcIdx = 79;
	  section.data(7).dtTransOffset = 36;
	
	  ;% Lab3_IMU_LQRI_P.StreamFormattedWrite_MaxUnits
	  section.data(8).logicalSrcIdx = 80;
	  section.data(8).dtTransOffset = 37;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_P.GameController_BufferSize
	  section.data(1).logicalSrcIdx = 81;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 41;
      section.data(41)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_P.HILInitialize_Active
	  section.data(1).logicalSrcIdx = 82;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOTerminate
	  section.data(2).logicalSrcIdx = 83;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOExit
	  section.data(3).logicalSrcIdx = 84;
	  section.data(3).dtTransOffset = 2;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOTerminate
	  section.data(4).logicalSrcIdx = 85;
	  section.data(4).dtTransOffset = 3;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOExit
	  section.data(5).logicalSrcIdx = 86;
	  section.data(5).dtTransOffset = 4;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POTerminate
	  section.data(6).logicalSrcIdx = 87;
	  section.data(6).dtTransOffset = 5;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POExit
	  section.data(7).logicalSrcIdx = 88;
	  section.data(7).dtTransOffset = 6;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_CKPStart
	  section.data(8).logicalSrcIdx = 89;
	  section.data(8).dtTransOffset = 7;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_CKPEnter
	  section.data(9).logicalSrcIdx = 90;
	  section.data(9).dtTransOffset = 8;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_CKStart
	  section.data(10).logicalSrcIdx = 91;
	  section.data(10).dtTransOffset = 9;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_CKEnter
	  section.data(11).logicalSrcIdx = 92;
	  section.data(11).dtTransOffset = 10;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AIPStart
	  section.data(12).logicalSrcIdx = 93;
	  section.data(12).dtTransOffset = 11;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AIPEnter
	  section.data(13).logicalSrcIdx = 94;
	  section.data(13).dtTransOffset = 12;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOPStart
	  section.data(14).logicalSrcIdx = 95;
	  section.data(14).dtTransOffset = 13;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOPEnter
	  section.data(15).logicalSrcIdx = 96;
	  section.data(15).dtTransOffset = 14;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOStart
	  section.data(16).logicalSrcIdx = 97;
	  section.data(16).dtTransOffset = 15;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOEnter
	  section.data(17).logicalSrcIdx = 98;
	  section.data(17).dtTransOffset = 16;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_AOReset
	  section.data(18).logicalSrcIdx = 99;
	  section.data(18).dtTransOffset = 17;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOPStart
	  section.data(19).logicalSrcIdx = 100;
	  section.data(19).dtTransOffset = 18;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOPEnter
	  section.data(20).logicalSrcIdx = 101;
	  section.data(20).dtTransOffset = 19;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOStart
	  section.data(21).logicalSrcIdx = 102;
	  section.data(21).dtTransOffset = 20;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOEnter
	  section.data(22).logicalSrcIdx = 103;
	  section.data(22).dtTransOffset = 21;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOReset
	  section.data(23).logicalSrcIdx = 104;
	  section.data(23).dtTransOffset = 22;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_EIPStart
	  section.data(24).logicalSrcIdx = 105;
	  section.data(24).dtTransOffset = 23;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_EIPEnter
	  section.data(25).logicalSrcIdx = 106;
	  section.data(25).dtTransOffset = 24;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_EIStart
	  section.data(26).logicalSrcIdx = 107;
	  section.data(26).dtTransOffset = 25;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_EIEnter
	  section.data(27).logicalSrcIdx = 108;
	  section.data(27).dtTransOffset = 26;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POPStart
	  section.data(28).logicalSrcIdx = 109;
	  section.data(28).dtTransOffset = 27;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POPEnter
	  section.data(29).logicalSrcIdx = 110;
	  section.data(29).dtTransOffset = 28;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POStart
	  section.data(30).logicalSrcIdx = 111;
	  section.data(30).dtTransOffset = 29;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POEnter
	  section.data(31).logicalSrcIdx = 112;
	  section.data(31).dtTransOffset = 30;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_POReset
	  section.data(32).logicalSrcIdx = 113;
	  section.data(32).dtTransOffset = 31;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_OOReset
	  section.data(33).logicalSrcIdx = 114;
	  section.data(33).dtTransOffset = 32;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOFinal
	  section.data(34).logicalSrcIdx = 115;
	  section.data(34).dtTransOffset = 33;
	
	  ;% Lab3_IMU_LQRI_P.HILInitialize_DOInitial
	  section.data(35).logicalSrcIdx = 116;
	  section.data(35).dtTransOffset = 34;
	
	  ;% Lab3_IMU_LQRI_P.HILReadEncoderTimebase_Active
	  section.data(36).logicalSrcIdx = 117;
	  section.data(36).dtTransOffset = 35;
	
	  ;% Lab3_IMU_LQRI_P.StreamCall1_NonBlocking
	  section.data(37).logicalSrcIdx = 118;
	  section.data(37).dtTransOffset = 36;
	
	  ;% Lab3_IMU_LQRI_P.StreamCall1_Active
	  section.data(38).logicalSrcIdx = 119;
	  section.data(38).dtTransOffset = 37;
	
	  ;% Lab3_IMU_LQRI_P.HILWriteAnalog_Active
	  section.data(39).logicalSrcIdx = 120;
	  section.data(39).dtTransOffset = 38;
	
	  ;% Lab3_IMU_LQRI_P.GameController_AutoCenter
	  section.data(40).logicalSrcIdx = 121;
	  section.data(40).dtTransOffset = 39;
	
	  ;% Lab3_IMU_LQRI_P.GameController_Enabled
	  section.data(41).logicalSrcIdx = 122;
	  section.data(41).dtTransOffset = 40;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_P.HILReadEncoderTimebase_Overflow
	  section.data(1).logicalSrcIdx = 123;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_P.StringConstant_Value
	  section.data(2).logicalSrcIdx = 124;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_LQRI_P.StreamCall1_URI
	  section.data(3).logicalSrcIdx = 125;
	  section.data(3).dtTransOffset = 256;
	
	  ;% Lab3_IMU_LQRI_P.StreamCall1_Endian
	  section.data(4).logicalSrcIdx = 126;
	  section.data(4).dtTransOffset = 257;
	
	  ;% Lab3_IMU_LQRI_P.Refp_c_CurrentSetting
	  section.data(5).logicalSrcIdx = 127;
	  section.data(5).dtTransOffset = 258;
	
	  ;% Lab3_IMU_LQRI_P.Refedot_c_CurrentSetting
	  section.data(6).logicalSrcIdx = 128;
	  section.data(6).dtTransOffset = 259;
	
	  ;% Lab3_IMU_LQRI_P.ManualSwitch_CurrentSetting
	  section.data(7).logicalSrcIdx = 129;
	  section.data(7).dtTransOffset = 260;
	
	  ;% Lab3_IMU_LQRI_P.GameController_ControllerNumber
	  section.data(8).logicalSrcIdx = 130;
	  section.data(8).dtTransOffset = 261;
	
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
    ;% Auto data (Lab3_IMU_LQRI_B)
    ;%
      section.nData     = 31;
      section.data(31)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_B.TravelCounttorad
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_B.TravelTransferFcn
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_LQRI_B.PitchCounttorad
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% Lab3_IMU_LQRI_B.PitchTransferFcn
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% Lab3_IMU_LQRI_B.ElevationCounttorad
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% Lab3_IMU_LQRI_B.ElevationTransferFcn
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% Lab3_IMU_LQRI_B.Switch
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% Lab3_IMU_LQRI_B.Gain1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 16;
	
	  ;% Lab3_IMU_LQRI_B.Gain2
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 19;
	
	  ;% Lab3_IMU_LQRI_B.DataTypeConversion
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 22;
	
	  ;% Lab3_IMU_LQRI_B.Integrator
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 23;
	
	  ;% Lab3_IMU_LQRI_B.FromWorkspace
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 28;
	
	  ;% Lab3_IMU_LQRI_B.RateTransitionx
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 30;
	
	  ;% Lab3_IMU_LQRI_B.Joystick_gain_x
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 31;
	
	  ;% Lab3_IMU_LQRI_B.Refp_c
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 32;
	
	  ;% Lab3_IMU_LQRI_B.RateTransitiony
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 33;
	
	  ;% Lab3_IMU_LQRI_B.Joystick_gain_y
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 34;
	
	  ;% Lab3_IMU_LQRI_B.Refedot_c
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 35;
	
	  ;% Lab3_IMU_LQRI_B.Fr
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 36;
	
	  ;% Lab3_IMU_LQRI_B.ManualSwitch
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 38;
	
	  ;% Lab3_IMU_LQRI_B.Integrator_m
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 39;
	
	  ;% Lab3_IMU_LQRI_B.u
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 41;
	
	  ;% Lab3_IMU_LQRI_B.Sum
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 43;
	
	  ;% Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 44;
	
	  ;% Lab3_IMU_LQRI_B.Sum1
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 71;
	
	  ;% Lab3_IMU_LQRI_B.FrontmotorSaturation
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 72;
	
	  ;% Lab3_IMU_LQRI_B.BackmotorSaturation
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 73;
	
	  ;% Lab3_IMU_LQRI_B.TmpSignalConversionAtIntegrator
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 74;
	
	  ;% Lab3_IMU_LQRI_B.Sum1_p
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 76;
	
	  ;% Lab3_IMU_LQRI_B.euler_rates
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 81;
	
	  ;% Lab3_IMU_LQRI_B.angles
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 84;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_B.StreamCall1_o2
	  section.data(1).logicalSrcIdx = 31;
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
    ;% Auto data (Lab3_IMU_LQRI_DW)
    ;%
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_AIMinimums
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_AIMaximums
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 8;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_AOMinimums
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 16;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_AOMaximums
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 24;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_AOVoltages
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 32;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_FilterFrequency
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 40;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_POSortedFreqs
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 48;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_POValues
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 56;
	
	  ;% Lab3_IMU_LQRI_DW.Memory_PreviousInput
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 64;
	
	  ;% Lab3_IMU_LQRI_DW.RateTransitionx_Buffer0
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 74;
	
	  ;% Lab3_IMU_LQRI_DW.RateTransitiony_Buffer0
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 75;
	
	  ;% Lab3_IMU_LQRI_DW.HILWriteAnalog_Buffer
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 76;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.StreamCall1_Stream
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.GameController_Controller
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.HILReadEncoderTimebase_Task
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 23;
      section.data(23)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.FromWorkspace_PWORK.TimePtr
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_DW.Scope_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_LQRI_DW.ToFile_PWORK.FilePtr
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 2;
	
	  ;% Lab3_IMU_LQRI_DW.e_imuve_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 19;
	  section.data(4).dtTransOffset = 3;
	
	  ;% Lab3_IMU_LQRI_DW.edot_imuvedot_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 20;
	  section.data(5).dtTransOffset = 6;
	
	  ;% Lab3_IMU_LQRI_DW.lambdadot_imuvlambdadot_PWORK.LoggedData
	  section.data(6).logicalSrcIdx = 21;
	  section.data(6).dtTransOffset = 9;
	
	  ;% Lab3_IMU_LQRI_DW.p_imuvp_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 22;
	  section.data(7).dtTransOffset = 12;
	
	  ;% Lab3_IMU_LQRI_DW.pdot_imuvpdot_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 23;
	  section.data(8).dtTransOffset = 15;
	
	  ;% Lab3_IMU_LQRI_DW.ElevationScoperads_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 24;
	  section.data(9).dtTransOffset = 18;
	
	  ;% Lab3_IMU_LQRI_DW.ElevationScoperad_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 25;
	  section.data(10).dtTransOffset = 19;
	
	  ;% Lab3_IMU_LQRI_DW.PitchScoperad_PWORK.LoggedData
	  section.data(11).logicalSrcIdx = 26;
	  section.data(11).dtTransOffset = 20;
	
	  ;% Lab3_IMU_LQRI_DW.PtichrateScoperads_PWORK.LoggedData
	  section.data(12).logicalSrcIdx = 27;
	  section.data(12).dtTransOffset = 21;
	
	  ;% Lab3_IMU_LQRI_DW.TravelrateScoperads_PWORK.LoggedData
	  section.data(13).logicalSrcIdx = 28;
	  section.data(13).dtTransOffset = 22;
	
	  ;% Lab3_IMU_LQRI_DW.TravelScoperad_PWORK.LoggedData
	  section.data(14).logicalSrcIdx = 29;
	  section.data(14).dtTransOffset = 23;
	
	  ;% Lab3_IMU_LQRI_DW.HILWriteAnalog_PWORK
	  section.data(15).logicalSrcIdx = 30;
	  section.data(15).dtTransOffset = 24;
	
	  ;% Lab3_IMU_LQRI_DW.Connected_PWORK.LoggedData
	  section.data(16).logicalSrcIdx = 31;
	  section.data(16).dtTransOffset = 25;
	
	  ;% Lab3_IMU_LQRI_DW.XScope_PWORK.LoggedData
	  section.data(17).logicalSrcIdx = 32;
	  section.data(17).dtTransOffset = 26;
	
	  ;% Lab3_IMU_LQRI_DW.YScope_PWORK.LoggedData
	  section.data(18).logicalSrcIdx = 33;
	  section.data(18).dtTransOffset = 27;
	
	  ;% Lab3_IMU_LQRI_DW.VdScope_PWORK.LoggedData
	  section.data(19).logicalSrcIdx = 34;
	  section.data(19).dtTransOffset = 28;
	
	  ;% Lab3_IMU_LQRI_DW.VsScope_PWORK.LoggedData
	  section.data(20).logicalSrcIdx = 35;
	  section.data(20).dtTransOffset = 29;
	
	  ;% Lab3_IMU_LQRI_DW.edotandecdot_PWORK.LoggedData
	  section.data(21).logicalSrcIdx = 36;
	  section.data(21).dtTransOffset = 30;
	
	  ;% Lab3_IMU_LQRI_DW.p2Run_PWORK.FilePtr
	  section.data(22).logicalSrcIdx = 37;
	  section.data(22).dtTransOffset = 32;
	
	  ;% Lab3_IMU_LQRI_DW.pcScoperad_PWORK.LoggedData
	  section.data(23).logicalSrcIdx = 38;
	  section.data(23).dtTransOffset = 33;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_ClockModes
	  section.data(1).logicalSrcIdx = 39;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_QuadratureModes
	  section.data(2).logicalSrcIdx = 40;
	  section.data(2).dtTransOffset = 3;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_InitialEICounts
	  section.data(3).logicalSrcIdx = 41;
	  section.data(3).dtTransOffset = 11;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_POModeValues
	  section.data(4).logicalSrcIdx = 42;
	  section.data(4).dtTransOffset = 19;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_POAlignValues
	  section.data(5).logicalSrcIdx = 43;
	  section.data(5).dtTransOffset = 27;
	
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_POPolarityVals
	  section.data(6).logicalSrcIdx = 44;
	  section.data(6).dtTransOffset = 35;
	
	  ;% Lab3_IMU_LQRI_DW.HILReadEncoderTimebase_Buffer
	  section.data(7).logicalSrcIdx = 45;
	  section.data(7).dtTransOffset = 43;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.HILInitialize_POSortedChans
	  section.data(1).logicalSrcIdx = 46;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.FromWorkspace_IWORK.PrevIndex
	  section.data(1).logicalSrcIdx = 47;
	  section.data(1).dtTransOffset = 0;
	
	  ;% Lab3_IMU_LQRI_DW.ToFile_IWORK.Count
	  section.data(2).logicalSrcIdx = 48;
	  section.data(2).dtTransOffset = 1;
	
	  ;% Lab3_IMU_LQRI_DW.p2Run_IWORK.Count
	  section.data(3).logicalSrcIdx = 49;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% Lab3_IMU_LQRI_DW.StreamCall1_State
	  section.data(1).logicalSrcIdx = 50;
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


  targMap.checksum0 = 3053075096;
  targMap.checksum1 = 309926603;
  targMap.checksum2 = 3232501935;
  targMap.checksum3 = 1567631671;

