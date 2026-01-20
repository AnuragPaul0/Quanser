    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 7;
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
        ;% Auto data (bb01_quick_start_P)
        ;%
            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% bb01_quick_start_P.Amplitudecm_gain
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% bb01_quick_start_P.HILWrite_analog_channels
                    section.data(1).logicalSrcIdx = 1;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section

            section.nData     = 35;
            section.data(35)  = dumData; %prealloc

                    ;% bb01_quick_start_P.Setpointm_Gain
                    section.data(1).logicalSrcIdx = 2;
                    section.data(1).dtTransOffset = 0;

                    ;% bb01_quick_start_P.HILInitialize_OOTerminate
                    section.data(2).logicalSrcIdx = 3;
                    section.data(2).dtTransOffset = 1;

                    ;% bb01_quick_start_P.HILInitialize_OOExit
                    section.data(3).logicalSrcIdx = 4;
                    section.data(3).dtTransOffset = 2;

                    ;% bb01_quick_start_P.HILInitialize_OOStart
                    section.data(4).logicalSrcIdx = 5;
                    section.data(4).dtTransOffset = 3;

                    ;% bb01_quick_start_P.HILInitialize_OOEnter
                    section.data(5).logicalSrcIdx = 6;
                    section.data(5).dtTransOffset = 4;

                    ;% bb01_quick_start_P.HILInitialize_AOFinal
                    section.data(6).logicalSrcIdx = 7;
                    section.data(6).dtTransOffset = 5;

                    ;% bb01_quick_start_P.HILInitialize_POFinal
                    section.data(7).logicalSrcIdx = 8;
                    section.data(7).dtTransOffset = 6;

                    ;% bb01_quick_start_P.HILInitialize_AIHigh
                    section.data(8).logicalSrcIdx = 9;
                    section.data(8).dtTransOffset = 7;

                    ;% bb01_quick_start_P.HILInitialize_AILow
                    section.data(9).logicalSrcIdx = 10;
                    section.data(9).dtTransOffset = 8;

                    ;% bb01_quick_start_P.HILInitialize_AOHigh
                    section.data(10).logicalSrcIdx = 11;
                    section.data(10).dtTransOffset = 9;

                    ;% bb01_quick_start_P.HILInitialize_AOLow
                    section.data(11).logicalSrcIdx = 12;
                    section.data(11).dtTransOffset = 10;

                    ;% bb01_quick_start_P.HILInitialize_AOInitial
                    section.data(12).logicalSrcIdx = 13;
                    section.data(12).dtTransOffset = 11;

                    ;% bb01_quick_start_P.HILInitialize_AOWatchdog
                    section.data(13).logicalSrcIdx = 14;
                    section.data(13).dtTransOffset = 12;

                    ;% bb01_quick_start_P.HILInitialize_EIFrequency
                    section.data(14).logicalSrcIdx = 15;
                    section.data(14).dtTransOffset = 13;

                    ;% bb01_quick_start_P.HILInitialize_POFrequency
                    section.data(15).logicalSrcIdx = 16;
                    section.data(15).dtTransOffset = 14;

                    ;% bb01_quick_start_P.HILInitialize_POInitial
                    section.data(16).logicalSrcIdx = 17;
                    section.data(16).dtTransOffset = 15;

                    ;% bb01_quick_start_P.SmoothSignalGenerator_InitialPh
                    section.data(17).logicalSrcIdx = 18;
                    section.data(17).dtTransOffset = 16;

                    ;% bb01_quick_start_P.SmoothSignalGenerator_Amplitude
                    section.data(18).logicalSrcIdx = 19;
                    section.data(18).dtTransOffset = 17;

                    ;% bb01_quick_start_P.SmoothSignalGenerator_Frequency
                    section.data(19).logicalSrcIdx = 20;
                    section.data(19).dtTransOffset = 18;

                    ;% bb01_quick_start_P.SS01CalibrationmV_Gain
                    section.data(20).logicalSrcIdx = 21;
                    section.data(20).dtTransOffset = 19;

                    ;% bb01_quick_start_P.BB01CalibrationmV_Gain
                    section.data(21).logicalSrcIdx = 22;
                    section.data(21).dtTransOffset = 20;

                    ;% bb01_quick_start_P.mtocm_Gain
                    section.data(22).logicalSrcIdx = 23;
                    section.data(22).dtTransOffset = 21;

                    ;% bb01_quick_start_P.ProportionalGain_Gain
                    section.data(23).logicalSrcIdx = 24;
                    section.data(23).dtTransOffset = 22;

                    ;% bb01_quick_start_P.NegFdbk_Gain
                    section.data(24).logicalSrcIdx = 25;
                    section.data(24).dtTransOffset = 23;

                    ;% bb01_quick_start_P.DiscreteTransferFcn_NumCoef
                    section.data(25).logicalSrcIdx = 26;
                    section.data(25).dtTransOffset = 24;

                    ;% bb01_quick_start_P.DiscreteTransferFcn_DenCoef
                    section.data(26).logicalSrcIdx = 27;
                    section.data(26).dtTransOffset = 26;

                    ;% bb01_quick_start_P.DiscreteTransferFcn_InitialStat
                    section.data(27).logicalSrcIdx = 28;
                    section.data(27).dtTransOffset = 28;

                    ;% bb01_quick_start_P.DerivativeGain_Gain
                    section.data(28).logicalSrcIdx = 29;
                    section.data(28).dtTransOffset = 29;

                    ;% bb01_quick_start_P.Saturation_UpperSat
                    section.data(29).logicalSrcIdx = 30;
                    section.data(29).dtTransOffset = 30;

                    ;% bb01_quick_start_P.Saturation_LowerSat
                    section.data(30).logicalSrcIdx = 31;
                    section.data(30).dtTransOffset = 31;

                    ;% bb01_quick_start_P.Counttorad_Gain
                    section.data(31).logicalSrcIdx = 32;
                    section.data(31).dtTransOffset = 32;

                    ;% bb01_quick_start_P.Subtract56deg_Bias
                    section.data(32).logicalSrcIdx = 33;
                    section.data(32).dtTransOffset = 33;

                    ;% bb01_quick_start_P.ServoGain_Gain
                    section.data(33).logicalSrcIdx = 34;
                    section.data(33).dtTransOffset = 34;

                    ;% bb01_quick_start_P.mtocm_Gain_a
                    section.data(34).logicalSrcIdx = 35;
                    section.data(34).dtTransOffset = 35;

                    ;% bb01_quick_start_P.Radiantodegree_Gain
                    section.data(35).logicalSrcIdx = 36;
                    section.data(35).dtTransOffset = 36;

            nTotData = nTotData + section.nData;
            paramMap.sections(3) = section;
            clear section

            section.nData     = 6;
            section.data(6)  = dumData; %prealloc

                    ;% bb01_quick_start_P.HILInitialize_CKChannels
                    section.data(1).logicalSrcIdx = 37;
                    section.data(1).dtTransOffset = 0;

                    ;% bb01_quick_start_P.HILInitialize_CKModes
                    section.data(2).logicalSrcIdx = 38;
                    section.data(2).dtTransOffset = 2;

                    ;% bb01_quick_start_P.HILInitialize_DOWatchdog
                    section.data(3).logicalSrcIdx = 39;
                    section.data(3).dtTransOffset = 4;

                    ;% bb01_quick_start_P.HILInitialize_EIInitial
                    section.data(4).logicalSrcIdx = 40;
                    section.data(4).dtTransOffset = 5;

                    ;% bb01_quick_start_P.HILInitialize_POModes
                    section.data(5).logicalSrcIdx = 41;
                    section.data(5).dtTransOffset = 6;

                    ;% bb01_quick_start_P.HILReadTimebase_Clock
                    section.data(6).logicalSrcIdx = 42;
                    section.data(6).dtTransOffset = 7;

            nTotData = nTotData + section.nData;
            paramMap.sections(4) = section;
            clear section

            section.nData     = 7;
            section.data(7)  = dumData; %prealloc

                    ;% bb01_quick_start_P.HILInitialize_AIChannels
                    section.data(1).logicalSrcIdx = 43;
                    section.data(1).dtTransOffset = 0;

                    ;% bb01_quick_start_P.HILInitialize_AOChannels
                    section.data(2).logicalSrcIdx = 44;
                    section.data(2).dtTransOffset = 4;

                    ;% bb01_quick_start_P.HILInitialize_EIChannels
                    section.data(3).logicalSrcIdx = 45;
                    section.data(3).dtTransOffset = 8;

                    ;% bb01_quick_start_P.HILInitialize_EIQuadrature
                    section.data(4).logicalSrcIdx = 46;
                    section.data(4).dtTransOffset = 12;

                    ;% bb01_quick_start_P.HILReadTimebase_SamplesInBuffer
                    section.data(5).logicalSrcIdx = 47;
                    section.data(5).dtTransOffset = 13;

                    ;% bb01_quick_start_P.HILReadTimebase_AnalogChannels
                    section.data(6).logicalSrcIdx = 48;
                    section.data(6).dtTransOffset = 14;

                    ;% bb01_quick_start_P.HILReadTimebase_EncoderChannels
                    section.data(7).logicalSrcIdx = 49;
                    section.data(7).dtTransOffset = 16;

            nTotData = nTotData + section.nData;
            paramMap.sections(5) = section;
            clear section

            section.nData     = 37;
            section.data(37)  = dumData; %prealloc

                    ;% bb01_quick_start_P.HILInitialize_Active
                    section.data(1).logicalSrcIdx = 50;
                    section.data(1).dtTransOffset = 0;

                    ;% bb01_quick_start_P.HILInitialize_AOTerminate
                    section.data(2).logicalSrcIdx = 51;
                    section.data(2).dtTransOffset = 1;

                    ;% bb01_quick_start_P.HILInitialize_AOExit
                    section.data(3).logicalSrcIdx = 52;
                    section.data(3).dtTransOffset = 2;

                    ;% bb01_quick_start_P.HILInitialize_DOTerminate
                    section.data(4).logicalSrcIdx = 53;
                    section.data(4).dtTransOffset = 3;

                    ;% bb01_quick_start_P.HILInitialize_DOExit
                    section.data(5).logicalSrcIdx = 54;
                    section.data(5).dtTransOffset = 4;

                    ;% bb01_quick_start_P.HILInitialize_POTerminate
                    section.data(6).logicalSrcIdx = 55;
                    section.data(6).dtTransOffset = 5;

                    ;% bb01_quick_start_P.HILInitialize_POExit
                    section.data(7).logicalSrcIdx = 56;
                    section.data(7).dtTransOffset = 6;

                    ;% bb01_quick_start_P.HILInitialize_CKPStart
                    section.data(8).logicalSrcIdx = 57;
                    section.data(8).dtTransOffset = 7;

                    ;% bb01_quick_start_P.HILInitialize_CKPEnter
                    section.data(9).logicalSrcIdx = 58;
                    section.data(9).dtTransOffset = 8;

                    ;% bb01_quick_start_P.HILInitialize_CKStart
                    section.data(10).logicalSrcIdx = 59;
                    section.data(10).dtTransOffset = 9;

                    ;% bb01_quick_start_P.HILInitialize_CKEnter
                    section.data(11).logicalSrcIdx = 60;
                    section.data(11).dtTransOffset = 10;

                    ;% bb01_quick_start_P.HILInitialize_AIPStart
                    section.data(12).logicalSrcIdx = 61;
                    section.data(12).dtTransOffset = 11;

                    ;% bb01_quick_start_P.HILInitialize_AIPEnter
                    section.data(13).logicalSrcIdx = 62;
                    section.data(13).dtTransOffset = 12;

                    ;% bb01_quick_start_P.HILInitialize_AOPStart
                    section.data(14).logicalSrcIdx = 63;
                    section.data(14).dtTransOffset = 13;

                    ;% bb01_quick_start_P.HILInitialize_AOPEnter
                    section.data(15).logicalSrcIdx = 64;
                    section.data(15).dtTransOffset = 14;

                    ;% bb01_quick_start_P.HILInitialize_AOStart
                    section.data(16).logicalSrcIdx = 65;
                    section.data(16).dtTransOffset = 15;

                    ;% bb01_quick_start_P.HILInitialize_AOEnter
                    section.data(17).logicalSrcIdx = 66;
                    section.data(17).dtTransOffset = 16;

                    ;% bb01_quick_start_P.HILInitialize_AOReset
                    section.data(18).logicalSrcIdx = 67;
                    section.data(18).dtTransOffset = 17;

                    ;% bb01_quick_start_P.HILInitialize_DOPStart
                    section.data(19).logicalSrcIdx = 68;
                    section.data(19).dtTransOffset = 18;

                    ;% bb01_quick_start_P.HILInitialize_DOPEnter
                    section.data(20).logicalSrcIdx = 69;
                    section.data(20).dtTransOffset = 19;

                    ;% bb01_quick_start_P.HILInitialize_DOStart
                    section.data(21).logicalSrcIdx = 70;
                    section.data(21).dtTransOffset = 20;

                    ;% bb01_quick_start_P.HILInitialize_DOEnter
                    section.data(22).logicalSrcIdx = 71;
                    section.data(22).dtTransOffset = 21;

                    ;% bb01_quick_start_P.HILInitialize_DOReset
                    section.data(23).logicalSrcIdx = 72;
                    section.data(23).dtTransOffset = 22;

                    ;% bb01_quick_start_P.HILInitialize_EIPStart
                    section.data(24).logicalSrcIdx = 73;
                    section.data(24).dtTransOffset = 23;

                    ;% bb01_quick_start_P.HILInitialize_EIPEnter
                    section.data(25).logicalSrcIdx = 74;
                    section.data(25).dtTransOffset = 24;

                    ;% bb01_quick_start_P.HILInitialize_EIStart
                    section.data(26).logicalSrcIdx = 75;
                    section.data(26).dtTransOffset = 25;

                    ;% bb01_quick_start_P.HILInitialize_EIEnter
                    section.data(27).logicalSrcIdx = 76;
                    section.data(27).dtTransOffset = 26;

                    ;% bb01_quick_start_P.HILInitialize_POPStart
                    section.data(28).logicalSrcIdx = 77;
                    section.data(28).dtTransOffset = 27;

                    ;% bb01_quick_start_P.HILInitialize_POPEnter
                    section.data(29).logicalSrcIdx = 78;
                    section.data(29).dtTransOffset = 28;

                    ;% bb01_quick_start_P.HILInitialize_POStart
                    section.data(30).logicalSrcIdx = 79;
                    section.data(30).dtTransOffset = 29;

                    ;% bb01_quick_start_P.HILInitialize_POEnter
                    section.data(31).logicalSrcIdx = 80;
                    section.data(31).dtTransOffset = 30;

                    ;% bb01_quick_start_P.HILInitialize_POReset
                    section.data(32).logicalSrcIdx = 81;
                    section.data(32).dtTransOffset = 31;

                    ;% bb01_quick_start_P.HILInitialize_OOReset
                    section.data(33).logicalSrcIdx = 82;
                    section.data(33).dtTransOffset = 32;

                    ;% bb01_quick_start_P.HILInitialize_DOFinal
                    section.data(34).logicalSrcIdx = 83;
                    section.data(34).dtTransOffset = 33;

                    ;% bb01_quick_start_P.HILInitialize_DOInitial
                    section.data(35).logicalSrcIdx = 84;
                    section.data(35).dtTransOffset = 34;

                    ;% bb01_quick_start_P.HILReadTimebase_Active
                    section.data(36).logicalSrcIdx = 85;
                    section.data(36).dtTransOffset = 35;

                    ;% bb01_quick_start_P.HILWrite_Active
                    section.data(37).logicalSrcIdx = 86;
                    section.data(37).dtTransOffset = 36;

            nTotData = nTotData + section.nData;
            paramMap.sections(6) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% bb01_quick_start_P.HILReadTimebase_OverflowMode
                    section.data(1).logicalSrcIdx = 87;
                    section.data(1).dtTransOffset = 0;

                    ;% bb01_quick_start_P.SPSource_CurrentSetting
                    section.data(2).logicalSrcIdx = 88;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(7) = section;
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
        nTotSects     = 1;
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
        ;% Auto data (bb01_quick_start_B)
        ;%
            section.nData     = 4;
            section.data(4)  = dumData; %prealloc

                    ;% bb01_quick_start_B.mtocm
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% bb01_quick_start_B.ServoGain
                    section.data(2).logicalSrcIdx = 2;
                    section.data(2).dtTransOffset = 2;

                    ;% bb01_quick_start_B.mtocm_e
                    section.data(3).logicalSrcIdx = 3;
                    section.data(3).dtTransOffset = 3;

                    ;% bb01_quick_start_B.Radiantodegree
                    section.data(4).logicalSrcIdx = 4;
                    section.data(4).dtTransOffset = 4;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
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
        nTotSects     = 6;
        sectIdxOffset = 1;

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
        ;% Auto data (bb01_quick_start_DW)
        ;%
            section.nData     = 9;
            section.data(9)  = dumData; %prealloc

                    ;% bb01_quick_start_DW.DiscreteTransferFcn_states
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% bb01_quick_start_DW.HILInitialize_AIMinimums
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% bb01_quick_start_DW.HILInitialize_AIMaximums
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 5;

                    ;% bb01_quick_start_DW.HILInitialize_AOMinimums
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 9;

                    ;% bb01_quick_start_DW.HILInitialize_AOMaximums
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 13;

                    ;% bb01_quick_start_DW.HILInitialize_AOVoltages
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 17;

                    ;% bb01_quick_start_DW.HILInitialize_FilterFrequency
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 21;

                    ;% bb01_quick_start_DW.HILReadTimebase_AnalogBuffer
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 25;

                    ;% bb01_quick_start_DW.DiscreteTransferFcn_tmp
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 27;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% bb01_quick_start_DW.HILInitialize_Card
                    section.data(1).logicalSrcIdx = 9;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% bb01_quick_start_DW.HILReadTimebase_Task
                    section.data(1).logicalSrcIdx = 10;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Amp
                    section.data(1).logicalSrcIdx = 11;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
            clear section

            section.nData     = 5;
            section.data(5)  = dumData; %prealloc

                    ;% bb01_quick_start_DW.BallPositioncm_PWORK.LoggedData
                    section.data(1).logicalSrcIdx = 12;
                    section.data(1).dtTransOffset = 0;

                    ;% bb01_quick_start_DW.CommandVoltage_PWORK.LoggedData
                    section.data(2).logicalSrcIdx = 13;
                    section.data(2).dtTransOffset = 1;

                    ;% bb01_quick_start_DW.HILWrite_PWORK
                    section.data(3).logicalSrcIdx = 14;
                    section.data(3).dtTransOffset = 2;

                    ;% bb01_quick_start_DW.RemoteSensorBallPositioncm_PWOR.LoggedData
                    section.data(4).logicalSrcIdx = 15;
                    section.data(4).dtTransOffset = 3;

                    ;% bb01_quick_start_DW.ServoAngledeg_PWORK.LoggedData
                    section.data(5).logicalSrcIdx = 16;
                    section.data(5).dtTransOffset = 4;

            nTotData = nTotData + section.nData;
            dworkMap.sections(5) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% bb01_quick_start_DW.HILInitialize_QuadratureModes
                    section.data(1).logicalSrcIdx = 17;
                    section.data(1).dtTransOffset = 0;

                    ;% bb01_quick_start_DW.HILInitialize_InitialEICounts
                    section.data(2).logicalSrcIdx = 18;
                    section.data(2).dtTransOffset = 4;

                    ;% bb01_quick_start_DW.HILReadTimebase_EncoderBuffer
                    section.data(3).logicalSrcIdx = 19;
                    section.data(3).dtTransOffset = 8;

            nTotData = nTotData + section.nData;
            dworkMap.sections(6) = section;
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


    targMap.checksum0 = 1578729505;
    targMap.checksum1 = 1401491924;
    targMap.checksum2 = 17512705;
    targMap.checksum3 = 2220623830;

