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
    ;% Auto data (heli_p3_LObserver_P)
    ;%
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_P.F
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_P.Joystick_gain_x
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 4;
	
	  ;% heli_p3_LObserver_P.Joystick_gain_y
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 5;
	
	  ;% heli_p3_LObserver_P.K
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 6;
	
	  ;% heli_p3_LObserver_P.edot_pulse
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 16;
	
	  ;% heli_p3_LObserver_P.pc_step
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 17;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_P.HILWriteAnalog_channels
	  section.data(1).logicalSrcIdx = 6;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 56;
      section.data(56)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_P.Constant_Value
	  section.data(1).logicalSrcIdx = 7;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_P.Constant1_Value
	  section.data(2).logicalSrcIdx = 8;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p3_LObserver_P.HILInitialize_OOTerminate
	  section.data(3).logicalSrcIdx = 9;
	  section.data(3).dtTransOffset = 2;
	
	  ;% heli_p3_LObserver_P.HILInitialize_OOExit
	  section.data(4).logicalSrcIdx = 10;
	  section.data(4).dtTransOffset = 3;
	
	  ;% heli_p3_LObserver_P.HILInitialize_OOStart
	  section.data(5).logicalSrcIdx = 11;
	  section.data(5).dtTransOffset = 4;
	
	  ;% heli_p3_LObserver_P.HILInitialize_OOEnter
	  section.data(6).logicalSrcIdx = 12;
	  section.data(6).dtTransOffset = 5;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOFinal
	  section.data(7).logicalSrcIdx = 13;
	  section.data(7).dtTransOffset = 6;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POFinal
	  section.data(8).logicalSrcIdx = 14;
	  section.data(8).dtTransOffset = 7;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AIHigh
	  section.data(9).logicalSrcIdx = 15;
	  section.data(9).dtTransOffset = 8;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AILow
	  section.data(10).logicalSrcIdx = 16;
	  section.data(10).dtTransOffset = 9;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOHigh
	  section.data(11).logicalSrcIdx = 17;
	  section.data(11).dtTransOffset = 10;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOLow
	  section.data(12).logicalSrcIdx = 18;
	  section.data(12).dtTransOffset = 11;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOInitial
	  section.data(13).logicalSrcIdx = 19;
	  section.data(13).dtTransOffset = 12;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOWatchdog
	  section.data(14).logicalSrcIdx = 20;
	  section.data(14).dtTransOffset = 13;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POFrequency
	  section.data(15).logicalSrcIdx = 21;
	  section.data(15).dtTransOffset = 14;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POLeading
	  section.data(16).logicalSrcIdx = 22;
	  section.data(16).dtTransOffset = 15;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POTrailing
	  section.data(17).logicalSrcIdx = 23;
	  section.data(17).dtTransOffset = 16;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POInitial
	  section.data(18).logicalSrcIdx = 24;
	  section.data(18).dtTransOffset = 17;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POWatchdog
	  section.data(19).logicalSrcIdx = 25;
	  section.data(19).dtTransOffset = 18;
	
	  ;% heli_p3_LObserver_P.Constant1_Value_g
	  section.data(20).logicalSrcIdx = 26;
	  section.data(20).dtTransOffset = 19;
	
	  ;% heli_p3_LObserver_P.Constant_Value_o
	  section.data(21).logicalSrcIdx = 27;
	  section.data(21).dtTransOffset = 20;
	
	  ;% heli_p3_LObserver_P.Constant1_Value_k
	  section.data(22).logicalSrcIdx = 28;
	  section.data(22).dtTransOffset = 21;
	
	  ;% heli_p3_LObserver_P.Memory_InitialCondition
	  section.data(23).logicalSrcIdx = 29;
	  section.data(23).dtTransOffset = 22;
	
	  ;% heli_p3_LObserver_P.Gain2_Gain
	  section.data(24).logicalSrcIdx = 30;
	  section.data(24).dtTransOffset = 32;
	
	  ;% heli_p3_LObserver_P.Gain1_Gain
	  section.data(25).logicalSrcIdx = 31;
	  section.data(25).dtTransOffset = 41;
	
	  ;% heli_p3_LObserver_P.Constant_Value_e
	  section.data(26).logicalSrcIdx = 32;
	  section.data(26).dtTransOffset = 50;
	
	  ;% heli_p3_LObserver_P.TravelCounttorad_Gain
	  section.data(27).logicalSrcIdx = 33;
	  section.data(27).dtTransOffset = 51;
	
	  ;% heli_p3_LObserver_P.TravelTransferFcn_A
	  section.data(28).logicalSrcIdx = 34;
	  section.data(28).dtTransOffset = 52;
	
	  ;% heli_p3_LObserver_P.TravelTransferFcn_C
	  section.data(29).logicalSrcIdx = 35;
	  section.data(29).dtTransOffset = 53;
	
	  ;% heli_p3_LObserver_P.TravelTransferFcn_D
	  section.data(30).logicalSrcIdx = 36;
	  section.data(30).dtTransOffset = 54;
	
	  ;% heli_p3_LObserver_P.PitchCounttorad_Gain
	  section.data(31).logicalSrcIdx = 37;
	  section.data(31).dtTransOffset = 55;
	
	  ;% heli_p3_LObserver_P.PitchTransferFcn_A
	  section.data(32).logicalSrcIdx = 38;
	  section.data(32).dtTransOffset = 56;
	
	  ;% heli_p3_LObserver_P.PitchTransferFcn_C
	  section.data(33).logicalSrcIdx = 39;
	  section.data(33).dtTransOffset = 57;
	
	  ;% heli_p3_LObserver_P.PitchTransferFcn_D
	  section.data(34).logicalSrcIdx = 40;
	  section.data(34).dtTransOffset = 58;
	
	  ;% heli_p3_LObserver_P.ElevationCounttorad_Gain
	  section.data(35).logicalSrcIdx = 41;
	  section.data(35).dtTransOffset = 59;
	
	  ;% heli_p3_LObserver_P.ElevationTransferFcn_A
	  section.data(36).logicalSrcIdx = 42;
	  section.data(36).dtTransOffset = 60;
	
	  ;% heli_p3_LObserver_P.ElevationTransferFcn_C
	  section.data(37).logicalSrcIdx = 43;
	  section.data(37).dtTransOffset = 61;
	
	  ;% heli_p3_LObserver_P.ElevationTransferFcn_D
	  section.data(38).logicalSrcIdx = 44;
	  section.data(38).dtTransOffset = 62;
	
	  ;% heli_p3_LObserver_P.Step_Time
	  section.data(39).logicalSrcIdx = 45;
	  section.data(39).dtTransOffset = 63;
	
	  ;% heli_p3_LObserver_P.Step_Y0
	  section.data(40).logicalSrcIdx = 46;
	  section.data(40).dtTransOffset = 64;
	
	  ;% heli_p3_LObserver_P.RateTransitionx_InitialConditio
	  section.data(41).logicalSrcIdx = 47;
	  section.data(41).dtTransOffset = 65;
	
	  ;% heli_p3_LObserver_P.DeadZonex_Start
	  section.data(42).logicalSrcIdx = 48;
	  section.data(42).dtTransOffset = 66;
	
	  ;% heli_p3_LObserver_P.DeadZonex_End
	  section.data(43).logicalSrcIdx = 49;
	  section.data(43).dtTransOffset = 67;
	
	  ;% heli_p3_LObserver_P.Gainx_Gain
	  section.data(44).logicalSrcIdx = 50;
	  section.data(44).dtTransOffset = 68;
	
	  ;% heli_p3_LObserver_P.FrontmotorSaturation_UpperSat
	  section.data(45).logicalSrcIdx = 51;
	  section.data(45).dtTransOffset = 69;
	
	  ;% heli_p3_LObserver_P.FrontmotorSaturation_LowerSat
	  section.data(46).logicalSrcIdx = 52;
	  section.data(46).dtTransOffset = 70;
	
	  ;% heli_p3_LObserver_P.BackmotorSaturation_UpperSat
	  section.data(47).logicalSrcIdx = 53;
	  section.data(47).dtTransOffset = 71;
	
	  ;% heli_p3_LObserver_P.BackmotorSaturation_LowerSat
	  section.data(48).logicalSrcIdx = 54;
	  section.data(48).dtTransOffset = 72;
	
	  ;% heli_p3_LObserver_P.RateTransitiony_InitialConditio
	  section.data(49).logicalSrcIdx = 55;
	  section.data(49).dtTransOffset = 73;
	
	  ;% heli_p3_LObserver_P.DeadZoney_Start
	  section.data(50).logicalSrcIdx = 56;
	  section.data(50).dtTransOffset = 74;
	
	  ;% heli_p3_LObserver_P.DeadZoney_End
	  section.data(51).logicalSrcIdx = 57;
	  section.data(51).dtTransOffset = 75;
	
	  ;% heli_p3_LObserver_P.Gainy_Gain
	  section.data(52).logicalSrcIdx = 58;
	  section.data(52).dtTransOffset = 76;
	
	  ;% heli_p3_LObserver_P.PulseGenerator_Period
	  section.data(53).logicalSrcIdx = 59;
	  section.data(53).dtTransOffset = 77;
	
	  ;% heli_p3_LObserver_P.PulseGenerator_Duty
	  section.data(54).logicalSrcIdx = 60;
	  section.data(54).dtTransOffset = 78;
	
	  ;% heli_p3_LObserver_P.PulseGenerator_PhaseDelay
	  section.data(55).logicalSrcIdx = 61;
	  section.data(55).dtTransOffset = 79;
	
	  ;% heli_p3_LObserver_P.Integrator_IC
	  section.data(56).logicalSrcIdx = 62;
	  section.data(56).dtTransOffset = 80;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 63;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOWatchdog
	  section.data(2).logicalSrcIdx = 64;
	  section.data(2).dtTransOffset = 3;
	
	  ;% heli_p3_LObserver_P.HILInitialize_EIInitial
	  section.data(3).logicalSrcIdx = 65;
	  section.data(3).dtTransOffset = 4;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POModes
	  section.data(4).logicalSrcIdx = 66;
	  section.data(4).dtTransOffset = 5;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POConfiguration
	  section.data(5).logicalSrcIdx = 67;
	  section.data(5).dtTransOffset = 6;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POAlignment
	  section.data(6).logicalSrcIdx = 68;
	  section.data(6).dtTransOffset = 7;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POPolarity
	  section.data(7).logicalSrcIdx = 69;
	  section.data(7).dtTransOffset = 8;
	
	  ;% heli_p3_LObserver_P.HILReadEncoderTimebase_Clock
	  section.data(8).logicalSrcIdx = 70;
	  section.data(8).dtTransOffset = 9;
	
	  ;% heli_p3_LObserver_P.StreamCall1_SendBufferSize
	  section.data(9).logicalSrcIdx = 71;
	  section.data(9).dtTransOffset = 10;
	
	  ;% heli_p3_LObserver_P.StreamCall1_ReceiveBufferSize
	  section.data(10).logicalSrcIdx = 72;
	  section.data(10).dtTransOffset = 11;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 73;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 74;
	  section.data(2).dtTransOffset = 8;
	
	  ;% heli_p3_LObserver_P.HILInitialize_EIChannels
	  section.data(3).logicalSrcIdx = 75;
	  section.data(3).dtTransOffset = 16;
	
	  ;% heli_p3_LObserver_P.HILInitialize_EIQuadrature
	  section.data(4).logicalSrcIdx = 76;
	  section.data(4).dtTransOffset = 24;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POChannels
	  section.data(5).logicalSrcIdx = 77;
	  section.data(5).dtTransOffset = 25;
	
	  ;% heli_p3_LObserver_P.HILReadEncoderTimebase_Channels
	  section.data(6).logicalSrcIdx = 78;
	  section.data(6).dtTransOffset = 33;
	
	  ;% heli_p3_LObserver_P.HILReadEncoderTimebase_SamplesI
	  section.data(7).logicalSrcIdx = 79;
	  section.data(7).dtTransOffset = 36;
	
	  ;% heli_p3_LObserver_P.StreamFormattedWrite_MaxUnits
	  section.data(8).logicalSrcIdx = 80;
	  section.data(8).dtTransOffset = 37;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_P.GameController_BufferSize
	  section.data(1).logicalSrcIdx = 81;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 41;
      section.data(41)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_P.HILInitialize_Active
	  section.data(1).logicalSrcIdx = 82;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOTerminate
	  section.data(2).logicalSrcIdx = 83;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOExit
	  section.data(3).logicalSrcIdx = 84;
	  section.data(3).dtTransOffset = 2;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOTerminate
	  section.data(4).logicalSrcIdx = 85;
	  section.data(4).dtTransOffset = 3;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOExit
	  section.data(5).logicalSrcIdx = 86;
	  section.data(5).dtTransOffset = 4;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POTerminate
	  section.data(6).logicalSrcIdx = 87;
	  section.data(6).dtTransOffset = 5;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POExit
	  section.data(7).logicalSrcIdx = 88;
	  section.data(7).dtTransOffset = 6;
	
	  ;% heli_p3_LObserver_P.HILInitialize_CKPStart
	  section.data(8).logicalSrcIdx = 89;
	  section.data(8).dtTransOffset = 7;
	
	  ;% heli_p3_LObserver_P.HILInitialize_CKPEnter
	  section.data(9).logicalSrcIdx = 90;
	  section.data(9).dtTransOffset = 8;
	
	  ;% heli_p3_LObserver_P.HILInitialize_CKStart
	  section.data(10).logicalSrcIdx = 91;
	  section.data(10).dtTransOffset = 9;
	
	  ;% heli_p3_LObserver_P.HILInitialize_CKEnter
	  section.data(11).logicalSrcIdx = 92;
	  section.data(11).dtTransOffset = 10;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AIPStart
	  section.data(12).logicalSrcIdx = 93;
	  section.data(12).dtTransOffset = 11;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AIPEnter
	  section.data(13).logicalSrcIdx = 94;
	  section.data(13).dtTransOffset = 12;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOPStart
	  section.data(14).logicalSrcIdx = 95;
	  section.data(14).dtTransOffset = 13;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOPEnter
	  section.data(15).logicalSrcIdx = 96;
	  section.data(15).dtTransOffset = 14;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOStart
	  section.data(16).logicalSrcIdx = 97;
	  section.data(16).dtTransOffset = 15;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOEnter
	  section.data(17).logicalSrcIdx = 98;
	  section.data(17).dtTransOffset = 16;
	
	  ;% heli_p3_LObserver_P.HILInitialize_AOReset
	  section.data(18).logicalSrcIdx = 99;
	  section.data(18).dtTransOffset = 17;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOPStart
	  section.data(19).logicalSrcIdx = 100;
	  section.data(19).dtTransOffset = 18;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOPEnter
	  section.data(20).logicalSrcIdx = 101;
	  section.data(20).dtTransOffset = 19;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOStart
	  section.data(21).logicalSrcIdx = 102;
	  section.data(21).dtTransOffset = 20;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOEnter
	  section.data(22).logicalSrcIdx = 103;
	  section.data(22).dtTransOffset = 21;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOReset
	  section.data(23).logicalSrcIdx = 104;
	  section.data(23).dtTransOffset = 22;
	
	  ;% heli_p3_LObserver_P.HILInitialize_EIPStart
	  section.data(24).logicalSrcIdx = 105;
	  section.data(24).dtTransOffset = 23;
	
	  ;% heli_p3_LObserver_P.HILInitialize_EIPEnter
	  section.data(25).logicalSrcIdx = 106;
	  section.data(25).dtTransOffset = 24;
	
	  ;% heli_p3_LObserver_P.HILInitialize_EIStart
	  section.data(26).logicalSrcIdx = 107;
	  section.data(26).dtTransOffset = 25;
	
	  ;% heli_p3_LObserver_P.HILInitialize_EIEnter
	  section.data(27).logicalSrcIdx = 108;
	  section.data(27).dtTransOffset = 26;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POPStart
	  section.data(28).logicalSrcIdx = 109;
	  section.data(28).dtTransOffset = 27;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POPEnter
	  section.data(29).logicalSrcIdx = 110;
	  section.data(29).dtTransOffset = 28;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POStart
	  section.data(30).logicalSrcIdx = 111;
	  section.data(30).dtTransOffset = 29;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POEnter
	  section.data(31).logicalSrcIdx = 112;
	  section.data(31).dtTransOffset = 30;
	
	  ;% heli_p3_LObserver_P.HILInitialize_POReset
	  section.data(32).logicalSrcIdx = 113;
	  section.data(32).dtTransOffset = 31;
	
	  ;% heli_p3_LObserver_P.HILInitialize_OOReset
	  section.data(33).logicalSrcIdx = 114;
	  section.data(33).dtTransOffset = 32;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOFinal
	  section.data(34).logicalSrcIdx = 115;
	  section.data(34).dtTransOffset = 33;
	
	  ;% heli_p3_LObserver_P.HILInitialize_DOInitial
	  section.data(35).logicalSrcIdx = 116;
	  section.data(35).dtTransOffset = 34;
	
	  ;% heli_p3_LObserver_P.HILReadEncoderTimebase_Active
	  section.data(36).logicalSrcIdx = 117;
	  section.data(36).dtTransOffset = 35;
	
	  ;% heli_p3_LObserver_P.StreamCall1_NonBlocking
	  section.data(37).logicalSrcIdx = 118;
	  section.data(37).dtTransOffset = 36;
	
	  ;% heli_p3_LObserver_P.StreamCall1_Active
	  section.data(38).logicalSrcIdx = 119;
	  section.data(38).dtTransOffset = 37;
	
	  ;% heli_p3_LObserver_P.HILWriteAnalog_Active
	  section.data(39).logicalSrcIdx = 120;
	  section.data(39).dtTransOffset = 38;
	
	  ;% heli_p3_LObserver_P.GameController_AutoCenter
	  section.data(40).logicalSrcIdx = 121;
	  section.data(40).dtTransOffset = 39;
	
	  ;% heli_p3_LObserver_P.GameController_Enabled
	  section.data(41).logicalSrcIdx = 122;
	  section.data(41).dtTransOffset = 40;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_P.HILReadEncoderTimebase_Overflow
	  section.data(1).logicalSrcIdx = 123;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_P.StringConstant_Value
	  section.data(2).logicalSrcIdx = 124;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p3_LObserver_P.StreamCall1_URI
	  section.data(3).logicalSrcIdx = 125;
	  section.data(3).dtTransOffset = 256;
	
	  ;% heli_p3_LObserver_P.StreamCall1_Endian
	  section.data(4).logicalSrcIdx = 126;
	  section.data(4).dtTransOffset = 257;
	
	  ;% heli_p3_LObserver_P.ManualSwitch_CurrentSetting
	  section.data(5).logicalSrcIdx = 127;
	  section.data(5).dtTransOffset = 258;
	
	  ;% heli_p3_LObserver_P.ManualSwitch1_CurrentSetting
	  section.data(6).logicalSrcIdx = 128;
	  section.data(6).dtTransOffset = 259;
	
	  ;% heli_p3_LObserver_P.ManualSwitch_CurrentSetting_f
	  section.data(7).logicalSrcIdx = 129;
	  section.data(7).dtTransOffset = 260;
	
	  ;% heli_p3_LObserver_P.GameController_ControllerNumber
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
    ;% Auto data (heli_p3_LObserver_B)
    ;%
      section.nData     = 21;
      section.data(21)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_B.Switch
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_B.Gain2
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 10;
	
	  ;% heli_p3_LObserver_B.X
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 13;
	
	  ;% heli_p3_LObserver_B.Gain1
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 14;
	
	  ;% heli_p3_LObserver_B.Z
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 17;
	
	  ;% heli_p3_LObserver_B.TravelCounttorad
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 18;
	
	  ;% heli_p3_LObserver_B.TravelTransferFcn
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 19;
	
	  ;% heli_p3_LObserver_B.PitchCounttorad
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 20;
	
	  ;% heli_p3_LObserver_B.PitchTransferFcn
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 21;
	
	  ;% heli_p3_LObserver_B.ElevationCounttorad
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 22;
	
	  ;% heli_p3_LObserver_B.ElevationTransferFcn
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 23;
	
	  ;% heli_p3_LObserver_B.RateTransitionx
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 24;
	
	  ;% heli_p3_LObserver_B.Joystick_gain_x
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 25;
	
	  ;% heli_p3_LObserver_B.ManualSwitch
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 26;
	
	  ;% heli_p3_LObserver_B.RateTransitiony
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 27;
	
	  ;% heli_p3_LObserver_B.Joystick_gain_y
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 28;
	
	  ;% heli_p3_LObserver_B.ManualSwitch1
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 29;
	
	  ;% heli_p3_LObserver_B.ManualSwitch_h
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 30;
	
	  ;% heli_p3_LObserver_B.Integrator
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 31;
	
	  ;% heli_p3_LObserver_B.u
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 33;
	
	  ;% heli_p3_LObserver_B.TmpSignalConversionAtIntegrator
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 35;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_B.StreamCall1_o2
	  section.data(1).logicalSrcIdx = 21;
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
    ;% Auto data (heli_p3_LObserver_DW)
    ;%
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.HILInitialize_AIMinimums
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_AIMaximums
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 8;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_AOMinimums
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 16;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_AOMaximums
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 24;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_AOVoltages
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 32;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_FilterFrequency
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 40;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_POSortedFreqs
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 48;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_POValues
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 56;
	
	  ;% heli_p3_LObserver_DW.Memory_PreviousInput
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 64;
	
	  ;% heli_p3_LObserver_DW.RateTransitionx_Buffer0
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 74;
	
	  ;% heli_p3_LObserver_DW.HILWriteAnalog_Buffer
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 75;
	
	  ;% heli_p3_LObserver_DW.RateTransitiony_Buffer0
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 77;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.StreamCall1_Stream
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.GameController_Controller
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.HILReadEncoderTimebase_Task
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 20;
      section.data(20)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.XPitch_PWORK.LoggedData
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_DW.YElevation_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 17;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p3_LObserver_DW.ZTravel_PWORK.LoggedData
	  section.data(3).logicalSrcIdx = 18;
	  section.data(3).dtTransOffset = 2;
	
	  ;% heli_p3_LObserver_DW.Connected_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 19;
	  section.data(4).dtTransOffset = 3;
	
	  ;% heli_p3_LObserver_DW.Heli3DLog_PWORK.FilePtr
	  section.data(5).logicalSrcIdx = 20;
	  section.data(5).dtTransOffset = 4;
	
	  ;% heli_p3_LObserver_DW.InputxpitchScope_PWORK.LoggedData
	  section.data(6).logicalSrcIdx = 21;
	  section.data(6).dtTransOffset = 5;
	
	  ;% heli_p3_LObserver_DW.ElevationScoperads_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 22;
	  section.data(7).dtTransOffset = 6;
	
	  ;% heli_p3_LObserver_DW.ElevationScoperad_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 23;
	  section.data(8).dtTransOffset = 7;
	
	  ;% heli_p3_LObserver_DW.PitchScoperad_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 24;
	  section.data(9).dtTransOffset = 8;
	
	  ;% heli_p3_LObserver_DW.PtichrateScoperads_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 25;
	  section.data(10).dtTransOffset = 9;
	
	  ;% heli_p3_LObserver_DW.TravelrateScoperads_PWORK.LoggedData
	  section.data(11).logicalSrcIdx = 26;
	  section.data(11).dtTransOffset = 10;
	
	  ;% heli_p3_LObserver_DW.TravelScoperad_PWORK.LoggedData
	  section.data(12).logicalSrcIdx = 27;
	  section.data(12).dtTransOffset = 11;
	
	  ;% heli_p3_LObserver_DW.HILWriteAnalog_PWORK
	  section.data(13).logicalSrcIdx = 28;
	  section.data(13).dtTransOffset = 12;
	
	  ;% heli_p3_LObserver_DW.XScope_PWORK.LoggedData
	  section.data(14).logicalSrcIdx = 29;
	  section.data(14).dtTransOffset = 13;
	
	  ;% heli_p3_LObserver_DW.YScope_PWORK.LoggedData
	  section.data(15).logicalSrcIdx = 30;
	  section.data(15).dtTransOffset = 14;
	
	  ;% heli_p3_LObserver_DW.VdScope_PWORK.LoggedData
	  section.data(16).logicalSrcIdx = 31;
	  section.data(16).dtTransOffset = 15;
	
	  ;% heli_p3_LObserver_DW.VsScope_PWORK.LoggedData
	  section.data(17).logicalSrcIdx = 32;
	  section.data(17).dtTransOffset = 16;
	
	  ;% heli_p3_LObserver_DW.edotandecdot_PWORK.LoggedData
	  section.data(18).logicalSrcIdx = 33;
	  section.data(18).dtTransOffset = 17;
	
	  ;% heli_p3_LObserver_DW.p2Run_PWORK.FilePtr
	  section.data(19).logicalSrcIdx = 34;
	  section.data(19).dtTransOffset = 19;
	
	  ;% heli_p3_LObserver_DW.pcScoperad_PWORK.LoggedData
	  section.data(20).logicalSrcIdx = 35;
	  section.data(20).dtTransOffset = 20;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.HILInitialize_ClockModes
	  section.data(1).logicalSrcIdx = 36;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_QuadratureModes
	  section.data(2).logicalSrcIdx = 37;
	  section.data(2).dtTransOffset = 3;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_InitialEICounts
	  section.data(3).logicalSrcIdx = 38;
	  section.data(3).dtTransOffset = 11;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_POModeValues
	  section.data(4).logicalSrcIdx = 39;
	  section.data(4).dtTransOffset = 19;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_POAlignValues
	  section.data(5).logicalSrcIdx = 40;
	  section.data(5).dtTransOffset = 27;
	
	  ;% heli_p3_LObserver_DW.HILInitialize_POPolarityVals
	  section.data(6).logicalSrcIdx = 41;
	  section.data(6).dtTransOffset = 35;
	
	  ;% heli_p3_LObserver_DW.HILReadEncoderTimebase_Buffer
	  section.data(7).logicalSrcIdx = 42;
	  section.data(7).dtTransOffset = 43;
	
	  ;% heli_p3_LObserver_DW.clockTickCounter
	  section.data(8).logicalSrcIdx = 43;
	  section.data(8).dtTransOffset = 46;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.HILInitialize_POSortedChans
	  section.data(1).logicalSrcIdx = 44;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.Heli3DLog_IWORK.Count
	  section.data(1).logicalSrcIdx = 45;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p3_LObserver_DW.p2Run_IWORK.Count
	  section.data(2).logicalSrcIdx = 46;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p3_LObserver_DW.StreamCall1_State
	  section.data(1).logicalSrcIdx = 47;
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


  targMap.checksum0 = 908892295;
  targMap.checksum1 = 1531246963;
  targMap.checksum2 = 3879778826;
  targMap.checksum3 = 2403817220;

