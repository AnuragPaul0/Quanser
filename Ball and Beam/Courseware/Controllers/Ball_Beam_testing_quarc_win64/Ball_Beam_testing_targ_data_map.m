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
        ;% Auto data (Ball_Beam_testing_P)
        ;%
            section.nData     = 9;
            section.data(9)  = dumData; %prealloc

                    ;% Ball_Beam_testing_P.K_AMP
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_P.K_BS
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% Ball_Beam_testing_P.K_ENC
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% Ball_Beam_testing_P.THETA_OFF
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% Ball_Beam_testing_P.VMAX_AMP
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% Ball_Beam_testing_P.VMAX_DAC
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% Ball_Beam_testing_P.InitialTimes_const
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% Ball_Beam_testing_P.ReadingZero_const
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% Ball_Beam_testing_P.Constantcm_gain
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% Ball_Beam_testing_P.HILReadEncoder_channels
                    section.data(1).logicalSrcIdx = 9;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_P.HILWriteAnalog_channels
                    section.data(2).logicalSrcIdx = 10;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section

            section.nData     = 22;
            section.data(22)  = dumData; %prealloc

                    ;% Ball_Beam_testing_P.HILInitialize_OOTerminate
                    section.data(1).logicalSrcIdx = 11;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_P.HILInitialize_OOExit
                    section.data(2).logicalSrcIdx = 12;
                    section.data(2).dtTransOffset = 1;

                    ;% Ball_Beam_testing_P.HILInitialize_OOStart
                    section.data(3).logicalSrcIdx = 13;
                    section.data(3).dtTransOffset = 2;

                    ;% Ball_Beam_testing_P.HILInitialize_OOEnter
                    section.data(4).logicalSrcIdx = 14;
                    section.data(4).dtTransOffset = 3;

                    ;% Ball_Beam_testing_P.HILInitialize_AOFinal
                    section.data(5).logicalSrcIdx = 15;
                    section.data(5).dtTransOffset = 4;

                    ;% Ball_Beam_testing_P.HILInitialize_POFinal
                    section.data(6).logicalSrcIdx = 16;
                    section.data(6).dtTransOffset = 5;

                    ;% Ball_Beam_testing_P.HILInitialize_AIHigh
                    section.data(7).logicalSrcIdx = 17;
                    section.data(7).dtTransOffset = 6;

                    ;% Ball_Beam_testing_P.HILInitialize_AILow
                    section.data(8).logicalSrcIdx = 18;
                    section.data(8).dtTransOffset = 7;

                    ;% Ball_Beam_testing_P.HILInitialize_AOHigh
                    section.data(9).logicalSrcIdx = 19;
                    section.data(9).dtTransOffset = 8;

                    ;% Ball_Beam_testing_P.HILInitialize_AOLow
                    section.data(10).logicalSrcIdx = 20;
                    section.data(10).dtTransOffset = 9;

                    ;% Ball_Beam_testing_P.HILInitialize_AOInitial
                    section.data(11).logicalSrcIdx = 21;
                    section.data(11).dtTransOffset = 10;

                    ;% Ball_Beam_testing_P.HILInitialize_AOWatchdog
                    section.data(12).logicalSrcIdx = 22;
                    section.data(12).dtTransOffset = 11;

                    ;% Ball_Beam_testing_P.HILInitialize_POFrequency
                    section.data(13).logicalSrcIdx = 23;
                    section.data(13).dtTransOffset = 12;

                    ;% Ball_Beam_testing_P.HILInitialize_POLeading
                    section.data(14).logicalSrcIdx = 24;
                    section.data(14).dtTransOffset = 13;

                    ;% Ball_Beam_testing_P.HILInitialize_POTrailing
                    section.data(15).logicalSrcIdx = 25;
                    section.data(15).dtTransOffset = 14;

                    ;% Ball_Beam_testing_P.HILInitialize_POInitial
                    section.data(16).logicalSrcIdx = 26;
                    section.data(16).dtTransOffset = 15;

                    ;% Ball_Beam_testing_P.HILInitialize_POWatchdog
                    section.data(17).logicalSrcIdx = 27;
                    section.data(17).dtTransOffset = 16;

                    ;% Ball_Beam_testing_P.Constant_Value
                    section.data(18).logicalSrcIdx = 28;
                    section.data(18).dtTransOffset = 17;

                    ;% Ball_Beam_testing_P.cmm_Gain
                    section.data(19).logicalSrcIdx = 29;
                    section.data(19).dtTransOffset = 18;

                    ;% Ball_Beam_testing_P.Gain_Gain
                    section.data(20).logicalSrcIdx = 30;
                    section.data(20).dtTransOffset = 19;

                    ;% Ball_Beam_testing_P.Constant_Value_j
                    section.data(21).logicalSrcIdx = 31;
                    section.data(21).dtTransOffset = 20;

                    ;% Ball_Beam_testing_P.DirectionConventionRightHandsys
                    section.data(22).logicalSrcIdx = 32;
                    section.data(22).dtTransOffset = 21;

            nTotData = nTotData + section.nData;
            paramMap.sections(3) = section;
            clear section

            section.nData     = 8;
            section.data(8)  = dumData; %prealloc

                    ;% Ball_Beam_testing_P.HILInitialize_CKChannels
                    section.data(1).logicalSrcIdx = 33;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_P.HILInitialize_DOWatchdog
                    section.data(2).logicalSrcIdx = 34;
                    section.data(2).dtTransOffset = 3;

                    ;% Ball_Beam_testing_P.HILInitialize_EIInitial
                    section.data(3).logicalSrcIdx = 35;
                    section.data(3).dtTransOffset = 4;

                    ;% Ball_Beam_testing_P.HILInitialize_POModes
                    section.data(4).logicalSrcIdx = 36;
                    section.data(4).dtTransOffset = 5;

                    ;% Ball_Beam_testing_P.HILInitialize_POConfiguration
                    section.data(5).logicalSrcIdx = 37;
                    section.data(5).dtTransOffset = 6;

                    ;% Ball_Beam_testing_P.HILInitialize_POAlignment
                    section.data(6).logicalSrcIdx = 38;
                    section.data(6).dtTransOffset = 7;

                    ;% Ball_Beam_testing_P.HILInitialize_POPolarity
                    section.data(7).logicalSrcIdx = 39;
                    section.data(7).dtTransOffset = 8;

                    ;% Ball_Beam_testing_P.HILReadAnalogTimebase_Clock
                    section.data(8).logicalSrcIdx = 40;
                    section.data(8).dtTransOffset = 9;

            nTotData = nTotData + section.nData;
            paramMap.sections(4) = section;
            clear section

            section.nData     = 8;
            section.data(8)  = dumData; %prealloc

                    ;% Ball_Beam_testing_P.HILInitialize_AIChannels
                    section.data(1).logicalSrcIdx = 41;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_P.HILInitialize_AOChannels
                    section.data(2).logicalSrcIdx = 42;
                    section.data(2).dtTransOffset = 8;

                    ;% Ball_Beam_testing_P.HILInitialize_DOChannels
                    section.data(3).logicalSrcIdx = 43;
                    section.data(3).dtTransOffset = 16;

                    ;% Ball_Beam_testing_P.HILInitialize_EIChannels
                    section.data(4).logicalSrcIdx = 44;
                    section.data(4).dtTransOffset = 24;

                    ;% Ball_Beam_testing_P.HILInitialize_EIQuadrature
                    section.data(5).logicalSrcIdx = 45;
                    section.data(5).dtTransOffset = 32;

                    ;% Ball_Beam_testing_P.HILInitialize_POChannels
                    section.data(6).logicalSrcIdx = 46;
                    section.data(6).dtTransOffset = 33;

                    ;% Ball_Beam_testing_P.HILReadAnalogTimebase_Channels
                    section.data(7).logicalSrcIdx = 47;
                    section.data(7).dtTransOffset = 41;

                    ;% Ball_Beam_testing_P.HILReadAnalogTimebase_SamplesIn
                    section.data(8).logicalSrcIdx = 48;
                    section.data(8).dtTransOffset = 43;

            nTotData = nTotData + section.nData;
            paramMap.sections(5) = section;
            clear section

            section.nData     = 38;
            section.data(38)  = dumData; %prealloc

                    ;% Ball_Beam_testing_P.HILInitialize_Active
                    section.data(1).logicalSrcIdx = 49;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_P.HILInitialize_AOTerminate
                    section.data(2).logicalSrcIdx = 50;
                    section.data(2).dtTransOffset = 1;

                    ;% Ball_Beam_testing_P.HILInitialize_AOExit
                    section.data(3).logicalSrcIdx = 51;
                    section.data(3).dtTransOffset = 2;

                    ;% Ball_Beam_testing_P.HILInitialize_DOTerminate
                    section.data(4).logicalSrcIdx = 52;
                    section.data(4).dtTransOffset = 3;

                    ;% Ball_Beam_testing_P.HILInitialize_DOExit
                    section.data(5).logicalSrcIdx = 53;
                    section.data(5).dtTransOffset = 4;

                    ;% Ball_Beam_testing_P.HILInitialize_POTerminate
                    section.data(6).logicalSrcIdx = 54;
                    section.data(6).dtTransOffset = 5;

                    ;% Ball_Beam_testing_P.HILInitialize_POExit
                    section.data(7).logicalSrcIdx = 55;
                    section.data(7).dtTransOffset = 6;

                    ;% Ball_Beam_testing_P.HILInitialize_CKPStart
                    section.data(8).logicalSrcIdx = 56;
                    section.data(8).dtTransOffset = 7;

                    ;% Ball_Beam_testing_P.HILInitialize_CKPEnter
                    section.data(9).logicalSrcIdx = 57;
                    section.data(9).dtTransOffset = 8;

                    ;% Ball_Beam_testing_P.HILInitialize_CKStart
                    section.data(10).logicalSrcIdx = 58;
                    section.data(10).dtTransOffset = 9;

                    ;% Ball_Beam_testing_P.HILInitialize_CKEnter
                    section.data(11).logicalSrcIdx = 59;
                    section.data(11).dtTransOffset = 10;

                    ;% Ball_Beam_testing_P.HILInitialize_AIPStart
                    section.data(12).logicalSrcIdx = 60;
                    section.data(12).dtTransOffset = 11;

                    ;% Ball_Beam_testing_P.HILInitialize_AIPEnter
                    section.data(13).logicalSrcIdx = 61;
                    section.data(13).dtTransOffset = 12;

                    ;% Ball_Beam_testing_P.HILInitialize_AOPStart
                    section.data(14).logicalSrcIdx = 62;
                    section.data(14).dtTransOffset = 13;

                    ;% Ball_Beam_testing_P.HILInitialize_AOPEnter
                    section.data(15).logicalSrcIdx = 63;
                    section.data(15).dtTransOffset = 14;

                    ;% Ball_Beam_testing_P.HILInitialize_AOStart
                    section.data(16).logicalSrcIdx = 64;
                    section.data(16).dtTransOffset = 15;

                    ;% Ball_Beam_testing_P.HILInitialize_AOEnter
                    section.data(17).logicalSrcIdx = 65;
                    section.data(17).dtTransOffset = 16;

                    ;% Ball_Beam_testing_P.HILInitialize_AOReset
                    section.data(18).logicalSrcIdx = 66;
                    section.data(18).dtTransOffset = 17;

                    ;% Ball_Beam_testing_P.HILInitialize_DOPStart
                    section.data(19).logicalSrcIdx = 67;
                    section.data(19).dtTransOffset = 18;

                    ;% Ball_Beam_testing_P.HILInitialize_DOPEnter
                    section.data(20).logicalSrcIdx = 68;
                    section.data(20).dtTransOffset = 19;

                    ;% Ball_Beam_testing_P.HILInitialize_DOStart
                    section.data(21).logicalSrcIdx = 69;
                    section.data(21).dtTransOffset = 20;

                    ;% Ball_Beam_testing_P.HILInitialize_DOEnter
                    section.data(22).logicalSrcIdx = 70;
                    section.data(22).dtTransOffset = 21;

                    ;% Ball_Beam_testing_P.HILInitialize_DOReset
                    section.data(23).logicalSrcIdx = 71;
                    section.data(23).dtTransOffset = 22;

                    ;% Ball_Beam_testing_P.HILInitialize_EIPStart
                    section.data(24).logicalSrcIdx = 72;
                    section.data(24).dtTransOffset = 23;

                    ;% Ball_Beam_testing_P.HILInitialize_EIPEnter
                    section.data(25).logicalSrcIdx = 73;
                    section.data(25).dtTransOffset = 24;

                    ;% Ball_Beam_testing_P.HILInitialize_EIStart
                    section.data(26).logicalSrcIdx = 74;
                    section.data(26).dtTransOffset = 25;

                    ;% Ball_Beam_testing_P.HILInitialize_EIEnter
                    section.data(27).logicalSrcIdx = 75;
                    section.data(27).dtTransOffset = 26;

                    ;% Ball_Beam_testing_P.HILInitialize_POPStart
                    section.data(28).logicalSrcIdx = 76;
                    section.data(28).dtTransOffset = 27;

                    ;% Ball_Beam_testing_P.HILInitialize_POPEnter
                    section.data(29).logicalSrcIdx = 77;
                    section.data(29).dtTransOffset = 28;

                    ;% Ball_Beam_testing_P.HILInitialize_POStart
                    section.data(30).logicalSrcIdx = 78;
                    section.data(30).dtTransOffset = 29;

                    ;% Ball_Beam_testing_P.HILInitialize_POEnter
                    section.data(31).logicalSrcIdx = 79;
                    section.data(31).dtTransOffset = 30;

                    ;% Ball_Beam_testing_P.HILInitialize_POReset
                    section.data(32).logicalSrcIdx = 80;
                    section.data(32).dtTransOffset = 31;

                    ;% Ball_Beam_testing_P.HILInitialize_OOReset
                    section.data(33).logicalSrcIdx = 81;
                    section.data(33).dtTransOffset = 32;

                    ;% Ball_Beam_testing_P.HILInitialize_DOFinal
                    section.data(34).logicalSrcIdx = 82;
                    section.data(34).dtTransOffset = 33;

                    ;% Ball_Beam_testing_P.HILInitialize_DOInitial
                    section.data(35).logicalSrcIdx = 83;
                    section.data(35).dtTransOffset = 34;

                    ;% Ball_Beam_testing_P.HILReadAnalogTimebase_Active
                    section.data(36).logicalSrcIdx = 84;
                    section.data(36).dtTransOffset = 35;

                    ;% Ball_Beam_testing_P.HILReadEncoder_Active
                    section.data(37).logicalSrcIdx = 85;
                    section.data(37).dtTransOffset = 36;

                    ;% Ball_Beam_testing_P.HILWriteAnalog_Active
                    section.data(38).logicalSrcIdx = 86;
                    section.data(38).dtTransOffset = 37;

            nTotData = nTotData + section.nData;
            paramMap.sections(6) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Ball_Beam_testing_P.HILReadAnalogTimebase_OverflowM
                    section.data(1).logicalSrcIdx = 87;
                    section.data(1).dtTransOffset = 0;

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
        ;% Auto data (Ball_Beam_testing_B)
        ;%
            section.nData     = 5;
            section.data(5)  = dumData; %prealloc

                    ;% Ball_Beam_testing_B.HILReadAnalogTimebase_o1
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_B.SS01CalibrationmV
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% Ball_Beam_testing_B.cmm
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% Ball_Beam_testing_B.Gain
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 4;

                    ;% Ball_Beam_testing_B.DACBSaturationV
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 6;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Ball_Beam_testing_B.Compare
                    section.data(1).logicalSrcIdx = 5;
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
        nTotSects     = 7;
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
        ;% Auto data (Ball_Beam_testing_DW)
        ;%
            section.nData     = 9;
            section.data(9)  = dumData; %prealloc

                    ;% Ball_Beam_testing_DW.HILInitialize_AIMinimums
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_DW.HILInitialize_AIMaximums
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 8;

                    ;% Ball_Beam_testing_DW.HILInitialize_AOMinimums
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 16;

                    ;% Ball_Beam_testing_DW.HILInitialize_AOMaximums
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 24;

                    ;% Ball_Beam_testing_DW.HILInitialize_AOVoltages
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 32;

                    ;% Ball_Beam_testing_DW.HILInitialize_FilterFrequency
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 40;

                    ;% Ball_Beam_testing_DW.HILInitialize_POSortedFreqs
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 48;

                    ;% Ball_Beam_testing_DW.HILInitialize_POValues
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 56;

                    ;% Ball_Beam_testing_DW.HILReadAnalogTimebase_Buffer
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 64;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Ball_Beam_testing_DW.HILReadAnalogTimebase_Task
                    section.data(1).logicalSrcIdx = 9;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Ball_Beam_testing_DW.HILInitialize_Card
                    section.data(1).logicalSrcIdx = 10;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 5;
            section.data(5)  = dumData; %prealloc

                    ;% Ball_Beam_testing_DW.xcm_PWORK.LoggedData
                    section.data(1).logicalSrcIdx = 11;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_DW.HILReadEncoder_PWORK
                    section.data(2).logicalSrcIdx = 12;
                    section.data(2).dtTransOffset = 1;

                    ;% Ball_Beam_testing_DW.theta_ldeg_PWORK.LoggedData
                    section.data(3).logicalSrcIdx = 13;
                    section.data(3).dtTransOffset = 2;

                    ;% Ball_Beam_testing_DW.HILWriteAnalog_PWORK
                    section.data(4).logicalSrcIdx = 14;
                    section.data(4).dtTransOffset = 3;

                    ;% Ball_Beam_testing_DW.VmV1_PWORK.LoggedData
                    section.data(5).logicalSrcIdx = 15;
                    section.data(5).dtTransOffset = 4;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
            clear section

            section.nData     = 8;
            section.data(8)  = dumData; %prealloc

                    ;% Ball_Beam_testing_DW.HILInitialize_ClockModes
                    section.data(1).logicalSrcIdx = 16;
                    section.data(1).dtTransOffset = 0;

                    ;% Ball_Beam_testing_DW.HILInitialize_DOStates
                    section.data(2).logicalSrcIdx = 17;
                    section.data(2).dtTransOffset = 3;

                    ;% Ball_Beam_testing_DW.HILInitialize_QuadratureModes
                    section.data(3).logicalSrcIdx = 18;
                    section.data(3).dtTransOffset = 11;

                    ;% Ball_Beam_testing_DW.HILInitialize_InitialEICounts
                    section.data(4).logicalSrcIdx = 19;
                    section.data(4).dtTransOffset = 19;

                    ;% Ball_Beam_testing_DW.HILInitialize_POModeValues
                    section.data(5).logicalSrcIdx = 20;
                    section.data(5).dtTransOffset = 27;

                    ;% Ball_Beam_testing_DW.HILInitialize_POAlignValues
                    section.data(6).logicalSrcIdx = 21;
                    section.data(6).dtTransOffset = 35;

                    ;% Ball_Beam_testing_DW.HILInitialize_POPolarityVals
                    section.data(7).logicalSrcIdx = 22;
                    section.data(7).dtTransOffset = 43;

                    ;% Ball_Beam_testing_DW.HILReadEncoder_Buffer
                    section.data(8).logicalSrcIdx = 23;
                    section.data(8).dtTransOffset = 51;

            nTotData = nTotData + section.nData;
            dworkMap.sections(5) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Ball_Beam_testing_DW.HILInitialize_POSortedChans
                    section.data(1).logicalSrcIdx = 24;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(6) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% Ball_Beam_testing_DW.HILInitialize_DOBits
                    section.data(1).logicalSrcIdx = 25;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(7) = section;
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


    targMap.checksum0 = 1002928623;
    targMap.checksum1 = 2751032461;
    targMap.checksum2 = 4272542429;
    targMap.checksum3 = 4269434791;

