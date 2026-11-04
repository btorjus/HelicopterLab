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
    ;% Auto data (heli_p4_kalman_kf_r2020b_P)
    ;%
      section.nData     = 12;
      section.data(12)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_P.Ad
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Bd
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 36;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Cd
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 48;
	
	  ;% heli_p4_kalman_kf_r2020b_P.F
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 78;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Joystick_gain_x
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 82;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Joystick_gain_y
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 83;
	
	  ;% heli_p4_kalman_kf_r2020b_P.K
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 84;
	
	  ;% heli_p4_kalman_kf_r2020b_P.P0
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 94;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Qd
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 130;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Rd
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 166;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Vs0
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 191;
	
	  ;% heli_p4_kalman_kf_r2020b_P.x0
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 192;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_P.HILWriteAnalog_channels
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 52;
      section.data(52)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_P.Constant_Value
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Constant1_Value
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Constant_Value_j
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 2;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_OOTerminate
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 3;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_OOExit
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 4;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_OOStart
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 5;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_OOEnter
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 6;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOFinal
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 7;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POFinal
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 8;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AIHigh
	  section.data(10).logicalSrcIdx = 22;
	  section.data(10).dtTransOffset = 9;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AILow
	  section.data(11).logicalSrcIdx = 23;
	  section.data(11).dtTransOffset = 10;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOHigh
	  section.data(12).logicalSrcIdx = 24;
	  section.data(12).dtTransOffset = 11;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOLow
	  section.data(13).logicalSrcIdx = 25;
	  section.data(13).dtTransOffset = 12;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOInitial
	  section.data(14).logicalSrcIdx = 26;
	  section.data(14).dtTransOffset = 13;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOWatchdog
	  section.data(15).logicalSrcIdx = 27;
	  section.data(15).dtTransOffset = 14;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POFrequency
	  section.data(16).logicalSrcIdx = 28;
	  section.data(16).dtTransOffset = 15;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POLeading
	  section.data(17).logicalSrcIdx = 29;
	  section.data(17).dtTransOffset = 16;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POTrailing
	  section.data(18).logicalSrcIdx = 30;
	  section.data(18).dtTransOffset = 17;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POInitial
	  section.data(19).logicalSrcIdx = 31;
	  section.data(19).dtTransOffset = 18;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POWatchdog
	  section.data(20).logicalSrcIdx = 32;
	  section.data(20).dtTransOffset = 19;
	
	  ;% heli_p4_kalman_kf_r2020b_P.TravelCounttorad_Gain
	  section.data(21).logicalSrcIdx = 33;
	  section.data(21).dtTransOffset = 20;
	
	  ;% heli_p4_kalman_kf_r2020b_P.TravelTransferFcn_A
	  section.data(22).logicalSrcIdx = 34;
	  section.data(22).dtTransOffset = 21;
	
	  ;% heli_p4_kalman_kf_r2020b_P.TravelTransferFcn_C
	  section.data(23).logicalSrcIdx = 35;
	  section.data(23).dtTransOffset = 22;
	
	  ;% heli_p4_kalman_kf_r2020b_P.TravelTransferFcn_D
	  section.data(24).logicalSrcIdx = 36;
	  section.data(24).dtTransOffset = 23;
	
	  ;% heli_p4_kalman_kf_r2020b_P.PitchCounttorad_Gain
	  section.data(25).logicalSrcIdx = 37;
	  section.data(25).dtTransOffset = 24;
	
	  ;% heli_p4_kalman_kf_r2020b_P.PitchTransferFcn_A
	  section.data(26).logicalSrcIdx = 38;
	  section.data(26).dtTransOffset = 25;
	
	  ;% heli_p4_kalman_kf_r2020b_P.PitchTransferFcn_C
	  section.data(27).logicalSrcIdx = 39;
	  section.data(27).dtTransOffset = 26;
	
	  ;% heli_p4_kalman_kf_r2020b_P.PitchTransferFcn_D
	  section.data(28).logicalSrcIdx = 40;
	  section.data(28).dtTransOffset = 27;
	
	  ;% heli_p4_kalman_kf_r2020b_P.ElevationCounttorad_Gain
	  section.data(29).logicalSrcIdx = 41;
	  section.data(29).dtTransOffset = 28;
	
	  ;% heli_p4_kalman_kf_r2020b_P.ElevationTransferFcn_A
	  section.data(30).logicalSrcIdx = 42;
	  section.data(30).dtTransOffset = 29;
	
	  ;% heli_p4_kalman_kf_r2020b_P.ElevationTransferFcn_C
	  section.data(31).logicalSrcIdx = 43;
	  section.data(31).dtTransOffset = 30;
	
	  ;% heli_p4_kalman_kf_r2020b_P.ElevationTransferFcn_D
	  section.data(32).logicalSrcIdx = 44;
	  section.data(32).dtTransOffset = 31;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Constant_Value_p
	  section.data(33).logicalSrcIdx = 45;
	  section.data(33).dtTransOffset = 32;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Constant1_Value_i
	  section.data(34).logicalSrcIdx = 46;
	  section.data(34).dtTransOffset = 33;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Memory_InitialCondition
	  section.data(35).logicalSrcIdx = 47;
	  section.data(35).dtTransOffset = 34;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Gain1_Gain
	  section.data(36).logicalSrcIdx = 48;
	  section.data(36).dtTransOffset = 44;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Gain2_Gain
	  section.data(37).logicalSrcIdx = 49;
	  section.data(37).dtTransOffset = 53;
	
	  ;% heli_p4_kalman_kf_r2020b_P.RateTransitionx_InitialConditio
	  section.data(38).logicalSrcIdx = 50;
	  section.data(38).dtTransOffset = 62;
	
	  ;% heli_p4_kalman_kf_r2020b_P.DeadZonex_Start
	  section.data(39).logicalSrcIdx = 51;
	  section.data(39).dtTransOffset = 63;
	
	  ;% heli_p4_kalman_kf_r2020b_P.DeadZonex_End
	  section.data(40).logicalSrcIdx = 52;
	  section.data(40).dtTransOffset = 64;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Gainx_Gain
	  section.data(41).logicalSrcIdx = 53;
	  section.data(41).dtTransOffset = 65;
	
	  ;% heli_p4_kalman_kf_r2020b_P.RateTransitiony_InitialConditio
	  section.data(42).logicalSrcIdx = 54;
	  section.data(42).dtTransOffset = 66;
	
	  ;% heli_p4_kalman_kf_r2020b_P.DeadZoney_Start
	  section.data(43).logicalSrcIdx = 55;
	  section.data(43).dtTransOffset = 67;
	
	  ;% heli_p4_kalman_kf_r2020b_P.DeadZoney_End
	  section.data(44).logicalSrcIdx = 56;
	  section.data(44).dtTransOffset = 68;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Gainy_Gain
	  section.data(45).logicalSrcIdx = 57;
	  section.data(45).dtTransOffset = 69;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Integrator_IC
	  section.data(46).logicalSrcIdx = 58;
	  section.data(46).dtTransOffset = 70;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Backgain_Gain
	  section.data(47).logicalSrcIdx = 59;
	  section.data(47).dtTransOffset = 71;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Frontgain_Gain
	  section.data(48).logicalSrcIdx = 60;
	  section.data(48).dtTransOffset = 72;
	
	  ;% heli_p4_kalman_kf_r2020b_P.FrontmotorSaturation_UpperSat
	  section.data(49).logicalSrcIdx = 61;
	  section.data(49).dtTransOffset = 73;
	
	  ;% heli_p4_kalman_kf_r2020b_P.FrontmotorSaturation_LowerSat
	  section.data(50).logicalSrcIdx = 62;
	  section.data(50).dtTransOffset = 74;
	
	  ;% heli_p4_kalman_kf_r2020b_P.BackmotorSaturation_UpperSat
	  section.data(51).logicalSrcIdx = 63;
	  section.data(51).dtTransOffset = 75;
	
	  ;% heli_p4_kalman_kf_r2020b_P.BackmotorSaturation_LowerSat
	  section.data(52).logicalSrcIdx = 64;
	  section.data(52).dtTransOffset = 76;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 10;
      section.data(10)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOWatchdog
	  section.data(2).logicalSrcIdx = 66;
	  section.data(2).dtTransOffset = 3;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_EIInitial
	  section.data(3).logicalSrcIdx = 67;
	  section.data(3).dtTransOffset = 4;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POModes
	  section.data(4).logicalSrcIdx = 68;
	  section.data(4).dtTransOffset = 5;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POConfiguration
	  section.data(5).logicalSrcIdx = 69;
	  section.data(5).dtTransOffset = 6;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POAlignment
	  section.data(6).logicalSrcIdx = 70;
	  section.data(6).dtTransOffset = 7;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POPolarity
	  section.data(7).logicalSrcIdx = 71;
	  section.data(7).dtTransOffset = 8;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILReadEncoderTimebase_Clock
	  section.data(8).logicalSrcIdx = 72;
	  section.data(8).dtTransOffset = 9;
	
	  ;% heli_p4_kalman_kf_r2020b_P.StreamCall1_SendBufferSize
	  section.data(9).logicalSrcIdx = 73;
	  section.data(9).dtTransOffset = 10;
	
	  ;% heli_p4_kalman_kf_r2020b_P.StreamCall1_ReceiveBufferSize
	  section.data(10).logicalSrcIdx = 74;
	  section.data(10).dtTransOffset = 11;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 75;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 76;
	  section.data(2).dtTransOffset = 8;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_EIChannels
	  section.data(3).logicalSrcIdx = 77;
	  section.data(3).dtTransOffset = 16;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_EIQuadrature
	  section.data(4).logicalSrcIdx = 78;
	  section.data(4).dtTransOffset = 24;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POChannels
	  section.data(5).logicalSrcIdx = 79;
	  section.data(5).dtTransOffset = 25;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILReadEncoderTimebase_Channels
	  section.data(6).logicalSrcIdx = 80;
	  section.data(6).dtTransOffset = 33;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILReadEncoderTimebase_SamplesI
	  section.data(7).logicalSrcIdx = 81;
	  section.data(7).dtTransOffset = 36;
	
	  ;% heli_p4_kalman_kf_r2020b_P.StreamFormattedWrite_MaxUnits
	  section.data(8).logicalSrcIdx = 82;
	  section.data(8).dtTransOffset = 37;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_P.GameController_BufferSize
	  section.data(1).logicalSrcIdx = 83;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(6) = section;
      clear section
      
      section.nData     = 41;
      section.data(41)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_Active
	  section.data(1).logicalSrcIdx = 84;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOTerminate
	  section.data(2).logicalSrcIdx = 85;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOExit
	  section.data(3).logicalSrcIdx = 86;
	  section.data(3).dtTransOffset = 2;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOTerminate
	  section.data(4).logicalSrcIdx = 87;
	  section.data(4).dtTransOffset = 3;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOExit
	  section.data(5).logicalSrcIdx = 88;
	  section.data(5).dtTransOffset = 4;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POTerminate
	  section.data(6).logicalSrcIdx = 89;
	  section.data(6).dtTransOffset = 5;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POExit
	  section.data(7).logicalSrcIdx = 90;
	  section.data(7).dtTransOffset = 6;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_CKPStart
	  section.data(8).logicalSrcIdx = 91;
	  section.data(8).dtTransOffset = 7;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_CKPEnter
	  section.data(9).logicalSrcIdx = 92;
	  section.data(9).dtTransOffset = 8;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_CKStart
	  section.data(10).logicalSrcIdx = 93;
	  section.data(10).dtTransOffset = 9;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_CKEnter
	  section.data(11).logicalSrcIdx = 94;
	  section.data(11).dtTransOffset = 10;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AIPStart
	  section.data(12).logicalSrcIdx = 95;
	  section.data(12).dtTransOffset = 11;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AIPEnter
	  section.data(13).logicalSrcIdx = 96;
	  section.data(13).dtTransOffset = 12;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOPStart
	  section.data(14).logicalSrcIdx = 97;
	  section.data(14).dtTransOffset = 13;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOPEnter
	  section.data(15).logicalSrcIdx = 98;
	  section.data(15).dtTransOffset = 14;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOStart
	  section.data(16).logicalSrcIdx = 99;
	  section.data(16).dtTransOffset = 15;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOEnter
	  section.data(17).logicalSrcIdx = 100;
	  section.data(17).dtTransOffset = 16;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_AOReset
	  section.data(18).logicalSrcIdx = 101;
	  section.data(18).dtTransOffset = 17;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOPStart
	  section.data(19).logicalSrcIdx = 102;
	  section.data(19).dtTransOffset = 18;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOPEnter
	  section.data(20).logicalSrcIdx = 103;
	  section.data(20).dtTransOffset = 19;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOStart
	  section.data(21).logicalSrcIdx = 104;
	  section.data(21).dtTransOffset = 20;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOEnter
	  section.data(22).logicalSrcIdx = 105;
	  section.data(22).dtTransOffset = 21;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOReset
	  section.data(23).logicalSrcIdx = 106;
	  section.data(23).dtTransOffset = 22;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_EIPStart
	  section.data(24).logicalSrcIdx = 107;
	  section.data(24).dtTransOffset = 23;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_EIPEnter
	  section.data(25).logicalSrcIdx = 108;
	  section.data(25).dtTransOffset = 24;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_EIStart
	  section.data(26).logicalSrcIdx = 109;
	  section.data(26).dtTransOffset = 25;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_EIEnter
	  section.data(27).logicalSrcIdx = 110;
	  section.data(27).dtTransOffset = 26;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POPStart
	  section.data(28).logicalSrcIdx = 111;
	  section.data(28).dtTransOffset = 27;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POPEnter
	  section.data(29).logicalSrcIdx = 112;
	  section.data(29).dtTransOffset = 28;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POStart
	  section.data(30).logicalSrcIdx = 113;
	  section.data(30).dtTransOffset = 29;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POEnter
	  section.data(31).logicalSrcIdx = 114;
	  section.data(31).dtTransOffset = 30;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_POReset
	  section.data(32).logicalSrcIdx = 115;
	  section.data(32).dtTransOffset = 31;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_OOReset
	  section.data(33).logicalSrcIdx = 116;
	  section.data(33).dtTransOffset = 32;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOFinal
	  section.data(34).logicalSrcIdx = 117;
	  section.data(34).dtTransOffset = 33;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILInitialize_DOInitial
	  section.data(35).logicalSrcIdx = 118;
	  section.data(35).dtTransOffset = 34;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILReadEncoderTimebase_Active
	  section.data(36).logicalSrcIdx = 119;
	  section.data(36).dtTransOffset = 35;
	
	  ;% heli_p4_kalman_kf_r2020b_P.StreamCall1_NonBlocking
	  section.data(37).logicalSrcIdx = 120;
	  section.data(37).dtTransOffset = 36;
	
	  ;% heli_p4_kalman_kf_r2020b_P.StreamCall1_Active
	  section.data(38).logicalSrcIdx = 121;
	  section.data(38).dtTransOffset = 37;
	
	  ;% heli_p4_kalman_kf_r2020b_P.HILWriteAnalog_Active
	  section.data(39).logicalSrcIdx = 122;
	  section.data(39).dtTransOffset = 38;
	
	  ;% heli_p4_kalman_kf_r2020b_P.GameController_AutoCenter
	  section.data(40).logicalSrcIdx = 123;
	  section.data(40).dtTransOffset = 39;
	
	  ;% heli_p4_kalman_kf_r2020b_P.GameController_Enabled
	  section.data(41).logicalSrcIdx = 124;
	  section.data(41).dtTransOffset = 40;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(7) = section;
      clear section
      
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_P.HILReadEncoderTimebase_Overflow
	  section.data(1).logicalSrcIdx = 125;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_P.StringConstant_Value
	  section.data(2).logicalSrcIdx = 126;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p4_kalman_kf_r2020b_P.StreamCall1_URI
	  section.data(3).logicalSrcIdx = 127;
	  section.data(3).dtTransOffset = 256;
	
	  ;% heli_p4_kalman_kf_r2020b_P.StreamCall1_Endian
	  section.data(4).logicalSrcIdx = 128;
	  section.data(4).dtTransOffset = 257;
	
	  ;% heli_p4_kalman_kf_r2020b_P.ManualSwitch_CurrentSetting
	  section.data(5).logicalSrcIdx = 129;
	  section.data(5).dtTransOffset = 258;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Refp_c_CurrentSetting
	  section.data(6).logicalSrcIdx = 130;
	  section.data(6).dtTransOffset = 259;
	
	  ;% heli_p4_kalman_kf_r2020b_P.Refedot_c_CurrentSetting
	  section.data(7).logicalSrcIdx = 131;
	  section.data(7).dtTransOffset = 260;
	
	  ;% heli_p4_kalman_kf_r2020b_P.ManualSwitch_CurrentSetting_g
	  section.data(8).logicalSrcIdx = 132;
	  section.data(8).dtTransOffset = 261;
	
	  ;% heli_p4_kalman_kf_r2020b_P.GameController_ControllerNumber
	  section.data(9).logicalSrcIdx = 133;
	  section.data(9).dtTransOffset = 262;
	
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
    ;% Auto data (heli_p4_kalman_kf_r2020b_B)
    ;%
      section.nData     = 35;
      section.data(35)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_B.TravelCounttorad
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_B.TravelTransferFcn
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p4_kalman_kf_r2020b_B.PitchCounttorad
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% heli_p4_kalman_kf_r2020b_B.PitchTransferFcn
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% heli_p4_kalman_kf_r2020b_B.ElevationCounttorad
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% heli_p4_kalman_kf_r2020b_B.ElevationTransferFcn
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Switch
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Gain1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 16;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Gain2
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 19;
	
	  ;% heli_p4_kalman_kf_r2020b_B.ManualSwitch
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 22;
	
	  ;% heli_p4_kalman_kf_r2020b_B.FromWorkspace
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 23;
	
	  ;% heli_p4_kalman_kf_r2020b_B.RateTransitionx
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 25;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Joystick_gain_x
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 26;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Refp_c
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 27;
	
	  ;% heli_p4_kalman_kf_r2020b_B.RateTransitiony
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 28;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Joystick_gain_y
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 29;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Refedot_c
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 30;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Fr
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 31;
	
	  ;% heli_p4_kalman_kf_r2020b_B.ManualSwitch_n
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 33;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Integrator
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 34;
	
	  ;% heli_p4_kalman_kf_r2020b_B.u
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 36;
	
	  ;% heli_p4_kalman_kf_r2020b_B.Sum
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 38;
	
	  ;% heli_p4_kalman_kf_r2020b_B.TmpSignalConversionAtToFileInpo
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 39;
	
	  ;% heli_p4_kalman_kf_r2020b_B.FrontmotorSaturation
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 73;
	
	  ;% heli_p4_kalman_kf_r2020b_B.BackmotorSaturation
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 74;
	
	  ;% heli_p4_kalman_kf_r2020b_B.edotcedot
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 75;
	
	  ;% heli_p4_kalman_kf_r2020b_B.pcp
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 76;
	
	  ;% heli_p4_kalman_kf_r2020b_B.TmpSignalConversionAtIntegrator
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 77;
	
	  ;% heli_p4_kalman_kf_r2020b_B.x_bar_next
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 79;
	
	  ;% heli_p4_kalman_kf_r2020b_B.P_bar_next
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 85;
	
	  ;% heli_p4_kalman_kf_r2020b_B.x_hat
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 121;
	
	  ;% heli_p4_kalman_kf_r2020b_B.P_hat
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 127;
	
	  ;% heli_p4_kalman_kf_r2020b_B.P_diag
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 163;
	
	  ;% heli_p4_kalman_kf_r2020b_B.euler_rates
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 169;
	
	  ;% heli_p4_kalman_kf_r2020b_B.angles
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 172;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_B.StreamCall1_o2
	  section.data(1).logicalSrcIdx = 35;
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
    ;% Auto data (heli_p4_kalman_kf_r2020b_DW)
    ;%
      section.nData     = 14;
      section.data(14)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.UnitDelay_DSTATE
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.UnitDelay1_DSTATE
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 6;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_AIMinimums
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 42;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_AIMaximums
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 50;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_AOMinimums
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 58;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_AOMaximums
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 66;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_AOVoltages
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 74;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_FilterFrequency
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 82;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_POSortedFreqs
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 90;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_POValues
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 98;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.Memory_PreviousInput
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 106;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.RateTransitionx_Buffer0
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 116;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.RateTransitiony_Buffer0
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 117;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILWriteAnalog_Buffer
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 118;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.StreamCall1_Stream
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.GameController_Controller
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 16;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.HILReadEncoderTimebase_Task
	  section.data(1).logicalSrcIdx = 17;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 23;
      section.data(23)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.FromWorkspace_PWORK.TimePtr
	  section.data(1).logicalSrcIdx = 18;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.Scope_PWORK.LoggedData
	  section.data(2).logicalSrcIdx = 19;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.ToFile_PWORK.FilePtr
	  section.data(3).logicalSrcIdx = 20;
	  section.data(3).dtTransOffset = 2;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.e_imuve_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 21;
	  section.data(4).dtTransOffset = 3;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.edot_imuvedot_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 22;
	  section.data(5).dtTransOffset = 6;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.lambdadot_imuvlambdadot_PWORK.LoggedData
	  section.data(6).logicalSrcIdx = 23;
	  section.data(6).dtTransOffset = 9;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.p_imuvp_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 24;
	  section.data(7).dtTransOffset = 12;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.pdot_imuvpdot_PWORK.LoggedData
	  section.data(8).logicalSrcIdx = 25;
	  section.data(8).dtTransOffset = 15;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.ElevationScoperads_PWORK.LoggedData
	  section.data(9).logicalSrcIdx = 26;
	  section.data(9).dtTransOffset = 18;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.ElevationScoperad_PWORK.LoggedData
	  section.data(10).logicalSrcIdx = 27;
	  section.data(10).dtTransOffset = 19;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.PitchScoperad_PWORK.LoggedData
	  section.data(11).logicalSrcIdx = 28;
	  section.data(11).dtTransOffset = 20;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.PtichrateScoperads_PWORK.LoggedData
	  section.data(12).logicalSrcIdx = 29;
	  section.data(12).dtTransOffset = 21;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.TravelrateScoperads_PWORK.LoggedData
	  section.data(13).logicalSrcIdx = 30;
	  section.data(13).dtTransOffset = 22;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.TravelScoperad_PWORK.LoggedData
	  section.data(14).logicalSrcIdx = 31;
	  section.data(14).dtTransOffset = 23;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILWriteAnalog_PWORK
	  section.data(15).logicalSrcIdx = 32;
	  section.data(15).dtTransOffset = 24;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.Connected_PWORK.LoggedData
	  section.data(16).logicalSrcIdx = 33;
	  section.data(16).dtTransOffset = 25;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.XScope_PWORK.LoggedData
	  section.data(17).logicalSrcIdx = 34;
	  section.data(17).dtTransOffset = 26;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.YScope_PWORK.LoggedData
	  section.data(18).logicalSrcIdx = 35;
	  section.data(18).dtTransOffset = 27;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.VdScope_PWORK.LoggedData
	  section.data(19).logicalSrcIdx = 36;
	  section.data(19).dtTransOffset = 28;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.VsScope_PWORK.LoggedData
	  section.data(20).logicalSrcIdx = 37;
	  section.data(20).dtTransOffset = 29;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.edotandecdot_PWORK.LoggedData
	  section.data(21).logicalSrcIdx = 38;
	  section.data(21).dtTransOffset = 30;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.p2Run_PWORK.FilePtr
	  section.data(22).logicalSrcIdx = 39;
	  section.data(22).dtTransOffset = 32;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.pcScoperad_PWORK.LoggedData
	  section.data(23).logicalSrcIdx = 40;
	  section.data(23).dtTransOffset = 33;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_ClockModes
	  section.data(1).logicalSrcIdx = 41;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_QuadratureModes
	  section.data(2).logicalSrcIdx = 42;
	  section.data(2).dtTransOffset = 3;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_InitialEICounts
	  section.data(3).logicalSrcIdx = 43;
	  section.data(3).dtTransOffset = 11;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_POModeValues
	  section.data(4).logicalSrcIdx = 44;
	  section.data(4).dtTransOffset = 19;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_POAlignValues
	  section.data(5).logicalSrcIdx = 45;
	  section.data(5).dtTransOffset = 27;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_POPolarityVals
	  section.data(6).logicalSrcIdx = 46;
	  section.data(6).dtTransOffset = 35;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.HILReadEncoderTimebase_Buffer
	  section.data(7).logicalSrcIdx = 47;
	  section.data(7).dtTransOffset = 43;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.HILInitialize_POSortedChans
	  section.data(1).logicalSrcIdx = 48;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(8) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.FromWorkspace_IWORK.PrevIndex
	  section.data(1).logicalSrcIdx = 49;
	  section.data(1).dtTransOffset = 0;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.ToFile_IWORK.Count
	  section.data(2).logicalSrcIdx = 50;
	  section.data(2).dtTransOffset = 1;
	
	  ;% heli_p4_kalman_kf_r2020b_DW.p2Run_IWORK.Count
	  section.data(3).logicalSrcIdx = 51;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(9) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% heli_p4_kalman_kf_r2020b_DW.StreamCall1_State
	  section.data(1).logicalSrcIdx = 52;
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


  targMap.checksum0 = 3609982127;
  targMap.checksum1 = 2178774664;
  targMap.checksum2 = 3579754462;
  targMap.checksum3 = 592239552;

